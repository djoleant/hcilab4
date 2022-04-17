// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__E6672BB6_6DD6_4BC5_BDA9_F1C38A9F1611__INCLUDED_)
#define AFX_STDAFX_H__E6672BB6_6DD6_4BC5_BDA9_F1C38A9F1611__INCLUDED_

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

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GL//glu32.lib")
#pragma comment (lib, "GL//glaux.lib")
#pragma comment (lib, "GL//glut32.lib")

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__E6672BB6_6DD6_4BC5_BDA9_F1C38A9F1611__INCLUDED_)
