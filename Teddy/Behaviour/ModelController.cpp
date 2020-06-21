
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


#include "Teddy/Behaviour/ModelController.h"
#include "Teddy/Behaviour/ModelAnimator.h"
#include "Teddy/Maths/Vector.h"
#include "Teddy/SysSupport/StdMaths.h"
#include "Teddy/SysSupport/StdIO.h"
using namespace Teddy::Maths;


namespace Teddy     {
namespace Behaviour {


//!  Constructor
ModelController::ModelController( ModelAnimator *animator )
:
animator(animator)
{
	if( animator != NULL ){
		animator->setController( this );
	}
}


/*virtual*/ ModelController::~ModelController(){
	if( animator != NULL ){
		animator->setController( NULL );
	}
}


//!  Get ModelAnimator
ModelAnimator *ModelController::getAnimator(){
	return animator;
}


//!  Set ModelAnimator
void ModelController::setAnimator( ModelAnimator *animator ){
	this->animator = animator;
	if( animator != NULL ){
		animator->setController( this );
	}
}


};  //  namespace Behaviour
};  //  namespace Teddy

