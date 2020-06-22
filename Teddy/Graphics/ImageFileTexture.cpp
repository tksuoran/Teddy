
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
#include "Teddy/Maths/Vector2.h"
#include "Teddy/Graphics/convgltex.h"
#include "Teddy/Graphics/ImageFileTexture.h"
#include "Teddy/Graphics/Device.h"
#include "Teddy/Graphics/View.h"
#include "Teddy/SysSupport/Messages.h"
using namespace Teddy::Maths;
using namespace Teddy::SysSupport;


namespace Teddy    {
namespace Graphics {


#ifdef HAVE_LIB_SDL_IMAGE
# include "SDL_image.h"
# if defined( _MSC_VER )
#  if defined( _DEBUG ) 
#   pragma comment (lib, "SDL_imageD.lib")
#  else
#   pragma comment (lib, "SDL_image.lib")
#  endif
# endif
#endif


static Uint32 getpixel( SDL_Surface *surface, int x, int y );


/*static*/ const unsigned long ImageFileTexture::TEXTURE_NO_SCALE   = 1;
/*static*/ const unsigned long ImageFileTexture::TEXTURE_MODE_COLOR = 1;
/*static*/ const unsigned long ImageFileTexture::TEXTURE_MODE_ALPHA = 2;


//!  Constructor from file
ImageFileTexture::ImageFileTexture( const std::string &fname, int mode, int flags ):Texture( fname){
#ifdef HAVE_LIB_SDL_IMAGE
	View::check();
	if( fname.length() > 0 ){
		SDL_Surface *sdl_surface = load_gl_texture( fname.c_str() );  // IMG_Load( fname );
		if( sdl_surface != NULL ){
			copySdlSurface( sdl_surface, mode, flags );
//			SDL_FreeSurface( sdl_surface );
			this->is_good = true;
		}else{
			is_bad = true;
			emsg( M_MAT, "Could not load texture file %s", fname.c_str() );
		}
	}else{
			is_bad = true;
		emsg( M_MAT, "Bad empty filename" );
	}
#else
	is_bad = true;
	emsg( M_MAT, "ImageFileTexture requires SDL_image, which was not available" );
#endif
}


//!  Copy SDL_Surface to texture
void ImageFileTexture::copySdlSurface( SDL_Surface *surface, int mode, int flags ){
	View::check();
    size = Vector2( surface->w, surface->h );
	int format   = 0;

	switch( surface->format->BitsPerPixel ){
	case  8: break;
	case 16: break;
	case 24: format = FORMAT_RGB;  break;
	case 32: format = FORMAT_RGBA; break;
	default: break;
	}

	setWrap  ( WRAP_REPEAT, WRAP_REPEAT );
	View::check();
//	setFilter( FILTER_LINEAR );
//	setFilter( FILTER_NEAREST );
	setFilter( FILTER_NEAREST_MIPMAP_LINEAR );
	View::check();
	setEnv   ( ENV_MODULATE );
	View::check();
	putData( (unsigned char*)surface->pixels, size, format, 0 );
//	putData( (unsigned char*)surface->pixels, width, height, format, TX_BLIT_NO_SCALE );
	View::check();
}


};  //  namespace Materials
};  //  namespace Teddy

