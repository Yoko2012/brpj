// YiRongCarInFo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CYiRongCarInFoApp:
// �йش����ʵ�֣������ YiRongCarInFo.cpp
//

class CYiRongCarInFoApp : public CWinApp
{
public:
	CYiRongCarInFoApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CYiRongCarInFoApp theApp;