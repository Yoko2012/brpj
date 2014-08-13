#if !defined(AFX_DLGSETBLACK_H__0287AC76_30D4_46E3_A6CC_ADC0002FA4D4__INCLUDED_)
#define AFX_DLGSETBLACK_H__0287AC76_30D4_46E3_A6CC_ADC0002FA4D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DLGSetBlack.h : header file
//
#include <vector>
#include <list>
using namespace::std;

#include "IO.h"

#define SET_BLACK_PAGE_MAX_NUM 40
/*
//����̫�������
struct BLACK_DATA_ST
{
	unsigned long int nid;
	char brand[256];	//Ʒ��
	char name[256];	//ʧ������
	char Phone[256];	//ʧ���绰
	char plate[256];	//���ƺ�
	char other[1024];	//������Ϣ

};
*/
/////////////////////////////////////////////////////////////////////////////
// CDLGSetBlack dialog

class CDLGSetBlack : public CDialog
{
// Construction
public:
	CDLGSetBlack(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDLGSetBlack)
	enum { IDD = IDD_SET_BLACK };
	CListCtrl	m_List;
	CString	m_Brand;
	CString	m_Name;
	CString	m_Phone;
	CString	m_Plate;
	CString	m_Other;
	int		m_page;
	//}}AFX_DATA

	BOOL OnInitDialog();
	void OnOK();

	list<struct BLACK_DATA_ST> list_black;
	struct BLACK_DATA_ST data;

	long ListTotal;
	long ListNow;
	long ListChoose;

	void DisplayerList(void);
	void reflush();
	void Clear();

	void Struct2M(void);
	void M2Struct(void);

	 void BlackInput();
	 void BlackOuput();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDLGSetBlack)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDLGSetBlack)
	afx_msg void OnButtonJump();
	afx_msg void OnButtonFirst();
	afx_msg void OnButtonPrevious();
	afx_msg void OnButtonNext();
	afx_msg void OnButtonLast();
	afx_msg void OnButtonBlackAdd();
	afx_msg void OnButtonBlackModify();
	afx_msg void OnButtonBlackdelete();
	afx_msg void OnButtonBlackClean();
	afx_msg void OnClickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonBlackInput();
	afx_msg void OnButtonBlackOuput();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETBLACK_H__0287AC76_30D4_46E3_A6CC_ADC0002FA4D4__INCLUDED_)
