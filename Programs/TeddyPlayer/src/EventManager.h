
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


#ifndef TEDDY_PLAYER__EVENT_MANAGER__H
#define TEDDY_PLAYER__EVENT_MANAGER__H


#include "Teddy/PhysicalComponents/EventListener.h"
#include "Teddy/SysSupport/StdSDL.h"

#include "CameraController.h"
#include "Node.h"


//  Forward declarations
namespace Teddy {
	namespace Models { class Model; };
};
using namespace Teddy::Models;


//!  EventManager
class EventManager 
: 
public Node,
public Teddy::PhysicalComponents::EventListener {
public:
	EventManager( Root *root );

	void          bindController( Teddy::Models::Model *model );

	//  WindowManager calls these methods when there is mouse event
	virtual bool  mouseKey     ( const Teddy::PhysicalComponents::Event &e );
	virtual bool  mouseMotion  ( const Teddy::PhysicalComponents::Event &e );
	
	//  WindowManager calls these methods when there is keyboard event
	virtual bool  keyDown      ( const Teddy::PhysicalComponents::Event &e );
	virtual bool  keyUp        ( const Teddy::PhysicalComponents::Event &e );

protected:
	CameraController *controller;
};


#endif  //  TEDDY_PLAYER__EVENT_MANAGER__H

