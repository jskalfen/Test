/*----------------------------------------------------------------------+
|    $Source: /bswcivilom-root/sldev/util/superupd/superupd.h,v $
|    $Revision: 1.4 $
|    $Date: 2016/07/08 17:06:16 $
|    $Author: Dave.Buckley $
|
|    $Copyright: (c) 2016 Bentley Systems, Incorporated. All rights reserved. $
|
|     $Log: superupd.h,v $
|     Revision 1.4  2016/07/08 17:06:16  Dave.Buckley
|     Add check for Elevated User level
|
|     Revision 1.3  2015/08/07 04:33:01  Dave.Buckley
|     Cleanup
|
|     Revision 1.2  2013/06/06 18:55:09  Dave.Buckley
|     S-96493
|
|     Revision 1.1  2012/11/14 03:16:22  Dave.Buckley
|     S-55693 Visual Studio conversion to VS2008(C & Fortran)
|
+----------------------------------------------------------------------*/
#pragma once

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"        // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSuperupdApp:
// See superupd.cpp for the implementation of this class
//

class CSuperupdApp : public CWinApp
    {
    public:
        CSuperupdApp();

        // Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(CSuperupdApp)
    public:
        virtual BOOL InitInstance();
        //}}AFX_VIRTUAL

        // Implementation
        BOOL IsElevated();

        //{{AFX_MSG(CSuperupdApp)
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
    };

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
