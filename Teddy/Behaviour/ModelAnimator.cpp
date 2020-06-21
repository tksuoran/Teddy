
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

	$Id:  $
*/


#include "Teddy/Models/Model.h"
#include "Teddy/Behaviour/ModelAnimator.h"
#include "Teddy/Behaviour/ModelController.h"
using namespace Teddy::Maths;
using namespace Teddy::Models;


namespace Teddy     {
namespace Behaviour {


//!  Constructor
ModelAnimator::ModelAnimator(
	Model         *m,
	DoubleVector  tick_translation,
	double        up,
	double        right,
	double        view
)
:
model              ( m     ),
controller         ( NULL  ),
tick_translation   ( tick_translation ),
tick_rotation_up   ( up    ),
tick_rotation_right( right ),
tick_rotation_view ( view  )
{
}


/*virtual*/ ModelAnimator::~ModelAnimator(){
	if( controller!=NULL ){
		controller->setAnimator( NULL );
	}
}


void ModelAnimator::setController( ModelController *controller ){
	this->controller = controller;
}


ModelController *ModelAnimator::getController(){
	return this->controller;
}


void ModelAnimator::setTickTranslation( DoubleVector tick_translation ){
	this->tick_translation = tick_translation;
}


float ModelAnimator::getSpeed(){
	return tick_translation.magnitude();
}


void ModelAnimator::setTickRotation( double up, double right, double view ){
	tick_rotation_up    = up;
	tick_rotation_right = right;
	tick_rotation_view  = view;
}


/*virtual*/ void ModelAnimator::tick(){
	if( controller != NULL ){
		controller->tick();
	}
	if( model != NULL ){
		model->translate( tick_translation    );
		model->heading  ( tick_rotation_up    );
		model->pitch    ( tick_rotation_right );
		model->roll     ( tick_rotation_view  );
	}
}


Model *ModelAnimator::getModel(){
	return this->model;
}


void ModelAnimator::setModel( Model *model ){
	this->model = model;
}


};  //  namespace Behaviour
};  //  namespace Teddy

