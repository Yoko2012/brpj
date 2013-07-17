#ifndef _ZOG_ORACALE_IO
#define _ZOG_ORACALE_IO
#import "msado15.dll" no_namespace rename("EOF","adoEOF")       //����ADO���Ϳ�
#include <vector>
#include <io.h>

using namespace::std;

//ConnectionOracleDB ���ݿ����Ӻ��� ����ֵ ����
#define YIRONGDB_ReadFile_FAIL -1	//�����ļ���ʧ��
#define YIRONGDB_Instance_FAIL -2	//���ݿ�ADO��ʼ��ʧ��
#define YIRONGDB_ContOpen_FAIL -3	//���ݿ��޷�����-�˺�����IP�쳣
#define YIRONGDB_Connectd_DONE 1	//���ݿ����ӳɹ�	

#define ORACLE_CONFIG_TXT _T("oracle_config.txt")

class IOoracle
{
public:
	IOoracle(void);
	~IOoracle(void);

	_ConnectionPtr m_pConnection;             //����oracle connection����

	int ConnectionOracleDB(TCHAR*  FileName);	   //����oracle���ݿ�

	bool DisConnectionOracleDB(void);		   //�Ͽ���oracle���ݿ������

	void ReadInfoFromOracleDB_TORG(CString str, vector<CString> &id,vector<CString> &name);

	void ReadInfoFromOracleDB_TBCAMERAINFO(CString str,vector<int> &id, vector<CString> &live,vector<CString> &ip,
			vector<CString> &user, vector<CString> &pwd,vector<CString> &channel,vector<CString> &port);

	BOOL GetSysdateFromOracleDB(char *str,
								  int *year,int *mon,int *day,
									  int *hour,int *min,int *sec);
	BOOL GetSysdateFromOracleDB_DATE( int *year,int *mon,int *day,
									  int *hour,int *min,int *sec);

	void WriteInfoFromOracleDB_TBVIDEOINFO(long int camid,	\
		const char *path,const char *filename,CTime stime,long int size,char *type);

	void WriteInfoFromOracleDB_NETVIDEOINFO(long int camid,	\
												 const char *path,const char *filename,	\
												 CTime stime,CTime etime,long int size,char *type);

	long int GetNID_VIDEO();
	void VIDEO_PRO(long int nid);

};

#endif