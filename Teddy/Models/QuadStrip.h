
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

	$Id: QuadStrip.h,v 1.4 2002/01/11 14:35:03 tksuoran Exp $
*/


#ifndef TEDDY__MODELS__QUAD_STRIP_H
#define TEDDY__MODELS__QUAD_STRIP_H


#include "Teddy/Models/Element.h"
#include "Teddy/SysSupport/StdList.h"

namespace Teddy {
	namespace PhysicalComponents {
		class Projection;
	};
};

namespace Teddy  {
namespace Models {


class Vertex;


//! Q uadStrip Element builds up a quad strip from its vertices.
class QuadStrip : public Element {
public:
	QuadStrip();
	virtual ~QuadStrip();

	virtual void  draw               ( Teddy::PhysicalComponents::Projection *p );
    virtual void  reverse            ();
#if defined( TEDDY_INCLUDE_COLDET )
	virtual int   addToCollisionModel( Teddy::ColDet::CollisionModel3D *collision_model );
#endif
	virtual void  makeNormal         ();
	virtual unsigned long countCSGFaceElements  ();

protected:
	std::list<Teddy::Maths::TVector<float>*> normals;
};


};  //  namespace Models
};  //  namespace Teddy


#endif  //  TEDDY__MODELS__QUAD_STRIP_H

