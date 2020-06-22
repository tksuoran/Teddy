
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


#ifndef TEDDY__SCENES__POST_ELEMENT__H
#define TEDDY__SCENES__POST_ELEMENT__H


#include "Teddy/Maths/Vector4.h"
#include "Teddy/Graphics/Texture.h"
#include "Teddy/Scenes/Ellipsoid.h"
#include "Teddy/SysSupport/StdList.h"
#include "Teddy/PhysicalComponents/Projection.h"
using namespace Teddy::Maths;
using Teddy::Graphics::Texture;
using Teddy::PhysicalComponents::Projection;


namespace Teddy  {
namespace Scenes {


/*!
	\brief Postprocessing rendering element

	Baseclass for laser beams, engine glows, explosions etc. alpha blending effects.
	These need 2D processing through gluProject() like scheme.
*/
class PostElement {
public:
	PostElement( const char *filename );
    virtual ~PostElement();

	void          insert( Ellipsoid  *e );
	virtual void  draw  ( Projection *p );

protected:
	list<Ellipsoid*>  ellipsoids;
	Texture          *txt;
};


};  //  namespace Scenes
};  //  namespace Teddy


#endif  //  TEDDY__SCENES__POST_ELEMENT__H


