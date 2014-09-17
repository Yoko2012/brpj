// DLGpictureView.cpp : implementation file
//

#include "stdafx.h"
#include "YiRongCarDetectAIO.h"
#include "DLGpictureView.h"

// CDLGpictureView dialog

IMPLEMENT_DYNAMIC(CDLGpictureView, CDialog)

CDLGpictureView::CDLGpictureView(CWnd* pParent /*=NULL*/)
	: CDialog(CDLGpictureView::IDD, pParent)
{

}

CDLGpictureView::~CDLGpictureView()
{
}

void CDLGpictureView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC, m_pic);
	DDX_Control(pDX, IDC_BUTTON_DOWNLOAD_BMP, m_b_download);
}


BEGIN_MESSAGE_MAP(CDLGpictureView, CDialog)
	ON_BN_CLICKED(IDCANCEL, &CDLGpictureView::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CDLGpictureView::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_DOWNLOAD, &CDLGpictureView::OnBnClickedButtonDownload)

	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
END_MESSAGE_MAP()

BOOL CDLGpictureView::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetWindowText(Titlestr);

	m_b_download.LoadBitmaps(IDB_DOWNLOAD_BUTTON,IDB_DOWNLOAD_BUTTON_MOVE,NULL,IDB_DOWNLOAD_BUTTON_DIS);
	m_b_download.SizeToContent();		//����ӦͼƬ��С

	//����ͼƬ
	bim=pic.LoadPicture(srcfile.GetBuffer());


	//��ʼ����� //�����
	ShowWindow(SW_MAXIMIZE);   


	return TRUE;
}
// CDLGpictureView message handlers

void CDLGpictureView::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	//�ͷ�ͼƬ
	pic.FreePicture();
	OnCancel();
}

void CDLGpictureView::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
//	OnOK();
}
void CDLGpictureView::OnBnClickedButtonDownload()
{
	//�����ļ�
	char szFilter[]="Jpeg Files (*.jpg)|*.jpg|*.*|*.*||";
	CFileDialog dlg(FALSE,".jpg",Titlestr.GetBuffer(0),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		szFilter);
	if(dlg.DoModal()==IDOK)
	{
		CopyFile(srcfile,dlg.GetPathName().GetBuffer(0),FALSE);
	}
}

void CDLGpictureView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	//������ͼ	
	CRect    rect;     
	GetClientRect(&rect);     

	//����Դ������λͼ     
	CBitmap    bitmap;     
	bitmap.LoadBitmap(IDB_FIND_BACK);    
	BITMAP bmp;
	bitmap.GetBitmap(&bmp);

	CDC    memdc;     
	memdc.CreateCompatibleDC(&dc);     
	memdc.SelectObject(bitmap); 
	dc.SetStretchBltMode(COLORONCOLOR);
	dc.StretchBlt(0,0,rect.Width(),rect.Height(),&memdc,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
	memdc.DeleteDC();

	// TODO: Add your message handler code here
	//����ONINIT����Ч

	//DrawFileImage(&m_pic,"c:\\36273.jpg");

	if(bim)
	{
		//��ʾͼƬ
		CDC *pDC=m_pic.GetDC();
		CRect rect; 
		m_pic.GetClientRect(&rect);//���pictrue�ؼ����ڵľ�������
		pic.DrawPicture(*pDC,0,0,rect.Width(),rect.Height());
		m_pic.ReleaseDC(pDC);
	}


	CDialog::OnPaint();
}


void CDLGpictureView::DrawImage(CStatic *m_picBox,unsigned char *image,unsigned long int size)
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
			pPic->Render(*pDC,0,0,rect.Width(),rect.Height(),0,hmHeight,hmWidth,-hmHeight,NULL); 
			pPic->Release(); 
			pStream->Release();//�ͷ�������
		}  
	}

	m_picBox->ReleaseDC(pDC);

	if(hGlobal)
	{
		GlobalFree(hGlobal);
		hGlobal = NULL;
	}
}
void CDLGpictureView::DrawFileImage(CStatic *m_picBox, char *filename)
{
	CRect rect; 
	m_picBox->GetClientRect(&rect);//���pictrue�ؼ����ڵľ�������
	CDC *pDC=m_picBox->GetDC();//���pictrue�ؼ���DC 

	IPicture *pPic;//������ʾͼƬ�Ľӿڣ�����ʾjpg��ʽͼƬ��

	FILE *fp = fopen(filename, "rb");
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	fseek(fp ,0, SEEK_SET);

	HGLOBAL hGlobal=GlobalAlloc(GMEM_MOVEABLE,size);//�����ڴ�ռ�
	void *pData=GlobalLock(hGlobal);//����ͼ������ָ��

	fread(pData, sizeof(BYTE), size, fp);
	GlobalUnlock(hGlobal);//�ͷ��ڴ�ռ�

	fclose(fp);

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
			pPic->Render(*pDC,0,0,rect.Width(),rect.Height(),0,hmHeight,hmWidth,-hmHeight,NULL); 
			pPic->Release(); 
			pStream->Release();//�ͷ�������
		}  
	}

	m_picBox->ReleaseDC(pDC);

	if(hGlobal)
	{
		GlobalFree(hGlobal);
		hGlobal = NULL;
	}
}


//��̬�ı��ؼ� ͸��
HBRUSH CDLGpictureView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT); // ����͸������
		// TODO: Change any attributes of the DC here
		pDC->SetTextColor(RGB(0, 0, 0)); // �����ı���ɫ
		// TODO: Return a non-NULL brush if the parent's handler should not be called
		hbr=(HBRUSH)GetStockObject(HOLLOW_BRUSH); // ����͸����ˢ	
		// TODO: Return a different brush if the default is not desired
	}

	return hbr;
}
void CDLGpictureView::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	CRect		m_clientRect;		//�����������λ��
	GetClientRect(&m_clientRect);

	//��ӡ��־��
	int download_height=24;
	int distance=5;
	int  txt_width=80;

	//ͼƬ
	CRect pic_Rect;
	pic_Rect.top=m_clientRect.top;
	pic_Rect.bottom=m_clientRect.bottom-download_height-distance*2;

	pic_Rect.left = m_clientRect.left;
	pic_Rect.right = m_clientRect.right;
	GetDlgItem(IDC_PIC)->MoveWindow(pic_Rect);

	//DOWNLOAD
	CRect download_Rect;
	download_Rect.top=pic_Rect.bottom+distance;
	download_Rect.bottom=m_clientRect.bottom-distance;

	download_Rect.left = m_clientRect.right-txt_width-distance;
	download_Rect.right = m_clientRect.right-distance;
	GetDlgItem(IDC_BUTTON_DOWNLOAD_BMP)->MoveWindow(download_Rect);

	Invalidate();
}
