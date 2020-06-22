
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


#include "Teddy/Maths/Vector.h"
#include "Teddy/Models/QuadStrip.h"
#include "Teddy/Models/Torus.h"
#include "Teddy/Models/Vertex.h"
#include "Teddy/SysSupport/StdMaths.h"
using namespace Teddy::Maths;


namespace Teddy  {
namespace Models {


/*!
	\brief Torus constructor
	\param name Name for new Torus mesh
	\param rt Torus major axis
	\param rc Torus minor axis
	\param numt Number of stack subdivisions
	\param numc Number of slice subdivisions
*/
Torus::Torus(
	const std::string &name,
	const double       major_radius,
	const double       minor_radius,
	const int          stacks,
	const int          slices
):Model( name ){
	int    i;
	int    j;
	int    k;
	double s;
	double t;
	double x;
	double y;
	double z;

	double cp = M_2_PI/(double)stacks;
	double tp = M_2_PI/(double)slices;

	for( i=0; i<stacks; i++ ){
		QuadStrip *qs = new QuadStrip();
		for( j=0; j<=slices; j++ ){
			for( k=0; k<2; k++ ){
				s = (i + k) % stacks + 0.5;
				t = j % slices;

				x = (major_radius + minor_radius * cos(s*cp)) * cos(t*tp);
				y = (major_radius + minor_radius * cos(s*cp)) * sin(t*tp);
				z = minor_radius * sin(s*cp);
				Vertex *v = new Vertex( x, y, z );

				x = cos(t*tp) * cos(s*cp);
				y = sin(t*tp) * cos(s*cp);
				z = sin(s*cp);
				v->setNormal( Vector( x, y, z ) );
				qs->add( v );
			}
		}
		add( qs );
	}

	setupClipRadius();
}


};  //  namespace Models
};  //  namespace Teddy

