
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


#include "Teddy/Models/Cone.h"
#include "Teddy/Models/QuadStrip.h"
#include "Teddy/Models/TriangleFan.h"
#include "Teddy/Models/Vertex.h"
#include "Teddy/Models/Model.h"
#include "Teddy/Models/Face.h"
#include "Teddy/SysSupport/StdMaths.h"
using namespace Teddy::Maths;


namespace Teddy  {
namespace Models {


/*!
	\brief Cone constructor
	\param name Name for new Cone Model
	\param base_radius Bottom radius of Cone
	\param top_radius Top radius of Cone
	\param height Height of Cone
	\param slices Number of slice subdivisions
	\param stacks Numebr of stack subdivisions
*/
Cone::Cone(
	const std::string &name,
	const double       base_radius,
	const double       top_radius,
	const double       height,
	int                slices,
	int                stacks,
	bool               use_bottom,
	bool               use_top
)
:Model( name )
{
	if( slices       < 3 ) slices     = 4;
	if( stacks       < 1 ) stacks     = 1;
	if( base_radius == 0 ) use_bottom = false;
	if( top_radius  == 0 ) use_top    = false;

	double  da     = M_2_PI / slices;
	double  dr     = (top_radius - base_radius) / stacks;
	double  dz     = height / stacks;
	double  nz     = (base_radius - top_radius) / height;  /* Z component of normal vectors */
	double  ds     = 1 / slices;
	double  dt     = 1 / stacks;
	double  t      = 0;
	double  z      = 0;
	double  r      = base_radius;
	Face   *top    = NULL;
	Face   *bottom = NULL;
	Vertex *v1;
	Vertex *v2;
	Vector	n1;
	Vector	n2;
	int     i;
	int     j;

	if( use_bottom ) bottom = new Face();
	if( use_top    ) top    = new Face();

	for( j=0; j<=stacks-1; j++ ){
		double      s = 0;
		QuadStrip *qs = new QuadStrip();

		for( i=slices; i>=0; i-- ){
			double x;
			double y;

			if( i==slices ){
				x = ::sin( 0 );
				y = ::cos( 0 );
			}else{
				x = ::sin( i * da );
				y = ::cos( i * da );
			}

			v1 = new Vertex( r*x, r*y,  z );
			n1 =     Vector(   x,   y, nz );
			n1.  normalize();
			v1 ->setNormal( n1 );
			qs->add( v1 );

			v2 = new Vertex( (r+dr)*x, (r+dr)*y, dz+z );
			n2 =     Vector(        x,        y,   nz );
			n2.  normalize();
			v2 ->setNormal( n2 );
			qs->add( v2 );

			if( i!=slices ){
				//  Bottom
				if( use_bottom ){
					if( (j==0) && (r!=0) ){
						Vertex *v_bot = new Vertex( v1 );
						v_bot->disable( Element::VX_USE_PARENT_NORMAL|Element::VX_USE_THIS_VERTEX );
						bottom->add( v_bot );
					}
				}

				//  Top
				if( use_top ){
					if( (j==stacks-1) && ((r+dr)!=0) ){
						Vertex *v_top = new Vertex( v2 );
						v_top->disable( Element::VX_USE_PARENT_NORMAL|Element::VX_USE_THIS_VERTEX );
						top->add( v_top );
					}
				}
			}

			s += ds;
		}  //  slices
		add( qs );
		r += dr;
		t += dt;
		z += dz;
	}  //  stacks
	if( use_bottom ){
		bottom->reverse();
		bottom->makeNormal();
		add( bottom );
	}
	if( use_top ){
		top ->makeNormal();
		add( top );
	}

	setupClipRadius();
}


};  //  namespace Models
};  //  namespace Teddy

