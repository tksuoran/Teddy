
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

	$Id: Element.cpp,v 1.6 2002/02/16 12:41:39 tksuoran Exp $
*/


#include "Teddy/Models/Element.h"
#include "Teddy/Models/Vertex.h"
#include "Teddy/SysSupport/Messages.h"
#include "Teddy/SysSupport/StdAlgo.h"
#include "Teddy/Maths/Matrix.h"
using namespace std;
using namespace Teddy::Maths;
using namespace Teddy::SysSupport;


namespace Teddy  {
namespace Models {


const unsigned long Element::EL_HAS_ELEMENT_NORMAL = (1L<< 0L);
const unsigned long Element::EL_USE_ELEMENT_NORMAL = (1L<< 1L);
const unsigned long Element::EL_USE_VERTEX_NORMALS = (1L<< 2L);

const unsigned long Element::VX_HAS_PARENT         = (1L<< 3L);
const unsigned long Element::VX_HAS_VERTEX         = (1L<< 4L);
const unsigned long Element::VX_HAS_NORMAL         = (1L<< 5L);
const unsigned long Element::VX_HAS_COLOR          = (1L<< 6L);
const unsigned long Element::VX_HAS_TEXTURE        = (1L<< 7L);

const unsigned long Element::VX_USE_THIS_VERTEX    = (1L<< 8L);
const unsigned long Element::VX_USE_THIS_NORMAL    = (1L<< 9L);
const unsigned long Element::VX_USE_THIS_COLOR     = (1L<<10L);
const unsigned long Element::VX_USE_THIS_TEXTURE   = (1L<<11L);

const unsigned long Element::VX_USE_PARENT_VERTEX  = (1L<<12L);
const unsigned long Element::VX_USE_PARENT_NORMAL  = (1L<<13L);
const unsigned long Element::VX_USE_PARENT_COLOR   = (1L<<14L);
const unsigned long Element::VX_USE_PARENT_TEXTURE = (1L<<15L);

const unsigned long Element::VX_TRAVERSAL_VISITED  = (1L<<16L);

const unsigned long Element::VX_USE_PARENT_ALL     = 
	Element::VX_USE_PARENT_VERTEX  | 
	Element::VX_USE_PARENT_NORMAL  | 
	Element::VX_USE_PARENT_COLOR   |
	Element::VX_USE_PARENT_TEXTURE;
;


Element::Element( unsigned long options )
:
Options( options ),
normal ( 0, 1, 0 )
{
}


//!  Element destructor
/*virtual*/ Element::~Element(){
}


//!  Debugging information
/*virtual*/ void Element::debug(){
}


//!  Insert a vertex to the face, pointer version
/*virtual*/ void Element::add( Vertex *v ){
	vertices.push_front( v );
	//v->addFace( this );
}


//!  Insert a vertex to the face, component version
/*virtual*/ void Element::add( const float x, const float y, const float z ){
	Vertex *v = new Vertex(x,y,z);
	vertices.push_front( v );
	//v->addFace( this );
}


//!  Insert a vertex to the face - pointer version, reverse order
/*virtual*/ void Element::append( Vertex *v ){
	vertices.push_back( v );
	//v->addFace( this );
}


//!  Insert a vertex to the face - pointer version, reverse order
/*virtual*/ void Element::append( const float x, const float y, const float z ){
	Vertex *v = new Vertex(x,y,z);
	vertices.push_back( v );
	//v->addFace( this );
}


//!  Set element normal
void Element::setNormal( const Vector &normal ){
	enable( EL_HAS_ELEMENT_NORMAL );
	this->normal = normal;
}
void Element::setNormal( const float x, const float y, const float z ){
	enable( EL_HAS_ELEMENT_NORMAL );
	normal = Vector( x, y, z );
}


//!  Set element normal
const Vector &Element::getNormal() const {
	return normal;
}


//!  Return true if element contains spesified vertex
bool Element::contains( const Vertex *v ) const {
	if(  find( vertices.begin(), vertices.end(), v ) != vertices.end()  )
	{
		return true;
	}else{
		return false;
	}
}


/*!
	Reverse order of vertices in Face.
	Remember to update normal as well if needed - that is not done by this.
*/
/*virtual*/ void Element::reverse(){
	vertices.reverse();
}


/*!
	Calculate a normal for Element.
	This requires at least three vertices,
	and the vertices must not be on a single line.
*/
/*virtual*/ void Element::makeNormal(){
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

	float len;

	//  This loop makes sure that we use proper vertices to
	//  get face normal calculated correctly. If we would blindly
	//  take three first vertices, they might be on a straight
	//  line, which is not good for normal calculation
	int max_count = vertices.size() * 3;
	v_i1++;
	if( v_i1 == vertices.end() ) v_i1 = vertices.begin();
	v_i1++;
	if( v_i1 == vertices.end() ) v_i1 = vertices.begin();
	do{
		max_count--;
		if( max_count <=0 ){
			dmsg( M_WARN, "Element had not good vertices for normal calculation" );
			normal = Vector(0,1,0);
			return;
		}	  
		v_i2 = v_i1++;
		if( v_i1 == vertices.end() ) v_i1 = vertices.begin();

		if( v_i2 == vertices.end() ) v_i2 = vertices.begin();
		Vector a  = (*v_i2++)->getVertex();

		if( v_i2 == vertices.end() ) v_i2 = vertices.begin();
		Vector b  = (*v_i2++)->getVertex();

		if( v_i2 == vertices.end() ) v_i2 = vertices.begin(); 
		Vector c  = (*v_i2++)->getVertex();

		Vector ac = a-c; ac.normalize();
		Vector ab = a-b; ab.normalize();
		if( (ac | ab) > 1 - 2*FLT_EPSILON ){
			dmsg( M_MAT, "Trying next vertex-triplet for normal" );
			continue;
		}
		normal    = ac^ab;
		normal.normalize();
		len = normal.magnitude();
	}while( len < 0.9f || len > 1.1f );
	dmsg( 
		M_LWO, 
		"Element normal: %8.4f, %8.4f, %8.4f", 
		normal.v[0],
		normal.v[1],
		normal.v[2]
	);

	enable( EL_HAS_ELEMENT_NORMAL | EL_USE_ELEMENT_NORMAL );
}


/*virtual*/ void Element::makeConvexNormal(){
    makeNormal();
	list<Vertex*>::iterator v_it = vertices.begin();

	Vector a  = (*v_it)->getVertex();
    double dp = a | normal;

	if( dp < 0 ){
		reverse   ();
        makeNormal();
	}
}


//!  Default Element smooth - does not do anything
/*virtual*/ void Element::smooth( float max_smoothing_angle ){
}


//!  Default Element add to collision model - does not do anything
#if defined( TEDDY_INCLUDE_COLDET )
/*virtual*/ int Element::addToCollisionModel( Teddy::ColDet::CollisionModel3D *collision_model ){
	return 0;
}
#endif


void Element::clearTraversal(){
	list<Vertex*>::const_iterator v_it = vertices.begin();
	while( v_it != vertices.end() ){
		Vertex *vertex  = *v_it;
		vertex->disable( VX_TRAVERSAL_VISITED );
		v_it++;
	}
}


double Element::getMaxVector() const {
	double max_len = 0;
	list<Vertex*>::const_iterator v_it = vertices.begin();
	while( v_it != vertices.end() ){
		Vertex *vertex = *v_it;
		double  len    = vertex->getVertex().magnitude();
		if( len > max_len ){
			max_len = len;
		}
		v_it++;
	}
	return max_len;
}


/*!
	\brief Transform all element vertices
*/
/*virtual*/ void Element::transformVertices( const Matrix &m, const Matrix &normal_matrix, const bool rev ){
	list<Vertex*>::iterator v_it = vertices.begin();
	while( v_it != vertices.end() ){
		Vertex *vertex  = *v_it;
		if( vertex->isDisabled(VX_TRAVERSAL_VISITED) ){
			vertex->enable   ( VX_TRAVERSAL_VISITED );
			vertex->transform( m, normal_matrix );
		}
		v_it++;
	}
	if( rev == true ){
        reverse();
    }
	if( isEnabled(EL_HAS_ELEMENT_NORMAL) ){
        normal = normal_matrix * normal;
		normal.normalize();
	}
}


#if 0
//  CSG; default for Elements, override if not equal
/*virtual*/ unsigned long Element::countCSGFaceElements(){
	return 1;
}


//  CSG; default for Elements, override if not equal
/*virtual*/ unsigned long Element::countCSGVertexElements(){
	return vertices.size();
}


/*virtual*/ void Element::initCSGFace( GeometryIterator *gi ){
	gi->face_v_it = vertices.begin();
	gi->face_data = 0;
}


/*virtual*/ void Element::initCSGVertex( GeometryIterator *gi ){
	gi->vertex_v_it = vertices.begin();
	gi->vertex_data = 0;
}


/*virtual*/ bool Element::stepCSGVertex( GeometryIterator *gi ){
	gi->vertex_data++;
	gi->vertex_v_it++;
	if( gi->vertex_v_it == vertices.end() ){
		return false;
	}else{
		return true;
	}
}


/*virtual*/ void Element::fillCSGVertex( GeometryIterator *gi, CSG_IVertex *vertex ){
	Vertex *vx = *(gi->vertex_v_it);
	Vector &v  = vx->getVertex();
	vertex->position[0] = v[0];
	vertex->position[1] = v[1];
	vertex->position[2] = v[2];
}


/*virtual*/ bool stepCSGFace( GeometryIterator *gi ){
	return false;
}


/*virtual*/ void fillCSGFace( GeometryIterator *gi, CSG_IFace *face ){
	return;
}
#endif


};  //  namespace Models
};  //  namespace Teddy

