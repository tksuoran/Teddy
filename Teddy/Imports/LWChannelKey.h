
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


#ifndef TEDDY__IMPORTS__LW_CHANNEL_KEY_H
#define TEDDY__IMPORTS__LW_CHANNEL_KEY_H


#include "Teddy/TeddyConfig.h"
#if defined( TEDDY_INCLUDE_LW_SCENE )


namespace Teddy   {
namespace Imports {


//!  LWScene
class LWChannelKey {
public:
	// value time spantype p1 p2 p3 p4 p5 p6
	LWChannelKey(
		float value,
		float time,
		int   shape,
		float p1,
		float p2,
		float p3,
		float p4,
		float p5,
		float p6
	);

	
	inline float tension   (){ return p1; };
	inline float continuity(){ return p2; };
	inline float bias      (){ return p3; };

public:
	float  value;
	float  time;
	int    shape;
	float  p1; 	  //  tension                       incoming time	 param[ 0 ]
	float  p2;    //  continuity                    incoming value  param[ 1 ]
	float  p3;    //  bias                          outgoing time   param[ 2 ]
	float  p4;    //  incoming tangent  param[ 0 ]  outgoing value  param[ 3 ]
	float  p5;    //  outgoing tangent  param[ 1 ]
	float  p6;    //  ignored 0                        
};


};  //  namespace Imports
};  //  namespace Teddy


#endif  //  TEDDY_INCLUDE_LW_SCENE
#endif  //  TEDDY__IMPORTS__LW_CHANNEL_KEY_H

