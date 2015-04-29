// DLGTabVideo.cpp : implementation file
//

#include "stdafx.h"
#include "SmartVillage.h"
#include "DLGTabVideo.h"
#include "SmartVillageDlg.h"
#include "DLGWarnning.h"
#include "DLGLogin.h"
extern CDLGLogin DlgLogin;
////////////////////////////////////////

#include "DLGHistoryVideo.h" //�������ı������DEBUG����
#include "DLGHistoryCarDetect.h"
#include "DLGSetUser.h"
#include "DLGSetBlack.h"
#include "DLGHistoryReport.h"
#include "DLGSetPTZ.h"
#include "DLGSetRecord.h"
#include "DLGAnalyseFlowrate.h"

#include "DLGhelp.h"

////////////////////////////////////////
#if	ALLTAB_DETECT_CAR_MODE
#include "DLGSetCar.h"
#else
#include "DLGSetElecar.h"
#endif


////////////////////////////////////////





#include "DLGSetSystem.h"
extern CDLGSetSystem DlgSetSystem;

////////////////lynn/////////////////
extern CYRSVMySQL MySqlIO;
////////////////lynn/////////////////


#include "DLGpictureView.h"

extern CSmartVillageDlg *DlgMain;
////////////////lynn/////////////////

// CDLGTabVideo dialog

IMPLEMENT_DYNAMIC(CDLGTabVideo, CDialog)

CDLGTabVideo::CDLGTabVideo(CWnd* pParent /*=NULL*/)
	: CDialog(CDLGTabVideo::IDD, pParent)
{

}

CDLGTabVideo::~CDLGTabVideo()
{
}

void CDLGTabVideo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CAR, m_ListCar);

}


BEGIN_MESSAGE_MAP(CDLGTabVideo, CDialog)
	ON_BN_CLICKED(IDOK, &CDLGTabVideo::OnOk)
	ON_BN_CLICKED(IDCANCEL, &CDLGTabVideo::OnCancel)
	ON_WM_PAINT()
	ON_NOTIFY(LVN_ITEMACTIVATE, IDC_LIST_CAR,OnLvnItemActivateList)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_CAR, OnNMCustomdrawList)
	ON_NOTIFY(SPN_MAXMINPOS, IDC_SPLITTER, OnMaxMinInfo)
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()

BOOL CDLGTabVideo::OnInitDialog()
{
	CDialog::OnInitDialog();


	DlgScreen.Create(IDD_SCREEN,this);
	DlgScreen.ShowWindow(SW_SHOW);

	DlgPictureFaceCap.hideflag=false;
	DlgPictureFaceCap.TitleDrawFlag=true;
	DlgPictureFaceCap.TitleResDef=IDB_FACE_CAP_TITLE;
	DlgPictureFaceCap.Create(IDD_PICTURE_FACE,this);
	DlgPictureFaceCap.ShowWindow(SW_SHOW);

	DlgPictureFaceAlarm.hideflag=true;
	DlgPictureFaceAlarm.TitleDrawFlag=true;
	DlgPictureFaceAlarm.TitleResDef=IDB_FACE_ALARM_TITLE;
	DlgPictureFaceAlarm.Create(IDD_PICTURE_FACE,this);
	DlgPictureFaceAlarm.ShowWindow(SW_SHOW);

	TabMainInit();

	//�б�
	ListMainInit();
#if OPEN_RECORD
	//��ʼ����ʱ¼����Ϣ
	DlgSetRecord.InitList();
#endif
	////////////////////////////
	//�ָ���
	initSplitter();
	//�������
	AutoSize();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDLGTabVideo::AutoSize()
{
	CRect rc(0, 0, 0, 0);
	GetClientRect(&m_clientRect);
	//	GetParent()->GetClientRect(&rc);
	//	((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
	//	MoveWindow(rc);


	//�л������=LOGOͼƬ�Ŀ��
	int tab_width=220;
	//LOGOͼƬ�ĸ߶�
	//int button_top=130;
	//int button_width=192;
	//tab�߶�
	//int tab_top=163;

	//LOGOͼƬ�ĸ߶�
	int button_top=0;
	int button_width=192;
	//tab�߶�
	int tree_top=0;

	//�б�ĸ߶�
	int list_height=180;

	//FACE�Ŀ��
	int face_width=230;
	int face_height=m_clientRect.Height()*3.0/5.0;

	//����߾�
	int distance=5;



	//�豸��
	CRect tree_Rect;
	tree_Rect.top = m_clientRect.top+tree_top;
	tree_Rect.bottom = m_clientRect.bottom-distance;
	tree_Rect.left = m_clientRect.left;
	tree_Rect.right = m_clientRect.left+tab_width;
	//���� ��ʽ=�ص����߿�=������С
	//	m_TabMain.MoveWindow(tab_Rect);

	DlgDeviceTree.MoveWindow(tree_Rect);

	//�б�
	CRect list_Rect;
	list_Rect.top = m_clientRect.bottom-distance-list_height/* + 5*/;
	list_Rect.bottom = m_clientRect.bottom-distance/* - 10*/;
	list_Rect.left = tree_Rect.right+distance/* + 10*/;
	list_Rect.right = m_clientRect.right-distance-face_width;
	//���� ��ʽ=�ص����߿�=������С
	m_ListCar.MoveWindow(list_Rect);

	//����
	CRect screen_Rect;
	screen_Rect.top = m_clientRect.top/* + 5*/;
	screen_Rect.bottom = list_Rect.top -distance/* - 10*/;
	screen_Rect.left = tree_Rect.right +distance/* + 10*/;
	screen_Rect.right = list_Rect.right;
	//���� ��ʽ=�ص����߿�=������С
	DlgScreen.MoveWindow(screen_Rect);


	DlgDeviceTree.AutoSize();
	DlgScreen.AutoSize();


	//�ָ���
	CRect rcSplit;

	rcSplit.top = screen_Rect.bottom;
	rcSplit.bottom = list_Rect.top;
	rcSplit.left = list_Rect.left;
	rcSplit.right =  list_Rect.right;
	//	GetDlgItem(IDC_SPLITTER)->MoveWindow(rcSplit);
	m_wndSplitter.MoveWindow(rcSplit);


	//����
	CRect facecap_Rect;
	facecap_Rect.top = m_clientRect.top;
	facecap_Rect.bottom =	facecap_Rect.top + face_height;
	facecap_Rect.left = list_Rect.right+2 ;
	facecap_Rect.right = m_clientRect.right;
	//���� ��ʽ=�ص����߿�=������С
	DlgPictureFaceCap.MoveWindow(facecap_Rect);
	DlgPictureFaceCap.AutoSize();

	//����
	CRect facealarm_Rect;
	facealarm_Rect.top = facecap_Rect.bottom ;
	facealarm_Rect.bottom =	m_clientRect.bottom-distance;
	facealarm_Rect.left = list_Rect.right+2 ;
	facealarm_Rect.right = m_clientRect.right;
	//���� ��ʽ=�ص����߿�=������С
	DlgPictureFaceAlarm.MoveWindow(facealarm_Rect);
	DlgPictureFaceAlarm.AutoSize();

	Invalidate();
}

void CDLGTabVideo::HideSize()
{
	CRect rc(0, 0, 0, 0);
	GetClientRect(&m_clientRect);
	//	GetParent()->GetClientRect(&rc);
	//	((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
	//	MoveWindow(rc);


	//�л������=LOGOͼƬ�Ŀ��
	int tab_width=220;
	//LOGOͼƬ�ĸ߶�
	//int button_top=130;
	//int button_width=192;
	//tab�߶�
	//int tab_top=163;

	//LOGOͼƬ�ĸ߶�
	int button_top=0;
	int button_width=192;
	//tab�߶�
	int tree_top=0;

	//�б�ĸ߶�
	int list_height=180;


	//����߾�
	int distance=5;

	//FACE�Ŀ��
	int face_width=230;
	int face_height=m_clientRect.Height()-distance-28;


	//�豸��
	CRect tree_Rect;
	tree_Rect.top = m_clientRect.top+tree_top;
	tree_Rect.bottom = m_clientRect.bottom-distance;
	tree_Rect.left = m_clientRect.left;
	tree_Rect.right = m_clientRect.left+tab_width;
	//���� ��ʽ=�ص����߿�=������С
	//	m_TabMain.MoveWindow(tab_Rect);

	DlgDeviceTree.MoveWindow(tree_Rect);

	//�б�
	CRect list_Rect;
	list_Rect.top = m_clientRect.bottom-distance-list_height/* + 5*/;
	list_Rect.bottom = m_clientRect.bottom-distance/* - 10*/;
	list_Rect.left = tree_Rect.right+distance/* + 10*/;
	list_Rect.right = m_clientRect.right-distance-face_width;
	//���� ��ʽ=�ص����߿�=������С
	m_ListCar.MoveWindow(list_Rect);

	//����
	CRect screen_Rect;
	screen_Rect.top = m_clientRect.top/* + 5*/;
	screen_Rect.bottom = list_Rect.top -distance/* - 10*/;
	screen_Rect.left = tree_Rect.right +distance/* + 10*/;
	screen_Rect.right = list_Rect.right;
	//���� ��ʽ=�ص����߿�=������С
	DlgScreen.MoveWindow(screen_Rect);


	DlgDeviceTree.AutoSize();
	DlgScreen.AutoSize();


	//�ָ���
	CRect rcSplit;

	rcSplit.top = screen_Rect.bottom;
	rcSplit.bottom = list_Rect.top;
	rcSplit.left = list_Rect.left;
	rcSplit.right =  list_Rect.right;
	//	GetDlgItem(IDC_SPLITTER)->MoveWindow(rcSplit);
	m_wndSplitter.MoveWindow(rcSplit);


	//����
	CRect facecap_Rect;
	facecap_Rect.top = m_clientRect.top;
	facecap_Rect.bottom =	facecap_Rect.top + face_height;
	facecap_Rect.left = list_Rect.right+2 ;
	facecap_Rect.right = m_clientRect.right;
	//���� ��ʽ=�ص����߿�=������С
	DlgPictureFaceCap.MoveWindow(facecap_Rect);
	DlgPictureFaceCap.AutoSize();

	//����
	CRect facealarm_Rect;
	facealarm_Rect.top = facecap_Rect.bottom ;
	facealarm_Rect.bottom =	m_clientRect.bottom-distance;
	facealarm_Rect.left = list_Rect.right+2 ;
	facealarm_Rect.right = m_clientRect.right;
	//���� ��ʽ=�ص����߿�=������С
	DlgPictureFaceAlarm.MoveWindow(facealarm_Rect);
	DlgPictureFaceAlarm.AutoSize();

	Invalidate();
}

// CDLGTabVideo message handlers

void CDLGTabVideo::OnOk()
{
	// TODO: Add your control notification handler code here
	//	CDialog::OnOK();
}

void CDLGTabVideo::OnCancel()
{
	// TODO: Add your control notification handler code here
	DlgMain->OnCancel();
}

void CDLGTabVideo::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	// TODO: Add your message handler code here

	// Do not call CDialog::OnPaint() for painting messages
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
}


//��ʼ���л���
void CDLGTabVideo::TabMainInit(void)
{
	DlgDeviceTree.Create(IDD_DEVICE_TREE,this);
	DlgNormal.Create(IDD_NORMAL,this);
	DlgDeviceTree.ShowWindow(SW_SHOW);
	DlgNormal.ShowWindow(SW_HIDE);

}

//////////////////////////////////////////////////////////////////////////
void CDLGTabVideo::ListMainInit(void)
{
	m_ListCar.SetBkColor(RGB(248,248,248));

	//Ĭ��ͼƬ

	int bmpw=96,bmph=20;
	defaultbitmap.LoadBitmap(IDB_DEFAULT_LIST);    

	//Ĭ��ͼ���С�����Ҫ�б��㡣Ҳ����
	m_ListImg.Init(&m_ListCar, bmpw, bmph, &defaultbitmap);

	m_ListCar.InsertColumn(0, _T("����ͼƬ"), LVCFMT_LEFT, bmpw);//-----
	m_ListCar.InsertColumn(1, _T("ʱ��" ), LVCFMT_LEFT, 140);
	m_ListCar.InsertColumn(2, _T("����ͷ����" ), LVCFMT_LEFT, 140);
	m_ListCar.InsertColumn(3, _T("IP��ַ"), LVCFMT_LEFT, 100);
	m_ListCar.InsertColumn(4, _T("���") , LVCFMT_LEFT, 40);
	m_ListCar.InsertColumn(5, _T("���ƺ�"), LVCFMT_LEFT, 70);
	m_ListCar.InsertColumn(6, _T("���Ŷ�"), LVCFMT_LEFT, 50);
	m_ListCar.InsertColumn(7, _T("��ʻ����"), LVCFMT_LEFT, 70);
	m_ListCar.InsertColumn(8, _T("������ɫ"), LVCFMT_LEFT, 70);
#if ALLTAB_DETECT_CAR_MODE
	m_ListCar.InsertColumn(9, _T("��������"), LVCFMT_LEFT, 90);
	m_ListCar.InsertColumn(10, _T("������ɫ"), LVCFMT_LEFT, 60);
	m_ListCar.InsertColumn(11, _T("������"), LVCFMT_LEFT, 50);
	m_ListCar.InsertColumn(12, _T("ͼƬ·��"), LVCFMT_LEFT, 0);
	m_ListCar.InsertColumn(13, _T("������ģʽ"), LVCFMT_LEFT, 0);
	m_ListCar.InsertColumn(14, _T("nid"), LVCFMT_LEFT, 0);
	m_ListCar.InsertColumn(15, _T("blackid"), LVCFMT_LEFT, 0);
#else

	m_ListCar.InsertColumn(9, _T("������"), LVCFMT_LEFT, 50);
	m_ListCar.InsertColumn(10, _T("ͼƬ·��"), LVCFMT_LEFT, 0);
	m_ListCar.InsertColumn(11, _T("������ģʽ"), LVCFMT_LEFT, 0);
	m_ListCar.InsertColumn(12, _T("nid"), LVCFMT_LEFT, 0);
	m_ListCar.InsertColumn(13, _T("blackid"), LVCFMT_LEFT, 0);

#endif
	//m_ListCar.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	//��ź�ͼƬ�ߵ�
	m_ListImg.SwapColumns(0, 4);
	

	m_ListCarTotal=0;
}

//˫����ʾ��ͼ
void CDLGTabVideo::OnLvnItemActivateList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	char str[ZOG_MAX_PATH_STR]={0};
	char blackstr[ZOG_MAX_PATH_STR]={0};
	//����
#if ALLTAB_DETECT_CAR_MODE
	//����
	m_ListCar.GetItemText(pNMIA->iItem,14,str,260);
	m_ListCar.GetItemText(pNMIA->iItem,15,blackstr,260);
#else
	//�綯��
	m_ListCar.GetItemText(pNMIA->iItem,12,str,260);
	m_ListCar.GetItemText(pNMIA->iItem,13,blackstr,260);
#endif

	struct BLACK_DATA_ST blackdata={0};

	CDLGpictureView dlgPicView;
	dlgPicView.m_txt="";

	long nid=atoi(str);
	long blackid=atoi(blackstr);

	struct HISTORY_CarDetect_ST tempdata={0};

	MySqlIO.CAR_MatchResult_ReadforListOne(nid,tempdata);

	dlgPicView.m_txt="ʱ��:";

	sprintf(str,"%04d-%02d-%02d %02d:%02d:%02d",		
		tempdata.year,
		tempdata.mon,
		tempdata.day,
		tempdata.hour,
		tempdata.min,
		tempdata.sec);

	dlgPicView.m_txt+=str;
	dlgPicView.m_txt+="\n�豸����:";
	dlgPicView.m_txt+=tempdata.name;
	dlgPicView.m_txt+="\n�豸IP:";
	dlgPicView.m_txt+=tempdata.ip;

	dlgPicView.m_txt+="\n���ƺ�:";
	dlgPicView.m_txt+=tempdata.plate;

	dlgPicView.m_txt+="\n����:";
	dlgPicView.m_txt+=tempdata.direction;

	dlgPicView.m_txt+="\n������ɫ:";
	dlgPicView.m_txt+=tempdata.platecolor;

#if ALLTAB_DETECT_CAR_MODE

	dlgPicView.m_txt+="\n��������:";
	dlgPicView.m_txt+=tempdata.platetype;

	dlgPicView.m_txt+="\n������ɫ:";
	dlgPicView.m_txt+=tempdata.carcolor;
#endif
	if( blackid >0)
	{
		if(MySqlIO.CAR_BlackTable_ReadOneWithNid(blackid,blackdata))
		{
			dlgPicView.m_txt+="\nʧ������:";
			dlgPicView.m_txt+=blackdata.name;
			dlgPicView.m_txt+="\nƷ��:";
			dlgPicView.m_txt+=blackdata.brand;
			dlgPicView.m_txt+="\n���ƺ�:";
			dlgPicView.m_txt+=blackdata.plate;
			dlgPicView.m_txt+="\nʧ���绰:";
			dlgPicView.m_txt+=blackdata.Phone;
			dlgPicView.m_txt+="\n������Ϣ:";
			dlgPicView.m_txt+=blackdata.other;
		}
	}
	//����
	dlgPicView.Titlestr=tempdata.name;

	char *p=strrchr(tempdata.path,'\\');
	if(p!=NULL)
		p++;
	else
		return ;

	dlgPicView.Titlestr+=p;
	//·��
	dlgPicView.srcfile=tempdata.path;
	dlgPicView.srcsmallfile=tempdata.smallpath;


	dlgPicView.DoModal();

	*pResult = 0;
}


//NMTVCUSTOMDRAW
//����
void CDLGTabVideo::OnNMCustomdrawList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVCUSTOMDRAW lplvcd=(LPNMLVCUSTOMDRAW)pNMHDR;
	*pResult=CDRF_DODEFAULT;

	switch(lplvcd->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
		{
			*pResult=CDRF_NOTIFYITEMDRAW;
			return;
		}
	case CDDS_ITEMPREPAINT:
		{
			*pResult=CDRF_NOTIFYSUBITEMDRAW;
			return;
		}
	case CDDS_ITEMPREPAINT|CDDS_SUBITEM:
		{
			char str[260]={0};
			COLORREF clrNewTextColor,clrNewBkColor;
			int nItem=static_cast<int>(lplvcd->nmcd.dwItemSpec);

#if ALLTAB_DETECT_CAR_MODE
			//����
			m_ListCar.GetItemText(nItem,11,str,260);
#else
			//�綯��
			m_ListCar.GetItemText(nItem,9,str,260);
#endif
			lplvcd->clrTextBk=RGB(248,248,248);
			if(NULL!=strstr(str,"��"))
			{
				clrNewBkColor=RGB(255,0,0);//��װ���
				lplvcd->clrTextBk=clrNewBkColor;
				clrNewTextColor=RGB(255,255,255);	
				lplvcd->clrText=clrNewTextColor;
			}
			*pResult=CDRF_DODEFAULT;
			return;
		}
	}
}

void CDLGTabVideo::initSplitter(void)
{
	CRect rc;
	CWnd* pWnd;

	pWnd = GetDlgItem(IDC_SPLITTER);
	pWnd->GetWindowRect(rc);
	ScreenToClient(rc);
	BOOL bRet = m_wndSplitter.Create(WS_CHILD | WS_VISIBLE, rc, this, IDC_SPLITTER, SPS_HORIZONTAL, RGB(0, 0, 255));
	if (FALSE == bRet)
	{
		AfxMessageBox("m_wndSplitter create failed");
	}

	m_wndSplitter.RegisterLinkedWindow(SPLS_LINKED_UP,   &(DlgScreen));
	m_wndSplitter.RegisterLinkedWindow(SPLS_LINKED_DOWN,  GetDlgItem(IDC_LIST_CAR));

	//  relayout the splotter to make them good look
	m_wndSplitter.Relayout();

}

void CDLGTabVideo::OnMaxMinInfo(NMHDR* pNMHDR, LRESULT* pResult)
{
	//  Get current pos of the child controls
	CRect rcScreen;
	CRect rcList;

	DlgScreen.GetWindowRect(rcScreen);
	m_ListCar.GetWindowRect(rcList);

	this->ScreenToClient(rcScreen);
	this->ScreenToClient(rcList);

	//  return the pos limit
	SPC_NM_MAXMINPOS* pNewMaxMinPos = (SPC_NM_MAXMINPOS*)pNMHDR;
	if (IDC_SPLITTER == pNMHDR->idFrom)
	{
		pNewMaxMinPos->lMin = rcScreen.top + 300;
		pNewMaxMinPos->lMax = rcList.bottom -180;
	}
}