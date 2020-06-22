
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
#include <cmath>
#include "Teddy/Graphics/Font.h"
#include "Teddy/Graphics/Texture.h"
#include "Teddy/Graphics/View.h"
#include "Teddy/SysSupport/EndianIn.h"
#include "Teddy/SysSupport/Messages.h"
using namespace Teddy::Graphics;
using namespace Teddy::Maths;
using namespace Teddy::PhysicalComponents;
using namespace Teddy::SysSupport;


namespace Teddy    {
namespace Graphics {


/*static*/       Font  Font::dummy_font;
/*static*/       Font *Font::default_font  = &Font::dummy_font;
/*static*/ const int   Font::MODE_NORMAL   =  0;
/*static*/ const int   Font::MODE_NO_BLEND =  1;

	
	// Font *Font::default_font = NULL;


static float DIV_256 = 1.0f/256.0f;


//!  Dummy font constructor for font which is used for default font while none is loaded
Font::Font(){
    int i;
    for( i=0; i<256; i++ ){
        tx[i] = Vector2( 255-8, 0 );
    }
    for( i=0; i<4; i++ ){
        tsize[i] = Vector2( 0.0f, 0.0f );
        psize[i] = Vector2( 0.0f, 0.0f );
    }
    pos = Vector2( 0.0f, 0.0f );
    texture = NULL;
	cw  = 0;
	ch  = 0;
	tw  = 0.0f;
	th  = 0.0f;
}

/*!
	\brief Font constructor
	\param fname Name of the datafile containing font definition as raw 256x256 8bit alpha values
*/
Font::Font( const char *fname, int mode ):mode(mode){
	unsigned char array[5][21] = {
//		 0         1         2
//		 012345678901234567890
		"!\"#$%&'()*+,-./01234", // 0 
		"56789:;<=>?@ABCDEFGH",  // 1
		"IJKLMNOPQRSTUVWXYZ[\\", // 2
		"]^_`abcdefghijklmnop",  // 3
		"qrstuvwxyz{|}~      "   // 4
	};
	int row;
	int col;
	int i;

	cw  =  8;
	ch  =  8;
	tw  = (cw) *DIV_256;
	th  = (ch) *DIV_256;

    for( i=0; i<256; i++ ){
        tx[i] = Vector2( 255-8, 0 );
	}
	for( row=0; row<9; row++ ){
		for( col=0; col<20; col++ ){
			printf( "%c", array[row][col] );
			tx[ array[row][col] ] = Vector2( (1+col*cw)*DIV_256, (row*ch)*DIV_256 );
		}
		printf( "\n" );
		fflush( stdout );
    }

    IntVector2     size(256,256);
	EndianIn      *s      = NULL;
	unsigned char *filler = NULL;
	unsigned char *data   = NULL;

	texture = new Texture( "font texture" );
	texture->setEnv   ( Texture::ENV_MODULATE );
	texture->setWrap  ( Texture::WRAP_REPEAT, Texture::WRAP_REPEAT );
	texture->setFilter( Texture::FILTER_NEAREST );

#	if defined( USE_TINY_GL )
	mode = MODE_NO_BLEND;
#	endif

	try{
		s = new EndianIn( fname );
		s->set_bigendian();
		if( mode==MODE_NORMAL ){
			filler = data = new unsigned char[256*256];
			for(int i=0; i<256*256;i++){
				*filler++ = s->read_byte();
			}
			texture->putData( data, size, Texture::FORMAT_ALPHA, Texture::TX_BLIT_NO_SCALE );
		}else{
			filler = data = new unsigned char[256*256*3];
			for(int i=0; i<256*256;i++){
				unsigned char in = s->read_byte();
				*filler++ = in;
				*filler++ = in;
				*filler++ = in;
				//*filler++ = in;
			}		
			texture->putData( data, size, Texture::FORMAT_RGB, Texture::TX_BLIT_NO_SCALE );
		}
	}catch( ... ){
		msg( M_INIT, "Could not find font file %s", fname );
	}

	texture->doBind();
    s->close();
	delete[] data;
    delete s;

#	if defined( USE_TINY_GL )
    tsize[0] = Vector2(  0.0f, 0.0f );
    tsize[1] = Vector2(  tw,   0.0f );
    tsize[2] = Vector2(  tw,   th-DIV_256 );
    tsize[3] = Vector2(  0.0f, th-DIV_256 );
    psize[0] = Vector2(  0,  1 );
    psize[1] = Vector2( cw,  1 );
    psize[2] = Vector2( cw, ch );
    psize[3] = Vector2(  0, ch );
#	else
    tsize[0] = Vector2(  0.0f, 0.0f );
    tsize[1] = Vector2(  tw,   0.0f );
    tsize[2] = Vector2(  tw,   th );
    tsize[3] = Vector2(  0.0f, th );
    psize[0] = Vector2(  0,  0 );
    psize[1] = Vector2( cw,  0 );
    psize[2] = Vector2( cw, ch );
    psize[3] = Vector2(  0, ch );
#	endif
}


/*!
	\brief Render string with this font
	\param v View to which to draw
	\param str C string to be drawn
	\param xp X coordinate for string start position
	\param yp Y coordinate for string start position
*/
void Font::drawString( const Vector2 &pos, const char *str, View *v ){
	const char *ptr = str;
	v->setTexture      ( texture      );
	v->enable          ( View::TEXTURE_2D   );
	v->setPolygonMode  ( GL_FILL      );
	if( mode==MODE_NORMAL ){
		v->setBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
		v->enable      ( View::BLEND  );
	}else{
		v->disable     ( View::BLEND  );
		v->color       ( Color::WHITE );
	}
    v->beginQuads();
    Vector2 cursor = pos;
    while( *ptr != '\0' ){
        v->vertex( cursor + psize[0], tx[*ptr] + tsize[0] );
        v->vertex( cursor + psize[1], tx[*ptr] + tsize[1] );
        v->vertex( cursor + psize[2], tx[*ptr] + tsize[2] );
        v->vertex( cursor + psize[3], tx[*ptr] + tsize[3] );
        cursor[0] += psize[1][0];
		ptr++;
	}
	v->end();
}


/*!
	\brief Return font width in pixels
	\return The font width in pixels
*/
int Font::getWidth(){
	return cw;
}


/*!
	\brief Return font height in pixels
	\return The font height in pixels
*/
int Font::getHeight(){
	return ch;
}


};  //  namespace Graphics
};  //  namespace Teddy

