
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


#ifndef TEDDY__IMPORTS__LW_MOTION__H
#define TEDDY__IMPORTS__LW_MOTION__H


#include "Teddy/TeddyConfig.h"
#if defined( TEDDY_INCLUDE_LW_SCENE )


#include "Teddy/SysSupport/StdMap.h"


namespace Teddy   {
namespace Imports {


class LWChannelEnvelope;


typedef map<int, LWChannelEnvelope*> int_to_LWChannelEnvelope;


//!  LWMotion
class LWMotion {
public:
	LWMotion();

	void               insert    ( LWChannelEnvelope *channel_envelope );
	LWChannelEnvelope *getChannel( int channel_id );

protected:
	int_to_LWChannelEnvelope channel_envelopes;
};


};  //  namespace Imports
};  //  namespace Teddy


#endif  //  TEDDY_INCLUDE_LW_SCENE
#endif  //  TEDDY__IMPORTS__LW_MOTION__H

