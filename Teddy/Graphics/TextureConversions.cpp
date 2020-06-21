
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

	$Id: TextureConversions.cpp,v 1.4 2002/01/11 14:34:59 tksuoran Exp $
*/


#include "Teddy/TeddyConfig.h"
#include "Teddy/Graphics/Device.h"
#include "Teddy/Graphics/Texture.h"


namespace Teddy    {
namespace Graphics {


//!  Convert Texture working image data to alpha-only format
void Texture::convert_to_a(){
	switch( work_data_pixel_format ){
	case GL_RGB:  convert_rgb_to_a (); break;
	case GL_RGBA: convert_rgba_to_a(); break;
	default: break;
	}

	work_data_pixel_format = GL_ALPHA;
}


//!  Convert Texture working image data to red-green-blue format
void Texture::convert_to_rgb(){
	switch( work_data_pixel_format ){
	case GL_ALPHA: convert_a_to_rgb   (); break;
	case GL_RGBA:  convert_rgba_to_rgb(); break;
	default: break;
	}

	work_data_pixel_format = GL_RGB;
}

/*
void Texture::convert_to_rgba(){
	switch( work_format ){
	case FORMAT_A:   convert_a_to_rgb   (); 
	case FORMAT_RGB: convert_rgb_to_rgba(); break;
	default: break;
	}

	work_format = FORMAT_RGBA;
}*/


//!  Convert Texture working image data from alpha format to red-green-blue format (greyscale)
void Texture::convert_a_to_rgb(){
	unsigned char *in  = work_data;
	unsigned char *out = new unsigned char[size[0]*size[1]];
	int            x   = 0;
	int            y   = 0;
	int            a   = 0;

	for( y=0; y<size[1]; y++ ){
		for( x=0; x<size[0]; x++ ){
			a = in[y*size[0]+x];
			out[y*size[0]*3+x*3+0] = a;
			out[y*size[0]*3+x*3+1] = a;
			out[y*size[0]*3+x*3+2] = a;
		}
	}

	setWorkData( out );
}


//!  Convert Texture working image data from red-green-blue format to alpha format; alpha == red
void Texture::convert_rgb_to_a(){
	unsigned char *in  = work_data;
	unsigned char *out = new unsigned char[size[0]*size[1]];
	int            x   = 0;
	int            y   = 0;
	int            r   = 0;
	int            g   = 0;
	int            b   = 0;
    int            a   = 0;

	for( y=0; y<size[1]; y++ ){
		for( x=0; x<size[0]; x++ ){
			r = in[y*size[0]*3+x*3+0];
			g = in[y*size[0]*3+x*3+1];
			b = in[y*size[0]*3+x*3+2];
			a = r;
			out[y*size[0]+x] = a;
		}
	}

	setWorkData( out );
}


//!  Convert Texture working image data from red-green-blue-alpha to alpha format
void Texture::convert_rgba_to_a(){
	unsigned char *in  = work_data;
	unsigned char *out = new unsigned char[size[0]*size[1]];
	int            x   = 0;
	int            y   = 0;
	int            r   = 0;
	int            g   = 0;
	int            b   = 0;
	int            a   = 0;

	for( y=0; y<size[1]; y++ ){
        for( x=0; x<size[0]; x++ ){
			r = in[y*size[0]*4+x*4+0];
			g = in[y*size[0]*4+x*4+1];
			b = in[y*size[0]*4+x*4+2];
			a = in[y*size[0]*4+x*4+2];
			out[y*size[0]+x] = a;
		}
	}

	setWorkData( out );
}


//!  Convert Texture working image data from red-green-blue-alpha to red-green-blue format
void Texture::convert_rgba_to_rgb(){
	unsigned char *in  = work_data;
	unsigned char *out = new unsigned char[int(size[0]*size[1])*3];
	int            x   = 0;
	int            y   = 0;
	int            r   = 0;
	int            g   = 0;
	int            b   = 0;
	int            a   = 0;

	for( y=0; y<size[1]; y++ ){
		for( x=0; x<size[0]; x++ ){
			r = in[y*size[0]*4+x*4+0];
			g = in[y*size[0]*4+x*4+1];
			b = in[y*size[0]*4+x*4+2];
			a = in[y*size[0]*4+x*4+2];
			out[y*size[0]*3+x*3+0] = r;
			out[y*size[0]*3+x*3+1] = g;
			out[y*size[0]*3+x*3+2] = b;
		}
	}

	setWorkData( out );
}


};  //  namespace Graphics
};  //  namespace Teddy

