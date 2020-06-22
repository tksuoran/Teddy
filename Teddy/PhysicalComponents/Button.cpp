
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


#include "Teddy/Graphics/Font.h"
#include "Teddy/Graphics/View.h"
#include "Teddy/PhysicalComponents/Button.h"
#include "Teddy/PhysicalComponents/Frame.h"
#include "Teddy/PhysicalComponents/GradientFill.h"
#include "Teddy/PhysicalComponents/Style.h"
#include "Teddy/SysSupport/Messages.h"
#include <cstring>
using namespace Teddy::SysSupport;


namespace Teddy              {
namespace PhysicalComponents {


//! Constructor
Button::Button(  std::string labe ):
Area (labe ),
label(labe )
{
    fill_base_pixels[0] = name.size() * style->button_font->getWidth() + style->padding[0] * 2;
    fill_base_pixels[1] = style->glyph_size[1] + style->padding[1]*2;;

/*	this->insert(
		new GradientFill(
			Color( 0.8f, 0.8f, 0.8f, 0.5f ),
			Color( 0.7f, 0.7f, 0.7f, 0.5f ),
			Color( 0.5f, 0.5f, 0.5f, 0.5f ),
			Color( 0.6f, 0.6f, 0.6f, 0.5f )
		)
	);*/

	state	         = up;
	drawing_ordering = post_self;
	event_ordering   = post_self;
}


//!  Area interface
/*virtual*/ void Button::drawSelf(){
/*	drawBiColRect( 1.0f,  1.0f,  size[0]-1.0f, size[1]-1.0f, style->hilight_color, style->shadow_color  );
	style->shadow_color.glApply();
	drawRect( 0.0f,  0.0f,  size[0]     , size[1] );

	style->text_color.glApply();*/
	drawString( style->padding, label.c_str(), style->button_font );
}


};  //  namespace PhysicalComponents
};  //  namespace Teddy

