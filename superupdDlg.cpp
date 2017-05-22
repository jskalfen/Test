/*----------------------------------------------------------------------+
|    $Source: /bswcivilom-root/sldev/util/superupd/superupdDlg.cpp,v $
|    $Revision: 1.28 $
|    $Date: 2017/02/13 17:32:00 $
|    $Author: Kevin.Holman $
|
|    $Copyright: (c) 2017 Bentley Systems, Incorporated. All rights reserved. $
|
|     $Log: superupdDlg.cpp,v $
|     Revision 1.28  2017/02/13 17:32:00  Kevin.Holman
|     Remove option to update MO address database - MO does not have one
|
|     Revision 1.27  2016/11/30 15:29:57  Tom.Mettel
|     Add Missouri Defaults
|
|     Revision 1.26  2016/10/12 20:47:36  Kevin.Holman
|     Enhancement 581700:(RF) (NJ) (V5) Create Address Database
|
|     Revision 1.25  2016/04/28 17:10:04  Dave.Buckley
|     Correct Addresss Tab Order
|
|     Revision 1.24  2016/04/28 16:14:27  Kevin.Holman
|     Changes for address databases
|
|     Revision 1.23  2015/06/02 21:01:41  Tom.Mettel
|     Rework for adding Queensland
|
|     Revision 1.22  2015/02/21 04:37:04  Dave.Buckley
|     Update logging
|
|     Revision 1.21  2014/12/07 19:47:50  Dave.Buckley
|     Update messaging for batch script file
|
|     Revision 1.20  2014/12/07 18:17:45  Dave.Buckley
|     Update messaging for batch script file
|
|     Revision 1.19  2014/10/23 03:22:34  Dave.Buckley
|     Change Windows system default
|
|     Revision 1.18  2014/08/28 15:36:39  Dave.Buckley
|     Add Route update when an ePASS update is requested
|
|     Revision 1.17  2014/08/28 00:11:18  Dave.Buckley
|     Base Super folder tag for all updates to access
|
|     Revision 1.16  2014/08/25 15:21:04  Dave.Buckley
|     Add check for plain copy to verify command status
|
|     Revision 1.15  2014/07/26 03:22:55  Dave.Buckley
|     Update error messages to include path and/or filename
|
|     Revision 1.14  2014/07/25 17:53:58  Dave.Buckley
|     Update error messages to include path and/or filename
|
|     Revision 1.13  2013/10/03 15:44:33  Dave.Buckley
|     Remove WVPASS client since they are web based now
|
|     Revision 1.12  2013/10/03 14:22:10  Dave.Buckley
|     Fix minor bug with log output format and GUI field position
|
|     Revision 1.11  2013/09/30 01:07:36  Dave.Buckley
|     Add MDePASS
|
|     Revision 1.10  2013/09/30 00:24:51  Dave.Buckley
|     Make data update by date if not selected.
|     Add data update folder
|
|     Revision 1.9  2013/06/06 18:55:10  Dave.Buckley
|     S-96493
|
|     Revision 1.8  2013/05/22 21:49:42  Dave.Buckley
|     Add AZeRM
|
|     Revision 1.7  2013/05/22 18:22:57  Dave.Buckley
|     Remove Georgia as it doesn't really work and we need the GUI space
|
|     Revision 1.6  2013/05/22 18:10:16  Dave.Buckley
|     BSW Style Guide - Remove tabs
|
|     Revision 1.5  2013/05/22 16:26:57  Jennifer.Gende
|     S-94904(AZ) Build the Development Framework
|
|     Revision 1.4  2013/04/11 16:59:41  Dave.Buckley
|     Add SLCache logic for helping multiple update runs
|     Add SD-eRM and WI-eRM
|
|     Revision 1.3  2013/03/20 16:21:01  Dave.Buckley
|     BSW Style guide
|
|     Revision 1.2  2013/01/16 22:53:01  Dave.Buckley
|     Delete the obsolete ini value LogFile
|
|     Revision 1.1  2012/11/14 03:16:25  Dave.Buckley
|     S-55693 Visual Studio conversion to VS2008(C & Fortran)
|
+----------------------------------------------------------------------*/
/*------------------------------------------------------------------------------
* FILENAME  superupddlg.cpp
* PURPOSE   This file contains the implementation of the SUPERLOAD Update program.
*-----------------------------------------------------------------------------*/

#include "stdafx.h"
#include "superupd.h"
#include "superupdDlg.h"
#include "fileutil.h"
#include <time.h>
#include <direct.h>
#include "ReporterSetup.h"

HINSTANCE hSLPrintDLL;

const CString SUPERUPD_UPDATEFILE_ERROR = "Ini : Missing UpdateFile setting or invalid path.\n[Defaults] UpdateFile=\\\\Path\\Filename";
const CString UPDATE_SCRIPT = "c:\\superupd.bat";
const CString UPDATE_ERROR_FILE = "c:\\superupd.err";
const CString UPDATE_SCRIPT_ERROR = "Unable to open SuperUpd batch script.\n\nPath does not exist or permission error.\n\nFile = ";
const CString UPDATE_SCRIPT_SUCCESS = "Superupd.bat batch file was created successfully.\n\nFile = ";
const CString UPDATE_BY_DATE = "Update by date";

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
    {
    public:
        CAboutDlg();

        // Dialog Data
        //{{AFX_DATA(CAboutDlg)
        enum { IDD = IDD_ABOUTBOX };
        //}}AFX_DATA

        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(CAboutDlg)
    protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        //}}AFX_VIRTUAL

        // Implementation
    protected:
        //{{AFX_MSG(CAboutDlg)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
    };

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
    {
    //{{AFX_DATA_INIT(CAboutDlg)
    //}}AFX_DATA_INIT
    }

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
    {
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CAboutDlg)
    //}}AFX_DATA_MAP
    }

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
    //{{AFX_MSG_MAP(CAboutDlg)
    // No message handlers
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

// CSuperupdDlg dialog

CSuperupdDlg::CSuperupdDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CSuperupdDlg::IDD, pParent)
    {
    //{{AFX_DATA_INIT(CSuperupdDlg)
    //}}AFX_DATA_INIT
    // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    int endLoc;

    m_routeDir = AfxGetApp()->GetProfileString("Defaults", "RouteBaseDir", "C:\\SUPER");

    endLoc = m_routeDir.GetLength() - 1;
    if ('\\' == m_routeDir.GetAt(endLoc))
        {
        m_routeDir.SetAt(endLoc, 0);
        }
    }

void CSuperupdDlg::DoDataExchange(CDataExchange* pDX)
    {
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CSuperupdDlg)
    DDX_Control(pDX, IDC_QLDEPASS_BASEDIR, m_QLDePASSBaseDir);
    DDX_Control(pDX, IDC_DO_QLDEPASS, m_DoQLDePASS);
    DDX_Control(pDX, IDC_QLDERM_BASEDIR, m_QLDeRMBaseDir);
    DDX_Control(pDX, IDC_DO_QLDERM, m_DoQLDeRM);
    DDX_Control(pDX, IDC_DO_QLDDATA, m_DoQLDData);
    DDX_Control(pDX, IDC_MIEPASS_BASEDIR, m_MIePASSBaseDir);
    DDX_Control(pDX, IDC_DO_MIEPASS, m_DoMIePASS);
    DDX_Control(pDX, IDC_DO_NJEPASS, m_DoNJePASS);
    DDX_Control(pDX, IDC_NJEPASS_BASEDIR, m_NJePASSBaseDir);
    DDX_Control(pDX, IDC_IAEPASS_BASEDIR, m_IAePASSBaseDir);
    DDX_Control(pDX, IDC_IAERM_BASEDIR, m_IAeRMBaseDir);
    DDX_Control(pDX, IDC_DO_IAEPASS, m_DoIAePASS);
    DDX_Control(pDX, IDC_DO_IAERM, m_DoIAeRM);
    DDX_Control(pDX, IDC_DO_SDERM, m_DoSDeRM);
    DDX_Control(pDX, IDC_SDERM_BASEDIR, m_SDeRMBaseDir);
    DDX_Control(pDX, IDC_DO_VAEROUTE, m_DoVAeRoute);
    DDX_Control(pDX, IDC_VAEROUTE_BASEDIR, m_VAeRouteBaseDir);
    DDX_Control(pDX, IDC_DO_VAERM, m_DoVAeRM);
    DDX_Control(pDX, IDC_VAERM_BASEDIR, m_VAeRMBaseDir);
    DDX_Control(pDX, IDC_DO_VADATA, m_DoVAData);
    DDX_Control(pDX, IDC_DO_WAData, m_DoWAData);
    DDX_Control(pDX, IDC_DO_LADATA, m_DoLAData);
    DDX_Control(pDX, IDC_DO_NJDATA, m_DoNJData);
    DDX_Control(pDX, IDC_DO_NCDATA, m_DoNCData);
    DDX_Control(pDX, IDC_DO_ILDATA, m_DoILData);
    DDX_Control(pDX, IDC_DO_CODATA, m_DoCOData);
    DDX_Control(pDX, IDC_DO_AZDATA, m_DoAZData);
    DDX_Control(pDX, IDC_DO_GADATA, m_DoGAData);
    DDX_Control(pDX, IDC_MIERM_BASEDIR, m_MIeRMBaseDir);
    DDX_Control(pDX, IDC_DO_MIERM, m_DoMIeRM);
    DDX_Control(pDX, IDC_DO_MIDATA, m_DoMIData);
    DDX_Control(pDX, IDC_DO_ARERM, m_DoAReRM);
    DDX_Control(pDX, IDC_ARERM_BASEDIR, m_AReRMBaseDir);
    DDX_Control(pDX, IDC_DO_AZERM, m_DoAZeRM);
    DDX_Control(pDX, IDC_AZERM_BASEDIR, m_AZeRMBaseDir);
    DDX_Control(pDX, IDC_DO_ALERM, m_DoALeRM);
    DDX_Control(pDX, IDC_ALERM_BASEDIR, m_ALeRMBaseDir);
    DDX_Control(pDX, IDC_DO_ALEPASS, m_DoALePASS);
    DDX_Control(pDX, IDC_ALEPASS_BASEDIR, m_ALePASSBaseDir);
    DDX_Control(pDX, IDC_MULTISTATE_BASEDIR, m_MultiStateBaseDir);
    DDX_Control(pDX, IDC_DO_MULTISTATE, m_DoMultiState);
    DDX_Control(pDX, IDC_WIEROUTE_BASEDIR, m_WIeRouteBaseDir);
    DDX_Control(pDX, IDC_DO_WIEROUTE, m_DoWIeRoute);
    DDX_Control(pDX, IDC_WIERM_BASEDIR, m_WIeRMBaseDir);
    DDX_Control(pDX, IDC_DO_WIERM, m_DoWIeRM);
    DDX_Control(pDX, IDC_WVERM_BASEDIR, m_WVeRMBaseDir);
    DDX_Control(pDX, IDC_DO_WVERM, m_DoWVeRM);
    DDX_Control(pDX, IDC_DO_CTERM, m_DoCTeRM);
    DDX_Control(pDX, IDC_CTERM_BASEDIR, m_CTeRMBaseDir);
    DDX_Control(pDX, IDC_RESTDB_BASEDIR, m_RestDBBaseDir);
    DDX_Control(pDX, IDC_DO_RESTDB, m_DoRestDB);
    DDX_Control(pDX, IDC_EPASS_SHAREDDIR, m_ePASSSharedDir);
    DDX_Control(pDX, IDC_DO_MAINTENANCEMGR, m_DoMaintenanceMgr);
    DDX_Control(pDX, IDC_DO_WVEPASS, m_DoWVePASS);
    DDX_Control(pDX, IDC_DO_WVDATA, m_DoWVData);
    DDX_Control(pDX, IDC_DO_WIDATA, m_DoWIData);
    DDX_Control(pDX, IDC_DO_SDPASS, m_DoSDPASS);
    DDX_Control(pDX, IDC_DO_SDEPASS, m_DoSDePASS);
    DDX_Control(pDX, IDC_DO_SDDATA, m_DoSDData);
    DDX_Control(pDX, IDC_DO_ROUTE, m_DoRoute);
    DDX_Control(pDX, IDC_DO_PASSDB, m_DoPASSDB);
    DDX_Control(pDX, IDC_DO_OHPASS, m_DoOHPASS);
    DDX_Control(pDX, IDC_DO_OHERM, m_DoOHeRM);
    DDX_Control(pDX, IDC_DO_OHEPASS, m_DoOHePASS);
    DDX_Control(pDX, IDC_DO_OHDATA, m_DoOHData);
    DDX_Control(pDX, IDC_DO_NEPASS, m_DoNEPASS);
    DDX_Control(pDX, IDC_DO_NEERM, m_DoNEeRM);
    DDX_Control(pDX, IDC_DO_NEEPASS, m_DoNEePASS);
    DDX_Control(pDX, IDC_DO_NEDATA, m_DoNEData);
    DDX_Control(pDX, IDC_DO_KYERM, m_DoKYeRM);
    DDX_Control(pDX, IDC_DO_KYDATA, m_DoKYData);
    DDX_Control(pDX, IDC_DO_IADATA, m_DoIAData);
    DDX_Control(pDX, IDC_DO_CTPASS, m_DoCTPASS);
    DDX_Control(pDX, IDC_DO_CTEPASS, m_DoCTePASS);
    DDX_Control(pDX, IDC_DO_CTDATA, m_DoCTData);
    DDX_Control(pDX, IDC_DO_ARPASS, m_DoARPASS);
    DDX_Control(pDX, IDC_DO_AREPASS, m_DoARePASS);
    DDX_Control(pDX, IDC_DO_ARDATA, m_DoARData);
    DDX_Control(pDX, IDC_DO_ALPASS, m_DoALPASS);
    DDX_Control(pDX, IDC_DO_ALDATA, m_DoALData);
    DDX_Control(pDX, IDC_OHERM_BASEDIR, m_OHeRMBaseDir);
    DDX_Control(pDX, IDC_NEERM_BASEDIR, m_NEeRMBaseDir);
    DDX_Control(pDX, IDC_KYERM_BASEDIR, m_KYeRMBaseDir);
    DDX_Control(pDX, IDC_WVEPASS_BASEDIR, m_WVePASSBaseDir);
    DDX_Control(pDX, IDC_WINSYSDIR, m_WinSysDir);
    DDX_Control(pDX, IDC_SDPASS_BASEDIR, m_SDPASSBaseDir);
    DDX_Control(pDX, IDC_SDEPASS_BASEDIR, m_SDePASSBaseDir);
    DDX_Control(pDX, IDC_ROUTE_BASE_DIR, m_RouteBaseDir);
    DDX_Control(pDX, IDC_PASSDB_BASEDIR, m_PASSDBBaseDir);
    DDX_Control(pDX, IDC_OHPASS_BASEDIR, m_OHPASSBaseDir);
    DDX_Control(pDX, IDC_OHEPASS_BASEDIR, m_OHePASSBaseDir);
    DDX_Control(pDX, IDC_NEPASS_BASEDIR, m_NEPASSBaseDir);
    DDX_Control(pDX, IDC_NEEPASS_BASEDIR, m_NEePASSBaseDir);
    DDX_Control(pDX, IDC_EPASS_BASEDIR, m_ePASSBaseDir);
    DDX_Control(pDX, IDC_CTPASS_BASEDIR, m_CTPASSBaseDir);
    DDX_Control(pDX, IDC_CTEPASS_BASEDIR, m_CTePASSBaseDir);
    DDX_Control(pDX, IDC_ARPASS_BASEDIR, m_ARPASSBaseDir);
    DDX_Control(pDX, IDC_AREPASS_BASEDIR, m_ARePASSBaseDir);
    DDX_Control(pDX, IDC_ALPASS_BASEDIR, m_ALPASSBaseDir);
    DDX_Control(pDX, IDC_AZEPASS_BASEDIR, m_AZePASSBaseDir);
    DDX_Control(pDX, IDC_DO_AZEPASS, m_DoAZePASS);
    DDX_Control(pDX, IDC_DO_CT_ADDRESS, m_doCTAddress);
    DDX_Control(pDX, IDC_DO_MD_ADDRESS, m_doMDAddress);
    DDX_Control(pDX, IDC_DO_NJ_ADDRESS, m_doNJAddress);
    DDX_Control(pDX, IDC_DO_QLD_ADDRESS, m_doQLDAddress);
    DDX_Control(pDX, IDC_DO_VA_ADDRESS, m_doVAAddress);
    DDX_Control(pDX, IDC_DO_WI_ADDRESS, m_doWIAddress);
    //}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_DO_NJERM, m_DoNJeRM);
    DDX_Control(pDX, IDC_NJERM_BASEDIR, m_NJeRMBaseDir);
    DDX_Control(pDX, IDC_DO_KYEPASS, m_DoKYePASS);
    DDX_Control(pDX, IDC_KYEPASS_BASEDIR, m_KYePASSBaseDir);
    DDX_Control(pDX, IDC_UPDATE_FILE, m_updateFile);
    DDX_Control(pDX, IDC_BAT_ONLY, batchCreateOnly);
    DDX_Control(pDX, IDC_LOCATION, m_sourceLocation);
    DDX_Control(pDX, IDC_DO_NCERSTMGR, m_DoNCeRM);
    DDX_Control(pDX, IDC_NCERM_BASEDIR, m_NCeRMBaseDir);
    DDX_Control(pDX, IDC_DO_ORDATA, m_DoORData);
    DDX_Control(pDX, IDC_DO_MDERSTMGR, m_DoMDeRM);
    DDX_Control(pDX, IDC_DO_MDDATA, m_DoMDData);
    DDX_Control(pDX, IDC_MDERM_BASEDIR, m_MDeRMBaseDir);
    DDX_Control(pDX, IDC_DO_MOERSTMGR, m_DoMOeRM);
    DDX_Control(pDX, IDC_DO_MODATA, m_DoMOData);
    DDX_Control(pDX, IDC_MOERM_BASEDIR, m_MOeRMBaseDir);
    DDX_Control(pDX, IDC_DATA_LOCATION, m_dataLocation);
    DDX_Control(pDX, IDC_DO_MDEPASS, m_DoMDePASS);
    DDX_Control(pDX, IDC_DO_MOEPASS, m_DoMOePASS);
    DDX_Control(pDX, IDC_MDEPASS_BASEDIR, m_MDePASSBaseDir);
    DDX_Control(pDX, IDC_MOEPASS_BASEDIR, m_MOePASSBaseDir);
    }

BEGIN_MESSAGE_MAP(CSuperupdDlg, CDialog)
    //{{AFX_MSG_MAP(CSuperupdDlg)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_SAVE_SETTINGS, OnSaveSettings)
    ON_BN_CLICKED(IDC_CLEAR_ALL, OnClearAll)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CSuperupdDlg message handlers
void CSuperupdDlg::OnSysCommand(UINT nID, LPARAM lParam)
    {
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
        {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
        }
    else
        {
        CDialog::OnSysCommand(nID, lParam);
        }
    }

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSuperupdDlg::OnPaint()
    {
    if (IsIconic())
        {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
        }
    else
        {
        CDialog::OnPaint();
        }
    }

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSuperupdDlg::OnQueryDragIcon()
    {
    return (HCURSOR) m_hIcon;
    }

/*------------------------------------------------------------------------------
* MODULE      OnInitDialog
* PURPOSE     Sets up the dialog with default or last saved settings
*-------------------------------------------------------------------------------
* AUTHOR      Dan Vogen                  DATE 01  8-2003
* REVISION    DATE         NAME          DESCRIPTION
*-------------------------------------------------------------------------------
* ARGUMENTS   Type         Call Conv  Purpose
*-------------------------------------------------------------------------------
* CONDITION   Value        Description
* VALUES      TRUE
* RETURNED
*-----------------------------------------------------------------------------*/
BOOL CSuperupdDlg::OnInitDialog()
    {
    CDialog::OnInitDialog();

    // Add "About..." menu item to system menu.

    // IDM_ABOUTBOX must be in the system command range.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
        {
        CString strAboutMenu;
        strAboutMenu.LoadString(IDS_ABOUTBOX);
        if (!strAboutMenu.IsEmpty())
            {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
            }
        }

    m_computerName = getenv("COMPUTERNAME");
    m_userName = getenv("USERNAME");

    // Set the icon for this dialog.  The framework does this automatically
    // when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);            // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon

    //
    // GET ALL VALUES FROM THE INI AND INITIALIZE THE DIALOG TO THE WAY IT WAS LAST USED
    //
    CString temp;

#ifdef _DEBUG
    // Just pull the file from the local directory for development work.
    char    currentWorking[_MAX_PATH];

    _getcwd(currentWorking, _MAX_PATH);
    temp = currentWorking;
    temp += "\\superupd.dat";
#else
    temp = AfxGetApp()->GetProfileString("Defaults", "UpdateFile", SUPERUPD_UPDATEFILE_ERROR);
#endif

    m_updateFile.SetWindowText(temp);

    // Convert base save locations
    CString string;

    string = AfxGetApp()->GetProfileString("Defaults", "UpdateSource", "EMPTY");

    if ("EMPTY" != string)
        {
        AfxGetApp()->WriteProfileString("Defaults", "UpdateSource", NULL);

        AfxGetApp()->WriteProfileString("SourceLocations", "UpdateSource", string);
        m_sourceLocation.SetWindowText(string);
        addSourceLocation(string);
        }
    else
        {
        // Ensure that we have something defined
        string = AfxGetApp()->GetProfileString("SourceLocations", "UpdateSource", "EMPTY");

        if ("EMPTY" == string)
            {
            string = "\\\\chisrc1\\src";

            AfxGetApp()->WriteProfileString("SourceLocations", "UpdateSource", string);
            m_sourceLocation.SetWindowText(string);
            addSourceLocation(string);
            }
        }

    //Convert base save locations
    string = AfxGetApp()->GetProfileString("Defaults", "UpdateData", "EMPTY");
    if ("EMPTY" != string)
        {
        AfxGetApp()->WriteProfileString("Defaults", "UpdateData", NULL);

        AfxGetApp()->WriteProfileString("DataLocations", "UpdateData", string);
        m_dataLocation.SetWindowText(string);
        addDataLocation(string);
        }
    else
        {
        //Ensure that we have something in the section
        string = AfxGetApp()->GetProfileString("DataLocations", "UpdateData", "EMPTY");
        if ("EMPTY" == string)
            {
            string = "\\\\chisrc1\\data";

            AfxGetApp()->WriteProfileString("DataLocations", "UpdateData", string);
            m_dataLocation.SetWindowText(string);
            addDataLocation(string);
            }
        }

    //Get the list of used locations
    getSourceLocations();

    //Add the data location
    getDataLocations();

    // ROUTE / MM
    m_DoRoute.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoRoute", 0));

    m_RouteBaseDir.SetWindowText(m_routeDir);

    m_DoMaintenanceMgr.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoMaintenanceMgr", 0));

    // PASS
    m_DoALPASS.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoALPASS", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "ALPASSBaseDir", "C:\\ALPASS");
    m_ALPASSBaseDir.SetWindowText(temp);

    m_DoARPASS.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoARPASS", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "ARPASSBaseDir", "C:\\ARPARS");
    m_ARPASSBaseDir.SetWindowText(temp);

    m_DoCTPASS.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoCTPASS", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "CTPASSBaseDir", "C:\\CTPASS");
    m_CTPASSBaseDir.SetWindowText(temp);

    m_DoNEPASS.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoNEPASS", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "NEPASSBaseDir", "C:\\NATPS");
    m_NEPASSBaseDir.SetWindowText(temp);

    m_DoOHPASS.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoOHPASS", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "OHPASSBaseDir", "C:\\OHPASS");
    m_OHPASSBaseDir.SetWindowText(temp);

    m_DoSDPASS.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoSDPASS", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "SDPASSBaseDir", "C:\\SDAPS");
    m_SDPASSBaseDir.SetWindowText(temp);

    // ePASS
    temp = AfxGetApp()->GetProfileString("Defaults", "ePASSSharedDir", "C:\\INETPUB\\WWWROOT\\SUPER");
    m_ePASSSharedDir.SetWindowText(temp);

    temp = AfxGetApp()->GetProfileString("Defaults", "ePASSBaseDir", "C:\\INETPUB\\WWWROOT");
    m_ePASSBaseDir.SetWindowText(temp);

    m_DoALePASS.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoALePASS", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "ALePASSBaseDir", "ALEPASS");
    m_ALePASSBaseDir.SetWindowText(temp);

    m_DoARePASS.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoARePASS", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "ARePASSBaseDir", "ARPARS");
    m_ARePASSBaseDir.SetWindowText(temp);

    m_DoAZePASS.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoAZePASS", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "AZePASSBaseDir", "ADOT");
    m_AZePASSBaseDir.SetWindowText(temp);

    m_DoCTePASS.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoCTePASS", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "CTePASSBaseDir", "CTPASS");
    m_CTePASSBaseDir.SetWindowText(temp);

    m_DoIAePASS.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoIAePASS", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "IAePASSBaseDir", "IAPS");
    m_IAePASSBaseDir.SetWindowText(temp);

    m_DoKYePASS.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoKYePASS", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "KYePASSBaseDir", "KYTC");
    m_KYePASSBaseDir.SetWindowText(temp);

    m_DoMIePASS.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoMIePASS", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "MIePASSBaseDir", "MIPASS");
    m_MIePASSBaseDir.SetWindowText(temp);

    m_DoMDePASS.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoMDePASS", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "MDePASSBaseDir", "MDPASS");
    m_MDePASSBaseDir.SetWindowText(temp);

    m_DoMOePASS.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoMOePASS", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "MOePASSBaseDir", "MOPASS");
    m_MOePASSBaseDir.SetWindowText(temp);

    m_DoNEePASS.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoNEePASS", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "NEePASSBaseDir", "NATPS");
    m_NEePASSBaseDir.SetWindowText(temp);

    m_DoNJePASS.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoNJePASS", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "boolBaseDir2", "NJPASS");
    m_NJePASSBaseDir.SetWindowText(temp);

    m_DoOHePASS.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoOHePASS", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "OHePASSBaseDir", "OHPASS");
    m_OHePASSBaseDir.SetWindowText(temp);

    m_DoMultiState.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoMultiState", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "MultiStateBaseDir", "MSPORTAL");
    m_MultiStateBaseDir.SetWindowText(temp);

    m_DoQLDePASS.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoQLDePASS", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "QLDePASSBaseDir", "QLDPASS");
    m_QLDePASSBaseDir.SetWindowText(temp);

    m_DoSDePASS.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoSDePASS", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "SDePASSBaseDir", "SDAPS");
    m_SDePASSBaseDir.SetWindowText(temp);

    m_DoWIeRoute.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoWIeRoute", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "WIeRouteBaseDir", "WIDOT");
    m_WIeRouteBaseDir.SetWindowText(temp);

    m_DoWVePASS.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoWVePASS", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "WVePASSBaseDir", "WVEPASS");
    m_WVePASSBaseDir.SetWindowText(temp);

    // eRM
    m_DoALeRM.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoALeRM", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "ALeRMBaseDir", "ALRSTMGR");
    m_ALeRMBaseDir.SetWindowText(temp);

    m_DoAReRM.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoAReRM", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "AReRMBaseDir", "ARRSTMGR");
    m_AReRMBaseDir.SetWindowText(temp);

    m_DoAZeRM.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoAZeRM", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "AZeRMBaseDir", "AZRSTMGR");
    m_AZeRMBaseDir.SetWindowText(temp);

    m_DoCTeRM.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoCTeRM", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "CTeRMBaseDir", "CTRSTMGR");
    m_CTeRMBaseDir.SetWindowText(temp);

    m_DoIAeRM.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoIAeRM", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "IAeRMBaseDir", "IARSTMGR");
    m_IAeRMBaseDir.SetWindowText(temp);

    m_DoKYeRM.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoKYeRM", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "KYeRMBaseDir", "KYRSTMGR");
    m_KYeRMBaseDir.SetWindowText(temp);

    m_DoMDeRM.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoMDeRM", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "MDeRMBaseDir", "MDRSTMGR");
    m_MDeRMBaseDir.SetWindowText(temp);

    m_DoMIeRM.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoMIeRM", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "MIeRMBaseDir", "MIRSTMGR");
    m_MIeRMBaseDir.SetWindowText(temp);

    m_DoMOeRM.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoMOeRM", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "MOeRMBaseDir", "MORSTMGR");
    m_MOeRMBaseDir.SetWindowText(temp);

    m_DoNCeRM.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoNCeRM", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "NCeRMBaseDir", "NCRSTMGR");
    m_NCeRMBaseDir.SetWindowText(temp);

    m_DoNEeRM.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoNEeRM", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "NEeRMBaseDir", "NERSTMGR");
    m_NEeRMBaseDir.SetWindowText(temp);

    m_DoNJeRM.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoNJeRM", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "NJeRMBaseDir", "NJRSTMGR");
    m_NJeRMBaseDir.SetWindowText(temp);

    m_DoOHeRM.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoOHeRM", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "OHeRMBaseDir", "OHRSTMGR");
    m_OHeRMBaseDir.SetWindowText(temp);

    m_DoQLDeRM.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoQLDeRM", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "QLDeRMBaseDir", "QLDRSTMGR");
    m_QLDeRMBaseDir.SetWindowText(temp);

    m_DoSDeRM.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoSDeRM", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "SDeRMBaseDir", "SDRSTMGR");
    m_SDeRMBaseDir.SetWindowText(temp);

    m_DoVAeRM.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoVAeRM", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "VAeRMBaseDir", "VARSTMGR");
    m_VAeRMBaseDir.SetWindowText(temp);

    m_DoVAeRoute.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoVAeRoute", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "VAeRouteBaseDir", "VAEROUTE");
    m_VAeRouteBaseDir.SetWindowText(temp);

    m_DoWIeRM.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoWIeRM", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "WIeRMBaseDir", "WIRSTMGR");
    m_WIeRMBaseDir.SetWindowText(temp);

    m_DoWVeRM.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoWVeRM", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "WVeRMBaseDir", "WVRSTMGR");
    m_WVeRMBaseDir.SetWindowText(temp);

    // Data
    m_DoALData.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoALData", 0));
    m_DoARData.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoARData", 0));
    m_DoAZData.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoAZData", 0));
    m_DoCOData.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoCOData", 0));
    m_DoCTData.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoCTData", 0));
    m_DoGAData.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoGAData", 0));
    m_DoIAData.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoIAData", 0));
    m_DoILData.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoILData", 0));
    m_DoKYData.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoKYData", 0));
    m_DoLAData.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoLAData", 0));
    m_DoMDData.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoMDData", 0));
    m_DoMIData.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoMIData", 0));
    m_DoMOData.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoMOData", 0));
    m_DoNCData.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoNCData", 0));
    m_DoNEData.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoNEData", 0));
    m_DoNJData.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoNJData", 0));
    m_DoOHData.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoOHData", 0));
    m_DoORData.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoORData", 0));
    m_DoQLDData.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoQLDData", 0));
    m_DoSDData.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoSDData", 0));
    m_DoVAData.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoVAData", 0));
    m_DoWAData.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoWAData", 0));
    m_DoWIData.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoWIData", 0));
    m_DoWVData.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoWVData", 0));
    m_DoPASSDB.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoPASSDB", 0));

    // Address Data
    m_doCTAddress.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoCTAddress", 0));
    m_doMDAddress.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoMDAddress", 0));
    m_doNJAddress.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoNJAddress", 0));
    m_doQLDAddress.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoQLDAddress", 0));
    m_doVAAddress.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoVAAddress", 0));
    m_doWIAddress.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoWIAddress", 0));

    temp = AfxGetApp()->GetProfileString("Defaults", "PASSDBBaseDir", "C:\\INETPUB\\WWWROOT\\SUPER");
    m_PASSDBBaseDir.SetWindowText(temp);

    m_DoRestDB.SetCheck(AfxGetApp()->GetProfileInt("Defaults", "DoRestDB", 0));
    temp = AfxGetApp()->GetProfileString("Defaults", "RestDBBaseDir", "C:\\INETPUB\\WWWROOT\\SUPER");
    m_RestDBBaseDir.SetWindowText(temp);

    temp = AfxGetApp()->GetProfileString("Defaults", "WinSysDir", "C:\\WINDOWS\\SYSWOW64");
    m_WinSysDir.SetWindowText(temp);

    //Hopefully prevent issues with field not showing up
    Invalidate();
    UpdateWindow();

    return TRUE;  // return TRUE  unless you set the focus to a control
    }

/*------------------------------------------------------------------------------
* MODULE      OnOK (Update)
* PURPOSE     Runs the update process
*-------------------------------------------------------------------------------
* AUTHOR      Dan Vogen                  DATE 01-18-2003
* REVISION    DATE         NAME          DESCRIPTION
*-------------------------------------------------------------------------------
* ARGUMENTS   Type         Call Conv  Purpose
*-------------------------------------------------------------------------------
* CONDITION   Value        Description
* VALUES      None
* RETURNED
*-----------------------------------------------------------------------------*/
void CSuperupdDlg::OnOK()
    {
    int     endLoc;
    time_t  aclock;
    FILE*   fp;
    CString logFile;
    CString pathWindowsSystem;
    CString pathEPassBase;
    CString pathPassShared;
    CString pathTemp;
    CString pathDestination;
    CString updateFile;
    CString message;
    CString sourceLocation;
    CString dataLocation;
    struct tm* newtime;

    CWaitCursor wait;

    m_updateFile.GetWindowText(updateFile);

    if (!FileExist(updateFile, 0))
        {
        message.Format("%s\n\nCurrent File = %s", SUPERUPD_UPDATEFILE_ERROR, updateFile);
        AfxMessageBox(message);
        return;
        }

    m_sourceLocation.GetWindowText(sourceLocation);

    if (!ValidPath(sourceLocation))
        {
        message.Format("Program update location path does not exist or permission error.\n\nPath = %s", sourceLocation);
        AfxMessageBox(message);
        return;
        }

    m_dataLocation.GetWindowText(dataLocation);

    if (!ValidPath(dataLocation))
        {
        message.Format("Data update location path does not exist or permission error.\n\nPath = %s", dataLocation);
        AfxMessageBox(message);
        return;
        }

    //Delete the obsolete Log File INI value
    AfxGetApp()->WriteProfileString("Defaults", "LogFile", NULL);

    logFile = updateFile;
    logFile.MakeLower();

    if (0 < logFile.FindOneOf(".dat"))
        {
        logFile.Replace(".dat", ".log");
        }
    else
        {
        logFile.Append(".log");
        }

    if (FileExist(UPDATE_ERROR_FILE, 0))
        {
        remove(UPDATE_ERROR_FILE);
        }

    // PUT UPDATE MARKER IN LOG FILE
    time(&aclock);
    newtime = gmtime(&aclock);

    if (NULL == (fp = fopen(logFile, "a+")))
        {
        message.Format("Unable to open the update log file\n\nFile=%s", logFile);
        AfxMessageBox(message);
        return;
        }
    else
        {
        fclose(fp);
        }

    message.Format("Updating - %s GMT from %s and %s based on %s", asctime(newtime), sourceLocation, dataLocation, updateFile);

    if (message.Find(10, 0) > 0)
        {
        message.Delete(message.Find(10, 0));
        }

    AppendToLog(message, logFile);

    if (batchCreateOnly.GetCheck())
        {
        message.Format("Batch Creation ONLY", asctime(newtime));

        AppendToLog(message, logFile);
        }

    // PUT HEADER IN SUPERUPD.BAT
    if (NULL == (fp = fopen(UPDATE_SCRIPT, "w")))
        {
        message = UPDATE_SCRIPT_ERROR + UPDATE_SCRIPT;

        AppendToLog(message, logFile);

        AfxMessageBox(message);

        return;
        }

    fprintf(fp, "REM SUPERLOAD UPDATE SCRIPT\n");
    fclose(fp);

    // GET ALL THE CORE / BASE VALUES
    m_WinSysDir.GetWindowText(pathWindowsSystem);
    endLoc = pathWindowsSystem.GetLength() - 1;
    if ('\\' == pathWindowsSystem.GetAt(endLoc))
        {
        pathWindowsSystem.SetAt(endLoc, 0);
        }

    m_RouteBaseDir.GetWindowText(m_routeDir);
    endLoc = m_routeDir.GetLength() - 1;
    if ('\\' == m_routeDir.GetAt(endLoc))
        {
        m_routeDir.SetAt(endLoc, 0);
        }

    m_ePASSBaseDir.GetWindowText(pathEPassBase);
    endLoc = pathEPassBase.GetLength() - 1;
    if ('\\' == pathEPassBase.GetAt(endLoc))
        {
        pathEPassBase.SetAt(endLoc, 0);
        }

    m_ePASSSharedDir.GetWindowText(pathPassShared);
    endLoc = pathPassShared.GetLength() - 1;
    if ('\\' == pathPassShared.GetAt(endLoc))
        {
        pathPassShared.SetAt(endLoc, 0);
        }

    resetCommands();

    // ROUTE
    if (m_DoRoute.GetCheck() || updateESUPER())
        {
        AppendToLog("ROUTE, BRIDGE, RM", logFile, m_routeDir);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "Route", m_routeDir, pathPassShared, pathWindowsSystem, "*** UPDATING ROUTE, BRIDGE, RM ***");
        }

    if (m_DoMaintenanceMgr.GetCheck())
        {
        AppendToLog("MAINTENANCE MANAGER", logFile, m_routeDir);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "MM", m_routeDir, pathPassShared, pathWindowsSystem, "*** UPDATING MAINTENANCE MANAGER ***");
        }

    // PASS
    if (m_DoALPASS.GetCheck())
        {
        m_ALPASSBaseDir.GetWindowText(pathDestination);
        endLoc = pathDestination.GetLength() - 1;
        if ('\\' == pathDestination.GetAt(endLoc))
            {
            pathDestination.SetAt(endLoc, 0);
            }

        AppendToLog("AL-PASS", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "ALPASS", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING AL-PASS ***");
        }

    if (m_DoARPASS.GetCheck())
        {
        m_ARPASSBaseDir.GetWindowText(pathDestination);
        endLoc = pathDestination.GetLength() - 1;
        if ('\\' == pathDestination.GetAt(endLoc))
            {
            pathDestination.SetAt(endLoc, 0);
            }

        AppendToLog("ARPASS", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "ARPASS", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING AR-PASS ***");
        }

    if (m_DoCTPASS.GetCheck())
        {
        m_CTPASSBaseDir.GetWindowText(pathDestination);
        endLoc = pathDestination.GetLength() - 1;
        if ('\\' == pathDestination.GetAt(endLoc))
            {
            pathDestination.SetAt(endLoc, 0);
            }

        AppendToLog("CTPASS", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "CTPASS", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING CT-PASS ***");
        }

    if (m_DoNEPASS.GetCheck())
        {
        m_NEPASSBaseDir.GetWindowText(pathDestination);
        endLoc = pathDestination.GetLength() - 1;
        if ('\\' == pathDestination.GetAt(endLoc))
            {
            pathDestination.SetAt(endLoc, 0);
            }

        AppendToLog("NE-PASS", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "NEPASS", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING NE-PASS ***");
        }

    if (m_DoOHPASS.GetCheck())
        {
        m_OHPASSBaseDir.GetWindowText(pathDestination);
        endLoc = pathDestination.GetLength() - 1;
        if ('\\' == pathDestination.GetAt(endLoc))
            {
            pathDestination.SetAt(endLoc, 0);
            }

        AppendToLog("OH-PASS", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "OHPASS", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING OH-PASS ***");
        }

    if (m_DoSDPASS.GetCheck())
        {
        m_SDPASSBaseDir.GetWindowText(pathDestination);
        endLoc = pathDestination.GetLength() - 1;
        if ('\\' == pathDestination.GetAt(endLoc))
            {
            pathDestination.SetAt(endLoc, 0);
            }

        AppendToLog("SD-PASS", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "SDPASS", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING SD-PASS ***");
        }

    //Check if any eSL sites are being updated
    if (updateESUPER())
        {
        AppendToLog("BaseESuper", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "BaseESuper", "", pathPassShared, pathWindowsSystem, "*** UPDATING BaseESuper ***");
        }

    // ePASS
    if (updateEPASS())
        {
        AppendToLog("BaseEpass", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "BaseEpass", "", pathPassShared, pathWindowsSystem, "*** UPDATING BaseEpass ***");
        }

    if (m_DoALePASS.GetCheck())
        {
        m_ALePASSBaseDir.GetWindowText(pathTemp);
        endLoc = pathTemp.GetLength() - 1;
        if ('\\' == pathTemp.GetAt(endLoc))
            {
            pathTemp.SetAt(endLoc, 0);
            }

        pathDestination.Format("%s\\%s", pathEPassBase, pathTemp);
        AppendToLog("AL-ePASS V2", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "ALePASS", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING AL-ePASS V2 ***");
        }

    if (m_DoARePASS.GetCheck())
        {
        m_ARePASSBaseDir.GetWindowText(pathTemp);
        endLoc = pathTemp.GetLength() - 1;
        if ('\\' == pathTemp.GetAt(endLoc))
            {
            pathTemp.SetAt(endLoc, 0);
            }

        pathDestination.Format("%s\\%s", pathEPassBase, pathTemp);
        AppendToLog("AR-ePASS", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "ARePASS", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING AR-ePASS ***");
        }

    if (m_DoAZePASS.GetCheck())
        {
        m_AZePASSBaseDir.GetWindowText(pathTemp);
        endLoc = pathTemp.GetLength() - 1;
        if ('\\' == pathTemp.GetAt(endLoc))
            {
            pathTemp.SetAt(endLoc, 0);
            }

        pathDestination.Format("%s\\%s", pathEPassBase, pathTemp);
        AppendToLog("AZ-ePASS", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "AZePASS", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING AZ-ePASS ***");
        }

    if (m_DoCTePASS.GetCheck())
        {
        m_CTePASSBaseDir.GetWindowText(pathTemp);
        endLoc = pathTemp.GetLength() - 1;
        if ('\\' == pathTemp.GetAt(endLoc))
            {
            pathTemp.SetAt(endLoc, 0);
            }

        pathDestination.Format("%s\\%s", pathEPassBase, pathTemp);
        AppendToLog("CT-ePASS", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "CTePASS", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING CT-ePASS ***");
        }

    if (m_DoIAePASS.GetCheck())
        {
        m_IAePASSBaseDir.GetWindowText(pathTemp);
        endLoc = pathTemp.GetLength() - 1;
        if ('\\' == pathTemp.GetAt(endLoc))
            {
            pathTemp.SetAt(endLoc, 0);
            }

        pathDestination.Format("%s\\%s", pathEPassBase, pathTemp);
        AppendToLog("IA-ePASS", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "IAePASS", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING IA-ePASS ***");
        }

    if (m_DoKYePASS.GetCheck())
        {
        m_KYePASSBaseDir.GetWindowText(pathTemp);
        endLoc = pathTemp.GetLength() - 1;
        if ('\\' == pathTemp.GetAt(endLoc))
            {
            pathTemp.SetAt(endLoc, 0);
            }

        pathDestination.Format("%s\\%s", pathEPassBase, pathTemp);
        AppendToLog("KY-ePASS", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "KYePASS", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING KY-ePASS ***");
        }

    if (m_DoMDePASS.GetCheck())
        {
        m_MDePASSBaseDir.GetWindowText(pathTemp);
        endLoc = pathTemp.GetLength() - 1;
        if ('\\' == pathTemp.GetAt(endLoc))
            {
            pathTemp.SetAt(endLoc, 0);
            }

        pathDestination.Format("%s\\%s", pathEPassBase, pathTemp);
        AppendToLog("MD-ePASS", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "MDePASS", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING MD-ePASS ***");
        }

    if (m_DoMIePASS.GetCheck())
        {
        m_MIePASSBaseDir.GetWindowText(pathTemp);
        endLoc = pathTemp.GetLength() - 1;
        if ('\\' == pathTemp.GetAt(endLoc))
            {
            pathTemp.SetAt(endLoc, 0);
            }

        pathDestination.Format("%s\\%s", pathEPassBase, pathTemp);
        AppendToLog("MI-ePASS", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "MIePASS", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING MI-ePASS ***");
        }

    if (m_DoMOePASS.GetCheck())
        {
        m_MOePASSBaseDir.GetWindowText(pathTemp);
        endLoc = pathTemp.GetLength() - 1;
        if ('\\' == pathTemp.GetAt(endLoc))
            {
            pathTemp.SetAt(endLoc, 0);
            }

        pathDestination.Format("%s\\%s", pathEPassBase, pathTemp);
        AppendToLog("MO-ePASS", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "MOePASS", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING MO-ePASS ***");
        }

    if (m_DoNEePASS.GetCheck())
        {
        m_NEePASSBaseDir.GetWindowText(pathTemp);
        endLoc = pathTemp.GetLength() - 1;
        if ('\\' == pathTemp.GetAt(endLoc))
            {
            pathTemp.SetAt(endLoc, 0);
            }

        pathDestination.Format("%s\\%s", pathEPassBase, pathTemp);
        AppendToLog("NE-ePASS", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "NEePASS", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING NE-ePASS ***");
        }

    if (m_DoNJePASS.GetCheck())
        {
        m_NJePASSBaseDir.GetWindowText(pathTemp);
        endLoc = pathTemp.GetLength() - 1;
        if ('\\' == pathTemp.GetAt(endLoc))
            {
            pathTemp.SetAt(endLoc, 0);
            }

        pathDestination.Format("%s\\%s", pathEPassBase, pathTemp);
        AppendToLog("NJ-ePASS2", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "NJePASS", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING NJ-ePASS 2 ***");
        }

    if (m_DoOHePASS.GetCheck())
        {
        m_OHePASSBaseDir.GetWindowText(pathTemp);
        endLoc = pathTemp.GetLength() - 1;
        if ('\\' == pathTemp.GetAt(endLoc))
            {
            pathTemp.SetAt(endLoc, 0);
            }

        pathDestination.Format("%s\\%s", pathEPassBase, pathTemp);
        AppendToLog("OH-ePASS", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "OHePASS", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING OH-ePASS ***");
        }

    if (m_DoMultiState.GetCheck())
        {
        m_MultiStateBaseDir.GetWindowText(pathTemp);
        endLoc = pathTemp.GetLength() - 1;
        if ('\\' == pathTemp.GetAt(endLoc))
            {
            pathTemp.SetAt(endLoc, 0);
            }

        pathDestination.Format("%s\\%s", pathEPassBase, pathTemp);
        AppendToLog("MSPORTAL", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "MSPortal", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING MSPORTAL ***");
        }

    if (m_DoQLDePASS.GetCheck())
        {
        m_QLDePASSBaseDir.GetWindowText(pathTemp);
        endLoc = pathTemp.GetLength() - 1;
        if ('\\' == pathTemp.GetAt(endLoc))
            {
            pathTemp.SetAt(endLoc, 0);
            }

        pathDestination.Format("%s\\%s", pathEPassBase, pathTemp);
        AppendToLog("QLD-ePASS", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "QLDePASS", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING QLD-ePASS ***");
        }

    if (m_DoSDePASS.GetCheck())
        {
        m_SDePASSBaseDir.GetWindowText(pathTemp);
        endLoc = pathTemp.GetLength() - 1;
        if ('\\' == pathTemp.GetAt(endLoc))
            {
            pathTemp.SetAt(endLoc, 0);
            }

        pathDestination.Format("%s\\%s", pathEPassBase, pathTemp);
        AppendToLog("SD-ePASS", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "SDePASS", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING SD-ePASS ***");
        }

    if (m_DoVAeRoute.GetCheck())
        {
        m_VAeRouteBaseDir.GetWindowText(pathTemp);
        endLoc = pathTemp.GetLength() - 1;
        if ('\\' == pathTemp.GetAt(endLoc))
            {
            pathTemp.SetAt(endLoc, 0);
            }

        pathDestination.Format("%s\\%s", pathEPassBase, pathTemp);
        AppendToLog("VA-eRoute", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "VAeRoute", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING VA-eRoute ***");
        }

    if (m_DoWIeRoute.GetCheck())
        {
        m_WIeRouteBaseDir.GetWindowText(pathTemp);
        endLoc = pathTemp.GetLength() - 1;
        if ('\\' == pathTemp.GetAt(endLoc))
            {
            pathTemp.SetAt(endLoc, 0);
            }

        pathDestination.Format("%s\\%s", pathEPassBase, pathTemp);
        AppendToLog("WI-eRoute", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "WIeRoute", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING WI-eRoute ***");
        }

    if (m_DoWVePASS.GetCheck())
        {
        m_WVePASSBaseDir.GetWindowText(pathTemp);
        endLoc = pathTemp.GetLength() - 1;
        if ('\\' == pathTemp.GetAt(endLoc))
            {
            pathTemp.SetAt(endLoc, 0);
            }

        pathDestination.Format("%s\\%s", pathEPassBase, pathTemp);
        AppendToLog("WV-ePASS", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "WVePASS", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING WV-ePASS ***");
        }

    // eRM
    if (updateERM())
        {
        AppendToLog("BaseERM", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "BaseERM", "", pathPassShared, pathWindowsSystem, "*** UPDATING BaseERM ***");
        }

    if (m_DoALeRM.GetCheck())
        {
        m_ALeRMBaseDir.GetWindowText(pathTemp);
        endLoc = pathTemp.GetLength() - 1;
        if ('\\' == pathTemp.GetAt(endLoc))
            {
            pathTemp.SetAt(endLoc, 0);
            }

        pathDestination.Format("%s\\%s", pathEPassBase, pathTemp);
        AppendToLog("AL-eRM", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "ALeRM", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING AL-eRM ***");
        }

    if (m_DoAReRM.GetCheck())
        {
        m_AReRMBaseDir.GetWindowText(pathTemp);
        endLoc = pathTemp.GetLength() - 1;
        if ('\\' == pathTemp.GetAt(endLoc))
            {
            pathTemp.SetAt(endLoc, 0);
            }

        pathDestination.Format("%s\\%s", pathEPassBase, pathTemp);
        AppendToLog("AR-eRM", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "AReRM", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING AR-eRM ***");
        }

    if (m_DoAZeRM.GetCheck())
        {
        m_AZeRMBaseDir.GetWindowText(pathTemp);
        endLoc = pathTemp.GetLength() - 1;
        if ('\\' == pathTemp.GetAt(endLoc))
            {
            pathTemp.SetAt(endLoc, 0);
            }

        pathDestination.Format("%s\\%s", pathEPassBase, pathTemp);
        AppendToLog("AR-eRM", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "AZeRM", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING AZ-eRM ***");
        }

    if (m_DoCTeRM.GetCheck())
        {
        m_CTeRMBaseDir.GetWindowText(pathTemp);
        endLoc = pathTemp.GetLength() - 1;
        if ('\\' == pathTemp.GetAt(endLoc))
            {
            pathTemp.SetAt(endLoc, 0);
            }

        pathDestination.Format("%s\\%s", pathEPassBase, pathTemp);
        AppendToLog("CT-eRM", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "CTeRM", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING CT-eRM ***");
        }

    if (m_DoIAeRM.GetCheck())
        {
        m_IAeRMBaseDir.GetWindowText(pathTemp);
        endLoc = pathTemp.GetLength() - 1;
        if ('\\' == pathTemp.GetAt(endLoc))
            {
            pathTemp.SetAt(endLoc, 0);
            }

        pathDestination.Format("%s\\%s", pathEPassBase, pathTemp);
        AppendToLog("IA-eRM", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "IAeRM", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING IA-eRM ***");
        }

    if (m_DoKYeRM.GetCheck())
        {
        m_KYeRMBaseDir.GetWindowText(pathTemp);
        endLoc = pathTemp.GetLength() - 1;
        if ('\\' == pathTemp.GetAt(endLoc))
            {
            pathTemp.SetAt(endLoc, 0);
            }

        pathDestination.Format("%s\\%s", pathEPassBase, pathTemp);
        AppendToLog("KY-eRM", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "KYeRM", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING KY-eRM ***");
        }

    if (m_DoMDeRM.GetCheck())
        {
        m_MDeRMBaseDir.GetWindowText(pathTemp);
        endLoc = pathTemp.GetLength() - 1;
        if ('\\' == pathTemp.GetAt(endLoc))
            {
            pathTemp.SetAt(endLoc, 0);
            }

        pathDestination.Format("%s\\%s", pathEPassBase, pathTemp);
        AppendToLog("MD-eRM", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "MDeRM", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING MD-eRM ***");
        }

    if (m_DoMIeRM.GetCheck())
        {
        m_MIeRMBaseDir.GetWindowText(pathTemp);
        endLoc = pathTemp.GetLength() - 1;
        if ('\\' == pathTemp.GetAt(endLoc))
            {
            pathTemp.SetAt(endLoc, 0);
            }

        pathDestination.Format("%s\\%s", pathEPassBase, pathTemp);
        AppendToLog("MI-eRM", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "MIeRM", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING MI-eRM ***");
        }

    if (m_DoMOeRM.GetCheck())
        {
        m_MOeRMBaseDir.GetWindowText(pathTemp);
        endLoc = pathTemp.GetLength() - 1;
        if ('\\' == pathTemp.GetAt(endLoc))
            {
            pathTemp.SetAt(endLoc, 0);
            }

        pathDestination.Format("%s\\%s", pathEPassBase, pathTemp);
        AppendToLog("MO-eRM", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "MOeRM", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING MO-eRM ***");
        }

    if (m_DoNCeRM.GetCheck())
        {
        m_NCeRMBaseDir.GetWindowText(pathTemp);
        endLoc = pathTemp.GetLength() - 1;
        if ('\\' == pathTemp.GetAt(endLoc))
            {
            pathTemp.SetAt(endLoc, 0);
            }

        pathDestination.Format("%s\\%s", pathEPassBase, pathTemp);
        AppendToLog("NC-eRM", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "NCeRM", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING NC-eRM ***");
        }

    if (m_DoNEeRM.GetCheck())
        {
        m_NEeRMBaseDir.GetWindowText(pathTemp);
        endLoc = pathTemp.GetLength() - 1;
        if ('\\' == pathTemp.GetAt(endLoc))
            {
            pathTemp.SetAt(endLoc, 0);
            }

        pathDestination.Format("%s\\%s", pathEPassBase, pathTemp);
        AppendToLog("NE-eRM", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "NEeRM", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING NE-eRM ***");
        }

    if (m_DoNJeRM.GetCheck())
        {
        m_NJeRMBaseDir.GetWindowText(pathTemp);
        endLoc = pathTemp.GetLength() - 1;
        if ('\\' == pathTemp.GetAt(endLoc))
            {
            pathTemp.SetAt(endLoc, 0);
            }

        pathDestination.Format("%s\\%s", pathEPassBase, pathTemp);
        AppendToLog("NJ-eRM", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "NJeRM", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING NJ-eRM ***");
        }

    if (m_DoOHeRM.GetCheck())
        {
        m_OHeRMBaseDir.GetWindowText(pathTemp);
        endLoc = pathTemp.GetLength() - 1;
        if ('\\' == pathTemp.GetAt(endLoc))
            {
            pathTemp.SetAt(endLoc, 0);
            }

        pathDestination.Format("%s\\%s", pathEPassBase, pathTemp);
        AppendToLog("OH-eRM", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "OHeRM", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING OH-eRM ***");
        }

    if (m_DoQLDeRM.GetCheck())
        {
        m_QLDeRMBaseDir.GetWindowText(pathTemp);
        endLoc = pathTemp.GetLength() - 1;
        if ('\\' == pathTemp.GetAt(endLoc))
            {
            pathTemp.SetAt(endLoc, 0);
            }

        pathDestination.Format("%s\\%s", pathEPassBase, pathTemp);
        AppendToLog("QLD-eRM", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "QLDeRM", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING QLD-eRM ***");
        }

    if (m_DoSDeRM.GetCheck())
        {
        m_SDeRMBaseDir.GetWindowText(pathTemp);
        endLoc = pathTemp.GetLength() - 1;
        if ('\\' == pathTemp.GetAt(endLoc))
            {
            pathTemp.SetAt(endLoc, 0);
            }

        pathDestination.Format("%s\\%s", pathEPassBase, pathTemp);
        AppendToLog("SD-eRM", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "SDeRM", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING SD-eRM ***");
        }

    if (m_DoVAeRM.GetCheck())
        {
        m_VAeRMBaseDir.GetWindowText(pathTemp);
        endLoc = pathTemp.GetLength() - 1;
        if ('\\' == pathTemp.GetAt(endLoc))
            {
            pathTemp.SetAt(endLoc, 0);
            }

        pathDestination.Format("%s\\%s", pathEPassBase, pathTemp);
        AppendToLog("VA-eRM", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "VAeRM", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING VA-eRM ***");
        }

    if (m_DoWIeRM.GetCheck())
        {
        m_WIeRMBaseDir.GetWindowText(pathTemp);
        endLoc = pathTemp.GetLength() - 1;
        if ('\\' == pathTemp.GetAt(endLoc))
            {
            pathTemp.SetAt(endLoc, 0);
            }

        pathDestination.Format("%s\\%s", pathEPassBase, pathTemp);
        AppendToLog("WI-eRM", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "WIeRM", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING WI-eRM ***");
        }

    if (m_DoWVeRM.GetCheck())
        {
        m_WVeRMBaseDir.GetWindowText(pathTemp);
        endLoc = pathTemp.GetLength() - 1;
        if ('\\' == pathTemp.GetAt(endLoc))
            {
            pathTemp.SetAt(endLoc, 0);
            }

        pathDestination.Format("%s\\%s", pathEPassBase, pathTemp);
        AppendToLog("WV-eRM", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "WVeRM", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING WV-eRM ***");
        }


    // DATA
    bool    dateDependent;
    CString updateMessage;

    if (m_DoALData.GetCheck() || m_DoALePASS.GetCheck() || m_DoALeRM.GetCheck() || m_DoMultiState.GetCheck())
        {
        //Use date dependent if not specifically requesting data
        dateDependent = false;
        updateMessage = "";

        if (!m_DoALData.GetCheck())
            {
            dateDependent = true;
            updateMessage = UPDATE_BY_DATE;
            }

        AppendToLog("AL DATA", logFile, m_routeDir, updateMessage);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "ALData", m_routeDir, pathPassShared, pathWindowsSystem, "*** UPDATING AL DATA ***", dateDependent);
        }

    if (m_DoARData.GetCheck() || m_DoARePASS.GetCheck() || m_DoAReRM.GetCheck())
        {
        //Use date dependent if not specifically requesting data
        dateDependent = false;
        updateMessage = "";

        if (!m_DoARData.GetCheck())
            {
            dateDependent = true;
            updateMessage = UPDATE_BY_DATE;
            }

        AppendToLog("AR DATA", logFile, m_routeDir, updateMessage);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "ARData", m_routeDir, pathPassShared, pathWindowsSystem, "*** UPDATING AR DATA ***", dateDependent);
        }

    if (m_DoAZData.GetCheck() || m_DoAZePASS.GetCheck() || m_DoAZeRM.GetCheck())
        {
        //Use date dependent if not specifically requesting data
        dateDependent = false;
        updateMessage = "";

        if (!m_DoAZData.GetCheck())
            {
            dateDependent = true;
            updateMessage = UPDATE_BY_DATE;
            }

        AppendToLog("AZ DATA", logFile, m_routeDir, updateMessage);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "AZData", m_routeDir, pathPassShared, pathWindowsSystem, "*** UPDATING AZ DATA ***", dateDependent);
        }

    if (m_DoCOData.GetCheck())
        {
        dateDependent = false;
        updateMessage = "";

        AppendToLog("CO DATA", logFile, m_routeDir, updateMessage);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "COData", m_routeDir, pathPassShared, pathWindowsSystem, "*** UPDATING CO DATA ***", dateDependent);
        }

    if (m_DoCTData.GetCheck() || m_DoCTePASS.GetCheck() || m_DoCTeRM.GetCheck())
        {
        //Use date dependent if not specifically requesting data
        dateDependent = false;
        updateMessage = "";

        if (!m_DoCTData.GetCheck())
            {
            dateDependent = true;
            updateMessage = UPDATE_BY_DATE;
            }

        AppendToLog("CT DATA", logFile, m_routeDir, updateMessage);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "CTData", m_routeDir, pathPassShared, pathWindowsSystem, "*** UPDATING CT DATA ***", dateDependent);
        }

    if (m_DoGAData.GetCheck())
        {
        //Use date dependent if not specifically requesting data
        dateDependent = false;
        updateMessage = "";

        if (!m_DoGAData.GetCheck())
            {
            dateDependent = true;
            updateMessage = UPDATE_BY_DATE;
            }

        AppendToLog("GA DATA", logFile, m_routeDir, updateMessage);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "GAData", m_routeDir, pathPassShared, pathWindowsSystem, "*** UPDATING GA DATA ***", dateDependent);
        }

    if (m_DoIAData.GetCheck() || m_DoIAePASS.GetCheck() || m_DoIAeRM.GetCheck())
        {
        //Use date dependent if not specifically requesting data
        dateDependent = false;
        updateMessage = "";

        if (!m_DoIAData.GetCheck())
            {
            dateDependent = true;
            updateMessage = UPDATE_BY_DATE;
            }

        AppendToLog("IA DATA", logFile, m_routeDir, updateMessage);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "IAData", m_routeDir, pathPassShared, pathWindowsSystem, "*** UPDATING IA DATA ***", dateDependent);
        }

    if (m_DoILData.GetCheck())
        {
        dateDependent = false;
        updateMessage = "";

        AppendToLog("IL DATA", logFile, m_routeDir, updateMessage);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "ILData", m_routeDir, pathPassShared, pathWindowsSystem, "*** UPDATING IL DATA ***", dateDependent);
        }

    if (m_DoKYData.GetCheck() || m_DoKYePASS.GetCheck() || m_DoKYeRM.GetCheck())
        {
        //Use date dependent if not specifically requesting data
        dateDependent = false;
        updateMessage = "";

        if (!m_DoKYData.GetCheck())
            {
            dateDependent = true;
            updateMessage = UPDATE_BY_DATE;
            }

        AppendToLog("KY DATA", logFile, m_routeDir, updateMessage);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "KYData", m_routeDir, pathPassShared, pathWindowsSystem, "*** UPDATING KY DATA ***", dateDependent);
        }

    if (m_DoLAData.GetCheck())
        {
        //Use date dependent if not specifically requesting data
        dateDependent = false;
        updateMessage = "";

        if (!m_DoLAData.GetCheck())
            {
            dateDependent = true;
            updateMessage = UPDATE_BY_DATE;
            }

        AppendToLog("LA DATA", logFile, m_routeDir, updateMessage);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "LAData", m_routeDir, pathPassShared, pathWindowsSystem, "*** UPDATING LA DATA ***", dateDependent);
        }

    if (m_DoMDData.GetCheck() || m_DoMDePASS.GetCheck() || m_DoMDeRM.GetCheck())
        {
        //Use date dependent if not specifically requesting data
        dateDependent = false;
        updateMessage = "";

        if (!m_DoMDData.GetCheck())
            {
            dateDependent = true;
            updateMessage = UPDATE_BY_DATE;
            }

        AppendToLog("MD DATA", logFile, m_routeDir, updateMessage);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "MDData", m_routeDir, pathPassShared, pathWindowsSystem, "*** UPDATING MD DATA ***", dateDependent);
        }

    if (m_DoMIData.GetCheck() || m_DoMIePASS.GetCheck() || m_DoMIeRM.GetCheck())
        {
        //Use date dependent if not specifically requesting data
        dateDependent = false;
        updateMessage = "";

        if (!m_DoMIData.GetCheck())
            {
            dateDependent = true;
            updateMessage = UPDATE_BY_DATE;
            }

        AppendToLog("MI DATA", logFile, m_routeDir, updateMessage);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "MIData", m_routeDir, pathPassShared, pathWindowsSystem, "*** UPDATING MI DATA ***", dateDependent);
        }

    if (m_DoMOData.GetCheck() || m_DoMOePASS.GetCheck() || m_DoMOeRM.GetCheck())
        {
        //Use date dependent if not specifically requesting data
        dateDependent = false;
        updateMessage = "";

        if (!m_DoMOData.GetCheck())
            {
            dateDependent = true;
            updateMessage = UPDATE_BY_DATE;
            }

        AppendToLog("MO DATA", logFile, m_routeDir, updateMessage);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "MOData", m_routeDir, pathPassShared, pathWindowsSystem, "*** UPDATING MO DATA ***", dateDependent);
        }

    if (m_DoNCData.GetCheck() || m_DoNCeRM.GetCheck())
        {
        //Use date dependent if not specifically requesting data
        dateDependent = false;
        updateMessage = "";

        if (!m_DoNCData.GetCheck())
            {
            dateDependent = true;
            updateMessage = UPDATE_BY_DATE;
            }

        AppendToLog("NC DATA", logFile, m_routeDir, updateMessage);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "NCData", m_routeDir, pathPassShared, pathWindowsSystem, "*** UPDATING NC DATA ***", dateDependent);
        }

    if (m_DoNEData.GetCheck() || m_DoNEePASS.GetCheck() || m_DoNEeRM.GetCheck() || m_DoMultiState.GetCheck())
        {
        //Use date dependent if not specifically requesting data
        dateDependent = false;
        updateMessage = "";

        if (!m_DoNEData.GetCheck())
            {
            dateDependent = true;
            updateMessage = UPDATE_BY_DATE;
            }

        AppendToLog("NE DATA", logFile, m_routeDir, updateMessage);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "NEData", m_routeDir, pathPassShared, pathWindowsSystem, "*** UPDATING NE DATA ***", dateDependent);
        }

    if (m_DoNJData.GetCheck() || m_DoNJePASS.GetCheck() || m_DoNJeRM.GetCheck() || m_DoMultiState.GetCheck())
        {
        //Use date dependent if not specifically requesting data
        dateDependent = false;
        updateMessage = "";

        if (!m_DoNJData.GetCheck())
            {
            dateDependent = true;
            updateMessage = UPDATE_BY_DATE;
            }

        AppendToLog("NJ DATA", logFile, m_routeDir, updateMessage);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "NJData", m_routeDir, pathPassShared, pathWindowsSystem, "*** UPDATING NJ DATA ***", dateDependent);
        }

    if (m_DoOHData.GetCheck() || m_DoOHePASS.GetCheck() || m_DoOHeRM.GetCheck() || m_DoMultiState.GetCheck())
        {
        //Use date dependent if not specifically requesting data
        dateDependent = false;
        updateMessage = "";

        if (!m_DoOHData.GetCheck())
            {
            dateDependent = true;
            updateMessage = UPDATE_BY_DATE;
            }

        AppendToLog("OH DATA", logFile, m_routeDir, updateMessage);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "OHData", m_routeDir, pathPassShared, pathWindowsSystem, "*** UPDATING OH DATA ***", dateDependent);
        }

    if (m_DoORData.GetCheck())
        {
        dateDependent = false;
        updateMessage = "";

        AppendToLog("OR DATA", logFile, m_routeDir, updateMessage);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "ORData", m_routeDir, pathPassShared, pathWindowsSystem, "*** UPDATING OR DATA ***", dateDependent);
        }

    if (m_DoQLDData.GetCheck() || m_DoQLDePASS.GetCheck() || m_DoQLDeRM.GetCheck() || m_DoMultiState.GetCheck())
        {
        //Use date dependent if not specifically requesting data
        dateDependent = false;
        updateMessage = "";

        if (!m_DoQLDData.GetCheck())
            {
            dateDependent = true;
            updateMessage = UPDATE_BY_DATE;
            }

        AppendToLog("QLD DATA", logFile, m_routeDir, updateMessage);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "QLDData", m_routeDir, pathPassShared, pathWindowsSystem, "*** UPDATING QLD DATA ***", dateDependent);
        }

    if (m_DoSDData.GetCheck() || m_DoSDePASS.GetCheck() || m_DoSDeRM.GetCheck() || m_DoMultiState.GetCheck())
        {
        //Use date dependent if not specifically requesting data
        dateDependent = false;
        updateMessage = "";

        if (!m_DoSDData.GetCheck())
            {
            dateDependent = true;
            updateMessage = UPDATE_BY_DATE;
            }

        AppendToLog("SD DATA", logFile, m_routeDir, updateMessage);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "SDData", m_routeDir, pathPassShared, pathWindowsSystem, "*** UPDATING SD DATA ***", dateDependent);
        }

    if (m_DoVAData.GetCheck() || m_DoVAeRM.GetCheck() || m_DoVAeRoute.GetCheck())
        {
        //Use date dependent if not specifically requesting data
        dateDependent = false;
        updateMessage = "";

        if (!m_DoVAData.GetCheck())
            {
            dateDependent = true;
            updateMessage = UPDATE_BY_DATE;
            }

        AppendToLog("VA DATA", logFile, m_routeDir, updateMessage);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "VAData", m_routeDir, pathPassShared, pathWindowsSystem, "*** UPDATING VA DATA ***", dateDependent);
        }

    if (m_DoWAData.GetCheck())
        {
        dateDependent = false;
        updateMessage = "";

        AppendToLog("WA DATA", logFile, m_routeDir, updateMessage);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "WAData", m_routeDir, pathPassShared, pathWindowsSystem, "*** UPDATING WA DATA ***", dateDependent);
        }

    if (m_DoWIData.GetCheck() || m_DoWIeRoute.GetCheck() || m_DoWIeRM.GetCheck())
        {
        //Use date dependent if not specifically requesting data
        dateDependent = false;
        updateMessage = "";

        if (!m_DoWIData.GetCheck())
            {
            dateDependent = true;
            updateMessage = UPDATE_BY_DATE;
            }

        AppendToLog("WI DATA", logFile, m_routeDir, updateMessage);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "WIData", m_routeDir, pathPassShared, pathWindowsSystem, "*** UPDATING WI DATA ***", dateDependent);
        }

    if (m_DoWVData.GetCheck() || m_DoWVePASS.GetCheck() || m_DoWVeRM.GetCheck() || m_DoMultiState.GetCheck())
        {
        //Use date dependent if not specifically requesting data
        dateDependent = false;
        updateMessage = "";

        if (!m_DoWVData.GetCheck())
            {
            dateDependent = true;
            updateMessage = UPDATE_BY_DATE;
            }

        AppendToLog("WV DATA", logFile, m_routeDir, updateMessage);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "WVData", m_routeDir, pathPassShared, pathWindowsSystem, "*** UPDATING WV DATA ***", dateDependent);
        }

    // Address Data
    dateDependent = false;

    if (m_doCTAddress.GetCheck())
        {
        AppendToLog("CT ADDRESS", logFile, m_routeDir, "");
        AddToUpdate(updateFile, sourceLocation, dataLocation, "CTAddress", m_routeDir, pathPassShared, pathWindowsSystem, "*** UPDATING CT ADDRESS DATA ***", dateDependent);
        }

    if (m_doMDAddress.GetCheck())
        {
        AppendToLog("MD ADDRESS", logFile, m_routeDir, "");
        AddToUpdate(updateFile, sourceLocation, dataLocation, "MDAddress", m_routeDir, pathPassShared, pathWindowsSystem, "*** UPDATING MD ADDRESS DATA ***", dateDependent);
        }

    if (m_doNJAddress.GetCheck())
        {
        AppendToLog("NJ ADDRESS", logFile, m_routeDir, "");
        AddToUpdate(updateFile, sourceLocation, dataLocation, "NJAddress", m_routeDir, pathPassShared, pathWindowsSystem, "*** UPDATING NJ ADDRESS DATA ***", dateDependent);
        }

    if (m_doQLDAddress.GetCheck())
        {
        AppendToLog("QLD ADDRESS", logFile, m_routeDir, "");
        AddToUpdate(updateFile, sourceLocation, dataLocation, "QLDAddress", m_routeDir, pathPassShared, pathWindowsSystem, "*** UPDATING QLD ADDRESS DATA ***", dateDependent);
        }

    if (m_doVAAddress.GetCheck())
        {
        AppendToLog("VA ADDRESS", logFile, m_routeDir, "");
        AddToUpdate(updateFile, sourceLocation, dataLocation, "VAAddress", m_routeDir, pathPassShared, pathWindowsSystem, "*** UPDATING VA ADDRESS DATA ***", dateDependent);
        }

    if (m_doWIAddress.GetCheck())
        {
        AppendToLog("WI ADDRESS", logFile, m_routeDir, "");
        AddToUpdate(updateFile, sourceLocation, dataLocation, "WIAddress", m_routeDir, pathPassShared, pathWindowsSystem, "*** UPDATING WI ADDRESS DATA ***", dateDependent);
        }

    if (m_DoPASSDB.GetCheck())
        {
        m_PASSDBBaseDir.GetWindowText(pathDestination);

        if ("\\" != pathDestination.Right(1))
            {
            pathDestination += "\\";
            }

        AppendToLog("PASS DB", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "PASSDB", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING PASS DB ***");
        }

    if (m_DoRestDB.GetCheck())
        {
        m_RestDBBaseDir.GetWindowText(pathDestination);

        if ("\\" != pathDestination.Right(1))
            {
            pathDestination += "\\";
            }

        AppendToLog("Restrictions DB", logFile, pathDestination);
        AddToUpdate(updateFile, sourceLocation, dataLocation, "RstrctnDB", pathDestination, pathPassShared, pathWindowsSystem, "*** UPDATING RESTRICTIONS DB ***");
        }

    if (updateESUPER())
        {
        AppendToLog("BaseESuperClean", logFile, "");
        AddToUpdate(updateFile, sourceLocation, dataLocation, "BaseESuperClean", "", pathPassShared, pathWindowsSystem, "*** UPDATING BaseESuperClean ***");
        }

    // PUT A WAIT AT THE END IN SUPERUPD.BAT
    if (NULL == (fp = fopen(UPDATE_SCRIPT, "a+")))
        {
        message = UPDATE_SCRIPT_ERROR + UPDATE_SCRIPT;

        AppendToLog(message, logFile);

        AfxMessageBox(message);
        return;
        }

    if (0 != AfxGetApp()->GetProfileInt("Defaults", "Pause", 0))
        {
        fprintf(fp, "PAUSE\n");
        }

    fclose(fp);

    if (0 == batchCreateOnly.GetCheck())
        {
        // RUN THE UPDATE SCRIPT
        STARTUPINFO si = {0};
        PROCESS_INFORMATION pi = {0};

        si.cb = sizeof(STARTUPINFO);
        si.lpReserved = NULL;
        si.lpReserved2 = NULL;
        si.cbReserved2 = 0;
        si.lpDesktop = NULL;
        si.dwFlags = 0;

        time_t start, finish;
        double elapsed_time;

        time(&start);
        CString temp = UPDATE_SCRIPT;
        CreateProcess(NULL, temp.GetBuffer(0), NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi);
        WaitForSingleObject(pi.hProcess, INFINITE);

        time(&finish);
        elapsed_time = difftime(finish, start);
        newtime = gmtime(&finish);
        message.Format("Complete - %s GMT(ET=%.2f m)", asctime(newtime), elapsed_time / 60);
        if (0 < message.Find(10, 0))
            {
            message.Delete(message.Find(10, 0));
            }

        AppendToLog(message, logFile);

        // Check if superupd.err file exists and notify user
        if (FileExist(UPDATE_ERROR_FILE, 0))
            {
            LPCWBINIT lpcwbinit;
            LPCWBADDF lpcwbaddf;
            LPCWBDISP lpcwbdisp;

            //O pen the reporter dialog and show the report
            ReporterSetup::InitializeReporter(&lpcwbinit, &lpcwbaddf, &lpcwbdisp);

            if (NULL != lpcwbaddf && NULL != lpcwbdisp)
                {
                CString temp = UPDATE_ERROR_FILE;
                lpcwbaddf("", temp.GetBuffer(0), "Portrait");
                lpcwbdisp();

                // Free the DLL since it's updated as part of the updates
                if (NULL != hSLPrintDLL)
                    {
                    FreeLibrary(hSLPrintDLL);
                    hSLPrintDLL = NULL;
                    }
                }
            }
        else if (0 == AfxGetApp()->GetProfileInt("Defaults", "Pause", 0))
            {
            AfxMessageBox("SUPERUPD Update process has completed successfully.", MB_ICONINFORMATION);
            }
        }
    else
        {
        message = UPDATE_SCRIPT_SUCCESS + UPDATE_SCRIPT;
        AppendToLog(message, logFile);
        AfxMessageBox(message, MB_ICONINFORMATION);
        }
    }

/*------------------------------------------------------------------------------
* MODULE      OnSaveSettings
* PURPOSE     Saves the current dialog settings to ini
*-------------------------------------------------------------------------------
* AUTHOR      Dan Vogen                  DATE 01-18-2003
* REVISION    DATE         NAME          DESCRIPTION
*-------------------------------------------------------------------------------
* ARGUMENTS   Type         Call Conv  Purpose
*-------------------------------------------------------------------------------
* CONDITION   Value        Description
* VALUES      None
* RETURNED
*-----------------------------------------------------------------------------*/
void CSuperupdDlg::OnSaveSettings()
    {
    bool    writeINIerror = false;
    CString temp;

    //
    // SAVE ALL OF THE CURRENT VALUES FROM THE DLG TO THE INI
    //
    m_sourceLocation.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("SourceLocations", "UpdateSource", temp))
        {
        writeINIerror = true;
        }
    addSourceLocation(temp);

    m_dataLocation.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("DataLocations", "UpdateData", temp))
        {
        writeINIerror = true;
        }
    addDataLocation(temp);

    // ROUTE
    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoRoute", m_DoRoute.GetCheck()))
        {
        writeINIerror = true;
        }

    m_RouteBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "RouteBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoMaintenanceMgr", m_DoMaintenanceMgr.GetCheck()))
        {
        writeINIerror = true;
        }

    // PASS
    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoALPASS", m_DoALPASS.GetCheck()))
        {
        writeINIerror = true;
        }

    m_ALPASSBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "ALPASSBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoARPASS", m_DoARPASS.GetCheck()))
        {
        writeINIerror = true;
        }

    m_ARPASSBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "ARPASSBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoCTPASS", m_DoCTPASS.GetCheck()))
        {
        writeINIerror = true;
        }

    m_CTPASSBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "CTPASSBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoNEPASS", m_DoNEPASS.GetCheck()))
        {
        writeINIerror = true;
        }

    m_NEPASSBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "NEPASSBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoOHPASS", m_DoOHPASS.GetCheck()))
        {
        writeINIerror = true;
        }

    m_OHPASSBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "OHPASSBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoSDPASS", m_DoSDPASS.GetCheck()))
        {
        writeINIerror = true;
        }

    m_SDPASSBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "SDPASSBaseDir", temp))
        {
        writeINIerror = true;
        }

    // ePASS
    m_ePASSBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "ePASSBaseDir", temp))
        {
        writeINIerror = true;
        }

    m_ePASSSharedDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "ePASSSharedDir", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoALePASS", m_DoALePASS.GetCheck()))
        {
        writeINIerror = true;
        }

    m_ALePASSBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "ALePASSBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoARePASS", m_DoARePASS.GetCheck()))
        {
        writeINIerror = true;
        }

    m_ARePASSBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "ARePASSBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (false == AfxGetApp()->WriteProfileInt("Defaults", "DoAZePASS", m_DoAZePASS.GetCheck()))
        {
        writeINIerror = true;
        }

    m_AZePASSBaseDir.GetWindowText(temp);
    if (false == AfxGetApp()->WriteProfileString("Defaults", "AZePASSBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (false == AfxGetApp()->WriteProfileInt("Defaults", "DoCTePASS", m_DoCTePASS.GetCheck()))
        {
        writeINIerror = true;
        }

    m_CTePASSBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "CTePASSBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoIAePASS", m_DoIAePASS.GetCheck()))
        {
        writeINIerror = true;
        }

    m_IAePASSBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "IAePASSBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoKYePASS", m_DoKYePASS.GetCheck()))
        {
        writeINIerror = true;
        }

    m_KYePASSBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "KYePASSBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoMDePASS", m_DoMDePASS.GetCheck()))
        {
        writeINIerror = true;
        }

    m_MDePASSBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "MDePASSBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoMIePASS", m_DoMIePASS.GetCheck()))
        {
        writeINIerror = true;
        }

    m_MIePASSBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "MIePASSBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoMOePASS", m_DoMOePASS.GetCheck()))
        {
        writeINIerror = true;
        }

    m_MOePASSBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "MOePASSBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoNEePASS", m_DoNEePASS.GetCheck()))
        {
        writeINIerror = true;
        }

    m_NEePASSBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "NEePASSBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoNJePASS", m_DoNJePASS.GetCheck()))
        {
        writeINIerror = true;
        }

    m_NJePASSBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "boolBaseDir2", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoOHePASS", m_DoOHePASS.GetCheck()))
        {
        writeINIerror = true;
        }

    m_OHePASSBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "OHePASSBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoMultiState", m_DoMultiState.GetCheck()))
        {
        writeINIerror = true;
        }

    m_MultiStateBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "MultiStateBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoQLDePASS", m_DoQLDePASS.GetCheck()))
        {
        writeINIerror = true;
        }

    m_QLDePASSBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "QLDePASSBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoSDePASS", m_DoSDePASS.GetCheck()))
        {
        writeINIerror = true;
        }

    m_SDePASSBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "SDePASSBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoWIeRoute", m_DoWIeRoute.GetCheck()))
        {
        writeINIerror = true;
        }

    m_WIeRouteBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "WIeRouteBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoWVePASS", m_DoWVePASS.GetCheck()))
        {
        writeINIerror = true;
        }

    m_WVePASSBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "WVePASSBaseDir", temp))
        {
        writeINIerror = true;
        }

    // eRM
    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoALeRM", m_DoALeRM.GetCheck()))
        {
        writeINIerror = true;
        }

    m_ALeRMBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "ALeRMBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoAReRM", m_DoAReRM.GetCheck()))
        {
        writeINIerror = true;
        }

    m_AReRMBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "AReRMBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoAZeRM", m_DoAZeRM.GetCheck()))
        {
        writeINIerror = true;
        }

    m_AZeRMBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "AZeRMBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoCTeRM", m_DoCTeRM.GetCheck()))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoCTeRM", m_DoCTeRM.GetCheck()))
        {
        writeINIerror = true;
        }

    m_CTeRMBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "CTeRMBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoIAeRM", m_DoIAeRM.GetCheck()))
        {
        writeINIerror = true;
        }

    m_IAeRMBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "IAeRMBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoKYeRM", m_DoKYeRM.GetCheck()))
        {
        writeINIerror = true;
        }

    m_KYeRMBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "KYeRMBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoMDeRM", m_DoMDeRM.GetCheck()))
        {
        writeINIerror = true;
        }

    m_MDeRMBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "MDeRMBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoMIeRM", m_DoMIeRM.GetCheck()))
        {
        writeINIerror = true;
        }

    m_MIeRMBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "MIeRMBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoMOeRM", m_DoMOeRM.GetCheck()))
        {
        writeINIerror = true;
        }

    m_MOeRMBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "MOeRMBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoNCeRM", m_DoNCeRM.GetCheck()))
        {
        writeINIerror = true;
        }

    m_NCeRMBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "NCeRMBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoNEeRM", m_DoNEeRM.GetCheck()))
        {
        writeINIerror = true;
        }

    m_NEeRMBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "NEeRMBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoNJeRM", m_DoNJeRM.GetCheck()))
        {
        writeINIerror = true;
        }

    m_NJeRMBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "NJeRMBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoOHeRM", m_DoOHeRM.GetCheck()))
        {
        writeINIerror = true;
        }

    m_OHeRMBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "OHeRMBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoQLDeRM", m_DoQLDeRM.GetCheck()))
        {
        writeINIerror = true;
        }

    m_QLDeRMBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "QLDeRMBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoSDeRM", m_DoSDeRM.GetCheck()))
        {
        writeINIerror = true;
        }

    m_SDeRMBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "SDeRMBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoVAeRM", m_DoVAeRM.GetCheck()))
        {
        writeINIerror = true;
        }

    m_VAeRMBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "VAeRMBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoVAeRoute", m_DoVAeRoute.GetCheck()))
        {
        writeINIerror = true;
        }

    m_VAeRouteBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "VAeRouteBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoWIeRM", m_DoWIeRM.GetCheck()))
        {
        writeINIerror = true;
        }

    m_WIeRMBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "WIeRMBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoWVeRM", m_DoWVeRM.GetCheck()))
        {
        writeINIerror = true;
        }

    m_WVeRMBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "WVeRMBaseDir", temp))
        {
        writeINIerror = true;
        }

    // DATA
    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoALData", m_DoALData.GetCheck()))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoARData", m_DoARData.GetCheck()))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoAZData", m_DoAZData.GetCheck()))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoCOData", m_DoCOData.GetCheck()))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoCTData", m_DoCTData.GetCheck()))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoIAData", m_DoIAData.GetCheck()))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoILData", m_DoILData.GetCheck()))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoKYData", m_DoKYData.GetCheck()))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoLAData", m_DoLAData.GetCheck()))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoMDData", m_DoMDData.GetCheck()))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoMIData", m_DoMIData.GetCheck()))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoMOData", m_DoMOData.GetCheck()))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoNCData", m_DoNCData.GetCheck()))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoNEData", m_DoNEData.GetCheck()))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoNJData", m_DoNJData.GetCheck()))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoOHData", m_DoOHData.GetCheck()))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoORData", m_DoORData.GetCheck()))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoQLDData", m_DoQLDData.GetCheck()))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoSDData", m_DoSDData.GetCheck()))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoVAData", m_DoVAData.GetCheck()))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoWAData", m_DoWAData.GetCheck()))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoWIData", m_DoWIData.GetCheck()))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoWVData", m_DoWVData.GetCheck()))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoPASSDB", m_DoPASSDB.GetCheck()))
        {
        writeINIerror = true;
        }

    m_PASSDBBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "PASSDBBaseDir", temp))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoRestDB", m_DoRestDB.GetCheck()))
        {
        writeINIerror = true;
        }

    m_RestDBBaseDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "RestDBBaseDir", temp))
        {
        writeINIerror = true;
        }

    m_WinSysDir.GetWindowText(temp);
    if (!AfxGetApp()->WriteProfileString("Defaults", "WinSysDir", temp))
        {
        writeINIerror = true;
        }

    // Address Data
    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoCTAddress", m_doCTAddress.GetCheck()))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoMDAddress", m_doMDAddress.GetCheck()))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoNJAddress", m_doNJAddress.GetCheck()))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoQLDAddress", m_doQLDAddress.GetCheck()))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoVAAddress", m_doVAAddress.GetCheck()))
        {
        writeINIerror = true;
        }

    if (!AfxGetApp()->WriteProfileInt("Defaults", "DoWIAddress", m_doWIAddress.GetCheck()))
        {
        writeINIerror = true;
        }

    if (writeINIerror)
        {
        AfxMessageBox("One or more settings were not able to be saved into INI file. Please ensure you have permissions to update the INI.");
        }
    }

/*------------------------------------------------------------------------------
* MODULE      OnClearAll
* PURPOSE     Clears all currently checked items.
*-------------------------------------------------------------------------------
* AUTHOR      Dan Vogen                  DATE 01-18-2003
* REVISION    DATE         NAME          DESCRIPTION
*-------------------------------------------------------------------------------
* ARGUMENTS   Type         Call Conv  Purpose
*-------------------------------------------------------------------------------
* CONDITION   Value        Description
* VALUES      None
* RETURNED
*-----------------------------------------------------------------------------*/
void CSuperupdDlg::OnClearAll()
    {
    m_DoRoute.SetCheck(0);
    m_DoMaintenanceMgr.SetCheck(0);

    // PASS
    m_DoALPASS.SetCheck(0);
    m_DoARPASS.SetCheck(0);
    m_DoCTPASS.SetCheck(0);
    m_DoNEPASS.SetCheck(0);
    m_DoOHPASS.SetCheck(0);
    m_DoSDPASS.SetCheck(0);

    // ePASS
    m_DoALePASS.SetCheck(0);
    m_DoARePASS.SetCheck(0);
    m_DoAZePASS.SetCheck(0);
    m_DoCTePASS.SetCheck(0);
    m_DoIAePASS.SetCheck(0);
    m_DoKYePASS.SetCheck(0);
    m_DoMDePASS.SetCheck(0);
    m_DoMIePASS.SetCheck(0);
    m_DoMOePASS.SetCheck(0);
    m_DoNEePASS.SetCheck(0);
    m_DoNJePASS.SetCheck(0);
    m_DoOHePASS.SetCheck(0);
    m_DoMultiState.SetCheck(0);
    m_DoQLDePASS.SetCheck(0);
    m_DoSDePASS.SetCheck(0);
    m_DoVAeRoute.SetCheck(0);
    m_DoWIeRoute.SetCheck(0);
    m_DoWVePASS.SetCheck(0);

    // eRM
    m_DoALeRM.SetCheck(0);
    m_DoAReRM.SetCheck(0);
    m_DoAZeRM.SetCheck(0);
    m_DoCTeRM.SetCheck(0);
    m_DoIAeRM.SetCheck(0);
    m_DoKYeRM.SetCheck(0);
    m_DoMDeRM.SetCheck(0);
    m_DoMIeRM.SetCheck(0);
    m_DoMOeRM.SetCheck(0);
    m_DoNCeRM.SetCheck(0);
    m_DoNEeRM.SetCheck(0);
    m_DoNJeRM.SetCheck(0);
    m_DoOHeRM.SetCheck(0);
    m_DoQLDeRM.SetCheck(0);
    m_DoSDeRM.SetCheck(0);
    m_DoVAeRM.SetCheck(0);
    m_DoWIeRM.SetCheck(0);
    m_DoWVeRM.SetCheck(0);

    // Data
    m_DoALData.SetCheck(0);
    m_DoARData.SetCheck(0);
    m_DoAZData.SetCheck(0);
    m_DoCOData.SetCheck(0);
    m_DoCTData.SetCheck(0);
    m_DoGAData.SetCheck(0);
    m_DoIAData.SetCheck(0);
    m_DoILData.SetCheck(0);
    m_DoKYData.SetCheck(0);
    m_DoLAData.SetCheck(0);
    m_DoMDData.SetCheck(0);
    m_DoMIData.SetCheck(0);
    m_DoMOData.SetCheck(0);
    m_DoNCData.SetCheck(0);
    m_DoNEData.SetCheck(0);
    m_DoNJData.SetCheck(0);
    m_DoOHData.SetCheck(0);
    m_DoORData.SetCheck(0);
    m_DoQLDData.SetCheck(0);
    m_DoSDData.SetCheck(0);
    m_DoVAData.SetCheck(0);
    m_DoWAData.SetCheck(0);
    m_DoWIData.SetCheck(0);
    m_DoWVData.SetCheck(0);
    m_DoPASSDB.SetCheck(0);
    m_DoRestDB.SetCheck(0);

    // Address Data
    m_doCTAddress.SetCheck(0);
    m_doMDAddress.SetCheck(0);
    m_doNJAddress.SetCheck(0);
    m_doQLDAddress.SetCheck(0);
    m_doVAAddress.SetCheck(0);
    m_doWIAddress.SetCheck(0);
    }

/*------------------------------------------------------------------------------
* MODULE      AppendToLog
* PURPOSE     Adds the specified text to the end of the specified log file
*-------------------------------------------------------------------------------
* AUTHOR      Dan Vogen                  DATE 01-18-2003
* REVISION    DATE         NAME          DESCRIPTION
*-------------------------------------------------------------------------------
* ARGUMENTS   Type         Call Conv  Purpose
* text        char         ref        text to add
* logFile     char         ref        log file to append to
*-------------------------------------------------------------------------------
* CONDITION   Value        Description
* VALUES      0            Success
* RETURNED    <> 0         Error
*-----------------------------------------------------------------------------*/
long CSuperupdDlg::AppendToLog
(
LPCSTR text,
LPCSTR logFile,
LPCSTR directory,
LPCSTR optional
)
    {
    FILE*   fp;
    CString message;
    CString temp;

    if (NULL == (fp = fopen(logFile, "a+")))
        {
        return 1;
        }

    message.Format("         %s : %s", m_computerName, text);

    if (0 < strlen(directory))
        {
        temp.Format(" Dir=%s", directory);
        message += temp;
        }

    if (0 < strlen(optional))
        {
        temp.Format(" %s", optional);
        message += temp;
        }

    fprintf(fp, "%s\n", message);
    fclose(fp);

    return 0;
    }

long CSuperupdDlg::AppendToLog
(
LPCSTR text,
LPCSTR logFile
)
    {
    FILE* fp;

    if (NULL == (fp = fopen(logFile, "a+")))
        {
        return 1;
        }

    fprintf(fp, "%s (%s) : %s\n", m_computerName, m_userName, text);
    fclose(fp);

    return 0;
    }

/*------------------------------------------------------------------------------
* MODULE      AddToUpdate
* PURPOSE     Adds appropriate commands to update script
*-------------------------------------------------------------------------------
* AUTHOR      Dan Vogen                  DATE 01-18-2003
* REVISION    DATE         NAME          DESCRIPTION
*-------------------------------------------------------------------------------
* ARGUMENTS   Type         Call Conv  Purpose
* updateFile  const char   ref        File with update commands
* update      char         ref        Item to be updated
* dir1        char         ref        First directory to replace
* dir2        char         ref        Second directory to replace
* winSysDir   char         ref        Windows System directory to replace
* message     char         ref        Message to add to script to highlight section
*-------------------------------------------------------------------------------
* CONDITION   Value        Description
* VALUES      0            Success
* RETURNED    <> 0         Error
*-----------------------------------------------------------------------------*/
long CSuperupdDlg::AddToUpdate
(
LPCSTR updateFile,
LPCSTR sourceUpdate,
LPCSTR dataUpdate,
LPCSTR update,
LPCSTR dir1,
LPCSTR dir2,
LPCSTR winSysDir,
LPCSTR message,
bool   dateDepenedent
)
    {
    FILE*   fp;
    FILE*   fp2;
    char    buffer[256];
    char    tmpUpdate[256];
    char    command[512];
    long    length;
    long    i;
    bool    skip;
    CString commandExecute;
    CString temp;

    temp = message;
    if (NULL == (fp = fopen(updateFile, "r")))
        {
        AfxMessageBox(SUPERUPD_UPDATEFILE_ERROR);
        return 1;
        }

    if (NULL == (fp2 = fopen(UPDATE_SCRIPT, "a+")))
        {
        CString tempMessage = UPDATE_SCRIPT_ERROR + UPDATE_SCRIPT;

        AfxMessageBox(tempMessage);
        return 2;
        }

    // read each line in the data file
    // each line has the following Format:
    // UPDATE:COMMAND
    // parse each line, if the update is the update we are trying to run, 
    // run the specified command
    fgets(buffer, 255, fp);

    while (!feof(fp))
        {
        if (strlen(buffer))
            {
            buffer[strlen(buffer) - 1] = '\0';
            }

        // does the update on this line match
        sprintf(tmpUpdate, "%s;", update);
        length = strlen(tmpUpdate);

        if (!strncmp(buffer, tmpUpdate, length))
            {
            strcpy(command, buffer + length);
            length = strlen(command);
            commandExecute = "";
            i = 0;

            while (i < length)
                {
                if ('%' != command[i])
                    {
                    commandExecute += command[i];
                    i++;
                    }
                else if (!strncmp(command + i, "%DIR1%", 6))
                    {
                    commandExecute += dir1;
                    i += 6;
                    }
                else if (!strncmp(command + i, "%DIR2%", 6))
                    {
                    commandExecute += dir2;
                    i += 6;
                    }
                else if (!strncmp(command + i, "%WINSYSDIR%", 11))
                    {
                    commandExecute += winSysDir;
                    i += 11;
                    }
                else if (!strncmp(command + i, "%BLD_SRC%", 9))
                    {
                    commandExecute += sourceUpdate;
                    i += 9;
                    }
                else if (!strncmp(command + i, "%DATA_SRC%", 10))
                    {
                    commandExecute += dataUpdate;
                    i += 10;
                    }
                else if (!strncmp(command + i, "%ROUTE_DIR%", 11))
                    {
                    commandExecute += m_routeDir;
                    i += 11;
                    }
                else if (!strncmp(command + i, "%DATE_DEPENDENT%", 16))
                    {
                    if (dateDepenedent)
                        commandExecute += "/D";

                    i += 16;
                    }
                else
                    {
                    commandExecute += command[i];
                    i++;
                    }
                }

            // only write out the commandExecute if it hasn't been
            skip = false;

            if (!existCommand(commandExecute) && 0 > commandExecute.Find("ERRORLEVEL"))
                {
                addCommand(commandExecute);
                }
            else
                {
                skip = true;
                }

            if (!skip)
                {
                fprintf(fp2, "%s\n", commandExecute);

                temp = commandExecute;
                temp.MakeLower();

                if (0 <= commandExecute.Find("xcopy ") || 0 <= commandExecute.Find("copy "))
                    {
                    fprintf(fp2, "if NOT \"%%ERRORLEVEL%%\" == \"0\" Echo Error Executing %s >> %s\n", commandExecute, UPDATE_ERROR_FILE);
                    }
                }
            }

        fgets(buffer, 255, fp);
        }

    fclose(fp);
    fclose(fp2);

    return 0;
    }

void CSuperupdDlg::OnCancel()
    {
    if (FileExist(UPDATE_ERROR_FILE, 0))
        {
        remove(UPDATE_ERROR_FILE);
        }

    CDialog::OnCancel();
    }

bool CSuperupdDlg::existCommand
(
LPCSTR  command
)
    {

    long    count;
    long    current;
    CString savedCommand;
    bool    exist;

    exist = false;
    count = m_arrayCommand.GetCount();

    for (current = 0; current < count && !exist; current++)
        {
        savedCommand = m_arrayCommand.GetAt(current);

        if (savedCommand == command)
            {
            exist = true;
            }
        }

    return exist;

    }
void CSuperupdDlg::addCommand
(
LPCSTR  command
)
    {
    m_arrayCommand.Add(command);
    }

void CSuperupdDlg::resetCommands()
    {
    m_arrayCommand.RemoveAll();
    }

void CSuperupdDlg::getSourceLocations()
    {
    int i;
    CString key;
    CString string;

    m_sourceLocation.ResetContent();

    for (i = 1; i < 100; i++)
        {
        key.Format("UpdateLoc%d", i);
        string = AfxGetApp()->GetProfileString("SourceLocations", key, "");

        if ("" == string)
            {
            break;
            }

        m_sourceLocation.AddString(string);
        }

    //Add the saved location
    string = AfxGetApp()->GetProfileString("SourceLocations", "UpdateSource", "");
    m_sourceLocation.SetWindowText(string);

    }

void CSuperupdDlg::addSourceLocation
(
LPCSTR location
)
    {
    CString temp;
    CString key;
    int     i;
    bool    isFound;

    isFound = false;

    for (i = 1; i < 11 && !isFound; i++)
        {
        key.Format("UpdateLoc%d", i);
        temp = AfxGetApp()->GetProfileString("SourceLocations", key, "");

        if ("" == temp)
            break;

        if (location == temp)
            {
            isFound = true;
            }
        }

    if (!isFound)
        {
        key.Format("UpdateLoc%d", i);

        if (!AfxGetApp()->WriteProfileString("SourceLocations", key, location))
            {
            AfxMessageBox("Unable to save the location into the INI file.");
            }

        getSourceLocations();
        }
    }

void CSuperupdDlg::getDataLocations()
    {
    int     i;
    CString key;
    CString string;

    m_dataLocation.ResetContent();

    for (i = 1; i < 100; i++)
        {
        key.Format("UpdateDataLoc%d", i);
        string = AfxGetApp()->GetProfileString("DataLocations", key, "");

        if ("" == string)
            {
            break;
            }

        m_dataLocation.AddString(string);
        }

    string = AfxGetApp()->GetProfileString("DataLocations", "UpdateData", "");
    m_dataLocation.SetWindowText(string);

    }

void CSuperupdDlg::addDataLocation
(
LPCSTR location
)
    {
    CString temp;
    CString key;
    int     i;
    bool    isFound;

    isFound = false;

    for (i = 1; i < 11 && !isFound; i++)
        {
        key.Format("UpdateDataLoc%d", i);
        temp = AfxGetApp()->GetProfileString("DataLocations", key, "");

        if ("" == temp)
            break;

        if (location == temp)
            {
            isFound = true;
            }
        }

    if (!isFound)
        {
        key.Format("UpdateDataLoc%d", i);

        if (!AfxGetApp()->WriteProfileString("DataLocations", key, location))
            {
            AfxMessageBox("Unable to save the data location into the INI file.");
            }

        getDataLocations();
        }
    }

//Include ePASS, eRM, or eRoute checkboxes
bool CSuperupdDlg::updateESUPER
(
void
)
    {
    return updateEPASS() || updateERM() || m_DoVAeRoute.GetCheck() || m_DoWIeRoute.GetCheck();
    }

//Include check boxes for pure ePASS updates
bool CSuperupdDlg::updateEPASS
(
void
)
    {
    return m_DoALePASS.GetCheck() ||
        m_DoARePASS.GetCheck() ||
        m_DoAZePASS.GetCheck() ||
        m_DoCTePASS.GetCheck() ||
        m_DoIAePASS.GetCheck() ||
        m_DoKYePASS.GetCheck() ||
        m_DoMDePASS.GetCheck() ||
        m_DoMIePASS.GetCheck() ||
        m_DoMOePASS.GetCheck() ||
        m_DoNEePASS.GetCheck() ||
        m_DoNJePASS.GetCheck() ||
        m_DoOHePASS.GetCheck() ||
        m_DoQLDePASS.GetCheck() ||
        m_DoSDePASS.GetCheck() ||
        m_DoWVePASS.GetCheck() ||
        m_DoMultiState.GetCheck();

    }

//Include check boxes for pure eRM updates
bool CSuperupdDlg::updateERM
(
void
)
    {
    return m_DoALeRM.GetCheck() ||
        m_DoAReRM.GetCheck() ||
        m_DoAZeRM.GetCheck() ||
        m_DoCTeRM.GetCheck() ||
        m_DoIAeRM.GetCheck() ||
        m_DoKYeRM.GetCheck() ||
        m_DoMDeRM.GetCheck() ||
        m_DoMIeRM.GetCheck() ||
        m_DoMOeRM.GetCheck() ||
        m_DoNEeRM.GetCheck() ||
        m_DoNCeRM.GetCheck() ||
        m_DoNJeRM.GetCheck() ||
        m_DoOHeRM.GetCheck() ||
        m_DoQLDeRM.GetCheck() ||
        m_DoSDeRM.GetCheck() ||
        m_DoVAeRM.GetCheck() ||
        m_DoWIeRM.GetCheck() ||
        m_DoWVeRM.GetCheck();
    }
