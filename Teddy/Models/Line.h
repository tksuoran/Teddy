
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


#ifndef TEDDY__MODELS__LINE_H
#define TEDDY__MODELS__LINE_H


#include "Teddy/Models/Element.h"


namespace Teddy {
	namespace PhysicalComponents {
		class Projection;
	};
};


namespace Teddy  {
namespace Models {


class Vertex;


/*!
	\brief Line Element

	Line is simple thin line defined by two points.
*/
class Line : public Element {
public:
	Vertex *start_point;
	Vertex *end_point;

	Line( Vertex *v1, Vertex * v2 );
	Line( const Line &l );

	virtual void draw ( Teddy::PhysicalComponents::Projection *p );
	virtual void swap ();

	bool operator==( const Line &l ) const;
	bool operator!=( const Line &l ) const;
};


};  //  namespace Models
};  //  namespace Teddy


#endif  //  TEDDY__MODELS__LINE_H

