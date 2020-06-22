
/*
	TEDDY - General graphics application library
	Copyright (C) 1999-2020  Timo Suoranta
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
#include "Teddy/Models/Model.h"
#include "Teddy/PhysicalComponents/Layer.h"
#include "Teddy/Scenes/Camera.h"
#include "Teddy/Scenes/Scene.h"
#include "Teddy/SysSupport/Messages.h"

#include "ActionManager.h"
#include "PlayerController.h"
#include "ControlProjection.h"
#include "Hud.h"
#include "ModelCamera.h"
#include "Scanner.h"
#include "Sight.h"
#include "UserInterface.h"
using namespace Teddy::Materials;
using namespace Teddy::Scenes;


#define TRANSLATE_SCALE   1.0f
#define ROTATE_SCALE      0.3f
#define distance_delta    0.01f
#define SCALE            1.00f


//!  Initialize actions
ActionManager::ActionManager( Root *root )
:
Node(root)
{
//displayHelp();
}


//!  Exit program
void ActionManager::quit(){
	exit( 0 );
}


#if 0
//!  Display OpenGL extensions
void ActionManager::displayExtensions(){
/*	con << ": OpenGL driver information:" << endl;
	con << ": " << view->getVendor  () << endl;
	con << ": " << view->getRenderer() << endl;
	con << ": " << view->getVersion () << endl;
	con << ": OpenGL extensions:" << endl;*/
	char *start;
	char *i;
	start = i = getUserInterface()->getView()->getExtensions();
	while( *i != '\0' ){
		if( *i==' ' ){
			*i = '\0';
//			con << ": " << start << endl;
			start = ++i;
			continue;
		}
		i++;
	}
	int width  = 0;
	int height = 0;
//	view->getMaxViewportDims( width, height );
/*	con << ": Maximum texture size:  " << view->getMaxTextureSize() << endl;
	con << ": Maximum lights:		 " << view->getMaxLights     () << endl;
	con << ": Maximum viewport dims: " << width << " x " << height  << endl;
*/
}
#endif


//!
void ActionManager::scannerCycle(){
	getUserInterface()->getScanner()->cycle();
}


void ActionManager::blendOff(){
	getUserInterface()->getView()->disable( View::BLEND );
}

void ActionManager::blendOn(){
	getUserInterface()->getView()->enable( View::BLEND );
}


void ActionManager::renderModePoint(){
	//con << ": Polygon Mode Point" << endl;
	getUserInterface()->getProjection()->getMaster()->setMode( Material::RENDER_MODE_POINT );
}


void ActionManager::renderModeLine(){
	//con << ": Polygon Mode Line" << endl;
	getUserInterface()->getProjection()->getMaster()->setMode( Material::RENDER_MODE_LINE );
}


void ActionManager::renderModeFill(){
	//con << ": Polygon Mode Fill" << endl;
	getUserInterface()->getProjection()->getMaster()->setMode( Material::RENDER_MODE_FILL );
}


void ActionManager::renderModeFillOutline(){
	//con << ": Polygon Mode Fill Outline" << endl;
	getUserInterface()->getProjection()->getMaster()->setMode( Material::RENDER_MODE_FILL_OUTLINE );
}


void ActionManager::cullFaceEnable(){
	//con << ": Master Face Culling Enabled" << endl;
	getUserInterface()->getProjection()->getMaster()->enable( Material::RENDER_OPTION_CULL_FACE_M );
}


void ActionManager::cullFaceDisable(){
	//con << ": Master Face Culling Disabled" << endl;
	getUserInterface()->getProjection()->getMaster()->disable( Material::RENDER_OPTION_CULL_FACE_M );
}


void ActionManager::depthTestEnable(){
	//con << ": Master Depth Test Enabled" << endl;
	getUserInterface()->getProjection()->getMaster()->enable( Material::RENDER_OPTION_DEPTH_TEST_M );
}


void ActionManager::depthTestDisable(){
	//con << ": Master Depth Test Disabled" << endl;
	getUserInterface()->getProjection()->getMaster()->disable( Material::RENDER_OPTION_DEPTH_TEST_M );
}


void ActionManager::lightingOn(){
//	con << ": Master Lighting Enabled (simple)" << endl;
	getUserInterface()->getProjection()->getMaster()->setLighting( Material::RENDER_LIGHTING_SIMPLE );
}


void ActionManager::lightingOff(){
//	con << ": Master Lighting Disabled (color)" << endl;
	getUserInterface()->getProjection()->getMaster()->setLighting( Material::RENDER_LIGHTING_COLOR );
}


void ActionManager::fovNormal(){
	float fov = getUserInterface()->getProjection()->getCamera()->getFov() - 5;
	if( fov > 0 ){
//		con << ": Field of Vision " << fov << " degrees" << endl;
		getUserInterface()->getProjection()->getCamera()->setFov( fov );
	}
}


void ActionManager::fovWide(){
	float fov = getUserInterface()->getProjection()->getCamera()->getFov() + 5;
	if( fov < 180 ){
//		con << ": Field of Vision " << fov << " degrees" << endl;
		getUserInterface()->getProjection()->getCamera()->setFov( fov );
	}
}


void ActionManager::antialiseOn(){
//	con << ": Line Smooth Hint Nicest" << endl;
	getUserInterface()->getProjection()->enable( Material::RENDER_OPTION_LINE_SMOOTH_M );
}


void ActionManager::antialiseOff(){
//	con << ": Line Smooth Hint Fastest" << endl;
	getUserInterface()->getProjection()->disable( Material::RENDER_OPTION_LINE_SMOOTH_M );
}


