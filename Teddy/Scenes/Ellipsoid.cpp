
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


#include "Teddy/Scenes/Ellipsoid.h"


namespace Teddy  {
namespace Scenes {


Ellipsoid::Ellipsoid( Vector location, Vector forward, double radius, double front, double rear ){
	this->location = location;
	this->forward  = forward;
	this->radius   = radius;
	this->front    = front;
	this->rear     = rear;

	if( front > rear ){
		if( front > radius ){
			this->clip_radius = front;
		}else{
            this->clip_radius = radius;
		}
	}else{
		if( rear > radius ){
			this->clip_radius = rear;
		}else{
            this->clip_radius = radius;
		}
	}
}


};  //  namespace Scenes
};  //  namespace Teddy


