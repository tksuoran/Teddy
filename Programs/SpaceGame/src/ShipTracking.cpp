
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


#include "Teddy/Behaviour/ModelAnimator.h"

#include "Root.h"
#include "ShipController.h"
#include "ShipType.h"
using namespace Teddy::Application;
using namespace Teddy::Behaviour;
using namespace Teddy::Maths;
using namespace Teddy::Models;


//  ----- TRACKING CODE -----


/*!
	Tactics:

	If V: > 0.5  ->  forward
	If V: < 0.5  ->  backward

	If U: < 0    ->  pitch up      ; do only if 
	If U: > 0    ->  pitch down    ; fabs(U) > fabs(R)

	If R: > 0    ->	 roll right
	If R: < 0    ->  roll left
*/
void ShipController::trackTarget(){
//	ShipType *ship_type = ship->getShipType();
	Model *model = animator->getModel();
	float  speed = animator->getSpeed();
	float  pitch = rotate_right->getValue();
	float  roll  = rotate_view ->getValue();

	if( target == NULL ){
		return;
	}
	
	Vector tpos   =	target->getPosition ();
	Vector cpos   = model ->getPosition ();
	Vector tview  = target->getAttitude().getViewAxis ();
	Vector tup    = target->getAttitude().getUpAxis   ();
	Vector tright = target->getAttitude().getRightAxis();
	Vector cview  = model ->getAttitude().getViewAxis ();
	Vector cup    = model ->getAttitude().getUpAxis   ();
	Vector cright = model ->getAttitude().getRightAxis();
	Vector offset = 
		tright * target_offset.v[0] +
	    tup    * target_offset.v[1] +
	    tview  * target_offset.v[2];
	Vector delta  = tpos + offset - cpos;
	float  target_speed;

/*	InstanceAnimator *target_animator = dynamic_cast<SimulatedInstance*>( target );
	if( sim_target != NULL ){
		target_speed = (float)(sim_target->tick_translation.magnitude());
	}else{*/
		target_speed = 0;
//	}

	delta.normalize();
	float target_distance  = getTargetDistance();
	float brake_distance   = 0; //(speed * speed) / (20 * ship_type->getAcceleration() );
	float b_pitch_distance = 0; //10 * (pitch * pitch) / (2 * ship_type->getPitchConst  () );
	float b_roll_distance  = 0; //10 * (roll  * roll ) / (2 * ship_type->getRollConst   () )
	float v                = cview  | delta;
	float u                = cup    | delta;
	float r                = cright | delta;
	float v_epsilon        = 0.01f;  // error tolerance
	float u_epsilon        = 0.01f;  // error tolerance
	float r_epsilon        = 0.02f;  // error tolerance
	float pitch_distance   = (float)acos( u );
	float roll_distance    = (float)acos( r );

	//  Arrived to target?
	if( target_distance < 1 ){
		translate_view->stop( true );
		rotate_right  ->stop( true );
		rotate_view   ->stop( true );
		return;
	}

	bool speed_control = false;
	if(
		(  brake_distance  <  target_distance  )
		
		&&

		(

		  (
		   (target_distance <  100                ) &&
		   (fabs(speed)     <  fabs(target_speed) )    
		  )
		 
		  ||

          (
		   target_distance >= 100
		  )
		)
	){
		speed_control = true;
	}

	//  Target in front
	if( v > 0.5 ){

		//  Go faster?
		if( speed_control == true ){
			translate_view->more( true  );
			translate_view->less( false );
		}else{
			translate_view->stop( true );
		}
	}

	//  Target behind
	if( v < 0.5 ){

		//  Go backwards
		if( speed_control == true ){
			translate_view->more( false );
			translate_view->less( true  );
		}else{
			translate_view->stop( true );
		}
	}

	// Looking pretty straight at target?
	if( fabs(0.5-v) < v_epsilon ){
		rotate_right->stop( true );
		rotate_view ->stop( true );
		return;
	}

	//  Target above
	if( u >= 0 ){ 

		//  Pitch up
		if( (b_pitch_distance < pitch_distance) && 
			(fabs(u)          > fabs(r)       ) &&
			(u > u_epsilon                    )    )
		{
			rotate_right->more( true  );
			rotate_right->less( false );
		}else{
			rotate_right->stop( true );
		}

		//  Target on right (above)
		if( r > r_epsilon ){
			//  Roll right
			if( b_roll_distance < roll_distance ){
				rotate_view->more( true  );
				rotate_view->less( false );
			}else{
				rotate_view->stop( true );
			}
		}

		//  Target on left (above)
		if( r < -r_epsilon ){
			//  Roll left
			if( b_roll_distance < roll_distance ){
				rotate_view->more( false );
				rotate_view->less( true  );
			}else{
				rotate_view->stop( true );
			}
		}
	}

	//  Target below
	if( u < 0 ){ 

		//  Pitch down
		if( (b_pitch_distance < pitch_distance) && 
			(fabs(u)          > fabs(r)       ) &&
			(u                < -u_epsilon    )    )
		{
			rotate_right->more( false );
			rotate_right->less( true  );
		}else{
			rotate_right->stop( true );
		}

		//  Target on right (below)
		if( r > r_epsilon ){
			//  Roll left
			if( b_roll_distance < roll_distance ){
				rotate_view->more( false );
				rotate_view->less( true  );
			}else{
				rotate_view->stop( true );
			}
		}

		//  Target on left (below)
		if( r < -r_epsilon ){
			//  Roll right
			if( b_roll_distance < roll_distance ){
				rotate_view->more( true  );
				rotate_view->less( false );
			}else{
				rotate_view->stop( true );
			}
		}
	}
}


//!  Teleport instantly to target postion. Used to initialize wingmen position
void ShipController::warpToPosition(){
	Vector tpos   =	target->getPosition();
//	Vector cpos   = this->getPosition();
	Vector tview  = target->getAttitude().getViewAxis ();
	Vector tup    = target->getAttitude().getUpAxis   ();
	Vector tright = target->getAttitude().getRightAxis();
//	Vector cview  = getViewAxis ();
//	Vector cup    = getUpAxis   ();
//	Vector cright = getRightAxis();
	Vector offset = 
		tright * target_offset.v[0] +
	    tup    * target_offset.v[1] +
	    tview  * target_offset.v[2];
//	Vector delta  = tpos + offset - cpos;
	animator->getModel()->setPosition( tpos + offset );
}

