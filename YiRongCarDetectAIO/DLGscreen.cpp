// DLGscreen.cpp : implementation file
//

#include "stdafx.h"
#include "YiRongCarDetectAIO.h"
#include "DLGscreen.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDLGscreen dialog


CDLGscreen::CDLGscreen(CWnd* pParent /*=NULL*/)
	: CDialog(CDLGscreen::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDLGscreen)
		// NOTE: the ClassWizard will add member initialization here
	m_curScreen = 0;
	//}}AFX_DATA_INIT
	/*
	for(int i=0;i<MAX_DEVICE_NUM;i++)
	{
		CarSet[i].RedRect=1;
		CarSet[i].Deskew=1;
		CarSet[i].JPGquality=75;
		CarSet[i].MinWidth=60;
		CarSet[i].MaxWidth=180;

		CarSet[i].RangeRate.x0=0;
		CarSet[i].RangeRate.x1=100;
		CarSet[i].RangeRate.y0=10;
		CarSet[i].RangeRate.y1=90;
		memcpy(CarSet[i].DefaultChar,"��",CAR_STR_MAX);
		for(int j=0;j<CAR_MASK_MAX;j++)
			CarSet[i].Mask[j]=1;
		CarSet[i].Mask[26]=0;
		CarSet[i].Reliability=50;
		CarSet[i].CarColor=1;
	}
	*/
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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDLGscreen message handlers
BOOL CDLGscreen::OnInitDialog()
{
	CDialog::OnInitDialog();

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
		m_videoInfo[i].area = "";
		m_videoInfo[i].name = "";
		m_videoInfo[i].user = "";
		m_videoInfo[i].psw = "";
		m_videoInfo[i].enableDetect = false;
		m_videoInfo[i].enableAlarm = false;
		m_videoInfo[i].playHandle = -1;
	}


/*******************lynn*****************/
	//�������
	AutoSize();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDLGscreen::AutoSize()
{
	CRect rc(0, 0, 0, 0);
	GetClientRect(&rc);
	//��Ҫ�仯�������
	m_screenPannel.MoveWindow(rc);

	Invalidate();
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
//���ݲ��ž����ȡ����ID
int CDLGscreen::GetHandleWindID(int RealHandle)
{
	for(int i=0;i<MAX_DEVICE_NUM;i++)
	{
		if(m_videoInfo[i].playHandle == RealHandle)
		{
			return i;
		}
	}
	return -1;
}
//��ȡ��ǰ���ڵ����������״̬
bool CDLGscreen::GetCurWindPlayState(int nCuWinID)
{
	return m_videoInfo[nCuWinID].isplay;
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
	Info.enableDetect = m_videoInfo[nCuWinID].enableDetect;
	Info.ip = m_videoInfo[nCuWinID].ip;
	Info.isplay = m_videoInfo[nCuWinID].isplay;
	Info.name = m_videoInfo[nCuWinID].name;
	Info.playHandle = m_videoInfo[nCuWinID].playHandle;
	Info.port = m_videoInfo[nCuWinID].port;
	Info.psw = m_videoInfo[nCuWinID].psw;
	Info.subtype = m_videoInfo[nCuWinID].subtype;
	Info.user= m_videoInfo[nCuWinID].user;
	Info.venderID = m_videoInfo[nCuWinID].venderID;
}

//����/�رճ���ʶ��
void CDLGscreen::EnableDetect(int nCuWinID,bool bEnable)
{
	m_videoInfo[nCuWinID].enableDetect = bEnable;
}

//����/�رձ���
void CDLGscreen::EnableAlarm(int nCuWinID,bool bEnable)
{
	m_videoInfo[nCuWinID].enableAlarm = bEnable;
}

//��ȡʶ��״̬
bool CDLGscreen::GetDetectState(int nCuWinID)
{
	return m_videoInfo[nCuWinID].enableDetect;
}

//��ȡʶ��״̬
bool CDLGscreen::GetAlarmState(int nCuWinID)
{
	return m_videoInfo[nCuWinID].enableAlarm;
}

//����ʶ������
void CDLGscreen::CarDetectSet(void)
{

#if ALLTAB_DETECT_CAR_MODE
	CDLGSetCar DlgSetCar;
#else
	CDLGSetElecar DlgSetCar;
#endif

#if OPEN_CARDETECT_CODE 

	DlgSetCar.ReadOldConfig(CarDetect[m_curScreen].CarSet);
	if(DlgSetCar.DoModal() == IDOK)
	{
		//���ó���ʶ��
		memcpy(&CarDetect[m_curScreen].CarSet,&DlgSetCar.CarSet,sizeof(CarSetStruct));
		CarDetect[m_curScreen].SetAll();
	}
#endif

}

//��ʼ����
bool CDLGscreen::StartPlay(int id,char *area,char *name,char *ip,int port,
						   char *user,char *psw,int screenNo,int subtype,int venderID)
{
	CWnd* pWnd = m_screenPannel.GetPage(screenNo);
	if (!pWnd)
	{
		return false;
	}

	bool ret = m_video.StartPlay(venderID,screenNo,name, ip, port, user, psw, pWnd->m_hWnd, subtype);
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
		m_videoInfo[screenNo].camID = id;
		m_videoInfo[screenNo].playHandle = m_video.m_RealHandle[screenNo];
		m_videoInfo[screenNo].venderID = venderID;
	}
	return ret;

}

//ֹͣ����
void CDLGscreen::StopPlay(int screenNo)
{
	m_videoInfo[screenNo].isplay = false;

	m_video.StopPlay(m_videoInfo[screenNo].venderID,screenNo);


#if OPEN_CARDETECT_CODE 
	//ֹͣʶ��
	CarDetect[m_curScreen].Stop();
#endif

	CWnd* pWnd = m_screenPannel.GetPage(screenNo);
	if (pWnd)
	{
		pWnd->PostMessage(VIDEO_REPAINT);
	}
}


//ץ��ͼ��
void CDLGscreen::Capture(long pHandle,char *filename)
{
	m_video.Capture(m_videoInfo[m_curScreen].venderID,pHandle,filename);
}

//ɾ���豸
void CDLGscreen::DeleteDevice(CString sip)
{
	for(int i=0;i<MAX_DEVICE_NUM;i++)
	{
		if(m_videoInfo[i].ip == sip)
		{
			StopPlay(i);
			m_videoInfo[i].subtype = 0;		//������
			m_videoInfo[i].isplay = false;
			m_videoInfo[i].area = "";
			m_videoInfo[i].name = "";
			m_videoInfo[i].user = "";
			m_videoInfo[i].psw = "";
			m_videoInfo[i].enableDetect = false;
			m_videoInfo[i].enableAlarm = false;
			m_videoInfo[i].playHandle = 0;
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
