
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

	$Id: Graphics.h,v 1.3 2002/01/22 19:30:04 tksuoran Exp $
*/


namespace Teddy {

/*!

This namespace contains the lower part of graphics rendering
architecture of %Teddy. Other parts are in several other modules;
you should at least know that PhysicalComponents module has Projection
class, which is responsible for applying materials and rendering any
3D graphics.

While some parts of OpenGL have been encapsulated into View class
in Graphics, there are still a lot of direct OpenGL calls all over
%Teddy. In the future all OpenGL should be made through encapsulated
interface.
*/
namespace Graphics {
};
};


