
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


#if defined( TEDDY_INCLUDE_COLDET )
# include "Teddy/ColDet/ColDet.h"
#endif
#include "Teddy/Models/Model.h"

#include "ShipType.h"
using namespace Teddy::Models;
#if defined( TEDDY_INCLUDE_COLDET )
using Teddy::ColDet::CollisionModel3D;
#endif


//!  ShipType constructor
ShipType::ShipType( const std::string &name, Model *model, float a, float ms, float pc, float rc, float mp, float mr )
:
Named       ( name  ),
model       ( model ),
acceleration( a     ),
pitch_const ( pc    ),
roll_const  ( rc    ),
max_pitch   ( mp    ),
max_roll    ( mr    ),
max_speed   ( ms    )
{
}


//!  Get ship's Mesh
Model *ShipType::getModel(){
	return this->model;
}


Model *ShipType::newModel( const std::string &name ){
	return new Model( name, model );
}


//!  Get ship's maximum acceleration
float ShipType::getAcceleration(){
	return this->acceleration;
}


//!  Get ship's pitch constant
float ShipType::getPitchConst(){
	return this->pitch_const;
}


//!  Get ship's roll constant
float ShipType::getRollConst(){
	return this->roll_const;
}


//!  Get ship's maximum pitch (delta)
float ShipType::getMaxPitch(){
	return this->max_pitch;
}


//!  Get ship's maximum roll (delta)
float ShipType::getMaxRoll(){
	return this->max_roll;
}


//!  Get ship's maximum speed
float ShipType::getMaxSpeed(){
	return this->max_speed;
}


