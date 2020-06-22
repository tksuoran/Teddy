
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


#ifndef TEDDY__SCENES__SKY_BOX__H
#define TEDDY__SCENES__SKY_BOX__H


#include "Teddy/Models/Model.h"
using Teddy::Models            ::Model;
using Teddy::Materials         ::Material;
using Teddy::PhysicalComponents::Projection;


namespace Teddy  {
namespace Scenes {


//!  Camera skybox model
class SkyBox : public Model {
public:
	SkyBox();

	virtual void drawElements ( Projection *p );

protected:
	Material *front;
	Material *back;
	Material *left;
	Material *right;
	Material *up;
	Material *down;
};


};  //  namespace Scenes
};  //  namespace Teddy


#endif  //  TEDDY__SCENES__SKY_BOX__H

