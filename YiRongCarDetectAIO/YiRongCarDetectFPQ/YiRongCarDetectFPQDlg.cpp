// YiRongCarDetectFPQDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "YiRongCarDetectFPQ.h"
#include "YiRongCarDetectFPQDlg.h"

#include "IO.h"
IO OracleIO;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CYiRongCarDetectFPQDlg �Ի���




CYiRongCarDetectFPQDlg::CYiRongCarDetectFPQDlg(CWnd* pParent /*=NULL*/)
: CDialog(CYiRongCarDetectFPQDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CYiRongCarDetectFPQDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CYiRongCarDetectFPQDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CYiRongCarDetectFPQDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CYiRongCarDetectFPQDlg::OnBnClickedCancel)
	ON_WM_SIZE()
	ON_WM_TIMER()
END_MESSAGE_MAP()

//�߳�
DWORD WINAPI ORACLE_ThreadPROC(LPVOID lpParameter)
{
	CYiRongCarDetectFPQDlg *pdlg = (CYiRongCarDetectFPQDlg*)lpParameter;
	pdlg->ThreadFlag=TRUE;

	long long Missionid=0;

	unsigned long int camid=0;
	unsigned long int isplay=0;
	unsigned long int userid=0;
	char indate[32];

	long DetectDeviceID=0;

	while(pdlg->ThreadFlag)
	{
		Missionid=0;
		camid=0;
		isplay=0;
		userid=0;
		DetectDeviceID=0;
		indate[0]=0;

		//ORACLE��ѯ���� �ַ�
		if(OracleIO.MISSION_Read(&Missionid,&camid,&isplay,&userid,indate)<0)
		{
			pdlg->ThreadFlag=FALSE;
			return 0;
		}

		if(isplay)
		{
			//��ʼ
			OracleIO.DEVICE_SearchForStop(&DetectDeviceID,camid);

			if(DetectDeviceID>0)
			{
				// �Ѿ���ʼ ʧЧ����
				OracleIO.MISSION_Edit( Missionid,0,2);
			}
			else
			{
				OracleIO.DEVICE_SearchForStart(&DetectDeviceID);

				if(DetectDeviceID>0)
				{
					//��Ч
					//Ԥռ��ʶ���������
					OracleIO.DETECT_EditCamera(DetectDeviceID,Missionid,camid);
					//�޸�����
					OracleIO.MISSION_Edit( Missionid,DetectDeviceID,1);
				}
				else
				{
					//����
					OracleIO.MISSION_Edit( Missionid,0,2);
				}
			}
		}
		else
		{
			//ֹͣ
			OracleIO.DEVICE_SearchForStop(&DetectDeviceID,camid);

			if(DetectDeviceID>0)
			{
				//��Ч
				OracleIO.MISSION_Edit( Missionid,DetectDeviceID,1);
			}
			else
			{
				// ���ֹͣ  ʧЧ����
				OracleIO.MISSION_Edit( Missionid,0,2);
			}
		}

		Sleep(200);
	}

	pdlg->ThreadFlag=FALSE;
	return 0;
}
// CYiRongCarDetectFPQDlg ��Ϣ�������

BOOL CYiRongCarDetectFPQDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������


	DlgDetectDevice.Create(IDD_DETECT_DEVICE,this);
	DlgDetectDevice.ShowWindow(SW_SHOW);

	////////////////lynn/////////////////
	int OracleError = OracleIO.ConnectionOracleDBTXT("YRDataBaseConfig.db");
	if(OracleError == ReadFile_FAIL)
	{
		this->MessageBox("�����ݿ������ļ�ʧ��","�������ݿ�");

		return FALSE;
	}
	else if(OracleError == Instance_FAIL)
	{
		this->MessageBox("���ݿ�ADO��ʼ��ʧ��","�������ݿ�");
		return FALSE;
	}
	else if(OracleError == ContOpen_FAIL)
	{
		this->MessageBox("���ݿ��޷�����:�˺�����IP�쳣 ���ļ��д�()","�������ݿ�");
		return FALSE;
	}
	else if(OracleError == Connectd_DONE)
	{
		//MessageBox("�������ݿ�ɹ�");
	}


	ThreadFlag=FALSE;
	pthread=NULL;

	pthread=CreateThread(NULL,0,ORACLE_ThreadPROC,this,0,NULL);

	if(NULL==pthread)
	{
		MessageBox("�����̴߳���");
	}
	else
		ThreadFlag=TRUE;


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CYiRongCarDetectFPQDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CYiRongCarDetectFPQDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CYiRongCarDetectFPQDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CYiRongCarDetectFPQDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//OnOK();
}

void CYiRongCarDetectFPQDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	ThreadFlag=FALSE;
	Sleep(1000);
	TerminateThread(pthread,0);

	OracleIO.DisConnectionOracleDB();
	OnCancel();
}

void CYiRongCarDetectFPQDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	//������С���봰�ڴ�С�ޱ仯������
	if ((cx ==0 && cy == 0) || 
		(cx == m_clientRect.Width() && cy == m_clientRect.Height())) 
	{
		return;
	}
	else
	{
		UpdatePannelPosition();

		DlgDetectDevice.AutoSize();

		Invalidate();
	}
}
void CYiRongCarDetectFPQDlg::UpdatePannelPosition()
{
	GetClientRect(&m_clientRect);
	/*
	int button_top=40;

	CRect dlg_Rect;
	dlg_Rect.top = m_clientRect.top+button_top;
	dlg_Rect.bottom = m_clientRect.bottom;
	dlg_Rect.left = 	m_clientRect.left;
	dlg_Rect.right =	m_clientRect.right;
	*/
	DlgDetectDevice.MoveWindow(m_clientRect);


}
void CYiRongCarDetectFPQDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnTimer(nIDEvent);
}
