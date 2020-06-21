
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

	$Id: BaseSimulationTimer.cpp,v 1.2 2002/02/16 12:41:39 tksuoran Exp $
*/


#include "Teddy/Application/BaseSimulationTimer.h"
#include "Teddy/SysSupport/Messages.h"
#include "Teddy/SysSupport/StdSDL.h"
using namespace Teddy::SysSupport;
using namespace Teddy::MixIn;


namespace Teddy       {
namespace Application {


#define SIMULATION_INTERVAL_MS 10


//!  BaseSimulationTimer construtor
BaseSimulationTimer::BaseSimulationTimer()
:
Mutex(),
Timer(SIMULATION_INTERVAL_MS)
{
}


void BaseSimulationTimer::add( Tick *tick ){
	lock();
	add_list.push_back( tick );
	unlock();
}


void BaseSimulationTimer::remove( Tick *tick ){
	lock();
	remove_list.push_back( tick );
	unlock();
	ticks.remove( tick );
}


//!  Tick BaseSimulationTimer
/*virtual*/ void BaseSimulationTimer::tick(){
	lock();
	ticks.merge( add_list );
	unlock();
	list<Tick*>::iterator t_it = ticks.begin();
	while( t_it != ticks.end() ){
		Tick *t = *t_it;
		t->tick();
		t_it++;
	}
}


};  //  namespace Application
};  //  namespace Teddy

