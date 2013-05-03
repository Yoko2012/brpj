// DLGOpenClose.cpp : implementation file
//

#include "stdafx.h"
#include "yirongcardetectaio.h"
#include "DLGOpenClose.h"

#include "YiRongCarDetectAIODlg.h"
extern CYiRongCarDetectAIODlg *DlgMain;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDLGOpenClose dialog


CDLGOpenClose::CDLGOpenClose(CWnd* pParent /*=NULL*/)
	: CDialog(CDLGOpenClose::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDLGOpenClose)
	m_check = FALSE;
	m_winno = 0;
	ListChoose=-1;
	//}}AFX_DATA_INIT
	flag=0;
}


void CDLGOpenClose::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDLGOpenClose)
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Check(pDX, IDC_CHECK, m_check);
	DDX_CBIndex(pDX, IDC_COMBO_WINNO, m_winno);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDLGOpenClose, CDialog)
	//{{AFX_MSG_MAP(CDLGOpenClose)
	ON_BN_CLICKED(IDC_CHECK, OnCheck)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnItemchangedList)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, OnButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
	ON_NOTIFY(NM_CLICK, IDC_LIST, OnClickList)
	ON_CBN_CLOSEUP(IDC_COMBO_WINNO, OnCloseupComboWinno)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDLGOpenClose message handlers

BOOL CDLGOpenClose::OnInitDialog()
{
	CDialog::OnInitDialog();

	//��ʼ���б�
	InitList();

	//����Ԥ������ٵ�����
	switch(flag)
	{
	case OPENCLOSE_PREVIEW :
		SetWindowText("����/�ر�Ԥ��");
		GetDlgItem(IDC_STATIC_WINNO)->ShowWindow(TRUE);
		GetDlgItem(IDC_COMBO_WINNO)->ShowWindow(TRUE);
		BuildListPreview();
		break;
	case OPENCLOSE_DETECT :
		SetWindowText("����/�ر�ʶ��");
		GetDlgItem(IDC_STATIC_WINNO)->ShowWindow(FALSE);
		GetDlgItem(IDC_COMBO_WINNO)->ShowWindow(FALSE);
		BuildListDetect();
		break;
	case OPENCLOSE_ALARM :
		SetWindowText("����/�رձ���");
		GetDlgItem(IDC_STATIC_WINNO)->ShowWindow(FALSE);
		GetDlgItem(IDC_COMBO_WINNO)->ShowWindow(FALSE);
		BuildListAlarm();
		break;
	case OPENCLOSE_RECORD :
		SetWindowText("����/�ر�¼��");
		GetDlgItem(IDC_STATIC_WINNO)->ShowWindow(FALSE);
		GetDlgItem(IDC_COMBO_WINNO)->ShowWindow(FALSE);
		BuildListRecord();
		break;
	default:
		MessageBox("BOOL CDLGOpenClose::OnInitDialog error",MESSAGEBOX_TITLE);
		return true;
	}


//	int nItem = m_List.InsertItem(0,"aaa");


	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CDLGOpenClose::OnOK()
{
	// TODO: Add your control notification handler code here
}



void CDLGOpenClose::InitList(void)
{
	m_List.InsertColumn(0, _T("���ں�") , LVCFMT_LEFT, 50);
	m_List.InsertColumn(1, _T("����ͷ����" ), LVCFMT_LEFT, 140);
	m_List.InsertColumn(2, _T("����ͷ����" ), LVCFMT_LEFT, 140);
	m_List.InsertColumn(3, _T("IP��ַ"), LVCFMT_LEFT, 110);
	m_List.InsertColumn(4, _T("��ǰ״̬"), LVCFMT_LEFT, 120);
	m_List.InsertColumn(5, _T("����ͷid"), LVCFMT_LEFT, 0);

	//����ѡ�� LVS_EX_CHECKBOXES
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);
}

void CDLGOpenClose::OnCheck() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	switch(flag)
	{
	case OPENCLOSE_PREVIEW :
		CheckAllListPreview();
		break;
	case OPENCLOSE_DETECT :
		CheckAllListDetect();
		break;
	case OPENCLOSE_ALARM :
		CheckAllListAlarm();
		break;
	case OPENCLOSE_RECORD :
		CheckAllListRecord();
		break;
	default:
		MessageBox("BOOL CDLGOpenClose::OnCheck error",MESSAGEBOX_TITLE);
		return ;
	}
}

///////////////////�����б�//////////////////////
void CDLGOpenClose::BuildListPreview(void)
{
	int nItem;
	char str[32];
	
	int k;
	for(int i=0;i<DlgMain->DlgDeviceTree.iptotal;i++)
	{	
		nItem = m_List.InsertItem(0,"");
		
		m_List.SetItemText(nItem,1,	DlgMain->DlgDeviceTree.iplist[i].area.GetBuffer(0));
		m_List.SetItemText(nItem,2,	DlgMain->DlgDeviceTree.iplist[i].name.GetBuffer(0));
		m_List.SetItemText(nItem,3,	DlgMain->DlgDeviceTree.iplist[i].ip.GetBuffer(0));
		
		k=1;
		for(int j=0;j<MAX_DEVICE_NUM;j++)
		{
			if(DlgMain->DlgScreen.m_videoInfo[j].ip == DlgMain->DlgDeviceTree.iplist[i].ip)
			{
				
				if(DlgMain->DlgScreen.m_videoInfo[j].isplay)
					m_List.SetItemText(nItem,4,"������Ԥ��");
				else
					m_List.SetItemText(nItem,4,"δ����Ԥ��");
				
				sprintf(str,"%02d",j+1);
				m_List.SetItemText(nItem,0,str);
				
				k=0;
				break;
			}
		}
		if(k)
		{
			m_List.SetItemText(nItem,4,"δָ������");
		}
		sprintf(str,"%d",i);
		m_List.SetItemText(nItem,5,str);
	}
}

void CDLGOpenClose::BuildListDetect(void)
{
	int nItem;
	char str[32];

	for(int i=0;i<MAX_DEVICE_NUM;i++)
	{	
		sprintf(str,"%02d",i+1);
		nItem = m_List.InsertItem(0,str);

		if( DlgMain->DlgScreen.m_videoInfo[i].isplay )
		{
			m_List.SetItemText(nItem,1,	DlgMain->DlgScreen.m_videoInfo[i].area.GetBuffer(0));
			m_List.SetItemText(nItem,2,	DlgMain->DlgScreen.m_videoInfo[i].name.GetBuffer(0));
			m_List.SetItemText(nItem,3,	DlgMain->DlgScreen.m_videoInfo[i].ip.GetBuffer(0));
	
			if(DlgMain->DlgScreen.GetDetectState(i))
				m_List.SetItemText(nItem,4,"������ʶ��");
			else
				m_List.SetItemText(nItem,4,"δ����ʶ��");
		}
		else
		{
			m_List.SetItemText(nItem,2,"��δָ������ͷ");
			m_List.SetItemText(nItem,4,"��δ����Ԥ��");
		}
	}
}

void CDLGOpenClose::BuildListAlarm(void)
{
	int nItem;
	char str[32];

	for(int i=0;i<MAX_DEVICE_NUM;i++)
	{	
		sprintf(str,"%02d",i+1);
		nItem = m_List.InsertItem(0,str);

		if( DlgMain->DlgScreen.m_videoInfo[i].isplay )
		{
			m_List.SetItemText(nItem,1,	DlgMain->DlgScreen.m_videoInfo[i].area.GetBuffer(0));
			m_List.SetItemText(nItem,2,	DlgMain->DlgScreen.m_videoInfo[i].name.GetBuffer(0));
			m_List.SetItemText(nItem,3,	DlgMain->DlgScreen.m_videoInfo[i].ip.GetBuffer(0));
	
			if(DlgMain->DlgScreen.GetAlarmState(i))
				m_List.SetItemText(nItem,4,"�����ñ���");
			else
				m_List.SetItemText(nItem,4,"δ���ñ���");
		}
		else
		{
			m_List.SetItemText(nItem,2,"��δָ������ͷ");
			m_List.SetItemText(nItem,4,"��δ����Ԥ��");
		}
	}
}

void CDLGOpenClose::BuildListRecord(void)
{

}
/////////////////ȫѡ�¼�////////////////////////
void CDLGOpenClose::CheckAllListPreview(void)
{
	for(int i=0;i<m_List.GetItemCount();i++)
		m_List.SetCheck(i,m_check);
}

void CDLGOpenClose::CheckAllListDetect(void)
{
	for(int i=0;i<m_List.GetItemCount();i++)
		m_List.SetCheck(i,m_check);
}

void CDLGOpenClose::CheckAllListAlarm(void)
{
	for(int i=0;i<m_List.GetItemCount();i++)
		m_List.SetCheck(i,m_check);
}

void CDLGOpenClose::CheckAllListRecord(void)
{
	for(int i=0;i<m_List.GetItemCount();i++)
		m_List.SetCheck(i,m_check);
}
///////////////////���ð�ť//////////////////////
void CDLGOpenClose::OpenListPreview(void)
{
	UpdateData(TRUE);
	char str[32];
	for(int i=0;i<m_List.GetItemCount();i++)
	{
		if(m_List.GetCheck(i))
		{
			m_List.GetItemText(i,0,str,32);
			if(strlen(str))
			{
				sscanf(str,"%d",&m_winno);
				if(m_winno > MAX_DEVICE_NUM || m_winno <1)
				{
					m_winno=0;
					return;
				}
				else
				{
					m_winno = m_winno - 1;
				}
				if(!(DlgMain->DlgScreen.GetCurWindPlayState(m_winno)))
				{
					m_List.GetItemText(i,5,str,32);
					int camID;
					sscanf(str,"%d",&camID);

					bool ret = DlgMain->DlgScreen.StartPlay(
											DlgMain->DlgDeviceTree.iplist[camID].camID,
											DlgMain->DlgDeviceTree.iplist[camID].area.GetBuffer(0),
											DlgMain->DlgDeviceTree.iplist[camID].name.GetBuffer(0),
											DlgMain->DlgDeviceTree.iplist[camID].ip.GetBuffer(0),
											DlgMain->DlgDeviceTree.iplist[camID].port,
											DlgMain->DlgDeviceTree.iplist[camID].user.GetBuffer(0),
											DlgMain->DlgDeviceTree.iplist[camID].psw.GetBuffer(0),
											m_winno,
											0,
											DlgMain->DlgDeviceTree.iplist[camID].venderID);
					if(ret)
					{
						DlgMain->DlgNormal.ChangePreviewFontPic(true);
						m_List.SetItemText(i,4,"������Ԥ��");
					}
					else
					{
						m_List.SetItemText(i,4,"���������ʧ��");
					}
				}
			}
			else
				m_winno=0;
		}
	}
}

void CDLGOpenClose::OpenListDetect(void)
{
	UpdateData(TRUE);
	for(int i=0;i<m_List.GetItemCount();i++)
	{
		if(m_List.GetCheck(i) 
			&& !DlgMain->DlgScreen.GetDetectState(i)
			&& DlgMain->DlgScreen.GetCurWindPlayState(i))
		{
			DlgMain->DlgScreen.EnableDetect(i,true);
			DlgMain->DlgNormal.ChangeDetectFontPic(true);
			m_List.SetItemText(i,4,"������ʶ��");
		}
	}
}

void CDLGOpenClose::OpenListAlarm(void)
{
	UpdateData(TRUE);
	for(int i=0;i<m_List.GetItemCount();i++)
	{
		if(m_List.GetCheck(i) 
			&& !DlgMain->DlgScreen.GetAlarmState(i)
			&& DlgMain->DlgScreen.GetCurWindPlayState(i))
		{
			DlgMain->DlgScreen.EnableAlarm(i,true);
			DlgMain->DlgNormal.ChangeAlarmFontPic(true);
			m_List.SetItemText(i,4,"�����ñ���");
		}
	}
}

void CDLGOpenClose::OpenListRecord(void)
{

}
/////////////////////�رհ�ť////////////////////
void CDLGOpenClose::CloseListPreview(void)
{
	UpdateData(TRUE);
	char ip[64];
	for(int i=0;i<m_List.GetItemCount();i++)
	{
		if(m_List.GetCheck(i))
		{
			m_List.GetItemText(i,3,ip,64);
			for(int j=0;j<MAX_DEVICE_NUM;j++)
			{
				if(DlgMain->DlgScreen.m_videoInfo[j].ip == ip)
				{
					if(DlgMain->DlgScreen.GetCurWindPlayState(j))
					{
						DlgMain->DlgScreen.StopPlay(j);
						DlgMain->DlgNormal.ChangePreviewFontPic(false);
						m_List.SetItemText(i,4,"δ����Ԥ��");
					}
				}
			}
		}
	}
}

void CDLGOpenClose::CloseListDetect(void)
{
	UpdateData(TRUE);
	for(int i=0;i<m_List.GetItemCount();i++)
	{
		if(m_List.GetCheck(i) 
			&& DlgMain->DlgScreen.GetDetectState(i)
			&& DlgMain->DlgScreen.GetCurWindPlayState(i))
		{
			DlgMain->DlgScreen.EnableDetect(i,false);
			DlgMain->DlgNormal.ChangeDetectFontPic(false);
			m_List.SetItemText(i,4,"δ����ʶ��");
		}
	}
}

void CDLGOpenClose::CloseListAlarm(void)
{
	UpdateData(TRUE);
	for(int i=0;i<m_List.GetItemCount();i++)
	{
		if(m_List.GetCheck(i) 
			&& DlgMain->DlgScreen.GetAlarmState(i)
			&& DlgMain->DlgScreen.GetCurWindPlayState(i))
		{
			DlgMain->DlgScreen.EnableAlarm(i,false);
			DlgMain->DlgNormal.ChangeAlarmFontPic(false);
			m_List.SetItemText(i,4,"δ���ñ���");
		}
	}
}

void CDLGOpenClose::CloseListRecord(void)
{

}
/////////////////////////////////////////
void CDLGOpenClose::OnButtonOpen() 
{
	// TODO: Add your control notification handler code here
	switch(flag)
	{
	case OPENCLOSE_PREVIEW :
		OpenListPreview();
		break;
	case OPENCLOSE_DETECT :
		OpenListDetect();
		break;
	case OPENCLOSE_ALARM :
		OpenListAlarm();
		break;
	case OPENCLOSE_RECORD :
		OpenListRecord();
		break;
	default:
		MessageBox("BOOL CDLGOpenClose::OnButtonOpen error",MESSAGEBOX_TITLE);
		return ;
	}
}


void CDLGOpenClose::OnButtonClose() 
{
	// TODO: Add your control notification handler code here
	switch(flag)
	{
	case OPENCLOSE_PREVIEW :
		CloseListPreview();
		break;
	case OPENCLOSE_DETECT :
		CloseListDetect();
		break;
	case OPENCLOSE_ALARM :
		CloseListAlarm();
		break;
	case OPENCLOSE_RECORD :
		CloseListRecord();
		break;
	default:
		MessageBox("BOOL CDLGOpenClose::OnButtonClose error",MESSAGEBOX_TITLE);
		return ;
	}
	
}
//רΪ�����ر�Ԥ����д
void CDLGOpenClose::OnClickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);
	// TODO: Add your control notification handler code here
	NM_LISTVIEW* p=	(NM_LISTVIEW *)pNMHDR;

	char str[32];
	ListChoose=p->iItem;
	//ѡ�еĸ�ֵ
	if(p->iItem < 0 )
		m_winno = 0;
	else
	{
		m_List.GetItemText(p->iItem,0,str,32);
		if(strlen(str))
		{
			sscanf(str,"%d",&m_winno);
			if(m_winno >MAX_DEVICE_NUM || m_winno <1)
				m_winno=0;
		}
		else
			m_winno=0;
	}

	//����
	UpdateData(FALSE);

	*pResult = 0;
}
//רΪ�����ر�Ԥ����д
void CDLGOpenClose::OnCloseupComboWinno() 
{
	UpdateData(TRUE);

	char str[32];
	char nostr[32];

	if(m_winno>0)
	{
		sprintf(nostr,"%02d",m_winno);
		
		// TODO: Add your control notification handler code here
		for(int i=0;i<m_List.GetItemCount();i++)
		{
			m_List.GetItemText(i,0,str,256);
			if(0==strcmp(str,nostr)
				&& strlen(str))
			{
				MessageBox("���ں��Ѿ������䣬����ѡ���ں�",MESSAGEBOX_TITLE);
				return ;
			}
		}
		m_List.SetItemText(ListChoose,0,nostr);
	}
	else
		m_List.SetItemText(ListChoose,0,"");

}


////////////���´��� ��ʱ��Ч//////////////////
void CDLGOpenClose::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if((pNMListView->uOldState & INDEXTOSTATEIMAGEMASK(1)) /* old state : unchecked */ 
		&& (pNMListView->uNewState & INDEXTOSTATEIMAGEMASK(2)) /* new state : checked */ 
		) 
	{ //����
	//	m_List.GetCheck(pNMListView->iItem);
	//	m_List.SetItemText(pNMListView->iItem,0,"1");

		switch(flag)
		{
		case OPENCLOSE_PREVIEW :
			CheckOneListPreview(pNMListView->iItem);
			break;
		case OPENCLOSE_DETECT :
			CheckOneListDetect(pNMListView->iItem);
			break;
		case OPENCLOSE_ALARM :
			CheckOneListAlarm(pNMListView->iItem);
			break;
		case OPENCLOSE_RECORD :
			CheckOneListRecord(pNMListView->iItem);
			break;
		default:
			MessageBox("BOOL CDLGOpenClose::OnItemchangedList 1 error",MESSAGEBOX_TITLE);
			return ;
		}
	} 
	else if((pNMListView->uOldState & INDEXTOSTATEIMAGEMASK(2)) /* old state : checked */ 
		&& (pNMListView->uNewState & INDEXTOSTATEIMAGEMASK(1)) /* new state : unchecked */ 
		) 
	{ //����
	//	m_List.GetCheck(pNMListView->iItem);
	//	m_List.SetItemText(pNMListView->iItem,0,"2");

		switch(flag)
		{
		case OPENCLOSE_PREVIEW :
			CheckOneListPreview(pNMListView->iItem);
			break;
		case OPENCLOSE_DETECT :
			CheckOneListDetect(pNMListView->iItem);
			break;
		case OPENCLOSE_ALARM :
			CheckOneListAlarm(pNMListView->iItem);
			break;
		case OPENCLOSE_RECORD :
			CheckOneListRecord(pNMListView->iItem);
			break;
		default:
			MessageBox("BOOL CDLGOpenClose::OnItemchangedList 2 error",MESSAGEBOX_TITLE);
			return ;
		}
	} 
	
	*pResult = 0;
}

///////////////////�������¼�//////////////////////
void CDLGOpenClose::CheckOneListPreview(int iItem)
{

}

void CDLGOpenClose::CheckOneListDetect(int iItem)
{

}

void CDLGOpenClose::CheckOneListAlarm(int iItem)
{

}

void CDLGOpenClose::CheckOneListRecord(int iItem)
{

}
