// DLGSetSystem.cpp : implementation file
//

#include "stdafx.h"
#include "yirongcardetectaio.h"
#include "DLGSetSystem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "DLGWarnning.h"
/////////////////////////////////////////////////////////////////////////////
// CDLGSetSystem dialog


CDLGSetSystem::CDLGSetSystem(CWnd* pParent /*=NULL*/)
	: CDialog(CDLGSetSystem::IDD, pParent)
	, m_display_preview(FALSE)
	, m_update_url(_T(""))
	, m_check_update(FALSE)
{
	//{{AFX_DATA_INIT(CDLGSetSystem)
	m_check_alarmpic = TRUE;
	m_check_alarmwav = FALSE;
	m_check_ftp = FALSE;
	m_display_preview=TRUE;
	m_recordfull = 1;
	m_path_alarmwav = _T("bj.wav");
	m_path_capbmp = _T("D:\\YRCapturePic");
	m_path_detect = _T("D:\\YRCarDetectResult");
	m_path_record = _T("D:\\YRRecord");
	m_record_cuttime = 20;
	m_ftp_ip = _T("");
	m_ftp_port = _T("");
	m_ftp_psw = _T("");
	m_ftp_user = _T("");
	m_check_savenet = FALSE;
	m_path_dahua = _T("�󻪲�����\\player264demo.exe");
	m_path_haikang = _T("����������\\VSPlayer.exe");
	m_path_yaan = _T("�ǰ�������\\RealMp4Play.exe");
	m_ftp_path = _T("/");
	m_tomcat_dir = _T("D:\\tomcatname\\webapps\\YRCapturePic");
	m_tomcat_url = _T("http://10.142.50.126:8089/YRCapturePic");
	m_update_url = _T("10.142.50.126:8089");
	m_check_update=TRUE;
	//}}AFX_DATA_INIT

}


void CDLGSetSystem::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDLGSetSystem)
	DDX_Check(pDX, IDC_CHECK_ALARM_PIC, m_check_alarmpic);
	DDX_Check(pDX, IDC_CHECK_ALARM_WAV, m_check_alarmwav);
	DDX_Check(pDX, IDC_CHECK_FTP, m_check_ftp);
	DDX_CBIndex(pDX, IDC_COMBO_RECORDFULL, m_recordfull);
	DDX_Text(pDX, IDC_EDIT_ALARM_WAV, m_path_alarmwav);
	DDV_MaxChars(pDX, m_path_alarmwav, 260);
	DDX_Text(pDX, IDC_EDIT_CAPBMP_DIR, m_path_capbmp);
	DDV_MaxChars(pDX, m_path_capbmp, 260);
	DDX_Text(pDX, IDC_EDIT_DETECT_DIR, m_path_detect);
	DDV_MaxChars(pDX, m_path_detect, 260);
	DDX_Text(pDX, IDC_EDIT_RECORD_DIR, m_path_record);
	DDV_MaxChars(pDX, m_path_record, 260);
	DDX_Text(pDX, IDC_EDIT_TIME, m_record_cuttime);
	DDV_MinMaxInt(pDX, m_record_cuttime, 1, 60);
	DDX_Text(pDX, IDC_EDIT_FTP_IPADDR, m_ftp_ip);
	DDV_MaxChars(pDX, m_ftp_ip, 32);
	DDX_Text(pDX, IDC_EDIT_FTP_PORT, m_ftp_port);
	DDV_MaxChars(pDX, m_ftp_port, 32);
	DDX_Text(pDX, IDC_EDIT_FTP_PSW, m_ftp_psw);
	DDV_MaxChars(pDX, m_ftp_psw, 32);
	DDX_Text(pDX, IDC_EDIT_FTP_USER, m_ftp_user);
	DDV_MaxChars(pDX, m_ftp_user, 32);
	DDX_Check(pDX, IDC_CHECK_SAVENET, m_check_savenet);
	DDX_Text(pDX, IDC_EDIT_DAHUA_PATH, m_path_dahua);
	DDV_MaxChars(pDX, m_path_dahua, 260);
	DDX_Text(pDX, IDC_EDIT_HAIKANG_PATH, m_path_haikang);
	DDV_MaxChars(pDX, m_path_haikang, 260);
	DDX_Text(pDX, IDC_EDIT_YAAN_PATH, m_path_yaan);
	DDV_MaxChars(pDX, m_path_yaan, 260);
	DDX_Text(pDX, IDC_EDIT_FTP_PATH, m_ftp_path);
	DDV_MaxChars(pDX, m_ftp_path, 260);
	DDX_Text(pDX, IDC_EDIT_TOMCAT_DIR, m_tomcat_dir);
	DDX_Text(pDX, IDC_EDIT_TOMCAT_URL, m_tomcat_url);
	//}}AFX_DATA_MAP
	DDX_Check(pDX, IDC_DISPLAY_PREVIEW, m_display_preview);
	DDX_Text(pDX, IDC_EDIT_UPDATEURL, m_update_url);
	DDX_Check(pDX, IDC_CHECK_UPDATE, m_check_update);
	DDX_Control(pDX, IDOK, m_b_ok);
	DDX_Control(pDX, IDCANCEL, m_b_cancel);
	DDX_Control(pDX, IDC_BUTTON_ALARM_WAV, m_b_alarmwav);
	DDX_Control(pDX, IDC_BUTTON_DETECT_DIR, m_b_detectdir);
	DDX_Control(pDX, IDC_BUTTON_RECORD_DIR, m_b_recorddir);
	DDX_Control(pDX, IDC_BUTTON_CAPBMP_DIR, m_b_cambmpdir);
	DDX_Control(pDX, IDC_BUTTON_HAIKANG_PATH, m_b_haikangpath);
	DDX_Control(pDX, IDC_BUTTON_DAHUA_PATH, m_b_dahuapath);
	DDX_Control(pDX, IDC_BUTTON_YAAN_PATH, m_b_yaanpath);
	DDX_Control(pDX, IDC_BUTTON_TOMCAT_DIR, m_b_tomcatdir);
}


BEGIN_MESSAGE_MAP(CDLGSetSystem, CDialog)
	//{{AFX_MSG_MAP(CDLGSetSystem)
	ON_BN_CLICKED(IDC_BUTTON_ALARM_WAV, OnButtonAlarmWav)
	ON_BN_CLICKED(IDC_BUTTON_DETECT_DIR, OnButtonDetectDir)
	ON_BN_CLICKED(IDC_BUTTON_RECORD_DIR, OnButtonRecordDir)
	ON_BN_CLICKED(IDC_BUTTON_CAPBMP_DIR, OnButtonCapbmpDir)
	ON_BN_CLICKED(IDC_BUTTON_HAIKANG_PATH, OnButtonHaikangPath)
	ON_BN_CLICKED(IDC_BUTTON_DAHUA_PATH, OnButtonDahuaPath)
	ON_BN_CLICKED(IDC_BUTTON_YAAN_PATH, OnButtonYaanPath)
	ON_BN_CLICKED(IDC_BUTTON_TOMCAT_DIR, OnButtonTomcatDir)
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDLGSetSystem message handlers
BOOL CDLGSetSystem::OnInitDialog()
{
	CDialog::OnInitDialog();

	Read2Dlg();
	UpdateData(FALSE);

#if OPEN_VS2008_POCO_FTP

	GetDlgItem(IDC_STATIC_FTP)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC_FTP_IP)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC_FTP_PORT)->ShowWindow(TRUE);	
	GetDlgItem(IDC_STATIC_FTP_USER)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC_FTP_PSW)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDIT_FTP_IPADDR)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDIT_FTP_PORT)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDIT_FTP_USER)->ShowWindow(TRUE);	
	GetDlgItem(IDC_EDIT_FTP_PSW)->ShowWindow(TRUE);

	GetDlgItem(IDC_CHECK_FTP)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC_FTP_PATH)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDIT_FTP_PATH)->ShowWindow(TRUE);
#endif

#if ALLTAB_CLIENT_MODE

	m_check_savenet = TRUE;
	GetDlgItem(IDC_CHECK_SAVENET)->ShowWindow(FALSE);

	m_display_preview=TRUE;
	GetDlgItem(IDC_DISPLAY_PREVIEW)->ShowWindow(FALSE);
	
#endif


#if (OPEN_TOMCAT_MODE && !ALLTAB_CLIENT_MODE)
	
	GetDlgItem(IDC_STATIC_TOMCAT_DIR)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC_TOMCAT_URL)->ShowWindow(TRUE);

	GetDlgItem(IDC_EDIT_TOMCAT_DIR)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDIT_TOMCAT_URL)->ShowWindow(TRUE);
	GetDlgItem(IDC_BUTTON_TOMCAT_DIR)->ShowWindow(TRUE);

#endif

	m_b_ok.LoadBitmaps(IDB_OK_BUTTON,IDB_OK_BUTTON_MOVE,NULL,NULL);
	m_b_ok.SizeToContent();		//����ӦͼƬ��С

	m_b_cancel.LoadBitmaps(IDB_CANCEL_BUTTON,IDB_CANCEL_BUTTON_MOVE,NULL,NULL);
	m_b_cancel.SizeToContent();		//����ӦͼƬ��С

	m_b_alarmwav.LoadBitmaps(IDB_VIEW_BUTTON,IDB_VIEW_BUTTON_MOVE,NULL,NULL);
	m_b_alarmwav.SizeToContent();		//����ӦͼƬ��С

	m_b_detectdir.LoadBitmaps(IDB_VIEW_BUTTON,IDB_VIEW_BUTTON_MOVE,NULL,NULL);
	m_b_detectdir.SizeToContent();		//����ӦͼƬ��С

	m_b_recorddir.LoadBitmaps(IDB_VIEW_BUTTON,IDB_VIEW_BUTTON_MOVE,NULL,NULL);
	m_b_recorddir.SizeToContent();		//����ӦͼƬ��С

	m_b_cambmpdir.LoadBitmaps(IDB_VIEW_BUTTON,IDB_VIEW_BUTTON_MOVE,NULL,NULL);
	m_b_cambmpdir.SizeToContent();		//����ӦͼƬ��С

	m_b_haikangpath.LoadBitmaps(IDB_VIEW_BUTTON,IDB_VIEW_BUTTON_MOVE,NULL,NULL);
	m_b_haikangpath.SizeToContent();		//����ӦͼƬ��С

	m_b_dahuapath.LoadBitmaps(IDB_VIEW_BUTTON,IDB_VIEW_BUTTON_MOVE,NULL,NULL);
	m_b_dahuapath.SizeToContent();		//����ӦͼƬ��С

	m_b_yaanpath.LoadBitmaps(IDB_VIEW_BUTTON,IDB_VIEW_BUTTON_MOVE,NULL,NULL);
	m_b_yaanpath.SizeToContent();		//����ӦͼƬ��С

	m_b_tomcatdir.LoadBitmaps(IDB_VIEW_BUTTON,IDB_VIEW_BUTTON_MOVE,NULL,NULL);
	m_b_tomcatdir.SizeToContent();		//����ӦͼƬ��С

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDLGSetSystem::OnButtonAlarmWav() 
{
	// TODO: Add your control notification handler code here
	char szFilter[]="wav Files (*.wav)|*.wav||";
	CFileDialog dlg(TRUE,"wav","",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		szFilter);
	if(dlg.DoModal()==IDOK)
	{
		//�ļ�·��
		m_path_alarmwav=dlg.GetPathName();
		UpdateData(FALSE);
	}
}

void CDLGSetSystem::OnButtonDetectDir() 
{
	// TODO: Add your control notification handler code here
	//����Ŀ¼
	BROWSEINFO   bi;                           //����BROWSEINFO�ṹ��
	TCHAR   Buffer[512]= " ";
	TCHAR   FullPath[512]= " ";
	bi.hwndOwner   =   GetSafeHwnd();               //���ھ��
	bi.pidlRoot   =   NULL;
	bi.pszDisplayName   =   Buffer;            //����ѡ���Ŀ¼���Ļ�����
	bi.lpszTitle   =   "Selection ";           //�����Ĵ��ڵ�������ʾ
	bi.ulFlags   =   BIF_RETURNONLYFSDIRS   ;  //ֻ����Ŀ¼��������־��MSDN
	bi.lpfn   =   NULL;               //�ص���������ʱ������
	bi.lParam   =   0;
	bi.iImage   =   0;
	ITEMIDLIST*   pidl   =   ::SHBrowseForFolder(&bi);   //��ʾ�������ڣ�ITEMIDLIST����Ҫ
	if(::SHGetPathFromIDList(pidl,FullPath)) //��ITEMIDLIST�еõ�Ŀ¼��������·��
	{
		m_path_detect=FullPath;
		UpdateData(FALSE);
	}
}

void CDLGSetSystem::OnButtonRecordDir() 
{
	// TODO: Add your control notification handler code here
	BROWSEINFO   bi;                           //����BROWSEINFO�ṹ��
	TCHAR   Buffer[512]= " ";
	TCHAR   FullPath[512]= " ";
	bi.hwndOwner   =   GetSafeHwnd();               //���ھ��
	bi.pidlRoot   =   NULL;
	bi.pszDisplayName   =   Buffer;            //����ѡ���Ŀ¼���Ļ�����
	bi.lpszTitle   =   "Selection ";           //�����Ĵ��ڵ�������ʾ
	bi.ulFlags   =   BIF_RETURNONLYFSDIRS   ;  //ֻ����Ŀ¼��������־��MSDN
	bi.lpfn   =   NULL;               //�ص���������ʱ������
	bi.lParam   =   0;
	bi.iImage   =   0;
	ITEMIDLIST*   pidl   =   ::SHBrowseForFolder(&bi);   //��ʾ�������ڣ�ITEMIDLIST����Ҫ
	if(::SHGetPathFromIDList(pidl,FullPath)) //��ITEMIDLIST�еõ�Ŀ¼��������·��
	{
		m_path_record=FullPath;
		UpdateData(FALSE);
	}
}

void CDLGSetSystem::OnButtonCapbmpDir() 
{
	// TODO: Add your control notification handler code here
	BROWSEINFO   bi;                           //����BROWSEINFO�ṹ��
	TCHAR   Buffer[512]= " ";
	TCHAR   FullPath[512]= " ";
	bi.hwndOwner   =   GetSafeHwnd();               //���ھ��
	bi.pidlRoot   =   NULL;
	bi.pszDisplayName   =   Buffer;            //����ѡ���Ŀ¼���Ļ�����
	bi.lpszTitle   =   "Selection ";           //�����Ĵ��ڵ�������ʾ
	bi.ulFlags   =   BIF_RETURNONLYFSDIRS   ;  //ֻ����Ŀ¼��������־��MSDN
	bi.lpfn   =   NULL;               //�ص���������ʱ������
	bi.lParam   =   0;
	bi.iImage   =   0;
	ITEMIDLIST*   pidl   =   ::SHBrowseForFolder(&bi);   //��ʾ�������ڣ�ITEMIDLIST����Ҫ
	if(::SHGetPathFromIDList(pidl,FullPath)) //��ITEMIDLIST�еõ�Ŀ¼��������·��
	{
		m_path_capbmp=FullPath;
		UpdateData(FALSE);
	}
}

void CDLGSetSystem::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	
	if(m_record_cuttime < 1 || m_record_cuttime >60)
		return ;

	Dlg2Write();

	//�����ļ���
	CreateDirectory(m_path_capbmp, NULL);
	CreateDirectory(m_path_detect, NULL);
	CreateDirectory(m_path_record, NULL);

	CDialog::OnOK();
}

void CDLGSetSystem::OnCancel() 
{
	// TODO: Add extra cleanup here
	//�ض�
	Read2Dlg();
	UpdateData(FALSE);
	CDialog::OnCancel();
}

void CDLGSetSystem::Read2Dlg() 
{
	//�����ļ��Ƿ����
	FILE *fp=NULL;
	fp=fopen(SystemIniPath,"r");
	if(fp)
		fclose(fp);
	else
	{
		//��������д����˳�
		Dlg2Write();
		CreateDirectory(m_path_capbmp, NULL);
		CreateDirectory(m_path_detect, NULL);
		CreateDirectory(m_path_record, NULL);

		return;
	}

	readini(SystemIniPath);
}

void CDLGSetSystem::Dlg2Write() 
{
	writeini(SystemIniPath);
}
//����
void CDLGSetSystem::InputIni() 
{
	CDLGWarnning dlgw;
	dlgw.m_wintxt="ϵͳ���õ��뾯��";
	dlgw.m_warntxt="���������ļ���ʹԭ���ñ�����";
	int nResponse=dlgw.DoModal();
	if (nResponse == IDOK)
	{
		char szFilter[]="systeminfo Files (*.ini)|*.ini|*.*|*.*||";
		CFileDialog dlg(TRUE,"ini","",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
			szFilter);
		if(dlg.DoModal()==IDOK)
		{
			//�����ļ�
			CopyFile(dlg.GetPathName(),SystemIniPath,FALSE);
		}
	}
	else if (nResponse == IDCANCEL)
		return ;
	else
		return ;

}
//����
void CDLGSetSystem::OutputIni() 
{
	//�����ļ�
	char szFilter[]="systeminfo Files (*.ini)|*.ini|*.*|*.*||";
	CFileDialog dlg(FALSE,"ini","",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		szFilter);
	if(dlg.DoModal()==IDOK)
	{
		//�����ļ�
		CopyFile(SystemIniPath,dlg.GetPathName(),FALSE);
	}
}

//��INI
void CDLGSetSystem::readini(char *path) 
{
	int	check_alarmpic;
	int	check_alarmwav;
	int	check_ftp;
	int check_savenet;
	int		recordfull;
	char	path_alarmwav[ZOG_MAX_PATH_STR]="";
	char	path_capbmp[ZOG_MAX_PATH_STR]="";
	char	path_detect[ZOG_MAX_PATH_STR]="";
	char	path_record[ZOG_MAX_PATH_STR]="";
	int		record_cuttime;
	char	ftp_ip[ZOG_MAX_NAME_STR]="";
	char	ftp_port[ZOG_MAX_NAME_STR]="";
	char	ftp_user[ZOG_MAX_NAME_STR]="";
	char	ftp_psw[ZOG_MAX_NAME_STR]="";
	char	ftp_psw_ext[(ZOG_MAX_NAME_STR+1)*5]="";
	char	ftp_path[ZOG_MAX_NAME_STR]="";

	char	path_dahua[ZOG_MAX_PATH_STR]="";
	char	path_haikang[ZOG_MAX_PATH_STR]="";
	char	path_yaan[ZOG_MAX_PATH_STR]="";

	char	tomcat_dir[ZOG_MAX_PATH_STR] = "";
	char	tomcat_url[ZOG_MAX_PATH_STR] = ""; 
	char	update_url[ZOG_MAX_PATH_STR] = ""; 
	int check_displaypreview;
	int check_update;
	////////////////////////////////////
	if(GetPrivateProfileStruct("Alarm", "CheckPic", &check_alarmpic, sizeof(int), path))
		m_check_alarmpic=check_alarmpic;
	if(GetPrivateProfileStruct("Alarm", "CheckWav", &check_alarmwav, sizeof(int), path))
		m_check_alarmwav=check_alarmwav;
	if(GetPrivateProfileStruct("Alarm", "CheckSaveNet", &check_savenet, sizeof(int), path))
		m_check_savenet=check_savenet;
	if(GetPrivateProfileString("Alarm", "PathAlarmWav", "", path_alarmwav, ZOG_MAX_PATH_STR, path))
		m_path_alarmwav=path_alarmwav;
	if(GetPrivateProfileString("Alarm", "PathDetect", "", path_detect, ZOG_MAX_PATH_STR, path))
		m_path_detect=path_detect;
	////////////////////////////////////
	if(GetPrivateProfileStruct("Record", "CutTime", &record_cuttime, sizeof(int), path))
		m_record_cuttime=record_cuttime;
	if(GetPrivateProfileStruct("Record", "RecordFull", &recordfull, sizeof(int), path))
		m_recordfull=recordfull;
	if(GetPrivateProfileString("Record", "PathRecord", "", path_record, ZOG_MAX_PATH_STR, path))
		m_path_record=path_record;
	if(GetPrivateProfileString("Record", "PathCapbmp", "", path_capbmp, ZOG_MAX_PATH_STR, path))
		m_path_capbmp=path_capbmp;
	////////////////////////////////////
	if(GetPrivateProfileString("Play", "PathDahua", "", path_dahua, ZOG_MAX_PATH_STR, path))
		m_path_dahua=path_dahua;
	if(GetPrivateProfileString("Play", "PathHaikang", "", path_haikang, ZOG_MAX_PATH_STR, path))
		m_path_haikang=path_haikang;
	if(GetPrivateProfileString("Play", "PathYaan", "", path_yaan, ZOG_MAX_PATH_STR, path))
		m_path_yaan=path_yaan;
	////////////////////////////////////
	if(GetPrivateProfileStruct("FTP", "check", &check_ftp, sizeof(int), path))
		m_check_ftp=check_ftp;
	if(GetPrivateProfileString("FTP", "ip", "", ftp_ip, ZOG_MAX_NAME_STR, path))
		m_ftp_ip=ftp_ip;
	if(GetPrivateProfileString("FTP", "port", "", ftp_port, ZOG_MAX_NAME_STR, path))
		m_ftp_port=ftp_port;
	if(GetPrivateProfileString("FTP", "user", "", ftp_user, ZOG_MAX_NAME_STR, path))
		m_ftp_user=ftp_user;
	if(GetPrivateProfileString("FTP", "password", "", ftp_psw_ext, (ZOG_MAX_NAME_STR+1)*5, path))
	{
		if(0!=strlen(ftp_psw_ext))
		{
			ZogDeCode(ftp_psw_ext,ftp_psw);
			m_ftp_psw=ftp_psw;
		}
	}
	if(GetPrivateProfileString("FTP", "path", "", ftp_path, ZOG_MAX_PATH_STR, path))
		m_ftp_path=ftp_path;

	if(GetPrivateProfileString("TomCat", "Dir", "", tomcat_dir, ZOG_MAX_PATH_STR, path))
		m_tomcat_dir=tomcat_dir;
	if(GetPrivateProfileString("TomCat", "Url", "", tomcat_url, ZOG_MAX_PATH_STR, path))
		m_tomcat_url=tomcat_url;

	if(GetPrivateProfileString("Update", "Url", "", update_url, ZOG_MAX_PATH_STR, path))
		m_update_url=update_url;
	if(GetPrivateProfileStruct("Update", "CheckAuto", &check_update, sizeof(int), path))
		m_check_update=check_update;
	
	
	if(GetPrivateProfileStruct("View", "CheckDisplayPreview", &check_displaypreview, sizeof(int), path))
		m_display_preview=check_displaypreview;

	CreateDirectory(m_path_capbmp, NULL);
	CreateDirectory(m_path_detect, NULL);
	CreateDirectory(m_path_record, NULL);

#if ALLTAB_CLIENT_MODE
	m_display_preview=TRUE;
	m_check_savenet=TRUE;
#endif

}
//дini
void CDLGSetSystem::writeini(char *path)
{
	////////////////////////////////////
	WritePrivateProfileStruct("Alarm", "CheckPic", &m_check_alarmpic, sizeof(int), path);
	WritePrivateProfileStruct("Alarm", "CheckWav", &m_check_alarmwav, sizeof(int), path);
	WritePrivateProfileStruct("Alarm", "CheckSaveNet", &m_check_savenet, sizeof(int), path);
	
	WritePrivateProfileString("Alarm", "PathAlarmWav", m_path_alarmwav.GetBuffer(0),path);
	WritePrivateProfileString("Alarm", "PathDetect", m_path_detect.GetBuffer(0),path);
	////////////////////////////////////
	WritePrivateProfileStruct("Record", "CutTime", &m_record_cuttime, sizeof(int), path);
	WritePrivateProfileStruct("Record", "RecordFull", &m_recordfull, sizeof(int), path);
	WritePrivateProfileString("Record", "PathRecord",  m_path_record.GetBuffer(0),  path);
	WritePrivateProfileString("Record", "PathCapbmp",  m_path_capbmp.GetBuffer(0), path);
	////////////////////////////////////
	WritePrivateProfileString("Play", "PathDahua",  m_path_dahua.GetBuffer(0),  path);
	WritePrivateProfileString("Play", "PathHaikang",  m_path_haikang.GetBuffer(0), path);
	WritePrivateProfileString("Play", "PathYaan",  m_path_yaan.GetBuffer(0), path);
	////////////////////////////////////
	WritePrivateProfileStruct("FTP", "check", &m_check_ftp, sizeof(int), path);
	WritePrivateProfileString("FTP", "ip", m_ftp_ip.GetBuffer(0), path);
	WritePrivateProfileString("FTP", "port", m_ftp_port.GetBuffer(0), path);
	WritePrivateProfileString("FTP", "user",  m_ftp_user.GetBuffer(0), path);

	char	ftp_psw_ext[(ZOG_MAX_NAME_STR+1)*5]="";
	ZogEnCode(m_ftp_psw.GetBuffer(0),ftp_psw_ext);
	WritePrivateProfileString("FTP", "password",  ftp_psw_ext, path);

	WritePrivateProfileString("FTP", "path",  m_ftp_path.GetBuffer(0), path);

	WritePrivateProfileString("TomCat", "Dir",  m_tomcat_dir.GetBuffer(0), path);
	WritePrivateProfileString("TomCat", "Url",  m_tomcat_url.GetBuffer(0), path);
	WritePrivateProfileString("Update", "Url",  m_update_url.GetBuffer(0), path);
	WritePrivateProfileStruct("Update", "CheckAuto", &m_check_update, sizeof(int), path);

	WritePrivateProfileStruct("View", "CheckDisplayPreview", &m_display_preview, sizeof(int), path);
	
}

void CDLGSetSystem::OnButtonHaikangPath() 
{
	// TODO: Add your control notification handler code here
	char szFilter[]="HaiKang Play Executable Files (*.exe)|*.exe|*.*|*.*||";
	CFileDialog dlg(TRUE,"exe","",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		szFilter);
	if(dlg.DoModal()==IDOK)
	{
		m_path_haikang=dlg.GetPathName();
		UpdateData(FALSE);
	}
}

void CDLGSetSystem::OnButtonDahuaPath() 
{
	// TODO: Add your control notification handler code here
	char szFilter[]="DaHua Play Executable Files (*.exe)|*.exe|*.*|*.*||";
	CFileDialog dlg(TRUE,"exe","",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		szFilter);
	if(dlg.DoModal()==IDOK)
	{
		m_path_dahua=dlg.GetPathName();
		UpdateData(FALSE);
	}
}

void CDLGSetSystem::OnButtonYaanPath() 
{
	// TODO: Add your control notification handler code here
	char szFilter[]="YaAn Play Executable Files (*.exe)|*.exe|*.*|*.*||";
	CFileDialog dlg(TRUE,"exe","",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		szFilter);
	if(dlg.DoModal()==IDOK)
	{
		m_path_yaan=dlg.GetPathName();
		UpdateData(FALSE);
	}
}

void CDLGSetSystem::OnButtonTomcatDir() 
{
	// TODO: Add your control notification handler code here
	//����Ŀ¼
	BROWSEINFO   bi;                           //����BROWSEINFO�ṹ��
	TCHAR   Buffer[512]= " ";
	TCHAR   FullPath[512]= " ";
	bi.hwndOwner   =   GetSafeHwnd();               //���ھ��
	bi.pidlRoot   =   NULL;
	bi.pszDisplayName   =   Buffer;            //����ѡ���Ŀ¼���Ļ�����
	bi.lpszTitle   =   "Selection ";           //�����Ĵ��ڵ�������ʾ
	bi.ulFlags   =   BIF_RETURNONLYFSDIRS   ;  //ֻ����Ŀ¼��������־��MSDN
	bi.lpfn   =   NULL;               //�ص���������ʱ������
	bi.lParam   =   0;
	bi.iImage   =   0;
	ITEMIDLIST*   pidl   =   ::SHBrowseForFolder(&bi);   //��ʾ�������ڣ�ITEMIDLIST����Ҫ
	if(::SHGetPathFromIDList(pidl,FullPath)) //��ITEMIDLIST�еõ�Ŀ¼��������·��
	{
		m_tomcat_dir=FullPath;
		UpdateData(FALSE);
	}
}



void CDLGSetSystem::OnPaint()
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
HBRUSH CDLGSetSystem::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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