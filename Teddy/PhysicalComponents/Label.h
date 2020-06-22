
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

	$Id: Label.h,v 1.4 2002/01/11 14:35:03 tksuoran Exp $
*/


#ifndef TEDDY__PHYSICAL_COMPONENTS__LABEL__H
#define TEDDY__PHYSICAL_COMPONENTS__LABEL__H


#include "Teddy/PhysicalComponents/Area.h"


namespace Teddy              {
namespace PhysicalComponents {


class LayoutConstraint;


//!  Simple text label
class Label : public Area {
public:
	Label( const char *label );

	//  Area interface
	virtual void  drawSelf();
	void          setText( const char *text );
	const char   *getText();

protected:
	const char *text;
};


};  //  namespace PhysicalComponents
};  //  namespace Teddy


#endif  //  TEDDY__PHYSICAL_COMPONENTS__LABEL__H

