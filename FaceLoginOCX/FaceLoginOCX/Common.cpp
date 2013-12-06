#include "StdAfx.h"
#include "Common.h"

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
			str.Format("[%d] %s",i,str_camera_name);
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
/*
void CCommon::DrawCtrlImage(CStatic * m_picBox, BITMAPINFO bmpInfo, char * buffer, int bufferSize, int list_size, FaceRect *face_rect_list)
{
	CRect   rect;
	
	CDC *pDC = m_picBox->GetDC();
	if(NULL == pDC)
		return;
	HDC hdc = pDC->GetSafeHdc();
	HDC hdcMem = CreateCompatibleDC(hdc); 
	m_picBox->GetClientRect(&rect);

	LPBYTE   lpBits;
	HBITMAP hBmp = CreateDIBSection(hdcMem,&bmpInfo,DIB_RGB_COLORS,(void **)&lpBits,NULL,0);  
	memcpy(lpBits, buffer, bufferSize);
	HBITMAP hOldBmp = (HBITMAP)SelectObject(hdcMem, hBmp); 

	// ��ȡͼƬ�Ŀ�͸�
	int w = bmpInfo.bmiHeader.biWidth;
	int h = bmpInfo.bmiHeader.biHeight;
	// �ҳ���͸��еĽϴ�ֵ��
	int max = (w > h)? w: h;
	// ���㽫ͼƬ���ŵ�TheImage��������ı�������
	float scale = 0.0;
	int rw ,rh;
	rw = rect.Width();// ���ͼƬ�ؼ��Ŀ�͸�
	rh = rect.Height();
	scale = (float)rh/h <(float) rw/w ?(float)rh/h:(float) rw/w;
	// ���ź�ͼƬ�Ŀ�͸�
	int nw = (int)( w*scale );
	int nh = (int)( h*scale );
	int iw = nw;//img->width;						// ��ȡͼƬ�Ŀ�͸�
	int ih = nh;//img->height;
	int tx = (int)(rw - iw)/2;					// ʹͼƬ����ʾλ�������ڿؼ�������
	int ty = (int)(rh - ih)/2;
	SetRect( rect, tx, ty, tx+iw, ty+ih );
	//SetStretchBltMode(hdc, HALFTONE);
	SetStretchBltMode(hdc, COLORONCOLOR);
	StretchBlt(hdc, rect.left,rect.top,rect.Width(),rect.Height(), hdcMem, 0, 0, bmpInfo.bmiHeader.biWidth, bmpInfo.bmiHeader.biHeight, SRCCOPY);	

	SelectObject(hdcMem,hOldBmp);//��ԭ����DC����.
	DeleteDC(hdcMem);
	DeleteObject(hOldBmp);
	DeleteObject(hBmp);
//	free(lpBits);

	for(int i=0;i<list_size;i++)
	{
		rect.left = face_rect_list[i].left*scale;
		rect.top  = face_rect_list[i].top*scale;
		rect.bottom = face_rect_list[i].bottom*scale;
		rect.right  = face_rect_list[i].right*scale;
		CBrush tempBrush(RGB(0,255,0));

		//pDC->FrameRect(rect, &pen);
		pDC->FrameRect(rect, &tempBrush);
	}

	if(NULL != pDC)
	{
		m_picBox-> ReleaseDC(pDC);
	}

}
*/

void CCommon::DrawCtrlImage(CStatic * m_picBox, BITMAPINFO bmpInfo,
							char * buffer, int bufferSize,
							int list_size, FaceRect *face_rect_list,
							CRect rect,float scale)
{
	
	CDC *pDC = m_picBox->GetDC();
	if(NULL == pDC)
		return;
	HDC hdc = pDC->GetSafeHdc();
	HDC hdcMem = CreateCompatibleDC(hdc); 

	LPBYTE   lpBits;
	HBITMAP hBmp = CreateDIBSection(hdcMem,&bmpInfo,DIB_RGB_COLORS,(void **)&lpBits,NULL,0);  
	memcpy(lpBits, buffer, bufferSize);
	HBITMAP hOldBmp = (HBITMAP)SelectObject(hdcMem, hBmp); 


	//SetStretchBltMode(hdc, HALFTONE);
	SetStretchBltMode(hdc, COLORONCOLOR);
	StretchBlt(hdc, rect.left,rect.top,rect.Width(),rect.Height(), hdcMem, 0, 0, bmpInfo.bmiHeader.biWidth, bmpInfo.bmiHeader.biHeight, SRCCOPY);	


	SelectObject(hdcMem,hOldBmp);//��ԭ����DC����.
	DeleteDC(hdcMem);
	DeleteObject(hOldBmp);
	DeleteObject(hBmp);
//	free(lpBits);

	for(int i=0;i<list_size;i++)
	{
		rect.left = face_rect_list[i].left*scale;
		rect.top  = face_rect_list[i].top*scale;
		rect.bottom = face_rect_list[i].bottom*scale;
		rect.right  = face_rect_list[i].right*scale;
		CBrush tempBrush(RGB(0,255,0));

		//pDC->FrameRect(rect, &pen);
		pDC->FrameRect(rect, &tempBrush);
	}

	if(list_size > 0)
	{
		pDC->SetTextColor(RGB(0,0,255));
		pDC->DrawText("  ���������У��뱣������  ",CRect(180,-380,400,400),DT_SINGLELINE|DT_LEFT|DT_VCENTER); 
	}
	else
	{
		pDC->SetTextColor(RGB(255,0,0));
		pDC->DrawText("δ��⵽����������������ͷ",CRect(180,-380,400,400),DT_SINGLELINE|DT_LEFT|DT_VCENTER); 
	}

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