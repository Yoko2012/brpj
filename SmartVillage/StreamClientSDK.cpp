
#include "stdafx.h"

#if OPEN_STREAM_CLIENT_SDK
#include "StreamClientSDK.h"

//////////////////////////////////
#include "CarDetect.h"
//////////////////////////////////
#include "FaceDetect.h"
//////////////////////////////////
#include "SmartVillage.h"
#include "SmartVillageDlg.h"
extern CSmartVillageDlg *DlgMain;
#include "DLGSetSystem.h"
extern CDLGSetSystem DlgSetSystem;

#include "YRSVMySQL.h"
extern CYRSVMySQL MySqlIO;


void CALLBACK StreamClientHikanCBFun(DISPLAY_INFO *pstDisplayInfo)
{
	int screenNo=pstDisplayInfo->nUser;
	if(screenNo<0)
		return;

	if( ! DlgMain->DlgTabVideo.DlgScreen.m_video.m_StreamClient.CapturePath[screenNo].IsEmpty())
	{
		DB33_PlayM4_ConvertToJpegFile(pstDisplayInfo->pBuf, pstDisplayInfo->nBufLen, pstDisplayInfo->nWidth, pstDisplayInfo->nHeight, pstDisplayInfo->nType, 
			DlgMain->DlgTabVideo.DlgScreen.m_video.m_StreamClient.CapturePath[screenNo].GetBuffer(0));

		DlgMain->DlgTabVideo.DlgScreen.m_video.m_StreamClient.CapturePath[screenNo]="";
	}

	//������ʶ��
	//MySqlIO.LOG_AddNewSystemLog("admin","c");
	//����ʶ��
#if OPEN_CARDETECT_CODE 	

	//����ʶ��
	if(DlgMain->DlgTabVideo.DlgScreen.m_videoInfo[screenNo].enableCarDetect)
	{
		
		//������ֵ
		DlgMain->DlgTabVideo.DlgScreen.CarDetect[screenNo].m_playhandle=screenNo;



		DlgMain->DlgTabVideo.DlgScreen.CarDetect[screenNo].camid=
			DlgMain->DlgTabVideo.DlgScreen.m_videoInfo[screenNo].camID;

		strcpy(DlgMain->DlgTabVideo.DlgScreen.CarDetect[screenNo].cam_name,
			DlgMain->DlgTabVideo.DlgScreen.m_videoInfo[screenNo].name.GetBuffer(0));

		if(DlgMain->DlgTabVideo.DlgScreen.m_videoInfo[screenNo].ip.GetLength() >1)
		{
			strcpy(DlgMain->DlgTabVideo.DlgScreen.CarDetect[screenNo].l_ipaddr,
				DlgMain->DlgTabVideo.DlgScreen.m_videoInfo[screenNo].ip.GetBuffer(0));
		}
		else
			strcpy(DlgMain->DlgTabVideo.DlgScreen.CarDetect[screenNo].l_ipaddr,"0.0.0.0");

		//��ɫLC_VIDEO_FORMAT_YV12 ����ɫLC_VIDEO_FORMAT_I420 �෴
		DlgMain->DlgTabVideo.DlgScreen.CarDetect[screenNo].Start(LC_VIDEO_FORMAT_YV12,\
			(unsigned char *)pstDisplayInfo->pBuf,pstDisplayInfo->nWidth,pstDisplayInfo->nHeight,pstDisplayInfo->nBufLen);

		DlgMain->DlgTabVideo.DlgScreen.CarDetect[screenNo].Result();
	}

#endif


#if OPEN_FACEDETECT_CODE
	//����ʶ��
	if(DlgMain->DlgTabVideo.DlgScreen.m_videoInfo[screenNo].enableFaceDetect)
	{
		DlgMain->DlgTabVideo.DlgScreen.FaceAdd[screenNo]++;
		if(0==DlgMain->DlgTabVideo.DlgScreen.FaceAdd[screenNo]%FACE_JUMP_NUM)
		
		{
			DlgMain->DlgTabVideo.DlgScreen.FaceAdd[screenNo]=0;
	

		long long ftime;
		CTime nowtime=CTime::GetTickCount();
		ftime=nowtime.GetTime();
		//	YUV2RGB((unsigned char *)pBuf, 	DlgMain->DlgTabVideo.DlgScreen.RGBdata[screenNo], 	nWidth,nHeight);

		//������ֵ
		DlgMain->DlgTabVideo.DlgScreen.FaceDetect[screenNo].m_playhandle=screenNo;

		DlgMain->DlgTabVideo.DlgScreen.FaceDetect[screenNo].camid=
			DlgMain->DlgTabVideo.DlgScreen.m_videoInfo[screenNo].camID;

		strcpy(DlgMain->DlgTabVideo.DlgScreen.FaceDetect[screenNo].cam_name,
			DlgMain->DlgTabVideo.DlgScreen.m_videoInfo[screenNo].name.GetBuffer(0));

		strcpy(DlgMain->DlgTabVideo.DlgScreen.FaceDetect[screenNo].l_ipaddr,
			DlgMain->DlgTabVideo.DlgScreen.m_videoInfo[screenNo].ip.GetBuffer(0));

		DlgMain->DlgTabVideo.DlgScreen.FaceDetect[screenNo].Start(VIDEO_FORMAT_YV12,
			(unsigned char *)pstDisplayInfo->pBuf,pstDisplayInfo->nWidth,pstDisplayInfo->nHeight,
			pstDisplayInfo->nWidth*3,pstDisplayInfo->nBufLen);

		//ZOGDramBMP("d:\\112212121.bmp",DlgMain->DlgTabVideo.DlgScreen.RGBdata[screenNo], nWidth,nHeight);
		}
	}

#endif
}


int  StreamClientHikanCBinitFun(int sessionhandle, void* userdata, int datatype, void* pdata,
								int ilen) 
{
	/*

	FILE *outfile = fopen("stream.txt", "a+");
	if(NULL!= outfile)
	{
	fwrite(pdata, ilen, 1, outfile);
	fclose(outfile);
	}

	*/

	CStreamClientSDK *StreamClientSDK = (CStreamClientSDK *)userdata;

	int screenNo = DlgMain->DlgTabVideo.DlgScreen.m_video.m_StreamClient.GetHandleWindID(sessionhandle);
	LONG lPort= StreamClientSDK->m_lPort[screenNo];

	CWnd* pWnd=NULL;
	char nstr[1024]="";

	switch  (datatype) 
	{ 
	case STREAM_HEAD:   // ����ͷ���� 


		if (DB33_PlayM4_GetPort(&lPort))  //��ȡ���ſ�δʹ�õ�ͨ����
		{
			DlgMain->DlgTabVideo.DlgScreen.m_video.m_StreamClient.m_lPort[screenNo] = lPort;
		}

		//m_iPort = lPort; //��һ�λص�����ϵͳͷ������ȡ�Ĳ��ſ�port�Ÿ�ֵ��ȫ��port���´λص�����ʱ��ʹ�ô�port�Ų���
		if (ilen > 0)
		{
			if (!DB33_PlayM4_SetStreamOpenMode(lPort, STREAME_REALTIME))  //����ʵʱ������ģʽ
			{
				DB33_PlayM4_FreePort(lPort);
				StreamClientSDK->m_lPort[screenNo]=-1;
				break;
			}
			if (!DB33_PlayM4_OpenStream(lPort, (PBYTE)pdata, ilen, 1920*1080*3)) //�����ӿ�
			{
				DB33_PlayM4_FreePort(lPort);
				StreamClientSDK->m_lPort[screenNo]=-1;
				break;
			}
/*
			if (!DB33_PlayM4_SetDisplayCallBack(lPort, StreamClientHikanCBFun))
			{

				DB33_PlayM4_CloseStream(lPort);
				DB33_PlayM4_FreePort(lPort);
				StreamClientSDK->m_lPort[screenNo]=-1;
				break;
			}
*/
			if (!DB33_PlayM4_SetDisplayCallBackEx(lPort, StreamClientHikanCBFun,screenNo))
			{
				DB33_PlayM4_CloseStream(lPort);
				DB33_PlayM4_FreePort(lPort);
				StreamClientSDK->m_lPort[screenNo]=-1;
				break;
			}

			if(DlgSetSystem.m_display_preview)
			{
				pWnd= DlgMain->DlgTabVideo.DlgScreen.m_screenPannel.GetPage(screenNo);
				if (!pWnd)
				{
					DB33_PlayM4_CloseStream(lPort);
					DB33_PlayM4_FreePort(lPort);
					StreamClientSDK->m_lPort[screenNo]=-1;
					return 0;
				}
				if (!DB33_PlayM4_Play(lPort, pWnd->m_hWnd)) //���ſ�ʼ
				{
					DB33_PlayM4_CloseStream(lPort);
					DB33_PlayM4_FreePort(lPort);
					StreamClientSDK->m_lPort[screenNo]=-1;
					break;
				}
			}
			else
			{
				if (!DB33_PlayM4_Play(lPort,NULL)) //���ſ�ʼ
				{
					DB33_PlayM4_CloseStream(lPort);
					DB33_PlayM4_FreePort(lPort);
					StreamClientSDK->m_lPort[screenNo]=-1;
					break;
				}
			}
		}

		break;

	case STREAM_DATA:   // �������� 

		if (ilen > 0 && lPort != -1)
		{
			if (!DB33_PlayM4_InputData(lPort, (PBYTE)pdata, ilen))
			{
				//DB33_PlayM4_CloseStream(lPort);
				//DB33_PlayM4_FreePort(lPort);
				//StreamClientSDK->m_lPort[screenNo]=-1;
				break;
			} 

		}
		break; 

	case STREAM_PLAYBACK_FINISH:    // �ط�/���������� =;
		break; 
	default: 
		break; 
	} 

	return 0;

}
int CALLBACK StreamClientSDKDataFunc(int sessionhandle, void* userdata, int datatype, void* pdata,
									 int ilen) 
{ 
	if ((sessionhandle  < 0) || (NULL == pdata) || (ilen <= 0)) 
	{ 
		return -1; 
	} 

	StreamClientHikanCBinitFun( sessionhandle, userdata,  datatype,  pdata,  ilen);

	return 0; 
} 

int  CALLBACK StreamClientSDKMsgFunc(int  sessionhandle,  void*  userdata,  int  opt, 
									 void*  param1,  void*  param2, void* param3,  void* param4) 
{   
	if (sessionhandle  < 0) 
	{ 
		return 0; 
	} 
	
	int screenNo = DlgMain->DlgTabVideo.DlgScreen.m_video.m_StreamClient.GetHandleWindID(sessionhandle);

	if(screenNo < 0 )
	{ 
		return 0; 
	} 

	char errDescribe[512] = {0}; 
	sprintf(errDescribe,  "StreamClient recv errCode:%d, errDescribe:%s", 
		opt, 
		StreamClient_GetErrMsgByErrCode(opt)); 

	DlgMain->ShowCameraMessage(DlgMain->DlgTabVideo.DlgScreen.m_videoInfo[screenNo].name.GetBuffer(0),errDescribe,FALSE);


	return 0; 
} 

CStreamClientSDK::CStreamClientSDK()
{
	for(int i=0;i<MAX_DEVICE_NUM;i++)
	{
		//m_LoginHandle[i] = -1;
		m_RealHandle[i] = -1;
		m_lPort[i] = -1;
	}
	m_ptzRealHandle = -1;
	//m_ptzLoginHandle = -1;
	SDKInit();
}

CStreamClientSDK::~CStreamClientSDK()
{
	for(int i=0;i<MAX_DEVICE_NUM;i++)
		StopPlay(i);

	PtzStopPlay();
	StreamClient_FiniLib();
}

void CStreamClientSDK::SDKInit()
{
	// ��ʼ��
	StreamClient_InitLib();
}

bool CStreamClientSDK::StartPlay(int screenNo,char *name,char *sip,
								 char *user,char *psw,HWND hWnd,int subtype,
								 char *Rtspurl,int RTP,int DecodeTag)
{
	if(m_RealHandle[screenNo] >=0)
	{
		StopPlay(screenNo);
	}
	int i;
	int transmethod;

	m_RealHandle[screenNo]=StreamClient_CreateSession();
	if(m_RealHandle[screenNo]>=0)
	{

		i=StreamClient_SetMsgCallBack(m_RealHandle[screenNo],StreamClientSDKMsgFunc,NULL);
		if(i)
		{
			DlgMain->ShowCameraMessage(name,(char*)StreamClient_GetErrMsgByErrCode(i),FALSE);
			StreamClient_DestroySession(m_RealHandle[screenNo]);
			m_RealHandle[screenNo]=-1;
			return false;
		}

		//����
		if(DecodeTag==DECODETAG_PS)
		{
			i=StreamClient_SetPsDataCallBack(m_RealHandle[screenNo],StreamClientSDKDataFunc,this);
		}
		else if(DecodeTag==DECODETAG_SRC)
		{
			i=StreamClient_SetDataCallBack(m_RealHandle[screenNo],StreamClientSDKDataFunc,this);
		}

		if(i)
		{
			DlgMain->ShowCameraMessage(name,(char*)StreamClient_GetErrMsgByErrCode(i),FALSE);
			StreamClient_DestroySession(m_RealHandle[screenNo]);
			m_RealHandle[screenNo]=-1;
			return false;
		}

		if(0==RTP)
			transmethod=RTPRTSP_TRANSMODE;
		else	if(1==RTP)
			transmethod=RTPUDP_TRANSMODE;
		else	if(2==RTP)
			transmethod=RTPMCAST_TRANSMODE;
		else
		{
			DlgMain->ShowCameraMessage(name,"RTPѡ�����",FALSE);
			StreamClient_DestroySession(m_RealHandle[screenNo]);
			m_RealHandle[screenNo]=-1;
			return false;
		}

		i=StreamClient_Start(m_RealHandle[screenNo], NULL, Rtspurl, "StreamClient",  transmethod, user, psw);
		if(i)
		{
			DlgMain->ShowCameraMessage(name,(char*)StreamClient_GetErrMsgByErrCode(i),FALSE);
			StreamClient_DestroySession(m_RealHandle[screenNo]);
			m_RealHandle[screenNo]=-1;
			return false;
		}
	}
	else
	{
		if(-3 == m_RealHandle[screenNo])
			DlgMain->ShowCameraMessage(name,"STREAM_CLIENT_NO_RTSP_SESSION��ý��ͻ��˻Ự���þ�!",FALSE);
		else	if(-2 == m_RealHandle[screenNo])
			DlgMain->ShowCameraMessage(name,"STREAM_CLIENT_NO_INIT ��ý��ͻ���δ��ʼ��!",FALSE);

		return false;
	}
	DlgMain->ShowCameraMessage(name,"���ӳɹ�",FALSE);
	return true;
}

void CStreamClientSDK::StopPlay(int screenNo)
{

	if(m_RealHandle[screenNo] >=0)
	{
		//�ر�Ԥ��
		StreamClient_Stop(m_RealHandle[screenNo]);

		//ע���û�
		StreamClient_DestroySession(m_RealHandle[screenNo]);
		//ֹͣ����
		DB33_PlayM4_Stop(m_lPort[screenNo]);
		DB33_PlayM4_CloseStream(m_lPort[screenNo]);

		DB33_PlayM4_FreePort(m_lPort[screenNo]);
	
#if OPEN_CARDETECT_CODE 	
		//ֹͣʶ��
		if(false == DlgMain->DlgTabVideo.DlgScreen.m_videoInfo[screenNo].enableCarDetect)
			DlgMain->DlgTabVideo.DlgScreen.CarDetect[screenNo].Stop();

		
				DlgMain->DlgTabVideo.DlgScreen.CarAdd[screenNo]=0;
#endif

#if OPEN_FACEDETECT_CODE 	
		//ֹͣʶ��
		if(false == DlgMain->DlgTabVideo.DlgScreen.m_videoInfo[screenNo].enableFaceDetect)
			DlgMain->DlgTabVideo.DlgScreen.FaceDetect[screenNo].Stop();

		DlgMain->DlgTabVideo.DlgScreen.FaceAdd[screenNo]=0;
#endif

	}
	m_lPort[screenNo]=-1;
	m_RealHandle[screenNo]=-1;


}

void CStreamClientSDK::PtzControl(LONG lRealHandle, int type, BOOL dwStop, int param)
{
	DlgMain->ShowCameraMessage("NULL","��ý�� ��֧����̨!",TRUE);
}

bool CStreamClientSDK::PtzStartPlay(char *sip,int nPort,int channel,char *user,char *psw,HWND hWnd)
{
	DlgMain->ShowCameraMessage("NULL","��ý�� ��֧����̨!",TRUE);
	return false;

}

void CStreamClientSDK::PtzStopPlay()
{
	return ;
}

void CStreamClientSDK::Capture(int screenNo,char *filename)
{

	CapturePath[screenNo]=filename;
	Sleep(150);

}

int CStreamClientSDK::GetPortWndindex(long lport)
{

	for(int i=0;i<MAX_DEVICE_NUM;i++)
	{
		if(m_lPort[i] == lport)
			return i;
	}
	return -1;
}

//���ݲ��ž����ȡ����ID
int CStreamClientSDK::GetHandleWindID(long RealHandle)
{
	for(int i=0;i<MAX_DEVICE_NUM;i++)
	{
		if(m_RealHandle[i] == RealHandle)
		{
			return i;
		}
	}
	return -1;
}


int CStreamClientSDK::StartRecord(int screenNo,char *filename)
{
	DlgMain->ShowCameraMessage("NULL","��ý�� ��֧��¼��!",TRUE);
	return 0;
}

int CStreamClientSDK::StopRecord(int screenNo)
{
	return 0;
}


//#endif


#endif