#if !defined(AFX_DLGHISTORYVIDEO_H__D1F53712_7E82_49A7_9092_ED0DD671B05F__INCLUDED_)
#define AFX_DLGHISTORYVIDEO_H__D1F53712_7E82_49A7_9092_ED0DD671B05F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DLGHistoryVideo.h : header file
//
#include "IO.h"
/////////////////////////////////////////////////////////////////////////////
// CDLGHistoryVideo dialog
#include <vector>
#include <list>
using namespace::std;

#define HISTORY_VIDEO_PAGE_MAX_NUM 40

/*
//����̫�������
struct HISTORY_VIDEO_ST
{
	unsigned long int nid;
	char name[260];	//����ͷ����
	char ip[32];	//IP��ַ
	int venderID;	//����
	char format[8];	//��׺MP4 AVI ��ʽ
	unsigned long int size;	//�ļ���С
	char path[260];

	//ʱ��
	int StartYear;
	int StartMon;
	int StartDay;
	int StartHour;
	int StartMin;
	int StartSec;
	//ʱ��
	int EndYear;
	int EndMon;
	int EndDay;
	int EndHour;
	int EndMin;
	int EndSec;
};
*/


class CDLGHistoryVideo : public CDialog
{
// Construction
public:
	CDLGHistoryVideo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDLGHistoryVideo)
	enum { IDD = IDD_HISTORY_VIDEO };
	CListCtrl	m_List;
	int		m_page;
	CString	m_name;
	CString	m_ip;
	CTime	m_StartMon;
	CTime	m_StartHour;
	CTime	m_EndMon;
	CTime	m_EndHour;
	BOOL	m_CheckTime;
	//}}AFX_DATA


	list<struct HISTORY_VIDEO_ST> list_history_video;

	int ListTotal;
	int ListNow;
	int ListChoose;
	void DisplayerList(void);

	int searchFlag;
	//�������SQL���ĺ���
	char SqlStr[1024];

	BOOL OnInitDialog();
	//���β���
	void OnOK();
	void ChooseEnable();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDLGHistoryVideo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDLGHistoryVideo)
	afx_msg void OnButtonSearch();
	afx_msg void OnButtonPlay();
	afx_msg void OnButtonFirst();
	afx_msg void OnButtonPrevious();
	afx_msg void OnButtonNext();
	afx_msg void OnButtonLast();
	afx_msg void OnButtonJump();
	afx_msg void OnClickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonDelete();
	afx_msg void OnLvnItemActivateList(NMHDR *pNMHDR, LRESULT *pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGHISTORYVIDEO_H__D1F53712_7E82_49A7_9092_ED0DD671B05F__INCLUDED_)
