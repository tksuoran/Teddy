
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


#ifndef TEDDY__APPLICATION__BASE_AUDIO_MANAGER__H
#define TEDDY__APPLICATION__BASE_AUDIO_MANAGER__H


#include "Teddy/MixIn/Options.h"


namespace Teddy       {
namespace Application {


//!  BaseAudioManager
class BaseAudioManager {
public:
	static const int OPT_MASTER;   //  unused
	static const int OPT_SAMPLES;
	static const int OPT_MIDI;
	static const int OPT_CD;       //  unused

public:
	BaseAudioManager( const Teddy::MixIn::Options &options );

	//  audio API
	void                   playWav   ( void *chunk );
	Teddy::MixIn::Options &getOptions();

protected:
	Teddy::MixIn::Options options;
};


};  //  namespace Application
};  //  namespace Teddy


#endif  //  TEDDY__APPLICATION__BASE_AUDIO_MANAGER__H

