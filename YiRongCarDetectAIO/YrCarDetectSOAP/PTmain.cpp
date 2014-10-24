// webserver.cpp : Defines the entry point for the console application.
//
//����ǰ
#include "afx.h"

#include "YrElecarDetect.nsmap"
//#pragma comment(lib,"wsock32.lib")

#include "pthreadinclude/pthread.h"
#pragma comment(lib, "pthreadlib/pthreadVC2.lib")




////////////////////////
#include "init.h"
#include "io.h"
#include "mylog.h"
IO OracleIO;
struct GLOBAL_CONFIG_S GlobalConfig;

////////////////////////////////

//����ȫ�ֱ����Ķ���

#define BACKLOG (100)
//�߳�����
#define MAX_THR (10)
//�������
#define MAX_QUEUE (1000)


pthread_mutex_t queue_cs;//������
pthread_cond_t queue_cv;//��������

SOAP_SOCKET queue[MAX_QUEUE];//�������
int head =0, tail =0;//����ͷ����β��ʼ��

void * process_queue(void *);//�߳���ں���
int enqueue(SOAP_SOCKET);//����к���
SOAP_SOCKET dequeue(void);//�����к���


//�߳���ں���
void * process_queue(void * soap)
{
	struct soap * tsoap = (struct soap *)soap;
	for(;;)
	{
		tsoap->socket = dequeue();

		if (!soap_valid_socket(tsoap->socket))
		{
			break;
		}

		soap_serve(tsoap);
		soap_destroy(tsoap);
		soap_end(tsoap);
	}
	return NULL;
}

//����в���
int enqueue(SOAP_SOCKET sock)
{
	int status = SOAP_OK;
	int next;

	pthread_mutex_lock(&queue_cs);
	next = tail +1;

	if (next >= MAX_QUEUE)
	{
		next = 0;
	}

	if (next == head)
	{
		status = SOAP_EOM;
	}
	else
	{
		queue[tail] =sock;
		tail = next;
	}

	pthread_cond_signal(&queue_cv);
	pthread_mutex_unlock(&queue_cs);

	return status;
}


//�����в���
SOAP_SOCKET dequeue()
{

	SOAP_SOCKET sock;
	pthread_mutex_lock(&queue_cs);

	while (head == tail )
	{
		pthread_cond_wait(&queue_cv,&queue_cs);
	}

	sock = queue[head++];

	if (head >= MAX_QUEUE)
	{
		head =0;
	}

	pthread_mutex_unlock(&queue_cs);

	return sock;
}

//�Ӵ˶� ��Ȼ����ʾadd.wsdl
int http_get(struct soap *soap)
{
	FILE*fd = NULL;
	fd = fopen("YrElecarDetect.wsdl", "rb"); //open WSDL file to copy
	if (!fd)
	{
		return 404; //return HTTP not found error
	}
	soap->http_content = "text/xml"; //HTTP header with text /xml content
	soap_response(soap,SOAP_FILE);
	for(;;)
	{
		size_t r = fread(soap->tmpbuf,1, sizeof(soap->tmpbuf), fd);
		if (!r)
		{
			break;
		}
		if (soap_send_raw(soap, soap->tmpbuf, r))
		{
			break; //cannot send, but little we can do about that
		}
	}
	fclose(fd);
	soap_end_send(soap);
	return SOAP_OK;
} 

//��ǿ�˴���
void fnExit(void)
{
	OracleIO.DisConnectionOracleDB();
	Log_fileout(LOG_ERROR,"�����˳�\n");
}

//������
int main(int argc,char ** argv)
{

	//========

	//��ʼ������·��
	TCHAR CurrentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, CurrentDir);

	if(false== ReadConfigFile("yredSOAPconfig.db",GlobalConfig))
	{
		Log_fileout(LOG_ERROR,"�����ļ�������\n");
		return 0;
	}
	//�������ݿ�Ҫ��
	//AfxOleInit();
	CoInitialize(NULL);

	if(OracleIO.ConnectionOracleDBTXT("YRDataBaseConfig.db")<0)
		return 0;

	//��ʼ��Ŀ¼
	initLogDir(CurrentDir);
	//ǿ����Ϣ
	atexit(fnExit);

	//========

	struct soap ServerSoap;

	//��ʼ������ʱ����
	soap_init(&ServerSoap);

	//�Ӵ��С���Ȼ����ʾWSDL
	ServerSoap.fget = http_get;
	//����UTF8���� ������������
	soap_set_mode(&ServerSoap, SOAP_C_UTFSTRING);

	//���û�в���������CGI������
	/*
	if (argc <2)
	{
	fprintf(stderr, "û�д��˿�\n");
	//CGI ���������󣬵��߳�
	soap_serve(&ServerSoap);

	//������л������ʵ��
	soap_destroy(&ServerSoap);

	//������л�������
	soap_end(&ServerSoap);
	}
	else
	*/
	{

		struct soap * soap_thr[MAX_THR];

		pthread_t tid[MAX_THR];

		int i;

		//int port = atoi(argv[1]);
		int port =GlobalConfig.Port;

		Log_fileout(LOG_ERROR,"�˿�:%d\n",port);

		SOAP_SOCKET m,s;

		//��������������ʼ��
		pthread_mutex_init(&queue_cs,NULL);
		pthread_cond_init(&queue_cv,NULL);

		//�󶨷���˿�
		m = soap_bind(&ServerSoap,NULL,port,BACKLOG);

		//ѭ��ֱ�������׽��ֺϷ�
		while (!soap_valid_socket(m))
		{
			Log_fileout(LOG_ERROR,"Bind port error!\n");
			m = soap_bind(&ServerSoap,NULL,port,BACKLOG);
		}

		Log_fileout(LOG_ERROR,"socket connection successful %d \n",m);


		//���ɷ����߳�
		for(i = 0; i <MAX_THR; i++)
		{
			soap_thr[i] = soap_copy(&ServerSoap);

			Log_fileout(LOG_ERROR,"Starting thread %d \n",i);

			pthread_create(&tid[i],NULL,(void*(*)(void*))process_queue,(void*)soap_thr[i]);
		}

		for(;;)
		{
			//���ܿͻ��˵�����
			s = soap_accept(&ServerSoap);

			if (!soap_valid_socket(s))
			{
				if (ServerSoap.errnum)
				{
					soap_print_fault(&ServerSoap,stderr);
					continue;
				}
				else
				{
					Log_fileout(LOG_ERROR,"Server timed out \n");
					break;
				}
			}

			//�ͻ��˵�IP��ַ

			Log_fileout(LOG_ERROR,"Accepted connection from IP= %d.%d.%d.%d socket = %d \n",

				((ServerSoap.ip)>>24)&&0xFF,((ServerSoap.ip)>>16)&0xFF,((ServerSoap.ip)>>8)&0xFF,(ServerSoap.ip)&0xFF,(ServerSoap.socket));

			//������׽��ֽ�����У��������������ѭ���ȴ�
			while(enqueue(s) == SOAP_EOM)
			{
				Sleep(1000);
			}

		}

		//����������������
		for(i = 0; i < MAX_THR; i++)
		{
			while (enqueue(SOAP_INVALID_SOCKET) == SOAP_EOM)
			{
				Sleep(1000);
			}
		}

		for(i=0; i< MAX_THR; i++)
		{
			Log_fileout(LOG_ERROR,"Waiting for thread %d to terminate ..\n",i);
			pthread_join(tid[i],NULL);

			Log_fileout(LOG_ERROR,"terminated \n");

			soap_done(soap_thr[i]);
			free(soap_thr[i]);
		}

		pthread_mutex_destroy(&queue_cs);
		pthread_cond_destroy(&queue_cv);

	}

	//��������ʱ�Ļ���
	soap_done(&ServerSoap);


	Log_fileout(LOG_ERROR,"�˳�����\n");	//��������

	return 0;
}

