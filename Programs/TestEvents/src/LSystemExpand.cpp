
/*
	TEDDY - General graphics application library
	Copyright (C) 1999, 2000, 2001	Timo Suoranta
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


#include "LSystem.h"

#include "Teddy/Models/Vertex.h"
#include "Teddy/Models/Line.h"
#include "Teddy/SysSupport/StdString.h"
#include "Teddy/SysSupport/Messages.h"
#include <cstring>
using namespace Teddy::Models;
using namespace Teddy::SysSupport;


void LSystem::expand( int max_depth ){
	string new_data;

	for( int depth=0; depth<max_depth; depth++ ){
		new_data.erase();
		for( cursor=0; cursor<cur_data.size(); cursor++ ){
			unsigned char c = cur_data[cursor];
			new_data.append( rules[c] );
		}
		cur_data = new_data;
	}
}


