
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

	$Id: TextureManager.cpp,v 1.1 2002/01/22 19:30:04 tksuoran Exp $
*/


#include "Teddy/TeddyConfig.h"
#include "Teddy/Graphics/TextureManager.h"
#include "Teddy/SysSupport/Messages.h"

#include <stdlib.h>

using namespace Teddy::SysSupport;


namespace Teddy    {
namespace Graphics {


//!  Constructor
TextureManager::TextureManager(){
}


//!  Destructor
/*virtual*/ TextureManager::~TextureManager(){
	deleteAll();
}


void TextureManager::deleteAll(){
}


void TextureManager::addTexture( Texture *t ){
}


Texture *TextureManager::newTexture( char *fname ){
	Texture *t = NULL;
	return t;
};


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


