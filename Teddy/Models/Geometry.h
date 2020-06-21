
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


#ifndef TEDDY__MODELS__GEOMETRY__H
#define TEDDY__MODELS__GEOMETRY__H


#if defined( TEDDY_INCLUDE_COLDET )
#	include "Teddy/ColDet/ColDet.h"
#endif
#include "Teddy/Maths/Vector.h"
#include "Teddy/SysSupport/StdList.h"
#if 0
#	include "Teddy/Bsp/CSG_BooleanOps.h"
#endif


//  Forward declarations
namespace Teddy {
	namespace Maths              { class Matrix;     };
	namespace PhysicalComponents { class Projection; };
};
using namespace Teddy::Maths;
using namespace Teddy::PhysicalComponents;


namespace Teddy  {
namespace Models {


class Element;
class Vertex;


#define TEXTURE_AXIS_X 0
#define TEXTURE_AXIS_Y 1
#define TEXTURE_AXIS_Z 2


//!  Geometry maintains modelling data for part of Model. No materials.
class Geometry {
public:
	Geometry();
	virtual ~Geometry();

	void            insert           ( Element    *e );
	virtual void    beginElements    ( Projection *p );
	virtual void    drawElements     ( Projection *p );
	virtual void    endElements      ( Projection *p );
	virtual void    transformVertices( const Matrix &m, const Matrix &normal_matrix, const bool reverse );
	void            clearTraversal   ();

	//  Smoothing and texture mapping
	double          getMaxVector                     ();
	void            smooth                           ( float max_smoothing_angle );
	void            makePlanarTextureCoordinates     ( Vector center, Vector size, int axis );
	void            makeCylindricalTextureCoordinates( Vector center, Vector size, int axis );
	void            makeSphericalTextureCoordinates  ( Vector center, Vector size, int axis );
	void            makeCubicTextureCoordinates      ( Vector center, Vector size );
	void            setTextureCoordinate             ( Element *e, list<Vertex*>::iterator v_it, float u, float v );

#if defined( TEDDY_INCLUDE_COLDET )
	int             addToCollisionModel              ( Teddy::ColDet::CollisionModel3D *collision_model );
#endif

public:
	list<Element*>  elements;

//  This part will be splitted to Graphics::Renderable or something
public:
	void            draw       ( Projection *p );  //!
	void            beginUpdate( Projection *p );  //!
	void            endUpdate  ( Projection *p );  //!

protected:
	unsigned int    gl_list_id;     //!
	bool            dirty;          //!

public:
	static int draw_count;
};


};  //  namespace Models
};  //  namespace Teddy


#endif  //  TEDDY__MODELS__GEOMETRY__H

