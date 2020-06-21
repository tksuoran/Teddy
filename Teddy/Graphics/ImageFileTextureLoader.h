
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

	$Id:  $
*/


#ifndef TEDDY__IMPORTS__IMAGE_FILE_TEXTURE_LOADER__H
#define TEDDY__IMPORTS__IMAGE_FILE_TEXTURE_LOADER__H


#include "Teddy/Graphics/ImageFileTexture.h"
#include "Teddy/SysSupport/Types.h"
#include "Teddy/SysSupport/StdMap.h"
#include "Teddy/SysSupport/StdString.h"


namespace Teddy    {
namespace Graphics {


//typedef std::map<std::string, Teddy::MixIn::CountedPointer<Model> > string_to_model;
typedef std::map<std::string, Texture*     > string_to_texture;
typedef std::map<Texture*,    unsigned long> texture_to_long;


class ImageFileTextureLoader {
public:
	static Texture *loadTexture( const std::string &name );

protected:
	static string_to_texture  loaded_textures;
	static texture_to_long    texture_counters;
};


};  //  namespace Graphics
};  //  namespace Teddy


#endif  //  TEDDY__IMPORTS__IMAGE_FILE_TEXTURE_LOADER__H

