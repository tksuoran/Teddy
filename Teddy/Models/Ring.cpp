
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
#include "Teddy/Models/Ring.h"
#include "Teddy/Models/QuadStrip.h"
#include "Teddy/Models/Vertex.h"
#include "Teddy/SysSupport/StdMaths.h"
using namespace Teddy::SysSupport;


namespace Teddy  {
namespace Models {


/*!
	\brief Ring constructor
	\param name Name for new Ring mesh
	\param inner_radius Inner ring radius
	\param outer_radius Outer ring radius
	\param slices Number of slice subdivisions
*/
Ring::Ring(
	const std::string &name,
	const double       inner_radius,
	const double       outer_radius,
	const int          slices )
:
Model( name )
{
	QuadStrip *qs = new QuadStrip();
	for( int i=0; i<=slices; i++ ){
		double theta = i*M_2_PI/slices;
		double slice = 1.0 - (double)(i)/(double)(slices);
		Vertex *v1 = new Vertex( inner_radius * cos(theta), 0, inner_radius * sin(theta) );
		v1->setNormal (  0.0f, 1.0f, 0.0f );
		v1->setTexture( slice, 0.0f, 0.0f );
		Vertex *v2 = new Vertex( outer_radius * cos(theta), 0, outer_radius * sin(theta) );
		v1->setNormal (  0.0f, 1.0f, 0.0f );
		v1->setTexture( slice, 1.0f, 0.0f );
		qs->add( v1 );
		qs->add( v2 );
	}
	add( qs );
	setClipRadius( outer_radius );
}


};  //  namespace Models
};  //  namespace Teddy

