// YiRongCarDetectFPQDlg.h : ͷ�ļ�
//

#pragma once

#include "DLGdetectDevice.h"

// CYiRongCarDetectFPQDlg �Ի���
class CYiRongCarDetectFPQDlg : public CDialog
{
// ����
public:
	CYiRongCarDetectFPQDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_YIRONGCARDETECTFPQ_DIALOG };

	HANDLE pthread;
	//�߳�����=false  �߳�δ��=ture
	bool ThreadFlag;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


	//������
	CDLGdetectDevice	DlgDetectDevice;

	CRect		m_clientRect;		//�����������λ��


	//�߳̾��


	//�л�λ��
	void UpdatePannelPosition();

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonCam();
	afx_msg void OnBnClickedButtonDetect();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
