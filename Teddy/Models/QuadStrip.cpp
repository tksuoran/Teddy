
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

	$Id: QuadStrip.cpp,v 1.5 2002/01/17 18:57:38 tksuoran Exp $
*/


#include "Teddy/Models/QuadStrip.h"
#include "Teddy/Models/Vertex.h"
#include "Teddy/PhysicalComponents/Projection.h"
#include "Teddy/SysSupport/Messages.h"
#include "Teddy/SysSupport/StdIO.h"
using namespace Teddy::SysSupport;
using namespace Teddy::PhysicalComponents;


namespace Teddy  {
namespace Models {


//!  Default constructor
QuadStrip::QuadStrip(){
}


//!  Destructor
QuadStrip::~QuadStrip(){
	//  FIX
}


//!  Draw QuadStrip
void QuadStrip::draw( Projection *p ){
	p->beginQuadStrip();

	if( isEnabled(EL_USE_ELEMENT_NORMAL|EL_HAS_ELEMENT_NORMAL) ){
		dmsg( M_VERT, "Drawing flat quadstrip" );
		p->normal( normal );
	}else{
		dmsg( M_VERT, "Drawing smoothed quadstrip" );
	}

/*	list<Vertex*>::const_iterator v_it = vertices.begin();
	while( v_it != vertices.end() ){
		(*v_it)->draw( p );
		v_it++;
	}*/

    /*
	list<Vertex*>::const_reverse_iterator v_it = vertices.rbegin();
	while( v_it != vertices.rend() ){
		(*v_it)->draw( p );
		v_it++;
	}
    */

	list<Vertex*>::const_iterator v_it = vertices.end();
	while( v_it != vertices.begin() ){
		v_it--;
		(*v_it)->draw( p );
	}

	p->end();
}


/*virtual*/ void QuadStrip::makeNormal(){
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
	do{
		v_i1++;
        if( v_i2 == vertices.end() ) return;
		v_i2 = v_i1++;

		if( v_i2 == vertices.end() ) return;
		Vector a  = (*v_i2++)->getVertex();

		if( v_i2 == vertices.end() ) return;
		Vector b  = (*v_i2++)->getVertex();

		if( v_i2 == vertices.end() ) return;
		Vector c  = (*v_i2++)->getVertex();

		if( v_i2 == vertices.end() ) return;
		Vector d  = (*v_i2++)->getVertex();

		normal    = (a-c)^(a-b);
		normal.normalize();
		len = normal.magnitude();
		if( len < 0.9 || len >11.1 ){
			dmsg( M_WARN, "TriangleStripe normal problem" );
            return;
		}
        normals.push_back( new Vector(normal) );
	}while( v_i2 != vertices.end() );

	enable( EL_HAS_ELEMENT_NORMAL | EL_USE_ELEMENT_NORMAL );
    printf( "\nQuadStrip normal done\n" );
}


/*virtual*/ void QuadStrip::reverse(){
	list<Vertex*>::iterator v1_it = vertices.begin();
	list<Vertex*>::iterator v2_it = vertices.begin();
    v2_it++;
	for(;;){
		if( v1_it == vertices.end() ) break;
		if( v2_it == vertices.end() ) break;
        //  Swap vertices
		std::swap( *v1_it, *v2_it );
		v1_it++;
        v2_it++;
		if( v1_it == vertices.end() ) break;
		if( v2_it == vertices.end() ) break;
		v1_it++;
        v2_it++;
	}
}


#if defined( TEDDY_INCLUDE_COLDET )
/*virtual*/ int QuadStrip::addToCollisionModel( Teddy::ColDet::CollisionModel3D *collision_model ){
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
/*virtual*/ unsigned long QuadStrip::countCSGFaceElements(){
	unsigned long size = vertices.size();
	return (size-2) / 2;
}



};  //  namespace Models
};  //  namespace Teddy

