// YrCarDetectAIOUpdateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "YrCarDetectAIOUpdate.h"
#include "YrCarDetectAIOUpdateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//���±�־
enum UPDATE_FLAG
{
	UF_CREAT_DIR=1,
	UF_DELETE_DIR=2,
	UF_CREAT_FILE=3,
	UF_DELETE_FILE=4,

};

#if X64_UPDATE
#define UPDATEFILE "yrupdateX64"
#else
#define UPDATEFILE "yrupdate"
#endif
/*
TOMCAT������Ҫ����
\yrupdate �ļ���
����topnew.txt Ϊ���°汾��

\yrupdate\N\ ΪҪ��N�汾������M�汾�� �ļ���
\yrupdate\N\updatelist.txt Ϊ�����б�
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
, m_ip(_T("35.24.13.37:8089"))
{
	copyMyselfFlag=false;
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
	sprintf(updatedir,"%s\\%s",CurrentDir,UPDATEFILE);

	sd.InitData();
	stopflag=true;
	realstop=true;

	char str[1024]="";
	sprintf(str,"%s\\yrversion.txt",CurrentDir);

	if(!ReadVersionFile(str))
	{
		MessageBox("�޷���ȡ�����ذ汾�ļ�");
		m_version=0;
	}

	if(copyMyselfFlag)
	{
		OnBnClickedOk();
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
		if(	pDlg->stopflag)
			break;
		else
			pDlg->GetDlgItem(IDC_STATIC_INFO)->SetWindowText("���ڶ�ȡ�����б�..");
		//���б�
		if(!pDlg->ReadUpdateList())
			break;

		if(	pDlg->stopflag)
			break;
		else
			pDlg->GetDlgItem(IDC_STATIC_INFO)->SetWindowText("���������ļ�");

		//��������
		if(!pDlg->DownloadUpdateList())
			break;
		
		if(	pDlg->stopflag)
			break;
		else
			pDlg->GetDlgItem(IDC_STATIC_INFO)->SetWindowText("�����У�����ǿ��ֹͣ��ϵ�");
		//��������
		if(!pDlg->CopyUpdateList())
			break;
		
		if(	pDlg->stopflag)
			break;
		else
			pDlg->GetDlgItem(IDC_STATIC_INFO)->SetWindowText("�������");
	}

	pDlg->realstop =true;
	//���
	char tempstr[1024]="";
	sprintf(tempstr,"cmd /c rmdir /s /q \"%s\"",pDlg->updatedir);
	WinExec(tempstr,SW_HIDE);

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
		
		GetDlgItem(IDC_STATIC_INFO)->SetWindowText("�û�ȡ����ֹͣ��");
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
	char url[1024]="";
	char url2[1024]="";
	char str[1024]="";
	char fail[1024]="";

	int new_version=0;

	sprintf(str,"%s\\yrversion.txt",CurrentDir);

	if(!ReadVersionFile(str))
	{
		MessageBox("�޷���ȡ�����ذ汾�ļ�");
		m_version=0;
	}

	sprintf(url,"http://%s/%s/topnew.txt",m_ip,UPDATEFILE);

	EncodeURI(url,url2,1024);

	sprintf(str,"%s\\temp.txt",CurrentDir);

	if(!sd.HTTPDownload(url2,str,fail,10,0))
	{
		MessageBox("�޷����ӵ����·�����");
		return false;
	}
	//������ش���
	if(CheckError(str,"temp"))
		return false;

	FILE *fp=_tfopen(str,_T("r"));
	if(fp)
	{
		_ftscanf(fp,_T("%d"),&new_version);
		if(new_version<1)
		{	
			fclose(fp);
			MessageBox("���·����� ������topnew ����ϵ����Ա");
			return false;
		}
		fclose(fp);

		sprintf(str,"%d",m_version);
		if(!stopflag)
			GetDlgItem(IDC_STATIC_VERSION)->SetWindowText(str);

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
		return false;

}
bool CYrCarDetectAIOUpdateDlg::CheckError(char *filepath,char *filename)
{
	char str[256]="";
	FILE *fp=_tfopen(filepath,_T("rb"));
	if(fp)
	{
		fread(str,256,1,fp);
		fclose(fp);

		if(NULL==strstr(str,"Error report</title><style>"))
			return false;
		else
		{
			sprintf(str,"���·����� ������%s ����ϵ����Ա",filename);
			MessageBox(str);
			return true;
		}
	}
	else
	{
		sprintf(str,"�޷���ȡ%s�ļ�",filename);
		MessageBox(str);
		return true;
	}
}

// *�Ź��˳� �ո�
void CYrCarDetectAIOUpdateDlg::filterstr(char *str)
{
	while((*str) != '\0')
	{
		if('*'==(*str))
			(*str)=' ';

		str++;
	}

}

bool CYrCarDetectAIOUpdateDlg::ReadUpdateList()
{
	char tempstr[1024]="";

	char url[1024]="";
	char url2[1024]="";
	char fail[1024]="";

	sprintf(tempstr,"cmd /c rmdir /s /q \"%s\"",updatedir);
	WinExec(tempstr,SW_HIDE);
	Sleep(2000);

	CreateDirectory(updatedir, NULL);

	//�����汾���ļ���
	sprintf(url,"http://%s/%s/%d/updatelist.txt",m_ip,UPDATEFILE,m_version);

	sprintf(tempstr,"%s\\updatelist.txt",updatedir);

	EncodeURI(url,url2,1024);

	if(!sd.HTTPDownload(url2,tempstr,fail,10,0))
	{
		UpdateData(false);
		MessageBox("�޷����ӵ����·����� ����updatelistʧ��");
		return false;
	}
	//������ش���
	if(CheckError(tempstr,"updatelist"))
		return false;

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
		if(updateListTotal<1)
		{	
			fclose(fp);
			MessageBox("���·����� ������updatelist ����ϵ����Ա");
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

			// *�Ź��˳� �ո�
			filterstr(updateList[i].srcurl);
			filterstr(updateList[i].dstpath);
			//����COPY����
			if(false ==copyMyselfFlag &&
				0==strcmp(updateList[i].dstpath,"YrCarDetectAIOUpdate.exe"))
			{
				sprintf(url,"%s\\YrCarDetectAIOUpdate.exe",CurrentDir);
				sprintf(url2,"%s\\YrCarDetectAIOUpdate_old.exe",CurrentDir);
				CopyFile(url,url2,FALSE);
				sprintf(tempstr,"copy%s",m_ip);
				ShellExecute(this->m_hWnd, NULL,url2,tempstr, CurrentDir, SW_NORMAL);
				 exit(0);
			}

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
		return false;
}


bool CYrCarDetectAIOUpdateDlg::DownloadUpdateList()
{
	char tempstr[1024]="";

	char url[1024]="";
	char url2[1024]="";
	char fail[1024]="";

	for(int i=0;i<updateListTotal;i++)
	{
		switch(updateList[i].flag)
		{
		case UF_CREAT_DIR:
			sprintf(tempstr,"%s\\%s",updatedir,updateList[i].dstpath);
			CreateDirectory(tempstr, NULL);
			break;
		case UF_CREAT_FILE:
			sprintf(url,"http://%s/%s/%d/%s",m_ip,UPDATEFILE,m_version,updateList[i].srcurl);
			sprintf(tempstr,"%s\\%s",updatedir,updateList[i].dstpath);

			EncodeURI(url,url2,1024);
			if(!sd.HTTPDownload(url2,tempstr,fail,10,0))
			{
				UpdateData(false);
				MessageBox("�޷����ӵ����·����� ����updatelistʧ��");
				return false;
			}
			//������ش���
			if(CheckError(tempstr,updateList[i].dstpath))
				return false;

			break;
		default:break;
		}
	}
	return true;
}

//���������
bool CYrCarDetectAIOUpdateDlg::CopyUpdateList()
{
	char tempstr[1024]="";

	char tempstr2[1024]="";

	for(int i=0;i<updateListTotal;i++)
	{
		switch(updateList[i].flag)
		{
		case UF_CREAT_DIR:
			sprintf(tempstr,"%s\\%s",CurrentDir,updateList[i].dstpath);
			CreateDirectory(tempstr, NULL);
			break;
		case UF_DELETE_DIR:
			sprintf(tempstr,"cmd /c rmdir /s /q \"%s\\%s\"",CurrentDir,updateList[i].dstpath);
			WinExec(tempstr,SW_HIDE);
			Sleep(2000);
			break;
		case UF_CREAT_FILE:
			sprintf(tempstr,"%s\\%s",updatedir,updateList[i].dstpath);
			sprintf(tempstr2,"%s\\%s",CurrentDir,updateList[i].dstpath);	
			CopyFile(tempstr,tempstr2,FALSE);
			break;
		case UF_DELETE_FILE:
			sprintf(tempstr,"%s\\%s",CurrentDir,updateList[i].dstpath);
			DeleteFile(tempstr);
			break;
		default:break;
		}
	}
	return true;
}