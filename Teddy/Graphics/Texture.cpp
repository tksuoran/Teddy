
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

	$Id: Texture.cpp,v 1.5 2002/01/11 14:34:59 tksuoran Exp $
*/


#include "Teddy/TeddyConfig.h"
#include "Teddy/Graphics/Texture.h"
#include "Teddy/Graphics/View.h"
#include "Teddy/Graphics/glu_mipmap.h"
#include "Teddy/SysSupport/Messages.h"
#include <cstdlib>
using namespace Teddy::Maths;
using namespace Teddy::SysSupport;


namespace Teddy    {
namespace Graphics {


/*static*/ const unsigned long Texture::TX_RESERVED         = (1ul<<0ul);
/*static*/ const unsigned long Texture::TX_BLIT_NO_SCALE    = (1ul<<1ul);
/*static*/ const unsigned long Texture::TX_GENERATE_ALPHA   = (1ul<<2ul);
/*static*/ const unsigned long Texture::TX_ALPHA_ONLY       = (1ul<<3ul);
/*static*/ const unsigned long Texture::TX_NO_ALPHA         = (1ul<<4ul);

/*static*/ const unsigned long Texture::WRAP_REPEAT         =     1		;
/*static*/ const unsigned long Texture::WRAP_CLAMP          =     2		;

/*static*/ const unsigned long Texture::ENV_BLEND              =  1;
/*static*/ const unsigned long Texture::ENV_REPLACE            =  2;
/*static*/ const unsigned long Texture::ENV_DECAL              =  3;
/*static*/ const unsigned long Texture::ENV_MODULATE           =  4;

/*static*/ const unsigned long Texture::FORMAT_INTENSITY       =  1;
/*static*/ const unsigned long Texture::FORMAT_LUMINANCE       =  2;
/*static*/ const unsigned long Texture::FORMAT_LUMINANCE_ALPHA =  3;
/*static*/ const unsigned long Texture::FORMAT_ALPHA           =  4;
/*static*/ const unsigned long Texture::FORMAT_RGB             =  5;
/*static*/ const unsigned long Texture::FORMAT_RGBA            =  6;

/*static*/ const unsigned long Texture::FILTER_NEAREST               = 1;
/*static*/ const unsigned long Texture::FILTER_LINEAR                = 2;
/*static*/ const unsigned long Texture::FILTER_NEAREST_MIPMAP_LINEAR = 3;
/*static*/ const unsigned long Texture::FILTER_LINEAR_MIPMAP_LINEAR  = 4;


/*!
	\brief  Return the minimum power of two at least as large as spesified value
	\param  value Minimum accepted result
	\return Smallest power of two not smaller than value
*/
static int minPow( GLuint value ){
	GLuint i = 2;

	while( i<value ) i *= 2;
	return i;
}


/*!
	\brief Texture constructor
	\param name Name for the new Texture
*/
Texture::Texture( const std::string &name )
:
Named( name )
{
	this->is_good                = false;
	this->is_bad                 = false;
	this->work_data              = NULL;
	this->work_data_pixel_format = 0;
	this->work_data_allocated    = false;
	this->gl_internal_format     = 0;
	this->env_function           = ENV_MODULATE;
	this->env_color              = Color(0,0,0,0);
	this->mag_filter             = FILTER_NEAREST;
	this->min_filter             = FILTER_LINEAR_MIPMAP_LINEAR;
	this->wrap_s                 = WRAP_REPEAT;
	this->wrap_t                 = WRAP_REPEAT;
	this->options                = 0;
	this->modify                 = 0;

#	if defined( USE_TINY_GL )
	this->env_function       = ENV_DECAL;
#	endif

	glGenTextures( 1, &gl_texture_id );
}


//!  Texture destructor
/*virtual*/ Texture::~Texture(){
	glDeleteTextures( 1, &gl_texture_id );
	setWorkData( NULL );
}


//!  Apply texture to OpenGL state
void Texture::apply(){
	if( is_good ){
		glBindTexture( GL_TEXTURE_2D, gl_texture_id );
	}else{
		emsg( M_MAT, "Texture::apply() texture is not good" );
	}

}


/*!
	\brief  Return true if there is actual texturemap bind to this texture
	\return True if this texture has been properly set, false if texture is not ready to be used
*/
bool Texture::isGood(){
	return is_good;
}

bool Texture::isBad(){
	return is_bad;
}


/*!
	\brief Set texture repeat parameters
	\param wrap_s Wrapping mode for texture s-axis, either WRAP_REPEAT or WRAP_CLAMP
	\param wrap_t Wrapping mode for texture t-axis, either WRAP_REPEAT or WRAP_CLAMP
*/
void Texture::setWrap( int wrap_s, int wrap_t ){
	this->wrap_s = wrap_s;
	this->wrap_t = wrap_t;
}


/*!
	\brief Set Texture function
	\param env Texture function. One of ENV_BLEND, ENV_REPLACE, ENV_DECAL, or ENV_MODULATE.
*/
void Texture::setEnv( int env_function ){
	this->env_function = env_function;
}


/*!
	\brief Set Texture function
	\param env Texture function. One of ENV_BLEND, ENV_REPLACE, ENV_DECAL, or ENV_MODULATE.
	\param c Color to be used by the Texture function
*/
void Texture::setEnv( int env_function, const Color &env_color ){
#	if !defined( USE_TINY_GL )
	this->env_function = env_function;
	this->env_color    = env_color;
#	endif
}


/*!
	\brief Set Texture filter
	\param filter The filter mode, either FILTER_NEAREST or FILTER_LINEAR
*/
void Texture::setFilter( const unsigned long filter_mode ){
	this->mag_filter = filter_mode;
	this->min_filter = filter_mode;
}

void Texture::setMagFilter( const unsigned long filter_mode ){
	this->mag_filter = filter_mode;
}

void Texture::setMinFilter( const unsigned long filter_mode ){
	this->min_filter = filter_mode;
}


/*!
	\brief Return the size of this Texture in texels
	\return The size of this Texture in texels
*/
const IntVector2 &Texture::getSize(){
	return size;
}


/*!
	\brief Set Texture image data
	\param data Pointer to Texture image data
	\param width Width of Texture image data in texels
	\param height Height of Texture image data in texels
	\param format Format of Texture image data
	\param modify Allowed and requested modification options for Texture image data
*/
void Texture::putData( unsigned char *data, const IntVector2 &size, int format, unsigned long modify ){
	switch( format ){
		case FORMAT_INTENSITY      : work_data_pixel_format = GL_INTENSITY;       break;
		case FORMAT_LUMINANCE      : work_data_pixel_format = GL_LUMINANCE;       break;
		case FORMAT_LUMINANCE_ALPHA: work_data_pixel_format = GL_LUMINANCE_ALPHA; break;
		case FORMAT_ALPHA          : work_data_pixel_format = GL_ALPHA;           break;
		case FORMAT_RGB            : work_data_pixel_format = GL_RGB;             break;
		case FORMAT_RGBA           : work_data_pixel_format = GL_RGBA;            break;
		default:
			emsg( M_MAT, "Texture::putData() unknown format" );
			break;
	}
	this->size   = size;
	this->modify = modify;

	gl_internal_format = work_data_pixel_format;

	setWorkData( data, false );
	doFormat();
	doSize();
}


/*!
	\brief Set working data for Texture
	\param data Pointer to working data

	The putData() -method puts texture data into texture in several phases.
	Each phase may modify the existing image data. The currently active
	image data is kept in work_data pointer. The work_data pointer should
	be updated through this method.
*/
void Texture::setWorkData( void *vdata, bool alloc ){
	unsigned char *data = (unsigned char *)vdata;
	if( work_data_allocated == true ){
		delete[] work_data;
	}
	work_data = data;
	if( alloc == true ){
		if( data != NULL ){
			work_data_allocated = true;
		}else{
			work_data_allocated;
		}
	}
}


//!  Determine the final image data format for Texture
bool Texture::doFormat(){

#	if defined( USE_TINY_GL )

	convert_to_rgb();

#	else

	//  Generate, add and remove alpha channel
	if( modify.isEnabled(TX_NO_ALPHA) ){
		switch( work_data_pixel_format ){
		case GL_INTENSITY      : gl_internal_format = GL_INTENSITY; break;
		case GL_LUMINANCE      : gl_internal_format = GL_LUMINANCE; break;
//		case GL_LUMINANCE_ALPHA: gl_internal_format = GL_LUMINANCE;
		case GL_ALPHA          : gl_internal_format     = GL_LUMINANCE;
		                         work_data_pixel_format = GL_LUMINANCE; break;
		case GL_RGB            : gl_internal_format = GL_RGB; break;
		case GL_RGBA           : gl_internal_format = GL_RGB; break;
		default:
			emsg( M_MAT, "Texture::doFormat() problem" );
			return false;
		}
	}else if( modify.isEnabled(TX_GENERATE_ALPHA) ){
		if( modify.isEnabled(TX_ALPHA_ONLY) ){
			convert_to_a();
		}
	}

#	endif

	return true;
}


//!  Determine the final size for Texture image data
bool Texture::doSize(){

#	if defined( USE_TINY_GL )
	gl_internal_format = GL_RGB;
#	endif

	//  Scale if needed
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	View::check();
    bool scale      = false;
    IntVector2 new_size = size;

	//  Scaling process should make sure that all
	//  texture sizes are ok to the OpenGL driver,
	//  which may be different on any machine.
	if( new_size[0] != minPow(new_size[0]) ){
		new_size[0] = minPow( new_size[0] );
		scale     = true;
	}
	if( new_size[1] != minPow(new_size[1]) ){
	    new_size[1]  = minPow( new_size[1] );
		scale      = true;
	}

	//  See if texture size is ok for OpenGL driver
	//  Does not seem to work :/

#	if defined( USE_TINY_GL )

	if( new_size[0] > 256 ){
		new_size[0] = 256;
		scale = true;
	}
	if( new_size[1] > 256 ){
		new_size[1] = 256;
		scale = true;
	}

#	else

	if( new_size[0] > 1024 ){
		new_size[0] = 1024;
		scale = true;
	}
	if( new_size[1] > 512 ){
		new_size[1] = 512;
		scale = true;
	}

	GLint format = 0;
	int   x      = 0;
	int   tries  = 0;

	for( tries=0; tries<1000; tries++ ){
		glTexImage2D( GL_PROXY_TEXTURE_2D, 0, gl_internal_format, new_size[0], new_size[1], 0, work_data_pixel_format, GL_UNSIGNED_BYTE, NULL );
		glGetTexLevelParameteriv( GL_PROXY_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &format );
		View::check();

		if( format == 0 ){  //  if not, go down in size
			x     = 1 - x;
			scale = true;
			if( x==0 ){
				new_size[1] = new_size[1] / 2;  //  halve height
			}else{
                new_size[0] = new_size[0] / 2;   //  halve width
			}
		}else{
			if( format == gl_internal_format ){
				break;  //  ok size!
			}else{
				emsg( M_MAT, "format?! 0x%x\n", format );
				break;
			}
		}
		if( new_size[0]==0 || new_size[1]==0 ){
			emsg( M_MAT, "Can not find memory for texture - Giving up!" );
			return false;
		}
	}

	if( tries==1000 ){
		emsg( M_MAT, "Can not find memory for texture after 1000 tries - Giving up!" );
		return false;
	}

#	endif

	if( scale ){
		//debug_msg( "Doing scale from %d x %d to %d x %d", width, height, new_width, new_height );
		void *new_data = NULL;//new unsigned char[ new_width * new_height * gl_components];
		glu_ScaleImage(
			work_data_pixel_format,
			size[0],     size[1],     GL_UNSIGNED_BYTE,  work_data,
			new_size[0], new_size[1], GL_UNSIGNED_BYTE, &new_data
		);
		View::check();

		setWorkData( new_data );
		this->size = new_size;
	}
	//debug_msg( "Texture size %d x %d", width, height );

	return true;
}


//!  Bind the image data to texture
/*virtual*/ bool Texture::doBind(){
	if( is_bad ){
		emsg( M_MAT, "Bad texture" );
		return false;
	}
	glBindTexture( GL_TEXTURE_2D,       gl_texture_id );
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	View::check();

	switch( mag_filter ){
	default:
		emsg( M_MAT, "Unknown texture mag filter" );
	case FILTER_NEAREST:
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
		break;
	case FILTER_LINEAR:
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		break;
	case FILTER_NEAREST_MIPMAP_LINEAR:
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
		break;
	case FILTER_LINEAR_MIPMAP_LINEAR:
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		break;
	}
	View::check();
	switch( min_filter ){
	default:
		emsg( M_MAT, "Unknown texture min filter" );
	case FILTER_NEAREST:
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
		break;
	case FILTER_LINEAR:
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		break;
	case FILTER_NEAREST_MIPMAP_LINEAR:
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR );
		break;
	case FILTER_LINEAR_MIPMAP_LINEAR:
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
		break;
	}
	View::check();

	switch( wrap_s ){
	default:
		emsg( M_MAT, "Unknown texture wrap mode" );
	case WRAP_REPEAT:
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		break;
	case WRAP_CLAMP:
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
		break;
	}
	View::check();

	switch( wrap_t ){
	default:
		emsg( M_MAT, "Unknown texture wrap mode" );
	case WRAP_REPEAT:
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		break;
	case WRAP_CLAMP:
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
		break;
	}
	View::check();

#	if !defined( USE_TINY_GL )
	switch( env_function ){
	default: 
		emsg( M_MAT, "Unknown texture function" );
	case ENV_BLEND   : 
		glTexEnvi ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,  GL_BLEND       );
		glTexEnvfv( GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, env_color.rgba ); 
		break;
	case ENV_REPLACE:
		glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE  );
		break;
	case ENV_DECAL:
		glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL    );
		break;
	case ENV_MODULATE:
		glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
		break;
	}
	View::check();

	if( modify.isEnabled(TX_BLIT_NO_SCALE) == true ){
		glTexImage2D(
			GL_TEXTURE_2D, 
			0, 
			gl_internal_format, 
			size[0], size[1],
			0, 
			work_data_pixel_format, 
			GL_UNSIGNED_BYTE, 
			work_data
		);
		View::check();
	}else{
		int error = glu_Build2DMipmaps(
			GL_TEXTURE_2D,
			gl_internal_format, 
			size[0], size[1],
			work_data_pixel_format, 
			GL_UNSIGNED_BYTE, 
			work_data 
		);

		if( error != 0 ){
			emsg( M_MAT, "glu_Build2DMipmaps() failed" );
			return false;
		} 
	};

#	else
	glTexImage2D( GL_TEXTURE_2D, 0, 3, size[0], size[1], 0, work_data_pixel_format, GL_UNSIGNED_BYTE, work_data );
#	endif
	View::check();
	is_good = true;
	return true;
}


};  //  namespace Graphics
};  //  namespace Teddy


/*

Useful extensions:

GL_IBM_texture_mirrored_repeat
GL_EXT_texture_filter_anisotropic (GL_TEXTURE_MAX_ANISOTROPY_EXT)
GL_ARB_texture_compression
GL_EXT_texture_compression_s3tc

Texture formats:

GL_INTENSITY
GL_LUMINANCE
GL_ALPHA
GL_LUMINANCE_ALPHA
GL_RGB
GL_RGBA

GL_ARB_texture_compression:

GL_COMPRESSED_ALPHA_ARB
GL_COMPRESSED_LUMINANCE_ARB
GL_COMPRESSED_INTENSITY_ARB
GL_COMPRESSED_LUMINANCE_ALPHA_ARB
GL_COMPRESSED_RGB_ARB
GL_COMPRESSED_RGBA_ARB

GL_EXT_texture_compression_s3tc:

GL_COMPRESSED_RGB_S3TC_DXT1_EXT
GL_COMPRESSED_RGBA_S3TC_DXT1_EXT
GL_COMPRESSED_RGBA_S3TC_DXT3_EXT
GL_COMPRESSED_RGBA_S3TC_DXT5_EXT

*/


