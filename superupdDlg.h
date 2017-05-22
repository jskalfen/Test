/*----------------------------------------------------------------------+
|    $Source: /bswcivilom-root/sldev/util/superupd/superupdDlg.h,v $
|    $Revision: 1.18 $
|    $Date: 2017/02/13 17:32:01 $
|    $Author: Kevin.Holman $
|
|    $Copyright: (c) 2017 Bentley Systems, Incorporated. All rights reserved. $
|
|     $Log: superupdDlg.h,v $
|     Revision 1.18  2017/02/13 17:32:01  Kevin.Holman
|     Remove option to update MO address database - MO does not have one
|
|     Revision 1.17  2016/11/30 15:29:56  Tom.Mettel
|     Add Missouri Defaults
|
|     Revision 1.16  2016/10/12 20:47:37  Kevin.Holman
|     Enhancement 581700:(RF) (NJ) (V5) Create Address Database
|
|     Revision 1.15  2016/04/28 16:14:28  Kevin.Holman
|     Changes for address databases
|
|     Revision 1.14  2015/08/07 04:33:02  Dave.Buckley
|     Cleanup
|
|     Revision 1.13  2015/06/02 21:01:45  Tom.Mettel
|     Rework for adding Queensland
|
|     Revision 1.12  2015/02/21 04:37:03  Dave.Buckley
|     Update logging
|
|     Revision 1.11  2014/08/28 00:11:21  Dave.Buckley
|     Base Super folder tag for all updates to access
|
|     Revision 1.10  2013/10/03 15:44:34  Dave.Buckley
|     Remove WVPASS client since they are web based now
|
|     Revision 1.9  2013/09/30 01:07:38  Dave.Buckley
|     Add MDePASS
|
|     Revision 1.8  2013/09/30 00:24:53  Dave.Buckley
|     Make data update by date if not selected.
|     Add data update folder
|
|     Revision 1.7  2013/06/06 18:55:11  Dave.Buckley
|     S-96493
|
|     Revision 1.6  2013/05/22 21:49:43  Dave.Buckley
|     Add AZeRM
|
|     Revision 1.5  2013/05/22 18:22:58  Dave.Buckley
|     Remove Georgia as it doesn't really work and we need the GUI space
|
|     Revision 1.4  2013/05/22 18:10:18  Dave.Buckley
|     BSW Style Guide - Remove tabs
|
|     Revision 1.3  2013/05/22 16:27:15  Jennifer.Gende
|     S-94904(AZ) Build the Development Framework
|
|     Revision 1.2  2013/04/11 16:59:43  Dave.Buckley
|     Add SLCache logic for helping multiple update runs
|     Add SD-eRM and WI-eRM
|
|     Revision 1.1  2012/11/14 03:16:27  Dave.Buckley
|     S-55693 Visual Studio conversion to VS2008(C & Fortran)
|
+----------------------------------------------------------------------*/
/*------------------------------------------------------------------------------
* FILENAME  superupddlg.h
* PURPOSE   This file contains the header for the SUPERLOAD Update program.
*-----------------------------------------------------------------------------*/
#pragma once

#include "afxwin.h"

class CSuperupdDlg : public CDialog
    {
    // Construction
    public:
        CSuperupdDlg (CWnd* pParent = NULL);    // standard constructor

        // Dialog Data
        //{{AFX_DATA(CSuperupdDlg)
        enum { IDD = IDD_SUPERUPD_DIALOG };
        CEdit       m_QLDePASSBaseDir;
        CButton     m_DoQLDePASS;
        CEdit       m_QLDeRMBaseDir;
        CButton     m_DoQLDeRM;
        CButton     m_DoQLDData;
        CEdit       m_MIePASSBaseDir;
        CEdit       m_MIPASSBaseDir;
        CButton     m_DoMIePASS;
        CButton     m_DoNJePASS;
        CButton     m_DoMIPASS;
        CEdit       m_NJePASSBaseDir;
        CEdit       m_IAePASSBaseDir;
        CEdit       m_IAeRMBaseDir;
        CButton     m_DoIAePASS;
        CButton     m_DoIAeRM;
        CButton     m_DoSDeRM;
        CEdit       m_SDeRMBaseDir;
        CButton     m_DoVAeRoute;
        CEdit       m_VAeRouteBaseDir;
        CButton     m_DoVAeRM;
        CEdit       m_VAeRMBaseDir;
        CButton     m_DoVAData;
        CButton     m_DoWAData;
        CButton     m_DoLAData;
        CButton     m_DoNJData;
        CButton     m_DoNCData;
        CButton     m_DoILData;
        CButton     m_DoCOData;
        CButton     m_DoAZData;
        CButton     m_DoGAData;
        CEdit       m_MIeRMBaseDir;
        CButton     m_DoMIeRM;
        CButton     m_DoMIData;
        CButton     m_DoAReRM;
        CEdit       m_AReRMBaseDir;
        CButton     m_DoAZeRM;
        CEdit       m_AZeRMBaseDir;
        CButton     m_DoALeRM;
        CEdit       m_ALeRMBaseDir;
        CButton     m_DoALePASS;
        CEdit       m_ALePASSBaseDir;
        CEdit       m_MultiStateBaseDir;
        CButton     m_DoMultiState;
        CEdit       m_WIeRouteBaseDir;
        CButton     m_DoWIeRoute;
        CEdit       m_WIeRMBaseDir;
        CButton     m_DoWIeRM;
        CEdit       m_WVeRMBaseDir;
        CButton     m_DoWVeRM;
        CButton     m_DoCTeRM;
        CEdit       m_CTeRMBaseDir;
        CEdit       m_RestDBBaseDir;
        CButton     m_DoRestDB;
        CEdit       m_ePASSSharedDir;
        CButton     m_DoMaintenanceMgr;
        CButton     m_DoWVePASS;
        CButton     m_DoWVData;
        CButton     m_DoWIData;
        CButton     m_DoSDPASS;
        CButton     m_DoSDePASS;
        CButton     m_DoSDData;
        CButton     m_DoRoute;
        CButton     m_DoPASSDB;
        CButton     m_DoOHPASS;
        CButton     m_DoOHeRM;
        CButton     m_DoOHePASS;
        CButton     m_DoOHData;
        CButton     m_DoNEPASS;
        CButton     m_DoNEeRM;
        CButton     m_DoNEePASS;
        CButton     m_DoNEData;
        CButton     m_DoKYeRM;
        CButton     m_DoKYData;
        CButton     m_DoIAData;
        CButton     m_DoCTPASS;
        CButton     m_DoCTePASS;
        CButton     m_DoCTData;
        CButton     m_DoARPASS;
        CButton     m_DoARePASS;
        CButton     m_DoARData;
        CButton     m_DoALPASS;
        CButton     m_DoALData;
        CEdit       m_OHeRMBaseDir;
        CEdit       m_NEeRMBaseDir;
        CEdit       m_KYeRMBaseDir;
        CEdit       m_WVePASSBaseDir;
        CEdit       m_WinSysDir;
        CEdit       m_SDPASSBaseDir;
        CEdit       m_SDePASSBaseDir;
        CEdit       m_RouteBaseDir;
        CEdit       m_PASSDBBaseDir;
        CEdit       m_OHPASSBaseDir;
        CEdit       m_OHePASSBaseDir;
        CEdit       m_NEPASSBaseDir;
        CEdit       m_NEePASSBaseDir;
        CEdit       m_ePASSBaseDir;
        CEdit       m_CTPASSBaseDir;
        CEdit       m_CTePASSBaseDir;
        CEdit       m_ARPASSBaseDir;
        CEdit       m_ARePASSBaseDir;
        CEdit       m_ALPASSBaseDir;
        CButton     m_DoORData;
        CEdit       m_AZePASSBaseDir;
        CButton     m_DoAZePASS;
        CButton     m_doCTAddress;
        CButton     m_doMDAddress;
        CButton     m_doNJAddress;
        CButton     m_doQLDAddress;
        CButton     m_doVAAddress;
        CButton     m_doWIAddress;
        //}}AFX_DATA

        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(CSuperupdDlg)
    protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        //}}AFX_VIRTUAL

        // Implementation
    protected:
        long AppendToLog(LPCSTR text, LPCSTR logFile, LPCSTR directory, LPCSTR optional = "");
        long AppendToLog(LPCSTR text, LPCSTR logFile);

        long AddToUpdate(LPCSTR updateFile, LPCSTR sourceUpdate, LPCSTR dataUpdate, LPCSTR update, LPCSTR dir1, LPCSTR dir2, LPCSTR winSysDir, 
            LPCSTR message, bool dateDepenedent = false);

        bool existCommand(LPCSTR text);
        void addCommand(LPCSTR text);
        void resetCommands();

        bool updateESUPER();
        bool updateEPASS();
        bool updateERM();

        CStringArray m_arrayCommand;

        CString m_computerName;
        CString m_userName;

        HICON m_hIcon;
        void getSourceLocations();
        void addSourceLocation(LPCSTR location);
        void getDataLocations();
        void addDataLocation(LPCSTR location);

        // Generated message map functions
        //{{AFX_MSG(CSuperupdDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
        afx_msg void OnPaint();
        afx_msg HCURSOR OnQueryDragIcon();
        virtual void OnOK();
        afx_msg void OnSaveSettings();
        afx_msg void OnClearAll();
        virtual void OnCancel();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    public:
        CButton m_DoNJeRM;
        CEdit m_NJeRMBaseDir;
        CButton m_DoKYePASS;
        CEdit m_KYePASSBaseDir;
        CButton m_DoMDePASS;
        CEdit m_MDePASSBaseDir;
        CButton m_DoMOePASS;
        CEdit m_MOePASSBaseDir;
        CEdit m_updateFile;
        CButton batchCreateOnly;
        CComboBox m_sourceLocation;
        CButton m_DoNCeRoute;
        CButton m_DoNCeRM;
        CEdit m_NCeRMBaseDir;
        CEdit m_NCeRouteBaseDir;
        CButton m_DoMDeRoute;
        CButton m_DoMDeRM;
        CButton m_DoMDData;
        CEdit m_MDeRMBaseDir;
        CEdit m_MDeRouteBaseDir;
        CButton m_DoMOeRoute;
        CButton m_DoMOeRM;
        CButton m_DoMOData;
        CEdit m_MOeRMBaseDir;
        CEdit m_MOeRouteBaseDir;
        CComboBox m_dataLocation;

        CString m_routeDir;

    };

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
