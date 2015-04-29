#if !defined(AFX_DLGSCREEN_H__08A4A59F_824B_475D_B94C_9FA7A3CFCE9D__INCLUDED_)
#define AFX_DLGSCREEN_H__08A4A59F_824B_475D_B94C_9FA7A3CFCE9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DLGscreen.h : header file
//
#include "ScreenPannel.h"
#include "DLGshortcut.h"
#if ALLTAB_DETECT_CAR_MODE
#include "DLGSetCar.h"
#else
#include "DLGSetElecar.h"
#endif

#include "CarDetect.h"
#include "FaceDetect.h"
#include "HYZJCarDetect.h"

#include "myCamera.h"

#define VIDEO_WIDTH     1920
#define VIDEO_HEIGHT    1080

//�豸��Ϣ
struct DEVICE_INFO 
{
	long  camID;
	CString area;				//����
	CString name;				//���������
	CString ip;
	CString user;
	CString psw;
	long port;
	bool isplay;
	bool isRecord;
	int subtype;
	bool enableCarDetect;
	bool enableFaceDetect;
	long playHandle;

	int  venderID;				//0---����,1---��  
	CString recordPath;
	CTime startTime;
	bool planRecord;
	long channel;
	//������ý��
	CString Rtspurl;
	int RTP;
	int DecodeTag;
	int Direction;
};


/////////////////////////////////////////////////////////////////////////////
// CDLGscreen dialog

class CDLGscreen : public CDialog
{
// Construction
public:
	CDLGscreen(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDLGscreen)
	enum { IDD = IDD_SCREEN };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	BOOL	OnInitDialog();
	void AutoSize();

	//���β���
	void OnOK();
	void OnCancel();
	//��ݰ�ť
	CDLGshortcut DlgShortCut;
	//���Ŵ���
	CScreenPannel m_screenPannel;

	struct DEVICE_INFO m_videoInfo[MAX_DEVICE_NUM];
	long CSdeviceID[MAX_DEVICE_NUM];


	//��������ֵ
	int FaceAdd[MAX_DEVICE_NUM];
		//��������ֵ
	int CarAdd[MAX_DEVICE_NUM];

#if OPEN_LC_CARDETECT_CODE 
	CCarDetect	CarDetect[MAX_DEVICE_NUM];
#endif

#if OPEN_HYZJ_CARDETECT_CODE 
	CHYZJCarDetect	HYZJCarDetect[MAX_DEVICE_NUM];
	int HYZJCarDetect_total;
#endif

	
#if OPEN_FACEDETECT_CODE 
	CFaceDetect	FaceDetect[MAX_DEVICE_NUM];
#endif

	CMyCamera   m_video;
	UINT  m_recordtimer;

	//��ǰ��ʾ�������
	int m_curScreen;

	//����ѡ��Ĵ���
	void SetCurWindId(int nCuWinID);
	//��ȡ��ǰѡ��Ĵ���
	int GetCurWindId(void);
	//��ȡ��ǰ���ڵ����������״̬
	bool GetCurWindPlayState(int nCuWinID);

	//��ȡ��ǰ���ڵ������¼��״̬
	bool GetCurWindRecordState(int nCuWinID);
	//��ȡ��ǰ���ڵ��������ʱ¼��״̬
	bool GetCurWindPlanRecordState(int nCuWinID);
	//��ȡ��ǰ���ڵĲ��ž��
	long GetCurWindPlayHandle(int nCuWinID);
	//��ȡ��ǰ���ڵ����������������
	int GetCurWindSubType(int nCuWinID);
	//��ȡ��ǰѡ�񴰿ڵ��������ϸ��Ϣ
	void GetCurWindCamInfo(int nCuWinID,struct DEVICE_INFO &Info);
	//����/�رճ���ʶ��
	void EnableCarDetect(int nCuWinID,bool bEnable);
void EnableFaceDetect(int nCuWinID,bool bEnable);

	//����/�ر�¼��
	void EnableRecord(int nCuWinID,bool bEnable);
	//��ȡʶ��״̬
	bool GetCarDetectState(int nCuWinID);
bool GetFaceDetectState(int nCuWinID);
	//��ȡ¼��״̬
	bool GetRecordState(int nCuWinID);
	//����ʶ������
	void CarDetectSet(void);

	//ɾ���豸
	void DeleteDevice(long camID);

	void SwitchMultiWnd(int nSplit);
	bool StartPlay(int id,char *area,char *name,char *ip,int port,int channel,
		char *user,char *psw,int subtype,int screenNo,int venderID,char *Rtspurl,int RTP,int DecodeTag,int Direction);
	void StopPlay(int screenNo);
	void Capture(char *filename);

	//��ʼ¼��
	int StartRecord(int screenNo,char *filename);
	//ֹͣ¼��
	void StopRecord(int screenNo);
	//¼��ʱʱ��
	void RecordTimerEvent();

	//��̨����
	void PtzControl(int type, BOOL dwStop, int param);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDLGscreen)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDLGscreen)
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSCREEN_H__08A4A59F_824B_475D_B94C_9FA7A3CFCE9D__INCLUDED_)
