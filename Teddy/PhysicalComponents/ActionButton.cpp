
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

	$Id: ActionButton.cpp,v 1.5 2002/03/12 10:46:06 tksuoran Exp $
*/


#include "Teddy/PhysicalComponents/ActionButton.h"
#include "Teddy/PhysicalComponents/Style.h"
#include "Teddy/PhysicalComponents/WindowManager.h"
#include "Teddy/Graphics/Font.h"
#include "Teddy/Graphics/View.h"
#include "Teddy/SysSupport/Messages.h"
#include <cstring>
using namespace Teddy::Graphics;
using namespace Teddy::SysSupport;


namespace Teddy              {
namespace PhysicalComponents {


//!  Constructor
ActionButton::ActionButton( std::string name, Teddy::Signals::Functor0<bool> *f, const int type )
:
EventListener(),
Area         (name),
label        (name)
{
    fill_base_pixels[0]    = 4 + name.size() * style->button_font->getWidth() + style->border[0] * 2; 
	fill_base_pixels[1]    = 4 + style->button_font->getHeight() + style->border[1] * 2;
	drawing_ordering       = pre_self;
	event_ordering         = post_self;
	this->v_type           = type;
	this->e_type           = 0;
	this->d_type           = 0;
	this->v_holder.functor = f;
	this->d_data           = NULL;
}


ActionButton::ActionButton( std::string name, Teddy::Signals::Functor1<bool,const Event &> *f, const int type )
:
EventListener(),
Area (name),
label(name)
{
    fill_base_pixels[0]    = 4 + name.size() * style->button_font->getWidth() + style->border[0] * 2; 
	fill_base_pixels[1]    = 4 + style->button_font->getHeight() + style->border[1] * 2;
	drawing_ordering       = pre_self;
	event_ordering         = post_self;
	this->v_type           = 0;
	this->e_type           = type;
	this->d_type           = 0;
	this->e_holder.functor = f;
	this->d_data           = NULL;
}


ActionButton::ActionButton( std::string name, Teddy::Signals::Functor1<bool,void *> *f, void *data, const int type )
:
EventListener(),
Area (name),
label(name)
{
    fill_base_pixels[0]    = 4 + name.size() * style->button_font->getWidth() + style->border[0] * 2; 
	fill_base_pixels[1]    = 4 + style->button_font->getHeight() + style->border[1] * 2;
	drawing_ordering       = pre_self;
	event_ordering         = post_self;
	this->v_type           = 0;
	this->e_type           = 0;
	this->d_type           = type;
	this->d_holder.functor = f;
	this->d_data           = data;
}


/*virtual*/ void ActionButton::event( const Event &e ){
	if( v_type == e.type ){
		v_holder();
	}
	if( e_type == e.type ){
		e_holder( e );
	}
	if( d_type == e.type ){
		d_holder( d_data );
	}
}

/*virtual*/ bool ActionButton::doesEvent( int type ){
	return
		( v_type == type ) ||
		( e_type == type ) ||
		( d_type == type );
}


//!  Destructor
ActionButton::~ActionButton(){
}


//!  Drawing code
void ActionButton::drawSelf(){
	view->disable( View::TEXTURE_2D );

#	if !defined( USE_TINY_GL )
	const float lwf = 160.0f / 255.0f;
	const float lwh = 190.0f / 255.0f;
	Color( lwf,lwf,lwf,1.0f ).glApply();
	drawFillRect( 2, 2, size[0]-2, size[1]-2 );
	drawBiColRect( 1,  1, size[0]-1, size[1]-1, Color(lwh,lwh,lwh,1.0f), style->shadow_color );
	drawBiColRect( 0,  0, size[0]  , size[1]  , style->shadow_color,     style->shadow_color );
#	endif

	view->setPolygonMode( GL_FILL );
	view->enable( View::BLEND );
	view->enable( View::TEXTURE_2D );
	view->setBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	style->text_color.glApply();
	drawString( style->border + Vector2(2.0f,2.0f), label.c_str(), style->button_font );
}


};  //  namespace PhysicalComponents
};  //  namespace Teddy

