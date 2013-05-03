// YiRongCarDetectAIO.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "YiRongCarDetectAIO.h"
#include "YiRongCarDetectAIODlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "DLGLogin.h"
CDLGLogin DlgLogin;

#include "DLGSetSystem.h"
CDLGSetSystem DlgSetSystem;

////////////////lynn/////////////////
#include "IO.h"
IO OracleIO;
////////////////lynn/////////////////

#include "DLGWarnning.h"


//��ǰ·��
TCHAR CurrentDir[ZOG_MAX_PATH_STR]="";

/////////////////////////////////////////////////////////////////////////////
// CYiRongCarDetectAIOApp

BEGIN_MESSAGE_MAP(CYiRongCarDetectAIOApp, CWinApp)
	//{{AFX_MSG_MAP(CYiRongCarDetectAIOApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CYiRongCarDetectAIOApp construction

CYiRongCarDetectAIOApp::CYiRongCarDetectAIOApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CYiRongCarDetectAIOApp object

CYiRongCarDetectAIOApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CYiRongCarDetectAIOApp initialization

BOOL CYiRongCarDetectAIOApp::InitInstance()
{
	//XP���ݿ�֧��
	//ZOGNA//DOWN
	AfxOleInit();
	CoInitialize(NULL);
	//��ǰ·��
	GetCurrentDirectory(ZOG_MAX_PATH_STR, CurrentDir);
	sprintf(DlgSetSystem.SystemIniPath,"%s\\systeminfo.ini",CurrentDir);
	
	//ZOGNA//UP
	//��ϵͳ���ñ�
	DlgSetSystem.Read2Dlg();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	////////////////lynn/////////////////
	int OracleError = OracleIO.ConnectionOracleDBTXT("DataBaseConfig.txt");
	if(OracleError == ReadFile_FAIL)
	{
		CDLGWarnning dlgw;
		dlgw.m_wintxt="�������ݿ�";					//���ڱ���
		dlgw.m_warntxt="�����ݿ������ļ�ʧ��";	//��������
		dlgw.DoModal();
		
		return FALSE;
	}
	else if(OracleError == Instance_FAIL)
	{
		CDLGWarnning dlgw;
		dlgw.m_wintxt="�������ݿ�";					//���ڱ���
		dlgw.m_warntxt="���ݿ�ADO��ʼ��ʧ��";	//��������
		dlgw.DoModal();
		
		return FALSE;
	}
	else if(OracleError == ContOpen_FAIL)
	{
		CDLGWarnning dlgw;
		dlgw.m_wintxt="�������ݿ�";					//���ڱ���
		dlgw.m_warntxt="���ݿ��޷�����:�˺�����IP�쳣 ���ļ��д�()";	//��������
		dlgw.DoModal();

		return FALSE;
	}
	else if(OracleError == Connectd_DONE)
	{
		//MessageBox("�������ݿ�ɹ�");
	}
	////////////////lynn/////////////////

	////////////////lynn/////////////////
#if YRVM_PINGTAI_MODE
	OracleError = OracleIO.YRVM_ConnectionOracleDBTXT("YRVMDataBaseConfig.txt");
	if(OracleError == ReadFile_FAIL)
	{
		CDLGWarnning dlgw;
		dlgw.m_wintxt="YRVM�������ݿ�";					//���ڱ���
		dlgw.m_warntxt="YRVM�����ݿ������ļ�ʧ��";	//��������
		dlgw.DoModal();
		
		return FALSE;
	}
	else if(OracleError == Instance_FAIL)
	{
		CDLGWarnning dlgw;
		dlgw.m_wintxt="YRVM�������ݿ�";					//���ڱ���
		dlgw.m_warntxt="YRVM���ݿ�ADO��ʼ��ʧ��";	//��������
		dlgw.DoModal();
		
		return FALSE;
	}
	else if(OracleError == ContOpen_FAIL)
	{
		CDLGWarnning dlgw;
		dlgw.m_wintxt="YRVM�������ݿ�";					//���ڱ���
		dlgw.m_warntxt="YRVM���ݿ��޷�����:�˺�����IP�쳣 ���ļ��д�()";	//��������
		dlgw.DoModal();

		return FALSE;
	}
	else if(OracleError == Connectd_DONE)
	{
		//MessageBox("�������ݿ�ɹ�");
	}
#endif
	////////////////lynn/////////////////


#if ALLTAB_LOGIN_WIN_MODE
	//��½��
	DlgLogin.flag=LOGIN_IN;
	if( IDCANCEL == DlgLogin.DoModal())
	{
		return FALSE;
	}
#else
	//������¼
	strcpy(DlgLogin.CurrentUser.user,"admin");
	DlgLogin.CurrentUser.admin=1;
	DlgLogin.CurrentUser.systemset=1;
	DlgLogin.CurrentUser.recordset=1;
	DlgLogin.CurrentUser.record=1;
	DlgLogin.CurrentUser.ptz=1;
	DlgLogin.CurrentUser.preview=1;
	DlgLogin.CurrentUser.historyvideo=1;
	DlgLogin.CurrentUser.historyreport=1;
	DlgLogin.CurrentUser.historydetect=1;
	DlgLogin.CurrentUser.historyalarm=1;
	DlgLogin.CurrentUser.device=1;
	DlgLogin.CurrentUser.blackset=1;
	DlgLogin.CurrentUser.capbmp=1;
	DlgLogin.CurrentUser.detect=1;
	DlgLogin.CurrentUser.detectset=1;
#endif


	//������
	CYiRongCarDetectAIODlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	//ZOGNA//DOWN
	CoUninitialize();
	//ZOGNA//UP

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}


////////////����
void ZogEnCode(char *src,char *dst)
{
	int a,b;
	int i,len,v;

	TCHAR tempchar[16]="";
	
	//4���ַ�����
	srand(GetTickCount()%6000);
	//�����1
	a=rand()%30+1;
	b=rand()%99;
	_stprintf(dst,"%02d%02d",a,b);
	
	len=_tcslen(src);
	
	for(i=0;i<len;i++)
	{
		//�����㷨
		v=(int)(src[i])*a+b;
		//�ϲ�
		_stprintf(tempchar,"%04d",v);
		_tcscat(dst,tempchar);
	}
}
///////////////����
void ZogDeCode(char *src,char *dst)
{
	int a,b;
	int i,len,v;

	a=(src[0]-'0')*10+(src[1]-'0');
	b=(src[2]-'0')*10+(src[3]-'0');
	
	len=_tcslen(src)/4-1;
	
	for(i=0;i<len;i++)
	{
		v=(src[(i+1)*4]-'0')*1000+
			(src[(i+1)*4+1]-'0')*100+
			(src[(i+1)*4+2]-'0')*10+
			(src[(i+1)*4+3]-'0');
		dst[i]=(v-b)/a;
	}
	dst[i]='\0';
}