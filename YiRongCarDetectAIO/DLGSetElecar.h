#if !defined(AFX_DLGSETELECAR_H__0BA2D819_DCBC_46C1_A79B_7FB5F827563E__INCLUDED_)
#define AFX_DLGSETELECAR_H__0BA2D819_DCBC_46C1_A79B_7FB5F827563E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DLGSetElecar.h : header file
//

#include "CarDetect.h"
#if 0
/////////////////////////////////////////////////////////////////////////////
// CDLGSetElecar dialog
//ÿ�����������ٸ��ַ�
#define CAR_STR_MAX 32
//����ʡ��
#define CAR_MASK_MAX 31

typedef struct
{
	short x0;	// ��
	short x1;	// ��
	short y0;	// ��
	short y1;	// ��
}Rects;

	////////////////////////////////////////////////////////
//��������
struct CarSetStruct
{
	//��ͼ���ƴ���� 0=���� 1=��
	int RedRect;
	//������бУ��ʹ�ܱ�־ 0:��У����1:У��
	int Deskew;
	//JPGͼƬ���� 75
	int JPGquality;
	//��Ƶͼ���
	int Width;
	//��Ƶͼ���
	int Hight;
	//������С��� 60
	int MinWidth;
	//��������� 180
	int MaxWidth;
	//��ⷶΧ ������ 
	Rects Range;
	//��ⷶΧ ������ 
	Rects RangeRate;
	//Ĭ��ʡ���ַ�  
	//ʡ�ݺ��֣��� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� ԥ �� �� �� �� �� �� �� ³ ��
	char DefaultChar[CAR_STR_MAX];
	//31��ʡ ��־λ
	//�� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� ԥ �� �� �� �� �� �� �� ³ �� (ʡ��)
	//1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	unsigned char Mask[CAR_MASK_MAX];
	//�������Ŷ� 75
	int Reliability;
	//������ɫʶ���־��0:��ʶ��1:ʶ��
	int CarColor;
};

#endif

class CDLGSetElecar : public CDialog
{
// Construction
public:
	struct CarSetStruct CarSet;
	void ReadOldConfig(struct CarSetStruct OldCarSet);
public:
	CDLGSetElecar(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDLGSetElecar)
	enum { IDD = IDD_SET_ELECAR };
	int		m_JPGquality;
	int		m_RectDown;
	int		m_RectLeft;
	int		m_RectRight;
	int		m_RectUp;
	int		m_MaxWidth;
	int		m_MinWidth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDLGSetElecar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDLGSetElecar)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETELECAR_H__0BA2D819_DCBC_46C1_A79B_7FB5F827563E__INCLUDED_)
