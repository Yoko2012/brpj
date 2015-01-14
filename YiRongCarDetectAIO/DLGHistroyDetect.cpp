// DLGHistroyDetect.cpp : implementation file
//

#include "stdafx.h"
#include "yirongcardetectaio.h"
#include "DLGHistroyDetect.h"

#include "DLGSetSystem.h"
extern CDLGSetSystem DlgSetSystem;

#include "URLencode.h"
#include "SignalDownload.h"

#include "DLGpictureView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern IO OracleIO;

/////////////////////////////////////////////////////////////////////////////
// CDLGHistroyDetect dialog


CDLGHistroyDetect::CDLGHistroyDetect(CWnd* pParent /*=NULL*/)
	: CDialog(CDLGHistroyDetect::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDLGHistroyDetect)
	m_ip = _T("");
	m_name = _T("");
	m_page = 1;
	m_plate = _T("");
	m_platetype = 0;
	m_platecolor = 0;
	m_direction = 0;
	m_carcolor = 0;
	m_CheckTime=FALSE;
	//}}AFX_DATA_INIT
	flag=0;

	CTime nowtime=CTime::GetTickCount();
	m_StartMon=nowtime;
	m_StartHour=nowtime;

	CTime cstime(
		nowtime.GetYear(),
		nowtime.GetMonth(),
		nowtime.GetDay(),
		0,	0,	0);

	m_StartHour=cstime;

	nowtime+=3600;
	m_EndMon=nowtime;
	m_EndHour=nowtime;

	ListTotal=0;
	ListNow=0;
}


void CDLGHistroyDetect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDLGHistroyDetect)
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Text(pDX, IDC_EDIT_IP, m_ip);
	DDV_MaxChars(pDX, m_ip, 32);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
	DDV_MaxChars(pDX, m_name, 260);
	DDX_Text(pDX, IDC_EDIT_PAGE, m_page);
	DDX_Text(pDX, IDC_EDIT_PLATE, m_plate);
	DDV_MaxChars(pDX, m_plate, 32);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_STARTMON, m_StartMon);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_STARTHOUR, m_StartHour);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_ENDMON, m_EndMon);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_ENDHOUR, m_EndHour);
	DDX_Check(pDX, IDC_CHECK_TIME, m_CheckTime);
	DDX_CBIndex(pDX, IDC_COMBO_PLATETYPE, m_platetype);
	DDX_CBIndex(pDX, IDC_COMBO_PLATECOLOR, m_platecolor);
	DDX_CBIndex(pDX, IDC_COMBO_DIRECTION, m_direction);
	DDX_CBIndex(pDX, IDC_COMBO_CARCOLOR, m_carcolor);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_BUTTON_SEARCH, m_search);
	DDX_Control(pDX, IDC_BUTTON_FIRST, m_first_button);
	DDX_Control(pDX, IDC_BUTTON_PREVIOUS, m_pre_button);
	DDX_Control(pDX, IDC_BUTTON_NEXT, m_next_button);
	DDX_Control(pDX, IDC_BUTTON_LAST, m_last_button);
	DDX_Control(pDX, IDC_BUTTON_JUMP, m_jump_button);
}


BEGIN_MESSAGE_MAP(CDLGHistroyDetect, CDialog)
	//{{AFX_MSG_MAP(CDLGHistroyDetect)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_FIRST, OnButtonFirst)
	ON_BN_CLICKED(IDC_BUTTON_PREVIOUS, OnButtonPrevious)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_LAST, OnButtonLast)
	ON_BN_CLICKED(IDC_BUTTON_JUMP, OnButtonJump)
	ON_NOTIFY(LVN_ITEMACTIVATE, IDC_LIST,OnLvnItemActivateList)
	ON_BN_CLICKED(IDC_CHECK_TIME, OnCheckTime)
	//}}AFX_MSG_MAP
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDLGHistroyDetect message handlers
BOOL CDLGHistroyDetect::OnInitDialog() 
{
	CDialog::OnInitDialog();


#if ALLTAB_DETECT_CAR_MODE
	m_List.InsertColumn(0, _T("���") , LVCFMT_LEFT, 60);
	m_List.InsertColumn(1, _T("ʱ��" ), LVCFMT_LEFT, 140);
	m_List.InsertColumn(2, _T("����ͷ����" ), LVCFMT_LEFT, 180);
	m_List.InsertColumn(3, _T("IP��ַ"), LVCFMT_LEFT, 100);
	m_List.InsertColumn(4, _T("���ƺ�"), LVCFMT_LEFT, 70);
	m_List.InsertColumn(5, _T("���Ŷ�"), LVCFMT_LEFT, 50);
	m_List.InsertColumn(6, _T("��ʻ����"), LVCFMT_LEFT, 70);
	m_List.InsertColumn(7, _T("������ɫ"), LVCFMT_LEFT, 70);
	m_List.InsertColumn(8, _T("��������"), LVCFMT_LEFT, 100);
	m_List.InsertColumn(9, _T("������ɫ"), LVCFMT_LEFT, 60);
	m_List.InsertColumn(10, _T("ͼƬ·��"), LVCFMT_LEFT, 0);
	m_List.InsertColumn(11, _T("nid"), LVCFMT_LEFT, 0);
	m_List.InsertColumn(12, _T("ͼƬ��С"), LVCFMT_LEFT, 0);
	
	GetDlgItem(IDC_COMBO_PLATETYPE)->ShowWindow(TRUE);
	GetDlgItem(IDC_COMBO_PLATECOLOR)->ShowWindow(TRUE);
	GetDlgItem(IDC_COMBO_CARCOLOR)->ShowWindow(TRUE);

#else
	m_List.InsertColumn(0, _T("���") , LVCFMT_LEFT, 60);
	m_List.InsertColumn(1, _T("ʱ��" ), LVCFMT_LEFT, 140);
	m_List.InsertColumn(2, _T("����ͷ����" ), LVCFMT_LEFT, 240);
	m_List.InsertColumn(3, _T("IP��ַ"), LVCFMT_LEFT, 100);
	m_List.InsertColumn(4, _T("���ƺ�"), LVCFMT_LEFT, 70);
	m_List.InsertColumn(5, _T("���Ŷ�"), LVCFMT_LEFT, 50);
	m_List.InsertColumn(6, _T("��ʻ����"), LVCFMT_LEFT, 70);
	m_List.InsertColumn(7, _T("������ɫ"), LVCFMT_LEFT, 70);
	m_List.InsertColumn(8, _T("ͼƬ·��"), LVCFMT_LEFT, 0);
	m_List.InsertColumn(9, _T("nid"), LVCFMT_LEFT, 0);
	m_List.InsertColumn(10, _T("ͼƬ��С"), LVCFMT_LEFT, 0);

	//���γ������� ������ɫ ������ɫ
	GetDlgItem(IDC_COMBO_PLATETYPE)->ShowWindow(FALSE);
	GetDlgItem(IDC_COMBO_PLATECOLOR)->ShowWindow(FALSE);
	GetDlgItem(IDC_COMBO_CARCOLOR)->ShowWindow(FALSE);
#endif

	//����Ԥ������ٵ�����
	switch(flag)
	{
	case HISTORY_DETECT_FLAG_CAR :
		SetWindowText("��ʷʶ���ѯ");
		break;
	case HISTORY_DETECT_FLAG_ALARM :
		SetWindowText("��ʷ������ѯ");
#if ALLTAB_DETECT_CAR_MODE

	m_List.InsertColumn(13, _T("ʧ������"), LVCFMT_LEFT, 70);
	m_List.InsertColumn(14, _T("Ʒ��"), LVCFMT_LEFT, 70);
	m_List.InsertColumn(15, _T("ʧ���绰"), LVCFMT_LEFT, 100);
#else

	m_List.InsertColumn(11, _T("ʧ������"), LVCFMT_LEFT, 70);
	m_List.InsertColumn(12, _T("Ʒ��"), LVCFMT_LEFT, 70);
	m_List.InsertColumn(13, _T("ʧ���绰"), LVCFMT_LEFT, 100);

#endif
		break;
	default:
		MessageBox("BOOL CDLGHistroyDetect::OnInitDialog error",MESSAGEBOX_TITLE);
		return true;
	}


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
void CDLGHistroyDetect::OnOK()
{
	// TODO: Add your control notification handler code here
}

void CDLGHistroyDetect::OnButtonSearch() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

/*
	CTime	StartT(m_TimeStartMon.GetYear(),m_TimeStartMon.GetMonth(),m_TimeStartMon.GetDay(),	\
		m_TimeStartHour.GetHour(),m_TimeStartHour.GetMinute(),m_TimeStartHour.GetSecond());

	CTime	EndT(m_TimeEndMon.GetYear(),m_TimeEndMon.GetMonth(),m_TimeEndMon.GetDay(),	\
		m_TimeEndHour.GetHour(),m_TimeEndHour.GetMinute(),m_TimeEndHour.GetSecond());
*/
	char STime[32]={0};
	char ETime[32]={0};

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

	CString directionstr="";
	CString platecolorstr="";
	CString platetypestr="";
	CString carcolorstr="";

	if(!m_name.IsEmpty())
	{
		searchFlag |= 0x01;
	}
	if(!m_ip.IsEmpty())
	{
		searchFlag |= 0x02;
	}
	if(!m_plate.IsEmpty())
	{
		searchFlag |= 0x04;
	}
	if(m_CheckTime)
	{
		searchFlag |= 0x08;

		CTime cstime(
			m_StartMon.GetYear(),
			m_StartMon.GetMonth(),
			m_StartMon.GetDay(),
			m_StartHour.GetHour(),
			m_StartHour.GetMinute(),
			m_StartHour.GetSecond());
		
		CTime cetime(
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
	if(m_direction >0)
	{
		searchFlag |= 0x10;
		((CComboBox *)GetDlgItem(IDC_COMBO_DIRECTION))->GetLBText(m_direction,directionstr);
	}

#if ALLTAB_DETECT_CAR_MODE
//����
	if(m_platecolor >0)
	{
		searchFlag |= 0x20;
		((CComboBox *)GetDlgItem(IDC_COMBO_PLATECOLOR))->GetLBText(m_platecolor,platecolorstr);
	}
	if(m_platetype >0)
	{
		searchFlag |= 0x40;
		((CComboBox *)GetDlgItem(IDC_COMBO_PLATETYPE))->GetLBText(m_platetype,platetypestr);
	}
	if(m_carcolor >0)
	{
		searchFlag |= 0x80;
		((CComboBox *)GetDlgItem(IDC_COMBO_CARCOLOR))->GetLBText(m_carcolor,carcolorstr);	
	}

	ListTotal=0;

	switch(flag)
	{
	case HISTORY_DETECT_FLAG_CAR :
		ListTotal=OracleIO.CAR_MatchResult_GetNum(
			m_name.GetBuffer(0),
			m_ip.GetBuffer(0),
			m_plate.GetBuffer(0),
			STime,
			ETime,
			directionstr.GetBuffer(0),
			platecolorstr.GetBuffer(0),
			platetypestr.GetBuffer(0),
			carcolorstr.GetBuffer(0),
			searchFlag,
			SqlStr);
		break;
	case HISTORY_DETECT_FLAG_ALARM :
		ListTotal=OracleIO.CAR_AlarmResult_GetNum(
			m_name.GetBuffer(0),
			m_ip.GetBuffer(0),
			m_plate.GetBuffer(0),
			STime,
			ETime,
			directionstr.GetBuffer(0),
			platecolorstr.GetBuffer(0),
			platetypestr.GetBuffer(0),
			carcolorstr.GetBuffer(0),
			searchFlag,
			SqlStr);
		break;
	default:
		MessageBox("CDLGHistroyDetect::OnButtonSearch A error",MESSAGEBOX_TITLE);
		return ;
	}

#else
//�綯��
	ListTotal=0;

	switch(flag)
	{
	case HISTORY_DETECT_FLAG_CAR :
		ListTotal=OracleIO.ELECAR_MatchResult_GetNum(		
			m_name.GetBuffer(0),
			m_ip.GetBuffer(0),
			m_plate.GetBuffer(0),
			STime,
			ETime,
			directionstr.GetBuffer(0),
			searchFlag,
			SqlStr);
		break;
	case HISTORY_DETECT_FLAG_ALARM :
		ListTotal=OracleIO.ELECAR_AlarmResult_GetNum(
			m_name.GetBuffer(0),
			m_ip.GetBuffer(0),
			m_plate.GetBuffer(0),
			STime,
			ETime,
			directionstr.GetBuffer(0),
			searchFlag,
			SqlStr);
		break;
	default:
		MessageBox("CDLGHistroyDetect::OnButtonSearch B error",MESSAGEBOX_TITLE);
		return ;
	}

#endif
	ListNow=0;

	DisplayerList();
}

void CDLGHistroyDetect::DisplayerList(void)
{
	list_history_detect.clear();
	m_List.DeleteAllItems();
	

	if(0==ListTotal)
	{
		GetDlgItem(IDC_STATIC_INFO)->SetWindowText("��0�� 1/1ҳ");
		InvalidateRect(printf_Rect, TRUE);
		return ;
	}

	unsigned long int si,ei;

	si=ListNow+1;
	if((ListNow+HISTORY_DETECT_PAGE_MAX_NUM) < ListTotal)
		ei=ListNow+HISTORY_DETECT_PAGE_MAX_NUM ;
	else
		ei=ListTotal;

	//��ѯ���ݿ�
#if ALLTAB_DETECT_CAR_MODE
//����
	switch(flag)
	{
	case HISTORY_DETECT_FLAG_CAR :
		OracleIO.CAR_MatchResult_Read(SqlStr,searchFlag,si,ei,list_history_detect);
		break;
	case HISTORY_DETECT_FLAG_ALARM :
		OracleIO.CAR_AlarmResult_Read(SqlStr,searchFlag,si,ei,list_history_detect);
		break;
	default:
		MessageBox("CDLGHistroyDetect::DisplayerList A error",MESSAGEBOX_TITLE);
		return ;
	}

#else
//�綯��
	switch(flag)
	{
	case HISTORY_DETECT_FLAG_CAR :
		OracleIO.ELECAR_MatchResult_Read(SqlStr,searchFlag,si,ei,list_history_detect);
		break;
	case HISTORY_DETECT_FLAG_ALARM :
		OracleIO.ELECAR_AlarmResult_Read(SqlStr,searchFlag,si,ei,list_history_detect);
		break;
	default:
		MessageBox("CDLGHistroyDetect::DisplayerList B error",MESSAGEBOX_TITLE);
		return ;
	}

#endif

	int nItem;
	char str[128];
	int i=0;

	list<struct HISTORY_DETECT_ST>::iterator beglist;
	
	struct BLACK_DATA_ST blackdata;

	for(beglist=list_history_detect.begin();beglist!=list_history_detect.end();beglist++)
	{
		sprintf(str,"%07d",ListNow+1+i);
		nItem = m_List.InsertItem(0,str);
		i++;

		sprintf(str,"%04d-%02d-%02d %02d:%02d:%02d",		
			beglist->year,
			beglist->mon,
			beglist->day,
			beglist->hour,
			beglist->min,
			beglist->sec);
		m_List.SetItemText(nItem,1,str);

		m_List.SetItemText(nItem,2,beglist->name);
		m_List.SetItemText(nItem,3,beglist->ip);
		m_List.SetItemText(nItem,4,beglist->plate);
	
		sprintf(str,"%d",beglist->reliability);
		m_List.SetItemText(nItem,5,str);

		m_List.SetItemText(nItem,6,beglist->direction);

#if ALLTAB_DETECT_CAR_MODE
//����
		m_List.SetItemText(nItem,7,beglist->platecolor);
		m_List.SetItemText(nItem,8,beglist->platetype);
		m_List.SetItemText(nItem,9,beglist->carcolor);
		m_List.SetItemText(nItem,10,beglist->path);
	
		sprintf(str,"%d",beglist->nid);
		m_List.SetItemText(nItem,11,str);

		sprintf(str,"%d",beglist->picsize);
		m_List.SetItemText(nItem,12,str);

	if( HISTORY_DETECT_FLAG_ALARM ==flag)
	{
		if(OracleIO.CAR_BlackTable_ReadOneWithNid(beglist->blackid,blackdata))
		{
				m_List.SetItemText(nItem,13,blackdata.name);
				m_List.SetItemText(nItem,14,blackdata.brand);
				m_List.SetItemText(nItem,15,blackdata.Phone);
		}
	}
#else
//�綯��
		m_List.SetItemText(nItem,7,beglist->platecolor);
		m_List.SetItemText(nItem,8,beglist->path);
	
		sprintf(str,"%d",beglist->nid);
		m_List.SetItemText(nItem,9,str);

		sprintf(str,"%d",beglist->picsize);
		m_List.SetItemText(nItem,10,str);

		if( HISTORY_DETECT_FLAG_ALARM ==flag)
		{
			if(OracleIO.ELECAR_BlackTable_ReadOneWithNid(beglist->blackid,blackdata))
			{
				m_List.SetItemText(nItem,11,blackdata.name);
				m_List.SetItemText(nItem,12,blackdata.brand);
				m_List.SetItemText(nItem,13,blackdata.Phone);
			}
		}
#endif

	}

	if(ListTotal%HISTORY_DETECT_PAGE_MAX_NUM)
	{
		sprintf(str,"��%d�� %d/%dҳ",
			ListTotal,
			ListNow/HISTORY_DETECT_PAGE_MAX_NUM+1,ListTotal/HISTORY_DETECT_PAGE_MAX_NUM+1);
	}
	else
	{
		sprintf(str,"��%d�� %d/%dҳ",
			ListTotal,
			ListNow/HISTORY_DETECT_PAGE_MAX_NUM+1,ListTotal/HISTORY_DETECT_PAGE_MAX_NUM);
	}
	GetDlgItem(IDC_STATIC_INFO)->SetWindowText(str);
	InvalidateRect(printf_Rect, TRUE);
}

void CDLGHistroyDetect::OnButtonFirst() 
{
	// TODO: Add your control notification handler code here
	if(0==ListTotal)
		return ;

	ListNow=0;
	DisplayerList();
}

void CDLGHistroyDetect::OnButtonPrevious() 
{
	// TODO: Add your control notification handler code here
	if(0==ListTotal)
		return ;

	if((ListNow-HISTORY_DETECT_PAGE_MAX_NUM) >= 0)
		ListNow-=HISTORY_DETECT_PAGE_MAX_NUM;

	DisplayerList();
}

void CDLGHistroyDetect::OnButtonNext() 
{
	// TODO: Add your control notification handler code here
	if(0==ListTotal)
		return ;

	if((ListNow+HISTORY_DETECT_PAGE_MAX_NUM) < ListTotal)
		ListNow+=HISTORY_DETECT_PAGE_MAX_NUM;

	DisplayerList();
}

void CDLGHistroyDetect::OnButtonLast() 
{
	// TODO: Add your control notification handler code here
	if(0==ListTotal)
		return ;

	while((ListNow+HISTORY_DETECT_PAGE_MAX_NUM) < ListTotal)
		ListNow+=HISTORY_DETECT_PAGE_MAX_NUM;

	DisplayerList();
}

void CDLGHistroyDetect::OnButtonJump() 
{
	// TODO: Add your control notification handler code here
	if(0==ListTotal)
		return ;

	UpdateData(TRUE);

	if((m_page>=1)
		&& (m_page <= (ListTotal/HISTORY_DETECT_PAGE_MAX_NUM+1))
		)
	{
		ListNow=0;
		while(((ListNow+HISTORY_DETECT_PAGE_MAX_NUM) < ListTotal)
			&& ((ListNow+HISTORY_DETECT_PAGE_MAX_NUM) < (HISTORY_DETECT_PAGE_MAX_NUM*m_page))
			)
			ListNow+=HISTORY_DETECT_PAGE_MAX_NUM;

		DisplayerList();
	}
	else
		MessageBox("����ҳ�淶Χ",MESSAGEBOX_TITLE);

}

void CDLGHistroyDetect::OnLvnItemActivateList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	char str[ZOG_MAX_PATH_STR];


#if OPEN_TOMCAT_MODE 

	DisplayTomcatPic(pNMIA->iItem);
#else

	//����
	if(DlgSetSystem.m_check_savenet)
	{
		DisplayNetPic(pNMIA->iItem);
	}
	else
	{
		//����
#if ALLTAB_DETECT_CAR_MODE
		//����
		m_List.GetItemText(pNMIA->iItem,10,str,260);
#else
		//�綯��
		m_List.GetItemText(pNMIA->iItem,8,str,260);
#endif
		//����ģʽ
		if(0==strcmp(str,"null"))
			DisplayNetPic(pNMIA->iItem);
		else
		{
			//ShellExecute(this->m_hWnd,NULL,str,NULL,NULL,SW_NORMAL);

			char str2[ZOG_MAX_PATH_STR];

			CDLGpictureView dlgPicView;
			//����ͷ����
			m_List.GetItemText(pNMIA->iItem,2,str2,ZOG_MAX_PATH_STR);

			dlgPicView.Titlestr=str2;

			char *p=strrchr(str,'\\');
			if(p!=NULL)
				p++;
			else
				return ;

			dlgPicView.Titlestr+=p;

			dlgPicView.srcfile=str;
			dlgPicView.DoModal();
		}
	}
#endif
	*pResult = 0;
}

void CDLGHistroyDetect::DisplayNetPic(int iItem)
{
	char str[ZOG_MAX_PATH_STR];
	
	unsigned long int nid;
	unsigned long int size;
	bool tempget;
	
	unsigned char *data=NULL;
	
#if ALLTAB_DETECT_CAR_MODE
	//����
	m_List.GetItemText(iItem,11,str,260);
#else
	//�綯��
	m_List.GetItemText(iItem,9,str,260);
#endif

	sscanf(str,"%d",&nid);
	
#if ALLTAB_DETECT_CAR_MODE
	//����
	m_List.GetItemText(iItem,12,str,260);
#else
	//�綯��
	m_List.GetItemText(iItem,10,str,260);
#endif

	sscanf(str,"%d",&size);
	//��ȡ���� ���浽��ʱ�ļ�
	data=(unsigned char *)calloc(size,sizeof(unsigned char));
	
	switch(flag)
	{
	case HISTORY_DETECT_FLAG_CAR :
#if ALLTAB_DETECT_CAR_MODE
		//����
		tempget=OracleIO.CAR_MatchResult_GetPicture(nid,data);
#else
		//�綯��
		tempget=OracleIO.ELECAR_MatchResult_GetPicture(nid,data);
#endif
		break;
	case HISTORY_DETECT_FLAG_ALARM :
#if ALLTAB_DETECT_CAR_MODE
		//����
		tempget=OracleIO.CAR_AlarmResult_GetPicture(nid,data);
#else
		//�綯��
		tempget=OracleIO.ELECAR_AlarmResult_GetPicture(nid,data);
#endif
		break;
	default:
		MessageBox("BOOL CDLGHistroyDetect::DisplayNetPic error",MESSAGEBOX_TITLE);
		free(data);
		return ;
	}
	
	sprintf(str,"%s\\yrcdtempResultpic.jpg",DlgSetSystem.m_path_detect);
	
	if(tempget)
	{
		FILE *fp=NULL;
		
		fp=fopen(str,"wb");
		if(fp)
		{
			fwrite(data,size,1,fp);
			fclose(fp);
			//������
			ShellExecute(this->m_hWnd,NULL,str,NULL,NULL,SW_NORMAL);
		}
	}
	
	free(data);
	data=NULL;
	
}

//��ҪNET�б� ΪNID
void CDLGHistroyDetect::DisplayTomcatPic(int iItem)
{
	char url[ZOG_MAX_PATH_STR];
	char url2[ZOG_MAX_PATH_STR*3];
	char str[ZOG_MAX_PATH_STR];
	char fail[1024];

#if ALLTAB_DETECT_CAR_MODE
	//����
	m_List.GetItemText(iItem,10,url,ZOG_MAX_PATH_STR);
#else
	//�綯��
	m_List.GetItemText(iItem,8,url,ZOG_MAX_PATH_STR);
#endif

	sprintf(str,"%s\\yrcdtempResultListpic.jpg",DlgSetSystem.m_path_detect);

	SignalDownload sd;
	sd.InitData();

	EncodeURI(url,url2,ZOG_MAX_PATH_STR*3);

	if(false == sd.HTTPDownload(url2,str,fail,10,0))
	{
		sd.DestroyData();
		return ;
	}

	sd.DestroyData();
	//������
	//ShellExecute(this->m_hWnd,NULL,str,NULL,NULL,SW_NORMAL);

	char str2[ZOG_MAX_PATH_STR];

	CDLGpictureView dlgPicView;
	//����ͷ����
	m_List.GetItemText(iItem,2,str2,ZOG_MAX_PATH_STR);

	dlgPicView.Titlestr=str2;

	char *p=strrchr(url,'/');
	if(p!=NULL)
		p++;
	else
		return ;

	dlgPicView.Titlestr+=p;

	dlgPicView.srcfile=str;
	dlgPicView.DoModal();

}


void CDLGHistroyDetect::OnCheckTime() 
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

void CDLGHistroyDetect::OnPaint()
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
HBRUSH CDLGHistroyDetect::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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