// DLGdevicetree.cpp : implementation file
//

#include "stdafx.h"
#include "SmartVillage.h"
#include "DLGdevicetree.h"
#include "SmartVillageDlg.h"
#include "DLGAddArea.h"
#include "DLGWarnning.h"

#include "DLGSetFace.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////lynn/////////////////
extern CYRSVMySQL MySqlIO;
extern CSmartVillageDlg *DlgMain;
////////////////lynn/////////////////
#include "DLGLogin.h"
extern CDLGLogin DlgLogin;

#include "DLGSetSystem.h"
extern CDLGSetSystem DlgSetSystem;

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
CDLGdevicetree::~CDLGdevicetree()
{

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

	ON_COMMAND(ID_MENUITEM_FLUSHTREE, &CDLGdevicetree::OnMenuitemFlushtree)
	ON_COMMAND(ID_MENUITEM_SET_CAR, &CDLGdevicetree::OnMenuitemSetCar)
	ON_COMMAND(ID_MENUITEM_SET_FACE, &CDLGdevicetree::OnMenuitemSetFace)
	ON_COMMAND(ID_MENUITEM_ADDAREA, &CDLGdevicetree::OnMenuitemAddarea)
	ON_COMMAND(ID_MENUITEM_MODIFYAREA, &CDLGdevicetree::OnMenuitemModifyarea)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDLGdevicetree message handlers
BOOL CDLGdevicetree::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_DeviceTree.SetBkColor(RGB(254,254,254));	//���б���ɫ

	OnMenuitemUpdate();

	//����ͼ��
	imagelist.Create(16, 16, ILC_COLOR8|ILC_MASK, 0, 4);    
	imagelist.Add(AfxGetApp()->LoadIcon(IDI_TREE_AREA));        // icoͼ��
	imagelist.Add(AfxGetApp()->LoadIcon(IDI_TREE_CAM));
	m_DeviceTree.SetImageList(&imagelist, TVSIL_NORMAL);  // ���� imagelist �� tree��ӳ���ϵ

#if OPEN_FACEDETECT_CODE
	faceMngTempDB.RWFaceMng_TempInit();
#endif

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
	tree_Rect.top = rc.top+28;
	tree_Rect.bottom = rc.bottom;
	tree_Rect.left = rc.left;
	tree_Rect.right = rc.right;

	m_DeviceTree.MoveWindow(tree_Rect);

	Invalidate();
}


void CDLGdevicetree::OnCancel()
{
	DlgMain->OnCancel();
}
void CDLGdevicetree::OnOK()
{

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
	//if(m_selectItem != NULL)
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
	bool flag=true;
	while(Item != NULL)
	{
		if(Item == m_selectItem)
		{
			flag=false;
			break;
		}
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
	
			if(flag)
			{
				MessageBox("��������豸 �� �������",MESSAGEBOX_TITLE);
				return ;
			}

			IPLIST tempCamInfo;
			long ncamera;

			tempCamInfo.areaID=DlgAddDevice.AreaList[DlgAddDevice.AreaComboCur ].nid;

			long nid = 0;
			MySqlIO.DEVICE_GetCameraID(nid,tempCamInfo.areaID,DlgAddDevice.m_CamName.GetBuffer(0));
			if(nid > 0)
			{
				MessageBox("���豸�Ѵ���",MESSAGEBOX_TITLE);
				return ;
			}

			strcpy(tempCamInfo.area , DlgAddDevice.m_CamArea);
			strcpy(tempCamInfo.ip , DlgAddDevice.m_CamIpAddr);
			strcpy(tempCamInfo.name , DlgAddDevice.m_CamName);
			tempCamInfo.port = DlgAddDevice.m_CamPort;
			tempCamInfo.channel = DlgAddDevice.m_CamChannel;
			strcpy(tempCamInfo.psw ,DlgAddDevice.m_CamPsw);
			strcpy(tempCamInfo.user , DlgAddDevice.m_CamUser);
			tempCamInfo.venderID = DlgAddDevice.VenderComboCur;
			strcpy(tempCamInfo.Rtspurl,DlgAddDevice.m_CamRtspurl);
			tempCamInfo.RTP= DlgAddDevice.RTPComboCur;
			tempCamInfo.DecodeTag= DlgAddDevice.DecodeTagComboCur;
			strcpy(tempCamInfo.longitude, DlgAddDevice.m_longitude);
			strcpy(tempCamInfo.latitude,DlgAddDevice .m_latitude);
			tempCamInfo.userID= DlgLogin.CurrentUser.nid;

		
#if OPEN_FACEDETECT_CODE
			CString str=DlgAddDevice.m_CamArea+DlgAddDevice.m_CamName;
			long dbid;
		
			if(false== faceMngTempDB.RWFaceMngDbAddNew(dbid,str.GetBuffer(0)))
			{
				faceMngTempDB.RWFaceMng_UnInit();
				MessageBox("RW��ʱ�����ʧ��",MESSAGEBOX_TITLE);
				return ;
			}
#endif
			MySqlIO.DEVICE_AddNewCamera(ncamera,tempCamInfo);
			//�������ƻ�����Ĭ������
			MySqlIO.DEVICE_SetTable_AddNew(ncamera);

#if OPEN_FACEDETECT_CODE

			struct FACE_TEMP_DB_ST tempdb={0};
			strcpy(tempdb.name,str.GetBuffer(0));
			tempdb.RW_tempID=dbid;
			tempdb.ncamera=ncamera;
			MySqlIO.TEMP_DB_AddNew(tempdb);

#endif
			DlgMain->ShowCameraMessage(	DlgAddDevice.m_CamName.GetBuffer(0),"����豸�ɹ�",0);
		
		OnMenuitemUpdate();
	}
}

void CDLGdevicetree::OnMenuitemUpdate() 
{
	// TODO: Add your command handler code here
	vector<struct DEVICE_AREA_ST> OrgName;
	vector<IPLIST> CameraList;
	//�����ݿ����е�����
	MySqlIO.DEVICE_ReadAllOrgName(OrgName);
	HTREEITEM hItem;
	HTREEITEM childItem;
	DlgAddDevice.AreaCount = OrgName.size();
	iptotal = 0;

	//ɾ�����е���
	m_DeviceTree.DeleteAllItems();
	if(OrgName.size() <=0)
		return ; 
	for(int i=0;i<OrgName.size();i++)
	{
		if(i == MAX_AREA)
		{
			MessageBox("��������������ƣ����������ֽ�����ʾ",MESSAGEBOX_TITLE);
			break;
		}
		strcpy(DlgAddDevice.AreaList[i].name, OrgName[i].name);
		DlgAddDevice.AreaList[i].nid = OrgName[i].nid;
		hItem = m_DeviceTree.InsertItem(OrgName[i].name,0,0,TVI_ROOT);		//�ڸ�������������
		CameraList.clear();
		MySqlIO.DEVICE_ReadCameraInfo(OrgName[i].nid,CameraList);
		if(CameraList.size() <=0)
			continue ; 
		for(int j=0;j<CameraList.size();j++)
		{

			strcpy(iplist[iptotal].area , CameraList[j].area);
			iplist[iptotal].ncamera = CameraList[j].ncamera;
			strcpy(iplist[iptotal].ip , CameraList[j].ip);
			strcpy(iplist[iptotal].name , CameraList[j].name);
			iplist[iptotal].port = CameraList[j].port;
			iplist[iptotal].channel = CameraList[j].channel;
			strcpy(iplist[iptotal].psw ,CameraList[j].psw);
			strcpy(iplist[iptotal].user , CameraList[j].user);
			iplist[iptotal].Parent_item = hItem;
			iplist[iptotal].venderID = CameraList[j].venderID;
			strcpy(iplist[iptotal].Rtspurl,CameraList[j].Rtspurl);
			iplist[iptotal].RTP= CameraList[j].RTP;
			iplist[iptotal].DecodeTag= CameraList[j].DecodeTag;
			strcpy(iplist[iptotal].longitude, CameraList[j].longitude);
			strcpy(iplist[iptotal].latitude,CameraList[j].latitude);
			iplist[iptotal].userID= CameraList[j].userID;
		
			childItem = m_DeviceTree.InsertItem(iplist[iptotal].name,1,1,hItem);		//����豸�ڵ�
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
		for(int i=0;i<MAX_AREA;i++)
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
				DlgAddDevice.m_CamChannel = iplist[i].channel;
				DlgAddDevice.m_CamIpAddr = iplist[i].ip;
				DlgAddDevice.m_CamName = iplist[i].name;
				DlgAddDevice.m_CamPsw = iplist[i].psw;
				DlgAddDevice.m_CamUser = iplist[i].user;
				DlgAddDevice.VenderComboCur = iplist[i].venderID;
				DlgAddDevice.m_CamRtspurl= iplist[i].Rtspurl;
				DlgAddDevice.RTPComboCur= iplist[i].RTP;
				DlgAddDevice.DecodeTagComboCur= iplist[i].DecodeTag;
				DlgAddDevice.m_longitude= iplist[i].longitude;
				DlgAddDevice.m_latitude= iplist[i].latitude;

				for(int k=0;k<MAX_DEVICE_NUM;k++)
				{
					if(DlgMain->DlgTabVideo.DlgScreen.m_videoInfo[k].camID == 	iplist[i].ncamera)
					{
						//������ڲ��š���
						if(DlgMain->DlgTabVideo.DlgScreen.GetCurWindPlayState(k))
						{
							MessageBox("�豸���ڲ��ţ�����ֹͣ���ź��ٱ༭!",MESSAGEBOX_TITLE);
							return ;
						}
					}
				}

				//�ж��豸�Ƿ���� ��������� ǿ�Ƹ���
				if(false==MySqlIO.DEVICE_JudgeCamera(iplist[i].ncamera))
				{
					DlgMain->ShowCameraMessage(iplist[i].name,"����ͷ�������û�ɾ����ǿ��ˢ���豸��",0);
					OnMenuitemUpdate();
					return ;
				}


				if(DlgAddDevice.DoModal() == IDOK)
				{
#if OPEN_RECORD
					//�޸Ķ�ʱ¼�Ƽƻ�
					MySqlIO.RECORD_PlanTable_UpdateCamInfo(
						iplist[i].camID,
						DlgAddDevice.m_CamArea.GetBuffer(0),\
						DlgAddDevice.m_CamName.GetBuffer(0),\
						DlgAddDevice.m_CamIpAddr.GetBuffer(0));
#endif		

					IPLIST tempCamInfo;

					tempCamInfo.areaID =DlgAddDevice.AreaList[DlgAddDevice.AreaComboCur].nid;
					tempCamInfo.ncamera=iplist[i].ncamera;
					strcpy(tempCamInfo.area , DlgAddDevice.m_CamArea);
					strcpy(tempCamInfo.ip , DlgAddDevice.m_CamIpAddr);
					strcpy(tempCamInfo.name , DlgAddDevice.m_CamName);
					tempCamInfo.port = DlgAddDevice.m_CamPort;
					tempCamInfo.channel = DlgAddDevice.m_CamChannel;
					strcpy(tempCamInfo.psw ,DlgAddDevice.m_CamPsw);
					strcpy(tempCamInfo.user , DlgAddDevice.m_CamUser);
					tempCamInfo.venderID = DlgAddDevice.VenderComboCur;
					strcpy(tempCamInfo.Rtspurl,DlgAddDevice.m_CamRtspurl);
					tempCamInfo.RTP= DlgAddDevice.RTPComboCur;
					tempCamInfo.DecodeTag= DlgAddDevice.DecodeTagComboCur;
					strcpy(tempCamInfo.longitude, DlgAddDevice.m_longitude);
					strcpy(tempCamInfo.latitude,DlgAddDevice .m_latitude);
					tempCamInfo.userID= 	 iplist[i].userID;

					//��������
					MySqlIO.DEVICE_UpdateCameraInfo(tempCamInfo);
#if OPEN_FACEDETECT_CODE
					CString str=DlgAddDevice.m_CamArea+DlgAddDevice.m_CamName;
					struct FACE_TEMP_DB_ST tempdb={0};
					strcpy(tempdb.name,str.GetBuffer(0));
					tempdb.ncamera=iplist[i].ncamera;
					MySqlIO.TEMP_DB_UpdateWithNcamera(tempdb);
#endif
					
					DlgMain->ShowCameraMessage(	DlgAddDevice.m_CamName.GetBuffer(0),"�༭�豸�ɹ�",0);
					OnMenuitemUpdate();

					//����ŵ�	OnMenuitemUpdate���� ����IPLIST��δ����
					for(int j=0;j<MAX_DEVICE_NUM;j++)
					{
						if(DlgMain->DlgTabVideo.DlgScreen.m_videoInfo[j].camID == 	iplist[i].ncamera)
						{
							//������ڲ��š���
							if(DlgMain->DlgTabVideo.DlgScreen.GetCurWindPlayState(j))
							{
								bool beforeCarDetect=DlgMain->DlgTabVideo.DlgScreen.GetCarDetectState(j);

						
								bool beforerecord=DlgMain->DlgTabVideo.DlgScreen.GetRecordState(j);

								//���²���
								DlgMain->DlgTabVideo.DlgScreen.StartPlay(
									iplist[i].ncamera,
									iplist[i].area,
									iplist[i].name,
									iplist[i].ip,
									iplist[i].port,
									iplist[i].channel,//20140718
									iplist[i].user,
									iplist[i].psw,
									j,
									0,
									iplist[i].venderID,
									iplist[i].Rtspurl,
									iplist[i].RTP,
									iplist[i].DecodeTag);

								//�ָ�״̬
								if(beforeCarDetect)
									DlgMain->DlgTabVideo.DlgNormal.OpenCarDetect(j);

							
								if(beforerecord)
									DlgMain->DlgTabVideo.DlgNormal.OpenRecord(j);
							}
							break;
						}
					}
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
	for(i=0;i<MAX_AREA;i++)
	{
		if(iplist[i].item == m_selectItem)
		{
			break;
		}
	}

	if(i==MAX_AREA)
	{
		OnMenuitemUpdate();
		return ;
	}

	CDLGWarnning dlgw;
	dlgw.m_wintxt=iplist[i].name;
	dlgw.m_warntxt="����ͷ������գ����ɻָ�";
	int nResponse=dlgw.DoModal();
	if (nResponse == IDOK)
	{
		DlgMain->DlgTabVideo.DlgScreen.DeleteDevice(iplist[i].ncamera);


		MySqlIO.DEVICE_DeleteCamera(iplist[i].ncamera);
		//ɾ������
		MySqlIO.DEVICE_SetTable_DeleteWithCamID(iplist[i].ncamera);
#if OPEN_RECORD
		//ɾ����ʱ¼�Ƽƻ�
		MySqlIO.RECORD_PlanTable_DeleteWithCamID(iplist[i].ncamera);
#endif

#if OPEN_FACEDETECT_CODE
		struct FACE_TEMP_DB_ST tempdb={0};
		MySqlIO.TEMP_DB_Read(iplist[i].ncamera,tempdb);

		faceMngTempDB.RWFaceMngDbDeleteWithID(tempdb.RW_tempID);

		MySqlIO.TEMP_DB_DeleteWithNcamera(iplist[i].ncamera);
#endif

		DlgMain->ShowCameraMessage(iplist[i].name,"ɾ���豸�ɹ�",0);

		OnMenuitemUpdate();
	}
	else
		return ;

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
	int tempflag=0;
	Item = m_DeviceTree.GetRootItem();
	while(Item != NULL)
	{
		if(m_selectItem == Item)
		{
			tempflag=1;
			break;
		}
		Item = m_DeviceTree.GetNextItem(Item,TVGN_NEXT);
		ItemCount++;
	}	

	if(0==tempflag)
	{
		OnMenuitemUpdate();
		return ;
	}
	CDLGWarnning dlgw;
	dlgw.m_wintxt=DlgAddDevice.AreaList[ItemCount].name;
	dlgw.m_warntxt="�����ڵ�����ͷ��������գ����ɻָ�";
	int nResponse=dlgw.DoModal();
	if (nResponse == IDOK)
	{
		list<long> ncameraList;
		ncameraList.clear();
		MySqlIO.DEVICE_GetCameraWithAreaID(DlgAddDevice.AreaList[ItemCount].nid,ncameraList);
		if(ncameraList.size()>0)
		{
			struct FACE_TEMP_DB_ST tempdb={0};
			list<long>::iterator beglist;
			for(beglist=ncameraList.begin();beglist!=ncameraList.end();beglist++)
			{		
				DlgMain->DlgTabVideo.DlgScreen.DeleteDevice((*beglist));
				//ɾ������
				MySqlIO.DEVICE_SetTable_DeleteWithCamID((*beglist));

#if OPEN_FACEDETECT_CODE
				memset(&tempdb,0,sizeof(struct FACE_TEMP_DB_ST));
				MySqlIO.TEMP_DB_Read(*beglist,tempdb);

				faceMngTempDB.RWFaceMngDbDeleteWithID(tempdb.RW_tempID);

				MySqlIO.TEMP_DB_DeleteWithNcamera(*beglist);
#endif
			}

		}
		m_DeviceTree.DeleteItem(m_selectItem);

		MySqlIO.DEVICE_DeleteCameraWithAreaID(DlgAddDevice.AreaList[ItemCount].nid);
		MySqlIO.DEVICE_DeleteArea(DlgAddDevice.AreaList[ItemCount].nid);

		DlgMain->ShowCameraMessage(DlgAddDevice.AreaList[ItemCount].name,"ɾ������ɹ�",0);
		OnMenuitemUpdate();
	}
	else
		return ;
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
			for(int i=0;i<MAX_AREA;i++)
			{
				if(iplist[i].item == m_selectItem)
				{
					break;
				}
				ItemCount++;
			}
			//�ж��豸�Ƿ���� ��������� ǿ�Ƹ���
			if(false==MySqlIO.DEVICE_JudgeCamera(iplist[ItemCount].ncamera))
			{
				DlgMain->ShowCameraMessage(iplist[ItemCount].name,"����ͷ�������û�ɾ����ǿ��ˢ���豸��",0);
				OnMenuitemUpdate();
				return ;
			}

			
			int screenNo = DlgMain->DlgTabVideo.DlgScreen.GetCurWindId();
			if( DlgMain->DlgTabVideo.DlgScreen.GetCurWindPlayState(screenNo))
			{
				//�Զ�ѡ�� δ�ڲ��ŵ� ��ת
				for(int i=0;i<MAX_DEVICE_NUM;i++)
				{
					if(false==DlgMain->DlgTabVideo.DlgScreen.GetCurWindPlayState(i))
					{
						screenNo=i;
						//��ת ѡ���
						DlgMain->DlgTabVideo.DlgScreen.m_screenPannel.SetActivePage(&(DlgMain->DlgTabVideo.DlgScreen.m_screenPannel.m_wndVideo[i]), TRUE);
						DlgMain->DlgTabVideo.DlgScreen.SetCurWindId(i);
						DlgMain->DlgTabVideo.DlgNormal.UpdateNormalWnd();
						break;
					}
				}
			}

			DlgMain->DlgTabVideo.DlgScreen.StartPlay(
				iplist[ItemCount].ncamera,
				iplist[ItemCount].area,
				iplist[ItemCount].name,
				iplist[ItemCount].ip,
				iplist[ItemCount].port,
				iplist[ItemCount].channel,//20140718
				iplist[ItemCount].user,
				iplist[ItemCount].psw,
				screenNo,
				0,
				iplist[ItemCount].venderID,
				iplist[ItemCount].Rtspurl,
				iplist[ItemCount].RTP,
				iplist[ItemCount].DecodeTag);

		}
	}

	(*pResult) = 0;
}


void CDLGdevicetree::OnMenuitemFlushtree()
{
	// TODO: Add your command handler code here
	OnMenuitemUpdate();
}

void CDLGdevicetree::OnMenuitemSetCar()
{
	if(!DlgLogin.CurrentUser.CarDetectset)
	{
		MessageBox("�� ʶ������ Ȩ�ޣ�����ϵ����Ա",MESSAGEBOX_TITLE);
		return ;
	}

	int i;
	for(i=0;i<MAX_AREA;i++)
	{
		if(iplist[i].item == m_selectItem)
		{
			break;
		}
	}

	if(i==MAX_AREA)
	{
		OnMenuitemUpdate();
		return ;
	}

	// TODO: Add your command handler code here
#if ALLTAB_DETECT_CAR_MODE
	CDLGSetCar DlgSetCar;
#else
	CDLGSetElecar DlgSetCar;
#endif
	struct DEVICE_SET_ST CamSet={0};
	struct CarSetStruct CarSet={0};

	MySqlIO.DEVICE_SetTable_Read(iplist[i].ncamera,CamSet);

	//��������ݿ��ȡ���Լ����档����ʶ��CPP�ļ�ҲҪ�Ӷ�ȡ
	CarSet.CarColor=CamSet.car.carlor;
	CarSet.Deskew=CamSet.car.deskew;
	CarSet.RedRect=CamSet.car.redrect;
	CarSet.JPGquality=CamSet.car.jpgquailty;
	CarSet.MinWidth=CamSet.car.minwidth;
	CarSet.MaxWidth=CamSet.car.maxwidth;
	CarSet.RangeRate.x0=CamSet.car.left;
	CarSet.RangeRate.x1=CamSet.car.right;
	CarSet.RangeRate.y0=CamSet.car.top;
	CarSet.RangeRate.y1=CamSet.car.bottom;
	strcpy(CarSet.DefaultChar,CamSet.car.defaultchar);
	CarSet.Reliability=CamSet.car.reliability;
	memcpy(CarSet.Mask,CamSet.car.mask,CAR_MASK_MAX);

	DlgSetCar.ReadOldConfig(CarSet);
	if(DlgSetCar.DoModal() == IDOK)
	{
		//���ó���ʶ��
		CamSet.car.carlor=	DlgSetCar.CarSet.CarColor;
		CamSet.car.deskew=DlgSetCar.CarSet.Deskew;
		CamSet.car.redrect=	DlgSetCar.CarSet.RedRect;
		CamSet.car.jpgquailty=	DlgSetCar.CarSet.JPGquality;
		CamSet.car.minwidth=DlgSetCar.CarSet.MinWidth;
		CamSet.car.maxwidth=	DlgSetCar.CarSet.MaxWidth;
		CamSet.car.left=	DlgSetCar.CarSet.RangeRate.x0;
		CamSet.car.right=DlgSetCar.CarSet.RangeRate.x1;
		CamSet.car.top=DlgSetCar.CarSet.RangeRate.y0;
		CamSet.car.bottom=	DlgSetCar.CarSet.RangeRate.y1;
		strcpy(CamSet.car.defaultchar,DlgSetCar.CarSet.DefaultChar);
		CamSet.car.reliability=	DlgSetCar.CarSet.Reliability;
		memcpy(CamSet.car.mask,DlgSetCar.CarSet.Mask,CAR_MASK_MAX);

		MySqlIO.DEVICE_SetTable_Update(CamSet);
	}
}


void CDLGdevicetree::OnMenuitemSetFace()
{
	// TODO: Add your command handler code here
	if(!DlgLogin.CurrentUser.FaceDetectset)
	{
		MessageBox("�� ʶ������ Ȩ�ޣ�����ϵ����Ա",MESSAGEBOX_TITLE);
		return ;
	}
	int i;
	for(i=0;i<MAX_AREA;i++)
	{
		if(iplist[i].item == m_selectItem)
		{
			break;
		}
	}

	if(i==MAX_AREA)
	{
		OnMenuitemUpdate();
		return ;
	}

	// TODO: Add your command handler code here
	CDLGSetFace DlgSetFace;

	struct DEVICE_SET_ST CamSet;

	MySqlIO.DEVICE_SetTable_Read(iplist[i].ncamera,CamSet);

	DlgSetFace.m_minface=CamSet.face.minface;	
	DlgSetFace.m_maxface=CamSet.face.maxface;
	DlgSetFace.m_e_front_ts=CamSet.face.frontface_ts;
	DlgSetFace.m_e_side_ts=CamSet.face.sideface_ts;
	DlgSetFace.m_e_timeout=CamSet.face.time_out;
	DlgSetFace.m_e_scale=CamSet.face.scale_ratio;
	DlgSetFace.m_e_video_ts=CamSet.face.video_ts;
	DlgSetFace.m_threshold=CamSet.face.threshold;
	DlgSetFace.m_maxcount=CamSet.face.maxcount;

	DlgSetFace.m_maxcount=CamSet.face.maxcount;
	DlgSetFace.dbTotal=CamSet.face.dbTotal;
	for(i=0;i<DlgSetFace.dbTotal;i++)
	{
		DlgSetFace.db_nid[i]=CamSet.face.db_nid[i];
	}

	if(DlgSetFace.DoModal() == IDOK)
	{
		CamSet.face.minface=	DlgSetFace.m_minface;	
		CamSet.face.maxface=	DlgSetFace.m_maxface;	
		CamSet.face.frontface_ts=	DlgSetFace.m_e_front_ts;
		CamSet.face.sideface_ts=	DlgSetFace.m_e_side_ts;
		CamSet.face.time_out=	DlgSetFace.m_e_timeout;
		CamSet.face.scale_ratio=	DlgSetFace.m_e_scale;
		CamSet.face.video_ts=	DlgSetFace.m_e_video_ts;
		CamSet.face.threshold=		DlgSetFace.m_threshold;
		CamSet.face.maxcount=		DlgSetFace.m_maxcount;

		CamSet.face.dbTotal=		DlgSetFace.dbTotal;
		for(i=0;i<DlgSetFace.dbTotal;i++)
		{
			CamSet.face.db_nid[i]=	DlgSetFace.db_nid[i];
		}

		MySqlIO.DEVICE_SetTable_Update(CamSet);
	}
}

void CDLGdevicetree::OnMenuitemAddarea()
{
	// TODO: Add your command handler code here
	if(!DlgLogin.CurrentUser.device)
	{
		MessageBox("�� �豸���� Ȩ�ޣ�����ϵ����Ա",MESSAGEBOX_TITLE);
		return ;
	}
	CDLGAddArea DlgAddArea;
	int nResponse=DlgAddArea.DoModal();
	if (nResponse == IDOK)
	{
		if(DlgAddArea.m_AddArea.IsEmpty())
			return ;
		if(	DlgAddDevice.AreaCount >= MAX_AREA)
		{
			MessageBox("��������������������",MESSAGEBOX_TITLE);
			return;
		}

		long nid = 0;
		MySqlIO.DEVICE_GetAreaID(nid,DlgAddArea.m_AddArea.GetBuffer(0));
		if(nid > 0)
		{
			MessageBox("���������Ѵ���",MESSAGEBOX_TITLE);
			return;
		}

		m_DeviceTree.InsertItem(DlgAddArea.m_AddArea,0,0,TVI_ROOT);
		MySqlIO.DEVICE_AddNewArea(DlgAddArea.m_AddArea.GetBuffer(0));
		OnMenuitemUpdate();
	}
	else
		return ;
}

void CDLGdevicetree::OnMenuitemModifyarea()
{
	// TODO: Add your command handler code here
	if(!DlgLogin.CurrentUser.device)
	{
		MessageBox("�� �豸���� Ȩ�ޣ�����ϵ����Ա",MESSAGEBOX_TITLE);
		return ;
	}

	// TODO: Add your command handler code here
	HTREEITEM Item;
	int ItemCount=0;
	int tempflag=0;
	Item = m_DeviceTree.GetRootItem();
	while(Item != NULL)
	{
		if(m_selectItem == Item)
		{
			tempflag=1;
			break;
		}
		Item = m_DeviceTree.GetNextItem(Item,TVGN_NEXT);
		ItemCount++;
	}	

	if(0==tempflag)
	{
		OnMenuitemUpdate();
		return ;
	}

	CDLGAddArea DlgAddArea;
	DlgAddArea.m_AddArea=DlgAddDevice.AreaList[ItemCount].name;
	int nResponse=DlgAddArea.DoModal();
	if (nResponse == IDOK)
	{
		if(DlgAddArea.m_AddArea.IsEmpty())
			return ;
	
		MySqlIO.DEVICE_UpdateAreaInfo(DlgAddDevice.AreaList[ItemCount].nid,DlgAddArea.m_AddArea.GetBuffer(0));
		OnMenuitemUpdate();
	}
	else
		return ;
}
