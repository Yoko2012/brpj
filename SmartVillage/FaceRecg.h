#pragma once

#include "Picture.h"
#include "YRSVMySQL.h"
//


#define RWFACE_INIT_DONE			0		//��ʼ���ɹ�
#define RWRACE_PROCESS_INIT_ERROR	1		//ͨ�ÿ��ʼ������
#define RWRACE_FEATURE_INIT_ERROR	2		//��ȡ������������
#define RWFACE_IMAGE_INIT_ERROR		3		//��ȡͼ���������	
#define RWFACE_MANAGE_INIT_ERROR	4		//����������ʼ������
#define RWFACE_DATABASE_INIT_ERROR	5		//�������ݿ��ʼ������

//��ʱץ�ı�δ�ȶԼ�¼���ݽṹ
struct  UNCMP_FACE_INFO_ST
{
	long capture_nid;		//ץ�ı�nid
	long ncamera;			//�����
	char path[260];			//�ļ�·��
	long size;				//��Ƭ��С
	int threshold;			//��С���ƶȷ�ֵ
	int maxcount;			//���ƥ����
	int dbTotal;			//���ò�������
	long db_nid[RW_MAX_FACE_DB_NUM];		//���ò��ؿ�ID
	char cameraName[64];	//����ͷ����
	char sip[32];			//����ͷIP
};

//����ͼƬ����ʱץ����Ա�Ƚ��������ݽṹ
struct TEMP_CMP_CONDITION_ST
{
	int max_match_count;
	int min_similarity;
	int sex;			//�Ա�
	long ncamera;		//����ͷ���

	int flag;
	char stime[32];		//��ʼʱ��
	char etime[32];		//����ʱ��
};

//����ͼƬ����ʱץ����Ա�ȶԽ��
struct TEMP_CMP_RESULT_ST
{
	struct FACE_CAPTURE_ST tempface;
	int similarity;
};

//����ͼƬ�벼����Ա�Ƚ��������ݽṹ
struct BLACK_CMP_CONDITION_ST
{
	int max_match_count;
	int min_similarity;

	char name[32];		//����
	int sex;			//�Ա�
	char sage[32];		//��ʼ��������
	char eage[32];		//������������
	int	cardtype;		//֤������
	char cardNO[32];	//֤����
	char phone[32];		//�绰
	int native;			//����
	char address[512];	//��ַ
	long db_id;		//����ͷ���

	int flag;
};

//����ͼƬ�벼����Ա�ȶԽ��
struct BLACK_CMP_RESULT_ST
{
	struct PERSON_BLACK_ST person;
	struct FACE_BLACK_ST face;
	int similarity;
};

#define MAX_MATCH_LIST_SIZE	32	//���ƥ�����������


class CFaceRecg
{
public:
	CFaceRecg(void);
	~CFaceRecg(void);

public:
	int faceImg_width;
	int faceImg_height;
	int faceImg_wStep;
	int faceImg_size;
	int faceFeatrue_size;

	RecoCommonHandle common_handle;
	RecoFaceMngHandle faceMngHandle;
	RecoFaceMngHandle tempMngHandle;

	bool faceFecgLock;
	bool m_bThreadWork;
	HANDLE m_pThreadRecognize;
	
	RecoImage* GetImage(HBITMAP pic);
	int SaveImage(const char *file, const RecoImage *image);
	void ReleaseImage(RecoImage *image);

	int RWFaceRecg_BlackInit(void);
	int RWFaceRecg_UnInit(void);

//	RecoFeatMatchRes real_match_list[MAX_MATCH_LIST_SIZE];//ʵʱ�ȶԽ��
//	RecoFeatMatchRes temp_match_list[MAX_MATCH_LIST_SIZE];//ͼƬ���������ȶԽ�����
	
	RecoFeatMatchRes *real_match_list;//ʵʱ�ȶԽ��
	RecoFeatMatchRes *temp_match_list;//ͼƬ���������ȶԽ�����

	int StartRecgThread(void);//���������ȶ��߳�
	int StopRecgThread(void);//ֹͣ�����ȶ��߳�

	//�������Ƚ�
	bool RWFaceMngFaceCompare(int &match_list_size,RecoFeatMatchRes *match_res_list,long dbID,int max_match_count,double min_similarity,char *path);
	//��ʱץ�Ŀ�Ƚ�
	bool RWFcaeMngTempCompare(int &match_list_size,RecoFeatMatchRes *match_res_list,long dbID,int max_match_count,double min_similarity,char *path);

	//�����ݿ��ȡ����
	bool GetUnCmpFaceFromMySQL(struct UNCMP_FACE_INFO_ST &cmpFace,struct FACE_CAPTURE_ST &tempFace);//�����ݿ��ȡδ�ȶ�������Ϣ
	void StartCompareWithBlack(struct UNCMP_FACE_INFO_ST cmpFace,struct FACE_CAPTURE_ST tempFace);//��ʱץ�Ŀ���������Ƚ�

	//����ͼƬ����ʱץ�Ŀ�Ƚ�
	bool ImageCmpWihtTempFace(char *path,struct TEMP_CMP_CONDITION_ST condition,list<struct TEMP_CMP_RESULT_ST> &faceList);
	//����ͼƬ��������Ŀ�Ƚ�
	bool ImageCmpWihtBlackFace(char *path,struct BLACK_CMP_CONDITION_ST condition,list<struct BLACK_CMP_RESULT_ST> &faceList);
};
