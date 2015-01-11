
#include "stdafx.h"
#include "YUV2RGB.h"
#include "ijl.h"
#pragma comment(lib,"ijl15l.lib")

void RGBup2down(unsigned char* pRGB24, int iWidth, int iHeight,unsigned char *RGBW)
{
	int tempw=iWidth*3;
	int halfh=iHeight/2;
	int  y;
	for(y=0; y <= halfh; y++)
	{
		memcpy(RGBW,&pRGB24[y*tempw],tempw);
		memcpy(&pRGB24[y*tempw],&pRGB24[(iHeight-1-y)*tempw],tempw);
		memcpy(&pRGB24[(iHeight-1-y)*tempw],RGBW,tempw);
	}
}

void RGBup2downOUT(unsigned char* pRGB24, int iWidth, int iHeight,unsigned char *RGBdst)
{
	int tempw=iWidth*3;
	int  y;
	for(y=0; y < iHeight; y++)
	{
		memcpy(&RGBdst[(iHeight-1-y)*tempw],&pRGB24[y*tempw],tempw);
	}
}

void RGB32to24(unsigned char *src,unsigned char *dst,long w,long h)
{
	long i,j;
	long srcws=w*4;
	long dstws=w*3;
	dst[0]=src[0];
	for(i=0;i<h;i++)
	{
		for(j=0;j<w;j++)
		{
			
			dst[i*dstws+j*3]=src[i*srcws+j*4];
			dst[i*dstws+j*3+1]=src[i*srcws+j*4+1];
			dst[i*dstws+j*3+2]=src[i*srcws+j*4+2];
			
		}
	}
}

/************************************************************************
Function EncodeToJPEGBuffer:RGBͼ������ѹ��ΪJPEG�ļ�����
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
		DWORD *lpjpgBufferSize)
{
	BOOL	bres;
	IJLERR	jerr = IJL_OK;
	DWORD	rawBufSize;
	JPEG_CORE_PROPERTIES jcprops;

	*lpjpgBufferSize=0;

	bres = TRUE;
	jerr = ijlInit(&jcprops);
	if(jerr != IJL_OK){
		printf("INIT IJL ERR -- %s\n", ijlErrorStr(jerr));
		bres = FALSE;
		return bres;
	}

	rawBufSize = dwWidth * dwHeight * 3;

	jcprops.DIBWidth = dwWidth;
	jcprops.DIBHeight = -dwHeight;//ͼ��ת
	jcprops.DIBBytes = lpRawBuffer;
	jcprops.DIBPadBytes = IJL_DIB_PAD_BYTES(jcprops.DIBWidth,3);
	jcprops.DIBChannels = 3;
	jcprops.DIBColor =IJL_BGR;
	//jcprops.DIBSubsampling = IJL_422;

	jcprops.JPGWidth = dwWidth;
	jcprops.JPGHeight = dwHeight;
	jcprops.JPGFile = NULL;
	jcprops.JPGBytes = lpJPEGBuffer;
	jcprops.JPGSizeBytes = rawBufSize;
	jcprops.JPGChannels = 3;
	jcprops.JPGColor = IJL_YCBCR;
	jcprops.JPGSubsampling = IJL_411;
	jcprops.jquality = 80;

	jerr = ijlWrite(&jcprops, IJL_JBUFF_WRITEWHOLEIMAGE);
	if(jerr != IJL_OK){
		printf("ijlWrite() failed -- %s\n", ijlErrorStr(jerr));
		bres = FALSE;
		goto ENCODE_ERROR;
	}else{
		*lpjpgBufferSize = jcprops.JPGSizeBytes;
	}
ENCODE_ERROR:
	ijlFree(&jcprops);
	return bres;
}

BOOL EncodeToJPEGBufferNo(
						BYTE *lpRawBuffer, 
						DWORD dwWidth, 
						DWORD dwHeight,  
						BYTE *lpJPEGBuffer,
						DWORD *lpjpgBufferSize)
{
	BOOL	bres;
	IJLERR	jerr = IJL_OK;
	DWORD	rawBufSize;
	JPEG_CORE_PROPERTIES jcprops;

	*lpjpgBufferSize=0;

	bres = TRUE;
	jerr = ijlInit(&jcprops);
	if(jerr != IJL_OK){
		printf("INIT IJL ERR -- %s\n", ijlErrorStr(jerr));
		bres = FALSE;
		return bres;
	}

	rawBufSize = dwWidth * dwHeight * 3;

	jcprops.DIBWidth = dwWidth;
	jcprops.DIBHeight = dwHeight;//ͼ�񲻷�ת
	jcprops.DIBBytes = lpRawBuffer;
	jcprops.DIBPadBytes = IJL_DIB_PAD_BYTES(jcprops.DIBWidth,3);
	jcprops.DIBChannels = 3;
	jcprops.DIBColor =IJL_BGR;
	//jcprops.DIBSubsampling = IJL_422;

	jcprops.JPGWidth = dwWidth;
	jcprops.JPGHeight = dwHeight;
	jcprops.JPGFile = NULL;
	jcprops.JPGBytes = lpJPEGBuffer;
	jcprops.JPGSizeBytes = rawBufSize;
	jcprops.JPGChannels = 3;
	jcprops.JPGColor = IJL_YCBCR;
	jcprops.JPGSubsampling = IJL_422;
	jcprops.jquality = 100;

	jerr = ijlWrite(&jcprops, IJL_JBUFF_WRITEWHOLEIMAGE);
	if(jerr != IJL_OK){
		printf("ijlWrite() failed -- %s\n", ijlErrorStr(jerr));
		bres = FALSE;
		goto ENCODE_ERROR;
	}else{
		*lpjpgBufferSize = jcprops.JPGSizeBytes;
	}
ENCODE_ERROR:
	ijlFree(&jcprops);
	return bres;
}
