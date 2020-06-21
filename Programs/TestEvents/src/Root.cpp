
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

	$Id: Root.cpp,v 1.3 2002/03/12 10:44:29 tksuoran Exp $
*/


/*!
	\file
	\brief   Teddy example program for input events
	\warning The documentation is old and needs to be updated

	This example program demonstrates how to make an
	interactive program using the Teddy framework.
	Texture mapping and use of Lightwave object
	loader is also demonstrated.

	The program creates a scene from several objects.
	Some objects are animated in the simulation timer.
	The test class is inherited from EventListener so
	that it can receive input event messages.

	Input event messages are handled in the main thread.
	The handlers only record the fact that control is
	changed. Controls are actually applied in the
	simulation timer at regular intervals.

	Keyboard input messages are handled as follows:

	- left    / right     : strafe left / right
	- up      / down      : move   up   / down

	Mouse input messages are handled as follow:

	- motion       : look at
	- left button  : move forward
	- right button : move backward
*/


#include "Teddy/Application/BaseSimulationTimer.h"   //  SimulationTimer::SimulationTimer()
#include "Teddy/PhysicalComponents/WindowManager.h"  //  setFocus()
#include "Teddy/Scenes/Camera.h"            
#include "Teddy/SysSupport/Messages.h"
#include "Teddy/Teddy.h"                             //  teddy_init()
#include "Teddy/SysSupport/StdIO.h"

#include "Root.h"                         //  Root::Root()
#include "UserInterface.h"                //  
#include "ObjectManager.h"                //

using namespace Teddy::Application;
using namespace Teddy::Graphics;
using namespace Teddy::PhysicalComponents;
using namespace Teddy::Scenes;

int play( void );


//!  main() for Teddy programs
TEDDY_MAIN
/*int SDL_main( int argc, char **argv ){
    fprintf( stdout, "Hello!\n" );
    Root *root = new Root();
    root->start( argc, argv );
    return 0;
} */


/*virtual*/ void Root::start( int argc, char **argv ){
    msg( M_INIT, "Root::start()" );

    BaseRoot::start( argc, argv );

	//play();

	simulation_timer = new BaseSimulationTimer();
	user_interface   = new UserInterface      ( this );  //  Opens view
	object_manager   = new ObjectManager      ( this );  //  Creates scene and camera

	user_interface  ->addComponents ();  //  Create UserInterface
	simulation_timer->start         ();  //  Start simulation timer
	user_interface  ->enterRunLoop  ();  //  Enter run loop
}




#if 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Teddy/MiniFMod/minifmod.h"

unsigned int fileopen( char *name );

unsigned int fileopen( char *name ){
  return((unsigned int)fopen(name, "rb"));
}

void fileclose( unsigned int handle ){
  fclose((FILE *)handle);
}

int fileread( void *buffer, int size, unsigned int handle ){
  return(fread(buffer, 1, size, (FILE *)handle));
}

void fileseek( unsigned int handle, int pos, signed char mode ){
  fseek((FILE *)handle, pos, mode);
}

int filetell( unsigned int handle ){
  return(ftell((FILE *)handle));
}


int play( void ){
  FMUSIC_MODULE *mod;
  FSOUND_File_SetCallbacks( fileopen, fileclose, fileread, fileseek, filetell );

  // Initialize
  if( !FSOUND_Init(44100, 0) ){
    return 1;
  }

  // Load song
  mod = FMUSIC_LoadSong( "Data/xm/empty.xm", NULL );
  if( !mod ){
    FSOUND_Close();
    return 1;
  }

  // Play song
  FMUSIC_PlaySong( mod );
	return 0;
    do {
      int   ord    = 0;
	  int   row    = 0;
      float mytime = 0;
      ord    = FMUSIC_GetOrder      ( mod );
      row    = FMUSIC_GetRow        ( mod );
      mytime = (float)FMUSIC_GetTime( mod ) / 1000.0f;
    }
    while( true );

  FMUSIC_StopSong( mod );
  FMUSIC_FreeSong( mod );
  FSOUND_Close   ();

  return 0;
}


#endif