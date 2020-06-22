
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


#ifndef TEDDY__MODELS__MODEL__H
#define TEDDY__MODELS__MODEL__H


#include "Teddy/Maths/Matrix.h"
#include "Teddy/Maths/Quaternion.h"
#include "Teddy/Maths/Vector.h"
#include "Teddy/MixIn/Mutex.h"
#include "Teddy/MixIn/Named.h"
#include "Teddy/MixIn/Options.h"
#include "Teddy/SysSupport/StdList.h"
#include "Teddy/SysSupport/StdSDL.h"
#include "Teddy/SysSupport/Types.h"


//  Forward declarations
namespace Teddy {
	namespace Materials          { class Material;   };
	namespace PhysicalComponents { class Projection; };
};


namespace Teddy  {
namespace Models {


class Geometry;
class Element;
class Vertex;


/*!
	This is the base class for all three-dimensional objects
	which can be part of scene.
*/
class Model
: 
    public Teddy::MixIn::Mutex,
    public Teddy::MixIn::Named,
    public Teddy::MixIn::Options
{
public:
	static const unsigned long OPT_VISIBLE;
	static const unsigned long OPT_RECURS_MATERIAL;
	
public:
	//	Constructors
	Model( std::string name, Model *shape = NULL );

    Teddy::Maths::Matrix                getLocalToWorldMatrix() const;
	Teddy::Maths::Matrix                getWorldToLocalMatrix() const;
	Teddy::Maths::Matrix                getViewMatrix        () const;
	Teddy::Maths::Matrix                getModelMatrix       ( Model *camera ) const;
	Teddy::Maths::Matrix                getScaledModelMatrix ( Model *camera ) const;

    void                                doMaterial ( Teddy::PhysicalComponents::Projection *p, Model *parent = NULL );
	virtual void                        draw       ( Teddy::PhysicalComponents::Projection *p, Model *parent = NULL );

	list<Model*>                       &getChildren();
	void                                add        ( Model *child  );
	void                                remove     ( Model *child  );
	Geometry                           *getGeometry() const;
	void                                setGeometry( Geometry *g );
	virtual Teddy::Materials::Material *getMaterial() const;
	void                                setMaterial( Teddy::Materials::Material *m, bool recursive = false );

	void                                applyMaterial    ( const Teddy::PhysicalComponents::Projection &p, Teddy::Materials::Material *material );
	void                                setClipRadius    ( const double clip_radius );
	void                                setupClipRadius  ();
	double                              getClipRadius    () const;
	void                                add              ( Element *e );
    void                                addTri           ( Vertex *a, Vertex *b, Vertex *c );
    void                                addQuad          ( Vertex *a, Vertex *b, Vertex *c, Vertex *d );
    void                                addPenta         ( Vertex *a, Vertex *b, Vertex *c, Vertex *d, Vertex *e );
    void                                addHexa          ( Vertex *a, Vertex *b, Vertex *c, Vertex *d, Vertex *e, Vertex *f );
    void                                addOcta          ( Vertex *a, Vertex *b, Vertex *c, Vertex *d, Vertex *e, Vertex *f, Vertex *g, Vertex *h );
    void                                transformVertices( const Teddy::Maths::Matrix &m );
	void                                transformVertices( const Teddy::Maths::Matrix &m, const Teddy::Maths::Matrix &normal_matrix, const bool reverse );
	void                                clearTraversal   ();
	void                                truncate         ();

	Teddy::Maths::Quaternion           &getAttitude    ();
	void                                copyAttitude   ( const Model &other );
	Teddy::Maths::TVector<double>       vectorTo       ( const Model &other ) const;
	double                              distanceTo     ( const Model &other ) const;
    double                              distanceTo     ( const Teddy::Maths::TVector<double> &pos ) const;
	void                                setPosition    ( const double x, const double y, const double z );
	void                                setPosition    ( const Teddy::Maths::TVector<double> &v );
	Teddy::Maths::TVector<double>       getPosition    () const;
	void                                transform      ( const Teddy::Maths::Matrix &m );
	void                                translate      ( const Teddy::Maths::TVector<double> &v );
	//void                              translate      ( const double x, const double y, const double z );
	void                                roll           ( const double radians );
	void                                pitch          ( const double radians );
	void                                heading        ( const double radians );
	void                                foward         ( const double l );

protected:
	Teddy::Maths::Quaternion       attitude;     //!<  Attitude (orientation)
	Teddy::Maths::TVector<double>  position;     //!<  Position (location)
	double                         clip_radius;  //!<  For view volume clipping
	list<Model*>                   children;     //!<  Hierarchial
	Geometry                      *geometry;     //!<  Geometry
	Teddy::Materials::Material    *material;     //!<  Material property for this Model

protected:
	static Teddy::Materials::Material *default_material;
};


};  //  namespace Models
};  //  namespace Teddy


#endif  //  TEDDY__MODELS__MODEL__H

