// zogvmDlg.h : header file
//

#include "afxcmn.h"
#if !defined(AFX_ZOGVMDLG_H__FE2A0F30_6672_4F61_A395_8DE4DED121A7__INCLUDED_)
#define AFX_ZOGVMDLG_H__FE2A0F30_6672_4F61_A395_8DE4DED121A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <vector>
#include <list>
using namespace::std;

/*�����ͷ�ļ�����Ȼ�ѱ���*/
#include "xlslib_include\ac-config.win32.h"
#include "xlslib_include\xlslib.h"
using namespace xlslib_core;

#include "SqliteOperate.h"


enum MODE_FLAG_EM
{
	MODE_DOUBLE=1, 
	MODE_FIND=2,
	MODE_TRASH=3
};

/////////////////////////////////////////////////////////////////////////////
// CZogvmDlg dialog

class CZogvmDlg : public CDialog
{
	// Construction
public:
	CZogvmDlg(CWnd* pParent = NULL);	// standard constructor

	// Dialog Data
	//{{AFX_DATA(CZogvmDlg)
	enum { IDD = IDD_ZOGVM_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	CImageList    m_SmallIcon;                     //����Сͼ��
	CImageList    m_NullIcon;                     //����Сͼ��

	list<struct HDD_ST> hddList;
	list<struct FILE_VIEW_ST> WinfileviewList;

	void CZogvmDlg::DisplayerList();
	char OutputPath[260];

	char SQLstr[1024] ;
	struct UPDOWN_ST SQLupdown;
	int ModeFlag;

	CRect printf_Rect;
	long ListTotal;
	long ListNow;
	long		m_page;
	CBitmapButton m_first_button;
	CBitmapButton m_pre_button;
	CBitmapButton m_next_button;
	CBitmapButton m_last_button;
	CBitmapButton m_jump_button;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZogvmDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	HICON m_hIcon;
	void CZogvmDlg::DisplaySize(long long size,char* str);

	// Generated message map functions
	//{{AFX_MSG(CZogvmDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnMenuitemSetType();
	afx_msg void OnButtonBuild();
	afx_msg void OnButtonFind();
	afx_msg void OnMenuitemSetHdd();
	afx_msg void OnButtonFirst();
	afx_msg void OnButtonPrevious();
	afx_msg void OnButtonNext();
	afx_msg void OnButtonLast();
	afx_msg void OnButtonJump();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CString m_sreach;
	CListCtrl m_list;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLvnColumnclickList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonDouble();
	afx_msg void OnNMCustomdrawList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHddDelete();
	afx_msg void OnBnClickedButtonOutputexecl();
	afx_msg void OnLvnItemActivateList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonTrash();
	afx_msg void OnBnClickedButtonTrashClean();
	BOOL m_c_delete_trash;
	afx_msg void OnYyets();
	afx_msg void OnAddEd2k();
	BOOL m_c_video;
	BOOL m_c_audio;
	BOOL m_c_sub;
	BOOL m_c_other;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZOGVMDLG_H__FE2A0F30_6672_4F61_A395_8DE4DED121A7__INCLUDED_)
