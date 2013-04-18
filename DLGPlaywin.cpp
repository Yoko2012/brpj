// DLGPlaywin.cpp : implementation file
//

#include "stdafx.h"
#include "BarcodeRecord.h"
#include "DLGPlaywin.h"

#include "Yaanlib/launet.h"
#include "Yaanlib/megaplay.h"

#include "BarcodeRecordDlg.h"
extern CBarcodeRecordDlg *pCMainDlg;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDLGPlaywin dialog


CDLGPlaywin::CDLGPlaywin(CWnd* pParent /*=NULL*/)
	: CDialog(CDLGPlaywin::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDLGPlaywin)
		// NOTE: the ClassWizard will add member initialization here

	//}}AFX_DATA_INIT
	m_curScreen = 0;
}


void CDLGPlaywin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDLGPlaywin)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDLGPlaywin, CDialog)
	//{{AFX_MSG_MAP(CDLGPlaywin)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDLGPlaywin message handlers
BOOL CDLGPlaywin::OnInitDialog()
{
	Language_SetWndStaticText(this);
	CDialog::OnInitDialog();
	
	LC_PLAYM4_Initial((long)this->m_hWnd);

	m_video.SDKinit();

	m_screenPannel.Create(
		NULL,
		NULL,
		WS_CHILD|WS_VISIBLE, 
		CRect(0,0,0,0), 
		this, 
		1981);
	//����
	m_screenPannel.ShowWindow(SW_SHOW);

	m_screenPannel.SetShowPlayWin(SCREEN_4MODE, m_curScreen);	
	

	AutoSize();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDLGPlaywin::AutoSize()
{
	CRect rc(0, 0, 0, 0);
	GetClientRect(&rc);

	//��Ϣ
	CRect info_Rect;
	info_Rect.top = rc.bottom-15;
	info_Rect.bottom =  rc.bottom;
	info_Rect.left = rc.left;
	info_Rect.right =rc.right;
	//���� ��ʽ=�ص����߿�=������С
	GetDlgItem(IDC_STATIC_INFO)->MoveWindow(info_Rect);

	//����rc
	rc.bottom=info_Rect.top;

	//���¸���Ƶ���䴰��
	m_screenPannel.MoveWindow(rc);


	Invalidate();
}

//����ѡ��Ĵ���
void CDLGPlaywin::SetCurWindId(int nCuWinID)
{
	m_curScreen = nCuWinID;
}

//��ȡ��ǰѡ��Ĵ���
int CDLGPlaywin::GetCurWindId()
{
	return m_curScreen;
}

//��ȡ��ǰѡ��Ĵ��ڵĲ���״̬
BOOL CDLGPlaywin::GetWindPlayState(int screenNo)
{
	return m_video.m_bplay[screenNo];
}

//��ʼ����
bool CDLGPlaywin::StartPlay()
{
	CWnd* pWnd = m_screenPannel.GetPage(m_curScreen);
	if (!pWnd)
	{
		return false;
	}
	//m_video.LinPlay("10.142.50.249",0,"�����",3000,"888888","888888",3,this->m_hWnd);
	m_video.StartPlay(m_curScreen,"�����","10.142.50.249",3000,"888888","888888",pWnd->m_hWnd);
	return false;
}

void CDLGPlaywin::StopPlay()
{
	m_video.StopPlay(m_curScreen);
}

//ץ��ͼ��
void CDLGPlaywin::CapturePic(char *filename)
{
	m_video.CapturePic(m_curScreen,filename);
}

//��ʼ¼��
void CDLGPlaywin::StartRecord(LPCSTR filename)
{
	m_video.StartRecord(m_curScreen,filename);
}

//ֹͣ¼��
void CDLGPlaywin::StopRecord()
{
	m_video.StopRecord(m_curScreen);
}

HBRUSH CDLGPlaywin::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT); // ����͸������
		// TODO: Change any attributes of the DC here
		pDC->SetTextColor(RGB(255, 0, 0)); // �����ı���ɫ
		// TODO: Return a non-NULL brush if the parent's handler should not be called
		hbr=(HBRUSH)GetStockObject(HOLLOW_BRUSH); // ����͸����ˢ	
		// TODO: Return a different brush if the default is not desired
	}
	return hbr;
}
