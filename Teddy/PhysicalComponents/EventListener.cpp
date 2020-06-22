
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


#include "Teddy/PhysicalComponents/EventListener.h"
#include "Teddy/PhysicalComponents/Area.h"
#include "Teddy/PhysicalComponents/ActionButton.h"
#include "Teddy/MixIn/Named.h"
#include "Teddy/SysSupport/Messages.h"
#include "Teddy/SysSupport/StdIO.h"
using namespace Teddy::MixIn;
using namespace Teddy::Signals;
using namespace Teddy::SysSupport;


namespace Teddy              {
namespace PhysicalComponents {


const int Event::Event_ID                  =  0;
const int Event::WindowEvent_ID            =  1;
const int Event::WindowFocusActiveEvent_ID =  2;
const int Event::WindowPopupOpenEvent_ID   =  3;
const int Event::WindowPopupCloseEvent_ID  =  4;
const int Event::WindowMoveEvent_ID        =  5;
const int Event::WindowSizeEventEvent_ID   =  6;
const int Event::WindowToFrontEvent_ID     =  7;
const int Event::WindowToBackEvent_ID      =  8;
const int Event::WindowSplitUpdateEvent_ID =  9;
const int Event::MouseButtonDownEvent_ID   = 10;
const int Event::MouseButtonUpEvent_ID     = 11;
const int Event::MouseMotionEvent_ID       = 12;
const int Event::MouseDragEvent_ID         = 13;
const int Event::MouseHoldDragEvent_ID     = 14;
const int Event::KeyEvent_ID               = 15;
const int Event::KeyDownEvent_ID           = 16;
const int Event::KeyUpEvent_ID             = 17;
const int Event::JoyEvent_ID               = 18;
const int Event::JoyButtonEvent_ID         = 19;
const int Event::JoyAxisEvent_ID           = 20;
const int Event::JoyHatEvent_ID            = 21;
const int Event::JoyBallEvent_ID           = 22;


EventListener::EventListener(){
    functor_mask = anon_mask = 0;
}


EventListener::~EventListener(){
}


void EventListener::bind( int type, Functor1<bool,const Event &> *f ){
	functor_mask |= (1<<(type));
	holder[type].functor = f;
}


/*virtual*/ bool EventListener::doesEvent( int type ){
    return ( functor_mask & 1<<(type)) != 0;
}


void EventListener::enableEvent( int type ){
    functor_mask |= (1<<(type));
}

void EventListener::disableEvent( int type ){
    functor_mask &= ~(1<<(type));
}


/*virtual*/ void EventListener::event( const Event &e ){
	if( e.type > Event::JoyBallEvent_ID ){
		emsg( M_WME, "Event ERROR %d", e.type );
	}
	if( functor_mask & (1<<(e.type)) ){
		holder[e.type]( e );
    }
}


};  //  namespace PhysicalComponents
};  //  namespace Teddy

