
/*
	TEDDY - General graphics application library
	Copyright (C) 1999, 2000, 2001	Timo Suoranta
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


#ifndef TEST_EVENTS__STATE__H
#define TEST_EVENTS__STATE__H


#include "Teddy/Maths/Vector.h"
#include "Teddy/Maths/Quaternion.h"
using namespace Teddy::Maths;


//!  LSystem state
class State {
public:
	State();

	void heading( double degrees );
	void pitch  ( double degrees );
	void roll   ( double degrees );

public:
	double     length;
	double     angle;
	double     thickness;
	Vector     position;
	Vector     direction;
	Quaternion quat;
};


#endif  //  TEST_EVENTS__STATE__H

