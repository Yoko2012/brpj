// DLGPictureFace.cpp : implementation file
//

#include "stdafx.h"
#include "SmartVillage.h"
#include "DLGPictureFace.h"
#include "SmartVillageDlg.h"
#include "DLGWarnning.h"

////////////////lynn/////////////////
extern CYRSVMySQL MySqlIO;
extern CSmartVillageDlg *DlgMain;
////////////////lynn/////////////////
#include "DLGLogin.h"
extern CDLGLogin DlgLogin;

#include "DLGSetSystem.h"
extern CDLGSetSystem DlgSetSystem;


// CDLGPictureFace dialog

IMPLEMENT_DYNAMIC(CDLGPictureFace, CDialog)

CDLGPictureFace::CDLGPictureFace(CWnd* pParent /*=NULL*/)
: CDialog(CDLGPictureFace::IDD, pParent)
{
	DlgPictureLite=NULL;
	DlgPLiteTotal=0;
	TitleDrawFlag=false;
	hidemode=false;
	hideflag=false;
}

CDLGPictureFace::~CDLGPictureFace()
{
	if(DlgPictureLite)
	{
		for(int i=0;i<DlgPLiteTotal;i++)
			delete DlgPictureLite[i];
		free(DlgPictureLite);
		DlgPictureLite=NULL;
		DlgPLiteTotal=0;
	}
}

void CDLGPictureFace::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_CLEAN, m_b_clean);
	DDX_Control(pDX, IDC_BUTTON_HIDE, m_b_hide);
}


BEGIN_MESSAGE_MAP(CDLGPictureFace, CDialog)
	ON_BN_CLICKED(IDOK, &CDLGPictureFace::OnOk)
	ON_BN_CLICKED(IDCANCEL, &CDLGPictureFace::OnCancel)
	ON_WM_PAINT()
	ON_MESSAGE(WM_ADDFACE_MESSAGE,OnAddMessage)
	ON_MESSAGE(WM_CLEANFACE_MESSAGE,OnCleanMessage)
	ON_BN_CLICKED(IDC_BUTTON_CLEAN, &CDLGPictureFace::OnBnClickedButtonClean)
	ON_BN_CLICKED(IDC_BUTTON_HIDE, &CDLGPictureFace::OnBnClickedButtonHide)
END_MESSAGE_MAP()


// CDLGPictureFace message handlers
BOOL CDLGPictureFace::OnInitDialog()
{
	CDialog::OnInitDialog();
	//������
	CRect localRect;
	GetDlgItem(IDC_STATIC_WIN)->GetWindowRect(&localRect);

	ScreenToClient(&localRect);


	if(TitleDrawFlag)
	{
		GetDlgItem(IDC_STATIC_TITLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_CLEAN)->ShowWindow(SW_SHOW);
	}
	else
	{
		GetDlgItem(IDC_STATIC_TITLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_CLEAN)->ShowWindow(SW_HIDE);
	}

	if(hideflag)
		GetDlgItem(IDC_BUTTON_HIDE)->ShowWindow(SW_SHOW);
	else
		GetDlgItem(IDC_BUTTON_HIDE)->ShowWindow(SW_HIDE);

	m_b_clean.LoadBitmaps(IDB_FACE_CLEAN,IDB_FACE_CLEAN_PRESS,NULL,NULL);
	m_b_hide.LoadBitmaps(IDB_FACE_HIDE_DOWN,IDB_FACE_HIDE_DOWN_PRESS,NULL,NULL);

	m_list.Create(NULL,NULL,WS_VISIBLE|WS_TABSTOP | WS_CHILD ,localRect,this,IDC_STATIC_WIN);

	//�������
	AutoSize();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDLGPictureFace::AutoSize()
{
	CRect rc(0, 0, 0, 0);
	GetClientRect(&rc);

	if(TitleDrawFlag)
	{
		int cleanw=18;
		int h=28;
		if(hideflag)
		{
			//����
			CRect hideRect;
			hideRect.top = rc.top;
			hideRect.bottom = rc.top+h;
			hideRect.left = rc.left;
			hideRect.right = rc.left+cleanw;

			GetDlgItem(IDC_BUTTON_HIDE)->MoveWindow(hideRect);

			//����
			CRect titleRect;
			titleRect.top = rc.top;
			titleRect.bottom = rc.top+h;
			titleRect.left =  rc.left+cleanw;
			titleRect.right = rc.right-cleanw;

			GetDlgItem(IDC_STATIC_TITLE)->MoveWindow(titleRect);

			//����
			CRect cleanRect;
			cleanRect.top = rc.top;
			cleanRect.bottom = rc.top+h;
			cleanRect.left =  titleRect.right;
			cleanRect.right = rc.right;

			GetDlgItem(IDC_BUTTON_CLEAN)->MoveWindow(cleanRect);
		}
		else
		{
			//����
			CRect titleRect;
			titleRect.top = rc.top;
			titleRect.bottom = rc.top+h;
			titleRect.left =  rc.left;
			titleRect.right = rc.right-cleanw;

			GetDlgItem(IDC_STATIC_TITLE)->MoveWindow(titleRect);
			//����
			CRect cleanRect;
			cleanRect.top = rc.top;
			cleanRect.bottom = rc.top+h;
			cleanRect.left =  titleRect.right;
			cleanRect.right = rc.right;

			GetDlgItem(IDC_BUTTON_CLEAN)->MoveWindow(cleanRect);
		}

		//����
		CRect Rect;
		Rect.top = rc.top+h;
		Rect.bottom = rc.bottom;
		Rect.left =  rc.left;
		Rect.right = rc.right;

		GetDlgItem(IDC_STATIC_WIN)->MoveWindow(Rect);

		MoveList(Rect);
	}
	else
	{
		//����
		CRect Rect;
		Rect.top = rc.top;
		Rect.bottom = rc.bottom;
		Rect.left =  rc.left;
		Rect.right = rc.right;

		GetDlgItem(IDC_STATIC_WIN)->MoveWindow(Rect);

		MoveList(Rect);

	}

	Invalidate();
}

// CDLGPictureFace message handlers

void CDLGPictureFace::OnOk()
{
	// TODO: Add your control notification handler code here
	//	CDialog::OnOK();
}

void CDLGPictureFace::OnCancel()
{
	// TODO: Add your control notification handler code here
	//	CDialog::OnCancel();
}

void CDLGPictureFace::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	// TODO: Add your message handler code here

	// Do not call CDialog::OnPaint() for painting messages
	//������ͼ	
	CRect    rect;     
	GetClientRect(&rect);     

	//����Դ������λͼ     
	CBitmap    bitmap;     
	bitmap.LoadBitmap(IDB_PIC_FACE_BACK);    
	BITMAP bmp;
	bitmap.GetBitmap(&bmp);

	CDC    memdc;     
	memdc.CreateCompatibleDC(&dc);     
	memdc.SelectObject(bitmap); 
	dc.SetStretchBltMode(COLORONCOLOR);
	dc.StretchBlt(0,0,rect.Width(),rect.Height(),&memdc,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
	memdc.DeleteDC();

	if(TitleDrawFlag)
	{
		CDC *pDC=GetDlgItem(IDC_STATIC_TITLE)->GetDC();
		CRect trect; 
		GetDlgItem(IDC_STATIC_TITLE)->GetClientRect(&trect);//���pictrue�ؼ����ڵľ�������

		CBitmap    tbitmap;     
		tbitmap.LoadBitmap(TitleResDef);    
		BITMAP tbmp;
		tbitmap.GetBitmap(&tbmp);

		CDC    tmemdc;     
		tmemdc.CreateCompatibleDC(pDC);     
		tmemdc.SelectObject(tbitmap); 
		pDC->SetStretchBltMode(COLORONCOLOR);
		pDC->StretchBlt(0,0,trect.Width(),trect.Height(),&tmemdc,0,0,tbmp.bmWidth,tbmp.bmHeight,SRCCOPY);
		memdc.DeleteDC();

		GetDlgItem(IDC_STATIC_TITLE)->ReleaseDC(pDC);
	}

	CDialog::OnPaint();
}

void CDLGPictureFace::CleanList(void) 
{
	if(DlgPictureLite)
	{
		for(int i=0;i<DlgPLiteTotal;i++)
			delete DlgPictureLite[i];
		free(DlgPictureLite);
		DlgPictureLite=NULL;
		DlgPLiteTotal=0;
	}
	Invalidate();
}
void CDLGPictureFace::InitList(void) 
{
	//����LIST
	CRect localRect;
	GetDlgItem(IDC_STATIC_WIN)->GetWindowRect(&localRect);

	ScreenToClient(&localRect);

	int i;

	CleanList();

	/*
	//�����ݿ��ȡ����
	list_photo.clear();
	MySqlIO.PHOTO_ReadAllPhotoInfoWithCaseID(list_photo,Casenid);

	//�����ݿ��ȡ����
	DlgPLiteTotal=list_photo.size();
	//	DlgPLiteTotal=9;

	DlgPictureLite =(CDLGPictureLite **)calloc(DlgPLiteTotal,sizeof(CDLGPictureLite *));
	Liteheight=0;
	Litewidth=0;

	CRect rect;
	//���LIST
	list<struct CASE_PHOTO_INFO_ST>::iterator beglist;

	//���LIST
	for(i=0,beglist=list_photo.begin();
	i<DlgPLiteTotal && beglist!=list_photo.end();
	i++,beglist++)
	{
	DlgPictureLite[i]=new CDLGPictureLite;
	//��������
	DlgPictureLite[i]->Casenid=Casenid;
	DlgPictureLite[i]->data=beglist;
	//��������
	DlgPictureLite[i]->Create(IDD_CASE_REGISTER_RESEARCH_LITE,&m_list);
	DlgPictureLite[i]->ShowWindow(SW_SHOW);
	if(0==i)
	{
	//ִֻ��һ��
	DlgPictureLite[i]->GetWindowRect(&rect);
	Liteheight=rect.Height();
	Litewidth=rect.Width();
	}
	}
	*/

	DlgPLiteTotal=9;

	DlgPictureLite =(CDLGPictureLite **)calloc(DlgPLiteTotal,sizeof(CDLGPictureLite *));
	Liteheight=133+60+5;
	Litewidth=100+6;

	CRect rect;

	//���LIST
	for(i=0;
		i<DlgPLiteTotal;
		i++)
	{
		DlgPictureLite[i]=new CDLGPictureLite;
		//��������

		//��������
		DlgPictureLite[i]->Create(IDD_PICTURE_LITE,&m_list);
		DlgPictureLite[i]->ShowWindow(SW_SHOW);
		if(0==i)
		{
			//ִֻ��һ��
			//	DlgPictureLite[i]->GetWindowRect(&rect);
			//	Liteheight=rect.Height();
			//	Litewidth=rect.Width();
			//�����������ڴ�С
			Liteheight=133+60+5;
			Litewidth=100+6;

		}
	}


	if(DlgPLiteTotal >0)
	{
		//������
		MoveListScroll(localRect);
		//LITE��
		MoveListWin(localRect);
	}
}
char* CDLGPictureFace::FaceSex(int i)
{
	switch(i)
	{
	case SEX_MALE:return "����";
	case SEX_UNKNOW:return "δ֪";
	case SEX_FEMALE:return "Ů��";
	default:return "δ֪";
	}
}

void CDLGPictureFace::DisplayCapList(list<struct FACE_CAPTURE_ST> &faceList,int AlarmFlag) 
{
	//����LIST
	CRect localRect;
	GetDlgItem(IDC_STATIC_WIN)->GetWindowRect(&localRect);

	ScreenToClient(&localRect);

	int i;

	Liteheight=133+60+5;
	Litewidth=100+6;
	char str[256]={0};
	CRect rect;

	DlgPLiteTotal=faceList.size();
	if(faceList.size()<=0)
		return ;
	DlgPictureLite =(CDLGPictureLite **)calloc(DlgPLiteTotal,sizeof(CDLGPictureLite *));

	list<struct FACE_CAPTURE_ST>::iterator beglist;

	for(i=0,beglist=faceList.begin();beglist!=faceList.end();i++,beglist++)
		//���LIST
	{
		DlgPictureLite[i]=new CDLGPictureLite;
		//��������

		//��������
		DlgPictureLite[i]->Create(IDD_PICTURE_LITE,&m_list);
		DlgPictureLite[i]->ShowWindow(SW_SHOW);
		DlgPictureLite[i]->srcfile=beglist->face;
		DlgPictureLite[i]->DrawFlag=true;

		sprintf(str,"%04d-%02d-%02d\n%02d:%02d:%02d\n%s\n����:%d %s",
			beglist->year,
			beglist->mon,
			beglist->day,
			beglist->hour,
			beglist->min,
			beglist->sec,
			beglist->cameraName,
			beglist->age,
			FaceSex(beglist->sex));

		DlgPictureLite[i]->m_info=str;
		DlgPictureLite[i]->capnid=beglist->nid;

		DlgPictureLite[i]->BlackFlag=AlarmFlag;


		DlgPictureLite[i]->LoadPic();

		if(0==i)
		{
			//ִֻ��һ��
			//	DlgPictureLite[i]->GetWindowRect(&rect);
			//	Liteheight=rect.Height();
			//	Litewidth=rect.Width();
			//�����������ڴ�С
			Liteheight=133+60+5;
			Litewidth=100+6;

		}
	}

	if(DlgPLiteTotal >0)
	{
		//������
		MoveListScroll(localRect);
		//LITE��
		MoveListWin(localRect);
	}
}

void CDLGPictureFace::DisplayRecgTEMPList(list<struct TEMP_CMP_RESULT_ST> &faceList,int AlarmFlag) 
{
	//����LIST
	CRect localRect;
	GetDlgItem(IDC_STATIC_WIN)->GetWindowRect(&localRect);

	ScreenToClient(&localRect);

	int i;

	Liteheight=133+60+5;
	Litewidth=100+6;
	char str[256]={0};
	CRect rect;

	DlgPLiteTotal=faceList.size();
	if(faceList.size() <=0)
		return ; 
	DlgPictureLite =(CDLGPictureLite **)calloc(DlgPLiteTotal,sizeof(CDLGPictureLite *));

	list<struct TEMP_CMP_RESULT_ST>::iterator beglist;

	for(i=0,beglist=faceList.begin();beglist!=faceList.end();i++,beglist++)
		//���LIST
	{
		DlgPictureLite[i]=new CDLGPictureLite;
		//��������

		//��������
		DlgPictureLite[i]->Create(IDD_PICTURE_LITE,&m_list);
		DlgPictureLite[i]->ShowWindow(SW_SHOW);
		DlgPictureLite[i]->srcfile=beglist->tempface.face;
		DlgPictureLite[i]->DrawFlag=true;

		sprintf(str,"%04d-%02d-%02d\n%02d:%02d:%02d\n����:%d %s\n���ƶ� %d",
			beglist->tempface.year,
			beglist->tempface.mon,
			beglist->tempface.day,
			beglist->tempface.hour,
			beglist->tempface.min,
			beglist->tempface.sec,
			beglist->tempface.age,
			FaceSex(beglist->tempface.sex),
			beglist->similarity);

		DlgPictureLite[i]->m_info=str;
		DlgPictureLite[i]->capnid=beglist->tempface.nid;

		DlgPictureLite[i]->BlackFlag=AlarmFlag;


		DlgPictureLite[i]->LoadPic();

		if(0==i)
		{
			//ִֻ��һ��
			//	DlgPictureLite[i]->GetWindowRect(&rect);
			//	Liteheight=rect.Height();
			//	Litewidth=rect.Width();
			//�����������ڴ�С
			Liteheight=133+60+5;
			Litewidth=100+6;

		}
	}

	if(DlgPLiteTotal >0)
	{
		//������
		MoveListScroll(localRect);
		//LITE��
		MoveListWin(localRect);
	}
}


void CDLGPictureFace::DisplayRecgBLACKList(list<struct BLACK_CMP_RESULT_ST> &faceList,int AlarmFlag) 
{
	//����LIST
	CRect localRect;
	GetDlgItem(IDC_STATIC_WIN)->GetWindowRect(&localRect);

	ScreenToClient(&localRect);

	char STR_NATIVE[32][32] = {"δ֪","����","���","����","�㶫","�ӱ�","ɽ��","����","����","������",
		"����","�㽭","����","����","����","ɽ��","����","����","����","����",
		"�Ĵ�","����","����","����","����","�ຣ","̨��","�½�","����","����",
		"���ɹ�","����"};

	int i;

	Liteheight=133+60+5;
	Litewidth=100+6;
	char str[256]={0};
	CRect rect;

	DlgPLiteTotal=faceList.size();
	if(faceList.size() <=0)
		return ; 
	DlgPictureLite =(CDLGPictureLite **)calloc(DlgPLiteTotal,sizeof(CDLGPictureLite *));

	list<struct BLACK_CMP_RESULT_ST>::iterator beglist;

	for(i=0,beglist=faceList.begin();beglist!=faceList.end();i++,beglist++)
		//���LIST
	{
		DlgPictureLite[i]=new CDLGPictureLite;
		//��������

		//��������
		DlgPictureLite[i]->Create(IDD_PICTURE_LITE,&m_list);
		DlgPictureLite[i]->ShowWindow(SW_SHOW);
		DlgPictureLite[i]->srcfile=beglist->face.face;
		DlgPictureLite[i]->DrawFlag=true;

		sprintf(str,"%s %s\n����:%s\n���� %04d-%02d-%02d\n���ƶ� %d",
			beglist->person.name,
			FaceSex(beglist->person.sex),
			STR_NATIVE[beglist->person.native],
			beglist->person.year,
			beglist->person.mon,
			beglist->person.day,
			beglist->similarity);

		DlgPictureLite[i]->m_info=str;
		DlgPictureLite[i]->capnid=beglist->face.nid;
		DlgPictureLite[i]->personnid=beglist->person.nid;

		DlgPictureLite[i]->BlackFlag=AlarmFlag;

		DlgPictureLite[i]->LoadPic();

		if(0==i)
		{
			//ִֻ��һ��
			//	DlgPictureLite[i]->GetWindowRect(&rect);
			//	Liteheight=rect.Height();
			//	Litewidth=rect.Width();
			//�����������ڴ�С
			Liteheight=133+60+5;
			Litewidth=100+6;

		}
	}

	if(DlgPLiteTotal >0)
	{
		//������
		MoveListScroll(localRect);
		//LITE��
		MoveListWin(localRect);
	}
}


void CDLGPictureFace::DisplayAlarmLiteList(list<struct FACE_ALARM_VIEW_ST> &faceList,int AlarmFlag) 
{

	//����LIST
	CRect localRect;
	GetDlgItem(IDC_STATIC_WIN)->GetWindowRect(&localRect);

	ScreenToClient(&localRect);

	int i;
	Liteheight=133+60+5;
	Litewidth=100+6;
	char str[256]={0};
	CRect rect;

	DlgPLiteTotal=faceList.size();
	if(faceList.size() <=0)
		return ; 
	DlgPictureLite =(CDLGPictureLite **)calloc(DlgPLiteTotal,sizeof(CDLGPictureLite *));

	list<struct FACE_ALARM_VIEW_ST>::iterator beglist;

	for(i=0,beglist=faceList.begin();beglist!=faceList.end();i++,beglist++)
		//���LIST
	{
		DlgPictureLite[i]=new CDLGPictureLite;
		//��������

		//��������
		DlgPictureLite[i]->Create(IDD_PICTURE_LITE,&m_list);
		DlgPictureLite[i]->ShowWindow(SW_SHOW);
		DlgPictureLite[i]->srcfile=beglist->face;
		DlgPictureLite[i]->DrawFlag=true;

		sprintf(str,"%s\n%s %s\n���� %04d-%02d-%02d\n���ƶ� %d",
			beglist->dbname,
			beglist->name,
			FaceSex(beglist->sex),
			beglist->year,
			beglist->mon,
			beglist->day,
			beglist->similarity);

		DlgPictureLite[i]->m_info=str;
		DlgPictureLite[i]->capnid=beglist->captureID;
		DlgPictureLite[i]->personnid=beglist->person_black_nid;

		DlgPictureLite[i]->BlackFlag=AlarmFlag;


		DlgPictureLite[i]->LoadPic();

		if(0==i)
		{
			//ִֻ��һ��
			//	DlgPictureLite[i]->GetWindowRect(&rect);
			//	Liteheight=rect.Height();
			//	Litewidth=rect.Width();
			//�����������ڴ�С
			Liteheight=133+60+5;
			Litewidth=100+6;

		}
	}

	if(DlgPLiteTotal >0)
	{
		//������
		MoveListScroll(localRect);
		//LITE��
		MoveListWin(localRect);
	}

}
void CDLGPictureFace::MoveList(CRect Rect) 
{

	m_list.MoveWindow(Rect);

	if(DlgPLiteTotal >0)
	{
		//������
		MoveListScroll(Rect);

		//LITE��
		MoveListWin(Rect);
	}
	int i;
	for(i=0;i<DlgPLiteTotal;i++)
	{
		DlgPictureLite[i]->AutoSize();
	}

}

void CDLGPictureFace::MoveListScroll(CRect Rect) 
{
	int w,h;
	int CountHeight;

	w=(Rect.Width()-15)/Litewidth;
	if(w>1)
	{
		//����ֹһ��
		h=(int)ceil((double)DlgPLiteTotal/(double)w);
		CountHeight = Rect.top	+ Liteheight*h;
	}
	else
	{
		CountHeight = Rect.top	+ Liteheight*DlgPLiteTotal;
	}

	if(CountHeight>Rect.bottom)//���ô�ֱ��������Ϣ
	{
		SCROLLINFO si;
		si.cbSize=sizeof(SCROLLINFO);
		si.nMin=0;
		si.nMax=CountHeight;//-LocalPicRect.bottom;//���������Χ��ʵ�ʴ��ڸ߶�һ��
		si.nPage=Rect.bottom;//LocalPicRect.Height();//LocalPicRect.bottom;//�ɼ����ڸ߶Ⱥ�ҳ��С����һ��
		si.nPos=0;
		si.fMask=SIF_ALL;
		//::SetScrollInfo(m_LocalAppContainer.m_hWnd,SBS_VERT,&si);
		m_list.SetScrollInfo(SBS_VERT,&si);	
	}
}

void CDLGPictureFace::MoveListWin(CRect Rect) 
{
	int i,w;

	w=(Rect.Width()-15)/Litewidth;
	if(w>1)
	{
		//����ֹһ��
		for(i=0;i<DlgPLiteTotal;i++)
		{
			CPoint MyPoint((i % w) * Litewidth, ((i / w) ) * Liteheight); 
			CRect literect(MyPoint, CSize(Litewidth, Liteheight));
			DlgPictureLite[i]->MoveWindow(literect);
		}
	}
	else
	{
		CRect rect;
		//����ֻ��ռһ��
		for(i=0;i<DlgPLiteTotal;i++)
		{
			rect.top=i*Liteheight;
			rect.bottom=rect.top+Liteheight;
			rect.left=Rect.left;
			rect.right=Rect.right;

			DlgPictureLite[i]->MoveWindow(rect);
		}
	}
}


void CDLGPictureFace::AddCapList(struct FACE_CAPTURE_ST facedata,int AlarmFlag) 
{
	//����LIST
	CRect localRect;
	GetDlgItem(IDC_STATIC_WIN)->GetWindowRect(&localRect);

	ScreenToClient(&localRect);

	Liteheight=133+60+5;
	Litewidth=100+6;
	char str[256]={0};
	CRect rect;

	if(0==DlgPLiteTotal)
		DlgPictureLite =(CDLGPictureLite **)calloc(1,sizeof(CDLGPictureLite *));
	else
	{
		DlgPictureLite =(CDLGPictureLite **)realloc(DlgPictureLite,(DlgPLiteTotal+1)*sizeof(CDLGPictureLite *));
		memcpy(&(DlgPictureLite[1]),&(DlgPictureLite[0]),DlgPLiteTotal*sizeof(CDLGPictureLite *));
	}

	DlgPictureLite[0]=new CDLGPictureLite;
	//��������

	//��������
	DlgPictureLite[0]->Create(IDD_PICTURE_LITE,&m_list);
	DlgPictureLite[0]->ShowWindow(SW_SHOW);
	DlgPictureLite[0]->srcfile=facedata.face;
	DlgPictureLite[0]->DrawFlag=true;

	sprintf(str,"%04d-%02d-%02d\n%02d:%02d:%02d\n%s\n����:%d %s",
		facedata.year,
		facedata.mon,
		facedata.day,
		facedata.hour,
		facedata.min,
		facedata.sec,
		facedata.cameraName,
		facedata.age,
		FaceSex(facedata.sex));

	DlgPictureLite[0]->m_info=str;
	DlgPictureLite[0]->capnid=facedata.nid;

	DlgPictureLite[0]->BlackFlag=AlarmFlag;

	DlgPictureLite[0]->LoadPic();

	//ִֻ��һ��
	//	DlgPictureLite[i]->GetWindowRect(&rect);
	//	Liteheight=rect.Height();
	//	Litewidth=rect.Width();
	//�����������ڴ�С
	Liteheight=133+60+5;
	Litewidth=100+6;

	DlgPLiteTotal++;

	if(DlgPLiteTotal >0)
	{
		//������
		MoveListScroll(localRect);
		//LITE��
		MoveListWin(localRect);
	}
	Invalidate();
}

//��ܶ��̴߳���
LRESULT CDLGPictureFace::OnAddMessage(WPARAM wParam,LPARAM lParam)
{
	struct FACE_CAPTURE_ST *facedata=(struct FACE_CAPTURE_ST *)lParam;
	int *a=(int*)wParam;

	//����ʱ����������
	if( TitleDrawFlag && hideflag && FLAG_FACE_ALARM == (*a))
		HideNormal();

	AddCapList(*facedata,*a);

	return 0;
}

LRESULT CDLGPictureFace::OnCleanMessage(WPARAM wParam,LPARAM lParam)
{
	CleanList();
	return 0;
}
void CDLGPictureFace::OnBnClickedButtonClean()
{
	// TODO: Add your control notification handler code here
	CleanList();
}

void CDLGPictureFace::OnBnClickedButtonHide()
{
	// TODO: Add your control notification handler code here
	if( !TitleDrawFlag || !hideflag)
		return ;

	if(hidemode)
	{
		m_b_hide.LoadBitmaps(IDB_FACE_HIDE_DOWN,IDB_FACE_HIDE_DOWN_PRESS,NULL,NULL);
		DlgMain->DlgTabVideo.AutoSize();
	}
	else
	{
		m_b_hide.LoadBitmaps(IDB_FACE_HIDE_UP,IDB_FACE_HIDE_UP_PRESS,NULL,NULL);
		DlgMain->DlgTabVideo.HideSize();
	}
	
	hidemode=!hidemode;
	m_b_hide.Invalidate();
}
void CDLGPictureFace::HideNormal()
{
	// TODO: Add your control notification handler code here
	if( !TitleDrawFlag || !hideflag)
		return ;

	m_b_hide.LoadBitmaps(IDB_FACE_HIDE_DOWN,IDB_FACE_HIDE_DOWN_PRESS,NULL,NULL);
	DlgMain->DlgTabVideo.AutoSize();

	hidemode=false;
	m_b_hide.Invalidate();
}
