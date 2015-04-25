// DLGSetUser.cpp : implementation file
//

#include "stdafx.h"
#include "SmartVillage.h"
#include "DLGSetUser.h"

#include "DLGLogin.h"
extern CDLGLogin DlgLogin;

#include "DLGWarnning.h"

extern CYRSVMySQL MySqlIO;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDLGSetUser dialog


CDLGSetUser::CDLGSetUser(CWnd* pParent /*=NULL*/)
	: CDialog(CDLGSetUser::IDD, pParent)


	, m_FaceDetect(FALSE)
	, m_FaceDetectSet(FALSE)
{
	//{{AFX_DATA_INIT(CDLGSetUser)
	m_password_again = _T("");
	m_password = _T("");
	m_user = _T("");
	m_systemset = FALSE;
	m_recordset = FALSE;
	m_record = FALSE;
	m_ptz = FALSE;
	m_preview = FALSE;
	m_historyvideo = FALSE;
	m_historyreport = FALSE;
	m_historyCarDetect = FALSE;
	m_historyCarAlarm = FALSE;
	m_device = FALSE;
	m_blackset = FALSE;
	m_capbmp = FALSE;
	m_CarDetect = FALSE;
	m_CarDetectset = FALSE;
	m_FaceDetect = FALSE;
	m_FaceDetectSet = FALSE;
	m_all = FALSE;
	m_admin = FALSE;
	//}}AFX_DATA_INIT

	ListChoose=-1;
}


void CDLGSetUser::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDLGSetUser)
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Text(pDX, IDC_EDIT_USER_PSWAGAIN, m_password_again);
	DDV_MaxChars(pDX, m_password_again, 32);
	DDX_Text(pDX, IDC_EDIT_USER_PSW, m_password);
	DDV_MaxChars(pDX, m_password, 32);
	DDX_Text(pDX, IDC_EDIT_USER, m_user);
	DDV_MaxChars(pDX, m_user, 32);
	DDX_Check(pDX, IDC_CHECK_USER_SYSTEMSET, m_systemset);
//	DDX_Check(pDX, IDC_CHECK_USER_RECORDSET, m_recordset);
//	DDX_Check(pDX, IDC_CHECK_USER_RECORD, m_record);
//	DDX_Check(pDX, IDC_CHECK_USER_PTZ, m_ptz);
	DDX_Check(pDX, IDC_CHECK_USER_PREVIEW, m_preview);
//	DDX_Check(pDX, IDC_CHECK_USER_HISTORYVIDEO, m_historyvideo);
	DDX_Check(pDX, IDC_CHECK_USER_HISTORYREPORT, m_historyreport);
	DDX_Check(pDX, IDC_CHECK_USER_HISTORYCARDETECT, m_historyCarDetect);
	DDX_Check(pDX, IDC_CHECK_USER_HISTORYCARALARM, m_historyCarAlarm);
	DDX_Check(pDX, IDC_CHECK_USER_DEVICE, m_device);
	DDX_Check(pDX, IDC_CHECK_USER_BLACKSET, m_blackset);
	DDX_Check(pDX, IDC_CHECK_USER_CAPBMP, m_capbmp);
	DDX_Check(pDX, IDC_CHECK_USER_CARDETECT, m_CarDetect);
	DDX_Check(pDX, IDC_CHECK_USER_CARDETECTSET, m_CarDetectset);
	DDX_Check(pDX, IDC_CHECK_ALL, m_all);
	DDX_Check(pDX, IDC_CHECK_ADMIN, m_admin);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_BUTTON_USER_ADD, m_b_add);
	DDX_Control(pDX, IDC_BUTTON_USER_MODIFY, m_b_edit);
	DDX_Control(pDX, IDC_BUTTON_USER_DELETE, m_b_delete);


	DDX_Check(pDX, IDC_CHECK_USER_FACEDETECT, m_FaceDetect);
	DDX_Check(pDX, IDC_CHECK_USER_FACEDETECTSET, m_FaceDetectSet);
}


BEGIN_MESSAGE_MAP(CDLGSetUser, CDialog)
	//{{AFX_MSG_MAP(CDLGSetUser)
	ON_NOTIFY(NM_CLICK, IDC_LIST, OnClickList)
	ON_BN_CLICKED(IDC_BUTTON_USER_ADD, OnButtonUserAdd)
	ON_BN_CLICKED(IDC_BUTTON_USER_MODIFY, OnButtonUserModify)
	ON_BN_CLICKED(IDC_BUTTON_USER_DELETE, OnButtonUserDelete)
	ON_BN_CLICKED(IDC_CHECK_ALL, OnCheckAll)
	ON_EN_CHANGE(IDC_EDIT_USER, OnChangeEditUser)
	ON_BN_CLICKED(IDC_CHECK_ADMIN, OnCheckAdmin)
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDLGSetUser message handlers
BOOL CDLGSetUser::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_List.InsertColumn(0, _T("���" ), LVCFMT_LEFT, 50);
	m_List.InsertColumn(1, _T("�û���" ), LVCFMT_LEFT, 150);

	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);


	DisplayerList();

	if(-1!=ListChoose)
	{
		GetDlgItem(IDC_BUTTON_USER_MODIFY)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_USER_DELETE)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_USER_MODIFY)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_USER_DELETE)->EnableWindow(FALSE);
	}

	m_b_add.LoadBitmaps(IDB_ADD_BUTTON,IDB_ADD_BUTTON_MOVE,NULL,IDB_ADD_BUTTON_DIS);
	m_b_add.SizeToContent();		//����ӦͼƬ��С

	m_b_edit.LoadBitmaps(IDB_EDIT_BUTTON,IDB_EDIT_BUTTON_MOVE,NULL,IDB_EDIT_BUTTON_DIS);
	m_b_edit.SizeToContent();		//����ӦͼƬ��С

	m_b_delete.LoadBitmaps(IDB_DEL_BUTTON,IDB_DEL_BUTTON_MOVE,NULL,IDB_DEL_BUTTON_DIS);
	m_b_delete.SizeToContent();		//����ӦͼƬ��С

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDLGSetUser::OnOK()
{
	// TODO: Add your control notification handler code here
}

void CDLGSetUser::OnClickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NM_LISTVIEW* p=	(NM_LISTVIEW *)pNMHDR;

	//ѡ�еĸ�ֵ
	ListChoose= p->iItem;
	//û��
	if(-1 == ListChoose)
		return ;

	//��ȡ�û���
	char str[260]={0};
	m_List.GetItemText(ListChoose,1,str,260);
//	m_List.GetItemText(ListChoose,0,str,260);
//	unsigned long int nid;
//	sscanf(str,"%d",&nid);
	if(!MySqlIO.USER_ReadUserInfoWithName(str,&data))
	{
		MessageBox("�޴��û��������ݿ����",MESSAGEBOX_TITLE);
		return ;
	}
	//����
	Struct2M();

	if(-1!=ListChoose)
	{
		GetDlgItem(IDC_BUTTON_USER_MODIFY)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_USER_DELETE)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_USER_MODIFY)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_USER_DELETE)->EnableWindow(FALSE);
	}

	//����
	UpdateData(FALSE);

	*pResult = 0;
}

void CDLGSetUser::DisplayerList(void)
{
	list_user.clear();
	m_List.DeleteAllItems();

	ListChoose=-1;
	Clear();

	//��ѯ���ݿ�
	MySqlIO.USER_ReadAllUserInfo(list_user);

	int nItem;

	list<struct SET_USER_LIST_ST>::iterator beglist;

	char str[128]={0};

	for(beglist=list_user.begin();beglist!=list_user.end();beglist++)
	{
		sprintf(str,"%07d",beglist->nid);
		nItem = m_List.InsertItem(0,str);
		
		m_List.SetItemText(nItem,1,beglist->user);
	}
}

void CDLGSetUser::Clear() 
{
	m_password_again = _T("");
	m_password = _T("");
	m_user = _T("");
	m_systemset = FALSE;
	m_recordset = FALSE;
	m_record = FALSE;
	m_ptz = FALSE;
	m_preview = FALSE;
	m_historyvideo = FALSE;
	m_historyreport = FALSE;
	m_historyCarDetect = FALSE;
	m_historyCarAlarm = FALSE;
	m_device = FALSE;
	m_blackset = FALSE;
	m_capbmp = FALSE;
	m_CarDetect = FALSE;
	m_CarDetectset = FALSE;
	m_FaceDetect = FALSE;
	m_FaceDetectSet = FALSE;
	m_all = FALSE;
	m_admin = FALSE;

	UpdateData(FALSE);
}

void CDLGSetUser::OnButtonUserAdd() 
{
	UpdateData(TRUE);

	// TODO: Add your control notification handler code here
	if(m_password_again.IsEmpty() ||
		m_password.IsEmpty()	||
		m_user.IsEmpty())
	{
		MessageBox("�û��������벻Ϊ��",MESSAGEBOX_TITLE);
		return ;
	}
	if(m_password_again!=m_password)
	{
		MessageBox("�����������벻һ��",MESSAGEBOX_TITLE);
		return ;
	}
	//����
	ZogEnCode(m_password.GetBuffer(0),data.psw);
	//�������ݿ�
	M2Struct();
	long nid = 0;
	MySqlIO.USER_UserNameJudge(nid,m_user.GetBuffer());
	if(nid > 0)
	{
		MessageBox("�û����Ѵ���",MESSAGEBOX_TITLE);
		return;
	}
	if(!MySqlIO.USER_AddNewUser(data))
	{
		MessageBox("�û����ظ��������ݿ�����޷������û�",MESSAGEBOX_TITLE);
		return ;
	}

	DisplayerList();

	CString str="����û�:"+m_user;
	MySqlIO.LOG_AddNewSystemLog(DlgLogin.CurrentUser.user,str.GetBuffer(0));
}

void CDLGSetUser::OnButtonUserModify() 
{
	UpdateData(TRUE);
	// TODO: Add your control notification handler code here
	if(0!=strcmp(data.user,m_user.GetBuffer(0)))
	{
		MessageBox("�����޸��û���",MESSAGEBOX_TITLE);
		return ;
	}
	//��������������
	if(0==strcmp(DlgLogin.CurrentUser.user,m_user.GetBuffer(0))
		&& FALSE==m_admin)
	{
		MessageBox("�޷�������Ĺ���ԱȨ��ȡ��",MESSAGEBOX_TITLE);
		return ;
	}
	if(!m_password_again.IsEmpty() ||
		!m_password.IsEmpty())
	{
		if(m_password_again!=m_password)
		{
			MessageBox("�����������벻һ��",MESSAGEBOX_TITLE);
			return ;
		}
		//���� 
		//��ֵ�����뵽�ṹ��
		ZogEnCode(m_password.GetBuffer(0),data.psw);
	}
	//�������ݿ�
	M2Struct();
	if(!MySqlIO.USER_UpdateUserInfo(data))
	{
		MessageBox("���ݿ�����޷��޸��û�");
		return ;
	}
	//������޸ı���
	if(0==strcmp(DlgLogin.CurrentUser.user,m_user.GetBuffer(0)))
	{
		//�����ṹ��
		memcpy(&(DlgLogin.CurrentUser),&data,sizeof(struct SET_USER_DATA_ST));
		//����
		ZogDeCode(DlgLogin.CurrentUser.psw,DlgLogin.CurrentPsw);
	}

	MessageBox("�޸ĳɹ�",MESSAGEBOX_TITLE);
	MySqlIO.LOG_AddNewSystemLog(DlgLogin.CurrentUser.user,"�޸��û���Ϣ�ɹ�");

	DisplayerList();
}

void CDLGSetUser::OnButtonUserDelete() 
{
	UpdateData(TRUE);
	// TODO: Add your control notification handler code here
	if(0==strcmp(DlgLogin.CurrentUser.user,m_user.GetBuffer(0)))
	{
		MessageBox("�޷�ɾ������",MESSAGEBOX_TITLE);
		return	;
	}

	//�����
	CDLGWarnning dlgw;
	dlgw.m_wintxt="ɾ���û�";					//���ڱ���
	dlgw.m_warntxt="���ٴ�ȷ���Ƿ�ɾ��:\t"+m_user;	//��������
	int nResponse=dlgw.DoModal();
	if (nResponse == IDOK)
	{
		///ɾ��
		MySqlIO.USER_DeletetUser(data.nid);
		DisplayerList();

		dlgw.m_warntxt="ɾ���û�:"+m_user;
		MySqlIO.LOG_AddNewSystemLog(DlgLogin.CurrentUser.user,dlgw.m_warntxt.GetBuffer(0));
	}
	else if (nResponse == IDCANCEL)
		return ;
	else
		return ;
}

void CDLGSetUser::OnCheckAll() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_all)
	{
		m_systemset = TRUE;
		m_recordset = TRUE;
		m_record = TRUE;
		m_ptz = TRUE;
		m_preview = TRUE;
		m_historyvideo = TRUE;
		m_historyreport = TRUE;
		m_historyCarDetect = TRUE;
		m_historyCarAlarm = TRUE;
		m_device = TRUE;
		m_blackset = TRUE;
		m_capbmp = TRUE;
		m_CarDetect = TRUE;
		m_CarDetectset = TRUE;
		m_FaceDetect = TRUE;
		m_FaceDetectSet = TRUE;
	}
	else
	{
		m_systemset = FALSE;
		m_recordset = FALSE;
		m_record = FALSE;
		m_ptz = FALSE;
		m_preview = FALSE;
		m_historyvideo = FALSE;
		m_historyreport = FALSE;
		m_historyCarDetect = FALSE;
		m_historyCarAlarm = FALSE;
		m_device = FALSE;
		m_blackset = FALSE;
		m_capbmp = FALSE;
		m_CarDetect = FALSE;
		m_CarDetectset = FALSE;
		m_FaceDetect = FALSE;
		m_FaceDetectSet = FALSE;
	}
	
	UpdateData(FALSE);
}


void CDLGSetUser::Struct2M(void)
{
	m_admin=data.admin;
	m_user =data.user;
	m_systemset = data.systemset;
	m_recordset = data.recordset;
	m_record = data.record;
	m_ptz = data.ptz;
	m_preview = data.preview;
	m_historyvideo = data.historyvideo;
	m_historyreport = data.historyreport;
	m_historyCarDetect = data.historydetect;
	m_historyCarAlarm = data.historyalarm;
	m_device = data.device;
	m_blackset = data.blackset;
	m_capbmp = data.capbmp;
	m_CarDetect = data.Cardetect;
	m_CarDetectset = data.CarDetectset;

	m_FaceDetect = data.Facedetect;
	m_FaceDetectSet = data.FaceDetectset;


}

void CDLGSetUser::M2Struct(void)
{
	strcpy(data.user,m_user.GetBuffer(0));
	data.systemset=	m_systemset;
	data.recordset=m_recordset;
	data.record=	m_record;
	data.ptz=	m_ptz;
	data.preview=	m_preview;
	data.historyvideo=	m_historyvideo;
	data.historyreport=m_historyreport;
	data.historydetect=	m_historyCarDetect;
	data.historyalarm= m_historyCarAlarm;
	data.device=	m_device;
	data.blackset=	m_blackset;
	data.capbmp=	m_capbmp;
	data.Cardetect=	m_CarDetect;
	data.CarDetectset=	m_CarDetectset;
	data.Facedetect=	m_FaceDetect;
	data.FaceDetectset=	m_FaceDetectSet;
	data.admin=	m_admin;


}

void CDLGSetUser::OnChangeEditUser() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	//һ���ı��û���  ���޷�ִ��ɾ�����޸�
	GetDlgItem(IDC_BUTTON_USER_MODIFY)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_USER_DELETE)->EnableWindow(FALSE);
}

void CDLGSetUser::OnCheckAdmin() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_admin)
	{
		m_all=TRUE;
		UpdateData(FALSE);
		OnCheckAll();
	}
}


void CDLGSetUser::OnPaint()
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
HBRUSH CDLGSetUser::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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