
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


#ifndef TEDDY__MODELS__CONE__H
#define TEDDY__MODELS__CONE__H


#include "Teddy/Models/Model.h"


namespace Teddy  {
namespace Models {


/*!
	\brief Cone shaped Model
	\todo  Add subdivision to ends
*/
class Cone : public Model {
public:
	Cone(
		const std::string &name,
		const double       base_radius,
		const double       top_radius,
		const double       height,
		int                slices,
		int                stacks,
		bool               use_bottom = true,
		bool               use_top    = true
	);
};


};  //  namespace Models
};  //  namespace Teddy;


#endif  //  TEDDY__MODELS__CONE__H

