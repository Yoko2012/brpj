#pragma once

#define RWFACE_INIT_DONE			0		//��ʼ���ɹ�
#define RWRACE_PROCESS_INIT_ERROR	1		//ͨ�ÿ��ʼ������
#define RWRACE_FEATURE_INIT_ERROR	2		//��ȡ������������
#define RWFACE_IMAGE_INIT_ERROR		3		//��ȡͼ���������	
#define RWFACE_MANAGE_INIT_ERROR	4		//����������ʼ������
#define RWFACE_DATABASE_INIT_ERROR	5		//�������ݿ��ʼ������

#include "Picture.h"


class CFaceMng
{
public:
	CFaceMng(void);
	~CFaceMng(void);

public:
	int faceImg_width;
	int faceImg_height;
	int faceImg_wStep;
	int faceImg_size;
	int faceFeatrue_size;
	bool mySqliteLock;

	RecoCommonHandle common_handle;
	RecoFaceMngHandle faceMngHandle;

	RecoImage* GetImage(HBITMAP pic);
	//RecoImage* GetImage(const char *file);
	int SaveImage(const char *file, const RecoImage *image);
	void ReleaseImage(RecoImage *image);

	//��ʼ��
	int RWFaceMng_BlackInit(void);
	int RWFaceMng_TempInit(void);
	int RWFaceMng_UnInit(void);

	//���������
	bool RWFaceMngDbAddNew(long &dbID,char *dbName);
	bool RWFaceMngDbDeleteWithID(long dbID);

	//��Ա����
	bool RWFaceMngPersonAddNew(long &personID,RecoPersonInfo pInfo);
	bool RWFaceMngPersonDeleteWithID(long personID);
	bool RWFaceMngPersonUpdate(RecoPersonInfo pInfo);
	bool RWFaceMngPersonRead(long personID,RecoPersonInfo &pInfo);

	//��������
	bool RWFaceMngFaceAddNew(long &faceID,long personID,HBITMAP pic);
	bool RWFaceMngFaceDeleteWithID(long faceID);
	bool RWFaceMngGetFaceImage(long faceID,long &size,char *path);

	//�����ʱ��Ա������
	bool RWFaceMngRegistTempPerson(long dbID,int age,char *sex,int width,int height,int step,
									unsigned char *image,long size,long &personID,long &faceID);
};
