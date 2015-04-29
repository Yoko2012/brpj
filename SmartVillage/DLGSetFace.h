#pragma once

#include "YRSVMySQL.h"
// CDLGSetFace dialog

class CDLGSetFace : public CDialog
{
	DECLARE_DYNAMIC(CDLGSetFace)

public:
	CDLGSetFace(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDLGSetFace();

// Dialog Data
	enum { IDD = IDD_SET_FACE };
	virtual BOOL OnInitDialog();

struct  DEVICE_SET_FACE_LITE_ST face;

	void InitList(void);

	int dbTotal;			//���ò�������
	long db_nid[RW_MAX_FACE_DB_NUM];		//���ò��ؿ�ID

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	afx_msg void OnCheck();


	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	CBitmapButton m_b_ok;
	CBitmapButton m_b_cancel;
	afx_msg void OnOk();
	int m_minface;
	int m_threshold;
	int m_maxcount;
	CListCtrl	m_List;
	BOOL	m_check;
	
	CBrush m_BgBrush;           // ����ɫ��ˢ

	float m_e_front_ts;
	float m_e_side_ts;
	int m_maxface;
	int m_e_timeout;
	float m_e_scale;
	int m_e_video_ts;
};
