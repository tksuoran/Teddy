
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

	$Id: Root.cpp,v 1.1 2002/02/16 12:48:45 tksuoran Exp $
*/


/*!
	\file
	\brief  Teddy example program for Lightwave objects and scenes

	Keyboard input messages are handled as follows:

	- left    / right     : strafe left / right
	- up      / down      : move   up   / down

	Mouse input messages are handled as follow:

	- motion       : look at
	- left button  : move forward
	- right button : move backward
*/


#include "Teddy/Application/BaseSimulationTimer.h"   //  SimulationTimer::SimulationTimer()
#include "Teddy/Teddy.h"                             //  teddy_init()

#include "Root.h"                        //  Root::Root()
#include "UserInterface.h"               //
#include "ObjectManager.h"               //
#include "Teddy/SysSupport/StdIO.h"
#include "Teddy/SysSupport/Messages.h"
using namespace Teddy::Graphics;
using Teddy::Application::BaseSimulationTimer;


//!  main() for Teddy programs
TEDDY_MAIN


//int play( void );

//!  This is the basic test setup constructor.
/*virtual*/ void Root::start( int argc, char **argv ){
	BaseRoot::start( argc, argv );

#if 0
	_CrtSetDbgFlag( int newFlag );
int tmp;

// Get the current bits
tmp = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);

// Clear the upper 16 bits and OR in the desired freqency
tmp = (tmp & 0x0000FFFF) | _CRTDBG_CHECK_EVERY_16_DF;

// Set the new bits
_CrtSetDbgFlag(tmp);
}
#endif

	fprintf( stderr, "Hello here is TeddyPlayer\n" );

	user_interface   = new UserInterface      ( this );  //  Opens view
	object_manager   = new ObjectManager      ( this );  //  Creates scene and camera
	simulation_timer = new BaseSimulationTimer();

	fprintf( stderr, "user_interface  ->addComponents();\n" );
    user_interface  ->addComponents();  //  Create UserInterface
	fprintf( stderr, "object_manager  ->adjustToScene();\n" );
    object_manager  ->adjustToScene();  //  Make camera and controls nice
	fprintf( stderr, "simulation_timer->start        ();\n" );
    simulation_timer->start        ();  //  Start simulation timer
	fprintf( stderr, "user_interface  ->enterRunLoop ();\n" );
	user_interface  ->enterRunLoop ();  //  Enter run loop
}

