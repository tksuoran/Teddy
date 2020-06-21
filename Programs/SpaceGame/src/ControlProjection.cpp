
/*
	TSGL - Teddy Space Game Library
	Copyright (C) 2002 Timo Suoranta
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


#include "Teddy/Behaviour/Control.h"
#include "Teddy/Application/BaseSimulationTimer.h"
#include "Teddy/Graphics/View.h"
#include "Teddy/PhysicalComponents/WindowManager.h"
#include "Teddy/PhysicalComponents/Style.h"
#include "Teddy/PhysicalComponents/Label.h"
#include "Teddy/SysSupport/Messages.h"
#include "SDL_mouse.h"

#include "ActionManager.h"
#include "ControlProjection.h"
#include "ModelCamera.h"
#include "ObjectManager.h"
#include "PlayerController.h"
#include "UserInterface.h"
using namespace Teddy::Behaviour;
using namespace Teddy::Graphics;
using namespace Teddy::PhysicalComponents;
using namespace Teddy::SysSupport;
using namespace Teddy::Signals;


//!  Constructor
ControlProjection::ControlProjection( const char *name, Camera *camera, Root *root )
:
Node      ( root         ),
Projection( name, camera )
{
	this->alt_down   = false;

    fill_free_size_relative = Vector2( 0.4f, 0.4f );    //!<

	title = new Label( "" );
/*	LayoutConstraint *cons = title->getLayoutConstraint();
	cons->local_x_offset_relative  = -0.5;
	cons->local_y_offset_relative  = -0.5;
	cons->parent_x_offset_relative =  0.5;
	cons->parent_y_offset_relative =  0;
	cons->local_y_offset_pixels    = 10;*/
	this->insert( title );

	joy_rot_up    = 0;
	joy_rot_right = 0;
	joy_rot_view  = 0;
	getSimulationTimer()->add( this );

    bind( Event::MouseButtonDownEvent_ID, functor(this,&ControlProjection::mouseKey    ) );
    bind( Event::MouseButtonUpEvent_ID,   functor(this,&ControlProjection::mouseKey    ) );
    bind( Event::MouseMotionEvent_ID,     functor(this,&ControlProjection::mouseMotion ) );
    bind( Event::MouseHoldDragEvent_ID,   functor(this,&ControlProjection::mouseMotion ) );
    bind( Event::KeyDownEvent_ID,         functor(this,&ControlProjection::keyDown     ) );
    bind( Event::KeyUpEvent_ID,           functor(this,&ControlProjection::keyUp       ) );
    bind( Event::JoyAxisEvent_ID,         functor(this,&ControlProjection::joyAxis     ) );
    bind( Event::JoyButtonEvent_ID,       functor(this,&ControlProjection::joyButton   ) );
    bind( Event::JoyHatEvent_ID,          functor(this,&ControlProjection::joyHat      ) );

}


void ControlProjection::toggleHold(){
	setHold( !hold );
}

void ControlProjection::setHold( bool hold ){
	this->hold = hold;
	WindowManager *wm = root->getUserInterface()->getWindowManager();

	if( hold == true ){
		wm->setHold( true );
		this->enableEvent ( Event::MouseMotionEvent_ID   );
		this->disableEvent( Event::MouseHoldDragEvent_ID );
	}else{
		wm->setHold( false );
		this->disableEvent( Event::MouseMotionEvent_ID   );
		this->enableEvent ( Event::MouseHoldDragEvent_ID );
	}
}


/*
bool ControlProjection::focusActive(){
	if( active ){
		getObjectManager()->setCamera( this->camera );
	}
}*/


//!  MouseListener interface
bool ControlProjection::mouseKey( const Event &e ){
	if( hold == true ){
		PlayerController *pc = getObjectManager()->getPlayerController();
		if( e.item_id/*button*/ == 1 ){
			pc->getTranslateView()->more( e.state==1?true:false );
		}
		if( e.item_id/*button*/ == 3 ){
			pc->getTranslateView()->less( e.state==1?true:false );
		}
	}else if( (e.item_id/*button*/ == SDL_BUTTON_LEFT) &&
	          (e.state  == SDL_RELEASED   )    )
	{
		getObjectManager()->selectModel( e.pos );
	}
	return true;
}


bool ControlProjection::mouseDrag( const Event &e ){
	PlayerController *pc = getObjectManager()->getPlayerController();
	pc->getRotateRight()->adjust( -e.delta[1] * 0.001 );
	pc->getRotateUp   ()->adjust( -e.delta[1] * 0.001 );
	return true;
}


bool ControlProjection::mouseMotion( const Event &e ){
	PlayerController *pc = getObjectManager()->getPlayerController();
	if( hold == true ){
		pc->getRotateUp   ()->adjust( rads(-0.1) * e.delta[0] );
		pc->getRotateRight()->adjust( rads(-0.1) * e.delta[1] );
	}
	return true;
}


/*virtual*/ void ControlProjection::tick(){
	PlayerController *pc = getObjectManager()->getPlayerController();
	pc->getRotateUp   ()->adjust( joy_rot_up    );
	pc->getRotateRight()->adjust( joy_rot_right );
	pc->getRotateView ()->adjust( joy_rot_view  );
}


#define JOY_AXIS_Y  0
#define JOY_AXIS_X  1
#define JOY_AXIS_W  2
#define JOY_AXIS_Z  3


bool ControlProjection::joyAxis( const Event &e ){
	PlayerController *pc = getObjectManager()->getPlayerController();
	double tra = -0.0002 * (double)(e.state /*value*/); //32768.0;
	double rad = (double)(e.state /*value*/ ) / (500.0*32768.0); //32768.0;
	switch( e.item_id /*axis_id*/ ){
	case JOY_AXIS_Y: joy_rot_up    = -rad; break;
	case JOY_AXIS_X: joy_rot_right =  rad; break;
	case JOY_AXIS_Z: joy_rot_view  =  rad; break;
	case JOY_AXIS_W: pc->getTranslateView()->setValue( tra ); break;
	default:
		break;
	}
	return true;
}


#define JOY_HAT_UP_M    1
#define JOY_HAT_RIGHT_M 2
#define JOY_HAT_DOWN_M  4
#define JOY_HAT_LEFT_M  8
bool ControlProjection::joyHat( const Event &e ){
	PlayerController *pc = getObjectManager()->getPlayerController();
	pc->getTranslateUp   ()->more( (e.state /*value*/ & JOY_HAT_UP_M   ) == JOY_HAT_UP_M   );
	pc->getTranslateUp   ()->less( (e.state /*value*/ & JOY_HAT_DOWN_M ) == JOY_HAT_DOWN_M );
	pc->getTranslateRight()->more( (e.state /*value*/ & JOY_HAT_RIGHT_M) == JOY_HAT_RIGHT_M);
	pc->getTranslateRight()->less( (e.state /*value*/ & JOY_HAT_LEFT_M ) == JOY_HAT_LEFT_M );
	return true;
}


bool ControlProjection::joyButton( const Event &e ){
	switch( e.item_id/*button_id*/ ){
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	default: break;
	}
	return true;
}


bool ControlProjection::joyBall( const Event &e ){
	return true;
}


//!  KeyListener interface implementation
bool ControlProjection::keyDown( const Event &e ){
	const SDL_keysym &key = e.key;
	ActionManager    *am = getActionManager();
	UserInterface    *ui = getUserInterface();
	ObjectManager    *om = getObjectManager();
	ModelCamera      *mc = getObjectManager()->getModelCamera     ();
	PlayerController *pc = getObjectManager()->getPlayerController();

	if( (key.mod & KMOD_ALT) != 0 ){
		alt_down = true;
	}

	if( alt_down == true ){
		return true;
	}

	switch( key.sym ){
	case SDLK_ESCAPE:
	case 'q': am->quit(); break;

	case SDLK_F9 : {
		if( ui->getProjection()->getView()->pngScreenshot( "screenshot.png" )==true ){
            msg( M_WM, "Screenshot saved\n" );
		}else{
            msg( M_WM, "Screenshot failed\n" );
		}
		break;
	}

	case SDLK_SPACE: toggleHold(); break;

	case 'j': pc->getTranslateView()->toggle( Control::DAMPEN_MULTIPLY_M ); break;
	
	case '5': am->scannerCycle         (); break;
	case 'd': am->blendOn              (); break;
	case 'c': am->blendOff             (); break;
	case 'u': am->renderModePoint      (); break;
	case 'i': am->renderModeLine       (); break;
	case 'o': am->renderModeFill       (); break;
	case 'p': am->renderModeFillOutline(); break;
	case 'v': am->cullFaceDisable      (); break;
	case 'b': am->cullFaceEnable       (); break;
	case 'f': am->depthTestDisable     (); break;
	case 'g': am->depthTestEnable      (); break;
	case 'k': am->lightingOff          (); break;
	case 'l': am->lightingOn           (); break;
	case 'n': am->fovNormal		           (); break;
	case 'm': am->fovWide              (); break;
	case 'r': am->antialiseOff         (); break;
	case 't': am->antialiseOn          (); break;

	case SDLK_F1:       mc->front (); break;
	case SDLK_F2:       mc->left  (); break;
	case SDLK_F3:       mc->right (); break;
	case SDLK_F4:       mc->rear  (); break;
	case SDLK_F5:       mc->top   (); break;
	case SDLK_F6:       mc->bottom(); break;

	case 'a':           pc->getWeaponFire   ()->more( true ); break;
	case 'x':           pc->getRotateRight  ()->more( true ); break;
	case 's':           pc->getRotateRight  ()->less( true ); break;
	case ',':           pc->getRotateView   ()->less( true ); break;
	case '.':           pc->getRotateView   ()->more( true ); break;
	case SDLK_PAGEUP:   pc->getTranslateView()->more( true ); break;
	case SDLK_PAGEDOWN: pc->getTranslateView()->less( true ); break;
	case SDLK_END:      pc->getTranslateView()->stop( true ); break;

	case SDLK_KP5:      mc->getDistance()->setValue( 0 ); break;
	case SDLK_KP1:      mc->getRoll    ()->less( true ); break;
	case SDLK_KP2:      mc->getPitch   ()->less( true ); break;
	case SDLK_KP3:      mc->getRoll    ()->more( true ); break;
	case SDLK_KP4:      mc->getHeading ()->less( true ); break;
	case SDLK_KP6:      mc->getHeading ()->more( true ); break;
	case SDLK_KP7:      mc->getRoll    ()->less( true ); break;
	case SDLK_KP8:      mc->getPitch   ()->more( true ); break;
	case SDLK_KP9:      mc->getRoll    ()->more( true ); break;

	case SDLK_KP_MINUS: mc->getDistance()->more( true ); break;
	case SDLK_KP_PLUS : mc->getDistance()->less( true ); break;
	default: break;
	}
	return true;
};


bool ControlProjection::keyUp( const Event &e ){
	const SDL_keysym &key = e.key;
	PlayerController *pc = getObjectManager()->getPlayerController();
	ModelCamera      *mc = getObjectManager()->getModelCamera     ();

	if( (key.mod & KMOD_ALT) != 0 ){
		alt_down = false;
	}

	switch( key.sym ){

	case 'a':           pc->getWeaponFire   ()->more( false ); break;
	case 'x':           pc->getRotateRight  ()->more( false ); break;
	case 's':           pc->getRotateRight  ()->less( false ); break;
	case ',':           pc->getRotateView   ()->less( false ); break;
	case '.':           pc->getRotateView   ()->more( false ); break;
	case SDLK_PAGEUP:   pc->getTranslateView()->more( false ); break;
	case SDLK_PAGEDOWN: pc->getTranslateView()->less( false ); break;
	case SDLK_END:      pc->getTranslateView()->stop( false ); break;

	case SDLK_KP1:      mc->getRoll    ()->less( false ); break;
	case SDLK_KP2:      mc->getPitch   ()->less( false ); break;
	case SDLK_KP3:      mc->getRoll    ()->more( false ); break;
	case SDLK_KP4:      mc->getHeading ()->less( false ); break;
	case SDLK_KP6:      mc->getHeading ()->more( false ); break;
	case SDLK_KP7:      mc->getRoll    ()->less( false ); break;
	case SDLK_KP8:      mc->getPitch   ()->more( false ); break;
	case SDLK_KP9:      mc->getRoll    ()->more( false ); break;
	case SDLK_KP_MINUS: mc->getDistance()->more( false ); break;
	case SDLK_KP_PLUS : mc->getDistance()->less( false ); break;
	default: break;
	}
	return true;
};

