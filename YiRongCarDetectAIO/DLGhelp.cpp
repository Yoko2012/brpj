// DLGhelp.cpp : implementation file
//

#include "stdafx.h"
#include "yirongcardetectaio.h"
#include "DLGhelp.h"

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
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDLGhelp message handlers


BOOL CDLGhelp::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//////��ʾ����///////////////////
	CString modeflag;

	//��������ƽ̨ ģʽ =1  ������=0 
	if(YRVM_PINGTAI_MODE)
	{
		modeflag="���� ";

		if(0==ALLTAB_DETECT_CAR_MODE)
		{
			//�綯�����ģʽ
			if(YRVM_PINGTAI_ELECAR_MIX_MODE)
				modeflag+="��";
			else
				modeflag+="��";
		}
	}
	else
		modeflag="���� ";

	if(OPEN_CARDETECT_CODE)
		modeflag+="��ʶ�� ";
	else
		modeflag+="��ʶ�� ";

	if(ALLTAB_DETECT_CAR_MODE)
		modeflag+="������ ";
	else
		modeflag+="�綯�� ";

	if(ALLTAB_CLIENT_MODE)
		modeflag+="�ͻ��� ";
	else
		modeflag+="����� ";

	if(OPEN_VS2008_POCO_FTP)
		modeflag+="FTP ";

	if(IVMS_ORACLE_DEVICETREE)
		modeflag+="ͬ��ƽ̨�� ";

	if(OPEN_TOMCAT_MODE)
		modeflag+="TOMCAT���� \n";
	else
		modeflag+="���ݿ⹲�� \n";

	if(OPEN_YAAN_NEW_SDK)
		modeflag+="֧���ǰ��°� ";

	if(OPEN_YAAN_SDK)
		modeflag+="֧���ǰ� ";

	if(OPEN_DAHUA_SDK)
		modeflag+="֧�ִ� ";

	if(OPEN_HAIKANG_SDK)
		modeflag+="֧�ֺ��� ";

	if(OPEN_STREAM_CLIENT_SDK)
		modeflag+="֧����ý�� ";

	

	CString str;
	str.Format("%s\n����ʱ��:%s",modeflag.GetBuffer(0),__DATE__);
	GetDlgItem(IDC_STATIC_TIME)->SetWindowText(str);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDLGhelp::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CDLGhelp::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
