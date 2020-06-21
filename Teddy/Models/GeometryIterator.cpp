
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


#include "Teddy/Models/GeometryIterator.h"
#include "Teddy/Models/Element.h"


#if 0

namespace Teddy  {
namespace Models {


GeometryIterator::GeometryIterator( Geometry *g ){
	this->geometry = g;
}


/*virtual*/ GeometryIterator::~GeometryIterator(){
}


unsigned long GeometryIterator::countCSGFaceElements(){
	unsigned long num_csg_faces = 0;
	list<Element*>::const_iterator e_it = geometry->elements.begin();
	while( e_it!=geometry->elements.end() ){
		Element *e = *e_it;
		num_csg_faces += e->countCSGFaceElements();
		e_it++;
	}
	return num_csg_faces;
}


unsigned long GeometryIterator::countCSGVertexElements(){
	unsigned long num_csg_vertices = 0;
	list<Element*>::const_iterator e_it = geometry->elements.begin();
	while( e_it!=geometry->elements.end() ){
		num_csg_vertices += (*e_it)->countCSGFaceElements();
		e_it++;
	}
	return num_csg_vertices;
}


CSG_FaceIteratorDescriptor GeometryIterator::getFaceIterator(){
	CSG_FaceIteratorDescriptor res;
	res.it           = (CSG_IteratorPtr)this;
	res.Done         = GeometryIterator::FaceItDone;
	res.Fill         = GeometryIterator::FaceItFill;
	res.Step         = GeometryIterator::FaceItStep;
	res.Reset        = GeometryIterator::FaceItReset;
	res.num_elements = countCSGFaceElements();
	face_e_it        = geometry->elements.begin();
	Element *e       = *face_e_it;
	e->initCSGFace( this );
	return res;
}


CSG_VertexIteratorDescriptor GeometryIterator::getVertexIterator(){
	CSG_VertexIteratorDescriptor res;
	res.it           = (CSG_IteratorPtr)this;
	res.Done         = GeometryIterator::VertexItDone;
	res.Fill         = GeometryIterator::VertexItFill;
	res.Step         = GeometryIterator::VertexItStep;
	res.Reset        = GeometryIterator::VertexItReset;
	res.num_elements = countCSGVertexElements();
	vertex_e_it      = geometry->elements.begin();
	Element *e       = *vertex_e_it;
	e->initCSGVertex( this );
	return res;
}


int GeometryIterator::faceDone(){
	//  NO-OP
	return 1;
}


void GeometryIterator::faceFill( CSG_IFace *face ){
	Element *e = *face_e_it;
	e->fillCSGFace( this, face );
}


void GeometryIterator::faceStep(){
	Element *e          = *face_e_it;
	bool     e_has_more = e->stepCSGFace( this );
	if( e_has_more == false ){
		face_e_it++;
		e = *face_e_it;
		e->initCSGFace( this );
	}
}


void GeometryIterator::faceReset(){
	face_e_it  =  geometry->elements.begin();
	Element *e = *face_e_it;
	e->initCSGFace( this );
}


int GeometryIterator::vertexDone(){
	//  NO-OP
	return 1;
}


void GeometryIterator::vertexFill( CSG_IVertex *vertex ){
	Element *e = *vertex_e_it;
	e->fillCSGVertex( this, vertex );
}


void GeometryIterator::vertexStep(){
	Element *e          = *vertex_e_it;
	bool     e_has_more = e->stepCSGVertex( this );
	if( e_has_more == false ){
		vertex_e_it++;
		e = *vertex_e_it;
		e->initCSGVertex( this );
	}
}


void GeometryIterator::vertexReset(){
	vertex_e_it =  geometry->elements.begin();
	Element *e  = *vertex_e_it;
	e->initCSGVertex( this );
}


/*static*/ int GeometryIterator::FaceItDone( CSG_IteratorPtr it ){
	GeometryIterator *g = (GeometryIterator *)( it );
	return g->faceDone();
}

/*static*/ void GeometryIterator::FaceItFill( CSG_IteratorPtr it, CSG_IFace *face ){
	GeometryIterator *g = (GeometryIterator *)( it );
	g->faceFill( face );
}

/*static*/ void GeometryIterator::FaceItStep( CSG_IteratorPtr it ){
	GeometryIterator *g = (GeometryIterator *)( it );
	g->faceStep();
}


/*static*/ void GeometryIterator::FaceItReset( CSG_IteratorPtr it ){
	GeometryIterator *g = (GeometryIterator *)( it );
	g->faceReset();
}


/*static*/ int GeometryIterator::VertexItDone( CSG_IteratorPtr it ){
	GeometryIterator *g = (GeometryIterator *)( it );
	return g->vertexDone();
}


/*static*/ void GeometryIterator::VertexItFill( CSG_IteratorPtr it, CSG_IVertex *vertex ){
	GeometryIterator *g = (GeometryIterator *)( it );
	g->vertexFill( vertex );
}


/*static*/ void GeometryIterator::VertexItStep( CSG_IteratorPtr it ){
	GeometryIterator *g = (GeometryIterator *)( it );
	g->vertexStep();
}
/*static*/ void GeometryIterator::VertexItReset( CSG_IteratorPtr it ){
	GeometryIterator *g = (GeometryIterator *)( it );
	g->vertexReset();
}


};  //  namespace Models
};  //  namespace Teddy


#endif

