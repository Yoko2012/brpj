#pragma once


#include "DLGscreen.h"
#include "DLGPictureFace.h"
#include "DLGdevicetree.h"
#include "DLGnormal.h"
//WAV����
#include "mmsystem.h"
#pragma comment(lib,"winmm.lib") 

#include "DLGSetRecord.h"

////////////////lynn/////////////////
#include "YRSVMySQL.h"
////////////////lynn/////////////////
#include "SplitterControl.h"
// CDLGTabVideo dialog


class CDLGTabVideo : public CDialog
{
	DECLARE_DYNAMIC(CDLGTabVideo)

public:
	CDLGTabVideo(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDLGTabVideo();

	BOOL	OnInitDialog();
	void AutoSize();
// Dialog Data
	enum { IDD = IDD_TAB_VIDEO };


	CListCtrl	m_ListCar;

	//}}AFX_DATA



	//��������Ļ
	CDLGscreen DlgScreen;
	//�豸��
	CDLGdevicetree	DlgDeviceTree;

	//����
	CDLGnormal	DlgNormal;

#if OPEN_RECORD
	//��ʱ¼��
	CDLGSetRecord DlgSetRecord;
#endif
	CDLGPictureFace DlgPictureFaceCap;
	CDLGPictureFace DlgPictureFaceAlarm;


	int	m_ListCarTotal;		//ʵʱ�б���������
	CRect		m_clientRect;		//�����������λ��
	//�л�λ��
	void UpdatePannelPosition();


	//�л���
	void TabMainInit(void);




	void ListMainInit(void);

	//�ָ���
	CSplitterControl    m_wndSplitter;
	void initSplitter();
	afx_msg void OnMaxMinInfo(NMHDR* pNMHDR, LRESULT* pResult);




protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOk();
	afx_msg void OnCancel();
	afx_msg void OnPaint();

	afx_msg void OnLvnItemActivateList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawList(NMHDR *pNMHDR, LRESULT *pResult);
};
