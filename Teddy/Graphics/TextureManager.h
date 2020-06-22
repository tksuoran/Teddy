
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


#ifndef TEDDY__GRAPHICS__TEXTURE_MANAGER_H
#define TEDDY__GRAPHICS__TEXTURE_MANAGER_H


#include "Teddy/SysSupport/StdList.h"


namespace Teddy    {
namespace Graphics {


class Texture;


/*!
	\brief Texture manager
	\bug   Not yet implemented
*/
class TextureManager {
public:
	TextureManager();
	virtual ~TextureManager();

	void     addTexture    ( Texture *t );
	void     reloadTextures();

	Texture *newTexture    ( char *fname );
	void     deleteTexture ( Texture *t );
	void     deleteAll     ();

protected:
	list<Texture*> textures;
};


};  //  namespace Graphics
};  //  namespace Teddy


#endif  //  TEDDY__GRAPHICS__TEXTURE_MANAGER_H

