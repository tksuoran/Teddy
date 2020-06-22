
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


#include "Teddy/PhysicalComponents/Label.h"
#include "Teddy/PhysicalComponents/Style.h"
#include "Teddy/Graphics/Font.h"
#include "Teddy/Graphics/View.h"
#include <cstring>


namespace Teddy              {
namespace PhysicalComponents {


//!  Constructor
Label::Label( const char *label ):Area(label),text(label){
    fill_base_pixels[0] = name.size() * style->button_font->getWidth() + style->padding[0] * 2;
    fill_base_pixels[1] = style->glyph_size[1] + style->padding[1]*2;;
	drawing_ordering = post_self;
}


//!  Area interface
/*virtual*/ void Label::drawSelf(){
	view ->enable      ( View::BLEND );
	view ->enable      ( View::TEXTURE_2D );
	view ->setBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	style->hilight_color.glApply();
	drawString         ( style->padding, text, style->button_font );
	view ->disable     ( View::TEXTURE_2D );
}


void Label::setText( const char *text ){
	this->text = text;
}


const char *Label::getText(){
	return this->text;
}


};  //  namespace PhysicalComponents
};  //  namespace Teddy

