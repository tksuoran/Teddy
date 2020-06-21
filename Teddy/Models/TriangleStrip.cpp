
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

	$Id:  $
*/


#include "Teddy/Models/TriangleStrip.h"
#include "Teddy/Models/Vertex.h"
#include "Teddy/PhysicalComponents/Projection.h"
#include "Teddy/SysSupport/Messages.h"
#include "Teddy/SysSupport/StdIO.h"
using namespace Teddy::PhysicalComponents;
using namespace Teddy::SysSupport;


namespace Teddy  {
namespace Models {


//!  Constructor
TriangleStrip::TriangleStrip(){
}


//!  Destructor
/*virtual*/ TriangleStrip::~TriangleStrip(){
	//  FIX
}


//!  Draw TriangleStrip
/*virtual*/ void TriangleStrip::draw( Projection *p ){

	if( isEnabled(EL_USE_ELEMENT_NORMAL|EL_HAS_ELEMENT_NORMAL) ){
		dmsg( M_INIT, "Drawing flat trianglestrip" );

		p->beginTriangles();

		list<Vector*>::const_iterator n_it  = normals .begin();
		list<Vertex*>::const_iterator v1_it = vertices.begin();
		list<Vertex*>::const_iterator v2_it = v1_it;
        bool swap = true;
		while( n_it != normals.end() && v2_it != vertices.end() ){
            Vector *normal = *n_it++;
			p->normal( *normal );
			v2_it = v1_it;
			Vertex *a = *v2_it++; if( v2_it == vertices.end() ){ dmsg( M_WARN, "TriangleStrip missing vertices" ); break; }
			Vertex *b = *v2_it++; if( v2_it == vertices.end() ){ dmsg( M_WARN, "TriangleStrip missing vertices" ); break; }
			Vertex *c = *v2_it++;
			if( swap ){
				b->draw( p );
				a->draw( p );
			}else{
				a->draw( p );
				b->draw( p );
			}
			c->draw( p );
            dprint( M_INIT, "." );
			v1_it++;
            swap = !swap;
		}

		p->end();

	}else{
		dmsg( M_INIT, "Drawing smoothed trianglestrip" );

		p->beginTriangleStrip();
		list<Vertex*>::const_iterator v_it = vertices.begin();
		while( v_it != vertices.end() ){
			(*v_it)->draw( p );
			v_it++;
		}

		p->end();
	}

}



/*virtual*/ void TriangleStrip::makeNormal(){
	list<Vertex*>::iterator v_i1 = vertices.begin();
	list<Vertex*>::iterator v_i2 = v_i1;

	if( vertices.size()<3 ){
        dmsg( M_WARN,
			"Element does not have enough vertices for normal calculation (%d vertices found)",
			vertices.size()
		);
		normal = Vector(0,1,0);
		return;
	}

	normals.clear();
	float len;
	bool swap = true;
	Vector a;
	Vector b;
	Vector c;
	do{
		v_i2 = v_i1++;

		if( swap ){
			if( v_i2 == vertices.end() ){ dmsg( M_WARN, "TriangleStripe normal problem" ); return; }
			b  = (*v_i2++)->getVertex();
			if( v_i2 == vertices.end() ){ dmsg( M_WARN, "TriangleStripe normal problem" ); return; }
			a  = (*v_i2++)->getVertex();
		}else{
			if( v_i2 == vertices.end() ){ dmsg( M_WARN, "TriangleStripe normal problem" ); return; }
			a  = (*v_i2++)->getVertex();
			if( v_i2 == vertices.end() ){ dmsg( M_WARN, "TriangleStripe normal problem" ); return; }
			b  = (*v_i2++)->getVertex();
		}

		if( v_i2 == vertices.end() ){ dmsg( M_WARN, "TriangleStripe normal problem" ); return; }
		c  = (*v_i2++)->getVertex();

		Vector ab = b-a;
		ab.normalize();
		Vector bc = c-b;
		bc.normalize();
		float test = ab | bc;
		normal = (a-c)^(a-b);
		normal.normalize();
		len = normal.magnitude();
		if( len < 0.9 || len >11.1 ){
			dmsg( M_WARN, "TriangleStripe normal problem" );
			return;
		}
		if( test == -1.0 || test == 1.0 ){
		}else{
			this->normal = normal;
		}
		normals.push_back( new Vector(normal) );
		swap = !swap;
	}while( v_i2 != vertices.end() );

	enable( EL_HAS_ELEMENT_NORMAL | EL_USE_ELEMENT_NORMAL );
}



#if defined( TEDDY_INCLUDE_COLDET )
/*virtual*/ int TriangleStrip::addToCollisionModel( Teddy::ColDet::CollisionModel3D *collision_model ){
	int tris = 0;
	list<Vertex*>::const_iterator v_it  = vertices.begin();

    FloatVector a  = (*v_it)->getVertex(); v_it++; if( v_it == vertices.end() ) return 0;
	FloatVector b  = (*v_it)->getVertex(); v_it++;
	while( v_it != vertices.end() ){
		FloatVector c = (*v_it)->getVertex();
		collision_model->addTriangle( a, b, c );
		a  = b;
		b  = c;
		tris++;
		v_it++;
	}
	return tris;
}
#endif


//  CSG
/*virtual*/ unsigned long TriangleStrip::countCSGFaceElements(){
	unsigned long size = vertices.size();
	return size - 2;
}


};  //  namespace Models
};  //  namespace Teddy

