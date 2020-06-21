
/*
	TEDDY - General graphics application library
	Copyright (C) 1999, 2000, 2001	Timo Suoranta
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

	$Id: Tree.h,v 1.2 2002/03/12 10:44:29 tksuoran Exp $
*/


#ifndef TEST_EVENTS__TREE__H
#define TEST_EVENTS__TREE__H


#include "Teddy/Models/Model.h"
#include "Teddy/Application/BaseSimulationTimer.h"

class Tree : public Teddy::Models::Model {
public:
	Tree( Teddy::Application::BaseSimulationTimer *st, int slices, int stacks, int cones, float height, float radius, float rad_add );
};


#endif  //  TEST_EVENTS__TREE__H

