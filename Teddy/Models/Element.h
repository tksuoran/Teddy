
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


#ifndef TEDDY__MODELS__ELEMENT__H
#define TEDDY__MODELS__ELEMENT__H


#include "Teddy/Maths/Vector.h"
#include "Teddy/SysSupport/StdList.h"
#include "Teddy/MixIn/Options.h"
#if defined( TEDDY_INCLUDE_COLDET )
# include "Teddy/ColDet/ColDet.h"
#endif
#if 0
# include "Teddy/Bsp/CSG_BooleanOps.h"
#endif


//  Forward declarations
namespace Teddy {
	namespace Maths              { class Matrix;     };
	namespace PhysicalComponents { class Projection; };
};


namespace Teddy  {
namespace Models {


class  Vertex;
class  GeometryIterator;


/*!
	\brief A simple renderable part of Geometry.
*/
class Element : public Teddy::MixIn::Options {
public:
	static const unsigned long EL_HAS_ELEMENT_NORMAL;
	static const unsigned long EL_USE_ELEMENT_NORMAL;
	static const unsigned long EL_USE_VERTEX_NORMALS;

	static const unsigned long VX_HAS_PARENT;        
	static const unsigned long VX_HAS_VERTEX;        
	static const unsigned long VX_HAS_NORMAL;        
	static const unsigned long VX_HAS_COLOR;         
	static const unsigned long VX_HAS_TEXTURE;       

	static const unsigned long VX_USE_THIS_VERTEX;   
	static const unsigned long VX_USE_THIS_NORMAL;   
	static const unsigned long VX_USE_THIS_COLOR;    
	static const unsigned long VX_USE_THIS_TEXTURE;  

	static const unsigned long VX_USE_PARENT_VERTEX; 
	static const unsigned long VX_USE_PARENT_NORMAL; 
	static const unsigned long VX_USE_PARENT_COLOR;  
	static const unsigned long VX_USE_PARENT_TEXTURE;
	 
	static const unsigned long VX_TRAVERSAL_VISITED; 

	static const unsigned long VX_USE_PARENT_ALL;

public:
	Element( unsigned long options = 0 );
	virtual ~Element();

	virtual void        draw        ( Teddy::PhysicalComponents::Projection *p ) = 0;
	virtual void        debug       ();

	virtual void        add         ( const float x, const float y, const float z );
	virtual void        add         ( Vertex *v );
	virtual void        append      ( const float x, const float y, const float z );
	virtual void        append      ( Vertex *v );
	virtual void        reverse     ();
	virtual bool        contains    ( const Vertex *v ) const;

	virtual void        makeNormal  ();
	virtual void        makeConvexNormal();

	virtual void        smooth      ( float max_smoothing_angle );

	void                setNormal   ( const Teddy::Maths::TVector<float> &normal );
	void                setNormal   ( const float x, const float y, const float z );
	const Teddy::Maths::TVector<float> &getNormal   () const;
	virtual double      getMaxVector() const;

	void                clearTraversal     ();
	virtual void        transformVertices  (
		const Teddy::Maths::Matrix &m, 
		const Teddy::Maths::Matrix &normal_matrix, 
		const bool reverse 
	);

#if defined( TEDDY_INCLUDE_COLDET )
	virtual int         addToCollisionModel( Teddy::ColDet::CollisionModel3D *collision_model );
#endif
	//	virtual GtsSurface *makeSurface        (){ return NULL; }

	//  CSG
#if 0
	virtual unsigned long countCSGFaceElements  ();
	virtual unsigned long countCSGVertexElements();
	virtual void          initCSGFace           ( GeometryIterator *gi );
	virtual bool          stepCSGFace           ( GeometryIterator *gi );  //  = 0
	virtual void          fillCSGFace           ( GeometryIterator *gi, CSG_IFace *face );  // = 0
	virtual void          initCSGVertex         ( GeometryIterator *gi );
	virtual bool          stepCSGVertex         ( GeometryIterator *gi );
	virtual void          fillCSGVertex         ( GeometryIterator *gi, CSG_IVertex *vertex );
#endif

	//  vertices -member is public for easy access from Model texture coordinate code
	public:    std::list<Vertex*>            vertices;
	protected: Teddy::Maths::TVector<float>  normal;
};


};  //  namespace Models
};  //  namespace Teddy


#endif  //  TEDDY__MODELS__ELEMENT__H

