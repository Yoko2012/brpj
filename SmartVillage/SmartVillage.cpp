// SmartVillage.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "SmartVillage.h"
#include "SmartVillageDlg.h"



#include "DLGLogin.h"
CDLGLogin DlgLogin;

#include "DLGSetSystem.h"
CDLGSetSystem DlgSetSystem;

////////////////lynn/////////////////
#include "YRSVMySQL.h"
CYRSVMySQL MySqlIO;
////////////////lynn/////////////////

#include "DLGWarnning.h"

////////////////////////////////////////
//


RecoModuleHandle RWmodule_handle = NULL;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//��ǰ·��
TCHAR CurrentDir[ZOG_MAX_PATH_STR]="";

/////////////////////////////////////////////////////////////////////////////
// CSmartVillageApp

BEGIN_MESSAGE_MAP(CSmartVillageApp, CWinApp)
	//{{AFX_MSG_MAP(CSmartVillageApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSmartVillageApp construction

CSmartVillageApp::CSmartVillageApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSmartVillageApp object

CSmartVillageApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSmartVillageApp initialization

BOOL CSmartVillageApp::InitInstance()
{
	//XP���ݿ�֧��
	//ZOGNA//DOWN
	AfxOleInit();
	//CoInitialize(NULL);

	//AfxGetStaticModuleState();
//	AfxGetModuleState()->m_hCurrentInstanceHandle = GetModuleHandle(NULL); 
/*

	HRESULT hr = OleInitialize(NULL);   
	if(hr == S_FALSE)   
	{   
		OleUninitialize();   
	}   
	AfxEnableControlContainer();   
	COleObjectFactory::RegisterAll(); 
*/
	//��ǰ·��
	GetCurrentDirectory(ZOG_MAX_PATH_STR, CurrentDir);
	sprintf(DlgSetSystem.SystemIniPath,"%s\\yrsysteminfo.ini",CurrentDir);
	
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
	////////////////lynn/////////////////
	int ioError = MySqlIO.ConnectionMySQL("YRSVDataBaseConfig.db");
	if(ioError == ReadFile_FAIL)
	{
		CDLGWarnning dlgw;
		dlgw.m_wintxt="�������ݿ�";					//���ڱ���
		dlgw.m_warntxt="�����ݿ������ļ�ʧ��";	//��������
		dlgw.DoModal();

		return FALSE;
	}
	else if(ioError == MySQLInit_FAIL)
	{
		CDLGWarnning dlgw;
		dlgw.m_wintxt="�������ݿ�";					//���ڱ���
		dlgw.m_warntxt="���ݿ�ADO��ʼ��ʧ��";	//��������
		dlgw.DoModal();

		return FALSE;
	}
	else if(ioError == ContOpen_FAIL)
	{
		CDLGWarnning dlgw;
		dlgw.m_wintxt="�������ݿ�";					//���ڱ���
		dlgw.m_warntxt="���ݿ��޷�����:�˺�����IP�쳣 ���ļ��д�()";	//��������
		dlgw.DoModal();

		return FALSE;
	}
	else if(ioError == Connectd_DONE)
	{
		//MessageBox("�������ݿ�ɹ�");
	}

#if OPEN_FACEDETECT_CODE
	//��ʼ������ģ��
	SetCurrentDirectory(CurrentDir);
	if(Face_Init("models", &RWmodule_handle) != 0)
	{
		CDLGWarnning dlgw;
		dlgw.m_wintxt="����ģ��";					//���ڱ���
		dlgw.m_warntxt="����ģ�ͼ���ʧ��";	//��������
		dlgw.DoModal();
	}
#endif
	////////////////lynn/////////////////

	LPWSTR *szArglist = NULL;  
    int nArgs = 0;  
    szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);  
    if( nArgs > 1)  
    {  
		//szArglist���Ǳ������������  
		//nArgs�������в����ĸ���  
		//����ĵ�һ��Ԫ�ر�ʾ���̵�path��Ҳ����szArglist[0]��������Ԫ�����������������  
		DlgLogin.SilentMode=TRUE;
		DlgLogin.flag=LOGIN_IN;
		DlgLogin.m_user = szArglist[1];
		DlgLogin.m_password = szArglist[2];
		//��Ĭ��½
		DlgLogin.OnOK_Silent();
    }  
	else
	{
		DlgLogin.SilentMode=FALSE;
		//��½��
		DlgLogin.flag=LOGIN_IN;
		if( IDCANCEL == DlgLogin.DoModal())
		{
#if OPEN_FACEDETECT_CODE
			Face_UnInit();
#endif
			return FALSE;
		}
	}
    //ȡ�ò������ͷ�CommandLineToArgvW����Ŀռ�  
    LocalFree(szArglist);  

		
	//������
	CSmartVillageDlg dlg;
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

#if OPEN_FACEDETECT_CODE
	Face_UnInit();
#endif

	//ZOGNA//DOWN
	//CoUninitialize();
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

