/*----------------------------------------------------------------------+
|    $Source: /bswcivilom-root/sldev/util/superupd/StdAfx.h,v $
|    $Revision: 1.3 $
|    $Date: 2017/02/08 16:24:08 $
|    $Author: Dave.Buckley $
|
|    $Copyright: (c) 2017 Bentley Systems, Incorporated. All rights reserved. $
|
|     $Log: StdAfx.h,v $
|     Revision 1.3  2017/02/08 16:24:08  Dave.Buckley
|     Cleanup
|
|     Revision 1.2  2013/06/06 18:55:08  Dave.Buckley
|     S-96493
|
|     Revision 1.1  2012/11/14 03:16:19  Dave.Buckley
|     S-55693 Visual Studio conversion to VS2008(C & Fortran)
+----------------------------------------------------------------------*/

#include "targetver.h"

#pragma once

#define VC_EXTRALEAN        // Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>        // MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>            // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
