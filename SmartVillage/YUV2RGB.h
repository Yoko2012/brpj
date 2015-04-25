
#ifndef _YUV2RGBIPL_H_
#define _YUV2RGBIPL_H_

#include "ijl.h"
#pragma comment(lib, "ijl15l.lib")

bool YV12_to_RGB24(unsigned char* pYV12, unsigned char* pRGB24,int iWidth, int iHeight);
bool I420_to_RGB24(unsigned char* pI420, unsigned char* pRGB24,int iWidth, int iHeight);

bool YV12toRGB24UD(unsigned char* pYV12, unsigned char* pRGB24, int iWidth, int iHeight,unsigned char *RGBW);


void YUV4202RGB(unsigned char *yuv_image,unsigned char* rgb_image,int iWidth, int iHeight);
void YV122RGB(unsigned char *yuv_image,unsigned char* rgb_image,int iWidth, int iHeight);

void ZOGDramBMP(char *path,unsigned char *buffer, int w, int h);
/************************************************************************
Function CompressRGBToJPEG:RGBͼ������ѹ��ΪJPEG�ļ�����
  Input:
  VIDEO_FRAMEINFO *yuv_image        YUVͼ������
  unsigned char* rgb_image			RGBͼ������
return:
        ��   
************************************************************************/
//void YUV2RGB(VIDEO_FRAMEINFO *yuv_image,unsigned char* rgb_image);

/************************************************************************
Function CompressRGBToJPEG:RGBͼ������ѹ��ΪJPEG�ļ�����
  Input:BYTE *lpImageRGB        RGBͼ��������
  int   originalWidth     ԭʼͼ����
  int   originalHeight    ԭʼͼ��߶�
  int   jpegQuality       JPEGѹ������[1-100]
  char* jpegFileName      JPEG�ļ���������� 
  int   isNeedReversal    �Ƿ���Ҫ��ת
  int   isResizeImage     �Ƿ���Ҫ����ͼ��ĳߴ�
return:
        �ɹ�����0ֵ,�쳣������������;
Update:
  Author         Date              Ver      Remark  
  Shimingjie     2005/01/06        1.0      Create         
************************************************************************/
int CompressRGBToJPEG(unsigned char *lpImageRGB,int originalWidth,int originalHeight,
					  int jpegQuality,char* jpegFileName,int isNeedReversal,int isResizeImage);

int CompressRGBAToJPEG(unsigned char *lpImageRGB,int originalWidth,int originalHeight,
					   int jpegQuality,char* jpegFileName,int isNeedReversal,int isResizeImage);

/************************************************************************
Function EncodeToJPEGBuffer:RGBͼ������ѹ��ΪJPEGͼ������
  Input:
	  BYTE *lpRawBuffer			RGBͼ��������
	  DWORD   dwWidth			ԭʼͼ����
	  DWORD   dwWidth			ԭʼͼ��߶�
	  BYTE *lpJPEGBuffer		JPEGͼ��������
	  DWORD *lpjpgBufferSize	JPEGͼ���С

return:
        �ɹ�����0ֵ,�쳣������������;   
************************************************************************/
BOOL EncodeToJPEGBuffer(
		BYTE *lpRawBuffer, 
		DWORD dwWidth, 
		DWORD dwHeight,  
		BYTE *lpJPEGBuffer,
		DWORD *lpjpgBufferSize);


BOOL JPEGFile2BMP(char* lpszFilename,
				  unsigned char* RGBdata, int *w,int *h,int *channel,long *wstep,long *size);

BOOL JPEGData2BMP(unsigned char *Jpegdata,long JpegSize,
				   unsigned char* RGBdata, int *w,int *h,int *channel,long *wstep,long *size);

void BGRA32toRGB24(
				  unsigned char *RGB32data,
				  unsigned char *RGB24data,
				  int w,
				  int h,
				  int RGB32wstep,
				  int RGB24wstep);

#endif