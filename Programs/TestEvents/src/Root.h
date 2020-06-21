
/*
	TEDDY - General graphics application library
	Copyright (C) 1999, 2000, 2001	Timo Suoranta
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

	$Id: Root.h,v 1.2 2002/02/16 12:47:30 tksuoran Exp $
*/


#ifndef TEST_EVENTS__ROOT__H
#define TEST_EVENTS__ROOT__H


#include "Teddy/Application/BaseRoot.h"
#include "Teddy/Application/BaseSimulationTimer.h"
using namespace Teddy::Application;


class EventManager;
class ObjectManager;
class UserInterface;


//!  Inherit from default root class
class Root : public BaseRoot {
public:
	virtual void start( int argc, char **argv );

	inline EventManager        *getEventManager   (){ return event_manager;    }
	inline ObjectManager       *getObjectManager  (){ return object_manager;   }
	inline BaseSimulationTimer *getSimulationTimer(){ return simulation_timer; }
	inline UserInterface       *getUserInterface  (){ return user_interface;   }

private:
	EventManager        *event_manager;
	ObjectManager       *object_manager;
	BaseSimulationTimer *simulation_timer;
	UserInterface       *user_interface;
};


#endif  //  TEST_EVENTS__ROOT__H

