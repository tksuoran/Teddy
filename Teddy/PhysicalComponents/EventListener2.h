
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

	$Id: EventListener.h,v 1.5 2002/03/12 10:46:07 tksuoran Exp $
*/


#ifndef TEDDY__PHYSICAL_COMPONENTS__EVENT_LISTENER__H
#define TEDDY__PHYSICAL_COMPONENTS__EVENT_LISTENER__H


#include "Teddy/SysSupport/StdSDL.h"
#include "Teddy/SysSupport/Signals.h"


namespace Teddy              {
namespace PhysicalComponents {


struct Event {
    int        type;
    SDL_keysym key;
    int        item_id;
    int        state;
    int        x;
    int        y;
    int        dx;
    int        dy;
};

const int Event_ID = 0;

const int WindowEvent_ID = 1;
struct WindowEvent : public Event {
};

const int WindowEvent_ID = 2;
struct WindowFocusActiveEvent : public WindowEvent {
    WindowFocusActiveEvent( int active ){
        type  = WindowEvent_ID;
        state = active;
    }
};

const int WindowPopupOpenEvent_ID = 3;
struct WindowPopupOpenEvent : public WindowEvent {
    WindowPopupOpenEvent(){
        type = WindowPopupOpenEvent_ID;
    }
};

const int WindowPopupCloseEvent_ID = 4;
struct WindowPopupCloseEvent : public WindowEvent {
    WindowPopupCloseEvent(){
        type = WindowPopupCloseEvent_ID;
    }
};

const int WindowMoveEvent_ID = 5;
struct WindowMoveEvent : public WindowEvent {
    WindowMoveEvent(){
        type = WindowMoveEvent_ID;
    }
}:

const int WindowSizeEventEvent_ID = 6;
struct WindowSizeEventEvent : public WindowEvent {
    WindowSizeEventEvent(){
        type = WindowSizeEventEvent_ID;
    }
};

const int WindowToFrontEvent_ID = 7;
struct WindowToFrontEvent : public WindowEvent {
    WindowToFrontEvent(){
        type = WindowToFrontEvent_ID;
    }
};

const int WindowToBackEvent_ID = 8;
struct WindowToBackEvent : public WindowEvent {
    WindowToBackEvent(){
        type = WindowToBackEvent_ID;
    }
};

const int WindowSplitUpdateEvent_ID = 9;
struct WindowSplitUpdateEvent : public WindowEvent {
    WindowSplitUpdateEvent(){
        type = WindowSplitUpdateEvent_ID;
    }
};

const int MouseEvent_ID = 10;
struct MouseEvent : public Event {
};

const int MouseButtonEvent_ID = 11;
struct MouseButtonEvent : public MouseEvent {
    MouseButtonEvent( int button, int state, int x, int y ){
        type        = MouseButtonEvent_ID;
        item_id     = button;
        this->state = state;
        this->x     = x;
        this->y     = y;
    }
};

const int MouseMotionEvent_ID = 12;
struct MouseMotionEvent : public MouseEvent {
    MouseMotionEvent( int x, int y, int dx, int dy ){
        type     = MouseMotionEvent_ID;
        this->x  = x;
        this->y  = y;
        this->dx = dx;
        this->dy = dy;
    }
};

const int MouseDragEvent_ID = 13;
struct MouseDragEvent : public MouseMotionEvent {
    MouseDragEvent( int x, int y, int dx, int dy,int button ){
        type          = MouseDragEvent_ID;
        this->item_id = button;
        this->x       = x;
        this->y       = y;
        this->dx      = dx;
        this->dy      = dy;
    }
};

const int MouseHoldDragEvent_ID = 14;
struct MouseHoldDragEvent : public MouseDragEvent  {
    MouseHoldDragEvent( int x, int y, int dx, int dy, int button ){
        type          = MouseHoldDragEvent_ID;
        this->item_id = button;
        this->x       = x;
        this->y       = y;
        this->dx      = dx;
        this->dy      = dy;
    }
};

const int KeyEvent_ID = 15;
struct KeyEvent : public Event {
};

const int KeyDownEvent_ID = 16;
struct KeyDownEvent : public KeyEvent {
    KeyDownEvent( SDL_keysym key ){
        type      = KeyDownEvent_ID;
        this->key = key;
    }
};

const int KeyUpEvent_ID = 17;
struct KeyUpEvent : public KeyEvent {
    KeyUpEvent( SDL_keysym key ){
        type      = KeyUpEvent_ID;
        this->key = key;
    }
};

const int JoyEvent_ID = 18;
struct JoyEvent : public Event {
};

const int JoyButtonEvent_ID = 19;
struct JoyButtonEvent : public JoyEvent {
    JoyButtonEvent( int button_id, int state ){
        type          = JoyButtonEvent_ID;
        this->item_id = button_id;
        this->state   = state;
    }
};

const int JoyAxisEvent_ID = 20;
struct JoyAxisEvent : public JoyEvent {
    JoyAxisEvent( int axis_id, int state ){
        type          = JoyAxisEvent_ID;
        this->item_id = axis_id;
        this->state   = state;

    }
};

const int JoyHatEvent_ID = 21;
struct JoyHatEvent : public JoyEvent {
    JoyHatEvent( int hat_id,int value ){
        type          = JoyHatEvent_ID;
        this->item_id = hat_id;
        this->state   = value;
    }
};

const int JoyBallEvent_ID = 22;
struct JoyBallEvent : public JoyEvent {
    JoyBallEvent( int ball_id, int xrel, int yrel ){
        type          = JoyBallEvent_ID;
        this->item_id = ball_id;
        this->dx      = xrel;
        this->dy      = yrel;
    }
};


//!  EventListener can receive input events from WindowManager
class EventListener {
public:
	EventListener();
	virtual ~EventListener();

    void bind ( int type, const SigC::Signal1<void,const Event &> &s ){ signal[type] = s; }
    void event( const Event &e ){ signal[e.type]( e ); }

    unsigned long                     signal_mask;
    SigC::Signal1<void,const Event &> signal[32];
};


};  //  namespace PhysicalComponents'
};  //  namespace Teddy


#endif  //  TEDDY__PHYSICAL_COMPONENTS__EVENT_LISTENER__H

