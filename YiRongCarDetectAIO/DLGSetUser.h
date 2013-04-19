#if !defined(AFX_DLGSETUSER_H__7C41A573_FB45_4E76_9213_500C84A73D0B__INCLUDED_)
#define AFX_DLGSETUSER_H__7C41A573_FB45_4E76_9213_500C84A73D0B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DLGSetUser.h : header file
//
#include <vector>
#include <list>
using namespace::std;

#include "IO.h"
/////////////////////////////////////////////////////////////////////////////
// CDLGSetUser dialog
/*
//����̫�������
struct SET_USER_LIST_ST
{
	//���ݿ��NID
	unsigned long int nid;
	char user[32];
};

//����̫�������
struct SET_USER_DATA_ST
{
	//���ݿ��NID
	unsigned long int nid;
	char user[32];
	char psw[260];
	//����ԱȨ��
	int admin;
	//Ȩ��
	//ϵͳ����
	int	systemset;
	//¼������
	int	recordset;
	//¼��
	int	record;
	//��̨
	int	ptz;
	//Ԥ��
	int	preview;
	//��ʷ��Ƶ��ѯ
	int	historyvideo;
	//ϵͳ��־��ѯ
	int	historyreport;
	//��ʷʶ���ѯ
	int	historydetect;
	//��ʷ������ѯ
	int	historyalarm;
	//�豸����
	int	device;
	//����������
	int	blackset;
	//ץ��
	int	capbmp;
	//ʶ��
	int	detect;
	//ʶ������
	int	detectset;
};
*/

class CDLGSetUser : public CDialog
{
// Construction
public:
	CDLGSetUser(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDLGSetUser)
	enum { IDD = IDD_SET_USER };
	CListCtrl	m_List;
	CString	m_password_again;
	CString	m_password;
	CString	m_user;
	BOOL	m_systemset;
	BOOL	m_recordset;
	BOOL	m_record;
	BOOL	m_ptz;
	BOOL	m_preview;
	BOOL	m_historyvideo;
	BOOL	m_historyreport;
	BOOL	m_historydetect;
	BOOL	m_historyalarm;
	BOOL	m_device;
	BOOL	m_blackset;
	BOOL	m_capbmp;
	BOOL	m_detect;
	BOOL	m_detectset;
	BOOL	m_all;
	BOOL	m_admin;
	//}}AFX_DATA

	BOOL OnInitDialog();
	//���β���
	void OnOK();

	list<struct SET_USER_LIST_ST> list_user;
	struct SET_USER_DATA_ST data;

	int ListTotal;
	int ListNow;
	int ListChoose;

	void DisplayerList(void);

	void Struct2M(void);
	void M2Struct(void);
	void Clear();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDLGSetUser)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDLGSetUser)
	afx_msg void OnClickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonUserAdd();
	afx_msg void OnButtonUserModify();
	afx_msg void OnButtonUserDelete();
	afx_msg void OnCheckAll();
	afx_msg void OnChangeEditUser();
	afx_msg void OnCheckAdmin();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETUSER_H__7C41A573_FB45_4E76_9213_500C84A73D0B__INCLUDED_)
