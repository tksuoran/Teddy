
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

	$Id: Tick.h,v 1.1 2002/01/22 19:30:05 tksuoran Exp $
*/


#ifndef TEDDY__MIX_IN__TICK_H
#define TEDDY__MIX_IN__TICK_H


namespace Teddy {
namespace MixIn {


//!  Mutex object mix in
class Tick {
public:
	Tick();
	virtual ~Tick();

	virtual void tick();
};


};  //  namespace MixIn
};  //  namespace Teddy


#endif  //  TEDDY__MIX_IN__TICK_H

