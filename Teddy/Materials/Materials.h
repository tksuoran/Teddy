
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


namespace Teddy {

/*!
	This namespace contains material management architecture of %Teddy.

	The material management in %Teddy is compilecated by the fact that
	objects material properties can be overridden by the Projection
	Area to which they are drawn. Middle part of this management is
	implemented by the Material class. The higher part of the material
	management is implemented in the Projection class in PhysicalComponents
	namespace. The lowlevel material apply methods are in View class
	of Graphics namespace.
*/
namespace Materials {
};
};





