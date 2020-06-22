
/*
	TSGL - Teddy Space Game Library
	Copyright (C) 2002 Timo Suoranta
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


#ifndef PACE_GAME__FRONT_CAMERA__H
#define PACE_GAME__FRONT_CAMERA__H


#include "Teddy/MixIn/Tick.h"
#include "Teddy/PhysicalComponents/EventListener.h"
#include "Teddy/PhysicalComponents/Projection.h"
#include "Node.h"


//  Forward declarations
namespace Teddy {
	namespace Scenes             { class Camera;      };
	namespace PhysicalComponents { class Label;       };
};
using namespace Teddy::PhysicalComponents;
using namespace Teddy::Scenes;


class PlayerController;


class ControlProjection
: 
	public Node,
	public Teddy::MixIn::Tick,
	public Teddy::PhysicalComponents::Projection, 
	public Teddy::PhysicalComponents::EventListener
{
public:
    ControlProjection( const char *name, Camera *camera, Root *root );

	virtual void  tick       ();

	//  FocusListener interface
	//bool  focusActive( const bool active );

	//  WindowManager calls these methods when there is joystick event
	bool  mouseKey   ( const Event &e );
	bool  mouseDrag  ( const Event &e );
	bool  mouseMotion( const Event &e );
	bool  joyAxis    ( const Event &e );
	bool  joyButton  ( const Event &e );
	bool  joyHat     ( const Event &e );
	bool  joyBall    ( const Event &e );

	void  toggleHold ();
	void  setHold    ( bool hold );
	
	//  KeyListener interface
	bool  keyDown    ( const Event &e );
	bool  keyUp      ( const Event &e );

protected:
	Label       *title;
	bool         alt_down;
	float        joy_rot_up;
	float        joy_rot_right;
	float        joy_rot_view;
	bool         hold;
};


#endif  //  SPACE_GAME__FRONT_CAMERA__H

