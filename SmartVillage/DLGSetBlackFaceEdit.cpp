// DLGSetBlackFaceEdit.cpp : implementation file
//

#include "stdafx.h"
#include "SmartVillage.h"
#include "DLGSetBlackFaceEdit.h"
#include "DLGWarnning.h"

extern CYRSVMySQL MySqlIO;

#include "DLGSetSystem.h"
extern CDLGSetSystem DlgSetSystem;

#include "SmartVillageDlg.h"
extern CSmartVillageDlg *DlgMain;

// CDLGSetBlackFaceEdit dialog

IMPLEMENT_DYNAMIC(CDLGSetBlackFaceEdit, CDialog)

CDLGSetBlackFaceEdit::CDLGSetBlackFaceEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CDLGSetBlackFaceEdit::IDD, pParent)
	, m_e_name(_T(""))
	, m_c_cardtype(0)
	, m_c_jiguan(0)
	, m_e_cardnum(_T(""))
	, m_e_phone(_T(""))
	, m_e_addr(_T(""))
	, m_c_sex(0)
	, bModifyFlag(false)
	, bFaceChange1(false)
	, bFaceChange2(false)
	, bFaceChange3(false)
	, bFaceChange4(false)
	, bFaceDelete1(false)
	, bFaceDelete2(false)
	, bFaceDelete3(false)
	, bFaceDelete4(false)
	, RegistFlag(true)
{
	CTime nowtime=CTime::GetTickCount();
	m_BirthDay=nowtime.GetTime();
	for(int i=0;i<MAX_PERSON_FACE;i++)
	{
		facepath[i][0] = 0;
		srcpath[i][0] = 0;
		filepath[i][0] = 0;
		filesize[i] = 0;

		faceID[i] = 0;
		RWfaceID[i] = 0;
	}

	bim1=NULL;
	//filepath1[0] = '0';
	bim2=NULL;
	//filepath2[0] = '0';
	bim3=NULL;
	//filepath3[0] = '0';
	bim4=NULL;
	//filepath4[0] = '0';
	db_id = 0;
	RWdb_id = 0;
	curFaceNum = 0;
	memset(&curBlackInfo,0,sizeof(PERSON_BLACK_ST));
}

CDLGSetBlackFaceEdit::~CDLGSetBlackFaceEdit()
{
}

void CDLGSetBlackFaceEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_b_ok);
	DDX_Control(pDX, IDCANCEL, m_b_cancel);
	DDX_Control(pDX, IDC_PIC1, m_pic1);
	DDX_Control(pDX, IDC_BUTTON_FILE1, m_b_file1);
	DDX_Control(pDX, IDC_PIC2, m_pic2);
	DDX_Control(pDX, IDC_BUTTON_FILE2, m_b_file2);
	DDX_Control(pDX, IDC_PIC3, m_pic3);
	DDX_Control(pDX, IDC_BUTTON_FILE3, m_b_file3);
	DDX_Control(pDX, IDC_PIC4, m_pic4);
	DDX_Control(pDX, IDC_BUTTON_FILE4, m_b_file4);

	DDX_Control(pDX, IDC_BUTTON_DELETE1, m_b_delete1);
	DDX_Control(pDX, IDC_BUTTON_DELETE2, m_b_delete2);
	DDX_Control(pDX, IDC_BUTTON_DELETE3, m_b_delete3);
	DDX_Control(pDX, IDC_BUTTON_DELETE4, m_b_delete4);

	DDX_Text(pDX, IDC_EDIT_NAME, m_e_name);
	DDV_MaxChars(pDX, m_e_cardnum, 32);
	DDX_CBIndex(pDX, IDC_COMBO_CARDTYPE, m_c_cardtype);
	DDX_CBIndex(pDX, IDC_COMBO_JIGUAN, m_c_jiguan);
	DDX_Text(pDX, IDC_EDIT_CARDNUM, m_e_cardnum);
	DDV_MaxChars(pDX, m_e_cardnum, 32);
	DDX_Text(pDX, IDC_EDIT_PHONE, m_e_phone);
	DDV_MaxChars(pDX, m_e_cardnum, 32);
	DDX_Text(pDX, IDC_EDIT_ADDR, m_e_addr);
	DDV_MaxChars(pDX, m_e_cardnum, 256);

	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_BIRTHDAY, m_BirthDay);
	DDX_CBIndex(pDX, IDC_COMBO_SEX, m_c_sex);
}


BEGIN_MESSAGE_MAP(CDLGSetBlackFaceEdit, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_FILE1, &CDLGSetBlackFaceEdit::OnBnClickedButtonFile1)
	ON_BN_CLICKED(IDC_BUTTON_FILE2, &CDLGSetBlackFaceEdit::OnBnClickedButtonFile2)
	ON_BN_CLICKED(IDC_BUTTON_FILE3, &CDLGSetBlackFaceEdit::OnBnClickedButtonFile3)
	ON_BN_CLICKED(IDC_BUTTON_FILE4, &CDLGSetBlackFaceEdit::OnBnClickedButtonFile4)
	ON_BN_CLICKED(IDC_BUTTON_DELETE1, &CDLGSetBlackFaceEdit::OnBnClickedButtonDelete1)
	ON_BN_CLICKED(IDC_BUTTON_DELETE2, &CDLGSetBlackFaceEdit::OnBnClickedButtonDelete2)
	ON_BN_CLICKED(IDC_BUTTON_DELETE3, &CDLGSetBlackFaceEdit::OnBnClickedButtonDelete3)
	ON_BN_CLICKED(IDC_BUTTON_DELETE4, &CDLGSetBlackFaceEdit::OnBnClickedButtonDelete4)
END_MESSAGE_MAP()

BOOL CDLGSetBlackFaceEdit::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_b_file1.LoadBitmaps(IDB_VIEW_BUTTON,IDB_VIEW_BUTTON_MOVE,NULL,NULL);
	m_b_file1.SizeToContent();		//����ӦͼƬ��С
	m_b_file2.LoadBitmaps(IDB_VIEW_BUTTON,IDB_VIEW_BUTTON_MOVE,NULL,NULL);
	m_b_file2.SizeToContent();		//����ӦͼƬ��С
	m_b_file3.LoadBitmaps(IDB_VIEW_BUTTON,IDB_VIEW_BUTTON_MOVE,NULL,NULL);
	m_b_file3.SizeToContent();		//����ӦͼƬ��С
	m_b_file4.LoadBitmaps(IDB_VIEW_BUTTON,IDB_VIEW_BUTTON_MOVE,NULL,NULL);
	m_b_file4.SizeToContent();		//����ӦͼƬ��С


	m_b_delete1.LoadBitmaps(IDB_DEL_BUTTON,IDB_DEL_BUTTON_MOVE,NULL,IDB_DEL_BUTTON_DIS);
	m_b_delete1.SizeToContent();		//����ӦͼƬ��С
	m_b_delete2.LoadBitmaps(IDB_DEL_BUTTON,IDB_DEL_BUTTON_MOVE,NULL,IDB_DEL_BUTTON_DIS);
	m_b_delete2.SizeToContent();		//����ӦͼƬ��С
	m_b_delete3.LoadBitmaps(IDB_DEL_BUTTON,IDB_DEL_BUTTON_MOVE,NULL,IDB_DEL_BUTTON_DIS);
	m_b_delete3.SizeToContent();		//����ӦͼƬ��С
	m_b_delete4.LoadBitmaps(IDB_DEL_BUTTON,IDB_DEL_BUTTON_MOVE,NULL,IDB_DEL_BUTTON_DIS);
	m_b_delete4.SizeToContent();		//����ӦͼƬ��С

	m_b_ok.LoadBitmaps(IDB_OK_BUTTON,IDB_OK_BUTTON_MOVE,NULL,NULL);
	m_b_ok.SizeToContent();		//����ӦͼƬ��С

	m_b_cancel.LoadBitmaps(IDB_CANCEL_BUTTON,IDB_CANCEL_BUTTON_MOVE,NULL,NULL);
	m_b_cancel.SizeToContent();		//����ӦͼƬ��С

	GetDlgItem(IDC_BUTTON_DELETE1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_DELETE2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_DELETE3)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_DELETE4)->EnableWindow(FALSE);


	if(bModifyFlag)
	{
		EditModeInit();
		//����ͼƬ
		if(filepath[0][0] != 0)
		{
			bim1=pic1.LoadPicture(filepath[0]);
			GetDlgItem(IDC_BUTTON_DELETE1)->EnableWindow(TRUE);
		}
		if(filepath[1][0] != 0)
		{
			bim2=pic2.LoadPicture(filepath[1]);
			GetDlgItem(IDC_BUTTON_DELETE2)->EnableWindow(TRUE);
		}
		if(filepath[2][0] != 0)
		{
			bim3=pic3.LoadPicture(filepath[2]);
			GetDlgItem(IDC_BUTTON_DELETE3)->EnableWindow(TRUE);
		}
		if(filepath[3][0] != 0)
		{
			bim4=pic4.LoadPicture(filepath[3]);
			GetDlgItem(IDC_BUTTON_DELETE4)->EnableWindow(TRUE);
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
void CDLGSetBlackFaceEdit::OnOK()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(!bModifyFlag)
	{
		AddNerPerson();
	}
	else
	{
		EditPersonInfo();
	}
	CDialog::OnOK();
}
void CDLGSetBlackFaceEdit::OnCancel() 
{
	CDialog::OnCancel();
}
void CDLGSetBlackFaceEdit::PicAutoWH(int rectw,int recth,int picw,int pich,int *dstw,int *dsth)
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
// CDLGSetBlackFaceEdit message handlers
void CDLGSetBlackFaceEdit::OnPaint()
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

	int w,h;


	if(bim1)
	{
		//��ʾͼƬ
		CDC *pDC=m_pic1.GetDC();
	
		m_pic1.GetClientRect(&rect);//���pictrue�ؼ����ڵľ�������

		PicAutoWH(rect.Width(),rect.Height(),pic1._GetWidth(),pic1._GetHeight(),&w,&h);

		pic1.DrawPicture(*pDC, (rect.Width()-w)/2,(rect.Height()-h)/2,w,h);
		m_pic1.ReleaseDC(pDC);
	}

	if(bim2)
	{
		//��ʾͼƬ
		CDC *pDC=m_pic2.GetDC();

		m_pic2.GetClientRect(&rect);//���pictrue�ؼ����ڵľ�������

		PicAutoWH(rect.Width(),rect.Height(),pic2._GetWidth(),pic2._GetHeight(),&w,&h);

		pic2.DrawPicture(*pDC, (rect.Width()-w)/2,(rect.Height()-h)/2,w,h);
		m_pic2.ReleaseDC(pDC);
	}

	if(bim3)
	{
		//��ʾͼƬ
		CDC *pDC=m_pic3.GetDC();

		m_pic3.GetClientRect(&rect);//���pictrue�ؼ����ڵľ�������

		PicAutoWH(rect.Width(),rect.Height(),pic3._GetWidth(),pic3._GetHeight(),&w,&h);

		pic3.DrawPicture(*pDC, (rect.Width()-w)/2,(rect.Height()-h)/2,w,h);
		m_pic3.ReleaseDC(pDC);
	}

	if(bim4)
	{
		//��ʾͼƬ
		CDC *pDC=m_pic4.GetDC();

		m_pic4.GetClientRect(&rect);//���pictrue�ؼ����ڵľ�������

		PicAutoWH(rect.Width(),rect.Height(),pic4._GetWidth(),pic4._GetHeight(),&w,&h);

		pic4.DrawPicture(*pDC, (rect.Width()-w)/2,(rect.Height()-h)/2,w,h);
		m_pic4.ReleaseDC(pDC);
	}



	CDialog::OnPaint();

}
//��̬�ı��ؼ� ͸��
HBRUSH CDLGSetBlackFaceEdit::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
void CDLGSetBlackFaceEdit::OnBnClickedButtonFile1()
{
	// TODO: Add your control notification handler code here
		// TODO: Add your control notification handler code here
	char szFilter[]="jpg Files (*.jpg)|*.jpg|bmp Files (*.bmp)|*.bmp||";
	CFileDialog dlg(TRUE,"jpg","",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		szFilter);
	if(dlg.DoModal()==IDOK)
	{
		bFaceChange1 = true;
		//�ļ�·��
		strcpy(filepath[0],dlg.GetPathName().GetBuffer());
		UpdateData(TRUE);
	
		//����ͼƬ
		bim1=pic1.LoadPicture(filepath[0]);
		GetDlgItem(IDC_BUTTON_DELETE1)->EnableWindow(TRUE);
		Invalidate();


/*
		//����Դ������λͼ     
		CBitmap    bitmapq;     
		bitmapq.Attach(bim1);    
		BITMAP bmp;
		bitmapq.GetBitmap(&bmp);
	bitmapq.Detach();
	*/
	}
}

void CDLGSetBlackFaceEdit::OnBnClickedButtonFile2()
{
	// TODO: Add your control notification handler code here
	char szFilter[]="jpg Files (*.jpg)|*.jpg|bmp Files (*.bmp)|*.bmp||";
	CFileDialog dlg(TRUE,"jpg","",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		szFilter);
	if(dlg.DoModal()==IDOK)
	{
		bFaceChange2 = true;
		//�ļ�·��
		strcpy(filepath[1],dlg.GetPathName().GetBuffer());
		UpdateData(TRUE);
	
		//����ͼƬ
		bim2=pic2.LoadPicture(filepath[1]);
		GetDlgItem(IDC_BUTTON_DELETE2)->EnableWindow(TRUE);
		Invalidate();

	

/*
		//����Դ������λͼ     
		CBitmap    bitmapq;     
		bitmapq.Attach(bim2);    
		BITMAP bmp;
		bitmapq.GetBitmap(&bmp);
	bitmapq.Detach();
	*/
	}
}

void CDLGSetBlackFaceEdit::OnBnClickedButtonFile3()
{
	// TODO: Add your control notification handler code here
	char szFilter[]="jpg Files (*.jpg)|*.jpg|bmp Files (*.bmp)|*.bmp||";
	CFileDialog dlg(TRUE,"jpg","",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		szFilter);
	if(dlg.DoModal()==IDOK)
	{
		bFaceChange3 = true;
		//�ļ�·��
		strcpy(filepath[2],dlg.GetPathName().GetBuffer());
		UpdateData(TRUE);
	
		//����ͼƬ
		bim3=pic3.LoadPicture(filepath[2]);
		GetDlgItem(IDC_BUTTON_DELETE3)->EnableWindow(TRUE);
		Invalidate();



/*
		//����Դ������λͼ     
		CBitmap    bitmapq;     
		bitmapq.Attach(bim3);    
		BITMAP bmp;
		bitmapq.GetBitmap(&bmp);
	bitmapq.Detach();
	*/
	}
}

void CDLGSetBlackFaceEdit::OnBnClickedButtonFile4()
{
	// TODO: Add your control notification handler code here
		char szFilter[]="jpg Files (*.jpg)|*.jpg|bmp Files (*.bmp)|*.bmp||";
	CFileDialog dlg(TRUE,"jpg","",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		szFilter);
	if(dlg.DoModal()==IDOK)
	{
		bFaceChange4 = true;
		//�ļ�·��
		strcpy(filepath[3],dlg.GetPathName().GetBuffer());
		UpdateData(TRUE);
	
		//����ͼƬ
		bim4=pic4.LoadPicture(filepath[3]);
		GetDlgItem(IDC_BUTTON_DELETE4)->EnableWindow(TRUE);
		Invalidate();



/*
		//����Դ������λͼ     
		CBitmap    bitmapq;     
		bitmapq.Attach(bim4);    
		BITMAP bmp;
		bitmapq.GetBitmap(&bmp);
	bitmapq.Detach();
	*/
	}
}

void CDLGSetBlackFaceEdit::OnBnClickedButtonDelete1()
{
	// TODO: Add your control notification handler code here
	if(filepath[0][0] == 0)
	{
		return;
	}

	//�����
	CDLGWarnning dlgw;
	dlgw.m_wintxt="ɾ������";					//���ڱ���
	dlgw.m_warntxt="���ٴ�ȷ���Ƿ�ɾ��";	//��������
	int nResponse=dlgw.DoModal();
	if (nResponse == IDOK)
	{
		if(faceID[0] != 0)
		{
#if OPEN_FACEDETECT_CODE 
			DlgMain->FaceMng.RWFaceMngFaceDeleteWithID(RWfaceID[0]);
			MySqlIO.FACE_BlackFace_DeleteWithNid(faceID[0]);
#endif
			//ɾ�������ļ�
			char cmd[1024]={0};
			sprintf(cmd,"cmd /c rm /s /q \"%s\"",srcpath[0]);
			WinExec(cmd,SW_HIDE);

			sprintf(cmd,"cmd /c rm /s /q \"%s\"",filepath[0]);
			WinExec(cmd,SW_HIDE);

			faceID[0] = 0;
			curFaceNum--;
		}

		memset(filepath[0],0,MAX_PATH);
		//����ͼƬ
		pic1.FreePicture();
		bim1=NULL;
		m_pic1.SetBitmap(0);
		GetDlgItem(IDC_BUTTON_DELETE1)->EnableWindow(FALSE);
		UpdateData(FALSE);
		Invalidate(TRUE);
	}
	bFaceChange1 = false;
}

void CDLGSetBlackFaceEdit::OnBnClickedButtonDelete2()
{
	// TODO: Add your control notification handler code here
	if(filepath[1][0] == 0)
	{
		return;
	}

	//�����
	CDLGWarnning dlgw;
	dlgw.m_wintxt="ɾ������";					//���ڱ���
	dlgw.m_warntxt="���ٴ�ȷ���Ƿ�ɾ��";	//��������
	int nResponse=dlgw.DoModal();
	if (nResponse == IDOK)
	{
		if(faceID[1] != 0)
		{
			#if OPEN_FACEDETECT_CODE 
			DlgMain->FaceMng.RWFaceMngFaceDeleteWithID(RWfaceID[1]);
			MySqlIO.FACE_BlackFace_DeleteWithNid(faceID[1]);
#endif
			//ɾ�������ļ�
			char cmd[1024]={0};
			sprintf(cmd,"cmd /c rm /s /q \"%s\"",srcpath[1]);
			WinExec(cmd,SW_HIDE);

			sprintf(cmd,"cmd /c rm /s /q \"%s\"",filepath[1]);
			WinExec(cmd,SW_HIDE);

			faceID[1] = 0;
			curFaceNum--;
		}

		memset(filepath[1],0,MAX_PATH);
		//����ͼƬ
		pic2.FreePicture();
		bim2=NULL;
		m_pic2.SetBitmap(0);
		GetDlgItem(IDC_BUTTON_DELETE2)->EnableWindow(FALSE);
		UpdateData(FALSE);
		Invalidate(TRUE);
	}
	bFaceChange2 = false;
}

void CDLGSetBlackFaceEdit::OnBnClickedButtonDelete3()
{
	// TODO: Add your control notification handler code here
	if(filepath[2][0] == 0)
	{
		return;
	}
	//�����
	CDLGWarnning dlgw;
	dlgw.m_wintxt="ɾ������";					//���ڱ���
	dlgw.m_warntxt="���ٴ�ȷ���Ƿ�ɾ��";	//��������
	int nResponse=dlgw.DoModal();
	if (nResponse == IDOK)
	{
		if(faceID[2] != 0)
		{
			#if OPEN_FACEDETECT_CODE 
			DlgMain->FaceMng.RWFaceMngFaceDeleteWithID(RWfaceID[2]);
			MySqlIO.FACE_BlackFace_DeleteWithNid(faceID[2]);
#endif
			//ɾ�������ļ�
			char cmd[1024]={0};
			sprintf(cmd,"cmd /c rm /s /q \"%s\"",srcpath[2]);
			WinExec(cmd,SW_HIDE);

			sprintf(cmd,"cmd /c rm /s /q \"%s\"",filepath[2]);
			WinExec(cmd,SW_HIDE);

			faceID[2] = 0;
			curFaceNum--;
		}

		memset(filepath[2],0,MAX_PATH);
		//����ͼƬ
		pic3.FreePicture();
		bim3=NULL;
		m_pic3.SetBitmap(0);
		GetDlgItem(IDC_BUTTON_DELETE3)->EnableWindow(FALSE);
		UpdateData(FALSE);
		Invalidate(TRUE);
	}
	bFaceChange3 = false;
}

void CDLGSetBlackFaceEdit::OnBnClickedButtonDelete4()
{
	// TODO: Add your control notification handler code here
	if(filepath[3][0] == 0)
	{
		return;
	}
	//�����
	CDLGWarnning dlgw;
	dlgw.m_wintxt="ɾ������";					//���ڱ���
	dlgw.m_warntxt="���ٴ�ȷ���Ƿ�ɾ��";	//��������
	int nResponse=dlgw.DoModal();
	if (nResponse == IDOK)
	{
		if(faceID[3] != 0)
		{
#if OPEN_FACEDETECT_CODE 
			DlgMain->FaceMng.RWFaceMngFaceDeleteWithID(RWfaceID[3]);
			MySqlIO.FACE_BlackFace_DeleteWithNid(faceID[3]);
#endif
			//ɾ�������ļ�
			char cmd[1024]={0};
			sprintf(cmd,"cmd /c rm /s /q \"%s\"",srcpath[3]);
			WinExec(cmd,SW_HIDE);

			sprintf(cmd,"cmd /c rm /s /q \"%s\"",filepath[3]);
			WinExec(cmd,SW_HIDE);

			faceID[3] = 0;
			curFaceNum--;
		}

		memset(filepath[3],0,MAX_PATH);
		//����ͼƬ
		pic4.FreePicture();
		bim4=NULL;
		m_pic4.SetBitmap(0);
		GetDlgItem(IDC_BUTTON_DELETE4)->EnableWindow(FALSE);
		UpdateData(FALSE);
		Invalidate(TRUE);
	}
	bFaceChange4 = false;
}

void CDLGSetBlackFaceEdit::AddNerPerson(void)
{
	struct PERSON_BLACK_ST black = {0};
	strcpy(black.address,m_e_addr.GetBuffer());
	strcpy(black.cardNO,m_e_cardnum.GetBuffer());
	black.cardtype = m_c_cardtype;
	black.day = m_BirthDay.GetDay();
	black.mon = m_BirthDay.GetMonth();
	black.year = m_BirthDay.GetYear();
	black.db_nid = db_id;
	strcpy(black.name,m_e_name.GetBuffer());
	black.native = m_c_jiguan;
	strcpy(black.phone,m_e_phone.GetBuffer());
	black.RW_dbID = RWdb_id;
	black.sex = m_c_sex;

#if OPEN_FACEDETECT_CODE
	char STR_SEX[3][32] = {"��","��","Ů"};
	char STR_CARD_TYPE[8][32] = {"δ֪","һ��֤","����֤","ʿ��֤","ѧ��֤","��ʻ֤","����","����"};
	char STR_NATIVE[32][32] = {"����","����","���","����","�㶫","�ӱ�","ɽ��","����","����","������",\
		"����","�㽭","����","����","����","ɽ��","����","����","����","����",\
		"�Ĵ�","����","����","����","����","�ຣ","̨��","�½�","����","����",\
		"���ɹ�","����"};

	RecoPersonInfo pInfo;
	strcpy(pInfo.address,black.address);
	CTime nowtime=CTime::GetTickCount();
	pInfo.birthday = nowtime.GetYear() - black.year;
	strcpy(pInfo.card_no,black.cardNO);
	pInfo.card_type = black.cardtype;
	pInfo.db_id = RWdb_id;

	strcpy(pInfo.gender,STR_SEX[black.sex]);
	strcpy(pInfo.name,black.name);
	strcpy(pInfo.native_place,STR_NATIVE[black.native]);
	strcpy(pInfo.phone,black.phone);
	pInfo.reserve1[0] = 0;

	if(!DlgMain->FaceMng.RWFaceMngPersonAddNew(black.RW_personID,pInfo))//��Ϊ
	{
		//ע�ᵽ��Ϊ���ؿ�ʧ��
		AfxMessageBox("��Ӳ�����Աʧ��");
		return;
	}

	long personID;
	MySqlIO.FACE_BlackPerson_AddNew(personID,black);
	char dir[260]={0};
	sprintf(dir,"%s\\%d\\%d",DlgSetSystem.m_path_faceblack,black.db_nid,personID);
	CreateDirectory(dir, NULL);
	black.nid = personID;

	if(bim1 != NULL)
	{
		RegistFace(bim1,filepath[0],black);
	}
	if(bim2 != NULL)
	{
		RegistFace(bim2,filepath[1],black);
	}
	if(bim3 != NULL)
	{
		RegistFace(bim3,filepath[2],black);
	}
	if(bim4 != NULL)
	{
		RegistFace(bim4,filepath[3],black);
	}

	if(!RegistFlag)
	{
		AfxMessageBox("��ͼƬδ�ܼ�⵽��������ע������ʶ�����ʵ������޸ģ�����");
	}
#else
	long personID;
	MySqlIO.FACE_BlackPerson_AddNew(personID,black);
#endif
}

void CDLGSetBlackFaceEdit::EditModeInit(void)
{
	MySqlIO.FACE_BlackPerson_ReadOne(person_id,curBlackInfo);
	
	m_e_addr = curBlackInfo.address;
	m_e_cardnum = curBlackInfo.cardNO;
	m_c_cardtype = curBlackInfo.cardtype;
	COleDateTime temp( curBlackInfo.year, curBlackInfo.mon, curBlackInfo.day, 0, 0, 0 );
	m_BirthDay = temp;

	m_e_name = curBlackInfo.name;
	m_c_jiguan = curBlackInfo.native;
	m_e_phone = curBlackInfo.phone;
	m_c_sex = curBlackInfo.sex;

	list<struct FACE_BLACK_ST> list_face;
	list_face.clear();
	MySqlIO.FACE_BlackFace_Read(person_id,list_face);

	list<struct FACE_BLACK_ST>::iterator beglist;
	int count=0;
	for(beglist=list_face.begin();beglist!=list_face.end();beglist++)
	{
		strcpy(srcpath[count],beglist->file);
		strcpy(facepath[count],beglist->face);
		strcpy(filepath[count],beglist->face);
		RWfaceID[count] = beglist->RW_faceID;
		faceID[count] = beglist->nid;
		count++;
	}
	curFaceNum = count;
	UpdateData(FALSE);
}

void CDLGSetBlackFaceEdit::EditPersonInfo(void)
{
	struct PERSON_BLACK_ST black = {0};
	memcpy(&black,&curBlackInfo,sizeof(PERSON_BLACK_ST));
	strcpy(black.address,m_e_addr.GetBuffer());
	strcpy(black.cardNO,m_e_cardnum.GetBuffer());
	black.cardtype = m_c_cardtype;
	black.day = m_BirthDay.GetDay();
	black.mon = m_BirthDay.GetMonth();
	black.year = m_BirthDay.GetYear();
	strcpy(black.name,m_e_name.GetBuffer());
	black.native = m_c_jiguan;
	strcpy(black.phone,m_e_phone.GetBuffer());
	black.sex = m_c_sex;

#if OPEN_FACEDETECT_CODE
	char STR_SEX[3][32] = {"��","��","Ů"};
	char STR_CARD_TYPE[8][32] = {"δ֪","һ��֤","����֤","ʿ��֤","ѧ��֤","��ʻ֤","����","����"};
	char STR_NATIVE[32][32] = {"����","����","���","����","�㶫","�ӱ�","ɽ��","����","����","������",\
		"����","�㽭","����","����","����","ɽ��","����","����","����","����",\
		"�Ĵ�","����","����","����","����","�ຣ","̨��","�½�","����","����",\
		"���ɹ�","����"};

	RecoPersonInfo pInfo;
	strcpy(pInfo.address,black.address);
	CTime nowtime=CTime::GetTickCount();
	pInfo.birthday = nowtime.GetYear() - black.year;
	strcpy(pInfo.card_no,black.cardNO);
	pInfo.card_type = black.cardtype;

	pInfo.db_id = black.RW_dbID;

	strcpy(pInfo.gender,STR_SEX[black.sex]);
	strcpy(pInfo.name,black.name);
	strcpy(pInfo.native_place,STR_NATIVE[black.native]);
	strcpy(pInfo.phone,black.phone);
	pInfo.reserve1[0] = 0;
	//m_List_person.GetItemText(ListPersonChoose,9,str,260);
	pInfo.person_id = black.RW_personID;

	if(!DlgMain->FaceMng.RWFaceMngPersonUpdate(pInfo))//��Ϊ
	{
		AfxMessageBox("�޸Ĳ�����Ա��Ϣʧ��");
		return;
	}

	char dir[260]={0};
	sprintf(dir,"%s\\%d\\%d",DlgSetSystem.m_path_faceblack,black.db_nid,black.nid);
	CreateDirectory(dir, NULL);

	if(bFaceChange1)
	{
		if(faceID[0] != 0)
		{
			ModifyFace(bim1,filepath[0],black,0);
		}
		else
		{
			//֮ǰδע������������������
			RegistFace(bim1,filepath[0],black);
		}
	}
	if(bFaceChange2)
	{
		if(faceID[1] != 0)
		{
			ModifyFace(bim2,filepath[1],black,1);
		}
		else
		{
			//֮ǰδע������������������
			RegistFace(bim2,filepath[1],black);
		}
	}
	if(bFaceChange3)
	{
		if(faceID[2] != 0)
		{
			ModifyFace(bim3,filepath[2],black,2);
		}
		else
		{
			//֮ǰδע������������������
			RegistFace(bim3,filepath[2],black);
		}
	}
	if(bFaceChange4)
	{
		if(faceID[3] != 0)
		{
			ModifyFace(bim4,filepath[3],black,3);
		}
		else
		{
			//֮ǰδע������������������
			RegistFace(bim4,filepath[3],black);
		}
	}
	if(!RegistFlag)
	{
		RegistFlag  = true;
		AfxMessageBox("��ͼƬδ�ܼ�⵽��������ע������ʶ�����ʵ������޸ģ�����");
	}

#endif

	MySqlIO.FACE_BlackPerson_Edit(black);
}

bool CDLGSetBlackFaceEdit::RegistFace(HBITMAP pic,char *path,struct PERSON_BLACK_ST black)
{
#if OPEN_FACEDETECT_CODE
	long faceID=0;
	curFaceNum++;

	bool ret = DlgMain->FaceMng.RWFaceMngFaceAddNew(faceID,black.RW_personID,pic);
	if(ret)
	{
		char facepath[260]={0};
		char filepath[260]={0};
		char strtime[32]={0};
		long facesize=0;

		CTime nowtime=CTime::GetTickCount();
		sprintf(strtime,"%04d%02d%02d %02d%02d%02d",nowtime.GetYear(),nowtime.GetMonth(),nowtime.GetDay(),
													nowtime.GetHour(),nowtime.GetMinute(),nowtime.GetSecond());
		sprintf(facepath,"%s\\%d\\%d\\face%d_%s.jpg",DlgSetSystem.m_path_faceblack,black.db_nid,black.nid,curFaceNum,strtime);
		sprintf(filepath,"%s\\%d\\%d\\pic%d_%s.jpg",DlgSetSystem.m_path_faceblack,black.db_nid,black.nid,curFaceNum,strtime);

		if(DlgMain->FaceMng.RWFaceMngGetFaceImage(faceID,facesize,facepath))
		{
			struct FACE_BLACK_ST face = {0};
			strcpy(face.face,facepath);
			face.facesize = facesize;
			face.person_black_nid = black.nid;
			face.RW_faceID = faceID;
			face.RW_personID = black.RW_personID;

			CopyFile(path,filepath,FALSE);
			strcpy(face.file,filepath);

			MySqlIO.FACE_BlackFace_AddNew(face);

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if(RegistFlag)
			RegistFlag = false;
		return false;
	}
#endif
	return false;
}

void CDLGSetBlackFaceEdit::ModifyFace(HBITMAP pic,char *path,struct PERSON_BLACK_ST black,int num)
{
#if OPEN_FACEDETECT_CODE
	long id;
	bool ret = DlgMain->FaceMng.RWFaceMngFaceAddNew(id,black.RW_personID,pic);
	if(ret)
	{
		long facesize=0;

		DlgMain->FaceMng.RWFaceMngFaceDeleteWithID(RWfaceID[num]);//������ע��ɹ���ɾ��������
		RWfaceID[num] = id;

		if(DlgMain->FaceMng.RWFaceMngGetFaceImage(id,facesize,facepath[num]))
		{
			struct FACE_BLACK_ST face = {0};

			strcpy(face.face,facepath[num]);
			CopyFile(path,srcpath[num],FALSE);
			strcpy(face.file,srcpath[num]);

			face.facesize = facesize;
			face.person_black_nid = black.nid;
			face.RW_faceID = RWfaceID[num];
			face.RW_personID = black.RW_personID;

			face.nid = faceID[num];
			MySqlIO.FACE_BlackFace_Update(face);
		}
	}
	else
	{
		if(RegistFlag)
			RegistFlag = false;
	}
#endif
}
