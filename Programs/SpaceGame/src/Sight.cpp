
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


#include "Teddy/PhysicalComponents/GradientFill.h"
#include "Teddy/PhysicalComponents/Frame.h"
#include "Teddy/Graphics/View.h"
#include "Sight.h"
using namespace Teddy::PhysicalComponents;


//!  Constructor
Sight::Sight():Area("Sight"){
	size = 16;
	float fs = (float)size * 4.0f;

    offset_self_size_relative = Vector2( -0.5f, -0.5f );
    offset_free_size_relative = Vector2(  0.5f,  0.5f );
    fill_base_pixels          = Vector2(    fs,    fs );
}


//!  Destructor
/*virtual*/ Sight::~Sight(){
}



//!  Drawing code
void Sight::drawSelf(){
	view->disable( View::TEXTURE_2D );
	color( C_LIGHT_GREEN );
	beginLines();
	vertex( 0*size, 2*size );
	vertex( 1*size, 2*size );
	vertex( 3*size, 2*size );
	vertex( 4*size, 2*size );
	vertex( 2*size, 0*size );
	vertex( 2*size, 1*size );
	vertex( 2*size, 3*size );
	vertex( 2*size, 4*size );
	end();
	
	color( C_BLACK );
	beginLines();
	vertex( 0*size,   2*size-1 );
	vertex( 1*size,   2*size-1 );
	vertex( 3*size,   2*size-1 );
	vertex( 4*size,   2*size-1 );
	vertex( 0*size,   2*size+1 );
	vertex( 1*size,   2*size+1 );
	vertex( 3*size,   2*size+1 );
	vertex( 4*size,   2*size+1 );
	vertex( 2*size-1, 0*size );
	vertex( 2*size-1, 1*size );
	vertex( 2*size-1, 3*size );
	vertex( 2*size-1, 4*size );
	vertex( 2*size+1, 0*size );
	vertex( 2*size+1, 1*size );
	vertex( 2*size+1, 3*size );
	vertex( 2*size+1, 4*size );
	end();
}

