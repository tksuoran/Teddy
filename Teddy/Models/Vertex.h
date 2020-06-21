
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


#ifndef TEDDY__MODELS__VERTEX__H
#define TEDDY__MODELS__VERTEX__H


#if defined(_MSC_VER)
#pragma warning(disable:4521)  //  multiple copy constructors defined (!)
#endif


#include "Teddy/Graphics/Color.h"
#include "Teddy/Maths/Vector.h"
#include "Teddy/Maths/Matrix.h"
#include "Teddy/MixIn/Options.h"
#include "Teddy/Models/Element.h"
#include "Teddy/SysSupport/StdList.h"


namespace Teddy  {
namespace Models {


class Face;


/*!
	\brief Defines one point of polygon or line or other element

	Vertex is the most basic primitive for building object models.
	This class attempts to provide flexible vertex by coupling
	possible vertex features into a single class. Additionally
	vertices can be arranged into hieararchy so that one vertex
	can inherit some (or all) features from its parent. By using
	feature inheritance it is possible eg. share the vertex
	coordinate but specify different normal, or different texture
	coordinate.
*/
class Vertex : public Element {
public:
	Vertex();
	Vertex( Vertex *v );
	Vertex( Vertex &v );
	Vertex( const Vertex                       &v );
	Vertex( const Teddy::Maths::TVector<float> &v );
	Vertex( const float x, const float y, const float z );
    virtual ~Vertex();

	virtual double getMaxVector() const;

public:
	virtual void  debug       ();
	virtual void  draw        ( Teddy::PhysicalComponents::Projection *p );
	virtual void  applyColor  ( Teddy::PhysicalComponents::Projection *p );
	virtual void  applyNormal ( Teddy::PhysicalComponents::Projection *p );
	virtual void  applyTexture( Teddy::PhysicalComponents::Projection *p );
	virtual void  applyVertex ( Teddy::PhysicalComponents::Projection *p );

	void          neg         ();
	void          transform   ( const Teddy::Maths::Matrix &m, const Teddy::Maths::Matrix &normal_matrix );
	void          setParent   ( const Vertex &vert    );
	void          setVertex   ( const Teddy::Maths::TVector<float> &vert    );
	void          setVertex   ( const float x, const float y, const float z );
	void          setColor    ( const Teddy::Graphics::Color  &color   );
	void          setNormal   ( const Teddy::Maths::TVector<float> &normal  );
	void          setNormal   ( const float x, const float y, const float z  );
	void          setTexture  ( const Teddy::Maths::TVector<float> &texture );
	void          setTexture  ( const float s, const float t, const float u = 0.0f );
	void          addNormal   ( const Teddy::Maths::TVector<float> &add     );
	void          normNormal  ();
	void          removeNormal();
	Vertex                          *getRoot     ();
	Vertex                          *getParent   ();
	Teddy::Maths   ::TVector<float> &getVertex   ();
	Teddy::Graphics::Color          &getColor    ();
	Teddy::Maths   ::TVector<float> &getNormal   ();
	Teddy::Maths   ::TVector<float> &getTexture  ();
	list<Face*>                     &getFaces    ();
	void                             addFace     ( Face *face );

	//  Basic operations on vertex
	Vertex &operator+=( Vertex &v ){ vert += v.getVertex(); return *this; };
	Vertex &operator-=( Vertex &v ){ vert -= v.getVertex(); return *this; };
	Vertex &operator*=( float   k ){ vert *= k; return *this; };
	Vertex &operator/=( float   k ){ vert /= k; return *this; };

	Vertex &operator+=( const Vertex &v ){ vert += v.vert; return *this; };
	Vertex &operator-=( const Vertex &v ){ vert -= v.vert; return *this; };
//	Vertex &operator*=( const float   k ){ vert *= k; return *this; };
//	Vertex &operator/=( const float   k ){ vert /= k; return *this; };

	Vertex  operator+( Vertex &v ){ return new Vertex(vert+v.vert); };
	Vertex  operator-( Vertex &v ){ return new Vertex(vert-v.vert); };
	Vertex  operator*( float   k ){ return new Vertex(vert*k     ); };
	Vertex  operator/( float   k ){ return new Vertex(vert/k     ); };

	Vertex  operator+( const Vertex &v ){ return new Vertex(vert+v.vert); };
	Vertex  operator-( const Vertex &v ){ return new Vertex(vert-v.vert); };
//	Vertex  operator*( const float   k ){ return new Vertex(vert*k            ); };
//	Vertex  operator/( const float   k ){ return new Vertex(vert/k            ); };

	//  Flip code; FIX if parent vertex is being used, copy it and only change the copy
	void flipX    (){ getVertex().v[0] *= -1; };
	void flipY    (){ getVertex().v[1] *= -1; };
	void flipZ    (){ getVertex().v[2] *= -1; };

	//  Length code; FIX if parent vertex is being used, copy it and only change the copy
	void  normalize(){ getVertex().normalize();        };
	float magnitude(){ return getVertex().magnitude(); };

public:
	list<Face*>  faces;    //!<  Cross-reference

protected:
	Vertex                          *parent;        //!<  Original shared vertex
	Teddy::Maths   ::TVector<float>  vert;          //!<  The actual vertex coordinates
	Teddy::Maths   ::TVector<float>  normal;        //!<  Normal coordinates
	Teddy::Graphics::Color           color;         //!<  Color
	Teddy::Maths   ::TVector<float>  texturecoord;  //!<  Texture coordinates
};


};  //  namespace Models
};  //  namespace Teddy


#endif  //  TEDDY__MODELS__VERTEX__H

