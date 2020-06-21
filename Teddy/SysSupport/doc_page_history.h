
/*
	TEDDY - General graphics application library
	Copyright (C) 1999-2002  Timo Suoranta
	tksuoran@cc.helsinki.fi

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

	$Id:  $
*/


/*********************************************************************************/
/*! \page page_history  History log of %Teddy so far

<ul>

<li>tksuoran 1st Nov 2002 Teddy 1.78</ul>
 <li>New Area layout and drawing code
 <li>New Event code
 <li>New classes Dock, Popup, MenuList
 <li>Removed some deprecated classes and features
 <li>Initial integration of Ftgl code
 <li>Initial integration of SGI glu tesselation code
 <li>Initial integration of Blender bsp code
 <li>Work in progress: extruded 3D truetype fonts
 <li>Work in progress: boolean csg operations for models

<li>tksuoran Teddy 1.77</ul>
 <li>Fixed configure help info for enable-static
 <li>Fixed transformVertices by adding clearTraversals
 <li>Work in progress: MacOSX support

<li>tksuoran Teddy 1.76</ul>
 <li>Fixed build scripts to support BSD unix systems
 <li>Fixed potential hasExtension() crash
 <li>Added support for SDL without joystick
 <li>Removed potential M_PI was redefinition

<li>tksuoran 25th May 2002 Teddy 1.75<ul>
 <li>New directory structure
 <li>New build scripts for GNU/Linux
 <li>New project files for VisualC++
 <li>Support for shared libraries on GNU/Linux
 <li>TeddyTests and SpaceGame included in Teddy
 <li>Uncountable number of bug fixes and other changes
 <li>CVS is out of sync
 </ul>

<li>tksuoran 12th March 2002 Teddy 1.72<ul>
 <li>Added joystick support (only MS Precision 2 tested at the moment)
 <li>Additions to windowing systems input processing
 <li>Additions to Application Root startup options
 <li>Additions to Control behaviour
 <li>Additions to Material management
 <li>Fixed Material constructors, fixes material related bugs on non-win32 platforms
 <li>Fixed camera quaternion, should no longer break view transformations
 </ul>

<li>tksuoran 12th February 2002 (%Teddy 1.71)<ul>
 <li>Added Application module with InstanceController and InstanceAnimator etc.
 <li>Changes to ModelInstance / Mesh rendering
 <li>Added working per Mesh for each ModelInstance view frustum culling
 <li>Added initial LightWave scene file parser
 <li>Added initial support for GTS - not used yet
 <li>Investigating Java interface for Teddy through JNI (Mika Pesu)
 </ul>

<li>tksuoran 17th January 2002 (%Teddy 1.70)<ul>
 <li>Improved Camera
 <li>Improved culling technique
 <li>Improved Material management
 <li>Imporved hierarchial Meshes
 <li>Added transformVertices() to Mesh
 <li>Added hierarchial ModelInstances
 </ul>

<li>tksuoran 11th January 2002 (%Teddy 1.68)<ul>
 <li>Fixed TinyGL support
 <li>Fixed View::hasExtension() crash bug
 <li>Fixed VisualStudio more
 <li>Added ColDet collision detection library
 </ul>

<li>tksuoran 8th January 2001 (%Teddy 1.67, TeddyTests 1.3):<ul>
 <li>Put everyting inside %Teddy namespace
 <li>Moved and renamed some classes
 <li>Changes to VisualStudio files
 <li>Splitted Geometry from Mesh
 <li>Geometry supports displaylists
 <li>Reworked Graphics::Texture a bit
 <li>Changed glu_ScaleImage() to allocate dataout itself
 <li>Fixed memory bug in WindowManager mouse buttons
 </ul>

<li>tksuoran 3rd December 2001 (%Teddy 1.66):<ul>
 <li>Sourceforge pages seem to be working now
 <li>Added support for GL_EXT_separate_specular_color, which is now use by default if available
 <li>Added lightwave object loader example to TestEvents.
 </ul>

<li>tksuoran 29th November 2001 (%Teddy 1.65):<ul>
 <li>Setting up Sourceforge CVS
 <li>Set new version numbering for TeddyTests and glElite
 </ul>

<li>tksuoran 27th November 2001 (%Teddy 1.64):<ul>
 <li>Created Sourceforge project for %Teddy
 </ul>

<li>tksuoran 17th November 2001 (%Teddy 1.63):<ul>
 <li>More graphics API encapsulation; much better now, still some work to do
 <li>Rearranged some classes into different namespaces
 <li>Separated framework and application
 <li>Added three small example application: TestBasic, TestObjects and TestEvents
 <li>Cabin is broken
 </ul>

<li>tksuoran 9th November 2001 (%Teddy 1.62):<ul>
 <li>Small fixes on projection-camera-material processing
 <li>Custom mouse cursor and alternative spectator camera control
 </ul>

<li>tksuoran 5th November 2001 (%Teddy 1.61):<ul>
 <li>Fixed texture mapping for TinyGL
 <li>Initial work on navigation AI
 </ul>

<li>tksuoran 31st Oct 2001 (%Teddy 1.60):<ul>
 <li>Improved Vertex API a lot; now allows feature inheritance
 <li>Fixed Vertex sharing for texture mapping and smoothing
 <li>Fixed texture mapping a lot
 <li>Fixed .PIX file textures loading
 <li>Buda 5 ship models mostly work now (on Win32) ?
 </ul>

<li>tksuoran 17th Oct 2001 (%Teddy 1.58):<ul>
 <li>Fixed Camera and PostElement
 <li>Fixed view frustum culling
 <li>Fixed LightWave Color reading
 <li>Fixed new char strlen missing + 1 bugs causing crashes
 <li>Fixed configure script SDL_image and SDL_mixer detection
 <li>Initial support for sprites (flares)
 <li>Initial support for cabins
 <li>Initial support for polygon offset in lightwave objects
 <li>Initial original object modelling
 <li>Initial code for atmosphere tracing, not tested
 <li>Picking seems to be mostly broken
 </ul>

<li>tksuoran 11th Oct 2001 (%Teddy 1.57):<ul>
 <li>Fixed horrible memory leak bug in Camera
 <li>Fixed even more horrible OpenGL thread abuse in PlayerControl
 <li>Integreated Open Dynamics Engine
 </ul>

<li>tksuoran 8th Oct 2001 (%Teddy 1.56):<ul>
 <li>Fixed things that were broken in GUI; mouse input works again
 <li>Fixed serious bug in matrix multiplication; picking works again
 <li>%Teddy no longer needs glu library.
 </ul>

<li>tksuoran 5th Oct 2001 (%Teddy 1.55):<ul>
 <li>Fixed building problems
 <li>Now uses config.h
 <li>Integrated optional TinyGL OpenGL subset rendering
 <li>Cleaned up source dependencies by (re)moving some include directives
 </ul>

<li>tksuoran 19th Sep 2001 (%Teddy 1.50):<ul>
 <li>Initial collisions, weapons and samples
 </ul>

<li>tksuoran 7th Sep 2001 (%Teddy 1.49):<ul>
 <li>Tweaked ROAM a bit
 </ul>

<li>tksuoran 27th Aug 2001 (%Teddy 1.48):<ul>
 <li>Updated Roam code
 <li>Fixed Lightwave loader
 </ul>
	
<li>tksuoran 31st Jul 2001 (%Teddy 1.46):<ul>
 <li>Fixed materials, should now work in linux too
 <li>Fixed texturemapping a little
 <li>Fixed scanner
 <li>Integrated bits of Celestia
 <li>Improved GUI a bit
 <li>Changed input processing
 </ul>
	
<li>tksuoran 28th Jun 2001 (%Teddy 1.45):<ul>
 <li>Cleanups
 <li>Initial texture mapping support
 <li>New vertex types
 <li>Some material system rework
 <li>Updated Win32 midi player
 </ul>

<li>tksuoran 8th Jun 2001 (%Teddy 1.44):<ul>
 <li>Improved ships controls (keyboard)
 <li>Frontier Bitmap extractor
 <li>Unified coding conventions
 <li>Removed old code
 <li>Added C++ stream buffer console
 <li>Added some structure to Visual studio workspace
 <li>Different ROAM priority setting algorithm
 </ul>

<li>tksuoran 29th May 2001 (%Teddy 1.43):<ul>
 <li>Code cleanups; removed Physics and Kamin
 <li>Windowing system fixes
 <li>Now understand several arguments
 <li>Initial dog-fight scene
 </ul>

<li>tksuoran 25th May 2001 (%Teddy 1.42):<ul>
 <li>Fixed view frustum culling
 <li>Small fixes to FFE ship interpreter
 <li>Added spline support to FFE ship interpreter
 </ul>

<li>tksuoran 22nd May 2001 (%Teddy 1.41):<ul>
 <li>Matrix now [col][row] - just like OpenGL
 <li>Testing multiple cameras - sort of works :)
 <li>Updated ROAM code
 <li>Integrated float-quaternion and double-position ModelInstances
 </ul>

<li>tksuoran 15th May 2001 (%Teddy 1.39):<ul>
 <li>Initial support for Frontier First Encounter ships
 <li>Fixed Visual Studio files which were gone wrong in 1.36
 </ul>

<li>tksuoran ? (%Teddy 1.38):<ul>
 <li>Small fixes, not released nor labeled
 </ul>

<li>tksuoran 2nd April 2001 (%Teddy 1.37):<ul>
 <li>Fixed the old version of Sean O'Neils ROAM
 integration so that it works again. But, it
 doesn't work too well, and it's old anyway.
 I hope to have time to put new, improved
 version into next version.
 </ul>

<li>tksuoran 30th March 2001 (%Teddy 1.36):<ul>
 <li>Fixed window system
 <li>Fixed keyboard; cleaned up the whole input system
 <li>Fixed selection by clicking objects with mouse
 <li>Still probelms with FocusManager?
 <li>Cleanups; removed unused classes
 <li>Visual Studio workspace broken sort of
 </ul>

<li>tksuoran 27th March 2001 (%Teddy 1.35):<ul>
 <li>Licensing has changed to GNU Lesser General Public License version 2.1.
 <li>Most of the new Material management works now.
 <li>Keyboard is broken.
 <li>USE_WINDOW_SYSTEM is broken.
 </ul>

<li>tksuoran 7th February 2001 (%Teddy 1.35):<ul>
 <li>Minor update release
 </ul>

<li>tksuoran 1st January 2001 (%Teddy 1.34):<ul>
 <li>Added RenderProperty and TransformView classes; new material management (These were removed later)
 </ul>

<li>tksuoran 18th December 2000 (%Teddy 1.33.3):<ul>
 <li>Further cleaned up UI class
 <li>Added Ship and Strategy classes
 </ul>

<li>tksuoran 14th December 2000 (%Teddy 1.33.2):<ul>
 <li>Initial multithreading code
 </ul>

<li>tksuoran 11th December 2000 (%Teddy 1.33):<ul>
 <li>Added Win32 Midi player (was replaced later with completely other implementation)
 <li>Changed test scene visual appearance
 <li>Split UI implementation to several files
 <li>Tested SDL timer; old still used, I suspect SDL is less precise
 <li>Input code slight modifications, code moved to Input module
 </ul>
	
<li>tksuoran 6th December 2000:<ul>
 <li>Removed ElementArrau (do vertex buffer instead)
 <li>Fixed Visual Studio workspace
 <li>Removed Ship*
 <li>There are now four people in sourceforge development
 team. In addition, Sean O'Neil contributed the ROAM
 implementation, and there are few other interested
 people. But no other contributions yet.
 </ul>

<li>tksuoran 14th November 2000:<ul>
 <li>Added some documentation
 <li>Commented teddy.cpp a little
 <li>Improved LWOB texture importing.
 Still needs work; use SDLImage for image reading
 <li>Added flags to LWSurface LWOB.
 <li>Updated all Visual Studio workspace and project files.
 fix.sh still needs to be fixed to avoid messing up with
 these.
 <li>Changed CVertex.h for MSVC.
 <li>Added SDL, X11 and OpenGL checks to configure script.
 This should help building on linux / posix platforms.
 </ul>

<li>tksuoran (%Teddy 1.32):<ul>
 <li>Simplified test scene
 <li>Added USE_WINDOW_SYSTEM define, without it, use simplified user interface
 <li>Changed Renderable interface, added RenderContext and Renderer
 <li>LightWave importer fixes
 <li>Working on Material
 <li>Linux configure and Makefiles now acceptable
 </ul>

<li>tksuoran (%Teddy 1.29):<ul>
 <li>Working on linux port and linux autoconf
 </ul>

<li>tksuoran (%Teddy 1.26):<ul>
 <li>Integrated Sean O'Neils ROAM planet code
 <li>Improved Lightwave Object loader, which now handles LWO2 format
 </ul>

<li>tksuoran (%Teddy 1.23):<ul>
 <li>Improved? looks of windowing system, rearranged layout
 <li>Added some lightwave objects from Buda5
 <li>Fixed endian IO, thus making Lightwave loader
 <li>Fixed keyboard
 <li>Should build on Win32
 <li>Started integrating Sean O'Neil's planet ROAM routine
 </ul>

<li>tksuoran (%Teddy 1.22):<ul>
 <li>Decided to move from Glut to SDL.
 <li>Removed copyrighted ship models
 <li>Released source in SourceForge
 <li>The release would not build
 <li>Lightwave loader was broken
 <li>Keyboard is different, layout messed up
 </ul>

<li>tksuoran (%Teddy 1.21):<ul>
 <li>Improved windowing system
 </ul>

<li>tksuoran (%Teddy 1.20):<ul>
 <li>Added ElementArray, DynamicMesh, DynamicInstance and DynamicSphere classes
 (All these were later removed)
 <li>Added EliteBody class with very primitive AI (removed later)
 <li>Fixed sphere & icosahedron view volume culling
 <li>Made solar body cycle to go near target
 <li>Tested dynamic subdivision (LOD) for planets - still needs work
 <li>Changed default graphics settings
 <li>Fixed HUD a little
 <li>Added Moon to scene
 </ul>

<li>tksuoran (%Teddy 1.17 - 1.19):<ul>
 <li>Assembly 2000: testing GTS - still needs work
 </ul>

<li>tksuoran (%Teddy 1.16):<ul>
 <li>Implemented view volume clipping
 <li>Implemented (simple) Elite like Scanner
 <li>Fixed resizing View -> Layer
 <li>Objects are now dragged in screen coord sys, not world
 </ul>

<li>tksuoran (%Teddy 1.15):<ul>
 <li>Made module and namespace for Tasks (Scheduler and Task)
 <li>Started work on PhysicalComponents::Style
 <li>Some more documentation on physical components
 </ul>

<li>tksuoran (%Teddy 1.14):<ul>
 <li>Working on Physical Components
 <li>Frames in use; can be dragged
 </ul>

<li>tksuoran (%Teddy 1.13):<ul>
 <li>Improved planet looks
 <li>Improved lowlevel layout code; gradientfill now in use
 <li>Now using namespaces for most classes
 <li>Fixed font
 </ul>

<li>tksuoran (%Teddy 1.12):<ul>
 <li>Fixed starfield back to work
 <li>Fixed lighting back to work (but fix transformations to lights later)
 <li>Removed silly lookat angles which didn't work
 <li>Added instance and solar body cycling (4, 5)
 <li>Changed face not to use fixed x-axis (sort of preserves roll now)
 </ul>

<li>tksuoran (%Teddy 1.11):<ul>
 <li>Started to make Solar System, planets done
 <li>Now carries origo with camera
 <li>Added HUD
 </ul>

<li>tksuoran (%Teddy 1.10):<ul>
 <li>Fixed material problems with LineMesh; had bad code inside glBegin()
 <li>Fixed Torus normals
 <li>Added sphere and torus to scene
 <li>Release
 </ul>

<li>tksuoran (%Teddy 1.9):<ul>
 <li>Cleanups
 <li>Relayouted keyboard
 <li>Extra checks in the code reveal that there is problem with grid displaylist.
 </ul>

<li>tksuoran (%Teddy 1.8):<ul>
 <li>Simple layout features working
 <li>Fixed depth buffer problems - damn range!
 <li>Fixed lighting (specular lighting still looks no good)
 <li>Still problems with Materials, especially the grid is not working
 </ul>

 <li>tksuoran (%Teddy 1.7):<ul>
 <li>Now builds again
 <li>Getting things back to work little by little
 <li>Depth buffer is messed up ):
 <li>Lighting is weird too ):
 </ul>

<li>tksuoran (%Teddy 1.6):<ul>
 <li>Major code clean and rearrangement again
 <li>Whole userinterface is under heavy now-do-it-better phase
 <li>Added some Input classes and made Physical Components folder
 <li>Wondering why depth buffer didn't work with 1.5 when I tried that (1.8: depthrange and depthclearvalue use range 0..1!)
 <li>This version did not build.
 </ul>

<li>tksuoran (%Teddy 1.5):<ul>
 <li>Fixed major bugs in lighting
 <li>Scaled back to reality, no solution to precision problem yet
 </ul>

<li>tksuoran (%Teddy 1.4):<ul>
 <li>Testing downscaled world (still no reference frame / carraying origo with camera)
 <li>Fixed sorting (and missing models) problem - 0.5/(i%6) :D
 <li>Added primitive lighting
 <li>Still no multithreading
 <li>Wrote more game plans
 <li>Introduced camera at origo bug
 <li>Cleaned up source, rethought UI/View/Camera/Scene/RigidBody/Instance relations
 </ul>

<li>tksuoran (%Teddy 1.3):<ul>
 <li>Encountered double precision problem - TODO
 <li>Decided to use two threads; one for rendering, other for input, physics and rest - TODO
 </ul>

<li>tksuoran (%Teddy 1.2):<ul>
 <li>Major cleanup to OpenGL state management
 <li>Investigating Sphere meshes - Added Earth and Moon
 <li>Investigating Facing algorithm
 <li>Investigating anti-aliased lines
 <li>Camera is now ModelInstance, not Mesh
 <li>Investigating cull property to Material
 <li>QuadStrip Element and Sphere Mesh
 <li>Writing game plans
 </ul>

<li>tksuoran (%Teddy 1.1):<ul>
 <li>Added Quaternion class
 <li>Linux/POSIX implementation for Timer and FileScan classes
 </ul>

<li>tksuoran (%Teddy 1.0):<ul>
 <li>Sources are now in single directory
 <li>Model and Component are history, a single Mesh replaces them
 <li>Mesh can contain submeshes (not fully tested)
 <li>Timer class is now used, but it has implementation only for WIN32 target
 <li>FileScan class is drafted, but it has implementation only for WIN32 target
 <li>Primitive physics System class is implemented for simple animations
 </ul>
</ul>

 *********************************************************************************/


