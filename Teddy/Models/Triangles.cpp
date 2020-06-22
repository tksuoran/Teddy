
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


#include "Teddy/Models/Triangles.h"
#include "Teddy/Models/Vertex.h"
#include "Teddy/PhysicalComponents/Projection.h"
#include "Teddy/SysSupport/Messages.h"
#include "Teddy/SysSupport/StdIO.h"
using namespace Teddy::PhysicalComponents;
using namespace Teddy::SysSupport;


namespace Teddy  {
namespace Models {


//!  Constructor
Triangles::Triangles(){
}


//!  Destructor
/*virtual*/ Triangles::~Triangles(){
}


//!  Draw TriangleFan
/*virtual*/ void Triangles::draw( Projection *p ){

	/*if( isEnabled(EL_USE_ELEMENT_NORMAL|EL_HAS_ELEMENT_NORMAL) ){
		dmsg( M_INIT, "Drawing flat triangles" );

		p->beginTriangles();

		list<Vector*>::const_iterator  n_it  = normals .begin();
		list<Vertex*>::const_iterator  v1_it = vertices.begin();
	 	list<Vertex*>::const_iterator  v2_it = v1_it;
		Vertex                        *v0    = *v1_it++;
		while( n_it != normals.end() && v2_it != vertices.end() ){
            Vector *normal = *n_it++;
			p->normal( *normal );
			v0->draw( p );
			v2_it = v1_it;
			(*v2_it++)->draw( p ); if( v2_it == vertices.end() ){ dmsg( M_WARN, "TriangleFan missing vertices" ); break; }
			(*v2_it++)->draw( p );
			v1_it++;
		}

		p->end();

	}else{*/
		dmsg( M_INIT, "Drawing smoothed triangles" );

		p->beginTriangles();
		list<Vertex*>::const_iterator v_it = vertices.begin();
		while( v_it != vertices.end() ){
			(*v_it)->draw( p );
			v_it++;
		}

		p->end();
	//}

}


//  CSG
/*virtual*/ unsigned long Triangles::countCSGFaceElements(){
	unsigned long size = vertices.size();
	return size / 3;
}


};  //  namespace Models
};  //  namespace Teddy

