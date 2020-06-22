
/*
	TSGL - Teddy Space Game Library
	Copyright (C) 2002 Timo Suoranta
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
#if !defined( TEDDY_INCLUDE_LW_SCENE )
#error You need to have TEDDY_INCLUDE_LW_SCENE in Teddy/TeddyConfig.h -- Rebuild Teddy
#endif
#include "Teddy/Graphics/View.h"
#include "Teddy/Imports/LWModel.h"
#include "Teddy/Models/Model.h"
#include "Cabin.h"
using namespace Teddy::Graphics;
using namespace Teddy::Imports;
using namespace Teddy::Materials;
using namespace Teddy::Models;
using namespace Teddy::PhysicalComponents;


//!  Cabin constructor
Cabin::Cabin( const std::string &name )
:
Area( "Cabin" )
{

    offset_free_size_relative = Vector2(  1.0f, 1.0f );
	model = new LWModel( name, 0 );
}


/*!
	\brief Draw cabin - currently not implemented
	\bug   Mesh::drawNoMaterial() needs to be fixed for this
*/
/*virtual*/ void Cabin::drawSelf(){
	return;
	view->setProjectionMatrix( Matrix::IDENTITY );
	view->setModelViewMatrix ( Matrix::IDENTITY );

	view->color( 0.1f, 0.1f, 0.2f, 0.8f );
	view->enable        ( View::BLEND );
	view->setBlendFunc  ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	view->disable       ( View::TEXTURE_2D );
	view->disable       ( View::DEPTH_TEST );
	view->setPolygonMode( GL_FILL );
//	mesh->drawNoMaterial(  );
	view->color( C_WHITE );
}

