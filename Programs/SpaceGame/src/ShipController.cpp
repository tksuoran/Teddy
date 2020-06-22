
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


#include "Teddy/Models/Model.h"
#include "Teddy/SysSupport/Messages.h"

#include "ObjectManager.h"
#include "Ship.h"
#include "ShipController.h"
#include "ShipType.h"
using namespace Teddy::Behaviour;
using namespace Teddy::Maths;


#define WEAPON_RATE 150


//!  Constructor
ShipController::ShipController( Ship *ship, Root *root )
:
Node           ( root                            ),
ModelController( ship->getAnimator()             ),
target         ( NULL                            ),
target_offset  ( DoubleVector(0.0,0.0,0.0)       )
{
	unsigned long rot_opts = Control::DAMPEN_MULTIPLY_M;//CONTROL_DAMPEN_LINEAR_M;
	unsigned long tra_opts = Control::DAMPEN_MULTIPLY_M;

	weapon_fire      = new Control( 1, 1, 0, 1 );
	rotate_up        = new Control( 1000.0, 1000.0, rot_opts, 0.9 );
	rotate_right     = new Control( 1000.0, 1000.0, rot_opts, 0.9 );
	rotate_view      = new Control( 1000.0, 1000.0, rot_opts, 0.9 );
	translate_up     = new Control( 0.01,  250.0, tra_opts, 0.98 );
	translate_right  = new Control( 0.01,  250.0, tra_opts, 0.98 );
	translate_view   = new Control( 0.01,  250.0, tra_opts, 0.98 );
	head_light       = NULL;
	prev_weapon_time = 0;
	clearControls();
}


//!  Apply ship controls
/*virtual*/ void ShipController::tick(){
	if( animator == NULL ){
		return;
	}

	Model   *model = animator->getModel();
	Vector   translation;

	//  Update Controls
	weapon_fire    ->tick();
	rotate_up      ->tick();
	rotate_right   ->tick();
	rotate_view    ->tick();
	translate_up   ->tick();
	translate_right->tick();
	translate_view ->tick();

	Quaternion &attitude = model->getAttitude();
	attitude.normalize();

	animator->setTickTranslation(
		attitude.getUpAxis   () * translate_up   ->getValue() +
		attitude.getRightAxis() * translate_right->getValue() +
		attitude.getViewAxis () * translate_view ->getValue()
	);

	animator->setTickRotation(
		rotate_up   ->getValue(),
		rotate_right->getValue(),
		rotate_view ->getValue()
	);

	if( head_light != NULL ){
		head_light->setPosition     ( model->getPosition()               );
		head_light->setSpotDirection( model->getAttitude().getViewAxis() );
	}

	if( weapon_fire->getValue() > 0 ){

		//msg( "%lf\n", weapon_fire->getValue() );

		float sys_time = SDL_GetTicks();

		if( sys_time - prev_weapon_time > WEAPON_RATE ){
			prev_weapon_time = sys_time;

			//getAudioManager ()->playPulse   ();
			getObjectManager()->rayCollision( target );
		}
	}

}


//!  used by debug hud
float ShipController::getTargetDistance() const {
	if( target != NULL ){
		Vector tpos     = target  ->getPosition();
		Vector cpos     = animator->getModel()->getPosition();
		Vector delta    = tpos - cpos;
		return delta.magnitude() - target->getClipRadius() * 2;
	}else{
		return 0;
	}
}


//!  Set current ship target
void ShipController::setTarget( Model *mi, DoubleVector offset ){
	target        = mi;
	target_offset = offset;
}


//  Get currents ship target
Model *ShipController::getTarget() const {
	return target;
}


/*virtual*/ void ShipController::clearControls(){
	weapon_fire    ->clear();
	rotate_up      ->clear();
	rotate_right   ->clear();
	rotate_view    ->clear();
	translate_up   ->clear();
	translate_right->clear();
	translate_view ->clear();
}


Control *ShipController::getWeaponFire    (){ return weapon_fire;     }
Control *ShipController::getRotateUp      (){ return rotate_up;       }
Control *ShipController::getRotateRight   (){ return rotate_right;    }
Control *ShipController::getRotateView    (){ return rotate_view;     }
Control *ShipController::getTranslateUp   (){ return translate_up;    }
Control *ShipController::getTranslateRight(){ return translate_right; }
Control *ShipController::getTranslateView (){ return translate_view;  }


