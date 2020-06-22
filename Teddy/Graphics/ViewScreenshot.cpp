
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

	$Id: View.cpp,v 1.8 2002/02/16 16:38:11 tksuoran Exp $
*/


#include "Teddy/TeddyConfig.h"
#include "Teddy/Graphics/Device.h"
#include "Teddy/Graphics/View.h"
#include "Teddy/SysSupport/StdSDL.h"
#include "Teddy/SysSupport/StdIO.h"

#ifndef SWIG
#include <cstdlib>
#ifdef HAVE_LIB_PNG
# include <png.h>
# if defined (_MSC_VER)
#  pragma comment (lib, "libpng1.lib" )
# endif
#endif
#endif

using namespace Teddy::Maths;
using namespace Teddy::PhysicalComponents;
using namespace Teddy::SysSupport;


namespace Teddy    {
namespace Graphics {


#ifdef HAVE_LIB_PNG


/*static*/ FILE *View::fp;


/*static*/ void View::pngUserWriteData( png_structp png_ptr, png_bytep data, png_size_t length ){
	fwrite( data, length, 1, fp );
}


/*static*/ void View::pngUserFlushData( png_structp png_ptr ){
	fflush( fp );
}


#endif



bool View::pngScreenshot( const char *const filename ){
#if defined( HAVE_LIB_PNG ) && !defined( USE_TINY_GL )
	unsigned char  *data         = NULL;
	png_structp     png_ptr      = NULL;
	png_infop       info_ptr     = NULL;
	png_byte      **row_pointers = NULL;
    bool            written      = false;

    int width  = size[0];
    int height = size[1];

	fp           = fopen( filename, "wb" );
	data         = (unsigned char*)malloc ( width  * height * 3 );
	row_pointers = (png_byte**)    malloc ( height * sizeof(png_byte*) );
	png_ptr      = png_create_write_struct( PNG_LIBPNG_VER_STRING, 0, 0, 0 );
	info_ptr     = png_create_info_struct ( png_ptr );
	if( (fp!=NULL) && (data!=NULL) && (row_pointers!=NULL) && (row_pointers!=NULL) && (png_ptr!=NULL) && (info_ptr!=NULL) ){
		for( int i=0; i<height; i++ ){
			row_pointers[i] = data + (height - i - 1) * 3 * width;
		}
		glReadPixels    ( 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data );
		png_set_write_fn( png_ptr, 0, View::pngUserWriteData, View::pngUserFlushData );
		png_set_IHDR    ( png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT );
		png_write_info  ( png_ptr, info_ptr     );
		png_write_image ( png_ptr, row_pointers );
		png_write_end   ( png_ptr, info_ptr     );
        written = true;
	}
	if( png_ptr      != NULL ){ png_destroy_write_struct( &png_ptr, &info_ptr ); }
	if( row_pointers != NULL ){ free                    ( row_pointers );        }
	if( data         != NULL ){ free                    ( data );                }
	if( fp           != NULL ){ fclose                  ( fp );                  }
	return written;
#else
	return false;
#endif /* png, !tinygl */
}


#ifdef BMP_SCREENSHOT
#include "Teddy/SysSupport/StdSDL.h"


bool bmpScreenshot( char *filename, int width, int height ){
	unsigned char *data;
    
	data = malloc( width * height * 3 );
	glReadPixels( 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data );

  /* this code is shamelessly stolen from Ray but, Kelm I believe he
     put it in the public domain */
	{
		SDL_Surface *temp;
		int i;

		temp = SDL_CreateRGBSurface( SDL_SWSURFACE, width, height, 24,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
									0x000000FF, 0x0000FF00, 0x00FF0000, 0
#else
									0x00FF0000, 0x0000FF00, 0x000000FF, 0
#endif
								   );

		if( temp == NULL ){
			return false;
		}

		for (i = 0; i < height; i++){
			memcpy(((char *) temp->pixels) + temp->pitch * i, data + 3 * width * (height - i - 1), width * 3);
		}

		SDL_SaveBMP( temp, filename );
		SDL_FreeSurface( temp );
	}

	free( data );
	return 0;
}

#endif


};  //  namespace Graphics
};  //  namespace Teddy

