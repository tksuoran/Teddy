
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


#ifndef TEDDY__PHYSICAL_COMPONENTS__DOCK__H
#define TEDDY__PHYSICAL_COMPONENTS__DOCK__H


#include "Teddy/PhysicalComponents/Area.h"
#include "Teddy/SysSupport/StdList.h"


namespace Teddy              {
namespace PhysicalComponents {


#define DOCK_HORIZONTAL 0
#define DOCK_VERTICAL   1


//!  Vertical docking component
class Dock : public Area {
public:
    Dock( std::string name, const int axis = DOCK_VERTICAL );
	virtual ~Dock();

	virtual void  beginSize ( const Vector2 &ref );
    virtual void  callSize  ( Area *a );
    virtual void  endSize   ();
	virtual void  beginPlace( const Rect &ref );
    virtual void  callPlace ( Area *a );

protected:
    Vector2 cursor_start;
    Vector2 cursor_end;
    int     axis_max;
    int     axis_sum;
};


};  //  namespace PhysicalComponents
};  //  namespace Teddy


#endif  //  TEDDY__PHYSICAL_COMPONENTS__DOCK__H

