
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

	$Id: GeometryCollisionModel.cpp,v 1.1 2002/01/11 14:35:02 tksuoran Exp $
*/


#include "Teddy/Models/Element.h"
#include "Teddy/Models/Geometry.h"


namespace Teddy  {
namespace Models {


//!  Constructor
#if defined( TEDDY_INCLUDE_COLDET )
int Geometry::addToCollisionModel( Teddy::ColDet::CollisionModel3D *collision_model ){
	int tris = 0;

	list<Element*>::const_iterator e_it = elements.begin();
	while( e_it!=elements.end() ){
		tris += (*e_it)->addToCollisionModel( collision_model );
		e_it++;
	}
	return tris;
}
#endif


};  //  namespace Models
};  //  namespace Teddy

