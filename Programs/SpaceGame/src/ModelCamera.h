
/*
	TSGL - Teddy Space Game Library
	Copyright (C) 2002 Timo Suoranta
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

	$Id:  $
*/


#ifndef SPACE_GAME__MODEL_CAMERA__H
#define SPACE_GAME__MODEL_CAMERA__H


#include "Teddy/Behaviour/Control.h"
#include "Teddy/MixIn/Tick.h"
#include "Teddy/Scenes/Camera.h"

#include "Node.h"


//!  Camera which is attached to a ship
class ModelCamera
: 
public Node,
public Teddy::Scenes::Camera,
public Teddy::MixIn::Tick
{
public:
	ModelCamera( Teddy::Models::Model *target, Root *root );

	virtual void   projectScene( Teddy::PhysicalComponents::Projection *p );
	virtual void   tick        ();

	void           front      ();
	void           left       ();
	void           right      ();
	void           rear       ();
	void           top        ();
	void           bottom     ();

	void                  setTarget  ( Teddy::Models::Model );
	Teddy::Models::Model *getTarget  ();
	Teddy::Scenes::Scene *getScene   ();
	Teddy::Models::Model *getModel   ();

	Teddy::Behaviour::Control *getHeading      ();
	Teddy::Behaviour::Control *getPitch        ();
	Teddy::Behaviour::Control *getRoll         ();
	Teddy::Behaviour::Control *getDistance     ();
	double                     getDistanceValue();

protected:
	Teddy::Models::Model      *target;
	Teddy::Behaviour::Control *c_heading;
	Teddy::Behaviour::Control *c_pitch;
	Teddy::Behaviour::Control *c_roll;	
	Teddy::Behaviour::Control *c_distance;
	double                     heading;      
	double                     pitch;        
	double                     roll;         
	double                     distance;     
};


#endif  //  SPACE_GAME__MODEL_CAMERA__H

