// DLGSetBlackFaceLib.cpp : implementation file
//

#include "stdafx.h"
#include "SmartVillage.h"
#include "DLGSetBlackFaceLib.h"
#include "DLGWarnning.h"
#include "DLGSetBlackFaceEdit.h"
// CDLGSetBlackFaceLib dialog

extern CYRSVMySQL MySqlIO;

#include "DLGSetSystem.h"
extern CDLGSetSystem DlgSetSystem;

#include "SmartVillageDlg.h"
extern CSmartVillageDlg *DlgMain;

IMPLEMENT_DYNAMIC(CDLGSetBlackFaceLib, CDialog)

CDLGSetBlackFaceLib::CDLGSetBlackFaceLib(CWnd* pParent /*=NULL*/)
: CDialog(CDLGSetBlackFaceLib::IDD, pParent)
, m_name(_T(""))
{
	ListChoose=-1;
	ListPersonChoose=-1;
	m_page = 1;

	ListPersonTotal=0;
	ListPersonNow=0;
	facedbNum = 0;
	
	list_facedb.clear();
	list_person.clear();
	m_page=1;
}

CDLGSetBlackFaceLib::~CDLGSetBlackFaceLib()
{
	list_facedb.clear();
	list_person.clear();
}

void CDLGSetBlackFaceLib::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
	DDV_MaxChars(pDX, m_name, 128);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Control(pDX, IDC_BUTTON_BLACK_ADD, m_b_add);
	DDX_Control(pDX, IDC_BUTTON_BLACK_MODIFY, m_b_edit);
	DDX_Control(pDX, IDC_BUTTON_BLACK_DELETE, m_b_delete);
	DDX_Control(pDX, IDC_BUTTON_BLACK_PERSONADD, m_b_person_add);
	DDX_Control(pDX, IDC_BUTTON_BLACK_PERSONMODIFY, m_b_person_modify);
	DDX_Control(pDX, IDC_BUTTON_BLACK_PERSONDELETE, m_b_person_delete);
	DDX_Control(pDX, IDC_LIST_PERSON, m_List_person);
	DDX_Text(pDX, IDC_EDIT_PAGE, m_page);
	//}}AFX_DATA_MAP

	DDX_Control(pDX, IDC_BUTTON_FIRST, m_first_button);
	DDX_Control(pDX, IDC_BUTTON_PREVIOUS, m_pre_button);
	DDX_Control(pDX, IDC_BUTTON_NEXT, m_next_button);
	DDX_Control(pDX, IDC_BUTTON_LAST, m_last_button);
	DDX_Control(pDX, IDC_BUTTON_JUMP, m_jump_button);
}


BEGIN_MESSAGE_MAP(CDLGSetBlackFaceLib, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_JUMP, OnButtonJump)
	ON_BN_CLICKED(IDC_BUTTON_FIRST, OnButtonFirst)
	ON_BN_CLICKED(IDC_BUTTON_PREVIOUS, OnButtonPrevious)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_LAST, OnButtonLast)
	ON_BN_CLICKED(IDC_BUTTON_BLACK_ADD, OnButtonBlackAdd)
	ON_BN_CLICKED(IDC_BUTTON_BLACK_MODIFY, OnButtonBlackModify)
	ON_BN_CLICKED(IDC_BUTTON_BLACK_DELETE, OnButtonBlackdelete)
	ON_NOTIFY(NM_CLICK, IDC_LIST, OnClickList)
	ON_NOTIFY(NM_CLICK, IDC_LIST_PERSON, OnClickPersonList)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_BLACK_PERSONADD, &CDLGSetBlackFaceLib::OnBnClickedButtonBlackPersonadd)
	ON_BN_CLICKED(IDC_BUTTON_BLACK_PERSONMODIFY, &CDLGSetBlackFaceLib::OnBnClickedButtonBlackPersonmodify)
	ON_BN_CLICKED(IDC_BUTTON_BLACK_PERSONDELETE, &CDLGSetBlackFaceLib::OnBnClickedButtonBlackPersondelete)
	ON_NOTIFY(LVN_ITEMACTIVATE, IDC_LIST_PERSON, &CDLGSetBlackFaceLib::OnLvnItemActivateListPerson)
END_MESSAGE_MAP()

BOOL CDLGSetBlackFaceLib::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_List.InsertColumn(0, _T("���") , LVCFMT_LEFT, 50);
	m_List.InsertColumn(1, _T("����" ), LVCFMT_LEFT, 190);
	m_List.InsertColumn(2, _T("RWID" ), LVCFMT_LEFT, 0);


	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	CHeaderCtrl* pHeaderCtrl = (CHeaderCtrl*)m_List.GetHeaderCtrl();
	pHeaderCtrl->EnableWindow(FALSE);

	DisplayerList();

	GetDlgItem(IDC_STATIC_INFO)->GetWindowRect(printf_Rect);
	ScreenToClient(printf_Rect);

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


	m_b_add.LoadBitmaps(IDB_ADD_BUTTON,IDB_ADD_BUTTON_MOVE,NULL,IDB_ADD_BUTTON_DIS);
	m_b_add.SizeToContent();		//����ӦͼƬ��С

	m_b_edit.LoadBitmaps(IDB_EDIT_BUTTON,IDB_EDIT_BUTTON_MOVE,NULL,IDB_EDIT_BUTTON_DIS);
	m_b_edit.SizeToContent();		//����ӦͼƬ��С

	m_b_delete.LoadBitmaps(IDB_DEL_BUTTON,IDB_DEL_BUTTON_MOVE,NULL,IDB_DEL_BUTTON_DIS);
	m_b_delete.SizeToContent();		//����ӦͼƬ��С

	m_List_person.InsertColumn(0, _T("���") , LVCFMT_LEFT, 50);
	m_List_person.InsertColumn(1, _T("��ԱID") , LVCFMT_LEFT, 0);
	m_List_person.InsertColumn(2, _T("����" ), LVCFMT_LEFT, 80);
	m_List_person.InsertColumn(3, _T("�Ա�") , LVCFMT_LEFT, 50);
	m_List_person.InsertColumn(4, _T("��������") , LVCFMT_LEFT, 100);
	m_List_person.InsertColumn(5, _T("֤������") , LVCFMT_LEFT, 80);
	m_List_person.InsertColumn(6, _T("֤����") , LVCFMT_LEFT, 150);
	m_List_person.InsertColumn(7, _T("����") , LVCFMT_LEFT, 50);
	m_List_person.InsertColumn(8, _T("��ַ") , LVCFMT_LEFT, 150);
	m_List_person.InsertColumn(9, _T("RW��ԱID") , LVCFMT_LEFT, 0);



	m_List_person.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	CHeaderCtrl* pHeaderCtrl1 = (CHeaderCtrl*)m_List_person.GetHeaderCtrl();
	pHeaderCtrl1->EnableWindow(FALSE);

	m_b_person_add.LoadBitmaps(IDB_ADD_BUTTON,IDB_ADD_BUTTON_MOVE,NULL,IDB_ADD_BUTTON_DIS);
	m_b_person_add.SizeToContent();		//����ӦͼƬ��С

	m_b_person_modify.LoadBitmaps(IDB_EDIT_BUTTON,IDB_EDIT_BUTTON_MOVE,NULL,IDB_EDIT_BUTTON_DIS);
	m_b_person_modify.SizeToContent();		//����ӦͼƬ��С

	m_b_person_delete.LoadBitmaps(IDB_DEL_BUTTON,IDB_DEL_BUTTON_MOVE,NULL,IDB_DEL_BUTTON_DIS);
	m_b_person_delete.SizeToContent();		//����ӦͼƬ��С

	GetDlgItem(IDC_BUTTON_BLACK_MODIFY)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BLACK_DELETE)->EnableWindow(FALSE);

	GetDlgItem(IDC_BUTTON_BLACK_PERSONADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BLACK_PERSONMODIFY)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BLACK_PERSONDELETE)->EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
void CDLGSetBlackFaceLib::OnOK()
{
	// TODO: Add your control notification handler code here
}
void CDLGSetBlackFaceLib::OnCancel() 
{
	CDialog::OnCancel();
}

// CDLGSetBlackFaceLib message handlers
void CDLGSetBlackFaceLib::OnPaint()
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
HBRUSH CDLGSetBlackFaceLib::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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

// CDLGSetBlackFaceLib message handlers

void CDLGSetBlackFaceLib::OnButtonBlackAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(facedbNum > RW_MAX_FACE_DB_NUM)
	{
		AfxMessageBox("��Ӳ��ؿ�ʧ�ܣ����������������ؿ���");
		return;
	}

	if(m_name.IsEmpty())
	{
		AfxMessageBox("�����벼�ؿ�����");
		return;
	}
	
	struct FACE_DB_ST faceDB={0};

	strcpy(faceDB.dbname,m_name.GetBuffer());
#if OPEN_FACEDETECT_CODE

	if(!DlgMain->FaceMng.RWFaceMngDbAddNew(faceDB.RW_dbID,m_name.GetBuffer()))//��Ϊ
	{
		AfxMessageBox("��Ӳ��ؿ�ʧ��");
		return;
	}
#endif
	long nid;
	MySqlIO.FACE_BlackDB_AddNew(nid,faceDB);
	char dir[260]={0};
	sprintf(dir,"%s\\%d",DlgSetSystem.m_path_faceblack,nid);
	CreateDirectory(dir, NULL);


	//��������
	DisplayerList();
}

void CDLGSetBlackFaceLib::OnButtonBlackModify() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	//û��
	if(-1 == ListChoose)
		return ;
	struct FACE_DB_ST faceDB={0};
	char str[260]={0};
	m_List.GetItemText(ListChoose,0,str,260);
	faceDB.nid = atoi(str);
	strcpy(faceDB.dbname,m_name.GetBuffer());
	m_List.GetItemText(ListChoose,2,str,260);
	faceDB.RW_dbID = atoi(str);

	MySqlIO.FACE_BlackDB_Edit(faceDB);
	//��������
	DisplayerList();
}

void CDLGSetBlackFaceLib::OnButtonBlackdelete() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if(-1 == ListChoose)
		return ;


	//�����
	CDLGWarnning dlgw;
	dlgw.m_wintxt="ɾ��������";					//���ڱ���
	dlgw.m_warntxt="���ٴ�ȷ���Ƿ�ɾ��";	//��������
	int nResponse=dlgw.DoModal();
	if (nResponse == IDOK)
	{
		char str[260]={0};
#if OPEN_FACEDETECT_CODE
		m_List.GetItemText(ListChoose,2,str,260);
		long RWdbid = atoi(str);
		if(!DlgMain->FaceMng.RWFaceMngDbDeleteWithID(RWdbid))//��Ϊ
		{
			AfxMessageBox("ɾ�����ؿ�ʧ��");
			return;
		}
#endif
		m_List.GetItemText(ListChoose,0,str,260);
		long nid = atoi(str);
		MySqlIO.FACE_BlackDB_DeleteWithNid(nid);
		MySqlIO.FACE_BlackPerson_DeleteWithDBID(nid);

		char cmd[1024]={0};
		sprintf(cmd,"cmd /c rmdir /s /q \"%s\\%d\"",DlgSetSystem.m_path_faceblack,nid);
		WinExec(cmd,SW_HIDE);
	}
	else if (nResponse == IDCANCEL)
		return ;
	else
		return ;

	//��������
	DisplayerList();
}
void CDLGSetBlackFaceLib::OnClickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NM_LISTVIEW* p=	(NM_LISTVIEW *)pNMHDR;
	if(ListChoose == p->iItem)
		return;
	//ѡ�еĸ�ֵ
	ListChoose = p->iItem;
	//û��
	if(-1 == ListChoose)
	{
		m_name.Empty();
		list_person.clear();
		m_List_person.DeleteAllItems();

		GetDlgItem(IDC_BUTTON_BLACK_PERSONADD)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_BLACK_PERSONMODIFY)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_BLACK_PERSONDELETE)->EnableWindow(FALSE);

		GetDlgItem(IDC_BUTTON_BLACK_MODIFY)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_BLACK_DELETE)->EnableWindow(FALSE);
		return ;
	}
	else
	{
		DisplayerPersonList();
		char str[260]={0};
		m_List.GetItemText(ListChoose,1,str,260);
		m_name = str;
		GetDlgItem(IDC_BUTTON_BLACK_PERSONADD)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_BLACK_PERSONMODIFY)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_BLACK_PERSONDELETE)->EnableWindow(FALSE);

		GetDlgItem(IDC_BUTTON_BLACK_MODIFY)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_BLACK_DELETE)->EnableWindow(TRUE);
	}

	//����
	UpdateData(FALSE);

	*pResult = 0;
}

void CDLGSetBlackFaceLib::DisplayerList() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	list_facedb.clear();
	m_List.DeleteAllItems();

	//��ѯ���ݿ�
	MySqlIO.FACE_BlackDB_ReadAll(list_facedb);
	facedbNum = list_facedb.size();
	if(list_facedb.size() <=0)
			return ; 
	int nItem;
	char str[128]={0};

	list<struct FACE_DB_ST>::iterator beglist;
	for(beglist=list_facedb.begin();beglist!=list_facedb.end();beglist++)
	{
		sprintf(str,"%d",beglist->nid);
		nItem = m_List.InsertItem(0,str);

		m_List.SetItemText(nItem,1,beglist->dbname);
		sprintf(str,"%d",beglist->RW_dbID);
		m_List.SetItemText(nItem,2,str);
	}
}

void CDLGSetBlackFaceLib::DisplayerPersonList() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	list_person.clear();
	m_List_person.DeleteAllItems();

	char str[260]={0};
	m_List.GetItemText(ListChoose,0,str,260);
	long DBid = atoi(str);

	//��ȡ�ܵļ�¼��
	ListPersonTotal = MySqlIO.FACE_BlackPerson_GetNum(DBid);
	if(0==ListPersonTotal)
	{
		GetDlgItem(IDC_STATIC_INFO)->SetWindowText("��0�� 1/1ҳ");
		InvalidateRect(printf_Rect, TRUE);
		return ;
	}

	unsigned long int si,ei;

	si=ListPersonNow+1;
	if((ListPersonNow+SET_FACEBLACK_PAGE_MAX_NUM) < ListPersonTotal)
		ei=ListPersonNow+SET_FACEBLACK_PAGE_MAX_NUM ;
	else
		ei=ListPersonTotal;

	//��ѯ���ݿ�
	MySqlIO.FACE_BlackPerson_Read(DBid,si,ei,list_person);

	int nItem;
	int i=0;

	char STR_SEX[3][32] = {"δ֪","����","Ů��"};
	char STR_CARD_TYPE[8][32] = {"δ֪","һ��֤","����֤","ʿ��֤","ѧ��֤","��ʻ֤","����","����"};
	char STR_NATIVE[32][32] = {"����","����","���","����","�㶫","�ӱ�","ɽ��","����","����","������",\
						 "����","�㽭","����","����","����","ɽ��","����","����","����","����",\
						 "�Ĵ�","����","����","����","����","�ຣ","̨��","�½�","����","����",\
						 "���ɹ�","����"};

	list<struct PERSON_BLACK_ST>::iterator beglist;
	
	//struct PERSON_BLACK_ST blackdata={0};

	for(beglist=list_person.begin();beglist!=list_person.end();beglist++)
	{
		sprintf(str,"%07d",ListPersonNow+1+i);
		nItem = m_List_person.InsertItem(0,str);
		i++;

		sprintf(str,"%d",beglist->nid);
		m_List_person.SetItemText(nItem,1,str);
		m_List_person.SetItemText(nItem,2,beglist->name);
		m_List_person.SetItemText(nItem,3,STR_SEX[beglist->sex]);	

		sprintf(str,"%04d-%02d-%02d",		
			beglist->year,
			beglist->mon,
			beglist->day);
		m_List_person.SetItemText(nItem,4,str);
		m_List_person.SetItemText(nItem,5,STR_CARD_TYPE[beglist->cardtype]);
		m_List_person.SetItemText(nItem,6,beglist->cardNO);
		m_List_person.SetItemText(nItem,7,STR_NATIVE[beglist->native]);
		m_List_person.SetItemText(nItem,8,beglist->address);
		sprintf(str,"%d",beglist->RW_personID);
		m_List_person.SetItemText(nItem,9,str);
	}

	if(ListPersonTotal%SET_FACEBLACK_PAGE_MAX_NUM)
	{
		sprintf(str,"��%d�� %d/%dҳ ÿҳ%d��",
			ListPersonTotal,
			ListPersonNow/SET_FACEBLACK_PAGE_MAX_NUM+1,ListPersonTotal/SET_FACEBLACK_PAGE_MAX_NUM+1,SET_FACEBLACK_PAGE_MAX_NUM);
	}
	else
	{
		sprintf(str,"��%d�� %d/%dҳ ÿҳ%d��",
			ListPersonTotal,
			ListPersonNow/SET_FACEBLACK_PAGE_MAX_NUM+1,ListPersonTotal/SET_FACEBLACK_PAGE_MAX_NUM,SET_FACEBLACK_PAGE_MAX_NUM);
	}
	GetDlgItem(IDC_STATIC_INFO)->SetWindowText(str);
	InvalidateRect(printf_Rect, TRUE);

}

void CDLGSetBlackFaceLib::OnBnClickedButtonBlackPersonadd()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CDLGSetBlackFaceEdit  DlgSetBlackFaceEdit;
	char str[260]={0};
	m_List.GetItemText(ListChoose,0,str,260);
	DlgSetBlackFaceEdit.db_id = atoi(str);
	m_List.GetItemText(ListChoose,2,str,260);
	DlgSetBlackFaceEdit.RWdb_id = atoi(str);

	if(DlgSetBlackFaceEdit.DoModal() == IDOK)
	{
		//��������
		DisplayerPersonList();
	}
}

void CDLGSetBlackFaceLib::OnBnClickedButtonBlackPersonmodify()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(-1 == ListPersonChoose)
		return;

	CDLGSetBlackFaceEdit  DlgSetBlackFaceEdit;

	char str[260]={0};
	m_List.GetItemText(ListChoose,0,str,260);
	DlgSetBlackFaceEdit.db_id = atoi(str);
	m_List.GetItemText(ListChoose,2,str,260);
	DlgSetBlackFaceEdit.RWdb_id = atoi(str);
	m_List_person.GetItemText(ListPersonChoose,1,str,260);
	DlgSetBlackFaceEdit.person_id = atoi(str);

	DlgSetBlackFaceEdit.bModifyFlag = true;
	if(DlgSetBlackFaceEdit.DoModal() == IDOK)
	{
		//��������
		DisplayerPersonList();
	}
}

void CDLGSetBlackFaceLib::OnBnClickedButtonBlackPersondelete()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if(-1 == ListPersonChoose)
		return;

	//�����
	CDLGWarnning dlgw;
	dlgw.m_wintxt="ɾ��������";					//���ڱ���
	dlgw.m_warntxt="���ٴ�ȷ���Ƿ�ɾ��";	//��������
	int nResponse=dlgw.DoModal();
	if (nResponse == IDOK)
	{
		char str[260]={0};
#if OPEN_FACEDETECT_CODE
		m_List_person.GetItemText(ListPersonChoose,9,str,260);
		long RWpersonid = atoi(str);
		if(!DlgMain->FaceMng.RWFaceMngPersonDeleteWithID(RWpersonid))//ɾ����Ϊ������Ա,�˽ӿ���ͬʱɾ������
		{
			AfxMessageBox("ɾ��������Աʧ��");
			return;
		}
#endif
		m_List.GetItemText(ListChoose,0,str,260);
		long db_nid = atoi(str);

		m_List_person.GetItemText(ListPersonChoose,1,str,260);
		long nid = atoi(str);

		char cmd[1024]={0};
		sprintf(cmd,"cmd /c rmdir /s /q \"%s\\%d\"",DlgSetSystem.m_path_faceblack,nid);
		WinExec(cmd,SW_HIDE);

		MySqlIO.FACE_BlackPerson_DeleteWithNid(nid);//ɾ�����ݿⲼ����Ա��Ϣ

		//ɾ���ļ�
		MySqlIO.FACE_BlackFace_DeleteWithPersonID(nid);//ɾ�����ݿⲼ��������Ϣ

	}
	else if (nResponse == IDCANCEL)
		return ;
	else
		return ;

	//��������
	DisplayerPersonList();
}
void CDLGSetBlackFaceLib::OnClickPersonList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NM_LISTVIEW* p=	(NM_LISTVIEW *)pNMHDR;
	//ѡ�еĸ�ֵ
	ListPersonChoose= p->iItem;
	//û��
	if(-1 == ListPersonChoose)
	{
		GetDlgItem(IDC_BUTTON_BLACK_PERSONMODIFY)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_BLACK_PERSONDELETE)->EnableWindow(FALSE);
		return ;
	}
	else
	{
		GetDlgItem(IDC_BUTTON_BLACK_PERSONMODIFY)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_BLACK_PERSONDELETE)->EnableWindow(TRUE);
	}

	//����
	UpdateData(FALSE);

	*pResult = 0;
}


void CDLGSetBlackFaceLib::OnButtonFirst() 
{
	// TODO: Add your control notification handler code here
	if(0==ListPersonTotal)
		return ;

	ListPersonNow=0;
	DisplayerPersonList();

}

void CDLGSetBlackFaceLib::OnButtonPrevious() 
{
	// TODO: Add your control notification handler code here
	if(0==ListPersonTotal)
		return ;

	if((ListPersonNow-SET_FACEBLACK_PAGE_MAX_NUM) >= 0)
		ListPersonNow-=SET_FACEBLACK_PAGE_MAX_NUM;

	DisplayerPersonList();

}

void CDLGSetBlackFaceLib::OnButtonNext() 
{
	// TODO: Add your control notification handler code here
	if(0==ListPersonTotal)
		return ;

	if((ListPersonNow+SET_FACEBLACK_PAGE_MAX_NUM) < ListPersonTotal)
		ListPersonNow+=SET_FACEBLACK_PAGE_MAX_NUM;

	DisplayerPersonList();
}

void CDLGSetBlackFaceLib::OnButtonLast() 
{
	// TODO: Add your control notification handler code here
	if(0==ListPersonTotal)
		return ;

	while((ListPersonNow+SET_FACEBLACK_PAGE_MAX_NUM) < ListPersonTotal)
		ListPersonNow+=SET_FACEBLACK_PAGE_MAX_NUM;

	DisplayerPersonList();
}

void CDLGSetBlackFaceLib::OnButtonJump() 
{
	// TODO: Add your control notification handler code here
	if(0==ListPersonTotal)
		return ;

	UpdateData(TRUE);

	if((m_page>=1)
		&& (m_page <= (ListPersonTotal/SET_FACEBLACK_PAGE_MAX_NUM+1))
		)
	{
		ListPersonNow=0;
		while(((ListPersonNow+SET_FACEBLACK_PAGE_MAX_NUM) < ListPersonTotal)
			&& ((ListPersonNow+SET_FACEBLACK_PAGE_MAX_NUM) < (SET_FACEBLACK_PAGE_MAX_NUM*m_page))
			)
			ListPersonNow+=SET_FACEBLACK_PAGE_MAX_NUM;

		DisplayerPersonList();
	}	
	else
		MessageBox("����ҳ�淶Χ",MESSAGEBOX_TITLE);
}


void CDLGSetBlackFaceLib::OnLvnItemActivateListPerson(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here

	CDLGSetBlackFaceEdit  DlgSetBlackFaceEdit;
	char str[260]={0};
	m_List.GetItemText(ListChoose,0,str,260);
	DlgSetBlackFaceEdit.db_id = atoi(str);
	m_List.GetItemText(ListChoose,2,str,260);
	DlgSetBlackFaceEdit.RWdb_id = atoi(str);
	m_List_person.GetItemText(pNMIA->iItem,1,str,260);
	DlgSetBlackFaceEdit.person_id = atoi(str);

	DlgSetBlackFaceEdit.bModifyFlag = true;
	if(DlgSetBlackFaceEdit.DoModal() == IDOK)
	{
		//��������
		DisplayerPersonList();
	}

	*pResult = 0;
}
