
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

	$Id: Button.h,v 1.4 2002/01/11 14:35:03 tksuoran Exp $
*/


#ifndef TEDDY__PHYSICAL_COMPONENTS__BUTTON__H
#define TEDDY__PHYSICAL_COMPONENTS__BUTTON__H


#include "Teddy/PhysicalComponents/Area.h"


namespace Teddy              {
namespace PhysicalComponents {


//!  Simple pushbutton
class Button : public Area {
public:
	Button(  std::string label );

	//  Area interface
	virtual void drawSelf();

protected:
	enum e_state {
		up,
		pressed		
	};
	e_state     state;
	std::string label;
};


};  //  namespace PhysicalComponents
};  //  namespace Teddy


#endif  //  TEDDY__PHYSICAL_COMPONENTS__BUTTON__H

