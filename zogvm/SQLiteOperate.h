
#ifndef _SQLITE_OPERATE_
#define _SQLITE_OPERATE_

#include "sqlite3.h"
#include <list>
using namespace::std;

#pragma comment( lib, "sqlite3.lib")



enum MAINTYPE_EM
{
	MAINTYPE_OTHER=0,
	MAINTYPE_VIDEO=1,
	MAINTYPE_MUSIC=2,
	MAINTYPE_SUB=3,
};

enum ZIDIAN_EM
{
	ZIDIAN_YAZHI=0,
	ZIDIAN_HUAZHI=1,
	ZIDIAN_FENBIANLV=2,
	ZIDIAN_3D=3,
	ZIDIAN_YEAR=4,
	ZIDIAN_YUYAN=5,

};

enum DEALSTEP_EM
{
	DEALSTEP_START=0,
	DEALSTEP_FIND_END=1,
	DEALSTEP_ALL_END=2,
};

#pragma pack(1)

struct ZIDIAN_ST
{
	long long  zidian_nid;
	int mainzidian; //�������ͱ��
	char  zidian[16]; //����Ӣ��
	char  lowzidian[16]; //����Ӣ��Сд
};

struct FILETYPE_ST
{
	long long  type_nid;
	int maintype; //�������ͱ��
	char type[16]; //���ͺ�׺Ӣ��
	int enable; //�Ƿ�����
};

//Ӳ�����к� ����
struct HDD_ST
{
	long long  hdd_nid; 
	char serno[32];//Ӳ�����к�  
	char area[32];//���� 
	char mark[128]; //��ǩ
	int insertflag; //�Ƿ����
	int enable;	//�Ƿ�ɨ��
	long long TotalBytes; //�ܿռ�
	long long FreeBytes; //ʣ��ռ�
	int dealstep;	//�������ж��߳��Ƿ����� �������ݿ�
};


struct FILE_ST
{
	long long  file_nid;
	char name[256];	//���ļ���
	char path[256];//����������·��
	long long hdd_nid;  //Ӳ��ID

	int maintype; //�������ͱ��
	char type[16]; //�ļ�����
	int resolutionW; //�ֱ��ʿ��
	int resolutionH;

	long long filesize; //�ļ�����
	long filetime;		//�ļ�ʱ��

	char md5[64];
	//�ļ��޸�ʱ��
	long long CreationTime;
	long long LastWriteTime;

	//�������Ļ ��ʾ���Ĺ�����ƵNID
	long long video_nid;

	char zidian_3d[16]; //3D�ֵ�
	char zidian_fenbianlv[16]; //�ֱ����ֵ�
	char zidian_yazhi[16]; //ѹ����
	char zidian_huazhi[16]; //����
	char zidian_year[16]; //���

	//��Ϊ1ʱ ���� �Ƿ���ڵļ�Ⲣ��־λ��Ϊ0
	//��Ϊ0ʱ ������ �Ƿ���ڵļ��
	int newflag;	
	long long double_nid; //�ظ�ID

	char Ed2kUrl[512]; //��¿��ַ
};

struct FILE_VIEW_ST
{
	struct HDD_ST hdd_data;
	struct FILE_ST file_data;
};

//����
struct DOUBLE_FILE_ST
{
	long long  double_nid;
	long long  file_nid;
};

//Ϊ�˼��ٲ����ٶȺ�����
struct FILE_VIEW_LITE_ST
{
	char hdd_area[32];//���� 
	long long  file_nid;
	char file_name[256];	//���ļ���
	char file_path[256];//����������·��
	int file_maintype; //�������ͱ��
	long long filesize; //�ļ�����
	char file_md5[64];
	long long double_nid; //�ظ�ID
};


struct YYETS_ST
{
	long long  yyets_nid;
	char name[256];	//���ļ���
	char filesize[32]; //�ļ�����
	char magnet[512];
	char ed2k[512];
	char wanpan[128];
};


struct EXTERN_ED2K_ST
{
	long long  nid;
	char name[256];	//���ļ���
	long long filesize; //�ļ�����
	char ed2k[512];
};

enum POINT_EM
{
	POINT_PATH=0,
	POINT_NAME=1,
	POINT_CREATTIME=2,
	POINT_LASTTIME=3,
	POINT_FILESIZE=4,
	POINT_RESOLUTION=5,
};

//�����õı��
struct UPDOWN_ST
{
	bool issearch;
	bool type_video;
	bool type_audio;
	bool type_sub;
	bool type_other;

	POINT_EM point; 

	bool path;
	bool name;
	bool creattime;
	bool lasttime;
	bool filesize;
	bool resolution;
};

class CSqliteOperate
{
public:
	sqlite3 * m_pDB;
	sqlite3_stmt* stmt;
public:
	CSqliteOperate(void);
	virtual ~CSqliteOperate(void);

	bool IOwriteLock;


	//�����ݿ�
	int OpenDB(char *file);
	int ChangeKey(char *key,int num);
	//�ر����ݿ�
	void CloseDB();
	//ִ��SQL���
	void Sql_UpdateExecute(char *sql);
	void Sql_FindExecute(char *sql);
	int Sql_CallBackExecute(char *sql,int (*callback)(void*,int,char**,char**), void *list);
	void Begin(void);
	void Commit(void);

	void filterstring(char *str,char *dst);
	void filterstringForLike(char *str,char *dst);
	void filterstringNameForLike(char *str,char *dst);

	void ZiDian_CreateTable(void);
	void ZiDian_Add(int mainzidian,char *zidian);
	bool ZiDian_Read(list<struct ZIDIAN_ST> &List);

	void Double_CreateTable(void);
	void Double_Add(long long file_nid);
	bool Double_Read(list<struct DOUBLE_FILE_ST> &List);
	void Double_ReadOne(long long *double_nid,long long file_nid);
	void Double_DeleteAll(void);
	void File_CleanDouble2Zero(void);

	void Type_CreateTable(void);
	void Type_Add(int maintype,char *type);
	void Type_ModifyEnable(char* nid,int enable);
	bool Type_Read(list<struct FILETYPE_ST> &List);
	void Type_Add_Lock(int maintype,char *type);
	void Type_DeleteAll(void);
	void Type_AddAll(void);

	void Hdd_CreateTable(void);
	void Hdd_Add(char *serno,char *area,char *mark,long long TotalBytes,long long FreeBytes);
	void Hdd_ModifyEnable(char* nid,int enable);
	bool Hdd_Read(list<struct HDD_ST> &List);
	void Hdd_SetNonsert(void);
	void Hdd_DeleteforHdd(long long hdd_nid);

	void File_CreateTable(void);
	void File_CreateView(void);
	bool File_CheckDoublePos(char *name,char *path,long long hdd_nid);

	void File_Add(struct FILE_ST data);
	void File_Delete(long long file_nid);
	void File_DeleteforHdd(long long hdd_nid);

	void File_SetNoFlagOne(long long hdd_nid);
	void File_SetNoFlagAll(void);

	bool File_ReadHddAllwithVideoAudio(list<struct FILE_VIEW_LITE_ST> &List,long long hdd_nid);
	bool File_ReadHddAllandOld(list<struct FILE_VIEW_LITE_ST> &List,long long hdd_nid);
	bool File_CheckDouble(int maintype,long long size,char *name,char *md5,
		list<struct FILE_VIEW_LITE_ST> &List);

	void File_SetDouble(long long double_nid,char *file_nid_str);


	long long File_NumberForHDD(long long hdd_nid);
	bool File_ReadHddPage(list<struct FILE_VIEW_ST> &List,long long hdd_nid,bool up,long long start,int num);

	void File_ResetDouble2Zero(void);

	long long File_DoubleNumber(void);
	bool File_ReadDouble(list<struct FILE_VIEW_ST> &List,long long start,int num);

	long long File_TrashNumber(void);
	bool File_ReadTrash(list<struct FILE_VIEW_ST> &List,long long start,int num);


	void File_filterUpDown(char *SQLstr,struct UPDOWN_ST updown);

	long long File_NumberForSearch(char *SQLstr,char *str);
	bool File_ReadForSearch(char *SQLstr,char *str,list<struct FILE_VIEW_ST> &List,long long start,int num);

	long long File_Number(char *SQLstr);
	bool File_Read(char *SQLstr,list<struct FILE_VIEW_ST> &List,long long start,int num);

	//YYETS
	long long YYETS_Number(void);
	long long YYETS_NumberForSearch(char *str);
	bool YYETS_Read(list<struct YYETS_ST> &List,long long start,int num);
	bool YYETS_ReadForSearch(char *str,list<struct YYETS_ST> &List,long long start,int num);

	void ExternED2K_CreateTable(void);
	void ExternED2K_Add(struct EXTERN_ED2K_ST data);
	long long CSqliteOperate::ExternED2K_Number(void);
	long long CSqliteOperate::ExternED2K_NumberForSearch(char *str);
	bool ExternED2K_ReadForSearch(char *str,list<struct EXTERN_ED2K_ST> &List,long long start,int num);
	bool ExternED2K_Read(list<struct EXTERN_ED2K_ST> &List,long long start,int num);

	void File_CleanIDX(long long hdd_nid);
;

};
















#endif