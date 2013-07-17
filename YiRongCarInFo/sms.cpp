#include "stdafx.h"
#include "sms.h"

void SMS::smsStart(void)
{
	//  ���庯��ָ��pointer function name(pfn) 
	pfnSP_Startup = NULL; 
	pfnSP_Cleanup = NULL; 
	pfnSP_Login = NULL;
	pfnSP_Logout = NULL;

	pfnSubmitShortMessage = NULL;
	pfnSubmitShortMessageMulti = NULL;
	//  ���嶯̬���ӿ��ں˶����� 
	hSMDLL = NULL; 

	FILE *fp;
	fp=fopen("smsclassload.log.txt","w");

	//  ��ʾ���ض�̬�⵽�����̿ռ��� 
	hSMDLL = LoadLibrary("SMEntry.dll"); 
	//  ����ʧ�ܴ��� 
	if(NULL == hSMDLL) 
		fprintf(fp,"%s \n","���ض�̬���ӿ�ʧ��!! ");

	//���ݶ�̬������������ƻ�ú�����ַ������ֵ 
	pfnSP_Startup = (SP_Startup)GetProcAddress(hSMDLL, "SP_Startup");
	//������ַ��ȡʧ�ܴ��� 
	if(NULL == pfnSP_Startup)
		fprintf(fp,"%s \n","��ȡ����SP_Startup��ַʧ��!! ");

	//���ݶ�̬������������ƻ�ú�����ַ������ֵ 
	pfnSP_Cleanup = (SP_Cleanup)GetProcAddress(hSMDLL,"SP_Cleanup"); 
	//  ������ַ��ȡʧ�ܴ��� 
	if(NULL == pfnSP_Cleanup) 
		fprintf(fp,"%s \n","��ȡ����SP_Cleanup��ַʧ��!! "); 

	//���ݶ�̬������������ƻ�ú�����ַ������ֵ
	pfnSP_Login = (SP_Login)GetProcAddress(hSMDLL, "SP_Login");
	// ������ַ��ȡʧ�ܴ���
	if(NULL == pfnSP_Login)
		fprintf(fp,"%s \n","��ȡ����SP_Login��ַʧ��!! ");

	//���ݶ�̬������������ƻ�ú�����ַ������ֵ
	pfnSP_Logout = (SP_Logout)GetProcAddress(hSMDLL, "SP_Logout");
	// ������ַ��ȡʧ�ܴ���
	if(NULL == pfnSP_Logout)
		fprintf(fp,"%s \n","��ȡ����SP_Logout��ַʧ��!! ");

	//hSMDLL Ϊ��̬���ӿ��ں˶�����
	pfnSubmitShortMessage=(SubmitShortMessage)GetProcAddress(hSMDLL, "SubmitShortMessage") ;  
	if(NULL == pfnSubmitShortMessage)
		fprintf(fp,"��ȡ����SubmitShortMessage��ַʧ��!! \n");

	 //hSMDLL Ϊ��̬���ӿ��ں˶�����
	pfnSubmitShortMessageMulti=(SubmitShortMessageMulti)GetProcAddress(hSMDLL, "SubmitShortMessageMulti");
	if(NULL == pfnSubmitShortMessageMulti)
		fprintf(fp,"��ȡ����SubmitShortMessageMulti��ַʧ��!! \n");
	

	fprintf(fp,"ok");

	fclose(fp);
}

void SMS::smsEnd(void)
{
	//  �������ʱ�ͷż��صĶ�̬���ӿ� 
	if ( NULL != hSMDLL ) 
		FreeLibrary(hSMDLL); 
}
///////////////////////////////////////////////////////////////////////

int SMS::smsInit(void)
{
	//  ʹ�ú���ָ����ö�̬���еĴ��� 
	return  pfnSP_Startup("10.131.1.24,1393","CustomSMS","SqlMsde@InfoxEie2000"); 
}

void SMS::smsUninit(void)
{
	//  ʹ�ú���ָ����ö�̬���еĴ��� 
	pfnSP_Cleanup(); 
}

int SMS::smsLogin(void)
{
	// ʹ�ú���ָ����ö�̬���еĴ���
	return pfnSP_Login("123","123456");
}

int SMS::smsLogout(void)
{
	// ʹ�ú���ָ����ö�̬���еĴ���
	return pfnSP_Logout ();
}
//�绰����  ��Ϣ ��Ϣ��С
int SMS::smsSendOne(char *dstPhoneNumber,char *msg,unsigned long msglen)
{
	if(0 == msglen)
		return -2;
	return pfnSubmitShortMessage("2013-01-23 10:20:20", "10657301110", dstPhoneNumber, msg,msglen,1,"EIE","01","1");
}

//�绰����·��  ��Ϣ ��Ϣ��С
int SMS::smsSendMulti(char *dstPhonePath,char *msg,unsigned long msglen)
{
	if(0 == msglen)
		return -2;
	return pfnSubmitShortMessageMulti("2013-01-23 10:20:20","10657301110",dstPhonePath,msg,msglen,1,"EIE","01","1");
}

//�绰����·��  ��Ϣ ��Ϣ��С
int SMS::smsSendMultiMy(char *dstPhonePath,char *msg,unsigned long msglen)
{
	if(0 == msglen)
		return -2;

	char temp[32];

	FILE *fp=fopen(dstPhonePath,"r");
	if(fp)
	{
		do
		{
			memset(temp,0,32);
			fscanf(fp,"%s",temp);
			//��ֵ
			if(strlen(temp))
				pfnSubmitShortMessage("2013-01-23 10:20:20", "10657301110", temp, msg,msglen,1,"EIE","01","1");

		}while(!feof(fp));
		fclose(fp);
		return 0;
	}
	else
		return -1;
}
