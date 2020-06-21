
/*
	TSGL - Teddy Space Game Library
	Copyright (C) 2002 Timo Suoranta
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


#include "ComputerController.h"


ComputerController::ComputerController( Ship *ship, Root *root )
:
ShipController( ship, root )
{
}


//!  Apply Plaeyr Controls
/*virtual*/ void ComputerController::tick(){
	//  switch( attitude_state )
	//  case AI_AVOID_COLLISION:
	//  case AI_GO_TO_POINT:
	//  case AI_AIM_POINT:

	//  switch( position_state )
	//  case AI_AVOID_COLLISION:
	//  case AI_GO_TO_POINT:
	//  case AI_AIM_POINT:
	trackTarget();
	ShipController::tick();
}

