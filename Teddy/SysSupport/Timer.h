
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

	$Id: Timer.h,v 1.6 2002/02/16 12:41:39 tksuoran Exp $
*/


#ifndef TEDDY__SYS_SUPPORT__TIMER_H
#define TEDDY__SYS_SUPPORT__TIMER_H


#include "Teddy/MixIn/Tick.h"
#include "Teddy/SysSupport/StdSDL.h"


namespace Teddy      {
namespace SysSupport {


//!  Wrapper for SDL thread which runs timer
class Timer : public Teddy::MixIn::Tick {
public:
	Timer( Uint32 frequency );

	//  Thread (Teddy::SysSupport::Timer at the moment) API
	virtual void run ();
	virtual void stop();

	//  Teddy::MixIn::Tick  API
	virtual void tick();

	Uint32 getFrequency();
	void   setFrequency( Uint32 frequency );
	void   start       ();

	//static Uint32 sdl_timer_callback( Uint32 interval, void *param );
	static int    sdl_thread_function( void *data );

protected:
	SDL_Thread *sdl_thread;
	Uint32      sync;
	Uint32      frequency;
	bool        running;
};


};  //  namespace SysSupport
};  //  namespace Teddy


#endif  //  TEDDY__SYS_SUPPORT__TIMER_H

