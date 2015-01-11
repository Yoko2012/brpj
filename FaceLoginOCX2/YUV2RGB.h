
#ifndef _YUV2RGBIPL_H_
#define _YUV2RGBIPL_H_


void RGBup2down(unsigned char* pRGB24, int iWidth, int iHeight,unsigned char *RGBW);
void RGBup2downOUT(unsigned char* pRGB24, int iWidth, int iHeight,unsigned char *RGBdst);

void RGB32to24(unsigned char *src,unsigned char *dst,long w,long h);


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

BOOL EncodeToJPEGBufferNo(
						  BYTE *lpRawBuffer, 
						  DWORD dwWidth, 
						  DWORD dwHeight,  
						  BYTE *lpJPEGBuffer,
						  DWORD *lpjpgBufferSize);
#endif