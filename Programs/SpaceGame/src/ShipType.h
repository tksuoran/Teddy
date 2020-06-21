
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


#ifndef SPACE_GAME__SHIP_TYPE__H
#define SPACE_GAME__SHIP_TYPE__H


#include "Teddy/MixIn/Named.h"
#include "Teddy/MixIn/Options.h"
#include "Teddy/SysSupport/StdMaths.h"


//  Forward declarations
namespace Teddy {
	namespace MOdels { class Model; };
};
using namespace Teddy::MixIn;
using namespace Teddy::Models;


#define PITCH_CONST  (   1.0 * M_2_PI/1000000.0 )  //  RADS PER TICK
#define ROLL_CONST   (   1.0 * M_2_PI/1000000.0 )  //  RADS PER TICK
#define MAX_PITCH    ( 500.0 * M_2_PI/1000000.0 )  //  RADS PER TICK
#define MAX_ROLL     ( 500.0 * M_2_PI/1000000.0 )  //  RADS PER TICK
#define ACCEL_CONST  (   0.0020)                    //  m/s PER TICK
#define MAX_SPEED    (   6.5000)                    //  m/s PER TICK


//!  ShipType
class ShipType : public Named {
public:
	ShipType(
		const std::string &name,
		Model             *model,
		float a  = ACCEL_CONST,
		float ms = MAX_SPEED,
		float pc = PITCH_CONST,
		float rc = ROLL_CONST,
		float mp = MAX_PITCH,
		float mr = MAX_ROLL
	);

	Model *newModel       ( const std::string &name );
	Model *getModel       ();
	float  getAcceleration();
	float  getRollConst   ();
	float  getPitchConst  ();
	float  getMaxRoll     ();
	float  getMaxPitch    ();
	float  getMaxSpeed    ();

protected:
	Model *model;
	float  acceleration;
	float  pitch_const;
	float  roll_const;
	float  max_pitch;
	float  max_roll;
	float  max_speed;
};


#endif  //  SPACE_GAME__SHIP_TYPE__H

