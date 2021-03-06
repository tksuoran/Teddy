
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


#ifndef TEDDY__MODELS__TRIANGLES__H
#define TEDDY__MODELS__TRIANGLES__H


#include "Teddy/Models/Element.h"
#include "Teddy/SysSupport/StdList.h"


namespace Teddy  {
namespace Models {


class Vertex;


class Triangles : public Element {
public:
	Triangles();
	virtual ~Triangles();

	virtual void          draw( Teddy::PhysicalComponents::Projection *p );
	virtual unsigned long countCSGFaceElements  ();

protected:
	std::list<Teddy::Maths::TVector<float>*> normals;
};


};  //  namespace Models
};  //  namespace Teddy


#endif  //  TEDDY__MODELS__TRIANGLES__H

