
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

	$Id: Frame.cpp,v 1.4 2002/01/11 14:35:03 tksuoran Exp $
*/


#include "Teddy/Graphics/View.h"
#include "Teddy/PhysicalComponents/Frame.h"
#include "Teddy/PhysicalComponents/ActionButton.h"
#include "Teddy/PhysicalComponents/MenuList.h"
#include "Teddy/PhysicalComponents/Style.h"
#include "Teddy/PhysicalComponents/WindowManager.h"
#include "Teddy/Graphics/Color.h"
using namespace Teddy::Graphics;
using namespace Teddy::Signals;


namespace Teddy              {
namespace PhysicalComponents {


//!  Default constructor
Frame::Frame( const std::string &name )
:
Area( name )
{
    offset_pixels           = Vector2( -2.0f, -2.0f );
    fill_base_pixels        = Vector2(  4.0f,  4.0f );
    fill_free_size_relative = Vector2(  1.0f,  1.0f );
	this->event_ordering = separate_self;
}


//!  Destructor
/*virtual*/ Frame::~Frame(){
	//	FIX
}


//!  Drawing code
void Frame::drawSelf(){
	view->setPolygonMode( GL_FILL );
    view->disable( View::TEXTURE_2D );
	style->shadow_color.glApply();
	drawRect( 0, 0, size[0], size[1] );
	drawBiColRect( 1, 1, size[0]-1, size[1]-1, style->hilight_color, style->shadow_color );
}


};  //  namespace PhysicalComponents
};  //  namespace Teddy

