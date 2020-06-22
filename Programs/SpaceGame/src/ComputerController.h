
/*
	TSGL - Teddy Space Game Library
	Copyright (C) 2002 Timo Suoranta
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


#ifndef SPACE_GAME__COMPUTER_SHIP__H
#define SPACE_GAME__COMPUTER_SHIP__H


#include "ShipController.h"


//!  Computer controlled ship
class ComputerController : public ShipController {
public:
	ComputerController( Ship *ship, Root *root );

	//  Computer AI routines do decide controls
	virtual void tick();
};


#endif  //  SPACE_GAME__COMPUTER_SHIP__H

