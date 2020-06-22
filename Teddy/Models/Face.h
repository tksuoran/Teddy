
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


#ifndef TEDDY__MODELS__FACE__H
#define TEDDY__MODELS__FACE__H


#include "Teddy/Models/Element.h"


namespace Teddy {
	namespace PhysicalComponents {
		class Projection;
	}
}

namespace Teddy  {
namespace Models {


class Vertex;


/*!
	\brief  Ordered collection of vertices to define a polygon

	Face Element is a polygon. The polygon is defined by edge vertices.
	Care must be taken to insert or append (and maintain) vertices 
	in counterclockwise (IIRC) order for backfaceculling to work.
*/
class Face : public Element {
public:
	Face();
	virtual ~Face();

	virtual void  add                ( const float x, const float y, const float z );
	virtual void  add                ( Vertex *v );
	virtual void  append             ( const float x, const float y, const float z );
	virtual void  append             ( Vertex *v );
	virtual void  draw               ( Teddy::PhysicalComponents::Projection *p );
	virtual void  smooth             ( float max_smoothing_angle );
#if defined( TEDDY_INCLUDE_COLDET )
	virtual int   addToCollisionModel( Teddy::ColDet::CollisionModel3D *collision_model );
//	virtual GtsSurface *makeSurface        ();
#endif
#if 0
	virtual bool   stepCSGFace        ( GeometryIterator *gi );
	virtual void   fillCSGFace        ( GeometryIterator *gi, CSG_IFace *face );
#endif
};


};  //  namespace Model
};  //  namespace Teddy


#endif  //  TEDDY__MODELS__FACE__H

