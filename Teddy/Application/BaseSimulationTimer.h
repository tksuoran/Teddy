
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


#ifndef TEDDY__APPLICATION__BASE_SIMULATION_TIMER__H
#define TEDDY__APPLICATION__BASE_SIMULATION_TIMER__H


#include "Teddy/SysSupport/StdList.h"
#include "Teddy/SysSupport/Timer.h"
#include "Teddy/MixIn/Mutex.h"
#include "Teddy/MixIn/Tick.h"


namespace Teddy       {
namespace Application {


class BaseSimulationTimer 
: 
public Teddy::MixIn::Mutex,
public Teddy::SysSupport::Timer
{
public:
	BaseSimulationTimer();

	virtual void tick();

	void add   ( Teddy::MixIn::Tick *tick );
	void remove( Teddy::MixIn::Tick *tick );

protected:
	std::list<Teddy::MixIn::Tick*> ticks;
	std::list<Teddy::MixIn::Tick*> add_list;
	std::list<Teddy::MixIn::Tick*> remove_list;
};


};  //  namespace Application
};  //  namespace Teddy


#endif  //  TEDDY__APPLICATION__BASE_SIMULATION_TIMER__H

