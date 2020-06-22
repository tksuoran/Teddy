
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


#ifndef TEDDY__PHYSICAL_COMPONENTS__GRADIENT_FILL__H
#define TEDDY__PHYSICAL_COMPONENTS__GRADIENT_FILL__H


#include "Teddy/PhysicalComponents/Fill.h"
#include "Teddy/Graphics/Color.h"
using namespace Teddy::Graphics;


namespace Teddy              {
namespace PhysicalComponents {


/*!
	\brief   Gradient userinterface component area fill
	\warning Very incomplete
	\bug     Destructors missing?
	\bug     OpenGL displaylists not yet used
*/
class GradientFill : public Fill {
public:
	GradientFill( const Color &left_top, const Color &right_top, const Color &right_bottom, const Color &left_bottom );

	virtual void drawSelf();

protected:
	Color left_top;
	Color right_top;
	Color right_bottom;
	Color left_bottom;
};


};  //  namespace PhysicalComponents
};  //  namespace Teddy


#endif  //  TEDDY__PHYSICAL_COMPONENTS__GRADIENT_FILL__H

