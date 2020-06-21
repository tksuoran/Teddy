# Microsoft Developer Studio Project File - Name="SpaceGame" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SpaceGame - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SpaceGame.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SpaceGame.mak" CFG="SpaceGame - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SpaceGame - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SpaceGame - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SpaceGame - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release/SpaceGame"
# PROP Intermediate_Dir "Release/SpaceGame"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /Zp4 /MD /W3 /Gi /GR /GX /O2 /Ob2 /I "." /I ".." /I "../TeddyTests" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
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

!ELSEIF  "$(CFG)" == "SpaceGame - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug/SpaceGame"
# PROP Intermediate_Dir "Debug/SpaceGame"
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

# Name "SpaceGame - Win32 Release"
# Name "SpaceGame - Win32 Debug"
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\ActionManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\ActionManager.h
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\Atmosphere.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\Atmosphere.h
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\Cabin.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\Cabin.h
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\ComputerController.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\ComputerController.h
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\ControlProjection.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\ControlProjection.h
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\FrontierBitmap.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\FrontierBitmap.h
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\FrontierFile.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\FrontierFile.h
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\FrontierMeshCommands.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\FrontierMeshVertices.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\FrontierModel.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\FrontierModel.h
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\FrontierObjects.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\Hud.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\Hud.h
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\LightwaveObjects.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\ModelCamera.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\ModelCamera.h
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\Node.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\Node.h
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\ObjectManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\ObjectManager.h
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\PlayerController.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\PlayerController.h
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\PrimitiveObjects.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\RoamAlgorithm.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\RoamAlgorithm.h
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\RoamInstance.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\RoamInstance.h
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\RoamObjects.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\RoamSphere.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\RoamSphere.h
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\Root.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\Root.h
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\Scanner.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\Scanner.h
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\Ship.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\Ship.h
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\ShipController.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\ShipController.h
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\ShipTracking.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\ShipType.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\ShipType.h
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\Sight.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\Sight.h
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\SpaceGame.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\SpectatorCamera.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\SpectatorCamera.h
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\UserInterface.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\UserInterface.h
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\VertexArray.cpp
# End Source File
# Begin Source File

SOURCE=..\Programs\SpaceGame\src\VertexArray.h
# End Source File
# End Target
# End Project
