
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

	$Id: Timer.cpp,v 1.6 2002/02/16 12:41:39 tksuoran Exp $
*/


#include "Teddy/SysSupport/Timer.h"
#include "Teddy/SysSupport/StdSDL.h"


namespace Teddy      {
namespace SysSupport {


//!  Constructor
Timer::Timer( Uint32 frequency ){
	this->frequency  = frequency;
	this->running    = false;
	this->sdl_thread = SDL_CreateThread( Timer::sdl_thread_function, this );
}


Uint32 Timer::getFrequency(){
	return frequency;
}


void Timer::setFrequency( Uint32 frequency ){
	this->frequency = frequency;
}


/*virtual*/ void Timer::start(){
	sync    = SDL_GetTicks();
	running = true;
}


/*virtual*/ void Timer::stop(){
	running = false;
}


void Timer::run(){
	
	for(;;){
		while( running==false ) SDL_Delay( 10 );
		sync += frequency;
		for(;;){
			Uint32 now  = SDL_GetTicks(); if( now  > sync ) break;
			Uint32 diff = sync-now;       if( diff < 10   ) break;
			SDL_Delay( 10 );
		}
		tick();
	}

}


//!  Default tick() implementation
/*virtual*/ void Timer::tick(){
}


//!  This is the timer update function implementation.
int Timer::sdl_thread_function( void *data ){
	Timer *t = (Timer *)( data );

	t->run();
	return 0;
}


};  //  namespace SysSupport
};  //  namespace Teddy

