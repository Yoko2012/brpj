#if !defined(AFX_DLGSETRECORD_H__6D570753_FDCB_415A_91FE_6C516D3E0062__INCLUDED_)
#define AFX_DLGSETRECORD_H__6D570753_FDCB_415A_91FE_6C516D3E0062__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DLGSetRecord.h : header file
//
#include <vector>
#include <list>
using namespace::std;

#include "IO.h"

/*
//����̫�������
struct SET_RECORD_DATA_ST
{
	//���ݿ��NID
	unsigned long int nid;

	unsigned long int camid;	//����ͷID
	char area[260];	//����ͷ����
	char name[260];	//����ͷ����
	char ip[32];	//IP��ַ

	//�������3������false ���������Ч
	int everyday;	//ʹ��ÿ�� bool
	int usedate;	//ʹ������ bool	 
	int useweek;	//ʹ��ÿ�� bool
	// ����״̬ ������ִ��¼�ơ������þ�ֻ�Ǳ��� bool
	int enable;

	//ʱ��
	int StartYear;
	int StartMon;
	int StartDay;
	int StartWeek; //1 ���� 2-7 ��һ������
	int StartHour;
	int StartMin;
	int StartSec;
	//ʱ��
	int EndYear;
	int EndMon;
	int EndDay;
	int EndWeek;	//0 ���� 1-6 ��һ������
	int EndHour;
	int EndMin;
	int EndSec;
};
*/
/////////////////////////////////////////////////////////////////////////////
// CDLGSetRecord dialog

class CDLGSetRecord : public CDialog
{
// Construction
public:
	CDLGSetRecord(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDLGSetRecord)
	enum { IDD = IDD_SET_RECORD };
	CComboBox	m_cam;
	CComboBox	m_area;
	CListCtrl	m_List;
	CTime	m_StartMon;
	CTime	m_StartHour;
	CTime	m_EndMon;
	CTime	m_EndHour;
	BOOL	m_all;
	BOOL	m_date;
	BOOL	m_enable;
	BOOL	m_everyday;
	BOOL	m_week;
	int		m_endweek;
	int		m_startweek;
	CString	m_camip;
	//}}AFX_DATA
	CRect printf_Rect;

	BOOL OnInitDialog();
	//���β���
	void OnOK();

	list<struct SET_RECORD_DATA_ST> list_record;
	struct SET_RECORD_DATA_ST data;
	bool rwLock;	//�������Ϊtrue ���ܶ�

	int ListTotal;
	int ListNow;
	int ListChoose;

	CString AreaStr;
	CString CamStr;
	unsigned long int camid;

	void InitList(void);
	void DisplayerList(void);
	void Clear();
	void Struct2M(void);
	void M2Struct(void);

	void SetToday();
	bool NeedRecord(unsigned long int camid);
	bool TimeLimit(void) ;
	unsigned long int GetNid(long int ListChoose) ;
	void DisplayWeek(int nItem,int i,int dayofweek);
	void DisplayTime(int nItem,list<struct SET_RECORD_DATA_ST>::iterator beglist) ;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDLGSetRecord)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDLGSetRecord)
	afx_msg void OnButtonEnable();
	afx_msg void OnButtonDisable();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonModify();
	afx_msg void OnButtonDelete();
	afx_msg void OnClickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheckAll();
	afx_msg void OnButtonDeleteall();
	afx_msg void OnCloseupComboArea();
	afx_msg void OnCloseupComboCam();
	afx_msg void OnCheckDate();
	afx_msg void OnCheckWeek();
	afx_msg void OnCheckEveryday();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	CBitmapButton m_b_add;
	CBitmapButton m_b_edit;
	CBitmapButton m_b_delete;
	CBitmapButton m_b_clear;
	CBitmapButton m_b_enable;
	CBitmapButton m_b_disable;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETRECORD_H__6D570753_FDCB_415A_91FE_6C516D3E0062__INCLUDED_)
