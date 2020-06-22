
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


#include "Teddy/SysSupport/StdSDL.h"
#include "Bouncer.h"
#include "Teddy/Models/Model.h"

using namespace Teddy::Behaviour;
using namespace Teddy::Models;
using namespace Teddy::Maths;


Bouncer::Bouncer(
	Model              *model,
	const DoubleVector &bottom,
	const DoubleVector &initial_velocity,
	const DoubleVector &gravity
)
:
ModelAnimator( model            ),
bottom       ( bottom           ),
velocity     ( initial_velocity ),
gravity      ( gravity          )
{
    model->setPosition( bottom );
}


/*virtual*/ void Bouncer::tick(){
	Vector pos = model->getPosition();
    velocity += gravity;
	pos      += velocity;
	if( pos[1] < bottom[1] ){
		velocity = -velocity;
		while( pos[1] < bottom[1] ){
            pos += velocity;
		}
	}
    model->setPosition( pos );
}

