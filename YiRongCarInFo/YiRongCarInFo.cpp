// YiRongCarInFo.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "YiRongCarInFo.h"
#include "YiRongCarInFoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CYiRongCarInFoApp

BEGIN_MESSAGE_MAP(CYiRongCarInFoApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CYiRongCarInFoApp ����

CYiRongCarInFoApp::CYiRongCarInFoApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CYiRongCarInFoApp ����

CYiRongCarInFoApp theApp;


// CYiRongCarInFoApp ��ʼ��

BOOL CYiRongCarInFoApp::InitInstance()
{
	//ZOGNA//DOWN
AfxOleInit();
CoInitialize(NULL);
//ZOGNA//UP

	CWinApp::InitInstance();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CYiRongCarInFoDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
