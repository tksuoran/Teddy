
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


#include "Teddy/Materials/Material.h"
#include "Teddy/Models/Model.h"
#include "Teddy/Models/Face.h"
#include "Teddy/Models/Geometry.h"
#include "Teddy/PhysicalComponents/Projection.h"
#include "Teddy/Scenes/Camera.h"
#include "Teddy/SysSupport/StdMaths.h"
#include "Teddy/SysSupport/StdSDL.h"
#include "Teddy/SysSupport/StdIO.h"
using namespace Teddy::Graphics;
using namespace Teddy::Materials;
using namespace Teddy::Scenes;


namespace Teddy  {
namespace Models {


const unsigned long Model::OPT_VISIBLE         = (1ul<<1ul);
const unsigned long Model::OPT_RECURS_MATERIAL = (1ul<<2ul);


/*!
	\brief Create new Model
	\param name Name for the new Model
	\param mesh Model defining shape for the new Model
*/
Model::Model( std::string name, Model *shape )
:
Named      ( name    ),
Options    ( OPT_VISIBLE /*| OPT_RECURS_MATERIAL*/ ),
attitude   ( 0.0f,0.0f,0.0f,1.0f ),
position   ( 0.0, 0.0 ,0.0       ),
clip_radius( 0.0f    ),
geometry   ( NULL    ),
material   ( NULL    )
{
	if( shape != NULL ){
		add( shape );
		setClipRadius( shape->getClipRadius() );
	}
}


//!  Add child Model
void Model::add( Model *child ){
	children.push_back( child );
}


/*!
	\brief Insert Element to Model
	\param e Element which is added to this Model
*/
void Model::add( Element *e ){
	if( geometry == NULL ){
		geometry = new Geometry();
	}
	geometry->insert( e );
}


//!  Remove child Model
void Model::remove( Model *child ){
	children.remove( child );
}


/*!
	\brief Return the effective material used for this Model
	\note Each Model may set material, but it does not have to set it.

	If Model has not set material, material of the Model is used when
	drawing. In such case this method returns the material of the Model.
*/
/*virtual*/ Material *Model::getMaterial() const {
	return material;
}


/*!
	\brief Set Model Material
	\param m Material for this Model
*/
void Model::setMaterial( Material *m, bool recursive ){
	this->material = m;
	if( recursive ){
		list<Model*>::iterator m_it;
		m_it = children.begin();
		while( m_it != children.end() ){
			(*m_it)->setMaterial( m, recursive );
			m_it++;
		}
	}
}



/*!
	\brief Transform all Model vertices
	\param m Transformation
*/
void Model::transformVertices( const Matrix &m ){
	// cleartraversals
	// normaalit inversion transpoosilla
	Matrix normal_matrix = m;
	normal_matrix.invert   ();
	normal_matrix.transpose();
	Vector x       = m.get3Row( 0 );
	Vector y       = m.get3Row( 1 );
	Vector z       = m.get3Row( 2 );
	Vector z2      = x^y;
	double dp      = z | z2;
	bool   reverse = false;

	if( dp < 0 ){
        reverse = true;
	}

//	clearTraversal();
	transformVertices( m, normal_matrix, reverse );
}


void Model::clearTraversal(){
	if( geometry != NULL ){
		geometry->clearTraversal();
	}

	list<Model*>::iterator m_it;
	m_it = children.begin();
	while( m_it != children.end() ){
		(*m_it)->clearTraversal();
		m_it++;
	}
}

void Model::transformVertices( const Matrix &m, const Matrix &normal_matrix, const bool reverse ){
	clearTraversal();
	if( geometry != NULL ){
		geometry->transformVertices( m, normal_matrix, reverse );
	}

	list<Model*>::iterator m_it;
	m_it = children.begin();
	while( m_it != children.end() ){
		(*m_it)->transformVertices( m, normal_matrix, reverse );
		m_it++;
	}
	setupClipRadius();
}


//  FIX this is not correct
//  should consider offset of children
//  because of this children are culled individually anyway
//  and hierarchial culling is not used
void Model::setupClipRadius(){
	double max_len = geometry != NULL ? geometry->getMaxVector() : 0;

	list<Model*>::iterator m_it;
	m_it = children.begin();
	while( m_it != children.end() ){
		Model *child = (*m_it);
		child->setupClipRadius();
		double len = child->getClipRadius();
		if( len>max_len ) max_len = len;
		m_it++;
	}
	setClipRadius( max_len );
}


void Model::setClipRadius( const double clip_radius ){
	this->clip_radius = clip_radius; 
}


double Model::getClipRadius() const {
	return clip_radius; 
}


void Model::setGeometry( Geometry *geometry ){
	this->geometry = geometry;
}


Geometry *Model::getGeometry() const {
	return geometry;
}


list<Model*> &Model::getChildren(){
	return children;
}


void Model::addTri( Vertex *a, Vertex *b, Vertex *c ){
	Face *face = new Face();
    face->add( a );
    face->add( b );
	face->add( c );
    face->makeConvexNormal();
    add( face );
}


void Model::addQuad( Vertex *a, Vertex *b, Vertex *c, Vertex *d ){
	Face *face = new Face();
    face->add( a );
    face->add( b );
	face->add( c );
	face->add( d );
    face->makeConvexNormal();
    add( face );
}


void Model::addPenta( Vertex *a, Vertex *b, Vertex *c, Vertex *d, Vertex *e ){
	Face *face = new Face();
    face->add( a );
    face->add( b );
	face->add( c );
	face->add( d );
	face->add( e );
    face->makeConvexNormal();
    add( face );
}


void Model::addHexa( Vertex *a, Vertex *b, Vertex *c, Vertex *d, Vertex *e, Vertex *f ){
	Face *face = new Face();
    face->add( a );
    face->add( b );
	face->add( c );
	face->add( d );
	face->add( e );
	face->add( f );
    face->makeConvexNormal();
    add( face );
}


void Model::addOcta( Vertex *a, Vertex *b, Vertex *c, Vertex *d, Vertex *e, Vertex *f, Vertex *g, Vertex *h ){
	Face *face = new Face();
    face->add( a );
    face->add( b );
	face->add( c );
	face->add( d );
	face->add( e );
	face->add( f );
	face->add( g );
	face->add( h );
    face->makeConvexNormal();
    add( face );
}


};	//	namespace Models
};  //  namespace Teddy

