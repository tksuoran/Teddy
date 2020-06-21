
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

	$Id:  $
*/


#include "Bender.h"
#include "Teddy/Maths/Quaternion.h"
using namespace Teddy::Behaviour;
using namespace Teddy::Maths;
using namespace Teddy::Models;


Bender::Bender(
    Teddy::Models::Model                *model,
    const Teddy::Maths::TVector<double> &axis,
	const float                         &min_angle,
	const float                         &max_angle,
	const float                         &cycle_time
)
:
ModelAnimator( model      ),
axis         ( axis       ),
min_angle    ( min_angle  ),
max_angle    ( max_angle  ),
cycle_time   ( cycle_time )
{
}


/*virtual*/ void Bender::tick(){
	Quaternion &attitude = model->getAttitude();
	double phase = ((double)SDL_GetTicks()) / cycle_time;

	float angle = (float)( max_angle * sin( phase ) );

	attitude = Quaternion( axis, angle );
}

