
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


#ifndef TEDDY__IMPORTS__LW_CHANNEL_ENVELOPE__H
#define TEDDY__IMPORTS__LW_CHANNEL_ENVELOPE__H


#include "Teddy/TeddyConfig.h"
#if defined( TEDDY_INCLUDE_LW_SCENE )


#include "Teddy/SysSupport/StdList.h"


namespace Teddy   {
namespace Imports {


class LWChannelKey;


//  Motion channels
#define LW_CHANNEL_X   0  //   0 - Move X                                          
#define LW_CHANNEL_Y   1  //   1 - Move Y                                          
#define LW_CHANNEL_Z   2  //   2 - Move Z                                          
#define LW_CHANNEL_H   3  //   3 - Rotate Heading                                  
#define LW_CHANNEL_P   4  //   4 - Rotate Pitch                                    
#define LW_CHANNEL_B   5  //   5 - Rotate Bank                                     
#define LW_CHANNEL_SX  6  //   6 - Scale X / Size X (channels are connected)      
#define LW_CHANNEL_SY  7  //   7 - Scale Y / Size Y (channels are connected)       
#define LW_CHANNEL_SZ  8  //   8 - Scale Z / Size Z (channels are connected)       
#define LW_CHANNEL_RX  9  //   9 - RestLength X                                    
#define LW_CHANNEL_RY 10  //  10 - RestLength Y                                    
#define LW_CHANNEL_RZ 11  //  11 - RestLength Z                                    
#define LW_CHANNEL_PX  9  //   9 - Move PivotPoint X 
#define LW_CHANNEL_PY 10  //  10 - Move PivotPoint Y
#define LW_CHANNEL_PZ 11  //  11 - Move PivotPoint Z


//  Motion channel span types
#define LW_SPAN_TCB        0  //  TCB (Kochanek-Bartels) 
#define LW_SPAN_HERMITE    1  //  Hermite 
#define LW_SPAN_1D_BEZIER  2  //  1D Bezier (obsolete, equivalent to Hermite) 
#define LW_SPAN_LINEAR     3  //  Linear 
#define LW_SPAN_STEPPED    4  //  Stepped 
#define LW_SPAN_2D_BEZIER  5  //  2D Bezier 

//  Motion channel pre and post behaviors
#define LW_BEHAVIOR_RESET          0  //  Reset          Sets the value to 0.0. 
#define LW_BEHAVIOR_CONSTAT        1  //  Constant       Sets the value to the value at the nearest key. 
#define LW_BEHAVIOR_REPEAT         2  //  Repeat         Repeats the interval between the first and last keys (the primary interval). 
#define LW_BEHAVIOR_OSCILLATE      3  //  Oscillate      Like Repeat, but alternating copies of the primary interval are time-reversed. 
#define LW_BEHAVIOR_OFFSET_REPEAT  4  //  Offset Repeat  Like Repeat, but offset by the difference between the values of the first and last keys. 
#define LW_BEHAVIOR_LINEAR         5  //  Linear         Linearly extrapolates the value based on the tangent at the nearest key. 


class LWChannelEnvelope {
public:
	LWChannelEnvelope( int channel_id );

	int    getChannelId();
	void   insert      ( LWChannelKey *channel_key );
	void   setBehaviors( int pre, int post );
	float  eval        ( float key_position );

protected:
	list<LWChannelKey*> keys;
	int                 channel_id;
	int                 steps;
	int                 pre_behavior;
	int                 post_behavior;
	float               last_time;
	float               last_value;
};


};  //  namespace Imports
};  //  namespace Teddy


#endif  //  TEDDY_INCLUDE_LW_SCENE
#endif  //  TEDDY__IMPORTS__LW_CHANNEL_ENVELOPE__H

