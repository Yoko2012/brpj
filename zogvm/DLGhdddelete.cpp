// DLGhdddelete.cpp : implementation file
//

#include "stdafx.h"
#include "zogvm.h"
#include "DLGhdddelete.h"

extern CSqliteOperate SQLDB;
// CDLGhdddelete dialog

IMPLEMENT_DYNAMIC(CDLGhdddelete, CDialog)

CDLGhdddelete::CDLGhdddelete(CWnd* pParent /*=NULL*/)
	: CDialog(CDLGhdddelete::IDD, pParent)
{
	m_check = FALSE;
}

CDLGhdddelete::~CDLGhdddelete()
{
}

void CDLGhdddelete::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Check(pDX, IDC_CHECK, m_check);
}


BEGIN_MESSAGE_MAP(CDLGhdddelete, CDialog)
		ON_BN_CLICKED(IDC_CHECK, OnCheck)
		ON_BN_CLICKED(IDC_BUTTON_DELETE_DOUBLE, &CDLGhdddelete::OnBnClickedButtonDeleteDouble)
END_MESSAGE_MAP()


// CDLGhdddelete message handlers

BOOL CDLGhdddelete::OnInitDialog()
{
	CDialog::OnInitDialog();


	m_list.InsertColumn(0, _T("�������к�") , LVCFMT_LEFT, 80);
	m_list.InsertColumn(1, _T("����") , LVCFMT_LEFT, 40);
	m_list.InsertColumn(2, _T("��ǩ") , LVCFMT_LEFT, 150);
	m_list.InsertColumn(3, _T("�ܿռ�") , LVCFMT_LEFT, 70);
	m_list.InsertColumn(4, _T("ʣ��ռ�") , LVCFMT_LEFT, 70);
	m_list.InsertColumn(5, _T("�Ƿ�Ӳ�") , LVCFMT_LEFT, 60);
	m_list.InsertColumn(6, _T("nid") , LVCFMT_LEFT, 0);

	//����ѡ�� LVS_EX_CHECKBOXES
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);



	DisplayerList() ;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDLGhdddelete::DisplayerList() 
{
	hddList.clear();
	SQLDB.Hdd_Read(hddList);
	m_list.DeleteAllItems();

	char str[32];
	int i=0;
	list<struct HDD_ST>::iterator beglist;

	for(beglist=hddList.begin();beglist!=hddList.end();beglist++)
	{
		m_list.InsertItem(i,beglist->serno);

		m_list.SetItemText(i,1,beglist->area);
		m_list.SetItemText(i,2,beglist->mark);

		sprintf(str,"%.3fG",(double)(beglist->TotalBytes/1024/1024)/1024.0);
		m_list.SetItemText(i,3,str);
		sprintf(str,"%.3fG",(double)(beglist->FreeBytes/1024/1024)/1024.0);
		m_list.SetItemText(i,4,str);

		if(beglist->insertflag)
			m_list.SetItemText(i,5,"����<--");
		else
			m_list.SetItemText(i,5,"�ѻ�-->");

		sprintf(str,"%d",beglist->hdd_nid);
		m_list.SetItemText(i,6,str);

		i++;
	}
}

void CDLGhdddelete::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	int i;

	char str[32];
	int check;

		SQLDB.Begin();
	for( i=0;i<m_list.GetItemCount();i++)
	{
		m_list.GetItemText(i,6,str,32);
		check=m_list.GetCheck(i);

		if(check)
		{
			SQLDB.File_DeleteforHdd(_atoi64(str));
			SQLDB.Hdd_DeleteforHdd(_atoi64(str));
		}
	}
		SQLDB.Commit();

	MessageBox("ɾ�����",NULL);

	hddList.clear();
	SQLDB.Hdd_Read(hddList);
	DisplayerList() ;

}

void CDLGhdddelete::OnCancel() 
{
	// TODO: Add extra cleanup here
	hddList.clear();
	CDialog::OnCancel();
}

void CDLGhdddelete::OnCheck() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	// TODO: Add your control notification handler code here
	for(int i=0;i<m_list.GetItemCount();i++)
		m_list.SetCheck(i,m_check);
}


void CDLGhdddelete::OnBnClickedButtonDeleteDouble()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

		SQLDB.Begin();
	SQLDB.Double_DeleteAll();
	SQLDB.File_CleanDouble2Zero();
			SQLDB.Commit();

	MessageBox("ɾ�����",NULL);
}
