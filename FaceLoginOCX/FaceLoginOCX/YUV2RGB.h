
#ifndef _YUV2RGBIPL_H_
#define _YUV2RGBIPL_H_

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

#endif