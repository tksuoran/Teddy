
/*
	TSGL - Teddy Space Game Library
	Copyright (C) 2002 Timo Suoranta
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

	$Id:  $
*/


#ifndef SPACE_GAME__CABIN__H
#define SPACE_GAME__CABIN__H


#include "Teddy/PhysicalComponents/Area.h"


//  Forward declarations
namespace Teddy {
	namespace Models { class Model; };
};
using namespace Teddy::Models;
using namespace Teddy::PhysicalComponents;


/*!
	A cabin mesh can be drawn on top of shipcamera view to add
	feeling of being inside a ship.
*/
class Cabin : public Area {
public:
	Cabin( const std::string &name );

	virtual void drawSelf();

protected:
	Model *model;

};


#endif  //  SPACE_GAME__CABIN__H

