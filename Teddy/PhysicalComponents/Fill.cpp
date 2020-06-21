
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

	$Id: Fill.cpp,v 1.4 2002/01/11 14:35:03 tksuoran Exp $
*/


#include "Teddy/PhysicalComponents/Fill.h"


namespace Teddy              {
namespace PhysicalComponents {


//!  Default constructor
Fill::Fill()
:
Area()
{
    fill_free_size_relative = Vector2( 1.0f, 1.0f );
}


//!  Destructor
/*virtual*/ Fill::~Fill(){
	//	FIX
}


//!  Drawing code
void Fill::drawSelf(){
/*	This code would be for FlatFill

	int width;
	int height;

	getSize( &width, &height );
	glEnable( GL_BLEND );
	glShadeModel( GL_SMOOTH );
	beginQuads();
	color( &color.rgba );
	vertex2i( 0, 0 );
	vertex2i( width, 0 );
	vertex2i( width, height );
	vertex2i( 0, height );
	end();*/
}


};  //  namespace PhysicalComponents
};  //  namespace Teddy

