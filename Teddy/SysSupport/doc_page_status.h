
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
/*! \page page_status  Current status of Teddy

At the moment there is a lot of work that needs to be done.
The list below contains some things in unsorted order. Feel
free to work any of these problems, and or list new ones!
I am sure we can make this list a long one..

<ul>
<lI>Rendering architecture should be improved so that it
    knows and uses vertex arrays (including compiled
	vertex arrays and NVidia stuffs) - At the moment Teddy
	uses very unoptimized rendering, no vertex arrays.

	<em>Update:</em>
	Display lists are now being used by Models::Geometry


<li>Rendering architecture should be improved so that it
    knows how to get best performance when handling materials.
	Applying different material means OpenGL state change, which
	is usually slow.

<li>Rendering architecture should be improved so that it
	knows how to do multiple depth buffer passes, or something,
	to get rid of limited depth buffer precision.

<li>I would like to have alpha blending effects like explosions
	and engine glows added to the rendering architecture. Some of
	these need that vertices are manually projected to screen
	coordinates.
	
	<em>Update:</em>
	There is simple sprite support now in TeddyTests/TestEvents,
    Enable with --glow startup option. Still buggy

<li>Texture support needs testing and improving.
	Multitexturing is not yet used.

<li>A proper installer for both Win32 and linux would be nice;
	there is none for either at the moment.

	<em>Update:</em>
    Linux scripts are now a bit better.

<li>The physical user interface component class hierarchy is very
    experimental. It would be nice to get something robust out of it
	eventually. It might be a good idea to get some basic components
	working 'soon', as they potentially could help development.

    <em>Update:</em>
	Since 1.78 area layout code is improved.

<li>The existing code does not pay much attention to memory leaks
	(which are guaranteed to exist). Destructors should be properly
	implemented at some point.

    <em>Update:</em>
	I've run Teddy with Valgrind, and found fewer leaks than I expected :)

<li>The whole source would benefit from refactoring.

<li>Documentation can always be improved.

</ul>
 *********************************************************************************/


