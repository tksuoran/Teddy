
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


#include "Teddy/PhysicalComponents/GradientFill.h"
#include "Teddy/Graphics/View.h"


namespace Teddy              {
namespace PhysicalComponents {


//!  Default constructor
GradientFill::GradientFill( const Color &left_top, const Color &right_top, const Color &right_bottom, const Color &left_bottom ):Fill(){
	//  Assign colors
	this->left_top     = left_top;
	this->right_top    = right_top;
	this->right_bottom = right_bottom;
	this->left_bottom  = left_bottom;
}


//!  Rendering overlay window
void GradientFill::drawSelf(){
#	if defined( USE_TINY_GL )
	return;
#	endif

	//	FIX add glPolygonMode();

	view->setPolygonMode( GL_FILL );
	view->enable        ( View::BLEND );
	view->disable       ( View::TEXTURE_2D );
	view->setBlendFunc  ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	view->setShadeModel ( GL_SMOOTH );

	beginQuads();
	color( left_top     ); drawVertex(    0.0f,    0.0f );
	color( right_top    ); drawVertex( size[0],    0.0f );
	color( right_bottom ); drawVertex( size[0], size[1] );
	color( left_bottom  ); drawVertex(    0.0f, size[1] );
	end();
}


};  //  namespace PhysicalComponents
};  //  namespace Teddy

