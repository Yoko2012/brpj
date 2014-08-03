#include "stdafx.h"
#include "SignalDownload.h"

#define SIGNALDOWN_DEBUG 1


#define LOWSPEEDLIMIT 32

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
size_t SD_WriteFunc(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	return fwrite(ptr, size, nmemb, stream);
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
//filename	�ļ�·��
//timeout	�趨���س�ʱʱ��
//���		���سɹ���ʧ��
//ִ������
bool SignalDownload::HTTPDownload(const char *url,const char *filename,TCHAR *failstr,long timeout=10,unsigned long long startsize=0)
{
	completesize=0;
	totalsize=0;
	//��ʼ��
	curl = curl_easy_init();
	if(NULL == curl)
		return false;
	//�򿪴�д�ļ�
	outfile = fopen(filename, "wb");
	if(NULL== outfile)
	{
		curl_easy_cleanup(curl);
		curl=NULL;
		return false;
	}
	//����URL��ַ
	SD_curl_easy_setopt_EXT(curl, CURLOPT_URL, url);
	/*
	//������ʼ����λ��
	sprintf(sizestr,"%I64u-",startsize);
	fseek(outfile,startsize,SEEK_SET);
	SD_curl_easy_setopt_EXT(curl, CURLOPT_RANGE, sizestr);
	*/
//	SD_curl_easy_setopt_EXT(curl, CURLOPT_PROXY, "10.142.50.140:808");
	//����д����ļ�ָ��
	SD_curl_easy_setopt_EXT(curl, CURLOPT_WRITEDATA, outfile);
	//����д��ص�����
	SD_curl_easy_setopt_EXT(curl, CURLOPT_WRITEFUNCTION, SD_WriteFunc);

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
		fclose(outfile);
		outfile=NULL;
		curl_easy_cleanup(curl);
		curl=NULL;
		return false;							
	}	

	//�ر��ļ�
	fclose(outfile);
	outfile=NULL;

	curl_easy_cleanup(curl);
	curl=NULL;


	return true;
}

void SignalDownload::InitData()
{
	curl_global_init(CURL_GLOBAL_ALL);
}

void SignalDownload::DestroyData()
{
	curl_global_cleanup();
}