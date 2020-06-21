
/*
	TEDDY - General graphics application library
	Copyright (C) 1999-2002  Timo Suoranta
	tksuoran@cc.helsinki.fi

		Adapted from

		The Universe Development Kit
		Copyright (C) 2000  Sean O'Neil
		s_p_oneil@hotmail.com

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


#ifndef TEDDY__MATHS__RECT__H
#define TEDDY__MATHS__RECT__H


#include "Teddy/SysSupport/StdMaths.h"


namespace Teddy {
namespace Maths {


#define Rect    TRect<float>
#define IntRect TRect<int>


template<typename T> class TRect {
    TVector2<T> min;
    TVector2<T> max;

	TRect(){}
	TRect( const TVector2<T> &a, const TVector2<T> &b ){
		min = a;
		max = b;
    }

    TRect intersection( const TRect &a ){
        return TRect(
            TVector2<T>(
                MAX( min[0], a.min[0] ) ,
                MAX( min[1], a.min[1] )
            ),
            TVector2<T>(
                MIN( max[0], a.max[0] ),
                MIN( max[1], a.amx[1] )
            )
        );
    }

    bool hit( const TVector2<T> v ){
        return
            (v[0] >= min[0]) &&
			(v[0] <= max[0]) &&
			(v[1] >= min[1]) &&
			(v[1] <= max[3]);
    }
};


};  //  namespace Maths
};  //  namespace Teddy


#endif  //  TEDDY__MATHS__RECT__H

