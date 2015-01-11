
#ifndef _FRMFACEENROLL_H_
#define _FRMFACEENROLL_H_

#include "Common.h"
#include "afxwin.h"
#include "FaceDetect.h"
#include <queue>
#include "BitComboBox.h"




#define VIDEO_WIDTH     1920
#define VIDEO_HEIGHT    1080
#define PICTURE_MAX		4
	


typedef struct IMAGE_LIST_S{
	unsigned char data[VIDEO_WIDTH * VIDEO_HEIGHT * 3];
	unsigned long int size;
	int display;
	int choose;

} IMGLIST;

// CFrmFaceEnroll dialog

class CFrmFaceEnroll : public CDialog
{
	DECLARE_DYNAMIC(CFrmFaceEnroll)

public:
	CFrmFaceEnroll(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFrmFaceEnroll();

// Dialog Data
	enum { IDD = IDD_FACEENROLL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString EnrollLog;	//ʶ���������ύ��ƽ̨
	int EnrollResult;			//�ӿڷ��ؽ��

	CFaceDetect m_Detect;
	CCommon * m_common;

	LONG m_lVideoWidth;
	LONG m_lVideoHeight;

	bool m_bThreadWork;
	bool m_bIsClose;//�Ƿ���ر�
	bool m_bCapture;
	bool b_listLock;

	HANDLE m_pThreadDisplay;
	HANDLE m_pThreadDetect;

	UINT  m_enrollTimer;
	UINT EnrollTimeOut;

	CBitmap    CfaceBGA[PICTURE_MAX];     
	BITMAP faceBGA[PICTURE_MAX];

	CBitmap    CfaceBGB[PICTURE_MAX];     
	BITMAP faceBGB[PICTURE_MAX];

	IMGLIST *FacePicList;


	BOOL InitLive();
	void unInitLive();

	void DisplayOne(int i);

	int m_iCapIndex;
	int face_Count;
	CRect face_Rect_List[32];
	CString Image_list[32];
	std::queue<CString>	m_DetectList;
	unsigned char *tempRGB;

//	std::queue<IMGLIST>	m_FaceList;
//	IMGLIST tempFaceImage;

	//��ʼ���Ļ�����ο� ��Զ����
	CRect old_DrawRect;
	//����ͼ���ľ��ο�
	CRect DrawRect;
	//����ͼ���ľ��ο�ͳ�ʼ����ı���
	float DrawScale;

	bool m_closefocus;
//	int m_focus;

	virtual BOOL OnInitDialog();
protected:
	virtual	void OnOK();
	virtual void OnCancel();
public:
	CBitmapButton m_btnStart;
	CBitmapButton m_btnCapture;
	CBitmapButton m_btnEnroll;
	CBitmapButton m_btnClear;
	CBitComboBox m_cbDevice;

	CBitmapButton m_btnclose;

	afx_msg void OnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedBtnCapture();
	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnBnClickedBtnEnroll();
	void InitChildWindow(void);
	void InitParameters(void);
	int StartEnrollThread(void);
	int StopEnrollThread(void);
	void FaceCapture(unsigned char *image,unsigned long int width,unsigned long int height);
	afx_msg void OnPaint();
	afx_msg void OnStnClickedStaticFace1();
	afx_msg void OnStnClickedStaticFace2();
	afx_msg void OnStnClickedStaticFace3();
	afx_msg void OnStnClickedStaticFace4();

	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#endif