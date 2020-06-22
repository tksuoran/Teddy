
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


#include "Teddy/Application/BaseSimulationTimer.h"
#include "Teddy/Behaviour/Control.h"
#include "Teddy/Behaviour/ModelAnimator.h"
#include "Teddy/Graphics/View.h"
#include "Teddy/Materials/Material.h"
#include "Teddy/Models/Model.h"
#include "Teddy/PhysicalComponents/ActionButton.h"
#include "Teddy/PhysicalComponents/EventListener.h"
#include "Teddy/PhysicalComponents/Frame.h"
#include "Teddy/PhysicalComponents/MenuList.h"
#include "Teddy/PhysicalComponents/Projection.h"
#include "Teddy/PhysicalComponents/WindowManager.h"
#include "Teddy/Scenes/Camera.h"
#include "Teddy/Scenes/Scene.h"
#include "Teddy/SysSupport/Messages.h"
#include "Teddy/SysSupport/StdIO.h"
#ifndef SWIG
#include <sstream>
#endif

#include "CameraController.h"
#include "Display.h"
#include "ObjectManager.h"
#include "Root.h"
#include "UserInterface.h"

using namespace Teddy::Application;
using namespace Teddy::Behaviour;
using namespace Teddy::Graphics;
using namespace Teddy::Materials;
using namespace Teddy::PhysicalComponents;
using namespace Teddy::Scenes;
using namespace Teddy::Signals;


#define CONTROL_KEY_STRAFE_LEFT  SDLK_LEFT
#define CONTROL_KEY_STRAFE_RIGHT SDLK_RIGHT
#define CONTROL_KEY_STRAFE_UP    SDLK_UP     //  See SDL documentation and/or
#define CONTROL_KEY_STRAFE_DOWN  SDLK_DOWN   //  header files for other keys.


int Display::count = 0;

Display::Display( Root *root, Camera *camera )
:
Node(root),
Projection( "TestEvents Display Projection", camera )
{
	is_active = false;

    offset_pixels             = Vector2( 0.0f, 20.0f );  //!<  offset in pixels
    offset_self_size_relative = Vector2(-0.5f, -0.5f );  //!<  offset relative to self size
    offset_free_size_relative = Vector2( 0.5f,  0.5f );  //!<  offset relative to remaining free size
	fill_base_pixels          = Vector2(-40.0f,-40.0f );  //!<
    fill_free_size_relative   = Vector2( 1.0f,  1.0f );  //!<

	controller    = new CameraController( NULL, root );
	joy_rot_up    = 0;
	joy_rot_right = 0;
	joy_rot_view  = 0;
	getSimulationTimer()->add( this );

	string name = string("Display");

	MenuList *menu = new MenuList( "Frame Menu", DOCK_HORIZONTAL );
	menu->insert(  new ActionButton( name,    functor(this,&Display::activate ) )  );
	menu->insert(  new ActionButton( "Move",  functor(this,&Display::moving), Event::MouseDragEvent_ID   )  );
	menu->insert(  new ActionButton( "Size",  functor(this,&Display::sizing), Event::MouseDragEvent_ID   )  );
	menu->insert(  new ActionButton( "Close", functor(this,&Display::close ) )  );
	menu->offset_self_size_relative = Vector2( 0.0f, -1.0f );
	menu->offset_pixels             = Vector2( 0.0f, -style->border[1] );

	this->insert( menu );

 
	//  Append postfix to contract id
	ostringstream fr_name;
	fr_name << "Display " << ++count;
	Frame *f = new Frame( fr_name.str() );
	this->insert( f );

    bind( Event::MouseButtonDownEvent_ID,   functor(this,&Display::mouseKey    ) );
    bind( Event::MouseButtonUpEvent_ID,     functor(this,&Display::mouseKey    ) );
    bind( Event::MouseMotionEvent_ID,   functor(this,&Display::mouseMotion ) );
    bind( Event::MouseHoldDragEvent_ID, functor(this,&Display::mouseMotion ) );
    bind( Event::KeyDownEvent_ID,       functor(this,&Display::keyDown     ) );
    bind( Event::KeyUpEvent_ID,         functor(this,&Display::keyUp       ) );
    bind( Event::JoyAxisEvent_ID,       functor(this,&Display::joyAxis     ) );
    bind( Event::JoyButtonEvent_ID,     functor(this,&Display::joyButton   ) );
    bind( Event::JoyHatEvent_ID,        functor(this,&Display::joyHat      ) );
	bind( Event::WindowFocusActiveEvent_ID, functor(this,&Display::activate   ) );
	//disableEvent( Event::MouseMotionEvent_ID );
    setHold( false ); // initially in drag mode

	//  Model animator
	model_animator = new ModelAnimator( NULL );
	controller->setAnimator( model_animator );
	getSimulationTimer()->add( model_animator );

	dmsg( M_INIT, "New Display" );
}


/*virtual*/ Display::~Display(){
}


//!  Set controller target
void Display::bindController( Model *model ){
	model_animator->setModel( model );
}


CameraController *Display::getCameraController(){
	return controller;
}


void Display::toggleHold(){
	setHold( !hold );
}


void Display::setHold( bool hold ){
	this->hold = hold;

	if( hold == true ){
		this->enableEvent ( Event::MouseMotionEvent_ID   );
		this->disableEvent( Event::MouseHoldDragEvent_ID );
	}else{
		this->disableEvent( Event::MouseMotionEvent_ID   );
		this->enableEvent ( Event::MouseHoldDragEvent_ID );
	}
	if( is_active == true ){
		getUserInterface()->getWindowManager()->setHold( hold );
	}
}


//!  MouseListener interface
/*virtual*/ bool Display::mouseKey( const Event &e ){
    const int &button = e.item_id;
    const int &state  = e.state;

	if( (button == 1) && (state == SDL_PRESSED) && (enable_select == true) ){

		selectModel( e );

	}else{

		if( button == 1 ){
			controller->getTranslateView()->more( state==1?true:false );
		}
		if( button == 3 ){
			controller->getTranslateView()->less( state==1?true:false );
		}

	}
	return true;
}


//!  Mouse motion
/*virtual*/ bool Display::mouseMotion( const Event &e ){
	dmsg( M_WME, "Display::mouseMotion" );
	controller->getRotateUp   ()->adjust( rads(-0.1) * e.delta[0] );
	controller->getRotateRight()->adjust( rads(-0.1) * e.delta[1] );
	return true;
}


/*virtual*/ void Display::tick(){
	controller->getRotateUp   ()->adjust( joy_rot_up    );
	controller->getRotateRight()->adjust( joy_rot_right );
	controller->getRotateView ()->adjust( joy_rot_view  );
}


#define JOY_AXIS_Y  0
#define JOY_AXIS_X  1
#define JOY_AXIS_W  2
#define JOY_AXIS_Z  3


/*virtual*/ bool Display::joyAxis( const Event &e ){
	dmsg( M_WME, "Display::joyAxis" );
    //const int &axis_id = e.item_id;
    //const int &value   = e.state;;

	float tra = -0.0003 * (float)(e.state); //32768.0;
	float rad = rads(0.00001) * (float)(e.state); //32768.0;
	switch( e.item_id ){
	case JOY_AXIS_Y: joy_rot_up    = -rad; break;
	case JOY_AXIS_X: joy_rot_right =  rad; break;
	case JOY_AXIS_Z: joy_rot_view  =  0.7f* rad; break;
	case JOY_AXIS_W: controller->getTranslateView()->setValue( tra ); break;
	default:
		break;
	}
	return true;
}


/*virtual*/ bool Display::joyButton( const Event &e ){
	dmsg( M_WME, "Display::joyButton" );
	return true;
}


#define JOY_HAT_UP_M    1
#define JOY_HAT_RIGHT_M 2
#define JOY_HAT_DOWN_M  4
#define JOY_HAT_LEFT_M  8
/*virtual*/ bool Display::joyHat( const Event &e ){
	dmsg( M_WME, "Display::joyHat" );
    const int value = e.state;
	controller->getTranslateUp   ()->more( (value & JOY_HAT_UP_M   ) == JOY_HAT_UP_M   );
	controller->getTranslateUp   ()->less( (value & JOY_HAT_DOWN_M ) == JOY_HAT_DOWN_M );
	controller->getTranslateRight()->more( (value & JOY_HAT_RIGHT_M) == JOY_HAT_RIGHT_M);
	controller->getTranslateRight()->less( (value & JOY_HAT_LEFT_M ) == JOY_HAT_LEFT_M );
	return true;
}


/*!
	Handle key down events. When control key is pressed,
	the control is activated. If escape or q is pressed,
	program exists instantly. If space is pressed, speed
	of the camera is set to zero.
*/
/*virtual*/ bool Display::keyDown( const Event &e ){
	dmsg( M_WME, "Display::keyDown" );
	static int        color_select = 0;
	Projection       *p            = getUserInterface()->getProjection();

	switch( e.key_sym ){
	case SDLK_ESCAPE:
	case 'q'        : exit(0); break;
	case '1'        : {
		if( p->getView()->pngScreenshot( "screenshot.png" )==true ){
            printf( "Screenshot saved\n" );
		}else{
            printf( "Screenshot failed\n" );
		}
		break;
	}
	case '2' : {
		p->getView()->displayPs( "figure.ps" );
	}

	case SDLK_SPACE: toggleHold(); break;

	case SDLK_RSHIFT:
	case SDLK_LSHIFT:
		{
		//BaseSimulationTimer *st = getSimulationTimer();
		//st->lock();
		controller->clearControls();
		Model *selected = getObjectManager()->getSelectedModel();
		if( selected != NULL ){
			model_animator->setModel( selected );
		}
		//st->unlock();
		enable_select = true;
		}
		break;

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
	case 'a': p->getSelect().toggle(Material::RENDER_OPTION_AMBIENT_M   ); break;
	case 'd': p->getSelect().toggle(Material::RENDER_OPTION_DIFFUSE_M   ); break;
	case 's': p->getSelect().toggle(Material::RENDER_OPTION_SPECULAR_M  ); break;
	case 'S': p->getSelect().toggle(Material::RENDER_OPTION_SHINYNESS_M ); break;
	case 'w': controller->enableDamp (); break;
	case 'e': controller->disableDamp(); break;
	case 'm': p->getSelect().toggle(Material::RENDER_OPTION_MASTER_LIGHTING_ONLY_M ); break;
	default: break;
	}
	return true;
};


/*!
	Handle key up events. When control key is released,
	the control is deactivated.
*/
/*virtual*/ bool Display::keyUp( const Event &e ){
	dmsg( M_WME, "Display::keyUp" );
	switch( e.key_sym ){
	case CONTROL_KEY_STRAFE_RIGHT: controller->getTranslateRight()->more(false); break;
	case CONTROL_KEY_STRAFE_LEFT : controller->getTranslateRight()->less(false); break;
	case CONTROL_KEY_STRAFE_UP   : controller->getTranslateUp   ()->more(false); break;
	case CONTROL_KEY_STRAFE_DOWN : controller->getTranslateUp   ()->less(false); break;
	case SDLK_RSHIFT:
	case SDLK_LSHIFT:
		{
		//BaseSimulationTimer *st = getSimulationTimer();
		enable_select = false;
		//st->lock();
		controller->clearControls();
		model_animator->setModel( getObjectManager()->getCamera() );
		//st->unlock();
		}
		break;

	default: break;
	}
	return true;
};


bool Display::moving( const Event &e ){ 
	dmsg( M_WME, "Display::moving( %4.4f, %4.4f )", e.delta[0], e.delta[1] );
	offset_pixels += e.delta;
    window_manager->update();
	return true; 
}

bool Display::sizing( const Event &e ){ 
	dmsg( M_WME, "Display::sizing( %4.4f, %4.4f )", e.delta[0], e.delta[1] );
	fill_base_pixels += e.delta;
    window_manager->update();
	return true; 
}

bool Display::close(){
	return true;
}

bool Display::activate( const Event &e ){
	getUserInterface()->setDisplay( this );
	if( e.state != 0 ){
		is_active = true;
		dmsg( M_WME, "Display::activate() while my hold is %s", hold?"true":"false" );
		getUserInterface()->getWindowManager()->setHold( hold );
	}else{
		is_active = false;
		getUserInterface()->getWindowManager()->setHold( false );
	}
	return true;
}

bool Display::selectModel( const Teddy::PhysicalComponents::Event &e ){
    Model *selected_model = pick( e.pos );
	getObjectManager()->selectModel( selected_model );
	if( selected_model != NULL ){
	}else{
	} 
	return true;
}
