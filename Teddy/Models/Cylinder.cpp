
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


#include "Teddy/Models/Cylinder.h"


namespace Teddy  {
namespace Models {


/*!
	\brief Cylinder constructor
	\param name Name for new Cylinder
	\param rad Cylinder radius
	\param height Height of cylinder
	\param quads Number of slice subdivisions
*/
Cylinder::Cylinder(
	const std::string &name,
	const double       rad,
	const double       height,
	const int          quads
)
:
Cone ( name,rad,rad,height,quads*2,quads/2 ),
quads( quads )
{
}


};  //  namespace Models
};  //  namespace Teddy

