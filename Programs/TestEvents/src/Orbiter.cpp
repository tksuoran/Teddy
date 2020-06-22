
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


#include "Teddy/Models/Model.h"
#include "Teddy/SysSupport/StdSDL.h"
#include "Orbiter.h"

using namespace Teddy::Behaviour;
using namespace Teddy::Models;
using namespace Teddy::Maths;


Orbiter::Orbiter(
	Model              *model,
	const DoubleVector &center,
	const DoubleVector &a_axis,
	const DoubleVector &b_axis,
	const double        cycle_time,
	const double        cycle_offset
)
:
ModelAnimator( model        ),
center       ( center       ),
a_axis       ( a_axis       ),
b_axis       ( b_axis       ),
cycle_time   ( cycle_time   ),
cycle_offset ( cycle_offset )
{
}


/*virtual*/ void Orbiter::tick(){
    double phase = ((double)SDL_GetTicks()) / cycle_time + cycle_offset;
    model->setPosition(  center + (a_axis * sin(phase)) + (b_axis * cos(phase))  );
}

