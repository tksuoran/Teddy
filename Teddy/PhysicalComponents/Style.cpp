
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

	$Id: Style.cpp,v 1.4 2002/01/11 14:35:03 tksuoran Exp $
*/


#include "Teddy/PhysicalComponents/Style.h"
#include "Teddy/Graphics/Color.h"
#include "Teddy/Graphics/Font.h"
#include <cstring>
using namespace Teddy::Maths;
using namespace Teddy::Graphics;


namespace Teddy              {
namespace PhysicalComponents {


/*static*/ Style *Style::default_style = NULL;	// Can't initialize here; there is no OpenGL context yet so there can't be default font. Done in View constructor.


//!  Constructor
Style::Style(){ 
	large_font                 = Font::default_font;
	medium_font                = Font::default_font;
	small_font                 = Font::default_font;
	window_title_font          = Font::default_font;
	group_title_font           = Font::default_font;
	monospace_font             = Font::default_font;
	basic_font                 = Font::default_font;
    button_font                = Font::default_font;
    padding                    = Vector2( 0, 0 );
    border                     = Vector2( 2, 1 );
	hilight_color              = Color::WHITE;
	shadow_color               = Color::BLACK;
	background_color           = Color(0.4f,0.4f,0.4f);
	fill_color                 = Color::DARK_GREEN;
	text_color                 = Color::BLACK; //WHITE;
	border_color               = Color::YELLOW;//(0.1f,0.4f,0.5f);
	border_color_fill          = Color::YELLOW;
	border_color_hilight       = Color::LIGHT_YELLOW;
	border_color_shadow        = Color::DARK_YELLOW;
	selection_background_color = Color::RED;
	selection_foreground_color = Color::WHITE;
	glyph_size                 = Vector2( 10, 10 );
};


//!  Destructor
/*virtual*/ Style::~Style(){
}


};  //  namespace PhysicalComponents
};  //  namespace Teddy

