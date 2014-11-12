#pragma once

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#define POINTER_64 __ptr64

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

#include <afxctl.h>         // MFC support for ActiveX Controls
#include <afxext.h>         // MFC extensions
#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Comon Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

// Delete the two includes below if you do not wish to use the MFC
//  database classes
#ifndef _WIN64

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>                      // MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>                     // MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#endif // _WIN64
#include <afxwin.h>

//#define USE_CHTTP
//��ʱ�궨�� ��
#define OCX_TIMEOUT_MAX				120

//����ע�ᡢʶ��OCX����ֵ
#define OCX_ERROR_NO_ERROR			0		//ʶ���ע��ɹ�
#define OCX_ERROR_NO_CAMERA			1		//δ��⵽USB����ͷ
#define OCX_ERROR_ENROLL_FAIL		2		//ע��ʧ��
#define OCX_ERROR_MATCH_FAIL		2		//ʶ��ʧ��
#define OCX_ERROR_UNALLOW_USER		3		//�Ƿ��û�
#define OCX_ERROR_TIME_OUT			4		//��ʱ
#define OCX_ERROR_FACESERVER_DOWN	5		//�������쳣
#define OCX_ERROR_USER_CANCEL		6		//�û�ȡ��
#define	OCX_ERROR_VERSION_ERROR		7		//OCX�汾����
#define	OCX_ERROR_LIVEFACE_INIT_FAIL		8		//�������ʼ��ʧ��
#define	OCX_ERROR_LIVEFACE_WIDGET_FAIL		9		//������WIDGET��ʼ��ʧ��
#define	OCX_ERROR_LIVEFACE_FAIL		10		//�������ж�Ϊ�ǻ���


//#define OCX_LOG_PATH	"C://Program Files//FaceLoginOCX//log.txt"
#define CURENT_OCX_VER	"v1.0.3"			//��ǰ����汾��
#define OCX_LOG_PATH	"D://log.txt"
//�����͹رջ����� �Լ����õ�·��
#define LIVE_FACE_TEST  1
#define LIVE_FACE_MODEL_PATH "C:\\FaceLoginModel"