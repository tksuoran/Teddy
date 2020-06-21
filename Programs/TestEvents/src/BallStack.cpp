
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

#include "BallStack.h"
using namespace Teddy::Maths;
using namespace Teddy::Materials;
using namespace Teddy::Models;


//!  Constructor
BallStack::BallStack( int num_balls, float radius, float ratio )
:
Model( "BallStack" )
{
	Matrix m_syz;  //  matrix to swap y and z
	m_syz.setRow( 0, Vector4(1,0,0,0) ); // nx = 1*x + 0*y + 0*z + 0
	m_syz.setRow( 1, Vector4(0,0,1,0) ); // ny = 0*x + 0*y + 1*z + 0
	m_syz.setRow( 2, Vector4(0,1,0,0) ); // nz = 0*x + 1*y + 0*z + 0
	m_syz.setRow( 3, Vector4(0,0,0,1) );

	float  old_rad = 0.0f;
	Model *below   = this;
	for( int b=0; b<num_balls; b++ ){
		float   fslices = 14.0f + 0.5f * radius / (float)M_2_PI;
		Sphere *s       = new Sphere( "ball", radius, (int)fslices, (int)fslices );
		s    ->transformVertices( m_syz );
		s    ->setupClipRadius  ();
		s    ->setPosition      ( 0.0, old_rad + radius, 0.0f );
		s    ->pitch            ( M_PI / 19.0f );
		s    ->heading          ( M_PI / 17.0f );
		below->add( s );
		below    = s;
		old_rad  = radius;
		radius  *= ratio;
	}
	setupClipRadius();
}
