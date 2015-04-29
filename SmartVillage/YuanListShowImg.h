#ifndef __YUAN_LIST_SHOWIMG_H__
#define __YUAN_LIST_SHOWIMG_H__

/*
* ������Ҫʱʵ����list��item�в���jpgͼƬ
*/
class CYuanListShowImg
{
public:
	CYuanListShowImg();
	~CYuanListShowImg();
	/*
	* ��������
	*/
	bool Init(CListCtrl *pLctrl, int nImgWidth, int nImgHeight, CBitmap *pDefaultBmp, int nColorType = ILC_COLOR24);
	/*
	* �����б�(Ҳ�������ⲿ����)
	*/
	int InsertColumn(int nCol, LPCTSTR lpszColumnHeading, int nFormat = LVCFMT_LEFT,  int nWidth = -1, int nSubItem = -1);

	/*
	* ���һ��ͼƬ
	*/
	bool AddImg(char *pImgPath);
	/*
	* ����Ĭ��ͼƬ
	*/
	BOOL SetDefaultBitmap(CBitmap *pBmp);
	/*
	* ɾ��ָ��ͼƬ(ɾ���󣬺���Ļ���ǰ�ƣ������)
	*/
	BOOL RemoveImg(int nIndex);
	/*
	* ���ͼƬ����
	*/
	void ClearImageList(void);
	/*
	* ����ͼƬitem(����nItem��nImgIndex��һ�µ�)
	*/
	int InsertItem(int nItem, int nImgIndex);
	/*
	* ����item���ݣ���0��Ĭ��ΪͼƬ�У����ܲ�������)
	*/
	BOOL SetItemText(int nItem, int nSubItem, LPCTSTR lpszText);
	/*
	* �����б���е�����λ��
	*/
	void SwapColumns(int c1, int c2);
	/*
	* ����ָ����С��CBitmap���ⲿ�ͷſռ�)
	*/
	CBitmap *GetScaleBitmap(HBITMAP bmp, int w, int h);
	/////////////���µĿ��Բ���///////////////
	/*
	* ��list ��imagelist��������
	*/
	void ListComImageList(void);
	/*
	* ���÷��
	*/
	int SetExtendedStyle(int nNewStyle);
	/*
	* ��ȡ���
	*/
	int GetExtendedStyle(void);
	/*
	* �����0
	*/
	void ReSetExtendedStyle(int nNewStyle = 0);
private:
	CListCtrl *m_plcShow; // �б�ָ��
	CImageList m_imList; // ͼƬ�б�ָ��
	int m_nImgWidth;
	int m_nImgHeight;
	CBitmap *m_pDefaultBmp;
	int m_nColorType;
};
#endif /* __YUAN_LIST_SHOWIMG_H__ */