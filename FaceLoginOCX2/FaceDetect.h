#pragma once

#include "MyWebService.h"

#define ERR_NO_ERROR		0	//OK
#define ERR_BAD_PERSON		1	//�޴�personID
#define ERR_REG_FAIL		2	//ע��ʧ��
#define ERR_SER_REEOR		3	//����ƽ̨�쳣
#define ERR_BAD_USER		4	//�Ƿ��û�
#define ERR_NONEED_MATCH	5	//����Ҫ����������֤�ı�־
#define ERR_WRONG_VERSION	6	//OCX�汾��������汾��һ��


class CFaceDetect
{
public:
	CFaceDetect(void);
	~CFaceDetect(void);

	CMyWebService m_webService;
	double m_macthThreshold;		//������ֵ
	int Facedb;						//ʶ�����ע���
	long PersonID;					//��ע����Ա��facecloud����Ա��ID
	CString ID_Card;				//���ȶ���Ա��facecloud����Ա���е�ID_Card
	CString HostInfo;				//facecloud�ķ�������ַ��Ϣ
	CString Token;					//��֤����
	int matchTimes;					//ƽ̨���õıȶԴ���
	int matchCount;					//��ǰ�ȶԴ���
public:
	//��ȡfacecloud������״̬
	bool GetFaceCloudState(void);
	//��ƽ̨У�鵱ǰע����Ա������ȡfacecloud��Ϣ
	//У���ע����Ա��Ϣ
	int CheckRegInfo(CString strFaceServer,int sysID,CString user,CString password);
	//����ע�᷵����Ϣ
	void ReadEnrollInfo(CString strHtml);
	//����ע����־��ƽ̨
	void SendEnrollLog(CString strFaceServer,CString strResult);
	//����ʶ����־��ƽ̨
	void SendMatchLog(CString strFaceServer,CString strResult);
	//У�鵱ǰ�����Ƿ�Ϸ�
	int CheckResultFlag(CString strHtml);
	//�жϵ�ǰ��Ա�Ƿ���Ҫ������֤
	bool CheckEnableFlag(CString strHtml);
	//�жϵ�ǰ��Ա�Ƿ���Ҫ������֤
	void GetToken(CString strHtml);
	//У�鵱ǰʶ����Ա��Ϣ
	int CheckMatchInfo(CString strFaceServer,int sysID,CString user,CString password);
	//����ʶ�𷵻���Ϣ
	void ReadMatchInfo(CString strHtml);


	//RGBתBASE64
	CString RGBtoBase64(unsigned char *image,unsigned long int size,unsigned long int w,unsigned long int h);
	//�ύ�������
	void FaceDetect(CString strRequest,int *faceCount,CRect *Face_Rect_List,CString *Image_List);
	//����ʶ��
	void FaceMacth(CString strRequest,CString *strResult,int *matchFlag);
	//����ע��
	int FaceEnroll(unsigned char *image,unsigned long int size,CString *FaceID);
	//CString FaceEnroll(CString strRequest,CString personID);
	//���������
	int GetFaceID(CString strHtml,CString *FaceID);
	CString GetMacthFace(CString strHtml);
	double GetMacthScore(CString strHtml);
	int GetFaceCount(CString strHtml);															//��ȡ��������
	void ParseFaceRect(int faceCount,CString strHtml,CRect *Face_List,CString *Image_List);		//��ȡ������
	//������ͼ
	void Clip(int faceCount,CRect *faceRect,int imageWidth,int imageHeight,CRect *ClipRect);
	void ClipFaceImage(unsigned char *image,int w,int h,unsigned char *clipImage,unsigned long int *size,CRect ClipRect);
};
