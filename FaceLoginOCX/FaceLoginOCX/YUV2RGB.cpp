
#include "stdafx.h"
#include "YUV2RGB.h"
#include "ijl.h"
#pragma comment(lib,"ijl15l.lib")

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
	jcprops.DIBHeight = dwHeight;
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
