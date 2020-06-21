
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


#ifndef TEST_EVENTS__BOUNCER__H
#define TEST_EVENTS__BOUNCER__H


#include "Teddy/Behaviour/ModelAnimator.h"
#include <cstring>


//!  Simulated ModelInstance
class Bouncer : public Teddy::Behaviour::ModelAnimator {
public:
	Bouncer(
        Teddy::Models::Model                *model,
        const Teddy::Maths::TVector<double> &bottom,
		const Teddy::Maths::TVector<double> &initial_velocity,
		const Teddy::Maths::TVector<double> &gravity
	);

	virtual void  tick();

protected:
	Teddy::Maths::TVector<double> bottom;
    Teddy::Maths::TVector<double> velocity;
    Teddy::Maths::TVector<double> gravity;
};


#endif  //  TEST_EVENTS__BOUNCER__H

