#ifndef _CAR_DETECT_H_
#define _CAR_DETECT_H_

#define VIDEO_WIDTH     1920
#define VIDEO_HEIGHT    1080
//WAV����
#include "mmsystem.h"
#pragma comment(lib,"winmm.lib") 


#if ALLTAB_DETECT_CAR_MODE
//����
#include "carSDK\\portab.h"
#include "carSDK\\lc_plate_analysis.h"

#else
//�綯��
#include "elecarSDK\\portab.h"
#include "elecarSDK\\lc_plate_analysis.h"

#endif
#if OPEN_CARDETECT_CODE

#if ALLTAB_DETECT_CAR_MODE
//����
#pragma comment(lib, "carSDK\\plate_dll.lib")

#else
//�綯��
#pragma comment(lib, "elecarSDK\\plate_dll.lib")

#endif

#endif



//һ��ͼ�������ٸ�����
#define CAR_STRUCT_MAX 8
//ÿ�����������ٸ��ַ�
#define CAR_STR_MAX 32
//����ʡ��
#define CAR_MASK_MAX 31
	////////////////////////////////////////////////////////
//������Ϣ
typedef struct  
{
	//�����ַ���
	char *Str;
	//�����ַ���Ŀ
	uint8_t CharTotal; 
	//������ɫ
	char* PlateColor; 
	//�������Ŷ�
	uint8_t Reliability;
	//�����˶����� �����˶�����(0:δ֪���� 1:���ƴ��ϵ����˶� 2:��ʾ���ƴ��µ����˶�)
	uint8_t Direction;
	//����λ�þ��ο�
	Rects CarRect;
	//��������
	char *PlateType;
	//������ɫ
	char *CarColor;
/*
	unsigned char *SmallJpg;
	int SmallJpgSize;
*/

}CarInfoStruct;
	////////////////////////////////////////////////////////

//��������
struct CarSetStruct
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
	Rects Range;
	//��ⷶΧ ������ 
	Rects RangeRate;
	//Ĭ��ʡ���ַ�  
	//ʡ�ݺ��֣��� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� ԥ �� �� �� �� �� �� �� ³ ��
	char DefaultChar[CAR_STR_MAX];
	//31��ʡ ��־λ
	//�� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� ԥ �� �� �� �� �� �� �� ³ �� (ʡ��)
	//1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	uint8_t Mask[CAR_MASK_MAX];
	//�������Ŷ� 75
	int Reliability;
	//������ɫʶ���־��0:��ʶ��1:ʶ��
	int CarColor;
};

	////////////////////////////////////////////////////////
class CCarDetect
{
public:
	CCarDetect();
	virtual ~CCarDetect();


	void SetRange();
	void SetRedRect();
	void SetDeskew();
	void SetMinMaxWidth();
	void SetMask();
	void SetDefaultChar();
	void SetReliability();
	void SetJPGquality();
	void SetCarColor();
	void SetAll();

	void CleanList(void);

	void Stop();
	void Start(int format,unsigned char *image,int w,int h,int size);
	int Result();
	char* CarColor(uint8_t i);
	char* CarType(uint8_t i);
	char* CarDirection(uint8_t i);
	//bool CarCheckCharLite(int i,char *src);
	void CarCheckChar(int i);
	////////////////////////////////////////////////////////
	void LimitMessageBox(void);
	void errorprintf(char *str);
	bool ErrorPlateName(char *name);
	void FilterPlateName(char *name);

	bool FtpUploadElecar(char *TimeStr,
						   char *IpAddr,
						   char *Plate,
						   unsigned int Reliability,	
						   char *Direction,
						   unsigned char *FileBuf,
						   unsigned long int FileSize);

	bool FtpUploadCar(char *TimeStr,
							  char *IpAddr,
							  char *Plate,
							  unsigned int Reliability,	
							  char *Direction,
							  char *PlateType,
							  char *PlateColor,
							  char *CarColor,
							  unsigned char *FileBuf,
							  unsigned long int FileSize);
public:
	Plate_handle CarHandle;
	//��������Ƿ�ɹ� 1=�ɹ��� 0Ϊʧ�� -1Ϊδ����
	int State;

	//��֡������Ϣ
	int CarTotal;
	CarInfoStruct CarInfo[CAR_STRUCT_MAX];
	//����ͼ PicFlag=1 ׼����ͼ PicFlag=0����ͼ 
	bool PicFlag;
	unsigned char *Jpg;
	int32_t JpgSize;
	unsigned char *JpgSmall;
	int32_t JpgSmallSize;
	//��������
	struct CarSetStruct CarSet;
	////////////////////////////////////////////////////////
	//���ݿ�
	int     m_playhandle;  //���ž��
	char	cam_name[256];	//����ͷ����
	char	l_ipaddr[64];	//IP��ַ
	unsigned long int	camid;			//����ͷNID



	bool JumpJPG;	//����ͼƬ �ⲿ���á���ֹ�ǰ������޷���ʾ
	char JumpJPGpath[260];

	//���ñ��
//	int ElcarDetectFlag;
//	int CarDetectFlag;

};


#endif