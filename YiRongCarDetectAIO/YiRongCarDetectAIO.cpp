// YiRongCarDetectAIO.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "YiRongCarDetectAIO.h"
#include "YiRongCarDetectAIODlg.h"



#include "DLGLogin.h"
CDLGLogin DlgLogin;

#include "DLGSetSystem.h"
CDLGSetSystem DlgSetSystem;

////////////////lynn/////////////////
#include "IO.h"
IO OracleIO;
////////////////lynn/////////////////

#include "DLGWarnning.h"

////////////////////////////////////////
#include "URLencode.h"
#include "SignalDownload.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


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
	sprintf(DlgSetSystem.SystemIniPath,"%s\\yrsysteminfo.ini",CurrentDir);
	
	//ZOGNA//UP
	//��ϵͳ���ñ�
	DlgSetSystem.Read2Dlg();

//�ж��Ƿ���Ҫ���� ���ͻ���
#if ALLTAB_CLIENT_MODE 

	if(DlgSetSystem.m_check_update)
	{
		char url[1024];
		char url2[1024];
		char str[1024];
		char fail[1024];
		sprintf(str,"%s\\yrversion.txt",CurrentDir);
		int cur_version=0;
		int new_version=0;
		FILE *fp=_tfopen(str,_T("r"));
		if(fp)
		{
			_ftscanf(fp,_T("%d"),&cur_version);
			fclose(fp);

			SignalDownload sd;
			sd.InitData();

			sprintf(url,"http://%s/yrupdate/topnew.txt",DlgSetSystem.m_update_url);

			EncodeURI(url,url2,1024);

			sprintf(str,"%s\\temp.txt",DlgSetSystem.m_path_detect);

			if(sd.HTTPDownload(url2,str,fail,10,0))
			{
				fp=_tfopen(str,_T("r"));
				if(fp)
				{
					_ftscanf(fp,_T("%d"),&new_version);
					fclose(fp);

					if(cur_version!=0 && new_version!=0 && new_version>cur_version)
					{
						ShellExecute(NULL,NULL,"YrCarDetectAIOUpdate.exe",DlgSetSystem.m_update_url,NULL,SW_NORMAL);
						return FALSE;
					}
				}
			}
			else
			{
				CDLGWarnning dlgw;
				dlgw.m_wintxt="���ӷ�����";					//���ڱ���
				dlgw.m_warntxt="�޷����Ӹ��·�����";	//��������
				dlgw.DoModal();
			}
			sd.DestroyData();
		}
	}
#endif

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
	int OracleError = OracleIO.ConnectionOracleDBTXT("YRDataBaseConfig.db");
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

#if IVMS_ORACLE_DEVICETREE
	OracleError = OracleIO.IVMS_ConnectionOracleDBTXT("IVMSDataBaseConfig.db");
	if(OracleError == ReadFile_FAIL)
	{
		CDLGWarnning dlgw;
		dlgw.m_wintxt="IVMS�������ݿ�";					//���ڱ���
		dlgw.m_warntxt="IVMS�����ݿ������ļ�ʧ��";	//��������
		dlgw.DoModal();
		
		return FALSE;
	}
	else if(OracleError == Instance_FAIL)
	{
		CDLGWarnning dlgw;
		dlgw.m_wintxt="IVMS�������ݿ�";					//���ڱ���
		dlgw.m_warntxt="IVMS���ݿ�ADO��ʼ��ʧ��";	//��������
		dlgw.DoModal();
		
		return FALSE;
	}
	else if(OracleError == ContOpen_FAIL)
	{
		CDLGWarnning dlgw;
		dlgw.m_wintxt="IVMS�������ݿ�";					//���ڱ���
		dlgw.m_warntxt="IVMS���ݿ��޷�����:�˺�����IP�쳣 ���ļ��д�()";	//��������
		dlgw.DoModal();

		return FALSE;
	}
	else if(OracleError == Connectd_DONE)
	{
		//MessageBox("�������ݿ�ɹ�");
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
			return FALSE;
		}
	}
    //ȡ�ò������ͷ�CommandLineToArgvW����Ŀռ�  
    LocalFree(szArglist);  
/*

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
*/

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

