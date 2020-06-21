
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

	$Id: Cylinder.h,v 1.5 2002/02/16 12:41:39 tksuoran Exp $
*/


#ifndef TEDDY__MODELS__CYLINDER__H
#define TEDDY__MODELS__CYLINDER__H


#include "Teddy/Models/Cone.h"


namespace Teddy  {
namespace Models {


//!  Cylinder shaped Model
class Cylinder : public Cone {
public:
	Cylinder(
		const std::string &name,
		const double       radius,
		const double       height,
		const int          quads
	);

protected:
	double radius;
	int    quads;
};


};  //  namespace Models
};  //  namespace Teddy


#endif  //  TEDDY__MODELS__CYLINDER__H

