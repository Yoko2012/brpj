#ifndef __YUAN_CACHE_H__
#define __YUAN_CACHE_H__

#define YF_RGBA_8(r, g, b, a) (unsigned int)(((unsigned int)((unsigned char)(b))) | ((unsigned int)(((unsigned char)(g))<<8)) | ((unsigned int)(((unsigned char)(r))<<16)) | ((unsigned int)(((unsigned char)(a))<<24)))

// ������ɫ�ṹ��
typedef struct tagRGBDATATYPE
{
	DWORD dwRed; // ��
	DWORD dwGreen; // ��
	DWORD dwBlue; // ��
}RGBDATATYPE;

//bmp��ʽ���ͣ�BI_BITFIELDS������ҪRGBDATATYPE
typedef struct tagBMPINFOTYPE
{
	BITMAPINFOHEADER bmiHeader;
	RGBDATATYPE bmiColors[1];
}BMPINFOTYPE, *PBMPINFOTYPE;

/*
���ļ���������˫������
*/

class CDCCache
{
public:
	CDCCache();
	~CDCCache();
	// ��������DC
	bool CreateCache(int nWidth, int nHeight, int nBitCount);
	// �ͷŻ���DC
	void FreeCache(void);
	// ��ȡ����ָ��
	unsigned char *GetCacheBuffer(void);
	// ��ȡ����DC
	CDC *GetCacheDC(void);
	// �ڻ���DC�ϻ�һ����
	void DrawRectangle(int x, int y, int w, int h, int nBold, unsigned int nColor = YF_RGBA_8(255, 0, 0, 255));
	
	CDC m_MemDC; //����һ���ڴ��豸��������󣨼��󱸻�������

private:
	int m_nBitCount; // ��ɫλ��
	int m_nWidth; // �ڴ���
	int m_nHeight; // �ڴ���
	unsigned char *m_pBuffer; // �ڴ�ָ��
	HBITMAP m_hBitmap;
	HBITMAP m_hOldBitmap;
	 CBitmap m_pBitmap;
	bool m_bCreate; // �Ƿ���Ҫ����cdc
};

#endif /* __YUAN_CACHE_H__ */