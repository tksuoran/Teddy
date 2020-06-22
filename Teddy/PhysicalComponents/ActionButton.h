
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


#ifndef TEDDY__PHYSICAL_COMPONENTS__ACTION_BUTTON__H
#define TEDDY__PHYSICAL_COMPONENTS__ACTION_BUTTON__H


#include "Teddy/TeddyConfig.h"
#include "Teddy/PhysicalComponents/Area.h"
#include "Teddy/PhysicalComponents/EventListener.h"
#include "Teddy/PhysicalComponents/WindowManager.h"
#include "Teddy/Graphics/Color.h"
#include "Teddy/SysSupport/Types.h"
using namespace Teddy::Graphics;


namespace Teddy              {
namespace PhysicalComponents {


//!  Action button
class ActionButton : public EventListener, public Area {
public:
    ActionButton( std::string name, Teddy::Signals::Functor0<bool> *f, const int type = Teddy::PhysicalComponents::Event::MouseButtonUpEvent_ID );
	ActionButton( std::string name, Teddy::Signals::Functor1<bool,const Event &> *f, const int type = Teddy::PhysicalComponents::Event::MouseButtonUpEvent_ID );
	ActionButton( std::string name, Teddy::Signals::Functor1<bool,void *> *f, void *data, const int type = Teddy::PhysicalComponents::Event::MouseButtonUpEvent_ID );
    virtual ~ActionButton();

	//  EventListener modification
	virtual void  event    ( const Event &e );
    virtual bool  doesEvent( int type );

	//  Area implementation
	virtual void  drawSelf ();

protected:
    std::string                                  label;
	int                                          v_type;
	int                                          e_type;
	int                                          d_type;
	Teddy::Signals::Holder0<bool>                v_holder;
	Teddy::Signals::Holder1<bool,const Event &>  e_holder;
	Teddy::Signals::Holder1<bool,void *>         d_holder;
	void                                        *d_data;
};


};  //  namespace PhysicalComponents
};  //  namespace Teddy


#endif  //  TEDDY__PHYSICAL_COMPONENTS__ACTION_BUTTON__H

