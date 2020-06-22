
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

	$Id: EventManager.cpp,v 1.2 2002/03/12 10:44:29 tksuoran Exp $
*/


#include "Teddy/Behaviour/Control.h"
#include "Teddy/Behaviour/ModelAnimator.h"
#include "Teddy/Application/BaseSimulationTimer.h"
#include "Teddy/Imports/LWSceneParser.h"
#include "Teddy/Materials/Material.h"
#include "Teddy/Models/Model.h"
#include "Teddy/PhysicalComponents/EventListener.h"
#include "Teddy/PhysicalComponents/Projection.h"
#include "Teddy/Scenes/Camera.h"
#include "Teddy/Scenes/Scene.h"

#include "CameraController.h"
#include "EventManager.h"
#include "ObjectManager.h"
#include "Root.h"
#include "UserInterface.h"
using namespace Teddy::Application;
using namespace Teddy::Behaviour;
using namespace Teddy::Imports;
using namespace Teddy::Materials;
using namespace Teddy::PhysicalComponents;
using namespace Teddy::Scenes;


//  Feel free to change these to your favorite first person shooter controls :)
#define CONTROL_KEY_STRAFE_LEFT  SDLK_LEFT   //  Also 'z' would work
#define CONTROL_KEY_STRAFE_RIGHT SDLK_RIGHT  //  Also 'c' would work
#define CONTROL_KEY_STRAFE_UP    SDLK_UP     //  See SDL documentation and/or
#define CONTROL_KEY_STRAFE_DOWN  SDLK_DOWN   //  header files for other keys.


EventManager::EventManager( Root *root )
:
Node         (root),
EventListener(    )
{
	controller = new CameraController( NULL, root );
}


//!  Set controller target
void EventManager::bindController( Model *model ){
	ModelAnimator *a = new ModelAnimator( model );
	controller->setAnimator( a );
	getSimulationTimer()->add( a );
}


//!  MouseListener interface
/*virtual*/ bool EventManager::mouseKey( const Event &e ){
	if( e.item_id == 1 ){
		controller->getTranslateView()->more( e.state==1?true:false );
	}
	if( e.item_id == 3 ){
		controller->getTranslateView()->less( e.state==1?true:false );
    }
    return true;
}


//!  Mouse motion
/*virtual*/ bool EventManager::mouseMotion( const Event &e ){
	controller->getRotateUp   ()->adjust( rads(-0.1) * e.delta[0] );
    controller->getRotateRight()->adjust( rads(-0.1) * e.delta[1] );
    return true;
}


/*!
	Handle key down events. When control key is pressed,
	the control is activated. If escape or q is pressed,
	program exists instantly. If space is pressed, speed
	of the camera is set to zero.
*/
/*virtual*/ bool EventManager::keyDown( const Event &e ){
	static int     color_select = 0;
	Projection    *p            = getUserInterface()->getProjection   ();
	LWSceneParser *lwsc         = getObjectManager()->getLWSceneParser();

	switch( e.key_sym ){
	case SDLK_ESCAPE:
	case 'q'        : exit(0); break;

	case 'z' : {
		float delta = controller->getTranslateRight()->getDelta() * 1.1;
		controller->getTranslateRight()->setDelta( delta );
		controller->getTranslateUp   ()->setDelta( delta );
		controller->getTranslateView ()->setDelta( delta );
		break;
	}
	case 'x' : {
		float delta = controller->getTranslateRight()->getDelta() / 1.1;
		controller->getTranslateRight()->setDelta( delta );
		controller->getTranslateUp   ()->setDelta( delta );
		controller->getTranslateView ()->setDelta( delta );
		break;
	}
	case 'c' : {
		float damp = controller->getTranslateRight()->getDampConst() * 1.05;
		controller->getTranslateRight()->setDampConst( damp );
		controller->getTranslateUp   ()->setDampConst( damp );
		controller->getTranslateView ()->setDampConst( damp );
		break;
	}
	case 'v' : {
		float damp = controller->getTranslateRight()->getDampConst() / 1.05;
		controller->getTranslateRight()->setDampConst( damp );
		controller->getTranslateUp   ()->setDampConst( damp );
		controller->getTranslateView ()->setDampConst( damp );
		break;
	}
	case 'b' :
		controller->getAnimator()->getModel()->setPosition( Vector(0.0f,1.65f,0.0f) );
		controller->getAnimator()->getModel()->getAttitude() = Quaternion(0.0f,0.0f,0.0f,1.0f);
		break;


	case 'p' : lwsc->play (); break;
	case 's' : lwsc->stop (); break;
	case 'r' : lwsc->reset(); break;
	case SDLK_KP_6 : {
		float multiplier = lwsc->getMultiplier();
		multiplier *= 1.1f;
		lwsc->setMultiplier( multiplier );
		break;
		}
	case SDLK_KP_5 : {
		float multiplier = lwsc->getMultiplier();
		multiplier *= -1;
		lwsc->setMultiplier( multiplier );
		break;
		}
	case SDLK_KP_4 : {
		float multiplier = lwsc->getMultiplier();
		multiplier /= 1.1f;
		lwsc->setMultiplier( multiplier );
		break;
		}

	case CONTROL_KEY_STRAFE_RIGHT: controller->getTranslateRight()->more(true); break;
	case CONTROL_KEY_STRAFE_LEFT : controller->getTranslateRight()->less(true); break;
	case CONTROL_KEY_STRAFE_UP   : controller->getTranslateUp   ()->more(true); break;
	case CONTROL_KEY_STRAFE_DOWN : controller->getTranslateUp   ()->less(true); break;
	case SDLK_F1 : p->getMaster()->setMode    ( Material::RENDER_MODE_POINT        ); break;
	case SDLK_F2 : p->getMaster()->setMode    ( Material::RENDER_MODE_LINE         ); break;
	case SDLK_F3 : p->getMaster()->setMode    ( Material::RENDER_MODE_FILL         ); break;
	case SDLK_F4 : p->getMaster()->setMode    ( Material::RENDER_MODE_FILL_OUTLINE ); break;
	case SDLK_F5 : p->getMaster()->setLighting( Material::RENDER_LIGHTING_COLOR    ); break;
	case SDLK_F6 : p->getMaster()->setLighting( Material::RENDER_LIGHTING_SIMPLE   ); break;
	case SDLK_F7 : p->getCamera()->modFov     (  5 ); break;
	case SDLK_F8 : p->getCamera()->modFov     ( -5 ); break;
	case SDLK_F9 : p->getMaster()->toggle     ( Material::RENDER_OPTION_TEXTURE_2D_M ); break;
	case SDLK_F10:
		p->getSelect().toggle( Material::RENDER_OPTION_DIFFUSE_M );
		if( p->getSelect().isEnabled(Material::RENDER_OPTION_DIFFUSE_M) ){
			p->setClearColor( Color(0.3f,0.4f,0.5f,1.0f) );
		}else{
			p->setClearColor( Color(0.5,0.5,0.5,1.0f) );
		}
		break;
	case SDLK_F11:
		color_select++;
		switch( color_select ){
		case  0: p->getMaster()->setDiffuse ( Color::BLACK         ); break;
		case  1: p->getMaster()->setDiffuse ( Color::GRAY_25       ); break;
		case  2: p->getMaster()->setDiffuse ( Color::GRAY_50       ); break;
		case  3: p->getMaster()->setDiffuse ( Color::GRAY_75       ); break;
		case  4: p->getMaster()->setDiffuse ( Color::WHITE         ); break;
		case  5: p->getMaster()->setDiffuse ( Color::DARK_RED      ); break;
		case  6: p->getMaster()->setDiffuse ( Color::DARK_ORANGE   ); break;
		case  7: p->getMaster()->setDiffuse ( Color::DARK_YELLOW   ); break;
		case  8: p->getMaster()->setDiffuse ( Color::DARK_GREEN    ); break;
		case  9: p->getMaster()->setDiffuse ( Color::DARK_CYAN     ); break;
		case 10: p->getMaster()->setDiffuse ( Color::DARK_BLUE     ); break;
		case 11: p->getMaster()->setDiffuse ( Color::DARK_MAGENTA  ); break;
		case 12: p->getMaster()->setDiffuse ( Color::RED           ); break;
		case 13: p->getMaster()->setDiffuse ( Color::ORANGE        ); break;
		case 14: p->getMaster()->setDiffuse ( Color::YELLOW        ); break;
		case 15: p->getMaster()->setDiffuse ( Color::GREEN         ); break;
		case 16: p->getMaster()->setDiffuse ( Color::CYAN          ); break;
		case 17: p->getMaster()->setDiffuse ( Color::BLUE          ); break;
		case 18: p->getMaster()->setDiffuse ( Color::MAGENTA       ); break;
		case 19: p->getMaster()->setDiffuse ( Color::LIGHT_RED     ); break;
		case 20: p->getMaster()->setDiffuse ( Color::LIGHT_ORANGE  ); break;
		case 21: p->getMaster()->setDiffuse ( Color::LIGHT_YELLOW  ); break;
		case 22: p->getMaster()->setDiffuse ( Color::LIGHT_GREEN   ); break;
		case 23: p->getMaster()->setDiffuse ( Color::LIGHT_CYAN    ); break;
		case 24: p->getMaster()->setDiffuse ( Color::LIGHT_BLUE    ); break;
		case 25: p->getMaster()->setDiffuse ( Color::LIGHT_MAGENTA ); break;
		default:
			color_select = 0;
			p->getMaster()->setDiffuse ( Color::BLACK         ); break;
		}
	default: break;
    }
    return true;
};


/*!
	Handle key up events. When control key is released,
	the control is deactivated.
*/
/*virtual*/ bool EventManager::keyUp( const Event &e ){
	switch( e.key_sym ){
	case CONTROL_KEY_STRAFE_RIGHT: controller->getTranslateRight()->more(false); break;
	case CONTROL_KEY_STRAFE_LEFT : controller->getTranslateRight()->less(false); break;
	case CONTROL_KEY_STRAFE_UP   : controller->getTranslateUp   ()->more(false); break;
	case CONTROL_KEY_STRAFE_DOWN : controller->getTranslateUp   ()->less(false); break;
	default: break;
    }
    return true;
};

