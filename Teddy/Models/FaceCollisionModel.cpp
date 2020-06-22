
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


#include "Teddy/Models/Face.h"
#if defined( TEDDY_INCLUDE_COLDET )
# include "Teddy/ColDet/ColDet.h"
#endif


namespace Teddy  {
namespace Models {


/*!
	\brief Face add to collision model
	\todo  Tesselate polygons which have move points than three
*/
#if defined( TEDDY_INCLUDE_COLDET )
/*virtual*/ int Face::addToCollisionModel( Teddy::ColDet::CollisionModel3D *collision_model ){
	int tris = 0;
	list<Vertex*>::const_iterator v_it = vertices.begin();

	Vector a  = (*v_it)->getVertex(); v_it++; if( v_it == vertices.end() ) return 0;
	Vector b  = (*v_it)->getVertex(); v_it++;
	while( v_it != vertices.end() ){
		Vector c = (*v_it)->getVertex();
		FloatVector fa = a;
		FloatVector fb = b;
        FloatVector fc = c;
		collision_model->addTriangle( fa, fb, fc );
		a  = b;
		b  = c;
		tris++;
		v_it++;
	}
	return tris;
}
#endif


};  //  namespace Models
};  //  namespace Teddy

