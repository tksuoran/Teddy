
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


#include "Teddy/TeddyConfig.h"
#include "Teddy/Graphics/View.h"
#include "Teddy/Materials/Material.h"
#include "Teddy/PhysicalComponents/WindowManager.h"
#include "Teddy/PhysicalComponents/Layer.h"
#include "Teddy/PhysicalComponents/WindowManager.h"
#include "Teddy/PhysicalComponents/Console.h"
#include "Teddy/PhysicalComponents/Dock.h"
#include "Teddy/SysSupport/Messages.h"

#include "Cabin.h"
#include "ControlProjection.h"
#include "Hud.h"
#include "ModelCamera.h"
#include "ObjectManager.h"
#include "Scanner.h"
#include "Sight.h"
#include "UserInterface.h"
using namespace Teddy::Application;
using namespace Teddy::Graphics;
using namespace Teddy::PhysicalComponents;


UserInterface::UserInterface( Root *root )
:
Node             ( root ),
BaseUserInterface( root )
{
}


//!  Create testing environment physical user interface
/*virtual*/ void UserInterface::addComponents(){
	Camera *camera       = getObjectManager()->getCamera     ();
	Camera *model_camera = getObjectManager()->getModelCamera();

	//	Create physical components for user interface
	ControlProjection *pro_1 = NULL;
	ControlProjection *pro_2 = NULL;

	pro_1 = new ControlProjection(
		"Camera 1",
		camera,
		root
    );
	pro_1->offset_free_size_relative = Vector2( 0.1f, 0.35f );
	layer         ->addProjection( pro_1 );
	window_manager->setFocus     ( pro_1 );
    pro_1->setHold( true  );
	setProjection( pro_1 );

	if( view->getOptions().isEnabled(View::OPT_MULTI_WINDOW) == true ){
		pro_2 = new ControlProjection(
			"Camera 2",
			model_camera,
			root
		);
		pro_2->offset_free_size_relative = Vector2( 0.5f, 0.35f );
		pro_2->insert( new Sight() );
		layer->addProjection( pro_2 );
	}else{
		pro_1->insert( new Sight() );
	}

	//  Set rendering preferences
	pro_1->setClearColor( Color(0,0,0,1) );
	pro_1->getMaster()->setOptions ( Material::RENDER_OPTION_ALL_M );
	pro_1->getMaster()->setMode    ( Material::RENDER_MODE_FILL_OUTLINE );
	pro_1->getMaster()->setLighting( Material::RENDER_LIGHTING_COLOR );

	if( pro_2 != NULL ){
		pro_2->setClearColor( Color(0.1f,0.3f,0.0f,1.0f) );
		pro_2->disableSelect( Material::RENDER_OPTION_DIFFUSE_M );
		pro_2->disableSelect( Material::RENDER_OPTION_BORDER_M  );
		pro_2->getMaster()->setMode    ( Material::RENDER_MODE_FILL_OUTLINE );
		pro_2->getMaster()->setLighting( Material::RENDER_LIGHTING_COLOR );
		pro_2->getMaster()->disable    ( Material::RENDER_OPTION_AMBIENT_M );
		pro_2->getMaster()->disable    ( Material::RENDER_OPTION_SPECULAR_M );
		pro_2->getMaster()->setDiffuse ( Color(0.0f,0.2f,0.0f,1.0f) );
		pro_2->getMaster()->setBorder  ( Color(0.6f,0.7f,0.5f,1.0f) );
	}
	layer->insert( new Hud    (root) );
	layer->insert( new Scanner(root) );
	layer->place  ();
}


Scanner *UserInterface::getScanner(){
	return this->scanner;
}

