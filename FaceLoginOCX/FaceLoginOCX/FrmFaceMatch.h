#pragma once

#include "Common.h"
#include "afxwin.h"

#include "FaceCloudDLL.h"
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
	void InitParameters();
	int StartThread();
	int StopThread();
	void CloseWindow();
public:
	CCommon * m_common;
	LONG m_lVideoWidth;
	LONG m_lVideoHeight;
	bool m_bThreadWork;
	bool m_bIsClose;//�Ƿ���ر�
	HANDLE m_pThreadDetect;


	char* FaceImage[10];

	int Face_count;
	RECT Face_range[32];
	unsigned char *tempRGB;
	int list_size;
	RwFaceRect face_rect_list[32];
	//��ʼ���Ļ�����ο� ��Զ����
	CRect old_DrawRect;
	//����ͼ���ľ��ο�
	CRect DrawRect;
	//����ͼ���ľ��ο�ͳ�ʼ����ı���
	float DrawScale;

protected:
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
public:
	CComboBox m_cbDevice;
	afx_msg void OnClose();
};