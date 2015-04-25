// CDLGHistoryReport.cpp : implementation file
//

#include "stdafx.h"
#include "SmartVillage.h"
#include "DLGHistoryReport.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CYRSVMySQL MySqlIO;

/////////////////////////////////////////////////////////////////////////////
// DLGHistoryReport dialog


CDLGHistoryReport::CDLGHistoryReport(CWnd* pParent /*=NULL*/)
	: CDialog(CDLGHistoryReport::IDD, pParent)
{

	//{{AFX_DATA_INIT(CDLGHistoryReport)
	m_page = 1;
	m_user = _T("");
	m_CheckTime = FALSE;
	//}}AFX_DATA_INIT

	CTime nowtime=CTime::GetTickCount();
	m_StartMon=nowtime.GetTime();
	m_StartHour=nowtime.GetTime();

	CTime cstime(
		nowtime.GetYear(),
		nowtime.GetMonth(),
		nowtime.GetDay(),
		0,	0,	0);

	m_StartHour=cstime.GetTime();

	nowtime+=3600;
	m_EndMon=nowtime.GetTime();
	m_EndHour=nowtime.GetTime();
	
	ListTotal=0;
	ListNow=0;
}


void CDLGHistoryReport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDLGHistoryReport)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Text(pDX, IDC_EDIT_PAGE, m_page);
	DDX_Text(pDX, IDC_EDIT_USER, m_user);
	DDV_MaxChars(pDX, m_user, 32);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_STARTMON, m_StartMon);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_STARTHOUR, m_StartHour);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_ENDMON, m_EndMon);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_ENDHOUR, m_EndHour);
	DDX_Check(pDX, IDC_CHECK_TIME, m_CheckTime);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_BUTTON_SEARCH, m_search);
	DDX_Control(pDX, IDC_BUTTON_FIRST, m_first_button);
	DDX_Control(pDX, IDC_BUTTON_PREVIOUS, m_pre_button);
	DDX_Control(pDX, IDC_BUTTON_NEXT, m_next_button);
	DDX_Control(pDX, IDC_BUTTON_LAST, m_last_button);
	DDX_Control(pDX, IDC_BUTTON_JUMP, m_jump_button);
}


BEGIN_MESSAGE_MAP(CDLGHistoryReport, CDialog)
	//{{AFX_MSG_MAP(CDLGHistoryReport)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_FIRST, OnButtonFirst)
	ON_BN_CLICKED(IDC_BUTTON_PREVIOUS, OnButtonPrevious)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_LAST, OnButtonLast)
	ON_BN_CLICKED(IDC_BUTTON_JUMP, OnButtonJump)
	ON_BN_CLICKED(IDC_CHECK_TIME, OnCheckTime)
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDLGHistoryReport message handlers
BOOL CDLGHistoryReport::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_List.InsertColumn(0, _T("���") , LVCFMT_LEFT, 60);
	m_List.InsertColumn(1, _T("�û���" ), LVCFMT_LEFT, 100);
	m_List.InsertColumn(2, _T("ʱ��"), LVCFMT_LEFT, 140);
	m_List.InsertColumn(3, _T("��־��Ϣ"), LVCFMT_LEFT, 425);

	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);


	OnCheckTime();


	GetDlgItem(IDC_STATIC_INFO)->GetWindowRect(printf_Rect);
	ScreenToClient(printf_Rect);

	m_search.LoadBitmaps(IDB_FIND_BUTTON,IDB_FIND_BUTTON_MOVE,NULL,NULL);
	m_search.SizeToContent();		//����ӦͼƬ��С

	m_first_button.LoadBitmaps(IDB_FIRST_BUTTON,IDB_FIRST_BUTTON_MOVE,NULL,NULL);
	m_first_button.SizeToContent();		//����ӦͼƬ��С

	m_pre_button.LoadBitmaps(IDB_PRE_BUTTON,IDB_PRE_BUTTON_MOVE,NULL,NULL);
	m_pre_button.SizeToContent();		//����ӦͼƬ��С

	m_next_button.LoadBitmaps(IDB_NEXT_BUTTON,IDB_NEXT_BUTTON_MOVE,NULL,NULL);
	m_next_button.SizeToContent();		//����ӦͼƬ��С

	m_last_button.LoadBitmaps(IDB_LAST_BUTTON,IDB_LAST_BUTTON_MOVE,NULL,NULL);
	m_last_button.SizeToContent();		//����ӦͼƬ��С

	m_jump_button.LoadBitmaps(IDB_JUMP_BUTTON,IDB_JUMP_BUTTON_MOVE,NULL,NULL);
	m_jump_button.SizeToContent();		//����ӦͼƬ��С


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDLGHistoryReport::OnOK()
{
	// TODO: Add your control notification handler code here
}

void CDLGHistoryReport::DisplayerList(void)
{
	list_history_report.clear();
	m_List.DeleteAllItems();

	if(0==ListTotal)
	{
		GetDlgItem(IDC_STATIC_INFO)->SetWindowText("��0�� 1/1ҳ");
		InvalidateRect(printf_Rect, TRUE);
		return ;
	}

	unsigned long int si,ei;

	si=ListNow+1;
	if((ListNow+HISTORY_REPORT_PAGE_MAX_NUM) < ListTotal)
		ei=ListNow+HISTORY_REPORT_PAGE_MAX_NUM ;
	else
		ei=ListTotal;

	//��ѯ���ݿ�
	MySqlIO.LOG_ReadSystemLog(sqlstr,searchFlag,si,ei,list_history_report);

	int nItem;
	char str[128]={0};
	int i=0;

	list<struct HISTORY_REPORT_ST>::iterator beglist;

	for(beglist=list_history_report.begin();beglist!=list_history_report.end();beglist++)
	{
		sprintf(str,"%07d",ListNow+1+i);
		nItem = m_List.InsertItem(0,str);
		i++;

		m_List.SetItemText(nItem,1,beglist->user);

		sprintf(str,"%04d-%02d-%02d %02d:%02d:%02d",		
			beglist->year,
			beglist->mon,
			beglist->day,
			beglist->hour,
			beglist->min,
			beglist->sec);

		m_List.SetItemText(nItem,2,str);

		m_List.SetItemText(nItem,3,beglist->str);
	}

	if(ListTotal%HISTORY_REPORT_PAGE_MAX_NUM)
	{
		sprintf(str,"��%d�� %d/%dҳ ÿҳ%d��",
			ListTotal,
			ListNow/HISTORY_REPORT_PAGE_MAX_NUM+1,ListTotal/HISTORY_REPORT_PAGE_MAX_NUM+1,HISTORY_REPORT_PAGE_MAX_NUM);
	}
	else
	{
		sprintf(str,"��%d�� %d/%dҳ ÿҳ%d��",
			ListTotal,
			ListNow/HISTORY_REPORT_PAGE_MAX_NUM+1,ListTotal/HISTORY_REPORT_PAGE_MAX_NUM,HISTORY_REPORT_PAGE_MAX_NUM);
	}
	GetDlgItem(IDC_STATIC_INFO)->SetWindowText(str);
	InvalidateRect(printf_Rect, TRUE);
}

void CDLGHistoryReport::OnButtonSearch() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	char STime[32]={0};
	char ETime[32]={0};

	if(	m_StartMon.GetYear() <1900  || m_StartMon.GetYear() >2100 ||
		m_EndMon.GetYear()<1900  || m_EndMon.GetYear() >2100) 
	{
		MessageBox("ʱ�䷶Χ����С��1900�꣬������2100��",MESSAGEBOX_TITLE);
		return ;
	}
	sprintf(STime,"%04d%02d%02d%02d%02d%02d",		
		m_StartMon.GetYear(),
		m_StartMon.GetMonth(),
		m_StartMon.GetDay(),
		m_StartHour.GetHour(),
		m_StartHour.GetMinute(),
		m_StartHour.GetSecond());

	sprintf(ETime,"%04d%02d%02d%02d%02d%02d",		
		m_EndMon.GetYear(),
		m_EndMon.GetMonth(),
		m_EndMon.GetDay(),
		m_EndHour.GetHour(),
		m_EndHour.GetMinute(),
		m_EndHour.GetSecond());

	/////////��ȡ
	searchFlag = 0;

	if(!m_user.IsEmpty())
	{
		searchFlag |= 0x01;
	}
	if(m_CheckTime)
	{
		searchFlag |= 0x02;
	
		COleDateTime cstime(
			m_StartMon.GetYear(),
			m_StartMon.GetMonth(),
			m_StartMon.GetDay(),
			m_StartHour.GetHour(),
			m_StartHour.GetMinute(),
			m_StartHour.GetSecond());
		
		COleDateTime cetime(
			m_EndMon.GetYear(),
			m_EndMon.GetMonth(),
			m_EndMon.GetDay(),
			m_EndHour.GetHour(),
			m_EndHour.GetMinute(),
			m_EndHour.GetSecond());
		
		if(cstime>cetime)
		{
			MessageBox("��ʼʱ�� ���ô��� ����ʱ��");
			return ;
		}
	}

	ListTotal=0;
	ListTotal=MySqlIO.LOG_GetSystemLogNum(m_user.GetBuffer(0),STime,ETime,searchFlag,sqlstr);
	ListNow=0;

	DisplayerList();
}

void CDLGHistoryReport::OnButtonFirst() 
{
	// TODO: Add your control notification handler code here
	if(0==ListTotal)
		return ;

	ListNow=0;
	DisplayerList();
}

void CDLGHistoryReport::OnButtonPrevious() 
{
	// TODO: Add your control notification handler code here
	if(0==ListTotal)
		return ;

	if((ListNow-HISTORY_REPORT_PAGE_MAX_NUM) >= 0)
		ListNow-=HISTORY_REPORT_PAGE_MAX_NUM;

	DisplayerList();
}

void CDLGHistoryReport::OnButtonNext() 
{
	// TODO: Add your control notification handler code here
	if(0==ListTotal)
		return ;

	if((ListNow+HISTORY_REPORT_PAGE_MAX_NUM) < ListTotal)
		ListNow+=HISTORY_REPORT_PAGE_MAX_NUM;

	DisplayerList();
}

void CDLGHistoryReport::OnButtonLast() 
{
	// TODO: Add your control notification handler code here
	if(0==ListTotal)
		return ;

	while((ListNow+HISTORY_REPORT_PAGE_MAX_NUM) < ListTotal)
		ListNow+=HISTORY_REPORT_PAGE_MAX_NUM;

	DisplayerList();
}

void CDLGHistoryReport::OnButtonJump() 
{
	// TODO: Add your control notification handler code here
	if(0==ListTotal)
		return ;

	UpdateData(TRUE);

	if((m_page>=1)
		&& (m_page <= (ListTotal/HISTORY_REPORT_PAGE_MAX_NUM+1))
		)
	{
		ListNow=0;
		while(((ListNow+HISTORY_REPORT_PAGE_MAX_NUM) < ListTotal)
			&& ((ListNow+HISTORY_REPORT_PAGE_MAX_NUM) < (HISTORY_REPORT_PAGE_MAX_NUM*m_page))
			)
			ListNow+=HISTORY_REPORT_PAGE_MAX_NUM;

		DisplayerList();
	}
	else
		MessageBox("����ҳ�淶Χ",MESSAGEBOX_TITLE);
}


void CDLGHistoryReport::OnCheckTime() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_CheckTime)
	{
		GetDlgItem(IDC_DATETIMEPICKER_STARTMON)->EnableWindow(TRUE);
		GetDlgItem(IDC_DATETIMEPICKER_STARTHOUR)->EnableWindow(TRUE);
		GetDlgItem(IDC_DATETIMEPICKER_ENDMON)->EnableWindow(TRUE);
		GetDlgItem(IDC_DATETIMEPICKER_ENDHOUR)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_DATETIMEPICKER_STARTMON)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATETIMEPICKER_STARTHOUR)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATETIMEPICKER_ENDMON)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATETIMEPICKER_ENDHOUR)->EnableWindow(FALSE);
	}
}

void CDLGHistoryReport::OnPaint()
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
HBRUSH CDLGHistoryReport::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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