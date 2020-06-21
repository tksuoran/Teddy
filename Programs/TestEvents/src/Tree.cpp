
/*
	TEDDY - General graphics application library
	Copyright (C) 1999, 2000, 2001	Timo Suoranta
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

	$Id: Tree.cpp,v 1.3 2002/03/12 10:44:29 tksuoran Exp $
*/


#include "Teddy/Materials/Material.h"
#include "Teddy/Maths/Matrix.h"
#include "Teddy/Models/Cone.h"
#include "Teddy/Models/Box.h"
#include "Teddy/Models/Sphere.h"
#include "Teddy/Models/Cylinder.h"
#include "Teddy/Models/Geometry.h"

#include "Tree.h"
#include "Bender.h"
using namespace Teddy::Application;
using namespace Teddy::Materials;
using namespace Teddy::Maths;
using namespace Teddy::Models;


//!  Constructor
Tree::Tree( BaseSimulationTimer *st, int slices, int stacks, int cones, float height, float radius, float rad_add )
:
Model( "Tree" )
{
	int    c;
	float  cone_height = height / (float)cones;
	Matrix m;

	Matrix m_syz;  //  matrix to swap y and z
	m_syz.setRow( 0, Vector4(1,0,0,0) ); // nx = 1*x + 0*y + 0*z + 0
	m_syz.setRow( 1, Vector4(0,0,1,0) ); // ny = 0*x + 0*y + 1*z + 0
	m_syz.setRow( 2, Vector4(0,1,0,0) ); // nz = 0*x + 1*y + 0*z + 0
	m_syz.setRow( 3, Vector4(0,0,0,1) );

	Cylinder *cyl = new Cylinder( "", height/20, cone_height, slices/3 );
	cyl->transformVertices( m_syz );
	cyl->setMaterial( &Material::DARK_ORANGE );
	add( cyl );
	Model *below = cyl;
	for( c=0; c<cones; c++ ){
		float top_radius    = (cones-1-c) * radius / (float)cones;
		float bottom_radius = top_radius + rad_add;
		Cone *co = new Cone( "", bottom_radius, top_radius, cone_height, slices, stacks, true, false );
		co->transformVertices( m_syz );
		co->setupClipRadius();
		co->setPosition( 0.0f, cone_height, 0.0f );
		co->pitch( M_PI / 20.0f );
		Bender *bender = new Bender( 
			co, 
			Vector(1.0f,0.0f,0.0f),
			0.0f,
			(float)(M_PI / 21.0f),
			500.0f
		);
		st->add( bender );
		below->add( co );
		below = co;
	}
	setupClipRadius();
}
