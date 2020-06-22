
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


#ifndef TEDDY_PLAYER__DISPLAY__H
#define TEDDY_PLAYER__DISPLAY__H


#include "Teddy/PhysicalComponents/Projection.h"
#include "Teddy/PhysicalComponents/EventListener.h"
#include "Teddy/MixIn/Tick.h"
#include "Teddy/Scenes/Camera.h"
#include "Teddy/SysSupport/StdSDL.h"

#include "CameraController.h"
#include "Node.h"



//  Forward declarations
namespace Teddy {
	namespace Models { class Model; };
};


//!  EventManager
class Display
: 
	public Node,
	public Teddy::MixIn::Tick,
    public Teddy::PhysicalComponents::EventListener,
    public Teddy::PhysicalComponents::Projection
{
public:
	Display( Root *root, Teddy::Scenes::Camera *camera );
	virtual ~Display();

	virtual void      tick               ();
    void              bindController     ( Teddy::Models::Model *model );
	void              setHold            ( bool hold );
	void              toggleHold         ();
	CameraController *getCameraController();

    bool mouseKey   ( const Teddy::PhysicalComponents::Event &e );
	bool mouseMotion( const Teddy::PhysicalComponents::Event &e );
	bool keyDown    ( const Teddy::PhysicalComponents::Event &e );
	bool keyUp      ( const Teddy::PhysicalComponents::Event &e );
	bool joyAxis    ( const Teddy::PhysicalComponents::Event &e );
	bool joyButton  ( const Teddy::PhysicalComponents::Event &e );
	bool joyHat     ( const Teddy::PhysicalComponents::Event &e );
	bool selectModel( const Teddy::PhysicalComponents::Event &e );

	bool activate( const Teddy::PhysicalComponents::Event &e );
	bool moving  ( const Teddy::PhysicalComponents::Event &e );
	bool sizing  ( const Teddy::PhysicalComponents::Event &e );
	bool close   ();

protected:
	Teddy::Behaviour::ModelAnimator *model_animator;
	CameraController                *controller;
	float                            joy_rot_up;
	float                            joy_rot_right;
	float                            joy_rot_view;
    bool                             hold;
	static int                       count;
	bool                             enable_select;
	bool                             is_active;
};


#endif  //  TEDDY_PLAYER__DISPLAY__H

