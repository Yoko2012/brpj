#ifndef __SIGNAL_DOWNLOAD_H
#define __SIGNAL_DOWNLOAD_H
#include "tchar.h"
#include "stdlib.h"
#include "curl/curl.h"
#include "curl/easy.h"

#define SD_MAX_STR_SIZE 256

class SignalDownload
{
public:
	//url		URL��ַ 
	//filename	�ļ�·��
	//timeout	�趨���س�ʱʱ��
	//start		��ʼ�����ֽ�
	//���		���سɹ���ʧ��
	//ִ������
	bool HTTPDownload(char *url,TCHAR *filename,long timeout,long startsize);
	//��ǰ����ֽ�
	long completesize;
	//�ļ����ֽ�
	long totalsize;

private:
	CURL *curl;
	CURLcode res;
	FILE *outfile;


};

#endif