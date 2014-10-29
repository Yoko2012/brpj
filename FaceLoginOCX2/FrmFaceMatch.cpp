// FrmFaceMatch.cpp : implementation file
//

#include "stdafx.h"
#include "FaceLoginOCX.h"
#include "FrmFaceMatch.h"

#define FACE_MACTH_TIMER 1
#include "FaceLoginOCXCtrl.h"
extern CFaceLoginOCXCtrl *DlgFaceLoginOCXCtrl;

//********************************�߳�**********************************
//�����ȶ��߳�
DWORD WINAPI MacthThread(void *p)
{
	CFrmFaceMatch * pFrmFaceMatch = (CFrmFaceMatch*)p;

	pFrmFaceMatch->m_bIsClose = false;

	while(pFrmFaceMatch->m_bThreadWork)
	{
		pFrmFaceMatch->MacthProcess();
		Sleep(10);
	}

	pFrmFaceMatch->m_bIsClose = true;
	return 0;
}

//��Ƶ��ʾ�߳�
DWORD WINAPI MacthDisplayThread(void *p)
{
	CFrmFaceMatch * pFrmFaceMatch = (CFrmFaceMatch*)p;
	
	long  bitmapSize;
	char * buffer= NULL;

	pFrmFaceMatch->m_bIsClose = false;

	while(pFrmFaceMatch->m_bThreadWork)
	{
		try
		{
			QueryFrameCB(&bitmapSize,&buffer);

			if(bitmapSize > 0)
			{
				BITMAPINFO bmpInfo = {0};   
				bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);   
				bmpInfo.bmiHeader.biWidth = pFrmFaceMatch->m_lVideoWidth;   
				bmpInfo.bmiHeader.biHeight = pFrmFaceMatch->m_lVideoHeight;
				bmpInfo.bmiHeader.biPlanes = 1;   
				bmpInfo.bmiHeader.biBitCount = 24;  
				try
				{
					if(!pFrmFaceMatch->b_listLock)
					{
						CString result = pFrmFaceMatch->m_Detect.RGBtoBase64((unsigned char *)buffer,
																				bitmapSize,
																				pFrmFaceMatch->m_lVideoWidth,
																				pFrmFaceMatch->m_lVideoHeight);
						if(!result.IsEmpty())
						{
							pFrmFaceMatch->m_DetectList.push(result);
						}
					}

					//��ʾ����ͷ���漰���������
					pFrmFaceMatch->m_common->DrawCtrlImage((CStatic *)pFrmFaceMatch->GetDlgItem(IDC_STATIC_MAIN), bmpInfo, 
															buffer, bitmapSize,pFrmFaceMatch->face_Count,pFrmFaceMatch->face_Rect_List,
															pFrmFaceMatch->DrawRect,pFrmFaceMatch->DrawScale);
				}
				catch(...)
				{
					continue;
				}
			}
			else
			{			
				Sleep(100);
			}

		}
		catch(...)
		{
			continue;
		}
	}

	pFrmFaceMatch->m_bIsClose = true;
	return 0;
}

//��������߳�
DWORD WINAPI MacthDetectThread(void *p)
{
	CFrmFaceMatch * pFrmFaceMatch = (CFrmFaceMatch*)p;

	pFrmFaceMatch->m_bIsClose = false;

	while(pFrmFaceMatch->m_bThreadWork)
	{
		try
		{
			if(pFrmFaceMatch->m_DetectList.size() > 0)
			{
				pFrmFaceMatch->b_listLock = true;
				CString strRequest = pFrmFaceMatch->m_DetectList.front();
				pFrmFaceMatch->m_DetectList.pop();
				pFrmFaceMatch->m_Detect.FaceDetect(strRequest,&pFrmFaceMatch->face_Count,pFrmFaceMatch->face_Rect_List,pFrmFaceMatch->Image_list);
				if(pFrmFaceMatch->face_Count>0)
				{
					if(!pFrmFaceMatch->b_macthLock)
					{
						for(int i=0;i<pFrmFaceMatch->face_Count;i++)
						{
							pFrmFaceMatch->m_MacthList.push(pFrmFaceMatch->Image_list[i]);
						}
					}
				}
				pFrmFaceMatch->b_listLock = false;
			}
		}
		catch(...)
		{
			continue;
		}
		Sleep(10);
	}

	pFrmFaceMatch->m_bIsClose = true;
	return 0;
}
//********************************�߳�**********************************

// CFrmFaceMatch dialog

IMPLEMENT_DYNAMIC(CFrmFaceMatch, CDialog)

CFrmFaceMatch::CFrmFaceMatch(CWnd* pParent /*=NULL*/)
	: CDialog(CFrmFaceMatch::IDD, pParent)
{
	b_listLock = false;
	b_macthLock = false;
}

CFrmFaceMatch::~CFrmFaceMatch()
{
}

void CFrmFaceMatch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DEV, m_cbDevice);
	DDX_Control(pDX, IDC_BTN_START, m_btnStart);
	DDX_Control(pDX, IDC_BUTTON_CLOSE, m_btnclose);
}


BEGIN_MESSAGE_MAP(CFrmFaceMatch, CDialog)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_START, &CFrmFaceMatch::OnBnClickedBtnStart)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CFrmFaceMatch::OnBnClickedButtonClose)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CFrmFaceMatch message handlers

BOOL CFrmFaceMatch::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	InitChildWindow();

	StartMacthThread();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CFrmFaceMatch::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
		
	StopMacthThread();
	CDialog::OnCancel();
}

void CFrmFaceMatch::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	MacthLog.Format(_T("{\
						\"ret\":\"fail\",\
						\"user\":\"%s\",\
						\"sysID\":\"%d\",\
						\"content\":\"User_Cancle\"\
						}"),DlgFaceLoginOCXCtrl->MatchUser,DlgFaceLoginOCXCtrl->MatchSysID);

	MacthResult.Format(_T("%d"),OCX_ERROR_USER_CANCLE);

	StopMacthThread();
	CDialog::OnClose();
}

void CFrmFaceMatch::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent == FACE_MACTH_TIMER)
	{
		if(matchFlag)
		{
			CString strlog;
			strlog.Format(_T("<TIPS><matchSuccess> - User<%s>"),DlgFaceLoginOCXCtrl->MatchUser);
			DlgFaceLoginOCXCtrl->ShowOcxLog(strlog);

			MacthResult = m_Detect.Token;//�ȶԳɹ�����������
			OnCancel();
		}
		if(MacthTimeOut++ > OCX_TIMEOUT_MAX)
		{
			if(MacthLog.IsEmpty())			//δ��⵽������ʶ��ʱ
			{
				MacthLog.Format(_T("{\
									\"ret\":\"fail\",\
									\"user\":\"%s\",\
									\"sysID\":\"%d\",\
									\"content\":\"Time_Out\"\
									}"),DlgFaceLoginOCXCtrl->MatchUser,DlgFaceLoginOCXCtrl->MatchSysID);

				MacthResult.Format(_T("%d"),OCX_ERROR_TIME_OUT);
			}
			else							//��ʶ�𣬵���δ�ɹ�
			{
				MacthResult.Format(_T("%d"),OCX_ERROR_MATCH_FAIL);
			}
			OnCancel();
		}
	}

	CDialog::OnTimer(nIDEvent);
}

void CFrmFaceMatch::OnBnClickedBtnStart()
{
	// TODO: Add your control notification handler code here
	if(m_bThreadWork)
	{
		m_bThreadWork = false;
		Sleep(1000);

		if(false == m_bIsClose)
		{
			TerminateThread(m_pThreadDisplay,0);
			m_pThreadDisplay=NULL;
			TerminateThread(m_pThreadDetect,0);
			m_pThreadDetect=NULL;
			TerminateThread(m_pThreadMacth,0);
			m_pThreadMacth=NULL;
		}
		Sleep(100);
		CloseCamera();
		Invalidate();
	}

	if(m_cbDevice.GetCount()>0)
	{
		CString tmp;
		tmp.Format("%d", m_cbDevice.GetCurSel());
		m_common->SetReg("Camera", tmp);
		if(!OpenCameraCB(m_cbDevice.GetCurSel(), false , &m_lVideoWidth, &m_lVideoHeight)) //����������ѡ�񴰿ڣ��ô����ƶ�ͼ���͸�
		{
			fprintf(stderr, "Can not open camera.\n");
			MessageBox("����ͷ��ʼ��ʧ��","��ʾ");
			CloseCamera();
			return;
		}

		Invalidate(true);
		if(m_lVideoWidth > 0)
		{
			//��������
			DrawRect=m_common->SetDrawSize((CStatic *)GetDlgItem(IDC_STATIC_MAIN),
					old_DrawRect,m_lVideoWidth,m_lVideoHeight,&DrawScale);

			m_bThreadWork = true;

			m_pThreadDisplay=NULL;
			m_pThreadDisplay=CreateThread(NULL,0,MacthDisplayThread,this,0,NULL);
			m_pThreadDetect=NULL;
			m_pThreadDetect=CreateThread(NULL,0,MacthDetectThread,this,0,NULL);
			m_pThreadMacth=NULL;
			m_pThreadMacth=CreateThread(NULL,0,MacthThread,this,0,NULL);
		}
		else
		{
			MessageBox("δ�ҵ��豸","��ʾ");
		}
	}
}

/************************************
* ��ʼ������
*************************************/
void CFrmFaceMatch::InitChildWindow(void)
{

	GetDlgItem(IDC_STATIC_MAIN)->MoveWindow(22,24,487,386);
	//�ƶ�֮����ʾƫ�ˣ�ֱ��ָ����Ƶ��ʾ����
	old_DrawRect.left=22;
	old_DrawRect.top=24;
	old_DrawRect.right =509;
	old_DrawRect.bottom =410;

	//��ť
	m_btnStart.LoadBitmaps(IDB_BTN_START_NORMAL,NULL,NULL,NULL);
	m_btnStart.SizeToContent();		//����ӦͼƬ��С
	m_btnStart.MoveWindow(448,426,53,24);

	//�豸�б�combo
	m_cbDevice.SetComboBitmap(IDB_BITMAP_LEFT,IDB_BITMAP_RIGHT,IDB_BITMAP_CEN);
	m_cbDevice.SetComboListBitmap(IDB_COMBO_LEFT, IDB_COMBO_RIGHT,IDB_COMBO_TOP,IDB_COMBO_BOTTOM);
	m_cbDevice.SetHighlightColor(RGB(0,41,41),RGB(255,255,255));
	m_cbDevice.SetNormalPositionColor(RGB(0,41,41),RGB(255,255,255));
	m_cbDevice.MoveWindow(303,425,145,100);
	//m_cbDevice.InsertString(0,"����ͷ�б�");
	//m_cbDevice.SetCurSel(0);
	m_btnclose.LoadBitmaps(IDB_BTN_CLOSE_NORMAL,IDB_BTN_CLOSE_PRESS,IDB_BTN_CLOSE_PRESS,NULL);
	m_btnclose.SizeToContent();		//����ӦͼƬ��С
	
	m_btnclose.MoveWindow(505,2,22,22);
}

/************************************
* ��ʼ������
*************************************/
void CFrmFaceMatch::InitParameters(void)
{
	m_pThreadDisplay=NULL;
	m_pThreadDetect=NULL;
	m_pThreadMacth=NULL;

	MacthLog = "";
	matchFlag = 0;
	m_bIsClose = true;
	m_bThreadWork = false;
	m_lVideoWidth = 0;
	m_lVideoHeight = 0;

	MacthTimeOut = 0;
	m_macthTimer = 0;
	m_macthTimer = SetTimer(FACE_MACTH_TIMER,1000,NULL);

	while(m_DetectList.size() > 0)
	{
		m_DetectList.pop();
	}
	while(m_MacthList.size() > 0)
	{
		m_MacthList.pop();
	}
	
	m_closefocus=false;
}

/************************************
* ���������ȶ��߳�
*************************************/
int CFrmFaceMatch::StartMacthThread(void)
{
	InitParameters();
	if(m_common->InitialDevice(m_cbDevice, &m_lVideoWidth, &m_lVideoHeight))//�豸��ʼ��
	{	
		//��������
		DrawRect=m_common->SetDrawSize((CStatic *)GetDlgItem(IDC_STATIC_MAIN),
				old_DrawRect,m_lVideoWidth,m_lVideoHeight,&DrawScale);

		m_bThreadWork = true;

		m_pThreadDisplay=NULL;
		m_pThreadDisplay=CreateThread(NULL,0,MacthDisplayThread,this,0,NULL);
		m_pThreadDetect=NULL;
		m_pThreadDetect=CreateThread(NULL,0,MacthDetectThread,this,0,NULL);
		m_pThreadMacth=NULL;
		m_pThreadMacth=CreateThread(NULL,0,MacthThread,this,0,NULL);

		return 1;
	}
	return 0;
}

/************************************
* ֹͣ�����ȶ��߳�
*************************************/
int CFrmFaceMatch::StopMacthThread(void)
{
	if(m_macthTimer) 
		KillTimer(m_macthTimer); 
	m_macthTimer = 0;

	m_bIsClose = true;
	if(m_bThreadWork)
	{
		m_bThreadWork = false;
		Sleep(1000);

		if(false == m_bIsClose)
		{
			TerminateThread(m_pThreadDisplay,0);
			m_pThreadDisplay=NULL;
			TerminateThread(m_pThreadDetect,0);
			m_pThreadDetect=NULL;
			TerminateThread(m_pThreadMacth,0);
			m_pThreadMacth=NULL;
		}
		Sleep(100);

		CloseCamera();
		Invalidate();

		return 1;
	}
	return 0;
}

/************************************
* �����ȶ�
*************************************/
void CFrmFaceMatch::MacthProcess(void)
{
	if(m_MacthList.size()>0)
	{
		b_macthLock = true;
		CString strRequest = m_MacthList.front();
		m_MacthList.pop();
		m_Detect.FaceMacth(strRequest,&MacthLog,&matchFlag);
		b_macthLock = false;
	}
}


void CFrmFaceMatch::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	//������ͼ	
	CRect    rect;     
	GetClientRect(&rect);     

	//����Դ������λͼ     
	CBitmap    bitmap;     
	bitmap.LoadBitmap(IDB_MATCHBACK);    
	BITMAP bmp;
	bitmap.GetBitmap(&bmp);

	CDC    memdc;     
	memdc.CreateCompatibleDC(&dc);     
	memdc.SelectObject(bitmap); 
	dc.SetStretchBltMode(COLORONCOLOR);
	dc.StretchBlt(0,0,rect.Width(),rect.Height(),&memdc,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
	memdc.DeleteDC();
	// Do not call CDialog::OnPaint() for painting messages
}

void CFrmFaceMatch::OnBnClickedButtonClose()
{
	// TODO: Add your message handler code here and/or call default
	MacthLog.Format(_T("{\
					   \"ret\":\"fail\",\
					   \"user\":\"%s\",\
					   \"sysID\":\"%d\",\
					   \"content\":\"User_Cancle\"\
					   }"),DlgFaceLoginOCXCtrl->MatchUser,DlgFaceLoginOCXCtrl->MatchSysID);

	MacthResult.Format(_T("%d"),OCX_ERROR_USER_CANCLE);

	StopMacthThread();
	CDialog::OnCancel();
}

void CFrmFaceMatch::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	bool old=m_closefocus;
	if(point.x <535 && point.x >500 &&point.y <35 && point.y >1 )
	{
		m_closefocus=true;
	}
	else
	{
		m_closefocus=false;
	}

	if( old != m_closefocus)
	{	
		if(m_closefocus)
			m_btnclose.SetFocus();
		else
			this->SetFocus();
	}

	CDialog::OnMouseMove(nFlags, point);
}
