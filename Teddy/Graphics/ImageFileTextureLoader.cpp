
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


#include "Teddy/Graphics/ImageFileTextureLoader.h"
#include "Teddy/SysSupport/StdAlgo.h"
#include "Teddy/SysSupport/Messages.h"
using namespace Teddy::SysSupport;


namespace Teddy    {
namespace Graphics {


/*static*/ string_to_texture  ImageFileTextureLoader::loaded_textures;
/*static*/ texture_to_long    ImageFileTextureLoader::texture_counters;


/*static*/ Texture *ImageFileTextureLoader::loadTexture( const std::string &name ){
	string_to_texture::iterator  m_it    = loaded_textures.find( name );
	Texture                     *texture = NULL;
	std::ostringstream           texture_name_stream;
	texture_name_stream << name << ".";
	
	if( m_it != loaded_textures.end() ){
		texture = (*m_it).second;
	}else{
		texture = new ImageFileTexture( name );
		loaded_textures.insert( std::make_pair(name,texture) );
	}

	texture_to_long::iterator l_it = texture_counters.find( texture );
	if( l_it == texture_counters.end() ){
		//  add to map
		texture_counters.insert( std::make_pair(texture,1) );
		texture_name_stream << "1";
	}else{
		// increase count
		(*l_it).second++;
		texture_name_stream << (*l_it).second;
		dmsg( M_LWS, "Reuse count %ul", (*l_it).second );
	}

	std::string texture_name = texture_name_stream.str();
	return texture;
}


};  //  namespace Graphics
};  //  namespace Teddy

