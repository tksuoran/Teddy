# Microsoft Developer Studio Project File - Name="TestEvents" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=TestEvents - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TestEvents.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TestEvents.mak" CFG="TestEvents - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TestEvents - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "TestEvents - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TestEvents - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release/TestEvents"
# PROP Intermediate_Dir "Release/TestEvents"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /Zp4 /MD /W3 /Gi /GR /GX /O2 /Ob2 /I "." /I ".." /I "../TeddyTests" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40b /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes /machine:I386

!ELSEIF  "$(CFG)" == "TestEvents - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug/TestEvents"
# PROP Intermediate_Dir "Debug/TestEvents"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /Zp4 /MDd /W3 /Gm /Gi /GR /GX /ZI /Od /I "." /I ".." /I "../TeddyTests" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40b /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /profile /debug /machine:I386

!ENDIF 

# Begin Target

# Name "TestEvents - Win32 Release"
# Name "TestEvents - Win32 Debug"
# Begin Group "DOC"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\AUTHORS
# End Source File
# Begin Source File

SOURCE=..\BUGS
# End Source File
# Begin Source File

SOURCE=..\CHANGELOG
# End Source File
# Begin Source File

SOURCE=..\README
# End Source File
# Begin Source File

SOURCE=..\README.Amiga.txt
# End Source File
# Begin Source File

SOURCE=..\README.Cygwin.txt
# End Source File
# Begin Source File

SOURCE=..\README.MingW.txt
# End Source File
# Begin Source File

SOURCE=..\README.VisualC.txt
# End Source File
# Begin Source File

SOURCE=..\TODO
# End Source File
# End Group
# Begin Source File

SOURCE=..\Programs\TestEvents\src\BallStack.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\TestEvents\src\BallStack.h
# End Source File
# Begin Source File

SOURCE=..\Programs\TestEvents\src\Bender.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\TestEvents\src\Bender.h
# End Source File
# Begin Source File

SOURCE=..\Programs\TestEvents\src\Bouncer.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\TestEvents\src\Bouncer.h
# End Source File
# Begin Source File

SOURCE=..\Programs\TestEvents\src\CameraController.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\TestEvents\src\CameraController.h
# End Source File
# Begin Source File

SOURCE=..\Programs\TestEvents\src\Display.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\TestEvents\src\Display.h
# End Source File
# Begin Source File

SOURCE=..\Programs\TestEvents\src\Gadget.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\TestEvents\src\Gadget.h
# End Source File
# Begin Source File

SOURCE=..\Programs\TestEvents\src\LSystem.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\TestEvents\src\LSystem.h
# End Source File
# Begin Source File

SOURCE=..\Programs\TestEvents\src\LSystemExpand.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\TestEvents\src\LSystemGenerate.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\TestEvents\src\Node.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\TestEvents\src\Node.h
# End Source File
# Begin Source File

SOURCE=..\Programs\TestEvents\src\ObjectManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\TestEvents\src\ObjectManager.h
# End Source File
# Begin Source File

SOURCE=..\Programs\TestEvents\src\ObjectManagerBallStacks.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\TestEvents\src\ObjectManagerLights.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\TestEvents\src\ObjectManagerLSystems.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\TestEvents\src\ObjectManagerLWO.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\TestEvents\src\ObjectManagerTrees.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\TestEvents\src\Orbiter.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\TestEvents\src\Orbiter.h
# End Source File
# Begin Source File

SOURCE=..\Programs\TestEvents\src\Root.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\TestEvents\src\Root.h
# End Source File
# Begin Source File

SOURCE=..\Programs\TestEvents\src\SimpleText.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\TestEvents\src\SimpleText.h
# End Source File
# Begin Source File

SOURCE=..\Programs\TestEvents\src\State.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\TestEvents\src\State.h
# End Source File
# Begin Source File

SOURCE=..\Programs\TestEvents\src\Tree.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\TestEvents\src\Tree.h
# End Source File
# Begin Source File

SOURCE=..\Programs\TestEvents\src\UserInterface.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\TestEvents\src\UserInterface.h
# End Source File
# End Target
# End Project
