
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


#include "Teddy/PhysicalComponents/Projection.h"
#include "Teddy/Models/Vertex.h"
#include "Teddy/Models/Face.h"
#include "Teddy/SysSupport/Messages.h"
using namespace Teddy::PhysicalComponents;
using namespace Teddy::SysSupport;


namespace Teddy  {
namespace Models {


//!  Default constructor
Vertex::Vertex()
:
Element     ( 0          ),
parent      ( NULL       ),
vert        ( 0, 0, 0    ),
normal      ( 0, 1, 0    ),
color       ( 1, 1, 1, 1 ),
texturecoord( 0, 0, 0    )
{
}


/*!
	Vertex - Vertex Inheritance constructor
	Notice that Face cross-reference -list is not copied
	Notice how Parent is set
*/
Vertex::Vertex( Vertex *v )
:
Element     ( VX_HAS_PARENT | VX_USE_PARENT_ALL ),
parent      ( v          ),
vert        ( 0, 0, 0    ),
normal      ( 0, 1, 0    ),
color       ( 1, 1, 1, 1 ),
texturecoord( 0, 0, 0    )
{
}


/*!
	Vertex - Vertex copy constructor
	Notice that Face cross-reference -list is not copied
	Notice how Parent is set
	Notice that accessor methods are not used for some members
*/
Vertex::Vertex( Vertex &v )
:
Element     ( v.getOptions() ),
parent      ( v.getParent () ),
vert        ( v.vert         ),
normal      ( v.normal       ),
color       ( v.color        ),
texturecoord( v.texturecoord )
{
}


//!  Vertex - Vector Copy-constructor
Vertex::Vertex( const Vector &v )
:
Element     ( VX_HAS_VERTEX | VX_USE_THIS_VERTEX ),
parent      ( NULL       ),
vert        ( v          ),
normal      ( 0, 1, 0    ),
color       ( 1, 1, 1, 1 ),
texturecoord( 0, 0, 0    )
{
}


//!  Vertex Component constructor
Vertex::Vertex( const float x, const float y, const float z)
:
Element     ( VX_HAS_VERTEX | VX_USE_THIS_VERTEX ),
parent      ( NULL       ),
vert        ( x, y, z    ),
normal      ( 0, 1, 0    ),
color       ( 1, 1, 1, 1 ),
texturecoord( 0, 0, 0    )
{
}


/*virtual*/ Vertex::~Vertex(){
}


//!  Flip the vertex. Notice that normal is not changed by this routine
void Vertex::neg(){
	vert.v[0] = -vert.v[0];
	vert.v[1] = -vert.v[1];
	vert.v[2] = -vert.v[2];
}


//!  Transform the vertex
void Vertex::transform( const Matrix &m, const Matrix &normal_matrix ){
	vert   = m             * vert;
	normal = normal_matrix * normal;
    normal.normalize();
}


//!  Set color to this vertex
void Vertex::setColor( const Color &color ){
	enable ( VX_USE_THIS_COLOR | VX_HAS_COLOR );
	disable( VX_USE_PARENT_COLOR );
	this->color = color;
}


//!  Set normal to this vertex
void Vertex::setNormal( const Vector &normal ){
	enable ( VX_USE_THIS_NORMAL | VX_HAS_NORMAL );
	disable( VX_USE_PARENT_NORMAL );
	this->normal = normal;
}
void Vertex::setNormal( const float x, const float y, const float z ){
	enable ( VX_USE_THIS_NORMAL | VX_HAS_NORMAL );
	disable( VX_USE_PARENT_NORMAL );
	normal = Vector( x, y, z );;
}


//!  Set vertex coordinate to this vertex
void Vertex::setVertex( const Vector &vertex ){
	enable ( VX_USE_THIS_VERTEX | VX_HAS_VERTEX );
	disable( VX_USE_PARENT_VERTEX );
	this->vert = vertex;
}
void Vertex::setVertex( const float x, const float y, const float z ){
	enable ( VX_USE_THIS_VERTEX | VX_HAS_VERTEX );
	disable( VX_USE_PARENT_VERTEX );
	vert = Vector( x, y, z );
}


//!  Add normal to this vertex
void Vertex::addNormal( const Vector &add ){
	this->normal += add;
}


//!  Normalize normal
void Vertex::normNormal(){
	if( isDisabled(VX_HAS_NORMAL) ){
		emsg( M_VERT, "Vertex has no normal which to normalize" );
		return;
	}

	enable ( VX_USE_THIS_NORMAL | VX_HAS_NORMAL );
	disable( VX_USE_PARENT_NORMAL );
	normal.normalize();

	//  Check that normalize worked
	float len = normal.magnitude();
	if( len > 1.1 || len < 0.9 ){
		emsg( M_VERT, "Bad normal" );
	}
}


//!  Set vertex texture coordinate
void Vertex::setTexture( const Vector &texture ){
	enable ( VX_USE_THIS_TEXTURE | VX_HAS_TEXTURE );
	disable( VX_USE_PARENT_TEXTURE );
	this->texturecoord  = texture;
}
void Vertex::setTexture( const float s, const float t, const float u ){
	enable ( VX_USE_THIS_TEXTURE | VX_HAS_TEXTURE );
	disable( VX_USE_PARENT_TEXTURE );
	texturecoord = Vector( s, t, u );
}


//!  Sharing lists are only stored in the root
void Vertex::addFace( Face *face ){
	getRoot()->faces.push_back( face );
}


//!  Return the share list of this vertex
list<Face*> &Vertex::getFaces(){
	return getRoot()->faces;
}


//!  Return the effective ancestor of this vertex. Recursively seeks for parent.
Vertex *Vertex::getRoot(){
	Vertex *p = getParent();
	if( p==NULL ){
		return this;
	}else{
		return p->getRoot();
	}
}


//!  Return the effective parent of this vertex
Vertex *Vertex::getParent(){
	return this->parent;
}


//!  Return the effective vertex position of this vertex
Vector &Vertex::getVertex(){
	if( isEnabled(VX_USE_THIS_VERTEX|VX_HAS_VERTEX) ){
		return this->vert;
	}else if( isEnabled(VX_USE_PARENT_VERTEX|VX_HAS_PARENT) ){
		return parent->getVertex();
	}else{
		dmsg( M_VERT, "Vertex not found in vertex" );
		return this->vert;
	}
}

//!  Return the effective vertex color
Color &Vertex::getColor(){
	if( isEnabled(VX_USE_THIS_COLOR|VX_HAS_COLOR) ){
		return this->color;
	}else if( isEnabled(VX_USE_PARENT_COLOR|VX_HAS_PARENT) ){
		return parent->getColor();
	}else{
		emsg( M_VERT, "Color not found in vertex" );
		return this->color;
	}
}


//!  Return the effective vertex normal coordinate
Vector &Vertex::getNormal(){
	if( isEnabled(VX_USE_THIS_NORMAL|VX_HAS_NORMAL) ){
		return this->normal;
	}else if( isEnabled(VX_USE_PARENT_NORMAL|VX_HAS_PARENT) ){
		return parent->getNormal();
	}else{
		emsg( M_VERT, "Normal not found in vertex" );
		return this->normal;
	}
}


//!  Return vertex texture coordinate
Vector &Vertex::getTexture(){
	if( isEnabled(VX_USE_THIS_TEXTURE|VX_HAS_TEXTURE) ){
		return this->texturecoord;
	}else if( isEnabled(VX_USE_PARENT_TEXTURE|VX_HAS_PARENT) ){
		return parent->getTexture();
	}else{
		emsg( M_VERT, "Texture coordinates not found in Vertex" );
		return this->texturecoord;
	}
}


/*!
	Draw.

	Since any feature may or may not be inherited
	from parent, all settings are handled in sub-methods.

	Does NOT include begin(), so Vertex can be used with
	any OpenGL primitives, but needs begin() outside.
*/
void Vertex::draw( Projection *p ){
	applyColor  ( p );
	applyNormal ( p );
	applyTexture( p );
	applyVertex ( p );
}


/*virtual*/ void Vertex::applyColor( Projection *p ){
	if( isEnabled(VX_USE_THIS_COLOR|VX_HAS_COLOR) ){
		p->color( color );
	}else if( isEnabled(VX_USE_PARENT_COLOR|VX_HAS_PARENT) ){
//		vert_debug_msg( "Using parent color" );
		parent->applyColor( p );
	}else{
//		vert_debug_msg( "This vertex has no color" );
	}
}


/*virtual*/ void Vertex::applyNormal( Projection *p ){
	if( isEnabled(VX_USE_THIS_NORMAL|VX_HAS_NORMAL) ){
		p->normal( normal );
	}else if( isEnabled(VX_USE_PARENT_NORMAL|VX_HAS_PARENT) ){
		dmsg( M_VERT, "Using parent normal" );
		parent->applyNormal( p );
	}else{
		debug();
		dmsg( M_VERT, "This vertex has no normal" );
	}
}


/*virtual*/ void Vertex::applyTexture( Projection *p ){
	if( isEnabled(VX_USE_THIS_TEXTURE|VX_HAS_TEXTURE) ){
		p->texture( texturecoord );
	}else if( isEnabled(VX_USE_PARENT_TEXTURE|VX_HAS_PARENT) ){
//		vert_debug_msg( "Using parent texture" );
		parent->applyTexture( p );
	}else{
//		vert_debug_msg( "This vertex has no texture" );
	}
}


/*virtual*/ void Vertex::applyVertex( Projection *p ){
	if( isEnabled(VX_USE_THIS_VERTEX|VX_HAS_VERTEX) ){
		p->vertex( vert );
	}else if( isEnabled(VX_USE_PARENT_VERTEX|VX_HAS_PARENT) ){
		//vert_debug_msg( "Using parent vertex" );
		parent->applyVertex( p );
	}else{
//		debug();
//		dmsg( M_VERT, "This vertex has no vertex" );
	}
}


/*virtual*/ void Vertex::debug(){
	if( isEnabled(VX_HAS_PARENT        ) ) dmsg( M_VERT, "VX_HAS_PARENT        ");
	if( isEnabled(VX_HAS_VERTEX        ) ) dmsg( M_VERT, "VX_HAS_VERTEX        ");
	if( isEnabled(VX_HAS_NORMAL        ) ) dmsg( M_VERT, "VX_HAS_NORMAL        ");
	if( isEnabled(VX_HAS_COLOR         ) ) dmsg( M_VERT, "VX_HAS_COLOR         ");
	if( isEnabled(VX_HAS_TEXTURE       ) ) dmsg( M_VERT, "VX_HAS_TEXTURE       ");

	if( isEnabled(VX_USE_THIS_VERTEX   ) ) dmsg( M_VERT, "VX_USE_THIS_VERTEX   ");
	if( isEnabled(VX_USE_THIS_NORMAL   ) ) dmsg( M_VERT, "VX_USE_THIS_NORMAL   ");
	if( isEnabled(VX_USE_THIS_COLOR    ) ) dmsg( M_VERT, "VX_USE_THIS_COLOR    ");
	if( isEnabled(VX_USE_THIS_TEXTURE  ) ) dmsg( M_VERT, "VX_USE_THIS_TEXTURE  ");

	if( isEnabled(VX_USE_PARENT_VERTEX ) ) dmsg( M_VERT, "VX_USE_PARENT_VERTEX ");
	if( isEnabled(VX_USE_PARENT_NORMAL ) ) dmsg( M_VERT, "VX_USE_PARENT_NORMAL ");
	if( isEnabled(VX_USE_PARENT_COLOR  ) ) dmsg( M_VERT, "VX_USE_PARENT_COLOR  ");
	if( isEnabled(VX_USE_PARENT_TEXTURE) ) dmsg( M_VERT, "VX_USE_PARENT_TEXTURE");
}


/*virtual*/ double Vertex::getMaxVector() const {
	return vert.magnitude();
}


};  //  namespace Models
};  //  namespace Teddy

