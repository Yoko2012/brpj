// YiRongCarDetectFPQ.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CYiRongCarDetectFPQApp:
// �йش����ʵ�֣������ YiRongCarDetectFPQ.cpp
//

class CYiRongCarDetectFPQApp : public CWinApp
{
public:
	CYiRongCarDetectFPQApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CYiRongCarDetectFPQApp theApp;