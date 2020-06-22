
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


#include "Teddy/PhysicalComponents/Area.h"
#include "Teddy/PhysicalComponents/EventListener.h"
#include "Teddy/PhysicalComponents/Projection.h"
#include "Teddy/PhysicalComponents/Style.h"
#include "Teddy/Graphics/View.h"
#include "Teddy/Graphics/Font.h"
#include "Teddy/SysSupport/Messages.h"
#include "Teddy/SysSupport/StdIO.h"
#ifndef SWIG
#include <cassert>
#endif
using namespace Teddy::Graphics;


namespace Teddy              {
namespace PhysicalComponents {


//!  Draw area recursively - draw all areas in layer
/*virtual*/ void Area::draw(){
    dmsg( M_WM, "%s->Area::draw()", this->getName().c_str() );
    dmsg( M_WM, "  %s->rect = %f, %f .. %f, %f", this->getName().c_str(), rect.min[0], rect.min[1], rect.max[0], rect.max[1] );
	if( drawing_ordering == pre_self ){
		drawSelf();
	}

	list<Area*>::iterator a_it = areas.begin();
	while( a_it != areas.end() ){
        Area *a = *a_it;
        const char *name = a->getName().c_str();
        dmsg( M_WM, "%s->Area::draw() calling %s->draw()", this->getName().c_str(), name );
		a->draw();
		a_it++;
	}

	if( drawing_ordering == post_self ){
		drawSelf();
	}
}


//!  Draw area - draw area self component
/*virtual*/ void Area::drawSelf(){
}


View *Area::getView() const {
	return view;
}


void Area::drawVertex( const float x1, const float y1 ){
	view->vertex( x1+rect.min[0], y1+rect.min[1] );
}


//!  Area Graphics interface - Draw non-filled rectangle
void Area::drawRect( const float x1, const float y1, const float x2, const float y2 ){
	view->drawRect( x1+rect.min[0], y1+rect.min[1], x2+rect.min[0], y2+rect.min[1] );
}


//!  Area Graphics interface - Draw filled rectangle
void Area::drawFillRect( const float x1, const float y1, const float x2, const float y2 ){
	const char *name = this->getName().c_str();
	msg( M_GL, "%s->Area::drawFillRect( %f, %f, %f, %f )", name, x1,y1,x2,y2 );
	msg( M_GL, "%s->rect.min = %f, %f", name, rect.min[0], rect.min[1] );
    view->drawFillRect( x1+rect.min[0], y1+rect.min[1], x2+rect.min[0], y2+rect.min[1] );
}


//!  Area Graphics interface - Draw twocolor rectangle
void Area::drawBiColRect( const float x1, const float y1, const float x2, const float y2, const Color &top_left, const Color &bottom_right ){
	view->drawBiColRect( x1+rect.min[0], y1+rect.min[1], x2+rect.min[0], y2+rect.min[1], top_left, bottom_right );
}


//!  Area Graphics interface - Draw string - no formatting
void Area::drawString( const Vector2 &pos, const char *str, Font *font ){
	view->drawString( pos + rect.min, str, font );
}


};  //  namespace PhysicalComponents
};  //  namespace Teddy

