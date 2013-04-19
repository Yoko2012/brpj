// DLGSetPTZ.cpp : implementation file
//

#include "stdafx.h"
#include "yirongcardetectaio.h"
#include "DLGSetPTZ.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDLGSetPTZ message handlers


CDLGSetPTZ::CDLGSetPTZ(CWnd* pParent /*=NULL*/)
	: CDialog(CDLGSetPTZ::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDLGSetPTZ)
	m_edit_speed = 0;
	m_edit_set = 0;
	//}}AFX_DATA_INIT
}


void CDLGSetPTZ::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDLGSetPTZ)

	DDX_Control(pDX, IDC_AUTO, m_auto);
	DDX_Control(pDX, IDC_BUTTON_GO, m_go);
	DDX_Control(pDX, IDC_BUTTON_SET, m_set);
	DDX_Control(pDX, IDC_DOWN, m_down);
	DDX_Control(pDX, IDC_DOWNLEFT, m_downleft);
	DDX_Control(pDX, IDC_DOWNRIGHT, m_downright);
	DDX_Control(pDX, IDC_FOCUS_SUB, m_focussub);
	DDX_Control(pDX, IDC_FOCUS_ADD, m_focusadd);
	DDX_Control(pDX, IDC_IRIS_ADD, m_irisadd);
	DDX_Control(pDX, IDC_IRIS_SUB, m_irissub);
	DDX_Control(pDX, IDC_LEFT, m_left);
	DDX_Control(pDX, IDC_RIGHT, m_right);
	DDX_Control(pDX, IDC_SPEED_ADD, m_speedadd);
	DDX_Control(pDX, IDC_SPEED_SUB, m_speedsub);
	DDX_Control(pDX, IDC_UP, m_up);
	DDX_Control(pDX, IDC_ZOOM_SUB, m_zoomsub);
	DDX_Control(pDX, IDC_ZOOM_ADD, m_zoomadd);
	DDX_Control(pDX, IDC_UPRIGHT, m_upright);
	DDX_Control(pDX, IDC_UPLEFT, m_upleft);

	DDX_Text(pDX, IDC_EDIT_SPEED, m_edit_speed);
	DDX_Text(pDX, IDC_EDIT_SET, m_edit_set);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDLGSetPTZ, CDialog)
	//{{AFX_MSG_MAP(CDLGSetPTZ)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_UPLEFT, OnUpleft)
	ON_BN_CLICKED(IDC_UP, OnUp)
	ON_BN_CLICKED(IDC_UPRIGHT, OnUpright)
	ON_BN_CLICKED(IDC_LEFT, OnLeft)
	ON_BN_CLICKED(IDC_AUTO, OnAuto)
	ON_BN_CLICKED(IDC_RIGHT, OnRight)
	ON_BN_CLICKED(IDC_DOWNLEFT, OnDownleft)
	ON_BN_CLICKED(IDC_DOWN, OnDown)
	ON_BN_CLICKED(IDC_DOWNRIGHT, OnDownright)
	ON_BN_CLICKED(IDC_FOCUS_ADD, OnFocusAdd)
	ON_BN_CLICKED(IDC_IRIS_ADD, OnIrisAdd)
	ON_BN_CLICKED(IDC_ZOOM_ADD, OnZoomAdd)
	ON_BN_CLICKED(IDC_FOCUS_SUB, OnFocusSub)
	ON_BN_CLICKED(IDC_IRIS_SUB, OnIrisSub)
	ON_BN_CLICKED(IDC_ZOOM_SUB, OnZoomSub)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSet)
	ON_BN_CLICKED(IDC_BUTTON_GO, OnButtonGo)
	ON_BN_CLICKED(IDC_SPEED_SUB, OnSpeedSub)
	ON_BN_CLICKED(IDC_SPEED_ADD, OnSpeedAdd)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDLGSetPTZ message handlers
BOOL CDLGSetPTZ::OnInitDialog()
{
	CDialog::OnInitDialog();
	//��ͼƬ
	ButtonBMP();

//�����޸�͸����
//RECT p;
//	GetDlgItem(IDC_STATIC_RECT)->GetWindowRect(&p);

	

	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CDLGSetPTZ::ButtonBMP() 
{

	m_auto.LoadBitmaps(IDB_PTZ_AUTO_OPEN,IDB_PTZ_AUTO_MOVE,NULL,IDB_PTZ_AUTO_CLOSE);
	m_auto.SizeToContent();		//����ӦͼƬ��С

	m_go.LoadBitmaps(IDB_PTZ_GO_OPEN,IDB_PTZ_GO_MOVE,NULL,IDB_PTZ_GO_CLOSE);
	m_go.SizeToContent();		//����ӦͼƬ��С

	m_set.LoadBitmaps(IDB_PTZ_SET_OPEN,IDB_PTZ_SET_MOVE,NULL,IDB_PTZ_SET_CLOSE);
	m_set.SizeToContent();		//����ӦͼƬ��С

	m_down.LoadBitmaps(IDB_PTZ_DOWN_OPEN,IDB_PTZ_DOWN_MOVE,NULL,IDB_PTZ_DOWN_CLOSE);
	m_down.SizeToContent();		//����ӦͼƬ��С

	m_downleft.LoadBitmaps(IDB_PTZ_LEFTDOWN_OPEN,IDB_PTZ_LEFTDOWN_MOVE,NULL,IDB_PTZ_LEFTDOWN_CLOSE);
	m_downleft.SizeToContent();		//����ӦͼƬ��С

	m_downright.LoadBitmaps(IDB_PTZ_RIGHTDOWN_OPEN,IDB_PTZ_RIGHTDOWN_MOVE,NULL,IDB_PTZ_RIGHTDOWN_CLOSE);
	m_downright.SizeToContent();		//����ӦͼƬ��С

	m_focusadd.LoadBitmaps(IDB_PTZ_FOCUSADD_OPEN,IDB_PTZ_FOCUSADD_MOVE,NULL,IDB_PTZ_FOCUSADD_CLOSE);
	m_focusadd.SizeToContent();		//����ӦͼƬ��С
	
	m_focussub.LoadBitmaps(IDB_PTZ_FOCUSSUB_OPEN,IDB_PTZ_FOCUSSUB_MOVE,NULL,IDB_PTZ_FOCUSSUB_CLOSE);
	m_focussub.SizeToContent();		//����ӦͼƬ��С

	m_irisadd.LoadBitmaps(IDB_PTZ_IRISADD_OPEN,IDB_PTZ_IRISADD_MOVE,NULL,IDB_PTZ_IRISADD_CLOSE);
	m_irisadd.SizeToContent();		//����ӦͼƬ��С
	
	m_irissub.LoadBitmaps(IDB_PTZ_IRISSUB_OPEN,IDB_PTZ_IRISSUB_MOVE,NULL,IDB_PTZ_IRISSUB_CLOSE);
	m_irissub.SizeToContent();		//����ӦͼƬ��С

	m_left.LoadBitmaps(IDB_PTZ_LEFT_OPEN,IDB_PTZ_LEFT_MOVE,NULL,IDB_PTZ_LEFT_CLOSE);
	m_left.SizeToContent();		//����ӦͼƬ��С
	
	m_right.LoadBitmaps(IDB_PTZ_RIGHT_OPEN,IDB_PTZ_RIGHT_MOVE,NULL,IDB_PTZ_RIGHT_CLOSE);
	m_right.SizeToContent();		//����ӦͼƬ��С

	m_speedadd.LoadBitmaps(IDB_PTZ_SPEEDADD_OPEN,IDB_PTZ_SPEEDADD_MOVE,NULL,IDB_PTZ_SPEEDADD_CLOSE);
	m_speedadd.SizeToContent();		//����ӦͼƬ��С
	
	m_speedsub.LoadBitmaps(IDB_PTZ_SPEEDSUB_OPEN,IDB_PTZ_SPEEDSUB_MOVE,NULL,IDB_PTZ_SPEEDSUB_CLOSE);
	m_speedsub.SizeToContent();		//����ӦͼƬ��С

	m_up.LoadBitmaps(IDB_PTZ_UP_OPEN,IDB_PTZ_UP_MOVE,NULL,IDB_PTZ_UP_CLOSE);
	m_up.SizeToContent();		//����ӦͼƬ��С

	m_zoomsub.LoadBitmaps(IDB_PTZ_ZOOMSUB_OPEN,IDB_PTZ_ZOOMSUB_MOVE,NULL,IDB_PTZ_ZOOMSUB_CLOSE);
	m_zoomsub.SizeToContent();		//����ӦͼƬ��С

	m_zoomadd.LoadBitmaps(IDB_PTZ_ZOOMADD_OPEN,IDB_PTZ_ZOOMADD_MOVE,NULL,IDB_PTZ_ZOOMADD_CLOSE);
	m_zoomadd.SizeToContent();		//����ӦͼƬ��С

	m_upright.LoadBitmaps(IDB_PTZ_RIGHTUP_OPEN,IDB_PTZ_RIGHTUP_MOVE,NULL,IDB_PTZ_RIGHTUP_CLOSE);
	m_upright.SizeToContent();		//����ӦͼƬ��С

	m_upleft.LoadBitmaps(IDB_PTZ_LEFTUP_OPEN,IDB_PTZ_LEFTUP_MOVE,NULL,IDB_PTZ_LEFTUP_CLOSE);
	m_upleft.SizeToContent();		//����ӦͼƬ��С

}

void CDLGSetPTZ::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
	//������ͼ	
	CRect    rect;     
	GetClientRect(&rect);     
	
	//����Դ������λͼ     
	CBitmap    bitmap;     
	bitmap.LoadBitmap(IDB_SETPTZ_BACK);    
	BITMAP bmp;
	bitmap.GetBitmap(&bmp);
	
	CDC    memdc;     
	memdc.CreateCompatibleDC(&dc);     
	memdc.SelectObject(bitmap); 
	dc.SetStretchBltMode(COLORONCOLOR);
	dc.StretchBlt(0,0,rect.Width(),rect.Height(),&memdc,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
	memdc.DeleteDC();

	CDialog::OnPaint();
}


//�����¼���Ӧ///////////////////////////////
void CDLGSetPTZ::OnUpleft() 
{
	// TODO: Add your control notification handler code here
}

void CDLGSetPTZ::OnUp() 
{
	// TODO: Add your control notification handler code here
	
}

void CDLGSetPTZ::OnUpright() 
{
	// TODO: Add your control notification handler code here
	
}

void CDLGSetPTZ::OnLeft() 
{
	// TODO: Add your control notification handler code here
	
}

void CDLGSetPTZ::OnAuto() 
{
	// TODO: Add your control notification handler code here
	
}

void CDLGSetPTZ::OnRight() 
{
	// TODO: Add your control notification handler code here
	
}

void CDLGSetPTZ::OnDownleft() 
{
	// TODO: Add your control notification handler code here
	
}

void CDLGSetPTZ::OnDown() 
{
	// TODO: Add your control notification handler code here
	
}

void CDLGSetPTZ::OnDownright() 
{
	// TODO: Add your control notification handler code here
	
}

void CDLGSetPTZ::OnFocusAdd() 
{
	// TODO: Add your control notification handler code here
	
}

void CDLGSetPTZ::OnIrisAdd() 
{
	// TODO: Add your control notification handler code here
	
}

void CDLGSetPTZ::OnZoomAdd() 
{
	// TODO: Add your control notification handler code here
	
}

void CDLGSetPTZ::OnFocusSub() 
{
	// TODO: Add your control notification handler code here
	
}

void CDLGSetPTZ::OnIrisSub() 
{
	// TODO: Add your control notification handler code here
	
}

void CDLGSetPTZ::OnZoomSub() 
{
	// TODO: Add your control notification handler code here
	
}

void CDLGSetPTZ::OnButtonSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_edit_set = 0;

}

void CDLGSetPTZ::OnButtonGo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_edit_set = 0;
}

void CDLGSetPTZ::OnSpeedSub() 
{
	// TODO: Add your control notification handler code here
	
	m_edit_speed = 0;
	UpdateData(FALSE);
				
}

void CDLGSetPTZ::OnSpeedAdd() 
{
	// TODO: Add your control notification handler code here
	m_edit_speed = 0;
	UpdateData(FALSE);
}

HBRUSH CDLGSetPTZ::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT); // ����͸������
		// TODO: Change any attributes of the DC here
		pDC->SetTextColor(RGB(0, 0, 0)); // �����ı���ɫ
		// TODO: Return a non-NULL brush if the parent's handler should not be called
		hbr=(HBRUSH)GetStockObject(HOLLOW_BRUSH); // ����͸����ˢ	
		// TODO: Return a different brush if the default is not desired
	}
	return hbr;
	
}
