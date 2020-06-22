
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


#ifndef SPACE_GAME__SHIP_CONTROLLER__H
#define SPACE_GAME__SHIP_CONTROLLER__H


#include "Teddy/Behaviour/Control.h"
#include "Teddy/Behaviour/ModelController.h"
#include "Teddy/Maths/Vector.h"
#include "Teddy/Materials/Light.h"

#include "Node.h"


class Ship;


//!  Simulated ModelInstance with collision detection
class ShipController 
: 
public Node,
public Teddy::Behaviour::ModelController
{
public:
	//	Constructors
	ShipController( Ship *ship, Root *root );

	virtual void   tick         ();
	virtual void   clearControls();

	//  Controls
	Teddy::Behaviour::Control   *getWeaponFire    ();
	Teddy::Behaviour::Control   *getRotateUp      ();
	Teddy::Behaviour::Control   *getRotateRight   ();
	Teddy::Behaviour::Control   *getRotateView    ();
	Teddy::Behaviour::Control   *getTranslateUp   ();
	Teddy::Behaviour::Control   *getTranslateRight();
	Teddy::Behaviour::Control   *getTranslateView ();
	Teddy::Models::Model        *getTarget        () const;
	void                         setTarget        ( Teddy::Models::Model *m, Teddy::Maths::TVector<double> offset = Teddy::Maths::TVector<double>(0.0,0.0,0.0) );
	void                         warpToPosition   ();
	void                         trackTarget      ();
	float                        getTargetDistance() const;
	
public:
	Teddy::Models::Model          *target;            //!<  Ship navigation aimpoint
	Teddy::Behaviour::Control     *weapon_fire;
	Teddy::Behaviour::Control     *rotate_up;         //!<  heading, yaw
	Teddy::Behaviour::Control     *rotate_right;      //!<  pitch
	Teddy::Behaviour::Control     *rotate_view;       //!<  roll;
	Teddy::Behaviour::Control     *translate_up;      //!<  Up/Down
	Teddy::Behaviour::Control     *translate_right;   //!<  Strafe left/right
	Teddy::Behaviour::Control     *translate_view;    //!<  Speed, forward, backward
	Teddy::Maths::TVector<double>  target_offset;     //!<  Aimpoint offset
	float                          prev_weapon_time;
	Teddy::Materials::Light       *head_light;        //!<  Light
};


#endif  //  SPACE_GAME__SHIP_CONTROLLER__H

