
/*
	TSGL - Teddy Space Game Library
	Copyright (C) 2002 Timo Suoranta
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


#ifndef SPACE_GAME__SCANNER__H
#define SPACE_GAME__SCANNER__H


#include "Teddy/PhysicalComponents/Area.h"

#include "Node.h"

//  Forward declarations
namespace Teddy {
	namespace Models  { class ModelInstance; };
	namespace Graphics{ class Texture;       };
	namespace Scenes  { class Camera;        };
};
using namespace Teddy::Graphics;
using namespace Teddy::PhysicalComponents;
using namespace Teddy::Scenes;


class Ship;


//!  A simple radar scanner showing objects in scene relative to player ship
class Scanner 
: 
public Node,
public Area {
public:
	Scanner( Root *root );

	void cycle();

	virtual void drawSelf();

protected:	
	int      range;
	Texture *txt;
};


#endif  //  SPACE_GAME__SCANNER__H

