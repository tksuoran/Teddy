
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


#include "Teddy/Signals/Functor.h"
#include "Teddy/Maths/Vector2.h"
#include "Teddy/SysSupport/StdSDL.h"


namespace Teddy              {
namespace PhysicalComponents {


struct Event {
	int                          type;
    SDL_keysym                   key;
    int                          item_id;
    int                          state;
    Teddy::Maths::TVector2<int>  pos;
    Teddy::Maths::TVector2<int>  delta;

	static const int Event_ID                  ;
	static const int WindowEvent_ID            ;
	static const int WindowFocusActiveEvent_ID ;
	static const int WindowPopupOpenEvent_ID   ;
	static const int WindowPopupCloseEvent_ID  ;
	static const int WindowMoveEvent_ID        ;
	static const int WindowSizeEventEvent_ID   ;
	static const int WindowToFrontEvent_ID     ;
	static const int WindowToBackEvent_ID      ;
	static const int WindowSplitUpdateEvent_ID ;
	static const int MouseButtonDownEvent_ID   ;
	static const int MouseButtonUpEvent_ID     ;
	static const int MouseMotionEvent_ID       ;
	static const int MouseDragEvent_ID         ;
	static const int MouseHoldDragEvent_ID     ;
	static const int KeyEvent_ID               ;
	static const int KeyDownEvent_ID           ;
	static const int KeyUpEvent_ID             ;
	static const int JoyEvent_ID               ;
	static const int JoyButtonEvent_ID         ;
	static const int JoyAxisEvent_ID           ;
	static const int JoyHatEvent_ID            ;
	static const int JoyBallEvent_ID           ;
};

struct WindowEvent : public Event {
};

struct WindowFocusActiveEvent : public WindowEvent {
    WindowFocusActiveEvent( int active ){
        type  = WindowFocusActiveEvent_ID;
        state = active;
    }
};

struct WindowPopupOpenEvent : public WindowEvent {
    WindowPopupOpenEvent(){
        type = WindowPopupOpenEvent_ID;
    }
};

struct WindowPopupCloseEvent : public WindowEvent {
    WindowPopupCloseEvent(){
        type = WindowPopupCloseEvent_ID;
    }
};

struct WindowMoveEvent : public WindowEvent {
    WindowMoveEvent(){
        type = WindowMoveEvent_ID;
    }
};

struct WindowSizeEventEvent : public WindowEvent {
    WindowSizeEventEvent(){
        type = WindowSizeEventEvent_ID;
    }
};

struct WindowToFrontEvent : public WindowEvent {
    WindowToFrontEvent(){
        type = WindowToFrontEvent_ID;
    }
};

struct WindowToBackEvent : public WindowEvent {
    WindowToBackEvent(){
        type = WindowToBackEvent_ID;
    }
};

struct WindowSplitUpdateEvent : public WindowEvent {
    WindowSplitUpdateEvent(){
        type = WindowSplitUpdateEvent_ID;
    }
};

struct MouseEvent : public Event {
};

struct MouseButtonDownEvent : public MouseEvent {
    MouseButtonDownEvent( const int button, const int state, const Teddy::Maths::TVector2<int> &pos ){
        type        = MouseButtonDownEvent_ID;
        item_id     = button;
        this->state = state;
        this->pos   = pos;
    }
};

struct MouseButtonUpEvent : public MouseEvent {
    MouseButtonUpEvent( const int button, const int state, const Teddy::Maths::TVector2<int> &pos ){
        type        = MouseButtonUpEvent_ID;
        item_id     = button;
        this->state = state;
        this->pos   = pos;
    }
};

struct MouseMotionEvent : public MouseEvent {
    MouseMotionEvent( const Teddy::Maths::TVector2<int> &pos, const Teddy::Maths::TVector2<int> &delta ){
        type        = MouseMotionEvent_ID;
        this->pos   = pos;
        this->delta = delta;
    }
};

struct MouseDragEvent : public MouseEvent {
    MouseDragEvent( const Teddy::Maths::TVector2<int> &pos, const Teddy::Maths::TVector2<int> &delta, const int button ){
        type          = MouseDragEvent_ID;
        this->item_id = button;
        this->pos     = pos;
        this->delta   = delta;
    }
};

struct MouseHoldDragEvent : public MouseEvent  {
    MouseHoldDragEvent( const Teddy::Maths::TVector2<int> &pos, const Teddy::Maths::TVector2<int> &delta, const int button ){
        type          = MouseHoldDragEvent_ID;
        this->item_id = button;
        this->pos     = pos;
        this->delta   = delta;
    }
};

struct KeyEvent : public Event {
};

struct KeyDownEvent : public KeyEvent {
    KeyDownEvent( const SDL_keysym key ){
        type      = KeyDownEvent_ID;
        this->key = key;
    }
};

struct KeyUpEvent : public KeyEvent {
    KeyUpEvent( const SDL_keysym key ){
        type      = KeyUpEvent_ID;
        this->key = key;
    }
};

struct JoyEvent : public Event {
};

struct JoyButtonEvent : public JoyEvent {
    JoyButtonEvent( const int button_id, const int state ){
        type          = JoyButtonEvent_ID;
        this->item_id = button_id;
        this->state   = state;
    }
};

struct JoyAxisEvent : public JoyEvent {
    JoyAxisEvent( const int axis_id, const int state ){
        type          = JoyAxisEvent_ID;
        this->item_id = axis_id;
        this->state   = state;
    }
};

struct JoyHatEvent : public JoyEvent {
    JoyHatEvent( const int hat_id, const int value ){
        type          = JoyHatEvent_ID;
        this->item_id = hat_id;
        this->state   = value;
    }
};

struct JoyBallEvent : public JoyEvent {
   JoyBallEvent( const int ball_id, const Teddy::Maths::TVector2<int> &delta ){
        type          = JoyBallEvent_ID;
        this->item_id = ball_id;
        this->delta   = delta;
    }
};


//!  EventListener can receive input events from WindowManager
class EventListener {
public:
	EventListener();
	virtual ~EventListener();

	virtual void event       ( const Event &e );
    virtual bool doesEvent   ( int type );
	void         bind        ( int type, Teddy::Signals::Functor1<bool,const Event &> *f );
    void         enableEvent ( int type );
    void         disableEvent( int type );

    unsigned long                                functor_mask;
    unsigned long                                anon_mask;
	Teddy::Signals::Holder1<bool,const Event &>  holder[32];
};


#undef Vector2
#define Vector2 TVector2<float>


};  //  namespace PhysicalComponents'
};  //  namespace Teddy


#endif  //  TEDDY__PHYSICAL_COMPONENTS__EVENT_LISTENER__H


/*
const int Event_ID                  =  0;
const int WindowEvent_ID            =  1;
const int WindowFocusActiveEvent_ID =  2;
const int WindowPopupOpenEvent_ID   =  3;
const int WindowPopupCloseEvent_ID  =  4;
const int WindowMoveEvent_ID        =  5;
const int WindowSizeEventEvent_ID   =  6;
const int WindowToFrontEvent_ID     =  7;
const int WindowToBackEvent_ID      =  8;
const int WindowSplitUpdateEvent_ID =  9;
const int MouseEvent_ID             = 10;
const int MouseButtonEvent_ID       = 11;
const int MouseMotionEvent_ID       = 12;
const int MouseDragEvent_ID         = 13;
const int MouseHoldDragEvent_ID     = 14;
const int KeyEvent_ID               = 15;
const int KeyDownEvent_ID           = 16;
const int KeyUpEvent_ID             = 17;
const int JoyEvent_ID               = 18;
const int JoyButtonEvent_ID         = 19;
const int JoyAxisEvent_ID           = 20;
const int JoyHatEvent_ID            = 21;
const int JoyBallEvent_ID           = 22;
*/

