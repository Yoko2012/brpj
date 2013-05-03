
#include "stdafx.h"
#include "HaikangSDK.h"

//////////////////////////////////
#include "CarDetect.h"
//////////////////////////////////

//////////////////////////////////
#include "YiRongCarDetectAIO.h"
#include "YiRongCarDetectAIODlg.h"
extern CYiRongCarDetectAIODlg *DlgMain;

//#if (ALLTAB_CAMERA_INC_TYPE == CAMERA_INC_HAIKANG)

#include "haikangSDK/HCNetSDK.h"
#include "haikangSDK/plaympeg4.h"

#pragma comment(lib, "haikangSDK/HCNetSDK.lib")
#pragma comment(lib, "haikangSDK/PlayCtrl.lib")

/*********************************************************
  Function:	DisplayCBFun
  Desc:		the call back function to snatch the bmp pictrue
  Input:	nPort,port;pBuf,pic buffer;nSize,pic size;nWidth,pic width;nHeight,pic height;nType,type;
  Output:	none
  Return:	none
**********************************************************/
void CALLBACK RemoteDisplayCBFun(long nPort,char * pBuf,long nSize,long nWidth,long nHeight,long nStamp,long nType,long nReserved)
{
	int screenNo = DlgMain->DlgScreen.m_video.m_haikang.GetPortWndindex(nPort);
	if(screenNo<0)
		return;
	//������ʶ��
	
	//δ����ʶ��
	if(! DlgMain->DlgScreen.m_videoInfo[screenNo].enableDetect)
		return ;
	
	//����ʶ��
#if OPEN_CARDETECT_CODE 	

	//������ֵ
	DlgMain->DlgScreen.CarDetect[screenNo].m_playhandle=screenNo;
	
	DlgMain->DlgScreen.CarDetect[screenNo].alarmflag=
		DlgMain->DlgScreen.m_videoInfo[screenNo].enableAlarm;
	
	DlgMain->DlgScreen.CarDetect[screenNo].camid=
		DlgMain->DlgScreen.m_videoInfo[screenNo].camID;
	
	strcpy(DlgMain->DlgScreen.CarDetect[screenNo].cam_name,
		DlgMain->DlgScreen.m_videoInfo[screenNo].name.GetBuffer(0));
	
	strcpy(DlgMain->DlgScreen.CarDetect[screenNo].l_ipaddr,
		DlgMain->DlgScreen.m_videoInfo[screenNo].ip.GetBuffer(0));
	//��ɫLC_VIDEO_FORMAT_YV12 ����ɫLC_VIDEO_FORMAT_I420 �෴
	DlgMain->DlgScreen.CarDetect[screenNo].Start(LC_VIDEO_FORMAT_YV12,\
		(unsigned char *)pBuf,nWidth,nHeight,nSize);
	
	DlgMain->DlgScreen.CarDetect[screenNo].Result();
	
#endif


}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CALLBACK g_RealDataCallBack_V30(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer,DWORD dwBufSize,void* dwUser)
{
	CHaikangSDK *HaikangSDK = (CHaikangSDK *)dwUser;
	int screenNo = DlgMain->DlgScreen.GetHandleWindID(lRealHandle);
	LONG lPort = HaikangSDK->m_lPort[screenNo];
	CWnd* pWnd = DlgMain->DlgScreen.m_screenPannel.GetPage(screenNo);
	if (!pWnd)
	{
		return;
	}
	switch (dwDataType)
	{
	case NET_DVR_SYSHEAD: //ϵͳͷ
		if (lPort < 0)
		{
			if (PlayM4_GetPort(&lPort))  //��ȡ���ſ�δʹ�õ�ͨ����
			{
				DlgMain->DlgScreen.m_video.m_haikang.m_lPort[screenNo] = lPort;
			}
		}
		//m_iPort = lPort; //��һ�λص�����ϵͳͷ������ȡ�Ĳ��ſ�port�Ÿ�ֵ��ȫ��port���´λص�����ʱ��ʹ�ô�port�Ų���
		if (dwBufSize > 0)
		{
			if (!PlayM4_SetStreamOpenMode(lPort, STREAME_REALTIME))  //����ʵʱ������ģʽ
			{
				break;
			}

			if (!PlayM4_OpenStream(lPort, pBuffer, dwBufSize, 1024*1024)) //�����ӿ�
			{
				break;
			}

			if (!PlayM4_SetDisplayCallBack(lPort, RemoteDisplayCBFun))
			{
				break;
			}
			if (!PlayM4_Play(lPort, pWnd->m_hWnd)) //���ſ�ʼ
			{
				break;
			}

		}
	case NET_DVR_STREAMDATA:   //��������
		if (dwBufSize > 0 && lPort != -1)
		{
			if (!PlayM4_InputData(lPort, pBuffer, dwBufSize))
			{
				break;
			} 
		}
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
	SDKInit();
}

CHaikangSDK::~CHaikangSDK()
{
	for(int i=0;i<MAX_DEVICE_NUM;i++)
		StopPlay(i);
	NET_DVR_Cleanup();
}

void CHaikangSDK::SDKInit()
{
	// ��ʼ��
	NET_DVR_Init();
	//��������ʱ��������ʱ��
	NET_DVR_SetConnectTime(2000, 1);
	NET_DVR_SetReconnect(10000, true);
}

bool CHaikangSDK::StartPlay(int screenNo,char *name,char *sip,int nPort,char *user,char *psw,HWND hWnd,int subtype)
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
		//DlgMain->ShowCameraMessage(name,"Login error!",flag);
		printf("Login error, %d\n", NET_DVR_GetLastError());
		NET_DVR_Cleanup();
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
	ClientInfo.lChannel = 1;		//Ԥ��ͨ����
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
		//DlgMain->ShowCameraMessage(name,"Play error!",flag);
		printf("NET_DVR_RealPlay_V30 error\n");
		NET_DVR_Logout(m_LoginHandle[screenNo]);
		NET_DVR_Cleanup();
		m_LoginHandle[screenNo] = -1;
		return false;
	}
	return true;
}

void CHaikangSDK::StopPlay(int screenNo)
{
	//�ر�Ԥ��
	NET_DVR_StopRealPlay(m_RealHandle[screenNo]);
	//ע���û�
	NET_DVR_Logout_V30(m_LoginHandle[screenNo]);

#if OPEN_CARDETECT_CODE 	
	//ֹͣʶ��
	DlgMain->DlgScreen.CarDetect[screenNo].Stop();
#endif

}

void CHaikangSDK::Capture(int screenNo,char *filename)
{
	if (NET_DVR_CapturePicture(m_LoginHandle[screenNo], filename))
	{
		//DlgMain->ShowCameraMessage(name,"ץͼ�ɹ�!",flag);
	}
	else
	{
		//DlgMain->ShowCameraMessage(name,"ץͼʧ��!",flag);
	}
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

//#endif
