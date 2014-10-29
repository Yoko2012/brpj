#include "StdAfx.h"
#include "Common.h"
#include "md5.h"

CCommon::CCommon(void)
{
}

CCommon::~CCommon(void)
{
}


CString CCommon::Char2CString(char * str)
{
	CString tmp;
	tmp.Append(str);
	return tmp;
}

char * CCommon::CString2Char(CString str)
{
	return str.GetBuffer();
}

CString CCommon::GetSystemFolder()
{
	CString sysPath;
	UINT size = GetSystemDirectory(NULL,0);
	CHAR * path = new CHAR[size];
	if(GetSystemDirectory(path,size) != 0)
	{
		sysPath.Append(path);
	}
	delete[] path;
	return sysPath;
}

char * CCommon::EncodeMd5(char * input)
{
	CMD5 md5;
	md5.GenerateMD5 ((unsigned char*)input,strlen(input));
	std::string md5string = md5.ToString();

	int len = md5string.length();
	char * retchar = new char[len];
	memset(retchar, 0, len);
	memcpy(retchar, md5string.c_str(),len+1);
	return (char *)retchar;
}

/************************************
* �豸��ʼ��
*************************************/
bool CCommon::InitialDevice(CComboBox &m_cbDevice, LONG * width, LONG * height)
{
	LONG w = 0, h = 0;
	bool m_bCameraOpen = false;
	int cam_count = GetCameraCount();//������ȡ����ͷ��Ŀ
	m_cbDevice.SetDroppedWidth(cam_count);
	//��ȡ��������ͷ������
	for(int i=0; i < cam_count; i++)
	{
		char camera_name[1024];  
		int retval = GetCameraName(i, camera_name, sizeof(camera_name));
		if(retval >0)
		{
			CString str,str_camera_name;
			str_camera_name = CCommon::Char2CString(camera_name);
			//��ֹ����ͷ����̫����������ʾ����
			int spaceNum = str_camera_name.Find(" ");
			CString strTemp = str_camera_name.Mid(0,spaceNum);
			str.Format("[%d] %s",i,strTemp);
			m_cbDevice.InsertString(i,str.GetBuffer(0));
		}
	}

	if(cam_count > 0)
	{		
		CString camera = CCommon::GetReg("Camera");
		int m_iCameraIndex = atoi(CCommon::CString2Char(camera));//ע����ȡ����ͷid

		if(m_iCameraIndex < 0 || m_iCameraIndex > cam_count - 1) m_iCameraIndex = 0;
			m_cbDevice.SetCurSel(m_iCameraIndex);//����Ĭ��ѡ�е�һ������ͷ�����ڴ������ļ���ȡ

		//�򿪵�һ������ͷ
		if(OpenCameraCB(m_iCameraIndex, false, &w,&h)) //����������ѡ�񴰿ڣ��ô����ƶ�ͼ���͸�
		{
			m_bCameraOpen = TRUE;
		}

		if(m_bCameraOpen == false)
		{
			for(int k = 0; k < cam_count; k++)
			{
				//�򿪵�һ������ͷ
				if(OpenCameraCB(k, false, &w, &h)) //����������ѡ�񴰿ڣ��ô����ƶ�ͼ���͸�
				{
					m_bCameraOpen = TRUE;
					break;
				}
			}
			
			if(m_bCameraOpen == false && cam_count> 0)
			{
				//AfxMessageBox("����ͷ��ʼ��ʧ��", MB_OK, MB_ICONINFORMATION);
			
				//OnOK();
				*width = w;
				*width = h;
				return false;
			}
		}
	}
	*width = w;
	*height = h;
	return true;
}

/// <summary>
/// ��ȡע���ֵ
/// </summary>
/// <param name="lpValueKey">����</param>
/// <returns>��ֵ</returns>
CString CCommon::GetReg(CString lpValueKey)
{
	unsigned char buffer[255]={0};
	unsigned long length;
	unsigned long type;
	HKEY hKey;
	LPCTSTR data_Set= _T("SOFTWARE\\Microsoft");

	RegOpenKey(HKEY_LOCAL_MACHINE,data_Set,&hKey);
	RegQueryValueEx(hKey,lpValueKey,NULL,&type,buffer,&length);
	RegCloseKey(hKey);

	CString ret;
	ret = Char2CString((char *)buffer);

	int Count;
	Count = atoi((const char*)buffer);
	if(Count == 0)
	{
		RegCreateKey(HKEY_LOCAL_MACHINE,data_Set,&hKey);
		RegSetValueEx(hKey,lpValueKey,0,REG_SZ,(const unsigned char *) "0",1);
		RegCloseKey(hKey);

		return "0";
	}

	return ret;
}

/// <summary>
/// ����ע���ֵ
/// </summary>
/// <param name="lpValueKey">����</param>
/// <param name="lpValueName">��ֵ</param>
/// <returns></returns>
void CCommon::SetReg(CString lpValueKey, CString lpValueName)
{
	unsigned char buffer[255]={0};
	unsigned long length;
	unsigned long type;
	HKEY hKey;
	LPCTSTR data_Set= _T("SOFTWARE\\Microsoft");

	RegOpenKey(HKEY_LOCAL_MACHINE,data_Set,&hKey);
	RegQueryValueEx(hKey,lpValueKey,NULL,&type,buffer,&length);
	RegCreateKey(HKEY_LOCAL_MACHINE,data_Set,&hKey);
	RegSetValueEx(hKey,lpValueKey,0,REG_SZ,(const unsigned char *) CString2Char(lpValueName),lpValueName.GetLength());
	RegCloseKey(hKey);
}

CRect CCommon::SetDrawSize(CStatic * m_picBox,CRect old_DrawRect,int bmpw,int bmph,float *scale) 
{
	//////////////������ο� �������δˢ��BUG

	CRect rect;

	// ��ȡͼƬ�Ŀ�͸�
	int w = bmpw;
	int h = bmph;
	// �ҳ���͸��еĽϴ�ֵ��
	int max = (w > h)? w: h;
	// ���㽫ͼƬ���ŵ�TheImage��������ı�������
	(*scale) = 1.0;
	int rw ,rh;
	rw = old_DrawRect.Width();// ���ͼƬ�ؼ��Ŀ�͸�
	rh = old_DrawRect.Height();
	(*scale) = (float)rh/h <(float) rw/w ?(float)rh/h:(float) rw/w;
	// ���ź�ͼƬ�Ŀ�͸�
	int nw = (int)( w* (*scale) );
	int nh = (int)( h*(*scale) );
	int iw = nw;//img->width;						// ��ȡͼƬ�Ŀ�͸�
	int ih = nh;//img->height;
	int tx = (int)(rw - iw)/2;					// ʹͼƬ����ʾλ�������ڿؼ�������
	int ty = (int)(rh - ih)/2;
	SetRect( rect, tx, ty, tx+iw, ty+ih );

	CRect new_clientRect;
	new_clientRect.left	=	old_DrawRect.left+rect.left;
	new_clientRect.top	=	old_DrawRect.top+rect.top;
	new_clientRect.bottom	=	new_clientRect.top+rect.Height();
	new_clientRect.right	=	new_clientRect.left+rect.Width();

	//���þ���
	m_picBox->MoveWindow(new_clientRect);

	//���û�ͼ����
	SetRect( rect, 0, 0, iw, ih );

	return rect;

}

/************************************
* ��ͼ
*************************************/
void CCommon::DrawCtrlImage(CStatic * m_picBox, BITMAPINFO bmpInfo,
							char * buffer, int bufferSize,
							int face_Count, CRect *face_Rect_List, 
							CRect rect,float scale)
{
	CRect tempRect;
	CDC *pDC = m_picBox->GetDC();
	if(NULL == pDC)
		return;
	HDC hdc = pDC->GetSafeHdc();
	HDC hdcMem = CreateCompatibleDC(hdc); 

	LPBYTE   lpBits;
	HBITMAP hBmp = CreateDIBSection(hdcMem,&bmpInfo,DIB_RGB_COLORS,(void **)&lpBits,NULL,0);  
	memcpy(lpBits, buffer, bufferSize);
	HBITMAP hOldBmp = (HBITMAP)SelectObject(hdcMem, hBmp); 

	
	CBrush tempBrush(RGB(0,255,0));

	//	free(lpBits);
	for(int i=0;i<face_Count;i++)
	{
		tempRect.left = face_Rect_List[i].left-1;
		tempRect.top  = face_Rect_List[i].top-1;
		tempRect.bottom = face_Rect_List[i].bottom+1;
		tempRect.right  = face_Rect_List[i].right+1;


		//FILE *fp = fopen("D:\\rect.txt","a+");
		//if(fp)
		//{
		//	fprintf(fp,"************************scale = %f*********************************\n",scale);
		//	fprintf(fp,"left = %d\ntop = %d\nbottom = %d\nright=%d\n",face_Rect_List[i].left,face_Rect_List[i].top,face_Rect_List[i].bottom,face_Rect_List[i].right);
		//	fprintf(fp,"left = %d\ntop = %d\nbottom = %d\nright=%d\n",rect.left,rect.top,rect.bottom,rect.right);
		//	fprintf(fp,"left = %d\ntop = %d\nbottom = %d\nright=%d\n",tempRect.left,tempRect.top,tempRect.bottom,tempRect.right);
		//	fprintf(fp,"**************************************************************\n");
		//	fclose(fp);
		//}
		//pDC->FrameRect(rect, &pen);
		FrameRect(hdcMem, face_Rect_List[i], (HBRUSH)tempBrush);
		FrameRect(hdcMem, tempRect, (HBRUSH)tempBrush);

		tempRect.left = face_Rect_List[i].left-2;
		tempRect.top  = face_Rect_List[i].top-2;
		tempRect.bottom = face_Rect_List[i].bottom+2;
		tempRect.right  = face_Rect_List[i].right+2;

		FrameRect(hdcMem, tempRect, (HBRUSH)tempBrush);

		tempRect.left = face_Rect_List[i].left-3;
		tempRect.top  = face_Rect_List[i].top-3;
		tempRect.bottom = face_Rect_List[i].bottom+3;
		tempRect.right  = face_Rect_List[i].right+3;

		FrameRect(hdcMem, tempRect, (HBRUSH)tempBrush);
	}


	char str[128]="";
	if(face_Count > 0)
	{
		strcpy(str,"���������У��뱣������");
		SetTextColor(hdcMem,RGB(0,0,255));
	}
	else
	{
		strcpy(str,"δ��⵽����������������ͷ");
		SetTextColor(hdcMem,RGB(255,0,0));
	}
	CFont font;
	VERIFY(font.CreateFont(
		28/scale,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_HEAVY,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		"Arial"));                 // lpszFacename

	// Do something with the font just created...
	SetBkMode(hdcMem,TRANSPARENT);

	HGDIOBJ oldfont=SelectObject(hdcMem,font);

	DrawText(hdcMem,str,-1,CRect(0,-bmpInfo.bmiHeader.biHeight+20/scale,bmpInfo.bmiHeader.biWidth,bmpInfo.bmiHeader.biHeight),DT_SINGLELINE|DT_CENTER|DT_VCENTER); 

	//SetStretchBltMode(hdc, HALFTONE);
	SetStretchBltMode(hdc, COLORONCOLOR);
	StretchBlt(hdc, rect.left,rect.top,rect.Width(),rect.Height(), hdcMem, 0, 0, bmpInfo.bmiHeader.biWidth, bmpInfo.bmiHeader.biHeight, SRCCOPY);	

	SelectObject(hdcMem,oldfont);

	SelectObject(hdcMem,hOldBmp);//��ԭ����DC����.
	DeleteDC(hdcMem);
	DeleteObject(hOldBmp);
	DeleteObject(hBmp);


	if(NULL != pDC)
	{
		m_picBox-> ReleaseDC(pDC);
	}
}

int CCommon::GetCamNum()
{
	int cam_count = GetCameraCount();//������ȡ����ͷ��Ŀ
	return cam_count;
}

void CCommon::DrawFaceImageMin(CStatic *m_picBox,unsigned char *image,unsigned long int size)
{
	CRect rect; 
	m_picBox->GetClientRect(&rect);//���pictrue�ؼ����ڵľ�������
	CDC *pDC=m_picBox->GetDC();//���pictrue�ؼ���DC 

	IPicture *pPic;//������ʾͼƬ�Ľӿڣ�����ʾjpg��ʽͼƬ��

	HGLOBAL hGlobal=GlobalAlloc(GMEM_MOVEABLE,size);//�����ڴ�ռ�
	void *pData=GlobalLock(hGlobal);//����ͼ������ָ��
	memcpy(pData,image,size); 
	GlobalUnlock(hGlobal);//�ͷ��ڴ�ռ�
	IStream *pStream=NULL;//����������ָ��
	//����������
	if(CreateStreamOnHGlobal(hGlobal,TRUE,&pStream)==S_OK) 
	{ 
		//װ��ͼ���ļ�
		if(SUCCEEDED(OleLoadPicture(pStream,size,TRUE,IID_IPicture,(LPVOID*)&pPic))) 
		{  
			OLE_XSIZE_HIMETRIC hmWidth; 
			OLE_XSIZE_HIMETRIC hmHeight; 
			pPic->get_Width(&hmWidth);//���ͼ����ʵ���
			pPic->get_Height(&hmHeight);//���ͼ����ʵ�߶�
	
			//�ڿؼ�����ʾͼƬ
			pPic->Render(*pDC,4,4,rect.Width()-8,rect.Height()-8,0,hmHeight,hmWidth,-hmHeight,NULL); 
			pPic->Release(); 
			pStream->Release();//�ͷ�������
		
		}  
	}

	if(hGlobal)
	{
		GlobalFree(hGlobal);
		hGlobal = NULL;
	}
	m_picBox-> ReleaseDC(pDC);
}

void CCommon::DrawFaceImage(CStatic *m_picBox,CBitmap    *cbitmap,    BITMAP *bitbmp)
{
	CRect rect; 
	m_picBox->GetClientRect(&rect);//���pictrue�ؼ����ڵľ�������
	CDC *pDC=m_picBox->GetDC();//���pictrue�ؼ���DC 

	CDC    memdc;     
	memdc.CreateCompatibleDC(pDC);     
	memdc.SelectObject(cbitmap); 
	pDC->SetStretchBltMode(COLORONCOLOR);
	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&memdc,0,0,bitbmp->bmWidth,bitbmp->bmHeight,SRCCOPY);
	memdc.DeleteDC();

	m_picBox-> ReleaseDC(pDC);
}