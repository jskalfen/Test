/*----------------------------------------------------------------------+
|    $Source: /bswcivilom-root/sldev/util/superupd/superupd.cpp,v $
|    $Revision: 1.7 $
|    $Date: 2016/07/23 13:13:39 $
|    $Author: Dave.Buckley $
|
|    $Copyright: (c) 2016 Bentley Systems, Incorporated. All rights reserved. $
|
|     $Log: superupd.cpp,v $
|     Revision 1.7  2016/07/23 13:13:39  Dave.Buckley
|     Update Elevated User level handling
|
|     Revision 1.6  2016/07/08 17:03:47  Dave.Buckley
|     Add check for Elevated User level
|
|     Revision 1.5  2016/04/28 17:10:03  Dave.Buckley
|     Correct Addresss Tab Order
|
|     Revision 1.4  2016/04/28 16:14:25  Kevin.Holman
|     Changes for address databases
|
|     Revision 1.3  2015/08/07 04:33:00  Dave.Buckley
|     Cleanup
|
|     Revision 1.2  2013/06/06 18:55:08  Dave.Buckley
|     S-96493
|
|     Revision 1.1  2012/11/14 03:16:19  Dave.Buckley
|     S-55693 Visual Studio conversion to VS2008(C & Fortran)
|
+----------------------------------------------------------------------*/
#include "stdafx.h"
#include "superupd.h"
#include "superupdDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CSuperupdApp, CWinApp)
    //{{AFX_MSG_MAP(CSuperupdApp)
    // NOTE - the ClassWizard will add and remove mapping macros here.
    //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG
    ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

CSuperupdApp::CSuperupdApp()
    {
    // TODO: add construction code here,
    // Place all significant initialization in InitInstance
    }

CSuperupdApp theApp;

BOOL CSuperupdApp::InitInstance()
    {

    if (!IsElevated())
        {
        AfxMessageBox("Application must be run with elevated permissions to update properly!!!\n\nConsider using 'Run as Administrator' when launching this application.", MB_ICONSTOP);
        return FALSE;
        }

    CSuperupdDlg dlg;

    m_pMainWnd = &dlg;
    int nResponse = dlg.DoModal();

    if (nResponse == IDOK)
        {
        // TODO: Place code here to handle when the dialog is
        //  dismissed with OK
        }
    else if (nResponse == IDCANCEL)
        {
        // TODO: Place code here to handle when the dialog is
        //  dismissed with Cancel
        }

    // Since the dialog has been closed, return FALSE so that we exit the
    //  application, rather than start the application's message pump.
    return FALSE;
    }

BOOL CSuperupdApp::IsElevated()
    {
    BOOL fRet = FALSE;
    HANDLE hToken = NULL;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
        {
        TOKEN_ELEVATION Elevation;
        DWORD cbSize = sizeof(TOKEN_ELEVATION);
        if (GetTokenInformation( hToken, TokenElevation, &Elevation, sizeof(Elevation), &cbSize))
            {
            fRet = Elevation.TokenIsElevated;
            }
        }
    if (hToken)
        {
        CloseHandle(hToken);
        }

    return fRet;
    }