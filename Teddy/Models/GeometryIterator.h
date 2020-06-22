
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


#ifndef TEDDY__MODELS__GEOMETRY_ITERATOR__H
#define TEDDY__MODELS__GEOMETRY_ITERATOR__H


#if 0
#include "Teddy/Models/Geometry.h"
#if 0
# include "Teddy/Bsp/CSG_BooleanOps.h"
#endif


namespace Teddy  {
namespace Models {


class GeometryIterator {
public:
	GeometryIterator( Geometry *g );
	virtual ~GeometryIterator();

	//  CSG
	unsigned long                 countCSGFaceElements  ();
	unsigned long                 countCSGVertexElements();
    CSG_FaceIteratorDescriptor    getFaceIterator       ();
	CSG_VertexIteratorDescriptor  getVertexIterator     ();
	int                           faceDone              ();
	void                          faceFill              ( CSG_IFace *face );
	void                          faceStep              ();
	void	                      faceReset             ();
	int                           vertexDone            ();
	void                          vertexFill            ( CSG_IVertex *vertex );
	void                          vertexStep            ();
	void                          vertexReset           ();
    static int                    FaceItDone            ( CSG_IteratorPtr it );
    static void                   FaceItFill            ( CSG_IteratorPtr it, CSG_IFace *face );
    static void                   FaceItStep            ( CSG_IteratorPtr it );
    static void                   FaceItReset           ( CSG_IteratorPtr it );
    static int                    VertexItDone          ( CSG_IteratorPtr it );
    static void                   VertexItFill          ( CSG_IteratorPtr it, CSG_IVertex *vertex );
    static void                   VertexItStep          ( CSG_IteratorPtr it );
    static void                   VertexItReset         ( CSG_IteratorPtr it );

public:
	Geometry                 *geometry;
	list<Element*>::iterator  face_e_it;
	list<Vertex*> ::iterator  face_v_it;
	unsigned long             face_data;
	list<Element*>::iterator  vertex_e_it;
	list<Vertex*> ::iterator  vertex_v_it;
	unsigned long             vertex_data;
};


};  //  namespace Models
};  //  namespace Teddy

#endif
#endif  //  TEDDY__MODELS__GEOMETRY_ITERATOR__H

