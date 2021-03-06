// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A11357BE_9127_40E4_8AEF_01EAD526B5CA__INCLUDED_)
#define AFX_STDAFX_H__A11357BE_9127_40E4_8AEF_01EAD526B5CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


#define CS_M_PI       3.14159265358979323846

#define RAD2DEG(xX) (180.0f/CS_M_PI * (xX))
#define DEG2RAD(xX) (CS_M_PI/180.0f * (xX))

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A11357BE_9127_40E4_8AEF_01EAD526B5CA__INCLUDED_)
