
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

	$Id: Style.h,v 1.4 2002/01/11 14:35:03 tksuoran Exp $
*/


#ifndef TEDDY__PHYSICAL_COMPONENTS__STYLE__H
#define TEDDY__PHYSICAL_COMPONENTS__STYLE__H


#include "Teddy/Graphics/Color.h"
#include "Teddy/Maths/Vector2.h"
namespace Teddy {
    namespace Graphics { class Font; }
};
using namespace Teddy::Graphics;


namespace Teddy              {
namespace PhysicalComponents {


class Frame;
class Fill;


/*!
	\brief   Style definition for physical components

	Style defines physical appearence for physical components.
	Each area has associated style. Style defines colorscheme,
	frame, fill, size, font etc. Physical components should not
	store these properties themselves in any case; instead they
	should consider expanding Style.

	Currently Style does not implement much anything..

	Style might actually use tags?
*/
class Style {
public:
	Style();
	virtual ~Style();

	static Style *default_style;

	Font    *large_font;
	Font    *medium_font;
	Font    *small_font;
	Font    *window_title_font;
	Font    *group_title_font;
	Font    *monospace_font;
	Font    *basic_font;
	Font    *button_font;
	Frame   *frame;
    Fill    *background;
    Teddy::Maths::TVector2<float>  border;
    Teddy::Maths::TVector2<float>  padding;
	Color    hilight_color;
	Color    shadow_color;
	Color    fill_color;
	Color    background_color;
	Color    text_color;
	Color    border_color;
	Color    selection_background_color;
	Color    selection_foreground_color;
	Color    border_color_fill;
	Color    border_color_hilight;
	Color    border_color_shadow;
    Teddy::Maths::TVector2<float>  glyph_size;
};


};  //  namespace PhysicalComponents
};  //  namespace Teddy


#endif  //  TEDDY__PHYSICAL_COMPONENTS__STYLE__H

