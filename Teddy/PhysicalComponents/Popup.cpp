
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


#include "Teddy/PhysicalComponents/Popup.h"
#include "Teddy/PhysicalComponents/ActionButton.h"
#include "Teddy/PhysicalComponents/Style.h"
#include "Teddy/SysSupport/Messages.h"
#include "Teddy/PhysicalComponents/Button.h"
#include "Teddy/SysSupport/StdIO.h"
using namespace Teddy::SysSupport;
using namespace Teddy::Signals;


#if defined( _MSC_VER )
# include <limits>
#else
extern "C" {
#include <limits.h>
}
#endif


namespace Teddy              {
namespace PhysicalComponents {


//!  Constructor
Popup::Popup( std::string name, Area *closed, Area *open )
:Dock(name)
{
    area_closed  = closed;
    area_open    = open;
    is_open      = false;
    insert( area_closed );
}


Popup::Popup( std::string name, Area *open )
:Dock(name)
{
    area_closed  = new ActionButton( name, functor(this, &Popup::open) );
    area_open    = open;
    is_open      = false;
    insert( area_closed );
}




//!  Destructor
/*virtual*/ Popup::~Popup(){
}


void Popup::setClosed( Area *closed ){
    area_closed = closed;
}

void Popup::setOpen( Area *open ){
    area_open = open;
}


bool Popup::isOpen(){
    return is_open;
}


bool Popup::open(){
    if( !is_open ){
        is_open = true;
        remove( area_closed );
        insert( area_open );
        if( parent != NULL ){
            window_manager->update();
        }
    }
	return true;
}


Area *Popup::getCurrent(){
    if( is_open ){
        return area_open;
    }else{
        return area_closed;
    }
}

bool Popup::close(){
    if( is_open ){
        is_open = false;
        remove( area_open );
        insert( area_closed );
        if( parent != NULL ){
            window_manager->update();
        }
    }
	return true;
}


};  //  namespace PhysicalComponents
};  //  namespace Teddy

