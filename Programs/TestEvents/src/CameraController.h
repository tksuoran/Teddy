
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

	$Id: CameraController.h,v 1.2 2002/03/12 10:44:29 tksuoran Exp $
*/


#ifndef TEST_EVENTS__CAMERA_CONTROLLER__H
#define TEST_EVENTS__CAMERA_CONTROLLER__H


#include "Teddy/Behaviour/ModelController.h"
#include "Teddy/Behaviour/Control.h"
#include "Teddy/Materials/Light.h"

#include "Node.h"


class CameraController 
: 
public Node,
public Teddy::Behaviour::ModelController
{
public:
	CameraController( Teddy::Behaviour::ModelAnimator *animator, Root *root );

	virtual void  tick             ();
	virtual void  clearControls    ();

	void                     setLight   ( Teddy::Materials::Light *light );
	Teddy::Materials::Light *getLight   ();
	void                     enableDamp ();
	void                     disableDamp();

	Teddy::Behaviour::Control  *getRotateUp      ();
	Teddy::Behaviour::Control  *getRotateRight   ();
	Teddy::Behaviour::Control  *getRotateView    ();
	Teddy::Behaviour::Control  *getTranslateUp   ();
	Teddy::Behaviour::Control  *getTranslateRight();
	Teddy::Behaviour::Control  *getTranslateView ();

protected:
	Teddy::Materials::Light   *light;
	Teddy::Behaviour::Control *rotate_up;        //!<  heading, yaw
	Teddy::Behaviour::Control *rotate_right;     //!<  pitch
	Teddy::Behaviour::Control *rotate_view;      //!<  roll;
	Teddy::Behaviour::Control *translate_up;     //!<  Up/Down
	Teddy::Behaviour::Control *translate_right;  //!<  Strafe left/right
	Teddy::Behaviour::Control *translate_view;   //!<  Speed, forward, backward
};


#endif  //  TEST_EVENTS__CAMERA_CONTROLLER__H

