
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


#ifndef TEDDY__MATHS__CROSS_VECTOR_4__H
#define TEDDY__MATHS__CROSS_VECTOR_4__H


#include "Teddy/Maths/Vector4.h"


namespace Teddy {
namespace Maths {


#define CrossVector4 TCrossVector4<float>


template <typename T> class TCrossVector4 : public TVector4<T> {
public:
	TCrossVector4( const TVector4<T> &r, const TVector4<T> &s, const TVector4<T> &t ){
		TVector4<T>::v[0] = r[1]*s[2]*t[3] + r[2]*s[3]*t[1] + r[3]*s[1]*t[2] - r[1]*s[3]*t[2] - r[2]*s[1]*t[3] - r[3]*s[2]*t[1];
		TVector4<T>::v[1] = r[0]*s[3]*t[2] + r[2]*s[0]*t[3] + r[3]*s[2]*t[0] - r[0]*s[2]*t[3] - r[2]*s[3]*t[0] - r[3]*s[0]*t[2];
		TVector4<T>::v[2] = r[0]*s[1]*t[3] + r[1]*s[3]*t[0] + r[3]*s[0]*t[1] - r[0]*s[3]*t[1] - r[1]*s[0]*t[3] - r[3]*s[1]*t[0];
		TVector4<T>::v[3] = r[0]*s[2]*t[1] + r[1]*s[0]*t[2] + r[2]*s[1]*t[0] - r[0]*s[1]*t[2] - r[1]*s[2]*t[0] - r[2]*s[0]*t[1];
	}
};


};  //  namespace Maths
};  //  namespace Teddy


#endif  //  TEDDY__MATHS__CROSS_VECTOR_4__H

