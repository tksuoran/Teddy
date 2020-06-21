
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


#ifndef TEDDY__PHYSICAL_COMPONENTS__POPUP__H
#define TEDDY__PHYSICAL_COMPONENTS__POPUP__H


#include "Teddy/PhysicalComponents/Dock.h"
#include "Teddy/SysSupport/StdList.h"


namespace Teddy              {
namespace PhysicalComponents {


class Popup:
    public Dock
{

public:
	Popup( std::string name, Area *closed, Area *open );
	Popup( std::string name, Area *open );
    virtual ~Popup();

    Area *getCurrent();
    void  setClosed ( Area *closed );
    void  setOpen   ( Area *open );
    bool  isOpen    ();

    bool  open      ();
    bool  close     ();

protected:
    bool  is_open;
    Area *area_closed;
    Area *area_open;
};


};  //  namespace PhysicalComponents
};  //  namespace Teddy


#endif  //  TEDDY__PHYSICAL_COMPONENTS__POPUP__H

