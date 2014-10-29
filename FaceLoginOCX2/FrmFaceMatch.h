#pragma once

#include "Common.h"
#include "afxwin.h"
#include "FaceDetect.h"
#include <queue>
#include "BitComboBox.h"

// CFrmFaceMatch dialog

class CFrmFaceMatch : public CDialog
{
	DECLARE_DYNAMIC(CFrmFaceMatch)

public:
	CFrmFaceMatch(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFrmFaceMatch();

// Dialog Data
	enum { IDD = IDD_FACEMATCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CString MacthLog;
	CString MacthResult;
	int matchFlag;

	CString m_MacthRequest;
	CFaceDetect m_Detect;
	CCommon * m_common;

	LONG m_lVideoWidth;
	LONG m_lVideoHeight;

	bool m_bThreadWork;
	bool m_bIsClose;//�Ƿ���ر�
	bool b_listLock;
	bool b_macthLock;

	bool m_closefocus;


	HANDLE m_pThreadDisplay;
	HANDLE m_pThreadDetect;
	HANDLE m_pThreadMacth;

	UINT  m_macthTimer;
	unsigned int MacthTimeOut;

	int face_Count;
	CRect face_Rect_List[32];
	CString Image_list[32];
	std::queue<CString>	m_DetectList;
	std::queue<CString>	m_MacthList;

	//��ʼ���Ļ�����ο� ��Զ����
	CRect old_DrawRect;
	//����ͼ���ľ��ο�
	CRect DrawRect;
	//����ͼ���ľ��ο�ͳ�ʼ����ı���
	float DrawScale;

	virtual BOOL OnInitDialog();
protected:
	virtual void OnCancel();
public:
	CBitmapButton m_btnStart;
	CBitComboBox m_cbDevice;
	CBitmapButton m_btnclose;

	afx_msg void OnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnStart();
	void InitChildWindow(void);
	void InitParameters(void);
	int StartMacthThread(void);
	int StopMacthThread(void);
	void MacthProcess(void);
	afx_msg void OnPaint();

	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
