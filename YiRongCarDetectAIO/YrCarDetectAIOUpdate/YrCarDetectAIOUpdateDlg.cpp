// YrCarDetectAIOUpdateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "YrCarDetectAIOUpdate.h"
#include "YrCarDetectAIOUpdateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

enum UPDATE_FLAG
{
	UF_CREAT_DIR=1,
	UF_DELETE_DIR=2,
	UF_CREAT_FILE=3,
	UF_DELETE_FILE=4,

};

/*
TOMCAT������Ҫ����
\yrupdate �ļ���
����topnew.txt Ϊ���°汾��

\yrupdate\N\ ΪҪ��N�汾������M�汾�� �ļ���
\yrupdate\N\yrversion.txt Ϊ����������M�汾�İ汾��

����Ŀ¼��Ҫ��yrversion.txt Ϊ��ǰ�汾��
//UPDALIST������ �ո���������·����Ҫ���пո�
//��� ·���пո���*�����棬
������
5				//������
1 ODAC ODAC		//�½��ļ���
2 ODAC ODAC		//ɾ���ļ���
3 ODAC/b.txt ODAC\b.txt	//�½��ļ�
4 a.txt   a.txt			//ɾ���ļ�
3 yrversion.txt yrversion.txt	//�½��ļ�

*/



// CYrCarDetectAIOUpdateDlg dialog




CYrCarDetectAIOUpdateDlg::CYrCarDetectAIOUpdateDlg(CWnd* pParent /*=NULL*/)
: CDialog(CYrCarDetectAIOUpdateDlg::IDD, pParent)
, m_version(0)
, m_ip(_T("35.24.252.109:8089"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CYrCarDetectAIOUpdateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_VERSION, m_version);
	DDX_Text(pDX, IDC_EDIT_IP, m_ip);
}

BEGIN_MESSAGE_MAP(CYrCarDetectAIOUpdateDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CYrCarDetectAIOUpdateDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CYrCarDetectAIOUpdateDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CYrCarDetectAIOUpdateDlg message handlers

BOOL CYrCarDetectAIOUpdateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	//////////////////////////////////////////////////////////////
	// TODO: Add extra initialization here
	GetCurrentDirectory(MAX_PATH, CurrentDir);
	sprintf(updatedir,"%s\\yrupdate",CurrentDir);

	sd.InitData();
	stopflag=true;
	realstop=true;

	char str[1024];
	sprintf(str,"%s\\yrversion.txt",CurrentDir);

	if(!ReadVersionFile(str))
	{
		MessageBox("�޷���ȡ�����ذ汾�ļ�");
		m_version=0;
	}

	UpdateData(false);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CYrCarDetectAIOUpdateDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CYrCarDetectAIOUpdateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

DWORD WINAPI PlayThreadPROC(LPVOID lpParameter)
{
	CYrCarDetectAIOUpdateDlg *pDlg= (CYrCarDetectAIOUpdateDlg*)lpParameter;

	pDlg->realstop=false;
	while(pDlg->CheckVersion())
	{
		if(!pDlg->ReadUpdateList())
			break;


		if(	pDlg->stopflag)
			break;
	}
	pDlg->realstop =true;

	pDlg->GetDlgItem(IDOK)->EnableWindow(TRUE);
	return 0;

}
void CYrCarDetectAIOUpdateDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//OnOK();
	UpdateData(true);

	stopflag=false;
	realstop=true;
	pthread=CreateThread(NULL,0,PlayThreadPROC,this,0,NULL);

	GetDlgItem(IDOK)->EnableWindow(FALSE);

	UpdateData(false);

}

void CYrCarDetectAIOUpdateDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	if(false==realstop)
	{
		//�ȴ��߳��˳�
		stopflag=true;
		while(false ==realstop)
		{
			Sleep(100);
		}
	}
	else
	{
		sd.DestroyData();
		OnCancel();
	}
}


//���汾�ļ�
bool CYrCarDetectAIOUpdateDlg::ReadVersionFile(TCHAR* FileName)
{
	FILE *fp=_tfopen(FileName,_T("r"));
	if(fp)
	{
		_ftscanf(fp,_T("%d"),&m_version);
		fclose(fp);

		return TRUE;
	}
	else
		return FALSE;
}

bool CYrCarDetectAIOUpdateDlg::CheckVersion()
{
	char url[1024];
	char url2[1024];
	char str[1024];
	char fail[1024];

	int new_version=0;

	sprintf(str,"%s\\yrversion.txt",CurrentDir);

	if(!ReadVersionFile(str))
	{
		MessageBox("�޷���ȡ�����ذ汾�ļ�");
		m_version=0;
	}


	sprintf(url,"http://%s/yrupdate/topnew.txt",m_ip);

	EncodeURI(url,url2,1024);

	sprintf(str,"%s\\temp.txt",CurrentDir);

	if(!sd.HTTPDownload(url2,str,fail,10,0))
	{
		MessageBox("�޷����ӵ����·�����");
		return false;
	}

	FILE *fp=_tfopen(str,_T("r"));
	if(fp)
	{
		_ftscanf(fp,_T("%d"),&new_version);
		fclose(fp);

		if(new_version>m_version)
		{
			return true;
		}
		else
		{
			MessageBox("�Ѿ������°� �������");
			return false;
		}
	}
	else
	{
		MessageBox("�޷���ȡtemp�ļ�");
		return false;
	}

}


bool CYrCarDetectAIOUpdateDlg::ReadUpdateList()
{
	char tempstr[1024];

	char url[1024];
	char url2[1024];
	char fail[1024];

	sprintf(tempstr,"rmdir /s /q \"%s\"",updatedir);
	WinExec(tempstr,SW_HIDE);

	CreateDirectory(updatedir, NULL);
	//�����汾���ļ���
	sprintf(url,"http://%s/yrupdate/%d/updatelist.txt",m_ip,m_version);

	sprintf(tempstr,"%s\\updatelist.txt",updatedir);

	EncodeURI(url,url2,1024);

	if(!sd.HTTPDownload(url2,tempstr,fail,10,0))
	{
		UpdateData(false);
		MessageBox("�޷����ӵ����·����� ����updatelistʧ��");
		return false;
	}

	updateListTotal=0;
	int i;
	FILE *fp=_tfopen(tempstr,_T("r"));
	if(fp)
	{
		_ftscanf(fp,_T("%d"),&updateListTotal);
		if(updateListTotal>=MAX_UPDATE_FILE)
		{	
			fclose(fp);
			MessageBox("�����ļ��������ֵ �޷��Զ����� ����ϵ����Ա");
			return false;
		}
		//UPDALIST������ �ո���������·����Ҫ���пո�
		//��� ·���пո���*�����棬
		for(i=0;i<updateListTotal;i++)
		{
			_ftscanf(fp,_T("%d%s%s"),
				&(updateList[i].flag),
				updateList[i].srcurl,
				updateList[i].dstpath);
		}
		/* ������
		5				//������
		1 ODAC ODAC		//�½��ļ���
		2 ODAC ODAC		//ɾ���ļ���
		3 ODAC/b.txt ODAC\b.txt	//�½��ļ�
		4 a.txt   a.txt			//ɾ���ļ�
		3 yrversion.txt yrversion.txt	//�½��ļ�
		*/

		fclose(fp);
		return true;
	}
	else
	{
		MessageBox("��ȡupdatelistʧ��");
		return false;
	}
}