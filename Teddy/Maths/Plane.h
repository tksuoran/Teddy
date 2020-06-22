
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


#ifndef TEDDY__MATHS__PLANE_H
#define TEDDY__MATHS__PLANE_H


#include "Teddy/Maths/Vector.h"
#include "Teddy/Maths/Vector4.h"


namespace Teddy {
namespace Maths {


//!  Plane
class Plane : public Vector4 {
public:
	Plane(){}
	Plane( const float a, const float b, const float c, const float d ):Vector4(a,b,c,d){}

	void    neg        ();
	double  distance   ( const Vector &p ) const;
	Plane  &operator=  ( const Vector &v );
	Plane  &operator=  ( const Vector4 &v );
	Vector  getNormal  () const;
	double  getConstant() const;
};


};  //  namespace Maths
};  //  namespace Teddy


#endif  //  TEDDY__MATHS__PLANE_H

