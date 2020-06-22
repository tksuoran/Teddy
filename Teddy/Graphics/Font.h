
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


#ifndef TEDDY__GRAPHICS__FONT_H
#define TEDDY__GRAPHICS__FONT_H


#include "Teddy/Maths/Vector2.h"


namespace Teddy    {
namespace Graphics {


class Texture;
class View;


/*!
	\brief   Glyph rendering with OpenGL textured quads
	\todo    Freetype
	\todo    Variable width font.

	This class implements glyph storing and rendering code
	(but it is not Renderable).

	Implementation is very primitive at the moment. Later,
	FreeType library could be intergrated here.
*/
class Font {
public:
	Font( const char *fname, const int mode=0 ); 
	Font();  // fummy font

	void drawString( const Teddy::Maths::Vector2 &pos, const char *str, View *v  );
	int  getWidth  ();
	int  getHeight ();

    static Font *default_font;
    static Font  dummy_font;

public:
	static const int MODE_NORMAL;
	static const int MODE_NO_BLEND;

private:
    Texture               *texture;     //!<  Texture object
    Teddy::Maths::Vector2  tx   [256];  //!<  Texture coordinates, char = index
    Teddy::Maths::Vector2  tsize[4];
    Teddy::Maths::Vector2  psize[4];
    Teddy::Maths::Vector2  pos;
	int      mode;
	int      cw;       //!<  Char width in pixels
	int      ch;       //!<  Char height
	float    tw;       //!<  Char width in texture coords
	float    th;       //!<  Char height in texture coords
};


};  //  namespace Graphics
};  //  namespace Teddy


#endif  //  TEDDY__GRAPHICS__FONT_H

