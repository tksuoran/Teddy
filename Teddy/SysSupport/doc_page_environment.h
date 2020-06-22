
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
/*! \page page_environment Teddy development environment

Notes about environment, library and tool requirements

%Teddy is intendent to work on multiple platforms,
although only Win32 and linux environments have been
tested so far. FreeBSD and Amiga versions have been
known to be built at least once.

%Teddy is developed concurrently in Microsoft Visual
Studio C++ version 6 and GNU/Linux using g++. Workspace
and Project files are included for VC, and autoconf,
configure, and make tools are supported for GNU/Linux.

%Teddy is written in C++, and uses STL, so you will
need a compiler which supports these; LCC for example
will not work. I have used Visual Studio 6 in Win32
environment and g++ in GNU/Linux. Project and workspace
files are provided for Visual Studio 6, and configure
script is provided for GNU/Linux.

%Teddy depends on several libraries, which you need
before you can build %Teddy. The SDL library is the
only absolutely required library. Others are optional,
but highly recommended.

The most important library is
<a href="http://www.libsdl.org/index.html">
the Simple Directmedia Library</a> - SDL. Setting
up SDL for %Teddy should be simple in linux. For Windows,
I have included headers and precompiled libraries.

<ul>
<li><a href="http://www.libsdl.org">SDL</a>
<li><a href="http://www.libsdl.org/projects/SDL_image/index.html">SDL_image</a>
 <ul>
 <li><a href="http://www.ijg.org/">libjpeg</a>
 <li><a href="http://www.cdrom.com/pub/png/">libpng</a>
 <li><a href="http://www.cdrom.com/pub/infozip/zlib/">libz</a>
 </ul>
<li><a href="http://gts.sf.net">GTS</a>
 <ul>
 <li>glib
 </ul>
</ul>

Documentation for %Teddy is generated using
<a href="http://www.stack.nl/~dimitri/doxygen/index.html">Doxygen</a>.
Doxygen is not required to build and test %Teddy, but reading
documentation of Doxygen helps to place documentation into sourcecode.
Doxygen is only required to regenerate and update documentation from the
sourcecode.
*********************************************************************************/


