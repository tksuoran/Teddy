
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


#ifndef TEDDY__PHYSICAL_COMPONENTS__MENU_LIST__H
#define TEDDY__PHYSICAL_COMPONENTS__MENU_LIST__H


#include "Teddy/SysSupport/StdList.h"
#include "Teddy/PhysicalComponents/Dock.h"
#include "Teddy/PhysicalComponents/Style.h"


namespace Teddy              {
namespace PhysicalComponents {


class MenuList : public Dock {
public:
	MenuList(  std::string name, const int axis = DOCK_VERTICAL  );
    virtual ~MenuList(){}

	virtual void  drawSelf();

};


};  //  namespace PhysicalComponents
};  //  namespace Teddy


#endif  //  TEDDY__PHYSICAL_COMPONENTS__MENU_LIST__H

