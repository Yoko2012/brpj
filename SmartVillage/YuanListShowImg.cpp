#include "stdafx.h"
#include "YuanListShowImg.h"
#include "Picture.h"

CYuanListShowImg::CYuanListShowImg()
{
	m_plcShow = NULL;
	m_nImgWidth = 0;
	m_nImgHeight = 0;
	m_nColorType = ILC_COLOR24;
	m_pDefaultBmp = NULL;
}
CYuanListShowImg::~CYuanListShowImg()
{
	ClearImageList();
}
/*
* �ⲿֻ��Ҫ����һ��CListCtrlֱ�Ӵ��Ϳ���
*/
bool CYuanListShowImg::Init(CListCtrl *pLctrl, int nImgWidth, int nImgHeight, CBitmap *pDefaultBmp, int nColorType)
{
	m_plcShow = pLctrl;
	m_nImgWidth = nImgWidth;
	m_nImgHeight = nImgHeight;
	m_nColorType = nColorType;
	m_pDefaultBmp = pDefaultBmp;
	// ����CListCtrl�ؼ���չ���(�����ߡ�����ѡ�С�ͼƬ)  
	DWORD dwStyle;  
	dwStyle = m_plcShow->GetExtendedStyle();  
	dwStyle = dwStyle|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_SUBITEMIMAGES;  // Ҫ��ʾͼƬ�����LVS_EX_SUBITEMIMAGES
	m_plcShow->SetExtendedStyle(dwStyle);
	//BitmapͼƬ(���ͼƬ��С��ͳһ������Ӧ������Ϊ��С�ģ���Ȼ�п���ͼƬ���ز��ɹ�)  
	m_imList.Create(m_nImgWidth, m_nImgHeight, m_nColorType, 0, 4);  

	// ����ͼ���б���CListCtrl�ؼ�������Ҫʹ��LVSIL_SMALL���  
	m_plcShow->SetImageList(&m_imList,LVSIL_SMALL ); //����Ҫʹ�ã�LVSIL_SMALL���
	return true;
}

/*
* �����б�
*/
int CYuanListShowImg::InsertColumn(int nCol, LPCTSTR lpszColumnHeading, int nFormat,  int nWidth, int nSubItem)
{
	return m_plcShow->InsertColumn(nCol, lpszColumnHeading, nFormat, nWidth, nSubItem);
}
/*
* ���÷��
*/
int CYuanListShowImg::SetExtendedStyle(int nNewStyle)
{
	return m_plcShow->SetExtendedStyle(nNewStyle);
}
/*
* ��ȡ���
*/
int CYuanListShowImg::GetExtendedStyle(void)
{
	return m_plcShow->GetExtendedStyle();
}
/*
* �����0
*/
void CYuanListShowImg::ReSetExtendedStyle(int nNewStyle)
{
	m_plcShow->SetExtendedStyle(nNewStyle);
}
/*
* ���һ��ͼƬ
*/
bool CYuanListShowImg::AddImg(char *pImgPath)
{
	{
	//	GetScaleBitmap(pImgPath, m_nImgWidth, m_nImgHeight);
	}
	int bef = m_imList.GetImageCount();
	
	CPicture pic;
	int nRet = 0;
	CBitmap * pBmp = NULL; 

	/*pBmp = new CBitmap();  
	HBITMAP bmp = NULL;
	bmp = pic.LoadPicture(pImgPath);
	nRet = pBmp->Attach(bmp);*/

	//��������档��Ȼָ��ᱻ���ٵ��²���ʾͼ��
	HBITMAP bmp = NULL;
	bmp = pic.LoadPicture(pImgPath);

	pBmp = GetScaleBitmap(bmp, m_nImgWidth, m_nImgHeight);
	if(NULL == pBmp)
	{
		// ����ʧ��ʱ���������һ��Ĭ�ϵ�ͼƬ����Ȼ�����ͼƬ��Ż������ƶ�
		// ����ͼƬ��ʾ����
		nRet = m_imList.Add(m_pDefaultBmp,RGB(0,0,0));  
		return true;
	}
	
	nRet = m_imList.Add(pBmp,RGB(0,0,0));  

	if (nRet == -1)
	{
		// ����ʧ��ʱ���������һ��Ĭ�ϵ�ͼƬ����Ȼ�����ͼƬ��Ż������ƶ�
		// ����ͼƬ��ʾ����
		nRet = m_imList.Add(m_pDefaultBmp,RGB(0,0,0));  
	}
	else
	{
		int aft = m_imList.GetImageCount();
		if(bef==aft)
		{
			nRet = m_imList.Add(m_pDefaultBmp,RGB(0,0,0));
		}
	}
	delete pBmp; 

	if (nRet == -1)
		return false;
	return true;
}
/*
* ����Ĭ��ͼƬ
*/
BOOL CYuanListShowImg::SetDefaultBitmap(CBitmap *pBmp)
{
	m_pDefaultBmp = pBmp;
	return TRUE;
}
/*
* ɾ��ָ��ͼƬ
*/
BOOL CYuanListShowImg::RemoveImg(int nIndex)
{
	if (nIndex >= m_imList.GetImageCount())
		return FALSE;
	return m_imList.Remove(nIndex);
}
/*
* ���ͼƬ����
*/
void CYuanListShowImg::ClearImageList(void)
{
	int nCount = m_imList.GetImageCount();
	int i = 0;
	for (i = nCount-1; i >= 0; i--)
	{
		m_imList.Remove(i);
	}
}
/*
* ����ͼƬitem
*/
int CYuanListShowImg::InsertItem(int nItem, int nImgIndex)
{

	LVITEM lvItem={0};
	lvItem.mask = LVIF_IMAGE|LVIF_TEXT|LVIF_STATE;  //���֡�ͼƬ��״̬  
	lvItem.iItem = nItem;       //�к�(��һ��)  
	lvItem.iImage = nImgIndex;  //ͼƬ������(��һ��ͼƬ)  
	lvItem.iSubItem = 0;    //���к�  
	//��һ��ΪͼƬ
	return m_plcShow->InsertItem(&lvItem);
}
/*
* ����item���ݣ���0��Ĭ��ΪͼƬ�У����ܲ�������)
*/
BOOL CYuanListShowImg::SetItemText(int nItem, int nSubItem, LPCTSTR lpszText)
{
	return m_plcShow->SetItemText(nItem, nSubItem, lpszText); 
}
/*
* �����б���е�����λ��
*/
void CYuanListShowImg::SwapColumns(int c1, int c2)
{
	CHeaderCtrl *pmyHeaderCtrl = m_plcShow->GetHeaderCtrl();
	int   nCount   =   pmyHeaderCtrl->GetItemCount();   
	LPINT   pnOrder   =   (LPINT)   malloc(nCount*sizeof(int));   
	ASSERT(pnOrder   !=   NULL);   

	pmyHeaderCtrl->GetOrderArray(pnOrder,   nCount);   
	int nTemp;
	nTemp     = pnOrder[c1];
	pnOrder[c1]        =   pnOrder[c2];  
	pnOrder[c2] = nTemp;

	pmyHeaderCtrl->SetOrderArray(nCount,   pnOrder);   
	free(pnOrder);
}
/*
* ����ָ����С��CBitmap���ⲿ�ͷſռ�)
*/
CBitmap *CYuanListShowImg::GetScaleBitmap(HBITMAP bmp,int w, int h)
{
	CPicture pic;

	if(NULL== bmp)
		return NULL;

	CBitmap *pBitmap = new CBitmap();
	pBitmap->Attach(bmp);
	BITMAP bitInfo = {0};
	pBitmap->GetBitmap(&bitInfo);


	// ��С���ϾͲ�����
	if (bitInfo.bmWidth == w && bitInfo.bmHeight == h)
		return pBitmap;

	CDC memdc;
	memdc.CreateCompatibleDC(NULL);     
	memdc.SelectObject(pBitmap);

	CDC m_dcCompatible;
	m_dcCompatible.CreateCompatibleDC(&memdc); // �˺�������DC���븳ֵ
	CBitmap *pTemp = new CBitmap();
	pTemp->CreateCompatibleBitmap(&memdc, w, h); // �˺�������DC���븳ֵ
	m_dcCompatible.SelectObject(pTemp);
		
	m_dcCompatible.SetStretchBltMode(COLORONCOLOR);
	m_dcCompatible.StretchBlt(0, 0, w, h, &memdc,0, 0, 
		bitInfo.bmWidth, bitInfo.bmHeight, SRCCOPY);
	m_dcCompatible.DeleteDC();
	memdc.DeleteDC();
	delete pBitmap;

	return pTemp;
}
/*
* ��list ��imagelist��������
*/
void CYuanListShowImg::ListComImageList(void)
{
	// ����ͼ���б���CListCtrl�ؼ�������Ҫʹ��LVSIL_SMALL���  
	m_plcShow->SetImageList(&m_imList,LVSIL_SMALL ); //����Ҫʹ�ã�LVSIL_SMALL���
}