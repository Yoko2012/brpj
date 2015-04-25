
#include "stdafx.h"

#if OPEN_HAIKANG_SDK

#include "HaikangSDK.h"

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



/*********************************************************
  Function:	DisplayCBFun
  Desc:		the call back function to snatch the bmp pictrue
  Input:	nPort,port;pBuf,pic buffer;nSize,pic size;nWidth,pic width;nHeight,pic height;nType,type;
  Output:	none
  Return:	none
**********************************************************/
void CALLBACK RemoteDisplayCBFun(long nPort,char * pBuf,long nSize,long nWidth,long nHeight,long nStamp,long nType,long nReserved)
{
	int screenNo = DlgMain->DlgTabVideo.DlgScreen.m_video.m_haikang.GetPortWndindex(nPort);
	if(screenNo<0)
		return;

	if( ! DlgMain->DlgTabVideo.DlgScreen.m_video.m_haikang.CapturePath[screenNo].IsEmpty())
	{
		PlayM4_ConvertToJpegFile(pBuf, nSize, nWidth, nHeight, nType, 
			DlgMain->DlgTabVideo.DlgScreen.m_video.m_haikang.CapturePath[screenNo].GetBuffer(0));

		DlgMain->DlgTabVideo.DlgScreen.m_video.m_haikang.CapturePath[screenNo]="";
	}

	//������ʶ��
	
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
		
		strcpy(DlgMain->DlgTabVideo.DlgScreen.CarDetect[screenNo].l_ipaddr,
			DlgMain->DlgTabVideo.DlgScreen.m_videoInfo[screenNo].ip.GetBuffer(0));
		//��ɫLC_VIDEO_FORMAT_YV12 ����ɫLC_VIDEO_FORMAT_I420 �෴
		DlgMain->DlgTabVideo.DlgScreen.CarDetect[screenNo].Start(LC_VIDEO_FORMAT_YV12,\
			(unsigned char *)pBuf,nWidth,nHeight,nSize);
		
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
			(unsigned char *)pBuf,nWidth,nHeight,nWidth*3,nSize);
		
			//ZOGDramBMP("d:\\112212121.bmp",DlgMain->DlgTabVideo.DlgScreen.RGBdata[screenNo], nWidth,nHeight);
		}
	}

#endif



}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CALLBACK g_RealDataCallBack_V30(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer,DWORD dwBufSize,void* dwUser)
{
	CHaikangSDK *HaikangSDK = (CHaikangSDK *)dwUser;
	int screenNo = DlgMain->DlgTabVideo.DlgScreen.m_video.m_haikang.GetHandleWindID(lRealHandle);
	LONG lPort = HaikangSDK->m_lPort[screenNo];
	CWnd* pWnd=NULL;
	switch (dwDataType)
	{
	case NET_DVR_SYSHEAD: //ϵͳͷ
		
			if (PlayM4_GetPort(&lPort))  //��ȡ���ſ�δʹ�õ�ͨ����
			{
				DlgMain->DlgTabVideo.DlgScreen.m_video.m_haikang.m_lPort[screenNo] = lPort;
			}
	
		//m_iPort = lPort; //��һ�λص�����ϵͳͷ������ȡ�Ĳ��ſ�port�Ÿ�ֵ��ȫ��port���´λص�����ʱ��ʹ�ô�port�Ų���
		if (dwBufSize > 0)
		{
			if (!PlayM4_SetStreamOpenMode(lPort, STREAME_REALTIME))  //����ʵʱ������ģʽ
			{
				PlayM4_FreePort(lPort);
				break;
			}

			if (!PlayM4_OpenStream(lPort, pBuffer, dwBufSize, 1920*1080*3)) //�����ӿ�
			{
				PlayM4_FreePort(lPort);
				break;
			}

			if (!PlayM4_SetDisplayCallBack(lPort, RemoteDisplayCBFun))
			{
				PlayM4_CloseStream(lPort);
				PlayM4_FreePort(lPort);
				break;
			}
			if(DlgSetSystem.m_display_preview)
			{
				pWnd= DlgMain->DlgTabVideo.DlgScreen.m_screenPannel.GetPage(screenNo);
				if (!pWnd)
				{
					PlayM4_CloseStream(lPort);
					PlayM4_FreePort(lPort);
					return;
				}
				if (!PlayM4_Play(lPort, pWnd->m_hWnd)) //���ſ�ʼ
				{
					PlayM4_CloseStream(lPort);
					PlayM4_FreePort(lPort);
					break;
				}
			}
			else
			{

				if (!PlayM4_Play(lPort,NULL)) //���ſ�ʼ
				{
					PlayM4_CloseStream(lPort);
					PlayM4_FreePort(lPort);
					break;
				}
			}
		}
		break;
	case NET_DVR_STREAMDATA:   //��������
		if (dwBufSize > 0 && lPort != -1)
		{
			if (!PlayM4_InputData(lPort, pBuffer, dwBufSize))
			{
				break;
			} 
		}
		break;
	}
}

void CALLBACK g_ExceptionCallBack(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser)
{
	char tempbuf[256] = {0};
	switch(dwType) 
	{
		case EXCEPTION_RECONNECT:    //Ԥ��ʱ����
			break;
		default:
			break;
	}
}


CHaikangSDK::CHaikangSDK()
{
	for(int i=0;i<MAX_DEVICE_NUM;i++)
	{
		m_LoginHandle[i] = -1;
		m_RealHandle[i] = -1;
		m_lPort[i] = -1;
	}
	m_ptzRealHandle = -1;
	m_ptzLoginHandle = -1;
	SDKInit();
}

CHaikangSDK::~CHaikangSDK()
{
	for(int i=0;i<MAX_DEVICE_NUM;i++)
		StopPlay(i);

	PtzStopPlay();
	NET_DVR_Cleanup();
}

void CHaikangSDK::SDKInit()
{
	// ��ʼ��
	NET_DVR_Init();
	//��������ʱ��������ʱ��
	NET_DVR_SetConnectTime(2000, 5);
	NET_DVR_SetReconnect(10000, true);
}

bool CHaikangSDK::StartPlay(int screenNo,char *name,char *sip,int nPort,int channel,
							char *user,char *psw,HWND hWnd,int subtype)
{
	if(m_LoginHandle[screenNo] != -1)
	{
		StopPlay(screenNo);
	}
	//---------------------------------------
	// ע���豸
	NET_DVR_DEVICEINFO_V30 struDeviceInfo;
	m_LoginHandle[screenNo] = NET_DVR_Login_V30(sip, nPort, user, psw, &struDeviceInfo);
	if (m_LoginHandle[screenNo] < 0)
	{
		DlgMain->ShowCameraMessage(name,"Login error!",FALSE);
		printf("Login error, %d\n", NET_DVR_GetLastError());
		//NET_DVR_Cleanup();
		return false;
	}

	//---------------------------------------
	//�����쳣��Ϣ�ص�����
	NET_DVR_SetExceptionCallBack_V30(0, NULL,g_ExceptionCallBack, NULL);

	//---------------------------------------
	//����Ԥ�������ûص�������
	NET_DVR_CLIENTINFO ClientInfo = {0};
	//��ҪSDK����ʱ�����Ϊ��Чֵ����ȡ��������ʱ����Ϊ��
	ClientInfo.hPlayWnd = NULL;
	ClientInfo.lChannel = channel;		//Ԥ��ͨ����
	//���λ(31)Ϊ0��ʾ��������Ϊ1��ʾ������0��30λ��ʾ���ӷ�ʽ��0��TCP��ʽ��1��UDP��ʽ��2���ಥ��ʽ��3��RTP��ʽ;
	if(subtype == 0)
		ClientInfo.lLinkMode = 0;
	else
		ClientInfo.lLinkMode = 0x80000000;
	ClientInfo.sMultiCastIP = NULL;	//�ಥ��ַ����Ҫ�ಥԤ��ʱ����
  
	BOOL bPreviewBlock = false;       //�������������Ƿ�������0����1����
	m_RealHandle[screenNo] = NET_DVR_RealPlay_V30(m_LoginHandle[screenNo], &ClientInfo, g_RealDataCallBack_V30, this, 0);
	if (m_RealHandle[screenNo] < 0)
	{
		DlgMain->ShowCameraMessage(name,"Play error!",FALSE);
		printf("NET_DVR_RealPlay_V30 error\n");
		NET_DVR_Logout(m_LoginHandle[screenNo]);
	//	NET_DVR_Cleanup();
		m_LoginHandle[screenNo] = -1;
		return false;
	}

	DlgMain->ShowCameraMessage(name,"���ӳɹ�",FALSE);
	return true;
}

void CHaikangSDK::StopPlay(int screenNo)
{

	//�ر�Ԥ��
	NET_DVR_StopRealPlay(m_RealHandle[screenNo]);
	//ע���û�
	NET_DVR_Logout_V30(m_LoginHandle[screenNo]);
	
	PlayM4_Stop(m_lPort[screenNo]);
	PlayM4_CloseStream(m_lPort[screenNo]);
	PlayM4_FreePort(m_lPort[screenNo]);

	m_LoginHandle[screenNo] = -1;
	m_lPort[screenNo]=-1;

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

void CHaikangSDK::PtzControl(LONG lRealHandle, int type, BOOL dwStop, int param)
{
	BOOL ret;
	if (dwStop)
	{
		if(!m_bPTZCtrl)
		{
			goto exitPTZCtrl;
		}
	}
	if(lRealHandle == 0)
	{
		goto exitPTZCtrl;
	}

	switch(type)
	{
		case PTZ_CONTROL_UP:
		case PTZ_CONTROL_DOWN:
		case PTZ_CONTROL_LEFT:
		case PTZ_CONTROL_RIGHT:
			ret = NET_DVR_PTZControlWithSpeed(lRealHandle, type+21, dwStop, param);
			m_bPTZCtrl = !dwStop;
			break;
		case PTZ_CONTROL_ZOOM_ADD:
		case PTZ_CONTROL_ZOOM_SUB:
		case PTZ_CONTROL_FOCUS_ADD:
		case PTZ_CONTROL_FOCUS_SUB:
		case PTZ_CONTROL_IRIS_ADD:
		case PTZ_CONTROL_IRIS_SUB:
			ret = NET_DVR_PTZControlWithSpeed(lRealHandle, type+7, dwStop, param);
			m_bPTZCtrl = !dwStop;
			break;
		case PTZ_CONTROL_POINT_MOVE:
			ret = NET_DVR_PTZControlWithSpeed(lRealHandle, GOTO_PRESET, dwStop, param);
			m_bPTZCtrl = !dwStop;
			break;
		case PTZ_CONTROL_POINT_SET:
			ret = NET_DVR_PTZControlWithSpeed(lRealHandle, SET_PRESET, dwStop, param);
			m_bPTZCtrl = !dwStop;
			break;
		case PTZ_CONTROL_UPLEFT:
		case PTZ_CONTROL_UPRIGHT:
		case PTZ_CONTROL_DOWNLEFT:
		case PTZ_CONTROL_DOWNRIGHT:
			ret = NET_DVR_PTZControlWithSpeed(lRealHandle, type+16, dwStop, param);
			m_bPTZCtrl = !dwStop;
			break;
		case PTZ_CONTROL_SPEED_ADD:
			break;
		case PTZ_CONTROL_SPEED_SUB:
			break;
		case PTZ_CONTROL_AUTO:
			ret = NET_DVR_PTZControlWithSpeed(lRealHandle, PAN_AUTO, dwStop, param);
			m_bPTZCtrl = !dwStop;
			break;
	}
	if(!ret)
	{
		//MessageBox(ConvertString(MSG_DEMODLG_PTZCTRLFAILED));
		goto exitPTZCtrl;
	}
	return;

exitPTZCtrl:
	m_bPTZCtrl = FALSE;
	return;
}

bool CHaikangSDK::PtzStartPlay(char *sip,int nPort,int channel,char *user,char *psw,HWND hWnd)
{
	//---------------------------------------
	// ע���豸
	NET_DVR_DEVICEINFO_V30 struDeviceInfo;
	m_ptzLoginHandle = NET_DVR_Login_V30(sip, nPort, user, psw, &struDeviceInfo);
	if (m_ptzLoginHandle < 0)
	{
		return false;
	}

	//---------------------------------------
	//����Ԥ�������ûص�������
	NET_DVR_CLIENTINFO ClientInfo = {0};
	//��ҪSDK����ʱ�����Ϊ��Чֵ����ȡ��������ʱ����Ϊ��
	ClientInfo.hPlayWnd = hWnd;
	ClientInfo.lChannel = channel;		//Ԥ��ͨ����
	//������
	ClientInfo.lLinkMode = 0;
	ClientInfo.sMultiCastIP = NULL;	//�ಥ��ַ����Ҫ�ಥԤ��ʱ����
	BOOL bPreviewBlock = false;

	m_ptzRealHandle = NET_DVR_RealPlay_V30(m_ptzLoginHandle, &ClientInfo, NULL, this, 0);
	if (m_ptzRealHandle < 0)
	{
		NET_DVR_Logout(m_ptzLoginHandle);
		m_ptzLoginHandle = -1;
		return false;
	}
	return true;
}

void CHaikangSDK::PtzStopPlay()
{
	//�ر�Ԥ��
	if(m_ptzRealHandle != -1)
	{
		NET_DVR_StopRealPlay(m_ptzRealHandle);
	}
	//ע���û�
	if(m_ptzLoginHandle != -1)
	{
		NET_DVR_Logout_V30(m_ptzLoginHandle);
	}
}

void CHaikangSDK::Capture(int screenNo,char *filename)
{
	/*
	if (NET_DVR_CapturePicture(m_RealHandle[screenNo], filename))
	{
		//DlgMain->ShowCameraMessage(name,"ץͼ�ɹ�!",flag);
	}
	else
	{
		//DlgMain->ShowCameraMessage(name,"ץͼʧ��!",flag);
	}
	*/
	CapturePath[screenNo]=filename;
	Sleep(150);

}

int CHaikangSDK::GetPortWndindex(long lport)
{
	int Wndindex=0;
	for(int i=0;i<MAX_DEVICE_NUM;i++)
	{
		if(m_lPort[i] == lport)
			return Wndindex;
		Wndindex++;
	}
	return -1;
}

//���ݲ��ž����ȡ����ID
int CHaikangSDK::GetHandleWindID(int RealHandle)
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

int CHaikangSDK::StartRecord(int screenNo,char *filename)
{
	int iRet;
	iRet = NET_DVR_SaveRealData(m_RealHandle[screenNo],filename);
	if(iRet == 0)
	{
		TRACE("StartRecord Error:%d\n",iRet);
		return 1;
	}
	else
	{
		return 0;
	}
}

int CHaikangSDK::StopRecord(int screenNo)
{
	int iRet;
	iRet = NET_DVR_StopSaveRealData(m_RealHandle[screenNo]);
	if(iRet == 0)
	{
		TRACE("StopRecord Error:%d\n",iRet);
		return 1;
	}
	else
	{
		return 0;
	}
}

//#endif

#endif