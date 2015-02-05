
#include "SignalDownload.h"

#define SIGNALDOWN_DEBUG 0

#define LOWSPEEDLIMIT 12

//��չ����
#define SD_curl_easy_setopt_EXT(A,B,C)			\
	res=curl_easy_setopt(A,B,C);				\
	if(CURLE_OK != res)  /* we failed */		\
	{											\
	fprintf(stderr, "ERROR:%s,%d,curl told us %s\n", __FILE__,__LINE__,curl_easy_strerror(res));	\
	fclose(outfile);						\
	outfile=NULL;							\
	curl_easy_cleanup(A);				\
	A=NULL;								\
	return false;							\
	}

//��չ����
#define SD_curl_easy_setopt_EXT_NOFILE(A,B,C)	\
	res=curl_easy_setopt(A,B,C);				\
	if(CURLE_OK != res)  /* we failed */		\
	{											\
	fprintf(stderr, "ERROR:%s,%d,curl told us %s\n", __FILE__,__LINE__,curl_easy_strerror(res));	\
	curl_easy_cleanup(A);					\
	A=NULL;									\
	return false;							\
	}

//��չ����
#define SD_curl_easy_getinfo_EXT_NOFILE(A,B,C)	\
	res=curl_easy_getinfo(A,B,C);				\
	if(CURLE_OK != res)  /* we failed */		\
	{											\
	fprintf(stderr, "ERROR:%s,%d,curl told us %s\n", __FILE__,__LINE__,curl_easy_strerror(res));	\
	curl_easy_cleanup(A);					\
	A=NULL;									\
	return false;							\
	}

//���ز�д���ļ��� �ص�����
/*
typedef size_t (*curl_write_callback)(char *buffer,
size_t size,
size_t nitems,
void *outstream);
*/

size_t SD_WriteFunc_FILE(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	return fwrite(ptr, size, nmemb, stream);
}

size_t SD_WriteFunc_STR(void *ptr, size_t size, size_t nmemb, void *stream)
{
	SignalDownload *p=(SignalDownload *)stream;

	int res_size;
	res_size = size * nmemb;

	if(0==p->totalstrlen)
		p->outstr = (char*) calloc(1,res_size + 1);
	else
		p->outstr =(char*) realloc(p->outstr, p->totalstrlen+res_size + 1);

	memcpy(p->outstr + p->totalstrlen, ptr, res_size);
	p->totalstrlen += res_size;

	return res_size;

}


//ʵʱ���ػ��ϴ����̵Ļص�����
/*
typedef int (*curl_progress_callback)(void *clientp,
double dltotal,
double dlnow,
double ultotal,
double ulnow);
*/
int SD_ProgressFunc(void *clientp,
					double dltotal, 
					double dlnow, 
					double ultotal,
					double ulnow)
{
	SignalDownload *s=(SignalDownload *)clientp;
	s->completesize=dlnow;
	s->totalsize=dltotal;

	fprintf(stderr,"%g / %g (%g %%)\r\n", dlnow, dltotal, dlnow*100.0/dltotal);

	//ע�����ﷵ�� 0Ϊ��������
	//���� 1Ϊ�˳����ؽ��̡�ֱ������ʧ��(��������ȡ�����ء�ʹ��)
	return 	0;
}

//url		URL��ַ 
//outflag	1�ļ�ģʽ 0�ַ���ģʽ
//filename	�ļ�·��
//proxyflag	1�������� 0��������
//failstr	ʧ����Ϣ
//timeout	�趨���س�ʱʱ��
//���		���سɹ���ʧ��
//ִ������
bool SignalDownload::HTTPDownload(const TCHAR *url,
								  bool outflag,const TCHAR *filename,
								  bool proxyflag,TCHAR *proxystr,
								  TCHAR *failstr,long timeout=10,unsigned  long startsize=0)
{
	completesize=0;
	totalsize=0;
	//��ʼ��
	curl = curl_easy_init();
	if(NULL == curl)
		return false;

	if(outflag)
	{
		//�򿪴�д�ļ�
		outfile = fopen(filename, "wb");
		if(NULL== outfile)
		{
			curl_easy_cleanup(curl);
			curl=NULL;
			return false;
		}
	}
	else
	{
		totalstrlen=0;
		if(NULL!=outstr)
		{
			free(outstr);
			outstr=NULL;
		}
	}
	//����URL��ַ
	SD_curl_easy_setopt_EXT(curl, CURLOPT_URL, url);
	/*
	//������ʼ����λ��
	sprintf(sizestr,"%I64u-",startsize);
	fseek(outfile,startsize,SEEK_SET);
	SD_curl_easy_setopt_EXT(curl, CURLOPT_RANGE, sizestr);
	*/
	if(proxyflag)
	{
		SD_curl_easy_setopt_EXT(curl, CURLOPT_PROXY, proxystr);
	}

	if(outflag)
	{	
		//����д����ļ�ָ��
		SD_curl_easy_setopt_EXT(curl, CURLOPT_WRITEDATA, outfile);
		//����д��ص�����
		SD_curl_easy_setopt_EXT(curl, CURLOPT_WRITEFUNCTION, SD_WriteFunc_FILE);
	}
	else
	{
		SD_curl_easy_setopt_EXT(curl, CURLOPT_WRITEDATA, this);
		//����д��ص�����
		SD_curl_easy_setopt_EXT(curl, CURLOPT_WRITEFUNCTION, SD_WriteFunc_STR);
	}

	//�����޽��̺���
	//SD_curl_easy_setopt_EXT(curl, CURLOPT_NOPROGRESS, FALSE);
	SD_curl_easy_setopt_EXT(curl, CURLOPT_NOPROGRESS, TRUE);
	//���ý��̻ص�����
	//SD_curl_easy_setopt_EXT(curl, CURLOPT_PROGRESSFUNCTION, SD_ProgressFunc);
	//���ý��̻ص����������Զ����
	//SD_curl_easy_setopt_EXT(curl, CURLOPT_PROGRESSDATA, this);
	//���������ٶ�=0ʱ N���˳�
	//	SD_curl_easy_setopt_EXT(curl, CURLOPT_TIMEOUT, timeout);���Բ��ܳ��֡���Ȼֻ����timeout��
	//����URL��ַ���� ����N�κ��Ƴ�
	SD_curl_easy_setopt_EXT(curl, CURLOPT_CONNECTTIMEOUT, timeout);
	//��������ٶȡ�Ϊ����;������
	SD_curl_easy_setopt_EXT(curl, CURLOPT_LOW_SPEED_LIMIT, LOWSPEEDLIMIT);
	SD_curl_easy_setopt_EXT(curl, CURLOPT_LOW_SPEED_TIME, timeout);

	if(SIGNALDOWN_DEBUG)
		SD_curl_easy_setopt_EXT(curl, CURLOPT_VERBOSE , 1);
	//��ʼִ��
	res = curl_easy_perform(curl);
	if(CURLE_OK != res)  /* we failed */				
	{										
		sprintf(failstr,"HTTPDownload %s",curl_easy_strerror(res));

		fprintf(stderr, "curl result %s\n",curl_easy_strerror(res));	
		long i=totalstrlen;
	if(outflag)
	{
		fclose(outfile);
		outfile=NULL;
	}
	else
	{
		totalstrlen=0;
		if(NULL!=outstr)
		{
			free(outstr);
			outstr=NULL;
		}
	}


		curl_easy_cleanup(curl);
		curl=NULL;
		return false;							
	}	

	if(outflag)
	{
		//�ر��ļ�
		fclose(outfile);
		outfile=NULL;
	}

	curl_easy_cleanup(curl);
	curl=NULL;


	return true;
}

void SignalDownload::InitData()
{
	curl_global_init(CURL_GLOBAL_ALL);
	totalstrlen=0;
	outstr=NULL;
}

void SignalDownload::DestroyData()
{
	curl_global_cleanup();

	if(NULL!=outstr)
	{
		free(outstr);
		outstr=NULL;
	}
}