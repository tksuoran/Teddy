
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

	$Id: Sphere.cpp,v 1.5 2002/02/16 12:41:39 tksuoran Exp $
*/


#include "Teddy/Models/Sphere.h"
#include "Teddy/Models/QuadStrip.h"
#include "Teddy/Models/Vertex.h"
#include "Teddy/SysSupport/StdMaths.h"
using namespace Teddy::Maths;


namespace Teddy  {
namespace Models {


/*!
	\brief Sphere constructor
	\param rad Radius of the Sphere
	\param stacks Number of stack subdivision for the Sphere
	\param slices NUmebr of slice subdividision for the Sphere
*/
Sphere::Sphere(
	const std::string &name,
	const double       rad,
	const int          stacks,
	const int          slices
)
:
Model ( name   ),
radius( rad    ),
stacks( stacks ),
slices( slices )
{
	double r;
	double x;
	double y;
	double z;
	int    i;
	int    j;
	int    k;

	for( j=0; j<stacks; j++ ){
		QuadStrip *qs = new QuadStrip();
		for( i=0; i<slices+1; i++ ){
			for( k=1; k>=0; k-- ){
				z = radius*cos( (j+k)*M_PI/stacks );
				r =	radius*sin( (j+k)*M_PI/stacks );
				x = r*cos( i*M_2_PI/slices );
				y = r*sin( i*M_2_PI/slices );
				Vector normal = Vector( x, y, z );
				normal.normalize();
				double  s        = 1 - (double)(   i   ) / (double)( stacks );
				double  t        =     (double)( (j+k) ) / (double)( slices );
				Vertex *v        = new Vertex( x, y, z );
				v->setNormal ( normal );
				v->setTexture( s, t, 0.0f );
				qs->add( v );
			}
		}
		add( qs );
	}

	setupClipRadius();
}


};  //  namespace Models
};  //  namespace Teddy

