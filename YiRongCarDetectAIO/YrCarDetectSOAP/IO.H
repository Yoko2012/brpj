/***********************************************************************************
//ver :YiRongCarDetectAIO
//time:2013-03-29 11:39:00
***********************************************************************************/

#ifndef _IO_H_
#define _IO_H_

#include "afx.h"
#include "tchar.h"

//���γ����ַ�
#pragma warning(disable : 4786)


#include <vector>
#include <list>

#import "msado15.dll" no_namespace rename("EOF","adoEOF")       //����ADO���Ϳ�
using namespace::std;

struct  S_DETECT
{
	long id;
	char ip[32];
	long isoccupy;
	long channel;
	long isenable;

};

struct  S_CAMERA
{
	long camid;
	char name[128];
	char ip[128];
	char rtspurl[1024];
	long isplay;

};

struct  S_MISSION
{
	long missionid;
	long userid;
	char username[64];
	char time[32];
	long isplay;
};


typedef struct S_DEVICE_LIST
{
	struct S_MISSION mission;
	struct S_CAMERA camera;
	struct S_DETECT detect;

}DEVICE_LIST;


//ConnectionOracleDB ���ݿ����Ӻ��� ����ֵ ����
#define ReadFile_FAIL -1	//�����ļ���ʧ��
#define Instance_FAIL -2	//���ݿ�ADO��ʼ��ʧ��
#define ContOpen_FAIL -3	//���ݿ��޷�����-�˺�����IP�쳣
#define Connectd_DONE 1		//���ݿ����ӳɹ�	

class IO
{
public:
	TCHAR Ip[256];
	TCHAR Port[256];
	TCHAR User[256];
	TCHAR Psw[256];
	TCHAR DataBaseName[256];
	_ConnectionPtr m_pConnection;					//����oracle connection����
	_RecordsetPtr m_pRecordsetPtr;					//�������ݼ�¼��
	bool state;
	//д��������ֹͬʱд��һ�ű� 
	// ���� LOG_AddNewSystemLog ����
	// VIDEO_AddNewVideo  ����
	//  CAR_MatchResult_AddNew  ����
	// ELECAR_MatchResult_AddNew ����
	bool IOwriteLock;

	CString errormessage;
public:
	IO(void);
	~IO(void);

	void DeCode(char *src,char *dst);				//����
	bool ReadFile(char* FileName);					//�����ݿ������ļ�
	void VarSaveStr(TCHAR *dst,variant_t src);		//������ַ���
	void VarSaveStr2(TCHAR *dst,_RecordsetPtr &p,TCHAR *name);	//������ַ���
	void IO::VarSaveString2(CString &dst,_RecordsetPtr &p,TCHAR *name);
	long long VarSaveNumber2(_RecordsetPtr &p,TCHAR *name);
	double VarSaveDouble2(_RecordsetPtr &p,TCHAR *name);
	void filterstring(char *str);

	bool DisConnectionOracleDB(void);				//�Ͽ���oracle���ݿ������
	int ConnectionOracleDBTXT(char* FileName);		//�������ݿ�
	unsigned long long IO::AutoAddNid(TCHAR *TableName);
	//��������
	bool IO::Mission_ADD(unsigned long int detectid,unsigned long int camid,unsigned long int userid,unsigned long int isplay);

	bool IO::DEVICE_AddNewArea(char* AreaName);

	bool IO::DEVICE_AddNewCamera(long long areaID,const char* CamName,const char* sip,int port,int channel,
		const char* user,const char* password,long venderID,const char* Rtspurl,int RTP,int DecodeTag,
		const char* longitude,const char* latitude,	
		const char* crossIndex,long crossID,
		long userID,long userLV,
		long long *out_camid);

	//��������ͷ�Ƿ����
	bool IO::DEVICE_IfCamera(unsigned long int camid);
	//����ʶ��������Ƿ����
	bool IO::DEVICE_IfDetectServer(unsigned long int detectid);

	//ɾ������ͷ
	bool IO::DEVICE_DeleteCamera(unsigned long int camid);
	//��ͼ��ѯ
	bool IO::DEVICE_ReadList(list<DEVICE_LIST> &DeviceList);


};
#endif