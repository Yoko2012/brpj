#ifndef __SIGNAL_DOWNLOAD_H
#define __SIGNAL_DOWNLOAD_H
#include "typedefine.h"
#include "tchar.h"
class SignalDownload
{
public:
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
		TCHAR *failstr,long timeout,unsigned  long startsize);
	//��ǰ����ֽ�
	double completesize;
	//�ļ����ֽ�
	double totalsize;

	void InitData();
	void DestroyData();

	char *outstr ;
	long totalstrlen;
private:
	CURL *curl;
	CURLcode res;

	FILE *outfile;
	char sizestr[128];

};

#endif