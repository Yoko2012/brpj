// ListCtrlEx.cpp : implementation file
//

#include "stdafx.h"
#include "ListCtrlEx.h"
#include "SmartVillage.h"
#include "SmartVillageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
// CListCtrlEx

/*
//��Ҫ����
#include <afxdisp.h>        // MFC Automation classes
#include <afxtempl.h>
#endif // _AFX_NO_AFXCMN_SUPPORT
*/


IMPLEMENT_DYNAMIC(CListCtrlEx, CListCtrl)
CListCtrlEx::CListCtrlEx() :m_ProgressValueColumn(0),m_ProgressColumn(1),m_Style(NULL),m_StyleEx(NULL),m_max(100)
{
	m_BKcolor=RGB(0,0,0);
	m_color=RGB(255,0,0);
}

CListCtrlEx::~CListCtrlEx()
{
}


BEGIN_MESSAGE_MAP(CListCtrlEx, CListCtrl)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CListCtrlEx message handlers


void CListCtrlEx::OnPaint()
{
	// TODO: Add your message handler code here
	// Do not call CListCtrl::OnPaint() for painting messages

	int Top=GetTopIndex();
	int Total=GetItemCount();
	int PerPage=GetCountPerPage();
	int LastItem=((Top+PerPage)>Total)?Total:Top+PerPage;

	// if the count in the list os nut zero delete all the progress controls and them procede
	{
		int Count=(int)m_ProgressList.GetSize();
		for(int i=0;i<Count;i++)
		{
			CProgressCtrl* pControl=m_ProgressList.GetAt(0);
			pControl->DestroyWindow();
			//�޸��ڴ�й¶
			delete pControl;
			m_ProgressList.RemoveAt(0);
		}
	}

	CHeaderCtrl* pHeader=GetHeaderCtrl();
	for(int i=Top;i<LastItem;i++)
	{
		CRect ColRt;
		pHeader->GetItemRect(m_ProgressColumn,&ColRt);
		// get the rect
		CRect rt;
		GetItemRect(i,&rt,LVIR_LABEL);
		rt.top+=1;
		rt.bottom-=1;
		rt.left+=ColRt.left;
		int Width=ColRt.Width();
		rt.right=rt.left+Width-4;
		/*
		rt.left=ColRt.left+1;
		rt.right=ColRt.right-1;
		*/

		// create the progress control and set their position
		CProgressCtrl* pControl=new CProgressCtrl();
		pControl->Create(m_Style,rt,this,IDC_PROGRESS_LIST+i);

		CString Data=GetItemText(i,m_ProgressValueColumn);
		int Percent=atoi(Data);

		// set the position on the control

		pControl->SetRange32(0,m_max);
		pControl->SetPos(Percent);
		pControl->ShowWindow(SW_SHOWNORMAL);
		// add them to the list
		m_ProgressList.Add(pControl);

		//����ǰ��ɫ
		pControl->SendMessage(PBM_SETBARCOLOR, 0, m_color);   
	//	pControl->SendMessage(PBM_SETBKCOLOR, 0, m_BKcolor); 
		//����ɫ ʹ��LISTCTRL�ı���ɫ
		pControl->SendMessage(PBM_SETBKCOLOR, 0, GetBkColor()); 
	
		//���
		pControl->ModifyStyleEx(m_StyleEx,0); 

	}
	CListCtrl::OnPaint();
}

void CListCtrlEx::InitProgressColumn(int ValueNum,int ColNum/*=0*/)
{
	//ֵ�ڵڼ���
	m_ProgressValueColumn=ValueNum;
	m_ProgressColumn=ColNum;
}

void CListCtrlEx::InitProgressStyle(DWORD style)
{
	m_Style=style;
}
//����ķ��
void CListCtrlEx::InitProgressStyleEx(DWORD styleEx)
{
	m_StyleEx=styleEx;
	//WS_EX_STATICEDGE �ް��ݿ�
}

//ǰ���ͱ���ɫ
void CListCtrlEx::InitProgressColor(DWORD color,DWORD BKcolor)
{
	m_BKcolor=BKcolor;
	m_color=color;
}

void CListCtrlEx::InitProgressMax(unsigned long int max)
{
	m_max=max;
}