// DLGSetFace.cpp : implementation file
//

#include "stdafx.h"
#include "SmartVillage.h"
#include "DLGSetFace.h"


extern CYRSVMySQL MySqlIO;
// CDLGSetFace dialog

IMPLEMENT_DYNAMIC(CDLGSetFace, CDialog)

CDLGSetFace::CDLGSetFace(CWnd* pParent /*=NULL*/)
	: CDialog(CDLGSetFace::IDD, pParent)
	, m_minface(32)		
	, m_threshold(80)
	, m_maxcount(10)
	, m_e_front_ts(0.8)
	, m_e_side_ts(0.8)
	, m_maxface(200)
	, m_e_timeout(10)
	, m_e_scale(1.0)
	, m_e_video_ts(80)
{
	m_BgBrush.CreateSolidBrush(RGB(216,216,216));         // ��������ɫ
}

CDLGSetFace::~CDLGSetFace()
{
}

void CDLGSetFace::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Check(pDX, IDC_CHECK, m_check);
	DDX_Control(pDX, IDOK, m_b_ok);
	DDX_Control(pDX, IDCANCEL, m_b_cancel);
	DDX_Text(pDX, IDC_EDIT_MIN_CAPFACE, m_minface);
	DDV_MinMaxInt(pDX, m_minface, 32, 240);
	DDX_Text(pDX, IDC_EDIT_THRESHOLD, m_threshold);
	DDV_MinMaxInt(pDX, m_threshold, 10, 100);
	DDX_Text(pDX, IDC_EDIT_MAX_ALARMNUM, m_maxcount);
	DDV_MinMaxInt(pDX, m_maxcount, 1, 100);

	DDX_Text(pDX, IDC_EDIT_FRONT_TS, m_e_front_ts);
	DDV_MinMaxFloat(pDX, m_e_front_ts, 0.1, 1.0);
	DDX_Text(pDX, IDC_EDIT_SIDE_TS, m_e_side_ts);
	DDV_MinMaxFloat(pDX, m_e_side_ts, 0.1, 1.0);
	DDX_Text(pDX, IDC_EDIT_MAX_CAPFACE, m_maxface);
	DDV_MinMaxInt(pDX, m_maxface, 32, 240);
	DDX_Text(pDX, IDC_EDIT_TIME_OUT, m_e_timeout);
	DDV_MinMaxInt(pDX, m_e_timeout, 0, 1800);
	DDX_Text(pDX, IDC_EDIT_SCALE, m_e_scale);
	DDV_MinMaxFloat(pDX, m_e_scale, 0.25, 1.0);
	DDX_Text(pDX, IDC_EDIT_VIDEO_TS, m_e_video_ts);
	DDV_MinMaxInt(pDX, m_e_video_ts, 10, 100);
}


BEGIN_MESSAGE_MAP(CDLGSetFace, CDialog)
	ON_BN_CLICKED(IDC_CHECK, OnCheck)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, &CDLGSetFace::OnOk)
END_MESSAGE_MAP()


// CDLGSetFace message handlers


BOOL CDLGSetFace::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here

	//��ʼ���б�
	InitList();

	m_b_ok.LoadBitmaps(IDB_OK_BUTTON,IDB_OK_BUTTON_MOVE,NULL,NULL);
	m_b_ok.SizeToContent();		//����ӦͼƬ��С

	m_b_cancel.LoadBitmaps(IDB_CANCEL_BUTTON,IDB_CANCEL_BUTTON_MOVE,NULL,NULL);
	m_b_cancel.SizeToContent();		//����ӦͼƬ��С


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
void CDLGSetFace::InitList(void)
{
	m_List.InsertColumn(0, _T("���") , LVCFMT_LEFT, 50);
	m_List.InsertColumn(1, _T("����"), LVCFMT_LEFT, 200);

	//����ѡ�� LVS_EX_CHECKBOXES
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);
	

	list<struct FACE_DB_ST> FaceDBList;

	MySqlIO.FACE_BlackDB_ReadAll(FaceDBList);


	int i,nItem;
	char str[32]={0};
	list<struct FACE_DB_ST>::iterator beglist;
	for(beglist=FaceDBList.begin();beglist!=FaceDBList.end();beglist++)
	{
		for(i=0;i<dbTotal;i++)
		{
			if(db_nid[i] == beglist->nid)
				break;
		}
		sprintf(str,"%d",beglist->nid);
		nItem = m_List.InsertItem(0,str);

		m_List.SetItemText(nItem,1,beglist->dbname);

		if(i!=dbTotal)
		{
			m_List.SetCheck(nItem,TRUE);
		}
	}
}

void CDLGSetFace::OnCheck() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	for(int i=0;i<m_List.GetItemCount();i++)
		m_List.SetCheck(i,m_check);

}

void CDLGSetFace::OnOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if(m_maxface<m_minface)
	{
		MessageBox("����������� ����С�� ��С��������");
		return ;
	}

	char str[32]={0};
	dbTotal=0;
	for(int i=0;i<m_List.GetItemCount();i++)
	{
		if(m_List.GetCheck(i))
		{
			m_List.GetItemText(i,0,str,32);
			db_nid[dbTotal]=atoi(str);
			dbTotal++;
		}
	}

	CDialog::OnOK();
}



void CDLGSetFace::OnPaint()
{

	CPaintDC dc(this); // device context for painting
	//������ͼ	
	CRect    rect;     
	GetClientRect(&rect);     

	//����Դ������λͼ     
	CBitmap    bitmap;     
	bitmap.LoadBitmap(IDB_FIND_BACK);    
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
//��̬�ı��ؼ� ͸��
HBRUSH CDLGSetFace::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	//��͸��
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_CAP)
	{
		// ����ɫ͸��
		pDC->SetBkMode(TRANSPARENT);

		// ���ر���ɫ�Ļ�ˢ
		return m_BgBrush;
	}
	
	//��͸��
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_ALARM)
	{
		// ����ɫ͸��
		pDC->SetBkMode(TRANSPARENT);

		// ���ر���ɫ�Ļ�ˢ
		return m_BgBrush;
	}
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

