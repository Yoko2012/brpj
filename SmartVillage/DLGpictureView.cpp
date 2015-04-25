// DLGpictureView.cpp : implementation file
//

#include "stdafx.h"
#include "SmartVillage.h"
#include "DLGpictureView.h"

// CDLGpictureView dialog

IMPLEMENT_DYNAMIC(CDLGpictureView, CDialog)

CDLGpictureView::CDLGpictureView(CWnd* pParent /*=NULL*/)
	: CDialog(CDLGpictureView::IDD, pParent)
	, m_txt(_T(""))
{
	bim=NULL;
	bimsmall=NULL;
}

CDLGpictureView::~CDLGpictureView()
{
}

void CDLGpictureView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC, m_pic);
	DDX_Control(pDX, IDC_BUTTON_DOWNLOAD_BMP, m_b_download);
	DDX_Control(pDX, IDC_BUTTON_DOWNLOAD_SMALL, m_b_download_small);
	DDX_Control(pDX, IDC_PIC_SMALL, m_pic_small);
	DDX_Text(pDX, IDC_STATIC_TXT, m_txt);
}


BEGIN_MESSAGE_MAP(CDLGpictureView, CDialog)
	ON_BN_CLICKED(IDCANCEL, &CDLGpictureView::OnCancel)
	ON_BN_CLICKED(IDOK, &CDLGpictureView::OnOk)
	ON_BN_CLICKED(IDC_BUTTON_DOWNLOAD, &CDLGpictureView::OnBnClickedButtonDownload)

	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()

	ON_BN_CLICKED(IDC_BUTTON_DOWNLOAD_SMALL, &CDLGpictureView::OnBnClickedButtonDownloadSmall)
END_MESSAGE_MAP()

BOOL CDLGpictureView::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetWindowText(Titlestr);

	m_b_download.LoadBitmaps(IDB_DOWNLOAD_BUTTON,IDB_DOWNLOAD_BUTTON_MOVE,NULL,IDB_DOWNLOAD_BUTTON_DIS);
	m_b_download.SizeToContent();		//����ӦͼƬ��С

	m_b_download_small.LoadBitmaps(IDB_DOWNLOAD_SMALL_BUTTON,IDB_DOWNLOAD_SMALL_BUTTON_MOVE,NULL,IDB_DOWNLOAD_SMALL_BUTTON_DIS);
	m_b_download_small.SizeToContent();		//����ӦͼƬ��С

	//����ͼƬ
	bim=pic.LoadPicture(srcfile.GetBuffer());
	bimsmall=picsmall.LoadPicture(srcsmallfile.GetBuffer());


	//��ʼ����� //�����
	ShowWindow(SW_MAXIMIZE);   


	return TRUE;
}
// CDLGpictureView message handlers

void CDLGpictureView::OnCancel()
{
	// TODO: Add your control notification handler code here
	//�ͷ�ͼƬ
	pic.FreePicture();
	picsmall.FreePicture();
	bim=NULL;
	bimsmall=NULL;

	CDialog::OnCancel();
}

void CDLGpictureView::OnOk()
{
	// TODO: Add your control notification handler code here
//		CDialog::OnOK();
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


void CDLGpictureView::OnBnClickedButtonDownloadSmall()
{
	// TODO: Add your control notification handler code here
	//�����ļ�
	char szFilter[]="Jpeg Files (*.jpg)|*.jpg|*.*|*.*||";
	CFileDialog dlg(FALSE,".jpg",Titlestr.GetBuffer(0),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		szFilter);
	if(dlg.DoModal()==IDOK)
	{
		CopyFile(srcsmallfile,dlg.GetPathName().GetBuffer(0),FALSE);
	}
}

void CDLGpictureView::PicAutoWH(int rectw,int recth,int picw,int pich,int *dstw,int *dsth)
{
	int w,h;
if( 0== rectw || 0== recth || 0==picw || 0==pich)
	{
		(*dstw)=100;
		(*dsth)=100;
		return ;
	}
	if(picw> rectw)
	{
		w=rectw;
		h= pich*((float)rectw/(float)picw);

		if(h> recth)
		{
			w=w*((float)recth/(float)h);
			h= recth;
		}

	}
	else
	{
		if(pich> recth)
		{

			w=picw*((float)recth/(float)pich);
			h= recth;
		}
		else
		{
			w=picw;
			h=pich;
		}
	}
	(*dstw)=w;
	(*dsth)=h;
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

	int w,h;

	if(bim)
	{
		//��ʾͼƬ
		CDC *pDC=m_pic.GetDC();
		CRect rect; 
		m_pic.GetClientRect(&rect);//���pictrue�ؼ����ڵľ�������


		PicAutoWH(rect.Width(),rect.Height(),pic._GetWidth(),pic._GetHeight(),&w,&h);

		pic.DrawPicture(*pDC, (rect.Width()-w)/2,(rect.Height()-h)/2,w,h);
		m_pic.ReleaseDC(pDC);

	}

	if(bimsmall)
	{
		//��ʾͼƬ
		CDC *pDCsmall=m_pic_small.GetDC();
		CRect rectsmall; 
		m_pic_small.GetClientRect(&rectsmall);//���pictrue�ؼ����ڵľ�������

		PicAutoWH(rectsmall.Width(),rectsmall.Height(),picsmall._GetWidth(),picsmall._GetHeight(),&w,&h);

		picsmall.DrawPicture(*pDCsmall,(rectsmall.Width()-w)/2,(rectsmall.Height()-h)/2,w,h);
		m_pic_small.ReleaseDC(pDCsmall);
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

	int distance=5;
	int bmp_width=200;

	int button_width=80;
	int button_height=30;

	m_clientRect.top+=distance+button_height;
	m_clientRect.bottom-=distance;
	m_clientRect.left+=distance;
	m_clientRect.right-=distance;

	//ͼƬ
	CRect pic_Rect;
	pic_Rect.top=m_clientRect.top;
	pic_Rect.bottom=m_clientRect.bottom;

	pic_Rect.left = m_clientRect.left;
	pic_Rect.right = m_clientRect.right-bmp_width-distance;
	GetDlgItem(IDC_PIC)->MoveWindow(pic_Rect);


	//СͼƬ
	CRect pic_small_Rect;
	pic_small_Rect.top=m_clientRect.top;
	pic_small_Rect.bottom=m_clientRect.top+bmp_width;

	pic_small_Rect.left = m_clientRect.right-bmp_width;
	pic_small_Rect.right = m_clientRect.right;
	GetDlgItem(IDC_PIC_SMALL)->MoveWindow(pic_small_Rect);

	//������Ϣ����
	CRect title_Rect;
	title_Rect.top=m_clientRect.top-button_height+distance;
	title_Rect.bottom=m_clientRect.top;

	title_Rect.left = 	pic_small_Rect.left ;
	title_Rect.right = m_clientRect.right;
	GetDlgItem(IDC_STATIC_TITLE)->MoveWindow(title_Rect);


	//DOWNLOAD
	CRect download_Rect;
	download_Rect.top=m_clientRect.bottom-button_height;
	download_Rect.bottom=m_clientRect.bottom;

	download_Rect.left =pic_small_Rect.left;
	download_Rect.right = pic_small_Rect.left+button_width;
	GetDlgItem(IDC_BUTTON_DOWNLOAD_BMP)->MoveWindow(download_Rect);

	//DOWNLOAD
	CRect download_small_Rect;
	download_small_Rect.top=m_clientRect.bottom-button_height;
	download_small_Rect.bottom=m_clientRect.bottom;

	download_small_Rect.left = m_clientRect.right-button_width-distance;
	download_small_Rect.right = m_clientRect.right;
	GetDlgItem(IDC_BUTTON_DOWNLOAD_SMALL)->MoveWindow(download_small_Rect);


	//TXT	
	CRect txt_Rect;
	txt_Rect.top=pic_small_Rect.bottom+distance;
	txt_Rect.bottom=download_small_Rect.top;

	txt_Rect.left = pic_small_Rect.left ;
	txt_Rect.right = m_clientRect.right;
	GetDlgItem(IDC_STATIC_TXT)->MoveWindow(txt_Rect);


	Invalidate();
}
