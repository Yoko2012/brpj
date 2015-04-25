// DLGAnalyseFlowrate.cpp : implementation file
//

#include "stdafx.h"
#include "SmartVillage.h"
#include "DLGAnalyseFlowrate.h"

#include "SmartVillageDlg.h"
extern CSmartVillageDlg *DlgMain;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CYRSVMySQL MySqlIO;

/////////////////////////////////////////////////////////////////////////////
// CDLGAnalyseFlowrate dialog


CDLGAnalyseFlowrate::CDLGAnalyseFlowrate(CWnd* pParent /*=NULL*/)
	: CDialog(CDLGAnalyseFlowrate::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDLGAnalyseFlowrate)
	m_ip = _T("");


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

	m_Day=nowtime.GetTime();

	nowtime+=3600;

	m_EndMon=nowtime.GetTime();
	m_EndHour=nowtime.GetTime();


}


void CDLGAnalyseFlowrate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDLGAnalyseFlowrate)
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Text(pDX, IDC_EDIT_IP, m_ip);
	DDV_MaxChars(pDX, m_ip, 32);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_STARTMON, m_StartMon);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_STARTHOUR, m_StartHour);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_ENDMON, m_EndMon);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_ENDHOUR, m_EndHour);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_DAY, m_Day);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDLGAnalyseFlowrate, CDialog)
	//{{AFX_MSG_MAP(CDLGAnalyseFlowrate)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH_ALL, OnButtonSearchAll)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH_SINGLE, OnButtonSearchSingle)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDLGAnalyseFlowrate message handlers
// CDLGBlackInOut message handlers
BOOL CDLGAnalyseFlowrate::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_List.InitProgressColumn(5,6);
	m_List.InitProgressStyle(PBS_SMOOTH);
	m_List.InitProgressStyleEx(WS_EX_STATICEDGE);
	m_List.InitProgressColor(RGB(0,0,128),RGB(255,255,255));

	m_List.InsertColumn(0,"���",LVCFMT_LEFT,60);
	m_List.InsertColumn(1,"����ͷ����",LVCFMT_LEFT,200);
	m_List.InsertColumn(2,"����ͷIP",LVCFMT_LEFT,110);
	m_List.InsertColumn(3,"��ʼʱ��",LVCFMT_LEFT,130);
	m_List.InsertColumn(4,"����ʱ��",LVCFMT_LEFT,130);
	m_List.InsertColumn(5,"ͳ������",LVCFMT_LEFT,60);
	m_List.InsertColumn(6,"ֱ��ͼ",LVCFMT_LEFT,160);

	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDLGAnalyseFlowrate::OnOK() 
{
	// TODO: Add extra validation here
}
 

void CDLGAnalyseFlowrate::OnButtonSearchAll() 
{

	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_List.DeleteAllItems();
	int nItem;
	char str[32]={0};

	unsigned long int total=0;
	unsigned long int max=100;

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

	for(int i=0;i<DlgMain->DlgTabVideo.DlgDeviceTree.iptotal;i++)
	{	
		sprintf(str,"%05d",i);
		nItem = m_List.InsertItem(0,str);
	
		m_List.SetItemText(nItem,1,	DlgMain->DlgTabVideo.DlgDeviceTree.iplist[i].name);
		m_List.SetItemText(nItem,2,	DlgMain->DlgTabVideo.DlgDeviceTree.iplist[i].ip);
///////////////////////
		sprintf(str,"%04d-%02d-%02d %02d:%02d:%02d",
			m_StartMon.GetYear(),
			m_StartMon.GetMonth(),
			m_StartMon.GetDay(),
			m_StartHour.GetHour(),
			m_StartHour.GetMinute(),
			m_StartHour.GetSecond());

		m_List.SetItemText(nItem,3,	str);

		sprintf(str,"%04d-%02d-%02d %02d:%02d:%02d",		
			m_EndMon.GetYear(),
			m_EndMon.GetMonth(),
			m_EndMon.GetDay(),
			m_EndHour.GetHour(),
			m_EndHour.GetMinute(),
			m_EndHour.GetSecond());

		m_List.SetItemText(nItem,4,	str);
//////////////////////////////
		total=GetCount(DlgMain->DlgTabVideo.DlgDeviceTree.iplist[i].ncamera,STime,ETime);
		sprintf(str,"%d",total);
		m_List.SetItemText(nItem,5,	str);
		//Ѱ�����ֵ
		if(total > max)
			max=total;
	}
	//�������ֵ
	m_List.InitProgressMax(max);
}

void CDLGAnalyseFlowrate::OnButtonSearchSingle() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_List.DeleteAllItems();

	int i,j,k;
	//Ѱ��IP
	CString ipname;

	//�ҵ�IP
	int nItem;
	char str[32];

	char STime[32]={0};
	char ETime[32]={0};
	unsigned long int max=100;
	unsigned long int total;

	ipname.Empty();

	k=0;
	for(i=0;i<DlgMain->DlgTabVideo.DlgDeviceTree.iptotal;i++)
	{	
		if(	DlgMain->DlgTabVideo.DlgDeviceTree.iplist[i].ip == m_ip)
		{
			ipname=DlgMain->DlgTabVideo.DlgDeviceTree.iplist[i].name;
		
			for(j=0;j<24;j++)
			{	
				sprintf(str,"%04d",k);
				k++;
				nItem = m_List.InsertItem(0,str);
				
				m_List.SetItemText(nItem,1,	ipname.GetBuffer(0));
				m_List.SetItemText(nItem,2,	m_ip.GetBuffer(0));
				/////////////////////////////
				sprintf(str,"%04d-%02d-%02d %02d:00:00",
					m_Day.GetYear(),
					m_Day.GetMonth(),
					m_Day.GetDay(),
					j);
				
				m_List.SetItemText(nItem,3,	str);
				
				sprintf(str,"%04d-%02d-%02d %02d:59:59",		
					m_Day.GetYear(),
					m_Day.GetMonth(),
					m_Day.GetDay(),
					j);
				
				m_List.SetItemText(nItem,4,	str);
				/////////////////////////////
				sprintf(STime,"%04d%02d%02d%02d0000",		
					m_Day.GetYear(),
					m_Day.GetMonth(),
					m_Day.GetDay(),
					j);
				
				sprintf(ETime,"%04d%02d%02d%02d5959",		
					m_Day.GetYear(),
					m_Day.GetMonth(),
					m_Day.GetDay(),
					j);
				
				total=GetCount(DlgMain->DlgTabVideo.DlgDeviceTree.iplist[i].ncamera,STime,ETime);
				
				sprintf(str,"%d",total);
				m_List.SetItemText(nItem,5,	str);
				//Ѱ�����ֵ
				if(total > max)
					max=total;
			}

		}
	}
	if(ipname.IsEmpty())
	{
		MessageBox("δ�ҵ���IP����Ӧ������ͷ",MESSAGEBOX_TITLE);
		return ;
	}

	//�������ֵ
	m_List.InitProgressMax(max);
}

unsigned long int CDLGAnalyseFlowrate::GetCount(unsigned long int camid,char *stime,char *etime)
{

#if ALLTAB_DETECT_CAR_MODE
	return MySqlIO.CAR_MatchResult_Count(camid,stime,etime);
#else
	return MySqlIO.ELECAR_MatchResult_Count(camid,stime,etime);
#endif

}