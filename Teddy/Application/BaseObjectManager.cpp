
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


#include "Teddy/Application/BaseObjectManager.h"
//using namespace Teddy::Graphics;
//using namespace Teddy::Materials;
//using namespace Teddy::PhysicalComponents;
using namespace Teddy::Scenes;


namespace Teddy       {
namespace Application {


//!  BaseObjectManager constructor
BaseObjectManager::BaseObjectManager(){
}


//!  \todo doc
void BaseObjectManager::setCamera( Camera *c ){
	this->camera = c;
}


void BaseObjectManager::setScene( Scene *scene ){
	this->scene = scene;
}


//!  Get camera
Camera *BaseObjectManager::getCamera(){
	return camera;
}


//!  Get scene
Scene *BaseObjectManager::getScene(){
	return scene;
}


};  //  namespace Application
};  //  namespace Teddy

