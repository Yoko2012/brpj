// DLGSetBlack.cpp : implementation file
//

#include "stdafx.h"
#include "yirongcardetectaio.h"
#include "DLGSetBlack.h"

#include "DLGBlackInOut.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "DLGWarnning.h"

extern IO OracleIO;
/////////////////////////////////////////////////////////////////////////////
// CDLGSetBlack dialog

CDLGSetBlack::CDLGSetBlack(CWnd* pParent /*=NULL*/)
	: CDialog(CDLGSetBlack::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDLGSetBlack)
	m_Brand = _T("");
	m_Name = _T("");
	m_Phone = _T("");
	m_Plate = _T("");
	m_Other = _T("");
	m_page = 0;
	//}}AFX_DATA_INIT
	ListChoose=-1;
}


void CDLGSetBlack::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDLGSetBlack)
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Text(pDX, IDC_EDIT_BLACK_BRAND, m_Brand);
	DDV_MaxChars(pDX, m_Brand, 256);
	DDX_Text(pDX, IDC_EDIT_BLACK_NAME, m_Name);
	DDV_MaxChars(pDX, m_Name,256);
	DDX_Text(pDX, IDC_EDIT_BLACK_PHONE, m_Phone);
	DDV_MaxChars(pDX, m_Phone, 256);
	DDX_Text(pDX, IDC_EDIT_BLACK_PLATE, m_Plate);
	DDV_MaxChars(pDX, m_Plate, 256);
	DDX_Text(pDX, IDC_EDIT_OTHER, m_Other);
	DDV_MaxChars(pDX, m_Other, 1024);
	DDX_Text(pDX, IDC_EDIT_PAGE, m_page);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDLGSetBlack, CDialog)
	//{{AFX_MSG_MAP(CDLGSetBlack)
	ON_BN_CLICKED(IDC_BUTTON_JUMP, OnButtonJump)
	ON_BN_CLICKED(IDC_BUTTON_FIRST, OnButtonFirst)
	ON_BN_CLICKED(IDC_BUTTON_PREVIOUS, OnButtonPrevious)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_LAST, OnButtonLast)
	ON_BN_CLICKED(IDC_BUTTON_BLACK_ADD, OnButtonBlackAdd)
	ON_BN_CLICKED(IDC_BUTTON_BLACK_MODIFY, OnButtonBlackModify)
	ON_BN_CLICKED(IDC_BUTTON_BLACK_DELETE, OnButtonBlackdelete)
	ON_BN_CLICKED(IDC_BUTTON_BLACK_INPUT, OnButtonBlackInput)
	ON_BN_CLICKED(IDC_BUTTON_BLACK_OUPUT, OnButtonBlackOuput)
	ON_BN_CLICKED(IDC_BUTTON_BLACK_CLEAN, OnButtonBlackClean)
	ON_NOTIFY(NM_CLICK, IDC_LIST, OnClickList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDLGSetBlack message handlers
BOOL CDLGSetBlack::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_List.InsertColumn(0, _T("���") , LVCFMT_LEFT, 50);
	m_List.InsertColumn(1, _T("����Ʒ��" ), LVCFMT_LEFT, 100);
	m_List.InsertColumn(2, _T("���ƺ�" ), LVCFMT_LEFT, 100);
	m_List.InsertColumn(3, _T("ʧ������" ), LVCFMT_LEFT, 100);
	m_List.InsertColumn(4, _T("��ϵ�绰" ), LVCFMT_LEFT, 120);
	m_List.InsertColumn(5, _T("������Ϣ" ), LVCFMT_LEFT, 200);
	m_List.InsertColumn(6, _T("id" ), LVCFMT_LEFT, 0);

	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	//��������
	reflush();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDLGSetBlack::OnOK()
{
	// TODO: Add your control notification handler code here
}

void CDLGSetBlack::OnButtonBlackAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if(m_Plate.IsEmpty())
	{
		MessageBox("���ƺŲ�Ϊ��",MESSAGEBOX_TITLE);
		return ;
	}
	//�������ݿ�
	M2Struct();

#if ALLTAB_DETECT_CAR_MODE
	if(!OracleIO.CAR_BlackTable_AddNew(data))
#else
	if(!OracleIO.ELECAR_BlackTable_AddNew(data))
#endif
	{
		MessageBox("���ݿ�����޷�����",MESSAGEBOX_TITLE);
		return ;
	}
	else
	{
		MessageBox("��ӳɹ�",MESSAGEBOX_TITLE);
	}

	//��������
	reflush();
}

void CDLGSetBlack::OnButtonBlackModify() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if(m_Plate.IsEmpty())
	{
		MessageBox("���ƺŲ�Ϊ��",MESSAGEBOX_TITLE);
		return ;
	}
	//�������ݿ�
	M2Struct();

#if ALLTAB_DETECT_CAR_MODE
	if(!OracleIO.CAR_BlackTable_Edit(data))
#else
	if(!OracleIO.ELECAR_BlackTable_Edit(data))
#endif
	{
		MessageBox("���ݿ�����޷��޸�",MESSAGEBOX_TITLE);
		return ;
	}
	else
	{
		MessageBox("�޸ĳɹ�",MESSAGEBOX_TITLE);
	}

	//��������
	reflush();
}

void CDLGSetBlack::OnButtonBlackdelete() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	//�����
	CDLGWarnning dlgw;
	dlgw.m_wintxt="ɾ��������";					//���ڱ���
	dlgw.m_warntxt="���ٴ�ȷ���Ƿ�ɾ��";	//��������
	int nResponse=dlgw.DoModal();
	if (nResponse == IDOK)
	{
		///ɾ��
#if ALLTAB_DETECT_CAR_MODE
		if(!OracleIO.CAR_BlackTable_DeleteWithNid(data.nid))
#else
		if(!OracleIO.ELECAR_BlackTable_DeleteWithNid(data.nid))
#endif
		{
			MessageBox("���ݿ�����޷�ɾ��",MESSAGEBOX_TITLE);
			return ;
		}
		else
		{
			MessageBox("ɾ���ɹ�",MESSAGEBOX_TITLE);
		}
	}
	else if (nResponse == IDCANCEL)
		return ;
	else
		return ;

	//��������
	reflush();
}

void CDLGSetBlack::OnButtonBlackInput() 
{
	// TODO: Add your control notification handler code here
	
	char szFilter[]="utf8 xml Files (*.xml)|*.xml|*.*||";
	CFileDialog dlg(TRUE,"xml","",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		szFilter);
	if(dlg.DoModal()==IDOK)
	{
		CDLGBlackInOut dlgBlackInout;
		dlgBlackInout.flag=BLACK_INOUT_INPUT;
		strcpy(dlgBlackInout.path,dlg.GetPathName().GetBuffer(0));
		dlgBlackInout.DoModal();
		reflush();
	}
}

void CDLGSetBlack::BlackInput() 
{
	// TODO: Add your control notification handler code here
	
	char szFilter[]="utf8 xml Files (*.xml)|*.xml|*.*||";
	CFileDialog dlg(TRUE,"xml","",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		szFilter);
	if(dlg.DoModal()==IDOK)
	{
		CDLGBlackInOut dlgBlackInout;
		dlgBlackInout.flag=BLACK_INOUT_INPUT;
		strcpy(dlgBlackInout.path,dlg.GetPathName().GetBuffer(0));
		dlgBlackInout.DoModal();
	}
}

void CDLGSetBlack::OnButtonBlackOuput() 
{
	// TODO: Add your control notification handler code here
	//�����ļ�
	char szFilter[]="utf8 xml Files (*.xml)|*.xml|*.*||";
	CFileDialog dlg(FALSE,"xml","",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		szFilter);
	if(dlg.DoModal()==IDOK)
	{
		CDLGBlackInOut dlgBlackInout;
		dlgBlackInout.flag=BLACK_INOUT_OUTPUT;
		strcpy(dlgBlackInout.path,dlg.GetPathName().GetBuffer(0));
		dlgBlackInout.DoModal();
		reflush();
	}
}

void CDLGSetBlack::BlackOuput() 
{
	// TODO: Add your control notification handler code here
	//�����ļ�
	char szFilter[]="utf8 xml Files (*.xml)|*.xml|*.*||";
	CFileDialog dlg(FALSE,"xml","",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		szFilter);
	if(dlg.DoModal()==IDOK)
	{
		CDLGBlackInOut dlgBlackInout;
		dlgBlackInout.flag=BLACK_INOUT_OUTPUT;
		strcpy(dlgBlackInout.path,dlg.GetPathName().GetBuffer(0));
		dlgBlackInout.DoModal();
	}
}

void CDLGSetBlack::OnButtonBlackClean() 
{
	// TODO: Add your control notification handler code here
	CDLGWarnning dlgw;
	dlgw.m_wintxt="������������վ���";
	dlgw.m_warntxt="���ݽ������";
	int nResponse=dlgw.DoModal();
	if (nResponse == IDOK)
	{

#if ALLTAB_DETECT_CAR_MODE
		OracleIO.CAR_BlackTable_DeleteAll();
#else
		OracleIO.ELECAR_BlackTable_DeleteAll();
#endif
		//��������
		reflush();
	}
	else if (nResponse == IDCANCEL)
		return ;
	else
		return ;
}


void CDLGSetBlack::OnButtonFirst() 
{
	// TODO: Add your control notification handler code here
	if(0==ListTotal)
		return ;

	ListNow=0;
	DisplayerList();
	
}

void CDLGSetBlack::OnButtonPrevious() 
{
	// TODO: Add your control notification handler code here
	if(0==ListTotal)
		return ;

	if((ListNow-SET_BLACK_PAGE_MAX_NUM) >= 0)
		ListNow-=SET_BLACK_PAGE_MAX_NUM;

	DisplayerList();

}

void CDLGSetBlack::OnButtonNext() 
{
	// TODO: Add your control notification handler code here
	if(0==ListTotal)
		return ;

	if((ListNow+SET_BLACK_PAGE_MAX_NUM) < ListTotal)
		ListNow+=SET_BLACK_PAGE_MAX_NUM;

	DisplayerList();
}

void CDLGSetBlack::OnButtonLast() 
{
	// TODO: Add your control notification handler code here
	if(0==ListTotal)
		return ;

	while((ListNow+SET_BLACK_PAGE_MAX_NUM) < ListTotal)
		ListNow+=SET_BLACK_PAGE_MAX_NUM;

	DisplayerList();
}

void CDLGSetBlack::OnButtonJump() 
{
	// TODO: Add your control notification handler code here
	if(0==ListTotal)
		return ;

	UpdateData(TRUE);

	if((m_page>=1)
		&& (m_page <= (ListTotal/SET_BLACK_PAGE_MAX_NUM+1))
		)
	{
		ListNow=0;
		while(((ListNow+SET_BLACK_PAGE_MAX_NUM) < ListTotal)
			&& ((ListNow+SET_BLACK_PAGE_MAX_NUM) < (SET_BLACK_PAGE_MAX_NUM*m_page))
			)
			ListNow+=SET_BLACK_PAGE_MAX_NUM;

		DisplayerList();
	}	
	else
		MessageBox("����ҳ�淶Χ",MESSAGEBOX_TITLE);
}

void CDLGSetBlack::OnClickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NM_LISTVIEW* p=	(NM_LISTVIEW *)pNMHDR;
	//ѡ�еĸ�ֵ
	ListChoose= p->iItem;
	//û��
	if(-1 == ListChoose)
		return ;
	//��ʾ
	char str[ZOG_MAX_PATH_STR];
	m_List.GetItemText(ListChoose,1,data.brand,256);
	m_List.GetItemText(ListChoose,2,data.plate,256);
	m_List.GetItemText(ListChoose,3,data.name,256);
	m_List.GetItemText(ListChoose,4,data.Phone,256);
	m_List.GetItemText(ListChoose,5,data.other,1024);

	m_List.GetItemText(ListChoose,6,str,ZOG_MAX_PATH_STR);
	sscanf(str,"%d",&(data.nid));

	Struct2M();

	if(-1!=ListChoose)
	{
		GetDlgItem(IDC_BUTTON_BLACK_MODIFY)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_BLACK_DELETE)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_BLACK_MODIFY)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_BLACK_DELETE)->EnableWindow(FALSE);
	}

	//����
	UpdateData(FALSE);

	*pResult = 0;
}

void CDLGSetBlack::reflush() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	ListTotal=0;

#if ALLTAB_DETECT_CAR_MODE
	ListTotal=OracleIO.CAR_BlackTable_GetNum();
#else
	ListTotal=OracleIO.ELECAR_BlackTable_GetNum();
#endif

	ListNow=0;

	DisplayerList();
}

void CDLGSetBlack::DisplayerList(void)
{
	list_black.clear();
	m_List.DeleteAllItems();
	GetDlgItem(IDC_STATIC_INFO)->SetWindowText("��0�� 1/1ҳ");
	ListChoose=-1;
	Clear();

	if(0==ListTotal)
		return ;

	unsigned long int si,ei;

	si=ListNow+1;
	if((ListNow+SET_BLACK_PAGE_MAX_NUM) < ListTotal)
		ei=ListNow+SET_BLACK_PAGE_MAX_NUM ;
	else
		ei=ListTotal;

	//��ѯ���ݿ�
#if ALLTAB_DETECT_CAR_MODE
	OracleIO.CAR_BlackTable_Read(si,ei,list_black);
#else
	OracleIO.ELECAR_BlackTable_Read(si,ei,list_black);
#endif

	int nItem;
	char str[128];
	int i=0;

	list<struct BLACK_DATA_ST>::iterator beglist;

	for(beglist=list_black.begin();beglist!=list_black.end();beglist++)
	{
		sprintf(str,"%07d",ListNow+1+i);
		nItem = m_List.InsertItem(0,str);
		i++;

		m_List.SetItemText(nItem,1,beglist->brand);
		m_List.SetItemText(nItem,2,beglist->plate);
		m_List.SetItemText(nItem,3,beglist->name);
		m_List.SetItemText(nItem,4,beglist->Phone);
		m_List.SetItemText(nItem,5,beglist->other);
		
		sprintf(str,"%d",beglist->nid);
		m_List.SetItemText(nItem,6,str);
	}

	if(ListTotal%SET_BLACK_PAGE_MAX_NUM)
	{
		sprintf(str,"��%d�� %d/%dҳ",
			ListTotal,
			ListNow/SET_BLACK_PAGE_MAX_NUM+1,ListTotal/SET_BLACK_PAGE_MAX_NUM+1);
	}
	else
	{
		sprintf(str,"��%d�� %d/%dҳ",
			ListTotal,
			ListNow/SET_BLACK_PAGE_MAX_NUM+1,ListTotal/SET_BLACK_PAGE_MAX_NUM);
	}
	GetDlgItem(IDC_STATIC_INFO)->SetWindowText(str);

	if(-1!=ListChoose)
	{
		GetDlgItem(IDC_BUTTON_BLACK_MODIFY)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_BLACK_DELETE)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_BLACK_MODIFY)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_BLACK_DELETE)->EnableWindow(FALSE);
	}
}

void CDLGSetBlack::Clear() 
{
	m_Brand = _T("");
	m_Name = _T("");
	m_Phone = _T("");
	m_Plate = _T("");
	m_Other = _T("");
	UpdateData(FALSE);
}

void CDLGSetBlack::Struct2M(void)
{
	m_Brand=data.brand;
	m_Name =data.name;
	m_Phone = data.Phone;
	m_Plate = data.plate;
	m_Other = data.other;
}

void CDLGSetBlack::M2Struct(void)
{
	strcpy(data.brand,m_Brand.GetBuffer(0));
	strcpy(data.name,m_Name.GetBuffer(0));
	strcpy(data.Phone,m_Phone.GetBuffer(0));
	strcpy(data.plate,m_Plate.GetBuffer(0));
	strcpy(data.other,m_Other.GetBuffer(0));
}