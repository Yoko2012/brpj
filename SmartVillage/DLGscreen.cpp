// DLGscreen.cpp : implementation file
//

#include "stdafx.h"
#include "SmartVillage.h"
#include "DLGscreen.h"

////////////////////////////////
#include "YRSVMySQL.h"
extern CYRSVMySQL MySqlIO;
//////////////////////////////////
#include "SmartVillageDlg.h"
extern CSmartVillageDlg *DlgMain;
//////////////////////////////////
#include "DLGSetSystem.h"
extern CDLGSetSystem DlgSetSystem;

#include "DLGLogin.h"
extern CDLGLogin DlgLogin;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define RECORD_TIMER 111

/////////////////////////////////////////////////////////////////////////////
// CDLGscreen dialog


CDLGscreen::CDLGscreen(CWnd* pParent /*=NULL*/)
	: CDialog(CDLGscreen::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDLGscreen)
		// NOTE: the ClassWizard will add member initialization here
	m_curScreen = 0;
	m_recordtimer = 0;
	//}}AFX_DATA_INIT
	
	for(int i=0;i<MAX_DEVICE_NUM;i++)
	{
		CSdeviceID[i]=0;
		m_videoInfo[i].camID=0;
		m_videoInfo[i].isplay=false;
		m_videoInfo[i].isRecord=false;
		m_videoInfo[i].name="";

	}


}


void CDLGscreen::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDLGscreen)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDLGscreen, CDialog)
	//{{AFX_MSG_MAP(CDLGscreen)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDLGscreen message handlers
BOOL CDLGscreen::OnInitDialog()
{
	CDialog::OnInitDialog();

	//
	DlgShortCut.Create(IDD_SHORTCUT,this);
	DlgShortCut.ShowWindow(SW_SHOW);

	//�����ʼ��
	//���Ŵ���
	m_screenPannel.Create(
		NULL,
		NULL,
		WS_CHILD|WS_VISIBLE, 
		CRect(0,0,0,0), 
		this, 
		1981);
	//����
	m_screenPannel.ShowWindow(SW_SHOW);

	m_screenPannel.SetShowPlayWin(SCREEN_16MODE, m_curScreen);	
/*******************lynn*****************/
	for(int i=0;i<MAX_DEVICE_NUM;i++)
	{
		m_videoInfo[i].subtype = 0;		//������
		m_videoInfo[i].isplay = false;
		m_videoInfo[i].isRecord = false;
		m_videoInfo[i].area = "";
		m_videoInfo[i].name = "";
		m_videoInfo[i].user = "";
		m_videoInfo[i].psw = "";
		m_videoInfo[i].recordPath = "";
		m_videoInfo[i].enableCarDetect = false;
m_videoInfo[i].enableFaceDetect= false;
		m_videoInfo[i].playHandle = -1;
	}
	//��ʱ1s
	m_recordtimer = SetTimer(RECORD_TIMER,1000,NULL);

/*******************lynn*****************/
	//�������
	AutoSize();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDLGscreen::AutoSize()
{
	CRect rc(0, 0, 0, 0);
	GetClientRect(&rc);


	//��ݰ�ť�Ŀ��
	int shortcut_height=20;

	//��ݰ�ť
	CRect shortcut_Rect;
	shortcut_Rect.top = rc.bottom-shortcut_height;
	shortcut_Rect.bottom = rc.bottom;
	shortcut_Rect.left = rc.left;
	shortcut_Rect.right =rc.right;
	//���� ��ʽ=�ص����߿�=������С
	DlgShortCut.MoveWindow(shortcut_Rect);
	
	DlgShortCut.AutoSize();
	//��ݰ�ť
	CRect Pannel_Rect;
	Pannel_Rect.top = rc.top;
	Pannel_Rect.bottom = rc.bottom-shortcut_height;
	Pannel_Rect.left = rc.left;
	Pannel_Rect.right =rc.right;

	//��Ҫ�仯�������
	m_screenPannel.MoveWindow(Pannel_Rect);

	Invalidate();
}

void CDLGscreen::OnCancel()
{
	DlgMain->OnCancel();
}
void CDLGscreen::OnOK()
{

}


//�໭���л�
void CDLGscreen::SwitchMultiWnd(int nSplit)
{
	if (SCREEN_1MODE == nSplit)
	{
		m_screenPannel.SetMultiScreen(FALSE);
		return ;
	}
	else
	{
		m_screenPannel.SetMultiScreen(TRUE);
		m_screenPannel.SetShowPlayWin(nSplit, m_curScreen);
	}
}

//����ѡ��Ĵ���
void CDLGscreen::SetCurWindId(int nCuWinID)
{
	m_curScreen = nCuWinID;
}

//��ȡ��ǰѡ��Ĵ���
int CDLGscreen::GetCurWindId()
{
	return m_curScreen;
}

//��ȡ��ǰ���ڵ����������״̬
bool CDLGscreen::GetCurWindPlayState(int nCuWinID)
{
	return m_videoInfo[nCuWinID].isplay;
}

//��ȡ��ǰ���ڵ������¼��״̬
bool CDLGscreen::GetCurWindRecordState(int nCuWinID)
{
	return m_videoInfo[nCuWinID].isRecord;
}
//��ȡ��ǰ���ڵ��������ʱ¼��״̬
bool CDLGscreen::GetCurWindPlanRecordState(int nCuWinID)
{
	return m_videoInfo[nCuWinID].planRecord;
}

//��ȡ��ǰ���ڵĲ��ž��
long CDLGscreen::GetCurWindPlayHandle(int nCuWinID)
{
	return m_videoInfo[nCuWinID].playHandle;
}

//��ȡ��ǰ���ڵ����������������
int CDLGscreen::GetCurWindSubType(int nCuWinID)
{
	return m_videoInfo[nCuWinID].subtype;
}

//��ȡ��ǰѡ�񴰿ڵ����������ϸ��Ϣ
void CDLGscreen::GetCurWindCamInfo(int nCuWinID,struct DEVICE_INFO &Info)
{
	Info.area = m_videoInfo[nCuWinID].area;
	Info.camID = m_videoInfo[nCuWinID].camID;
	Info.enableCarDetect = m_videoInfo[nCuWinID].enableCarDetect;
	Info.enableFaceDetect = m_videoInfo[nCuWinID].enableFaceDetect;

	Info.ip = m_videoInfo[nCuWinID].ip;
	Info.isplay = m_videoInfo[nCuWinID].isplay;
	Info.name = m_videoInfo[nCuWinID].name;
	Info.playHandle = m_videoInfo[nCuWinID].playHandle;
	Info.port = m_videoInfo[nCuWinID].port;
	Info.channel =  m_videoInfo[nCuWinID].channel;
	Info.psw = m_videoInfo[nCuWinID].psw;
	Info.subtype = m_videoInfo[nCuWinID].subtype;
	Info.user= m_videoInfo[nCuWinID].user;
	Info.venderID = m_videoInfo[nCuWinID].venderID;
	Info.Rtspurl = m_videoInfo[nCuWinID].Rtspurl;
	Info.RTP = m_videoInfo[nCuWinID].RTP;
	Info.DecodeTag = m_videoInfo[nCuWinID].DecodeTag;
}

//����/�رճ���ʶ��
void CDLGscreen::EnableCarDetect(int nCuWinID,bool bEnable)
{
	m_videoInfo[nCuWinID].enableCarDetect = bEnable;


}

//����/�رճ���ʶ��
void CDLGscreen::EnableFaceDetect(int nCuWinID,bool bEnable)
{
	m_videoInfo[nCuWinID].enableFaceDetect = bEnable;


}


//����/�ر�¼��
void CDLGscreen::EnableRecord(int nCuWinID,bool bEnable)
{
	m_videoInfo[nCuWinID].isRecord = bEnable;
}
//��ȡʶ��״̬
bool CDLGscreen::GetCarDetectState(int nCuWinID)
{
	return m_videoInfo[nCuWinID].enableCarDetect;
}

//��ȡʶ��״̬
bool CDLGscreen::GetFaceDetectState(int nCuWinID)
{
	return m_videoInfo[nCuWinID].enableFaceDetect;
}

//��ȡ¼��״̬
bool CDLGscreen::GetRecordState(int nCuWinID)
{
	return m_videoInfo[nCuWinID].isRecord;
}



//��ʼ����
bool CDLGscreen::StartPlay(int id,char *area,char *name,char *ip,int port,int channel,
						   char *user,char *psw,int screenNo,int subtype,int venderID,
						   char *Rtspurl,int RTP,int DecodeTag)
{
	CWnd* pWnd = m_screenPannel.GetPage(screenNo);
	if (!pWnd)
	{
		return false;
	}

	//ֻ����һ����Ƶ�ڲ���
	for(int i=0;i<MAX_DEVICE_NUM;i++)
	{
		if(true == m_videoInfo[i].isplay)
		{
			if(id == m_videoInfo[i].camID)
			{

				//�Ƿ�����ִ��
				MessageBox("�����������ڲ�����",MESSAGEBOX_TITLE);
				return false;
			}
		}
	}
	//·������
	int j=0;
	for(int i=0;i<MAX_DEVICE_NUM;i++)
	{
		if(true == m_videoInfo[i].isplay)
		{
			j++;
		}
	}
	char str[64];
	sprintf(str,"���汾���֧��%d·�豸\n",MAX_CAMERA);
	if(j>=MAX_CAMERA)
	{
		//�Ƿ�����ִ��
		MessageBox(str,MESSAGEBOX_TITLE);
		return false;
	}

	if(m_videoInfo[screenNo].isplay == true)
	{
		StopPlay(screenNo);
	}

	FaceAdd[screenNo]=0;
	CarAdd[screenNo]=0;

	bool ret = m_video.StartPlay(venderID,screenNo,name, ip, port, channel, user, psw, pWnd->m_hWnd, subtype,Rtspurl,RTP,DecodeTag);
	if(ret)
	{
		m_videoInfo[screenNo].subtype = subtype;		//������
		m_videoInfo[screenNo].isplay = true;
		m_videoInfo[screenNo].area = area;
		m_videoInfo[screenNo].name = name;
		m_videoInfo[screenNo].ip = ip;
		m_videoInfo[screenNo].user = user;
		m_videoInfo[screenNo].psw = psw;
		m_videoInfo[screenNo].port = port;
		m_videoInfo[screenNo].channel = channel;
		m_videoInfo[screenNo].camID = id;
		m_videoInfo[screenNo].playHandle = m_video.m_RealHandle[screenNo];
		m_videoInfo[screenNo].venderID = venderID;
		m_videoInfo[screenNo].Rtspurl = Rtspurl;
		m_videoInfo[screenNo].RTP = RTP;
		m_videoInfo[screenNo].DecodeTag = DecodeTag;


//���������ܸ���ͼ��
		DlgMain->DlgTabVideo.DlgNormal.UpdateNormalWnd();

	}

	return ret;

}

//ֹͣ����
void CDLGscreen::StopPlay(int screenNo)
{
	if(m_videoInfo[screenNo].isRecord == true)
	{
		StopRecord(screenNo);
	}
	
	m_videoInfo[screenNo].enableCarDetect = false;
	m_videoInfo[screenNo].enableFaceDetect=false;
	Sleep(100);

	if(m_videoInfo[screenNo].isplay == true)
	{
		m_videoInfo[screenNo].isplay = false;
		m_video.StopPlay(m_videoInfo[screenNo].venderID,screenNo);
		DlgMain->ShowCameraMessage(m_videoInfo[screenNo].name.GetBuffer(0),"����ֹͣ",FALSE);
	}



#if OPEN_CARDETECT_CODE 
	//ֹͣʶ��
	if(false == m_videoInfo[screenNo].enableCarDetect)
		CarDetect[screenNo].Stop();
	
		CarAdd[screenNo]=0;
#endif
#if OPEN_FACEDETECT_CODE 	
	//ֹͣʶ��
	if(false == m_videoInfo[screenNo].enableFaceDetect)
		FaceDetect[screenNo].Stop();
	FaceAdd[screenNo]=0;
#endif


	CWnd* pWnd = m_screenPannel.GetPage(screenNo);
	if (pWnd)
	{
		pWnd->PostMessage(VIDEO_REPAINT);
	}

}
//��̨����
void CDLGscreen::PtzControl(int type, BOOL dwStop, int param)
{
	m_video.PtzControl(m_videoInfo[m_curScreen].venderID,m_curScreen,type,dwStop,param);
}

//��ʼ¼��
int CDLGscreen::StartRecord(int screenNo,char *filename)
{
	int ret = m_video.StartRecord(m_videoInfo[screenNo].venderID,screenNo,filename);
	if(ret == 0)
	{
		m_videoInfo[screenNo].isRecord = true;
	}
	return ret;
}

//ֹͣ¼��
void CDLGscreen::StopRecord(int screenNo)
{
	if(m_videoInfo[screenNo].isRecord == false)
	{
		return;
	}

	char stime[32]={0};
	char etime[32]={0};
	sprintf(stime,"%04d-%02d-%02d %02d:%02d:%02d",
					m_videoInfo[screenNo].startTime.GetYear(),
					m_videoInfo[screenNo].startTime.GetMonth(),
					m_videoInfo[screenNo].startTime.GetDay(),
					m_videoInfo[screenNo].startTime.GetHour(),
					m_videoInfo[screenNo].startTime.GetMinute(),
					m_videoInfo[screenNo].startTime.GetSecond());

	CTime nowtime=CTime::GetTickCount();

	sprintf(etime,"%04d-%02d-%02d %02d:%02d:%02d",
					nowtime.GetYear(),
					nowtime.GetMonth(),
					nowtime.GetDay(),
					nowtime.GetHour(),
					nowtime.GetMinute(),
					nowtime.GetSecond());

	m_video.StopRecord(m_videoInfo[screenNo].venderID,screenNo);
	m_videoInfo[screenNo].isRecord = false;

	FILE *fp;
	unsigned long long size=0;

	fp= fopen(m_videoInfo[screenNo].recordPath.GetBuffer(0),"rb");
	if(fp)
	{
		fseek(fp,0,SEEK_END);
		size = _ftelli64(fp);
		fclose(fp);
	}
#if OPEN_RECORD 
	MySqlIO.VIDEO_AddNewVideo(m_videoInfo[screenNo].name.GetBuffer(0),
								m_videoInfo[screenNo].ip.GetBuffer(0),
								m_videoInfo[screenNo].venderID,
								"mp4",
								size,
								stime,
								etime,
								m_videoInfo[screenNo].recordPath.GetBuffer(0));
#endif
}


//ץ��ͼ��
void CDLGscreen::Capture(char *filename)
{
	//m_video.Capture(m_videoInfo[m_curScreen].venderID,m_videoInfo[m_curScreen].playHandle,filename);
	m_video.Capture(m_videoInfo[m_curScreen].venderID,m_curScreen,filename);
}

//ɾ���豸
void CDLGscreen::DeleteDevice(long camID)
{
	for(int i=0;i<MAX_DEVICE_NUM;i++)
	{
		if(m_videoInfo[i].camID == camID)
		{
			StopPlay(i);
			DlgMain->DlgTabVideo.DlgNormal.UpdateNormalWnd();

			m_videoInfo[i].subtype = 0;		//������
			m_videoInfo[i].isplay = false;
			m_videoInfo[i].area = "";
			m_videoInfo[i].name = "";
			m_videoInfo[i].user = "";
			m_videoInfo[i].psw = "";
			m_videoInfo[i].enableCarDetect = false;
			m_videoInfo[i].enableFaceDetect = false;
			m_videoInfo[i].playHandle = -1;

		}
	}
}

void CDLGscreen::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	//������ͼ	
	CRect    rect;     
	GetClientRect(&rect);     
	
	//����Դ������λͼ     
	CBitmap    bitmap;     
	bitmap.LoadBitmap(IDB_SCREEN_BACK);    
	BITMAP bmp;
	bitmap.GetBitmap(&bmp);
	
	CDC    memdc;     
	memdc.CreateCompatibleDC(&dc);     
	memdc.SelectObject(bitmap); 
	dc.SetStretchBltMode(COLORONCOLOR);
	dc.StretchBlt(0,0,rect.Width(),rect.Height(),&memdc,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
	memdc.DeleteDC();

	CDialog::OnPaint();
	// Do not call CDialog::OnPaint() for painting messages
}

void CDLGscreen::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnTimer(nIDEvent);

	if(nIDEvent == RECORD_TIMER)
	{
		RecordTimerEvent();
#if OPEN_CARDETECT_CODE
		for(int i=0;i<MAX_DEVICE_NUM;i++)
		{
			if(CarDetect[i].JumpJPG)
			{
				ShellExecute(DlgMain->DlgTabVideo.m_hWnd,NULL,CarDetect[i].JumpJPGpath,NULL,NULL,SW_NORMAL);
				CarDetect[i].JumpJPG=false;
			}
		}
#endif
	}
}

void CDLGscreen::OnDestroy() 
{
	CDialog::OnDestroy();
	// TODO: Add your message handler code here
	if(m_recordtimer) 
		KillTimer(m_recordtimer); 
	m_recordtimer = 0;
}

//¼��ʱ�¼�
void CDLGscreen::RecordTimerEvent()
{
	for(int i=0;i<MAX_DEVICE_NUM;i++)
	{
		if(m_videoInfo[i].isRecord == true)
		{
			CTime nowtime=CTime::GetTickCount();
			CTimeSpan ts = nowtime - m_videoInfo[i].startTime;
			int recMinutes = ts.GetMinutes();
			if(recMinutes >= DlgSetSystem.m_record_cuttime)
			{
				StopRecord(i);
				DlgMain->DlgTabVideo.DlgNormal.OpenRecord(i);
			}
		}
#if OPEN_RECORD
		//��ʱ¼��
		if(DlgMain->DlgTabVideo.DlgSetRecord.NeedRecord(m_videoInfo[i].camID))
		{
			if(m_videoInfo[i].isRecord == false)
			{
				m_videoInfo[i].planRecord = true;
				DlgMain->DlgTabVideo.DlgNormal.OpenRecord(i);	//��ʼ¼��
			}
		}
		else
		{
			if(m_videoInfo[i].planRecord == true)
			{
				m_videoInfo[i].planRecord = false;
				if(m_videoInfo[i].isRecord == true)
				{
					DlgMain->DlgTabVideo.DlgNormal.CloseRecord(i);	//ֹͣ¼��
				}
			}
		}
#endif
	}

	//��ʱ¼�������ZOG
	//FOR N������ͷ
#if OPEN_RECORD
	if(DlgMain->DlgTabVideo.DlgSetRecord.NeedRecord(CAMID) )
	{
		if(m_videoInfo[i].isRecord)
		//��������
		else
		//��ʼ¼��
	
	}
	else
	{
		if(m_videoInfo[i].isRecord)
		//ֹͣ¼��
		else
		//��������
	}
#endif
}