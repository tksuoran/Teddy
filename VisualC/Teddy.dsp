# Microsoft Developer Studio Project File - Name="Teddy" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Teddy - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Teddy.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Teddy.mak" CFG="Teddy - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Teddy - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Teddy - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "Teddy - Win32 ReleaseWithDebug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Teddy - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release/Teddy"
# PROP Intermediate_Dir "Release/Teddy"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /Zp4 /MD /W3 /Gi /GR /GX /O2 /Ob2 /I "." /I ".." /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x40b /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Teddy - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug/Teddy"
# PROP Intermediate_Dir "Debug/Teddy"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /Zp4 /MDd /W3 /Gm /Gi /GR /GX /Zi /Od /I "." /I ".." /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x40b /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"Debug/TeddyD.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Debug\TeddyD.lib"

!ELSEIF  "$(CFG)" == "Teddy - Win32 ReleaseWithDebug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Teddy___Win32_ReleaseWithDebug"
# PROP BASE Intermediate_Dir "Teddy___Win32_ReleaseWithDebug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseWithDebug/Teddy"
# PROP Intermediate_Dir "ReleaseWithDebug/Teddy"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Zp4 /MD /W3 /Gi /GR /GX /O2 /Ob2 /I "." /I ".." /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /Zp4 /MD /W3 /Gi /GR /GX /Zi /O2 /Ob2 /I "." /I ".." /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "Teddy - Win32 Release"
# Name "Teddy - Win32 Debug"
# Name "Teddy - Win32 ReleaseWithDebug"
# Begin Group "Application"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Teddy\Application\BaseAudioManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Application\BaseAudioManager.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Application\BaseObjectManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Application\BaseObjectManager.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Application\BaseRoot.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Application\BaseRoot.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Application\BaseSimulationTimer.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Application\BaseSimulationTimer.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Application\BaseUserInterface.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Application\BaseUserInterface.h
# End Source File
# End Group
# Begin Group "Behaviour"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Teddy\Behaviour\Control.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Behaviour\Control.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Behaviour\ModelAnimator.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Behaviour\ModelAnimator.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Behaviour\ModelController.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Behaviour\ModelController.h
# End Source File
# End Group
# Begin Group "Graphics"

# PROP Default_Filter ""
# Begin Group "Textures"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Teddy\Graphics\ImageFileTexture.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Graphics\ImageFileTexture.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Graphics\ImageFileTextureLoader.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Graphics\ImageFileTextureLoader.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Graphics\PixFileTexture.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Graphics\PixFileTexture.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Graphics\Texture.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Graphics\Texture.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Graphics\TextureConversions.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Graphics\TextureManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Graphics\TextureManager.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\Teddy\Graphics\Color.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Graphics\Color.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Graphics\convgltex.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Graphics\convgltex.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Graphics\Device.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Graphics\Device.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Graphics\Font.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Graphics\Font.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Graphics\glu_mipmap.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Graphics\glu_mipmap.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Graphics\Graphics.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Graphics\PsRenderer.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Graphics\PsRenderer.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Graphics\View.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Graphics\View.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Graphics\ViewClient.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Graphics\ViewClient.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Graphics\ViewDraw.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Graphics\ViewFeatures.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Graphics\ViewGL.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Graphics\ViewScreenshot.cpp
# End Source File
# End Group
# Begin Group "Imports"

# PROP Default_Filter ""
# Begin Group "LWObject"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Teddy\Imports\LWClip.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWClip.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\lwdef.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWFile.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWFile.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWLayer.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWLayer.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWModel.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWModel.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWSurface.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWSurface.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWSurfaceBlok.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWSurfaceBlok.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWSurfaceBlokGradient.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWSurfaceBlokImageMap.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWSurfaceBlokProcedural.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWSurfaceBlokShader.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWTexture.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWTexture.h
# End Source File
# End Group
# Begin Group "LWScene"

# PROP Default_Filter ""
# Begin Group "Parser"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Teddy\Imports\LWScene.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWSceneCamera.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWSceneEffects.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWSceneFile.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWSceneFile.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWSceneLight.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWSceneObject.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWSceneObjectDisplacement.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWSceneObjectSkeleton.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWSceneOptions.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWSceneRecord.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWSceneTokens.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\Teddy\Imports\LWBone.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWBone.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWCamera.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWCamera.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWChannelEnvelope.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWChannelEnvelope.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWChannelKey.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWChannelKey.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWEnvelope.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWEnvelope.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWEnvelopeKey.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWEnvelopeKey.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWInstance.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWInstance.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWLight.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWLight.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWMotion.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWMotion.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWSceneParser.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWSceneParser.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\Teddy\Imports\Imports.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWModelLoader.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Imports\LWModelLoader.h
# End Source File
# End Group
# Begin Group "Maths"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Teddy\Maths\CrossVector4.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Maths\CrossVector4.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Maths\Maths.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Maths\Matrix.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Maths\Matrix.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Maths\Plane.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Maths\Plane.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Maths\Quaternion.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Maths\Quaternion.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Maths\Rect.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Maths\Vector.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Maths\Vector.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Maths\Vector2.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Maths\Vector2.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Maths\Vector4.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Maths\Vector4.h
# End Source File
# End Group
# Begin Group "Materials"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Teddy\Materials\Light.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Materials\Light.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Materials\Material.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Materials\Material.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Materials\Materials.h
# End Source File
# End Group
# Begin Group "MixIn"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Teddy\MixIn\Counted.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\MixIn\Counted.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\MixIn\MixIn.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\MixIn\Mutex.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\MixIn\Mutex.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\MixIn\Named.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\MixIn\Named.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\MixIn\Options.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\MixIn\Options.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\MixIn\PostInit.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\MixIn\PostInit.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\MixIn\Tick.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\MixIn\Tick.h
# End Source File
# End Group
# Begin Group "Models"

# PROP Default_Filter ""
# Begin Group "Primitives"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Teddy\Models\Box.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\Box.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\Capsule.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\Capsule.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\Cone.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\Cone.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\Cylinder.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\Cylinder.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\Grid.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\Grid.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\Ring.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\Ring.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\Solids.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\Solids.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\Sphere.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\Sphere.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\Torus.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\Torus.h
# End Source File
# End Group
# Begin Group "Elements"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Teddy\Models\Element.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\Element.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\Face.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\Face.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\FaceCollisionModel.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\FaceSurface.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\Line.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\Line.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\Quads.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\Quads.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\QuadStrip.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\QuadStrip.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\TriangleFan.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\TriangleFan.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\Triangles.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\Triangles.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\TriangleStrip.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\TriangleStrip.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\Vertex.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\Vertex.h
# End Source File
# End Group
# Begin Group "Geometries"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Teddy\Models\Geometry.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\Geometry.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\GeometryCollisionModel.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\GeometryIterator.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\GeometryIterator.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\GeometryTextureCoordinates.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\LineGeometry.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\LineGeometry.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\PointGeometry.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\PointGeometry.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\Teddy\Models\Model.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\Model.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\ModelDraw.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\ModelMatrices.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\Models.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Models\ModelTransform.cpp
# End Source File
# End Group
# Begin Group "PhysicalComponents"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Teddy\PhysicalComponents\ActionButton.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\PhysicalComponents\ActionButton.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\PhysicalComponents\Area.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\PhysicalComponents\Area.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\PhysicalComponents\AreaDraw.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\PhysicalComponents\AreaLayout.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\PhysicalComponents\Button.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\PhysicalComponents\Button.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\PhysicalComponents\Console.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\PhysicalComponents\Console.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\PhysicalComponents\ConsoleStream.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\PhysicalComponents\ConsoleStream.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\PhysicalComponents\ConsoleStreamBuffer.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\PhysicalComponents\ConsoleStreamBuffer.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\PhysicalComponents\Dock.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\PhysicalComponents\Dock.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\PhysicalComponents\EventListener.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\PhysicalComponents\EventListener.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\PhysicalComponents\Fill.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\PhysicalComponents\Fill.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\PhysicalComponents\Frame.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\PhysicalComponents\Frame.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\PhysicalComponents\GradientFill.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\PhysicalComponents\GradientFill.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\PhysicalComponents\Label.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\PhysicalComponents\Label.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\PhysicalComponents\Layer.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\PhysicalComponents\Layer.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\PhysicalComponents\MenuList.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\PhysicalComponents\MenuList.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\PhysicalComponents\PhysicalComponents.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\PhysicalComponents\Popup.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\PhysicalComponents\Popup.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\PhysicalComponents\Projection.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\PhysicalComponents\Projection.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\PhysicalComponents\Style.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\PhysicalComponents\Style.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\PhysicalComponents\WindowManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\PhysicalComponents\WindowManager.h
# End Source File
# End Group
# Begin Group "Scenes"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Teddy\Scenes\Camera.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Scenes\Camera.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Scenes\Ellipsoid.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Scenes\Ellipsoid.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Scenes\PostElement.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Scenes\PostElement.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Scenes\Scene.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Scenes\Scene.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Scenes\Scenes.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\Scenes\SkyBox.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Scenes\SkyBox.h
# End Source File
# End Group
# Begin Group "SysSupport"

# PROP Default_Filter ""
# Begin Group "Std"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Teddy\SysSupport\StdAlgo.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\StdAlgo.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\StdIO.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\StdList.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\StdList.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\StdMap.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\StdMap.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\StdMaths.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\StdMaths.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\StdSDL.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\StdStack.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\StdStack.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\StdString.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\StdString.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\StdVector.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\StdVector.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\Teddy\SysSupport\EndianIn.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\EndianIn.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\EndianIO.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\EndianIO.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\EndianOut.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\EndianOut.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\Exception.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\Exception.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\FileScan.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\FileScan.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\MemoryBlock.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\MemoryBlock.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\Messages.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\Messages.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\SysSupport.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\Timer.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\Timer.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\Types.h
# End Source File
# End Group
# Begin Group "Signals"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Teddy\Signals\Functor.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Signals\Functor.h
# End Source File
# End Group
# Begin Group "NonVC"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\configure.in
# End Source File
# Begin Source File

SOURCE=..\fix
# End Source File
# Begin Source File

SOURCE=..\Makefile
# End Source File
# Begin Source File

SOURCE=..\Makefile.in
# End Source File
# End Group
# Begin Group "ReadMe"

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
# Begin Group "Doc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Teddy\SysSupport\doc_page_build_process.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\doc_page_coding_conventions.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\doc_page_cvs_support.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\doc_page_design.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\doc_page_environment.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\doc_page_getting.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\doc_page_history.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\doc_page_registering.h
# End Source File
# Begin Source File

SOURCE=..\Teddy\SysSupport\doc_page_status.h
# End Source File
# Begin Source File

SOURCE=..\Doxyfile
# End Source File
# End Group
# Begin Group "LowRast"

# PROP Default_Filter ""
# End Group
# Begin Source File

SOURCE=..\Teddy\Teddy.cpp
# End Source File
# Begin Source File

SOURCE=..\Teddy\Teddy.h
# End Source File
# Begin Source File

SOURCE=.\Teddy\TeddyConfig.h
# End Source File
# End Target
# End Project
