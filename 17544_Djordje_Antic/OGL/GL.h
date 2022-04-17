// GL.h : main header file for the GL application
//

#if !defined(AFX_GL_H__7D03266C_6EEA_4E63_B302_9E843DA4F47F__INCLUDED_)
#define AFX_GL_H__7D03266C_6EEA_4E63_B302_9E843DA4F47F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGLApp:
// See GL.cpp for the implementation of this class
//

class CGLApp : public CWinApp
{
public:
	CGLApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGLApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CGLApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GL_H__7D03266C_6EEA_4E63_B302_9E843DA4F47F__INCLUDED_)
