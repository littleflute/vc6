# Microsoft Developer Studio Project File - Name="WalkLtDemo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=WalkLtDemo - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "WalkLtDemo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WalkLtDemo.mak" CFG="WalkLtDemo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WalkLtDemo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "WalkLtDemo - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WalkLtDemo - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"../Bin/WalkLtDemo.exe" /libpath:"../Lib"

!ELSEIF  "$(CFG)" == "WalkLtDemo - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"../Bin/WalkLtDemo.exe" /pdbtype:sept /libpath:"../Lib"

!ENDIF 

# Begin Target

# Name "WalkLtDemo - Win32 Release"
# Name "WalkLtDemo - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\GdiplusDemoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MyCodeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\WalkLtDemo.cpp
# End Source File
# Begin Source File

SOURCE=.\WalkLtDemo.rc
# End Source File
# Begin Source File

SOURCE=.\WalkLtDemoDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\WalkLtDemoHelp.cpp
# End Source File
# Begin Source File

SOURCE=.\WalkLtDemoView.cpp
# End Source File
# Begin Source File

SOURCE=".\WalkLtDemoÉè¼ÆÊµÀý.cpp"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "gdiplus"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=..\include\GdiPlus.h
# End Source File
# Begin Source File

SOURCE=..\include\GdiPlusBase.h
# End Source File
# Begin Source File

SOURCE=..\include\GdiPlusBitmap.h
# End Source File
# Begin Source File

SOURCE=..\include\GdiPlusBrush.h
# End Source File
# Begin Source File

SOURCE=..\include\GdiPlusCachedBitmap.h
# End Source File
# Begin Source File

SOURCE=..\include\GdiPlusColor.h
# End Source File
# Begin Source File

SOURCE=..\include\GdiPlusColorMatrix.h
# End Source File
# Begin Source File

SOURCE=.\GdiplusDemoFuns.h
# End Source File
# Begin Source File

SOURCE=..\include\GdiPlusEnums.h
# End Source File
# Begin Source File

SOURCE=..\include\GdiPlusFlat.h
# End Source File
# Begin Source File

SOURCE=..\include\GdiPlusFont.h
# End Source File
# Begin Source File

SOURCE=..\include\GdiPlusFontCollection.h
# End Source File
# Begin Source File

SOURCE=..\include\GdiPlusFontFamily.h
# End Source File
# Begin Source File

SOURCE=..\include\GdiPlusGpStubs.h
# End Source File
# Begin Source File

SOURCE=..\include\GdiPlusGraphics.h
# End Source File
# Begin Source File

SOURCE=..\include\GdiPlusHeaders.h
# End Source File
# Begin Source File

SOURCE=..\include\GdiPlusimageAttributes.h
# End Source File
# Begin Source File

SOURCE=..\include\GdiPlusImageCodec.h
# End Source File
# Begin Source File

SOURCE=..\include\GdiPlusImaging.h
# End Source File
# Begin Source File

SOURCE=..\include\GdiPlusInit.h
# End Source File
# Begin Source File

SOURCE=..\include\GdiPlusLineCaps.h
# End Source File
# Begin Source File

SOURCE=..\include\GdiPlusMatrix.h
# End Source File
# Begin Source File

SOURCE=..\include\GdiPlusMem.h
# End Source File
# Begin Source File

SOURCE=..\include\GdiPlusMetaFile.h
# End Source File
# Begin Source File

SOURCE=..\include\GdiPlusMetaHeader.h
# End Source File
# Begin Source File

SOURCE=..\include\GdiPlusPath.h
# End Source File
# Begin Source File

SOURCE=..\include\GdiPlusPen.h
# End Source File
# Begin Source File

SOURCE=..\include\GdiPlusPixelFormats.h
# End Source File
# Begin Source File

SOURCE=..\include\GdiPlusRegion.h
# End Source File
# Begin Source File

SOURCE=..\include\GdiPlusStringFormat.h
# End Source File
# Begin Source File

SOURCE=..\include\GdiPlusTypes.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\GdiplusDemoDlg.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MyCodeDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\WalkLtDemo.h
# End Source File
# Begin Source File

SOURCE=.\WalkLtDemoDoc.h
# End Source File
# Begin Source File

SOURCE=.\WalkLtDemoHelp.h
# End Source File
# Begin Source File

SOURCE=.\WalkLtDemoView.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WalkLtDemo.ico
# End Source File
# Begin Source File

SOURCE=.\res\WalkLtDemo.rc2
# End Source File
# Begin Source File

SOURCE=.\res\WalkLtDemoDoc.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
