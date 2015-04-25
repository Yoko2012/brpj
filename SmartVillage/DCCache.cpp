#include "stdafx.h"
#include "DCCache.h"


CDCCache::CDCCache()
{
	m_nWidth = 0;
	m_nHeight = 0;
	m_hBitmap = NULL;
	m_hOldBitmap = NULL;
	m_pBuffer = NULL;
	m_bCreate = true;
}
CDCCache::~CDCCache()
{

	FreeCache(m_MemDC);
}
// ��������DC
bool CDCCache::CreateCache(int nWidth, int nHeight, int nBitCount)
{
	bool bRet = false;
	BMPINFOTYPE bi = {0};

	if (m_bCreate)
	{
		m_MemDC.CreateCompatibleDC(NULL);
		m_bCreate = false;
	}
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_nBitCount = nBitCount;
	// ͼƬ�ߴ�
	bi.bmiHeader.biWidth = m_nWidth;
	bi.bmiHeader.biHeight = -m_nHeight;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = m_nBitCount;
	bi.bmiHeader.biSizeImage = m_nWidth*m_nHeight*(nBitCount/8);
	if (m_nBitCount == 32)
	{
		// ���ͼƬ��ʾ��ɫ����(r��bλ�÷��ˣ�����ʹ��BI_RGB����
		bi.bmiHeader.biCompression = BI_BITFIELDS; 
		bi.bmiColors[0].dwRed = 0xFF; //��5λ
		bi.bmiColors[0].dwGreen = 0x00FF00; //6λ
		bi.bmiColors[0].dwBlue = 0xFF0000; //��5λ
	}
	else if (m_nBitCount == 24)
	{
		bi.bmiHeader.biCompression = BI_RGB;
	}
	else
	{// ����Ϊ16λ
		bi.bmiHeader.biCompression = BI_BITFIELDS;
		bi.bmiColors[0].dwRed = 0xF800; //��5λ
		bi.bmiColors[0].dwGreen = 0x07E0; //6λ
		bi.bmiColors[0].dwBlue = 0x001F; //��5λ
	}

	m_hBitmap = CreateDIBSection(NULL, (BITMAPINFO *)&bi, DIB_RGB_COLORS, (void **)&m_pBuffer, NULL, 0);
	if (m_hBitmap != NULL)
	{
		m_hOldBitmap = (HBITMAP)m_MemDC.SelectObject(m_hBitmap);
		bRet = true;
	}
	m_MemDC.SetStretchBltMode(COLORONCOLOR);
	return bRet;
}
// �ͷŻ���DC
void CDCCache::FreeCache(CDC &dc)
{
	if (m_hBitmap != NULL)
	{
		SelectObject(dc, m_hOldBitmap);
		DeleteObject(m_hBitmap);
		m_hBitmap = NULL;
	}
}
void CDCCache::FreeCache()
{
	if (m_hBitmap != NULL)
	{
		SelectObject(m_MemDC, m_hOldBitmap);
		DeleteObject(m_hBitmap);
		m_hBitmap = NULL;
	}
}
// ��ȡ����ָ��
unsigned char *CDCCache::GetCacheBuffer(void)
{	
	
	return m_pBuffer;
}
// ��ȡ����DC
CDC *CDCCache::GetCacheDC(void)
{
	return &m_MemDC;
}
// �ڻ���DC�ϻ�һ����
void CDCCache::DrawRectangle(int x, int y, int w, int h, int nBold, unsigned int nColor)
{
	int i,j;
	unsigned int *pData = (unsigned int *)m_pBuffer;
	// ����
	for (i = x; i < w+x; i++)
	{
		pData[y*m_nWidth+i] = nColor;
	}
	// ����
	for (i = x; i < w+x; i++)
	{
		pData[(y+w)*m_nWidth+i] = nColor;
	}
	// ����
	for (j = y; j < h+y; j++)
	{
		pData[j*m_nWidth+x] = nColor;
	}
	// ����
	for (j = y; j < h+y; j++)
	{
		pData[j*m_nWidth+x+w] = nColor;
	}
}