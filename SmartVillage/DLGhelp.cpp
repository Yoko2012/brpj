// DLGhelp.cpp : implementation file
//

#include "stdafx.h"
#include "SmartVillage.h"
#include "SmartVillageDlg.h"
#include "DLGhelp.h"
#include "DLGpictureView.h"

#include "DLGSetSystem.h"
extern CDLGSetSystem DlgSetSystem;

////////////////////////////////////////


//��ǰ·��
extern TCHAR CurrentDir[ZOG_MAX_PATH_STR];

extern CSmartVillageDlg *DlgMain;
#include "DLGLogin.h"
extern CDLGLogin DlgLogin;



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDLGhelp dialog


CDLGhelp::CDLGhelp(CWnd* pParent /*=NULL*/)
: CDialog(CDLGhelp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDLGhelp)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDLGhelp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDLGhelp)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDLGhelp, CDialog)
	//{{AFX_MSG_MAP(CDLGhelp)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, &CDLGhelp::OnBnClickedButtonUpdate)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDLGhelp message handlers


BOOL CDLGhelp::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//////��ʾ����///////////////////
	CString modeflag;

	if(TEST_DEBUG)
		modeflag+="����ģʽ ";

	char tempstr[32];
	sprintf(tempstr,"���֧��%d·�豸\n",MAX_CAMERA);
	modeflag+=tempstr;

	if(OPEN_LC_CARDETECT_CODE)
		modeflag+="֧��LC����ʶ�� ";
	else if(OPEN_HYZJ_CARDETECT_CODE)
		modeflag+="֧��HY����ʶ�� ";
	else 
		modeflag+="��֧�ֳ���ʶ�� ";


	if(OPEN_FACEDETECT_CODE)
		modeflag+="֧������ʶ�� ";
	else
		modeflag+="��֧������ʶ�� ";


	if(ALLTAB_DETECT_CAR_MODE)
		modeflag+="������ ";
	else
		modeflag+="�綯�� ";

	if(OPEN_DAHUA_SDK)
		modeflag+="֧�־ɰ�� ";
	if(OPEN_DAHUA_SDK_NEW)
		modeflag+="֧���°�� ";
		
	if(OPEN_HAIKANG_SDK)
		modeflag+="֧�ֺ��� ";

	if(OPEN_STREAM_CLIENT_SDK)
		modeflag+="֧����ý�� ";

	if(OPEN_VLC_RTSP_SDK)
		modeflag+="֧��RTSP \n";

	CString str;
	str.Format("%s\n����ʱ��:%s",modeflag.GetBuffer(0),__DATE__);
	GetDlgItem(IDC_STATIC_TIME)->SetWindowText(str);

	GetDlgItem(IDC_BUTTON_UPDATE)->EnableWindow(FALSE);


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDLGhelp::OnOK() 
{
	// TODO: Add extra validation here
#if 0
	CDLGpictureView dlgPicView;
	dlgPicView.Titlestr+="aa";

	dlgPicView.srcfile="C:\\36273.jpg";
	dlgPicView.srcsmallfile="C:\\36273.jpg";
	
	dlgPicView.DoModal();
#else

	CDialog::OnOK();
#endif

}

void CDLGhelp::OnCancel() 
{
	// TODO: Add extra cleanup here

	CDialog::OnCancel();
}

void CDLGhelp::OnBnClickedButtonUpdate()
{
	// TODO: Add your control notification handler code here


}
