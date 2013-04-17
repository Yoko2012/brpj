
#ifndef _SQLITE_OPERATE_
#define _SQLITE_OPERATE_

#include "sqlite3.h"
#include <list>
using namespace::std;

#pragma comment( lib, "sqlite3.lib")

struct PRODUCT_INFO_ST
{
	unsigned long int nid;
	char RunningNumber[256];	
	char tag[256];		
	char MainCategory[256];
	char SubCategory[256];
	char MetaField[256];
	char ColourDesc[256];
	char Colour[256];
	char Unit[256];
	char FactoryItem[256];
	char HmNum[256];
	char Description[2560];
	char path1[260];		//ͼƬ·��
	char path2[260];		//ͼƬ·��
	char path3[260];		//ͼƬ·��
};

struct VIDEO_INFO_ST
{
	unsigned long int nid;
	
	//��Ʒ��Ϣ
	char RunningNumber[256];	
	char tag[256];
	char HmNum[256];
	char Description[2560];		

	//��ʼʱ��
	int start_year;
	int start_mon;
	int start_day;
	int start_hour;
	int start_min;
	int start_sec;
	//����ʱ��
	int end_year;
	int end_mon;
	int end_day;
	int end_hour;
	int end_min;
	int end_sec;

	unsigned long int size;	//�ļ���С
	char path[260];	//�ļ�·��
};

class CSqliteOperate
{
public:
	sqlite3 * m_pDB;
	sqlite3_stmt* stmt;
	bool readProductSuccess;
	struct PRODUCT_INFO_ST m_productInfo;
public:
	CSqliteOperate(void);
	virtual ~CSqliteOperate(void);
	//�����ݿ�
	int OpenDB(char *file);
	//�ر����ݿ�
	void CloseDB();
	//ִ��SQL���
	void Sql_Execute(char *sql);
	//��Ʒ��Ϣ��
	void Product_CreatTable(void);
	void Product_Add(struct PRODUCT_INFO_ST pInfo);
	void Product_Modify(struct PRODUCT_INFO_ST pInfo);
	void Product_Delete(unsigned long int nid);
	bool Product_Read(char *barcode,struct PRODUCT_INFO_ST &pInfo);

	//��Ƶ��Ϣ��
	void Video_CreatTable(void);
	void Video_Add(struct PRODUCT_INFO_ST pInfo,char *starttime,char *endtime,char *path,unsigned long size);
	void Video_Delete(unsigned long int nid);
	bool Video_Read(list<struct VIDEO_INFO_ST> &videoList);
	unsigned long Video_GetCount(char *runnum,char *HmNum,char *Description,\
								 char *starttime,char *endtime,int flag,char *sql);
	bool Video_GetHistory(char *sql,int flag,int startNum,int endNum,\
							list<struct VIDEO_INFO_ST> &videoList);

};
















#endif