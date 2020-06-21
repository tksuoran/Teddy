
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


#include "Teddy/Application/BaseSimulationTimer.h"
#include "Teddy/Scenes/Scene.h"
#include "Teddy/SysSupport/Messages.h"

#include "ObjectManager.h"
#include "Ship.h"
#include "ShipController.h"
#include "ShipType.h"
using namespace Teddy::Behaviour;
using namespace Teddy::Maths;
using namespace Teddy::Models;
using namespace Teddy::Scenes;


/*!
	\brief Ship constructor
	\param name Name for this Ship instance
	\param ship_type Type of this Ship
*/
Ship::Ship( const std::string &name, ShipType *ship_type, Root *root )
:
Node  ( root ),
Model ( name, ship_type->getModel() ),
energy( 10000 )
{
	animator = new ModelAnimator( this );
	getObjectManager  ()->getScene()->add( this );
	getSimulationTimer()->add( animator );
}


/*virtual*/ Ship::~Ship(){
	getSimulationTimer()->remove( animator );
	getObjectManager  ()->getScene()->remove( this );
	delete animator;
}


ModelAnimator *Ship::getAnimator(){
	return animator;
}


//!  Collision
void Ship::collide( Model *mi ){
/*	Ship *other = dynamic_cast<Ship*>( mi );
	if( other != NULL ){
		//                    s2 / b                    s1 / a
		Vector impact       = other->tick_translation - this->tick_translation;
		Vector impulse      = other->vectorTo( *this );
		impulse.normalize();
		float  impact_speed = impact | impulse;
		impulse *= impact_speed;

		other->tick_translation -= impulse;
		this ->tick_translation += impulse;

	}else{
		Vector impact   = - this->tick_translation;
		Vector impulse  = mi->vectorTo( *this );
		impulse.normalize();
		float  impact_speed = impact | impulse;
		impulse *= impact_speed;
		msg( "impact_speed % 9.4f\n", impact_speed );
		msg( "old_speed    % 9.4f\n", tick_translation.magnitude() );

		this ->tick_translation += impulse;
		msg( "new_speed    % 9.4f\n", tick_translation.magnitude() );
	}
	translate( tick_translation*2 );
*/

	//getRoot()->getAudioManager()->playHitEm();
	DoubleVector t = animator->getTickTranslation() * -1;
	animator->setTickTranslation( t );
//	tick_rotation = tick_rotation *
	translate( t );
	translate( t );
	//speed *= -0.5;
}


//!  Refresh energy etc
void Ship::refresh(){
	if( energy<10000 ){
		energy += 5;
	}
}


//  Damage ship
void Ship::damage(){
	energy -= 1000;
	if( energy < 0 ){
		delete this;
	}
}


//!  Get ships type
ShipType *Ship::getShipType(){
	return this->ship_type;
}

