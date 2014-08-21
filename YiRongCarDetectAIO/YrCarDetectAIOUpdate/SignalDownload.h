#ifndef __SIGNAL_DOWNLOAD_H
#define __SIGNAL_DOWNLOAD_H
#include "typedefine.h"
#include "tchar.h"


class SignalDownload
{
public:
	//url		URL��ַ 
	//filename	�ļ�·��
	//timeout	�趨���س�ʱʱ��
	//start		��ʼ�����ֽ�
	//���		���سɹ���ʧ��
	//ִ������
	bool HTTPDownload(const char *url,const char *filename,TCHAR *failstr,long timeout,unsigned long long startsize);
	//��ǰ����ֽ�
	double completesize;
	//�ļ����ֽ�
	double totalsize;

	static void InitData();
	static void DestroyData();

private:
	CURL *curl;
	CURLcode res;
	FILE *outfile;
	char sizestr[128];
};

#endif