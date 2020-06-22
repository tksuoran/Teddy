
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


#ifndef TEST_EVENTS__ORBITER__H
#define TEST_EVENTS__ORBITER__H


#include "Teddy/Behaviour/ModelAnimator.h"
#include <cstring>


//!  Simulated ModelInstance
class Orbiter : public Teddy::Behaviour::ModelAnimator {
public:
	Orbiter(
        Teddy::Models::Model                *model,
        const Teddy::Maths::TVector<double> &center,
		const Teddy::Maths::TVector<double> &a_axis,
		const Teddy::Maths::TVector<double> &b_axis,
		const double                         cycle_time,
		const double                         cycle_offset
	);

	virtual void  tick();

protected:
	Teddy::Maths::TVector<double> center;
	Teddy::Maths::TVector<double> a_axis;
    Teddy::Maths::TVector<double> b_axis;
    double                        cycle_time;
    double                        cycle_offset;
};


#endif  //  TEST_EVENTS__ORBITER__H

