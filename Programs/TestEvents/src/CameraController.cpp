
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

	$Id: CameraController.cpp,v 1.2 2002/03/12 10:44:29 tksuoran Exp $
*/


#include "Teddy/Behaviour/ModelAnimator.h"
#include "Teddy/Maths/Vector.h"
#include "Teddy/SysSupport/StdMaths.h"
#include "Teddy/SysSupport/StdIO.h"

#include "CameraController.h"
using namespace Teddy::Maths;
using namespace Teddy::Materials;
using namespace Teddy::Behaviour;


//!  Constructor
CameraController::CameraController( ModelAnimator *animator, Root *root )
:
Node           ( root     ),
ModelController( animator )
{
	unsigned long opts = Control::DAMPEN_MULTIPLY_M;
	rotate_up       = new Control( 1 * M_2_PI/100.0, 250.0 * M_2_PI/1000.0, opts, 0.888 );
	rotate_right    = new Control( 1 * M_2_PI/100.0, 250.0 * M_2_PI/1000.0, opts, 0.888 );
	rotate_view     = new Control( 1 * M_2_PI/100.0, 250.0 * M_2_PI/1000.0, opts, 0.888 );
	translate_up    = new Control( 1.0/80, 150.0, opts, 0.98 );
	translate_right = new Control( 1.0/80, 150.0, opts, 0.98 );
	translate_view  = new Control( 1.0/80, 150.0, opts, 0.98 );
	light           = NULL;
}


/*virtual*/ void CameraController::clearControls(){
	rotate_up      ->clear();
	rotate_right   ->clear();
	rotate_view    ->clear();
	translate_up   ->clear();
	translate_right->clear();
	translate_view ->clear();
}


void CameraController::enableDamp(){
//	rotate_up      ->enable( CONTROL_DAMPEN_MULTIPLY_M );
//	rotate_right   ->enable( CONTROL_DAMPEN_MULTIPLY_M );
//	rotate_view    ->enable( CONTROL_DAMPEN_MULTIPLY_M );
//	translate_up   ->enable( CONTROL_DAMPEN_MULTIPLY_M );
//	translate_right->enable( CONTROL_DAMPEN_MULTIPLY_M );
	translate_view ->enable( Control::DAMPEN_MULTIPLY_M );
}


void CameraController::disableDamp(){
//	rotate_up      ->disable( CONTROL_DAMPEN_MULTIPLY_M );
//	rotate_right   ->disable( CONTROL_DAMPEN_MULTIPLY_M );
//	rotate_view    ->disable( CONTROL_DAMPEN_MULTIPLY_M );
//	translate_up   ->disable( CONTROL_DAMPEN_MULTIPLY_M );
//	translate_right->disable( CONTROL_DAMPEN_MULTIPLY_M );
	translate_view ->disable( Control::DAMPEN_MULTIPLY_M );
}


Control *CameraController::getRotateUp      (){ return rotate_up;       }
Control *CameraController::getRotateRight   (){ return rotate_right;    }
Control *CameraController::getRotateView    (){ return rotate_view;     }
Control *CameraController::getTranslateUp   (){ return translate_up;    }
Control *CameraController::getTranslateRight(){ return translate_right; }
Control *CameraController::getTranslateView (){ return translate_view;  }


//!  Apply ship controls
/*virtual*/ void CameraController::tick(){
	Vector translation;

	//  Update Controls
	rotate_up      ->tick();
	rotate_right   ->tick();
	rotate_view    ->tick();
	translate_up   ->tick();
	translate_right->tick();
	translate_view ->tick();

	if( animator != NULL ){
		Quaternion &attitude = animator->getModel()->getAttitude();
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

		if( light != NULL ){
			light->setPosition(
				animator->getModel()->getPosition()
				- animator->getModel()->getAttitude().getViewAxis() * 200.0
				+ animator->getModel()->getAttitude().getUpAxis() * 400.0
			);
			light->setSpotDirection( animator->getModel()->getAttitude().getViewAxis() );
		}
	}
}


void CameraController::setLight( Light *light ){
	this->light = light;
}


Light *CameraController::getLight(){
	return light;
}

