#ifndef _HYZJ_CAR_DETECT_H_
#define _HYZJ_CAR_DETECT_H_

#define VIDEO_WIDTH     1920
#define VIDEO_HEIGHT    1080
//WAV����
#include "mmsystem.h"
#pragma comment(lib,"winmm.lib") 


#define HY_MAX_CAR_LIST_NUM 100

//����
#include "HYZJcarSDK\\LPKernelEx.h"

#if OPEN_HYZJ_CARDETECT_CODE
//����
#pragma comment(lib, "HYZJcarSDK\\LPKernelEx.lib")

#endif



//һ��ͼ�������ٸ�����
#define HYZJ_CAR_STRUCT_MAX 32
//ÿ�����������ٸ��ַ�
#define HYZJ_CAR_STR_MAX 32
//����ʡ��
#define HYZJ_CAR_MASK_MAX 31
	////////////////////////////////////////////////////////

typedef struct
{
	int x0;	// ��
	int x1;	// ��
	int y0;	// ��
	int y1;	// ��
}Recti;

//��������
struct HYZJCarSetStruct
{
	//��ͼ���ƴ���� 0=���� 1=��
	int RedRect;
	//������бУ��ʹ�ܱ�־ 0:��У����1:У��
	int Deskew;
	//JPGͼƬ���� 75
	int JPGquality;
	//��Ƶͼ���
	int Width;
	//��Ƶͼ���
	int Hight;
	//������С��� 60
	int MinWidth;
	//��������� 180
	int MaxWidth;
	//��ⷶΧ ������ 
	Recti Range;
	//��ⷶΧ ������ 
	Recti RangeRate;
	//Ĭ��ʡ���ַ�  
	//ʡ�ݺ��֣��� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� ԥ �� �� �� �� �� �� �� ³ ��
	char DefaultChar[HYZJ_CAR_STR_MAX];
	//31��ʡ ��־λ
	//�� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� ԥ �� �� �� �� �� �� �� ³ �� (ʡ��)
	//1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	unsigned char Mask[HYZJ_CAR_MASK_MAX];
	//�������Ŷ� 75
	int Reliability;
	//������ɫʶ���־��0:��ʶ��1:ʶ��
	int CarColor;
	//ҹ��ģʽ
	int Night;
};

	////////////////////////////////////////////////////////
class CHYZJCarDetect
{
public:
	CHYZJCarDetect();
	virtual ~CHYZJCarDetect();


	void SetRange();
	char* CarType(int i);

char* CHYZJCarDetect::CarColor(int i);
char* CHYZJCarDetect::CarDirection(int i);

	void CleanList(void);

	void Stop();
	bool Start(int format,unsigned char *image,int w,int h,int size);
	int Result();


	////////////////////////////////////////////////////////
	void LimitMessageBox(void);
	void errorprintf(char *str);
	bool ErrorPlateName(char *name);



	char* CHYZJCarDetect::CarColor2JingAo(int i);
	char* CHYZJCarDetect::CarType2JingAo(int i);

public:
	int CarHandle;
	//��������Ƿ�ɹ� 1=�ɹ��� 0Ϊʧ�� -1Ϊδ����
	int State;

	//��֡������Ϣ
	int CarTotal;
	TH_PlateResultImage CarInfo[HYZJ_CAR_STRUCT_MAX];

	TH_PlateResult PlateResultReal[HYZJ_CAR_STRUCT_MAX];



	long JpgSize;
	unsigned char *JpgSmall;
	long JpgSmallSize;


	//��������
	struct HYZJCarSetStruct CarSet;
	TH_RECT CarSetrcRange ;

	////////////////////////////////////////////////////////
	//���ݿ�
	int     m_playhandle;  //���ž��
	char	cam_name[256];	//����ͷ����
	char	l_ipaddr[64];	//IP��ַ
	unsigned long int	camid;			//����ͷNID
	
	int cam_Direction;


	bool JumpJPG;	//����ͼƬ �ⲿ���á���ֹ�ǰ������޷���ʾ
	char JumpJPGpath[260];

	//���ñ��
//	int ElcarDetectFlag;
//	int CarDetectFlag;

};


#endif