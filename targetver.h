/*----------------------------------------------------------------------+
|   $Source: /bswcivilom-root/sldev/util/superupd/targetver.h,v $
|   $Revision: 1.6 $
|   $Date: 2017/02/10 15:52:58 $
|   $Author: Marcin.Wozniczka $
|
|    $Copyright: (c) 2017 Bentley Systems, Incorporated. All rights reserved. $
|
|   $Log: targetver.h,v $
|   Revision 1.6  2017/02/10 15:52:58  Marcin.Wozniczka
|   Change WINVER value to 0x0600
|
|   Revision 1.5  2017/02/08 16:24:15  Dave.Buckley
|   Cleanup
|
|   Revision 1.4  2017/02/07 16:20:16  Marcin.Wozniczka
|   Enhancement 634237:(RF) VS2015 Upgrade - Perform Build Tools Pilot
|
|   Revision 1.3  2014/04/18 01:54:22  Dave.Buckley
|   Update supported platforms
|
|   Revision 1.2  2013/06/06 18:55:12  Dave.Buckley
|   S-96493
|
|   Revision 1.1  2012/11/14 03:16:27  Dave.Buckley
|   S-55693 Visual Studio conversion to VS2008(C & Fortran)
|
|   Revision 1.1  2010/09/17 18:21:44  Dave.Buckley
|   Add targetver.h to superupd project
+----------------------------------------------------------------------*/
#pragma once

// The following macros define the minimum required platform.  The minimum required platform
// is the earliest version of Windows, Internet Explorer etc. that has the necessary features to run 
// your application.  The macros work by enabling all features available on platform versions up to and 
// including the version specified.

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.

#ifndef WINVER                  // Specifies that the minimum required platform is Windows Server 2008/Windows Vista.
#define WINVER 0x0600           // Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT            // Specifies that the minimum required platform is Windows Server 2008/Windows Vista.
#define _WIN32_WINNT 0x0600     // Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINDOWS          // Specifies that the minimum required platform is Windows Server 2008/Windows Vista.
#define _WIN32_WINDOWS 0x0600   // Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_IE               // Specifies that the minimum required platform is Internet Explorer 9.0.
#define _WIN32_IE 0x0900        // Change this to the appropriate value to target other versions of IE.
#endif
