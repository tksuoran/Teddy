
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


#include "Teddy/TeddyConfig.h"
#include "Teddy/Graphics/Device.h"
#include "Teddy/Graphics/Font.h"
#include "Teddy/Graphics/PsRenderer.h"
#include "Teddy/Graphics/Texture.h"
#include "Teddy/Graphics/View.h"
#include "Teddy/Maths/Matrix.h"
#include "Teddy/PhysicalComponents/WindowManager.h"
#include "Teddy/PhysicalComponents/Style.h"
#include "Teddy/SysSupport/Messages.h"
#include "Teddy/SysSupport/StdSDL.h"
#include "Teddy/SysSupport/StdIO.h"
#ifndef SWIG
#include <cstdlib>
#endif
using namespace Teddy::Maths;
using namespace Teddy::PhysicalComponents;
using namespace Teddy::SysSupport;


namespace Teddy    {
namespace Graphics {




//!  Enter 3D vertex with texture coordinates
void View::vertex( const Vector &v, const Vector2 &t ) const {
	texture( t );
	vertex ( v );
}


//!  Enter 2D vertex with texture coordinates
void View::vertex( const Vector2 &v, const Vector2 &t ) const {
	msg( M_GL, "vertex( %f, %f   %f, %f )", v[0],v[1],t[0],t[1] );
    texture( t );
    vertex( v );
}


//!  Area Graphics interface - Draw filled rectangle - changed polygonmode..
void View::drawFillRect( const float x1, const float y1, const float x2, const float y2 ){
	msg( M_GL, "View::drawFillRect( %f, %f, %f, %f )", x1,y1,x2,y2 );
	setPolygonMode( GL_FILL );
	beginQuads();
	vertex( x1, y1 );
	vertex( x2, y1 );
	vertex( x2, y2 );
	vertex( x1, y2 );
	end();
}


void View::blit( const Vector2 &pos, Texture *t ){
    Vector2 size = Vector2( t->getSize() );
    Vector2 max  = pos + size - Vector2( 1, 1 );
    //int x2 = x1 + t->getWidth () -1 ;
	//int y2 = y1 + t->getHeight() -1 ;

	color         ( C_WHITE    );
	setTexture    ( t          );
	setPolygonMode( GL_FILL    );
	setBlendFunc  ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	enable        ( TEXTURE_2D );
	enable        ( BLEND      );

    beginQuads();
	vertex( pos                       , Vector2(0,0) );
	vertex( Vector2( max[0], pos[1] ) , Vector2(1,0) );
	vertex( max                       , Vector2(1,1) );
	vertex( Vector2( pos[0], max[1] ) , Vector2(0,1) );
	end();
}


//!  Area Graphics interface - Draw non-filled rectangle - changed polygonmode..
void View::drawRect( const float x1, const float y1, const float x2, const float y2 ){
	setPolygonMode( GL_LINE );
	beginQuads();
	vertex( x1     , y1+1.0f );
	vertex( x2-1.0f, y1+1.0f );
	vertex( x2-1.0f, y2      );
	vertex( x1     , y2      );
	end();
}


//!  Area Graphics interface - Draw twocolor rectangle
void View::drawBiColRect( const float x1, const float y1, const float x2, const float y2, const Color &top_left, const Color &bottom_right ){
	color( top_left );
	beginLineStrip();
	vertex( x1, y2      );
	vertex( x1, y1+1.0f );
	vertex( x2, y1+1.0f );
	end();
	color( bottom_right );
	beginLineStrip();
	vertex( x2-1.0f, y1+1.0f );
	vertex( x2-1.0f, y2      );
	vertex( x1,      y2      );
	end();
}


//!  Area Graphics interface - Draw string - no formatting
void View::drawString( const Vector2 &pos, const char *str, Font *font ){
	font->drawString( pos, str, this );
}


};  //  namespace Graphics
};  //  namespace Teddy

