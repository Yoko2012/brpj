// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__21E4EB70_D66A_443D_B9D1_4C61F2B153E1__INCLUDED_)
#define AFX_STDAFX_H__21E4EB70_D66A_443D_B9D1_4C61F2B153E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

//修改这里 记得把主程序也改下
//#define MESSAGEBOX_TITLE "智能视频车牌分析服务软件 2.0版-数据库连接设置"

#define MESSAGEBOX_TITLE "车牌识别分析应用软件 2.0版-数据库连接设置"


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__21E4EB70_D66A_443D_B9D1_4C61F2B153E1__INCLUDED_)
