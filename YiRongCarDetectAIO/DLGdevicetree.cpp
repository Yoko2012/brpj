// DLGdevicetree.cpp : implementation file
//

#include "stdafx.h"
#include "YiRongCarDetectAIO.h"
#include "DLGdevicetree.h"
#include "YiRongCarDetectAIODlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////lynn/////////////////
extern IO OracleIO;
extern CYiRongCarDetectAIODlg *DlgMain;
////////////////lynn/////////////////
#include "DLGLogin.h"
extern CDLGLogin DlgLogin;

/////////////////////////////////////////////////////////////////////////////
// CDLGdevicetree dialog


CDLGdevicetree::CDLGdevicetree(CWnd* pParent /*=NULL*/)
	: CDialog(CDLGdevicetree::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDLGdevicetree)
		// NOTE: the ClassWizard will add member initialization here
	m_selectItem = NULL;
	iptotal = 0;
	//}}AFX_DATA_INIT
}


void CDLGdevicetree::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDLGdevicetree)
	DDX_Control(pDX, IDC_TREE_DEVICE, m_DeviceTree);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDLGdevicetree, CDialog)
	//{{AFX_MSG_MAP(CDLGdevicetree)
	ON_WM_PAINT()
	ON_NOTIFY(NM_RCLICK, IDC_TREE_DEVICE, OnRclickTreeDevice)
	ON_COMMAND(ID_MENUITEM_ADDDEVICE, OnMenuitemAdddevice)
	ON_COMMAND(ID_MENUITEM_EDITDEVICE, OnMenuitemEdit)
	ON_COMMAND(ID_MENUITEM_DELETEDEVICE, OnMenuitemDeleteDevice)
	ON_COMMAND(ID_MENUITEM_DELETEAREA, OnMenuitemDeletearea)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_DEVICE, OnDblclkTreeDevice)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDLGdevicetree message handlers
BOOL CDLGdevicetree::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_DeviceTree.SetBkColor(RGB(232,248,254));

	OnMenuitemUpdate();

	//�������
	AutoSize();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDLGdevicetree::AutoSize()
{
	CRect rc(0, 0, 0, 0);
	GetClientRect(&rc);
//	GetParent()->GetClientRect(&rc);
//	((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
//	MoveWindow(rc);

	//��
	CRect tree_Rect;
	tree_Rect.top = rc.top+5;
	tree_Rect.bottom = rc.bottom -5;
	tree_Rect.left = rc.left+5;
	tree_Rect.right = rc.right-5;
	m_DeviceTree.MoveWindow(tree_Rect);

	Invalidate();
}



void CDLGdevicetree::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
	//������ͼ	
	CRect    rect;     
	GetClientRect(&rect);     
	
	//����Դ������λͼ     
	CBitmap    bitmap;     
	bitmap.LoadBitmap(IDB_BACK_TREE);    
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

void CDLGdevicetree::OnRclickTreeDevice(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CPoint point;
	CMenu menu;
	CMenu *ptrMenu;

	GetCursorPos(&point);
	CPoint PointInTree = point;
	m_DeviceTree.ScreenToClient( &PointInTree);
	UINT nFlag = TVHT_ONITEM;// ���� m_DeviceTree ���һ�ʱ
	m_selectItem = m_DeviceTree.HitTest( PointInTree, &nFlag );

// lynn 20130419 �����޸� ����ʱ�޷��һ���BUG
//	if(m_selectItem != NULL)
	{
		if(m_DeviceTree.GetParentItem(m_selectItem) == NULL)
		{
			menu.LoadMenu(IDR_MENU_RCTREE);
			ptrMenu=menu.GetSubMenu(0);
			ptrMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this,NULL);
		}
		else
		{
			menu.LoadMenu(IDR_MENU_RCTREE1);
			ptrMenu=menu.GetSubMenu(0);
			ptrMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this,NULL);	
		}
	}
	*pResult = 0;
}

void CDLGdevicetree::OnMenuitemAdddevice() 
{
	if(!DlgLogin.CurrentUser.device)
	{
		MessageBox("�� �豸���� Ȩ�ޣ�����ϵ����Ա",MESSAGEBOX_TITLE);
		return ;
	}

	// TODO: Add your command handler code here
	HTREEITEM Item = m_DeviceTree.GetRootItem();
	int count = 0;
	while(Item != NULL)
	{
		if(Item == m_selectItem)
			break;
		Item = m_DeviceTree.GetNextItem(Item,TVGN_NEXT);
		count++;
	}
	DlgAddDevice.AreaComboCur = count;
	if(DlgAddDevice.DoModal() == IDOK)
	{
		//HTREEITEM Item;
		//Item = m_DeviceTree.GetRootItem();
		//for(int i=0;i<DlgAddDevice.AreaComboCur;i++)
		//{
		//	Item = m_DeviceTree.GetNextItem(Item,TVGN_NEXT);
		//}
		//m_DeviceTree.InsertItem(DlgAddDevice.m_CamName,Item);
		if(DlgAddDevice.AddAreaFlag)
		{
			m_DeviceTree.InsertItem(DlgAddDevice.m_AddArea,TVI_ROOT);
			OracleIO.DEVICE_AddNewArea(DlgAddDevice.m_AddArea);
			DlgAddDevice.AddAreaFlag = false;
		}
		else
		{
			OracleIO.DEVICE_AddNewCamera(DlgAddDevice.m_CamArea,\
				DlgAddDevice.m_CamName,\
				DlgAddDevice.m_CamIpAddr,\
				DlgAddDevice.m_CamPort,\
				DlgAddDevice.m_CamUser,\
				DlgAddDevice.m_CamPsw,
				DlgAddDevice.VenderComboCur);
		}
		OnMenuitemUpdate();
	}
}

void CDLGdevicetree::OnMenuitemUpdate() 
{
	// TODO: Add your command handler code here
	vector<struct DEVICE_AREA_ST> OrgName;
	vector<IPLIST> CameraList;
	//�����ݿ����е�����
	OracleIO.DEVICE_ReadAllOrgName(OrgName);
	HTREEITEM hItem;
	HTREEITEM childItem;
	DlgAddDevice.AreaCount = OrgName.size();
	iptotal = 0;

	//ɾ�����е���
	m_DeviceTree.DeleteAllItems();
	for(int i=0;i<OrgName.size();i++)
	{
		if(i == MAX_AREA)
		{
			MessageBox("��������������ƣ����������ֽ�����ʾ",MESSAGEBOX_TITLE);
			break;
		}
		strcpy(DlgAddDevice.AreaList[i].name, OrgName[i].name);
		DlgAddDevice.AreaList[i].nid = OrgName[i].nid;
		hItem = m_DeviceTree.InsertItem(OrgName[i].name,TVI_ROOT);		//�ڸ�������������
		CameraList.clear();
		OracleIO.DEVICE_ReadCameraInfo(OrgName[i].name,CameraList);
		for(int j=0;j<CameraList.size();j++)
		{
			iplist[iptotal].area = CameraList[j].area;
			iplist[iptotal].camID = CameraList[j].camID;
			iplist[iptotal].ip = CameraList[j].ip;
			iplist[iptotal].name = CameraList[j].name;
			iplist[iptotal].port = CameraList[j].port;
			iplist[iptotal].psw = CameraList[j].psw;
			iplist[iptotal].user = CameraList[j].user;
			iplist[iptotal].Parent_item = hItem;
			iplist[iptotal].venderID = CameraList[j].venderID;
			childItem = m_DeviceTree.InsertItem(iplist[iptotal].name,hItem);		//����豸�ڵ�
			iplist[iptotal].item = childItem;
			iptotal++;
		}
	}
}


void CDLGdevicetree::OnMenuitemEdit() 
{
	if(!DlgLogin.CurrentUser.device)
	{
		MessageBox("�� �豸���� Ȩ�ޣ�����ϵ����Ա",MESSAGEBOX_TITLE);
		return ;
	}

	// TODO: Add your command handler code here
	if(m_DeviceTree.GetParentItem(m_selectItem) == NULL)		//�༭����Ԥ��
	{
		HTREEITEM Item;
		Item = m_DeviceTree.GetRootItem();
		while(Item != NULL)
		{
			if(m_selectItem == Item)
			{
				//�༭����
				break;
			}
			Item = m_DeviceTree.GetNextItem(Item,TVGN_NEXT);
		}
	}
	else														//�༭�豸
	{
		for(int i=0;i<1024;i++)
		{
			if(iplist[i].item == m_selectItem)
			{
				HTREEITEM Item;
				Item = m_DeviceTree.GetRootItem();
				int count=0;
				while(Item != NULL)
				{
					if(iplist[i].Parent_item == Item)			//��ȡ���ǵڼ������ڵ�
						break;
					count++;
					Item = m_DeviceTree.GetNextItem(Item,TVGN_NEXT);
				}
				DlgAddDevice.AreaComboCur = count;
				DlgAddDevice.m_CamPort = iplist[i].port;
				DlgAddDevice.m_CamIpAddr = iplist[i].ip;
				DlgAddDevice.m_CamName = iplist[i].name;
				DlgAddDevice.m_CamPsw = iplist[i].psw;
				DlgAddDevice.m_CamUser = iplist[i].user;
				DlgAddDevice.VenderComboCur = iplist[i].venderID;
				if(DlgAddDevice.DoModal() == IDOK)
				{
					OracleIO.DEVICE_UpdateCameraInfo(iplist[i].camID,\
						DlgAddDevice.m_CamArea,\
						DlgAddDevice.m_CamName,\
						DlgAddDevice.m_CamIpAddr,\
						DlgAddDevice.m_CamPort,\
						DlgAddDevice.m_CamUser,\
						DlgAddDevice.m_CamPsw,\
						DlgAddDevice.VenderComboCur);
					OnMenuitemUpdate();
				}
				break;
			}
		}

	}	
}

void CDLGdevicetree::OnMenuitemDeleteDevice() 
{
	if(!DlgLogin.CurrentUser.device)
	{
		MessageBox("�� �豸���� Ȩ�ޣ�����ϵ����Ա",MESSAGEBOX_TITLE);
		return ;
	}

	// TODO: Add your command handler code here
	int i;
	for(i=0;i<1024;i++)
	{
		if(iplist[i].item == m_selectItem)
		{
			break;
		}
	}
	DlgMain->DlgScreen.DeleteDevice(iplist[i].ip);
	OracleIO.DEVICE_DeleteCamera(iplist[i].camID);
	OnMenuitemUpdate();
}

void CDLGdevicetree::OnMenuitemDeletearea() 
{
	if(!DlgLogin.CurrentUser.device)
	{
		MessageBox("�� �豸���� Ȩ�ޣ�����ϵ����Ա",MESSAGEBOX_TITLE);
		return ;
	}

	// TODO: Add your command handler code here
	HTREEITEM Item;
	int ItemCount=0;
	Item = m_DeviceTree.GetRootItem();
	while(Item != NULL)
	{
		if(m_selectItem == Item)
		{
			m_DeviceTree.DeleteItem(m_selectItem);
			OracleIO.DEVICE_DeleteCameraWithAreaID(DlgAddDevice.AreaList[ItemCount].nid);
			OracleIO.DEVICE_DeleteArea(DlgAddDevice.AreaList[ItemCount].nid);
			OnMenuitemUpdate();
			break;
		}
		Item = m_DeviceTree.GetNextItem(Item,TVGN_NEXT);
		ItemCount++;
	}	
}

////LYNN///////////
void CDLGdevicetree::OnDblclkTreeDevice(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(!DlgLogin.CurrentUser.preview)
	{
		MessageBox("�� Ԥ�� Ȩ�ޣ�����ϵ����Ա",MESSAGEBOX_TITLE);
		return ;
	}

	// TODO: Add your control notification handler code here
	CPoint point;
	CMenu menu;

	GetCursorPos(&point);
	CPoint PointInTree = point;
	m_DeviceTree.ScreenToClient( &PointInTree);
	UINT nFlag = TVHT_ONITEM;// ���� m_DeviceTree ���һ�ʱ
	m_selectItem = m_DeviceTree.HitTest( PointInTree, &nFlag );

	if(m_selectItem != NULL)
	{
		if(m_DeviceTree.GetParentItem(m_selectItem) != NULL)
		{
			int ItemCount = 0;
			for(int i=0;i<1024;i++)
			{
				if(iplist[i].item == m_selectItem)
				{
					break;
				}
				ItemCount++;
			}

			int screenNo = DlgMain->DlgScreen.GetCurWindId();
			DlgMain->DlgScreen.StartPlay(
				iplist[ItemCount].camID,
				iplist[ItemCount].area.GetBuffer(0),
				iplist[ItemCount].name.GetBuffer(0),
				iplist[ItemCount].ip.GetBuffer(0),
				iplist[ItemCount].port,
				iplist[ItemCount].user.GetBuffer(0),
				iplist[ItemCount].psw.GetBuffer(0),
				screenNo,
				0,
				iplist[ItemCount].venderID);
		}
	}
	*pResult = 0;
}
