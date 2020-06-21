
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

	$Id: BaseUserInterface.cpp,v 1.2 2002/02/16 12:41:39 tksuoran Exp $
*/


#include "Teddy/TeddyConfig.h"
#include "Teddy/Application/BaseRoot.h"
#include "Teddy/Application/BaseUserInterface.h"
#include "Teddy/Graphics/View.h"
#include "Teddy/PhysicalComponents/WindowManager.h"
#include "Teddy/PhysicalComponents/Layer.h"
#include "Teddy/SysSupport/Messages.h"
using namespace Teddy::Graphics;
using namespace Teddy::PhysicalComponents;


namespace Teddy       {
namespace Application {


//!  The base class creates view, window_manager and layer
BaseUserInterface::BaseUserInterface( BaseRoot *root ){
	view           = new View         ( root->getScreenWidth(), root->getScreenHeight(), root->getScreenOptions() );
	layer          = new Layer        ( "Root Layer", view );
	window_manager = new WindowManager( view );
	view          ->setWindowManager( window_manager );
	window_manager->insert          ( layer );
	Area::setDefaultWindowManager( window_manager );
}


void BaseUserInterface::enterRunLoop(){
	window_manager->inputLoop();
}


void BaseUserInterface::setProjection( Projection *projection ){ this->projection = projection; }


Layer         *BaseUserInterface::getLayer        (){ return layer;          }
Projection    *BaseUserInterface::getProjection   (){ return projection;     }
View          *BaseUserInterface::getView         (){ return view;           }
WindowManager *BaseUserInterface::getWindowManager(){ return window_manager; }


};  //  namespace Application
};  //  namespace Teddy

