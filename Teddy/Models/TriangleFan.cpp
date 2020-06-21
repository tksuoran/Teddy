
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

	$Id: TriangleFan.cpp,v 1.5 2002/01/17 18:57:38 tksuoran Exp $
*/


#include "Teddy/Models/TriangleFan.h"
#include "Teddy/Models/Vertex.h"
#include "Teddy/PhysicalComponents/Projection.h"
#include "Teddy/SysSupport/Messages.h"
#include "Teddy/SysSupport/StdIO.h"
using namespace Teddy::PhysicalComponents;
using namespace Teddy::SysSupport;


namespace Teddy  {
namespace Models {


//!  Constructor
TriangleFan::TriangleFan(){
	//  FIX
}


//!  Destructor
/*virtual*/ TriangleFan::~TriangleFan(){
	//  FIX
}


//!  Draw TriangleFan
/*virtual*/ void TriangleFan::draw( Projection *p ){

	if( isEnabled(EL_USE_ELEMENT_NORMAL|EL_HAS_ELEMENT_NORMAL) ){
		dmsg( M_INIT, "Drawing flat trianglefan" );

		p->beginTriangles();

		list<Vector*>::const_iterator  n_it  = normals .begin();
		list<Vertex*>::const_iterator  v1_it = vertices.begin();
	 	list<Vertex*>::const_iterator  v2_it = v1_it;
		Vertex                        *v0    = *v1_it++;
		while( n_it != normals.end() && v2_it != vertices.end() ){
            Vector *normal = *n_it++;
			p->normal( *normal );
			v0->draw( p );
			v2_it = v1_it;
			(*v2_it++)->draw( p ); if( v2_it == vertices.end() ){ dmsg( M_WARN, "TriangleFan missing vertices" ); break; }
			(*v2_it++)->draw( p );
			v1_it++;
		}

		p->end();

	}else{
		dmsg( M_INIT, "Drawing smoothed trianglefan" );

		p->beginTriangleFan();
		list<Vertex*>::const_iterator v_it = vertices.begin();
		while( v_it != vertices.end() ){
			(*v_it)->draw( p );
			v_it++;
		}

		p->end();
	}

}


/*virtual*/ void TriangleFan::makeNormal(){
	list<Vertex*>::iterator v_i1 = vertices.begin();
	list<Vertex*>::iterator v_i2 = v_i1;

	if( vertices.size()<3 ){
        emsg( M_MAT,
			"TriangleFan does not have enough vertices for normal calculation (%d vertices found)",
			vertices.size()
		);
		normal = Vector(0,1,0);
		return;
	}

	msg( M_INIT, "TriangleFan has %d vertices", vertices.size() );

    normals.clear();
    Vector a = (*v_i1++)->getVertex();
	float  len;
	do{
		v_i2 = v_i1++;

		Vector b  = (*v_i2++)->getVertex();
		Vector ab = b-a;
		ab.normalize();
		msg( M_INIT, "TriangleFan ab %f, %f, %f a = %f, %f, %f", ab[0], ab[1], ab[2], a[0], a[1], a[2] );

		if( v_i2 == vertices.end() ) break;
		Vector c  = (*v_i2++)->getVertex();
		Vector ac = c-a;
		ac.normalize();
		msg( M_INIT, "TriangleFan ac %f, %f, %f b = %f, %f, %f", ac[0], ac[1], ac[2], b[0], b[1], b[2] );

		float test = ab | ac;
		msg( M_INIT, "TriangleFan  b %f, %f, %f c = %f, %f, %f  test %f", b[0], b[1], b[2], c[0], c[1], c[2], test );

		normal    = (a-b)^(a-c);
		normal.normalize();
		len = normal.magnitude();
		if( len < 0.9 || len >11.1 ){
			emsg( M_MAT, "TriangleFan normal problem" );
            return;
		}
        normals.push_back( new Vector(normal) );
		if( test == -1.0 || test == 1.0 ){
			msg( M_INIT, "TriangleFan normal %f, %f, %f degenerate", normal[0], normal[1], normal[2] );
		}else{
			this->normal = normal;
			msg( M_INIT, "TriangleFan normal %f, %f, %f stored", normal[0], normal[1], normal[2] );
		}
	}while( v_i2 != vertices.end() );

	enable( EL_HAS_ELEMENT_NORMAL | EL_USE_ELEMENT_NORMAL );
}


#if defined( TEDDY_INCLUDE_COLDET )
/*virtual*/ int TriangleFan::addToCollisionModel( Teddy::ColDet::CollisionModel3D *collision_model ){
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
/*virtual*/ unsigned long TriangleFan::countCSGFaceElements(){
	unsigned long size = vertices.size();
	return size - 2;
}



};  //  namespace Models
};  //  namespace Teddy

