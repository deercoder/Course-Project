// TOOL.h : main header file for the TOOL DLL
//

#if !defined(AFX_TOOL_H__6AA67614_1AFA_4517_ADD2_50485659B488__INCLUDED_)
#define AFX_TOOL_H__6AA67614_1AFA_4517_ADD2_50485659B488__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTOOLApp
// See TOOL.cpp for the implementation of this class
//

class CTOOLApp : public CWinApp
{
public:
	CTOOLApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTOOLApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CTOOLApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOL_H__6AA67614_1AFA_4517_ADD2_50485659B488__INCLUDED_)
