
/*
	TEDDY - General graphics application library
	Copyright (C) 1999-2020  Timo Suoranta
	tksuoran@gmail.com

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
*/


/*********************************************************************************/
/*! \page page_build_process How to build Teddy

This page describes how to build %Teddy. Following sections are included:

<ul>
<li>\ref section_quick
<li>\ref section_prepare
<li>\ref section_configure
<li>\ref section_compile
<li>\ref section_link
<li>\ref section_run
</ul>


\section section_quick Quick instructions to build Teddy


\subsection subsection_win32 Windows with Visual C++

<ol>
<li>You will need SDL and related libraries to build and run Teddy.
These are provided in the win32libs.rar archive. Unpack it.
Once you have the files somewhere, you need to tell Visual Studio
about them in menu Tools/Options/Directories.
You will also need to either add the path to dll files to your PATH from
My Computer/Properties/Advanced/Environment Variables, or copy
the .dll files to TeddyTests/Data directory.
<li>Use VisualC/Teddy.dsw
</ol>

\subsection subsection_linux Linux etc.

<ol>
<li>./configure && gmake
<li>cd TeddyTests
<li>./configure && gmake
</ol>


\section section_prepare Preparing to build Teddy


The configure script may have trouble locating SDL. This usually
means that you have not SDL installed, or you SDL is not in your
path (SDL contains configuration script which gets to path when
you install it), or your SDL is too old. It is also possible
(even likely if you have specific linux distribution, and/or install
newer SDL manually) that you have several versions of SDL in your
system, and they mess up each other.

If you are trying to build %Teddy on multiuser system where you
are not superuser, there might be SDL installed on the system,
but it might not be in the default path. Ask if SDL is present
and where it would be. You have also option to install your own
version of SDL using prefix option of SDL configure script. You
may get it work even on top of older version of SDL if you set
paths correctly.


\section section_compile Compiling Teddy library


Compiling may fail for several reasons. If you get errors about
SDL or other library includes in Win32 MSVC environment, you must
add SDL includes (also libs) to Tools/Options/Directories in Visual
Studio. In linux the ./configure -script usually makes sure SDL
and other libraries will work.

Compiling may also fail if for some reason platform dependent
code is tried to be built on alien platform. This will happen
when someone who has written the code has not been careful.
You will have to isolate the offending code and disable it for
your platform, or write implementation. I mean, you could, if
you wanted to. Usually you should just let me know.

Compiling may also fail just because there is error in the code.
This can happen when someone fixes the code when resolving CVS

Visual studio project and workspace files may be corrupted in
some weird way. This may happen when development takes place in
linux side and things change. You may need to add and or remove
files or even add new projects.

If you use the same directory on multiple machines, from network
filesystem, or simply pack and copy to other machine, or upgrade
you machine, you should remember to clean the old working files.
This problem is severe in linux environment; configure cache may
be incorrect for the new system; Makefile generated by configure may
be outdated, etc. In linux environment source dependencies are
generated by Makefile by scanning source directories for sources.
Thus if new files are added or got from CVS update, you will have
to make clean, maybe rerun configure and make sure Makefile is updated.


\section section_link Linking programs with Teddy library


In linux environment you may get errors about missing symbols even
though source code is fine and compiles without errors. It turns out
that gcc processes files <em>in the order which they are given</em> on
the command line. When gcc is linking libraries, it only picks those
symbols that have been referenced so far. I think I have fixed these
problems now by using ar to create a single .lib file from all program
.o files before doing gcc linking with just .lib files.

If you have not set up SDL and other libraries correctly you will
have problems with linking, too.

You will need SDL library. Other libraries, SDL_image and SDL_mixer,
are optional. SDL_image further requires libpng, libz, and libpng.


\section section_run Running programs using Teddy library


Executable will happily crash if it can not find some crucial
data files. The normal ./configure && make procedure in linux
will copy executables to the Release/ directory, which is outside
the CVS, but part of the source archive. You must run executables
there.
*/


