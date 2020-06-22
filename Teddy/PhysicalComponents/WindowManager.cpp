
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
#include "Teddy/PhysicalComponents/ActionButton.h"
#include "Teddy/PhysicalComponents/WindowManager.h"
#include "Teddy/PhysicalComponents/Dock.h"
#include "Teddy/PhysicalComponents/Layer.h"
#include "Teddy/Graphics/View.h"
#include "Teddy/Graphics/ImageFileTexture.h"
#include "Teddy/SysSupport/Messages.h"
#include "Teddy/SysSupport/StdSDL.h"
#include "Teddy/SysSupport/StdIO.h"
using namespace Teddy::Graphics;


namespace Teddy              {
namespace PhysicalComponents {


//! Constructor
WindowManager::WindowManager( View *view ){
	int i;

	this->view        = view;
	this->focus       = NULL;
	this->show_cursor = true;

	//SDL_EnableUNICODE  ( 1 );
	//SDL_EnableKeyRepeat( SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL );

#	if 0//!defined( USE_TINY_GL )
	this->cursor    = new ImageFileTexture( "Data/gui/frontier_cursor.png" );
	if( cursor != NULL ){
		if( cursor->isGood() == true ){
			//SDL_ShowCursor( SDL_DISABLE );
		}
	}
#	else
	this->cursor = NULL;
#	endif

#if defined( HAVE_SDL_JOYSTICKOPEN )
	//  Quick-hack joystick test code
	int num_joys = SDL_NumJoysticks();
	dmsg( M_INIT, "%d joysticks found", num_joys );
	for( i=1; i<=num_joys; i++ ){
		const char *j_name = SDL_JoystickName( i );
		if( j_name != NULL ){
			dmsg( M_WME, "Joystick number %d: %s", i, j_name );
		}
	}
	
	if( num_joys >= 1 ){
		//  Open first joystick
		joystick = SDL_JoystickOpen( 0 );
		if( joystick != NULL ){
			int joy_axes    = SDL_JoystickNumAxes   ( joystick );
			int joy_balls   = SDL_JoystickNumBalls  ( joystick );
			int joy_hats    = SDL_JoystickNumHats   ( joystick );
			int joy_buttons = SDL_JoystickNumButtons( joystick );
            dmsg( M_WME,
				"Joystick: %d axes %d balls %d hats %d buttons", 
				joy_axes,
				joy_balls,
				joy_hats,
				joy_buttons
			);

			//int joy_events_enabled = SDL_JoystickEventState( SDL_DISABLE );
			int joy_events_enabled = SDL_JoystickEventState( SDL_ENABLE );
			if( joy_events_enabled == SDL_ENABLE ){
				dmsg( M_WME, "Joystick events enabled" );
			}else{
				dmsg( M_WME, "Joystick events : %d", joy_events_enabled );
			}
		}else{
			emsg( M_WME, "SDL_JoystickOpen() did not work" );
		}
	}else{
		joystick = NULL;
	}
#else
    dmsg( M_INIT, "Teddy was compiled without SDL joystick support" );
	joystick = NULL;
#endif

	show_cursor = true;
	hold        = false;

	for( i=1; i<4; i ++ ){ 
		mouse_b[i] = 0; 
	} 
	hold_pos  = view->getSize() / 2; 
	mouse_pos = view->getSize() / 2; 
	//SDL_WarpMouse( (int)hold_pos[0], (int)hold_pos[1] );
}


//!  Destructor
WindowManager::~WindowManager(){
#if defined( HAVE_SDL_JOYSTICKOPEN )
	if( joystick != NULL ){
		SDL_JoystickClose( joystick );
		joystick = NULL;
	}
#endif
}


//!  Never returning input loop forwarding host system messages to application
void WindowManager::inputLoop(){
	for( ;; ){
		SDL_Event event;

#	if !defined( USE_TINY_GL )
		SDL_Delay( 1 );  // FIX some kind of delay is needed if going faster than 100 fps
#	endif
		view->display();

        while( SDL_PollEvent(&event) ) {
            switch( event.type ){

            case SDL_KEYDOWN:
                switch( event.key.keysym.sym ){
                case SDLK_ESCAPE:
					dmsg( M_WME, "SDL_KEYDOWN SDLK_ESCAPE" );
					exit( 0 );
					break;
                case SDLK_EXCLAIM: // for those that dont have print key
                case SDLK_PRINTSCREEN:
					dmsg( M_WME, "SDL_KEYDOWN SDLK_EXCLAIM or SDLK_PRINT" );
					view->pngScreenshot( "shot.png" );
					break;
                default: break;
                }
                break;
            case SDL_MOUSEMOTION:
                dmsg( M_WME, "SDL_MOUSEMOTION" );
                mouseMotion( event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel );
                break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                dmsg( M_WME, "SDL_MOUSEBUTTONDOWN / SDL_MOUSEBUTTONUP" );
                mouseKey( event.button.button, event.button.state, event.button.x, event.button.y );
                break;
            case SDL_QUIT:
				dmsg( M_WME, "SDL_QUIT" );
				exit( 0 );
				break;
            default:
                break;
            }

            if( focus != NULL ){  //  Some focus
				Named       *focus_name = dynamic_cast<Named *>( focus );
				std::string  names      = "[unnamed]";
				if( focus_name != NULL ){
					names = focus_name->getName();
				}
				const char *name = names.c_str();
                dmsg( M_WME, "%s focus", name );
                switch( event.type ){
                case SDL_KEYDOWN:
					dmsg( M_WME, "SDL_KEYDOWN" );
					focus->event( KeyDownEvent  (event.key.keysym.scancode, event.key.keysym.sym, event.key.keysym.mod) );
					break;
                case SDL_KEYUP:
					dmsg( M_WME, "SDL_KEYUP" );
					focus->event( KeyUpEvent    (event.key.keysym.scancode, event.key.keysym.sym, event.key.keysym.mod) );
					break;
                case SDL_JOYAXISMOTION:
					dmsg( M_WME, "SDL_JOYAXISMOTION" );
					focus->event( JoyAxisEvent  (event.jaxis.axis, event.jaxis.value) );
					break;
                case SDL_JOYHATMOTION:
					dmsg( M_WME, "SDL_JOYHATMOTION" );
					focus->event( JoyHatEvent   (event.jhat.hat, event.jhat.value) );
					break;
                case SDL_JOYBALLMOTION:
					dmsg( M_WME, "SDL_JOYBALLMOTION" );
					focus->event( JoyBallEvent  (event.jball.ball, Vector2(event.jball.xrel,event.jball.yrel) ) );\
					break;
                case SDL_JOYBUTTONDOWN:
                case SDL_JOYBUTTONUP:
					dmsg( M_WME, "SDL_JOYBUTTONDOWN / SDL_JOYBUTTONUP" );
					focus->event( JoyButtonEvent(event.jbutton.button, event.jbutton.state) ); 
					break;
                default:
                    break;
                }
            }
        }  //  while( SDL_PollEvent(&event) )
    }  //  for(;;){
}


//!  MouseListener interface
/*virtual*/ void WindowManager::mouseKey( int button, int state, int x, int y ){
	EventListener *focus_try      = NULL;
    Area          *focus_try_area = NULL;
    Vector2        pos(x,y);

	mouse_b[button] = state;

#	if defined( USE_TINY_GL )
	bool all_released = true;
	for( int i=1; i<4; i++ ){
		if( mouse_b[i] == SDL_PRESSED ){
			all_released = false;
		}
	}
#	endif


	//  Every click checks if area needs to be changed
	//  This is click to focus policy
	//  Should be configurable; do later
	if( state==SDL_PRESSED ){
        dmsg( M_WME, "looking for hit" );
		Area *hit = NULL;

		list<Layer*>::iterator l_it = layers.begin();
		while( l_it != layers.end() ){
			Layer *l = (*l_it);
			hit = l->getHit( pos );
			if( hit != NULL ){
				break;
			}
			l_it++;
		}

		if( hit == NULL ){
			dmsg( M_WME, "No area there" );
		}else{
			dmsg( M_WME, "Click over %s", hit->getName().c_str() );

			Named        *focus_name = dynamic_cast<Named *>( hit );
			std::string   name       = "[unnamed]";
			if( focus_name != NULL ){
				name = focus_name->getName();
			}
			//  Is this Area an EventListener one?
			dmsg( M_WME, "Area          * = 0x%08x", (unsigned long)(hit)       );
			focus_try = dynamic_cast<EventListener*>( hit );
			dmsg( M_WME, "EventListener * = 0x%08x", (unsigned long)(focus_try) );
			if( focus_try == NULL ){
				dmsg( M_WME, "%s is not listening to events", name.c_str() );
			}

			this->setFocus( focus_try );
		}

	}

	Named       *focus_name = dynamic_cast<Named *>( focus );
	std::string  name       = "[unnamed]";
	if( focus_name != NULL ){
		name = focus_name->getName();
	}

	//  FIX It is unclear - should use style or something - if
	//  Area wants to receive the event that activated it.
	if( focus != NULL ){
		if( state && focus->doesEvent(Event::MouseButtonDownEvent_ID) ){
			dmsg( M_WME, "MouseButtonDownEvent sent to %s", name.c_str() );
			focus->event( MouseButtonDownEvent(button,state,pos) );
		}else if( !state && focus->doesEvent(Event::MouseButtonUpEvent_ID) ){
			dmsg( M_WME, "MouseButtonUpEvent sent to %s", name.c_str() );
			focus->event( MouseButtonUpEvent(button,state,pos) );
        }else{
			dmsg( M_WME, "does not MouseButtonDownEvent / MouseButtonUpEvent" );
        }
		if( focus->doesEvent(Event::MouseHoldDragEvent_ID) ){
			hold_pos = pos;
			setHold( state==SDL_PRESSED ? true : false );
        }else{
			dmsg( M_WME, "does not MouseHoldDragEvent_ID" );
        }
	}else{
		dmsg( M_WME, "No Area has focus" );
	}

}


//  MouseListener interface
/*virtual*/ void WindowManager::mouseMotion( int x, int y, int dx, int dy ){
    IntVector2 pos(x,y);
	//  Motion does not currently check for
	//  focus change; Click to focus policy is used
	//  Should be able to change focus with motion
	//  only too; Add later

	//  If warping, don't process mouse motion
	//  Actually here may be some cases which want the
	//  motion

    IntVector2 delta = hold ? IntVector2(dx, dy) : pos - mouse_pos;
    mouse_pos = pos;

	if( focus == NULL ){
		dmsg( M_WME, "No Area has focus" );
		return;
	}

	Named       *focus_name = dynamic_cast<Named *>( focus );
	std::string  names      = "[unnamed]";
	if( focus_name != NULL ){
		names = focus_name->getName();
	}
	const char *name = names.c_str();

	if( focus->doesEvent(Event::MouseMotionEvent_ID) ){
		focus->event( MouseMotionEvent(mouse_pos,delta) );
	}else{
		dmsg( M_WME, "%s does not MouseMotionEvent", name );
	}

	//  Update last button drag positions
	for( int b=1; b<4; b++ ){
		if( mouse_b[b]==SDL_PRESSED ){
			if( focus->doesEvent(Event::MouseHoldDragEvent_ID) ){
#				if defined( USE_TINY_GL )
				//SDL_ShowCursor( SDL_DISABLE );
#				endif
				focus->event( MouseHoldDragEvent(pos,delta,b) );
			}else if( focus->doesEvent(Event::MouseDragEvent_ID) ){
				focus->event( MouseDragEvent(pos,delta,b) );
			}else{
				dmsg( M_WME, "%s does not MouseHoldDragEvent nor MouseDragEvent", name );
			}
		}
	}

}


//!  Insert Layer to View
void WindowManager::insert( Layer *layer ){
	layers.push_back( layer );
}


//!  Show mouse cursor
void WindowManager::showCursor(){
#	if !defined( USE_TINY_GL )
	show_cursor = true;
#	else
	//SDL_ShowCursor( SDL_ENABLE );
#	endif
}


//!  Hide mouse cursor
void WindowManager::hideCursor(){
#	if !defined( USE_TINY_GL )
	show_cursor = false;
#	else
	//SDL_ShowCursor( SDL_DISABLE );
#	endif
}

 
//!  Draw layers
void WindowManager::draw(){
	list<Layer*>::iterator l_it = layers.begin();
	while( l_it != layers.end() ){
		Layer *l = (*l_it);
		l->drawLayer();
		l_it++;
	}

	view->begin2d();
	view->enable( View::TEXTURE_2D );
	view->enable( View::BLEND );

#	if !defined( USE_TINY_GL )
	if( (show_cursor == true) && (cursor != NULL) && (cursor->isGood() == true) ){
		view->color( C_WHITE );
		Vector2 fpos = mouse_pos - cursor->getSize()/2;
		view->blit( fpos, cursor );
	}
#	endif
}


//!  Update all windows, after view resize etc.
void WindowManager::update(){
	list<Layer*>::iterator l_it = layers.begin();
	while( l_it != layers.end() ){
		(*l_it)->update( view );
		l_it++;
	}
}



void WindowManager::setHold( bool apply ){
	dmsg( M_WME, "WindowManager::setHold( %s )", apply?"true":"false" );
	if( hold != apply ){
		hold     = apply;
		if( hold == true ){
            SDL_SetRelativeMouseMode(SDL_TRUE);
			hold_pos = mouse_pos;
			dmsg( M_WME, "Set hold to true" );
		}else{
            SDL_SetRelativeMouseMode(SDL_FALSE);
			dmsg( M_WME, "Hold released" );
		}
		if( cursor == NULL || cursor->isGood() == false ){
			if( hold==true ){
				//SDL_ShowCursor( SDL_DISABLE );
			}else{
				//SDL_ShowCursor( SDL_ENABLE );
			}
		}
	}else{
		dmsg( M_WME, "Hold unchanged" );
	}
}


bool WindowManager::getHold() const {
	return hold;
}


//!  Set focus
void WindowManager::setFocus( EventListener *focus_try ){
	if( focus != focus_try ){
		if( focus != NULL ){
			focus->event( WindowFocusActiveEvent(0) );
		}
		focus = focus_try;
		if( focus != NULL ){
			focus->event( WindowFocusActiveEvent(1) );
		}
	}
}


//!  Return View
View *WindowManager::getView(){
	return this->view;
}


};  //  namespace PhysicalComponents
};  //  namespace Teddy


