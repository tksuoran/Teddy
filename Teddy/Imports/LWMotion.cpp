
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

	$Id: LWMotion.cpp,v 1.1 2002/02/16 12:41:39 tksuoran Exp $
*/


#include "Teddy/TeddyConfig.h"
#if defined( TEDDY_INCLUDE_LW_SCENE )


#include "Teddy/Imports/LWChannelEnvelope.h"
#include "Teddy/Imports/LWMotion.h"

#include <stdlib.h>


namespace Teddy   {
namespace Imports {


LWMotion::LWMotion(){
}


void LWMotion::insert( LWChannelEnvelope *channel_envelope ){
	channel_envelopes.insert(
		make_pair(
			channel_envelope->getChannelId(),
			channel_envelope
		)
	);
}


LWChannelEnvelope *LWMotion::getChannel( int channel_id ){
	LWChannelEnvelope                  *channel_envelope = NULL;
	int_to_LWChannelEnvelope::iterator  c_it = 
		channel_envelopes.find( channel_id );
	if( c_it != channel_envelopes.end() ){
		channel_envelope = (*c_it).second;
	}
	return channel_envelope;
}


};  //  namespace Imports
};  //  namespace Teddy


#endif  //  TEDDY_INCLUDE_LW_SCENE
