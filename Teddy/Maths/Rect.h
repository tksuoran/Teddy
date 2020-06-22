
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


#ifndef TEDDY__MATHS__RECT__H
#define TEDDY__MATHS__RECT__H


#include "Teddy/Maths/Vector2.h"
#include "Teddy/SysSupport/StdMaths.h"
#include "Teddy/SysSupport/StdIO.h"


namespace Teddy {
namespace Maths {


#ifndef SWIG
#define Rect    TRect<float>
#define IntRect TRect<int>
#endif


template<typename T> class TRect {
public:
    TVector2<T> min;
    TVector2<T> max;

	TRect(){}
/*	TRect( const TVector2<T> &a, const TVector2<T> &b ){
		min = a;
		max = b;
    }*/
	TRect( const TVector2<int> &a, const TVector2<int> &b ){
		min = TVector2<T>(a);
		max = TVector2<T>(b);
   }
	TRect( const TVector2<float> &a, const TVector2<float> &b ){
		min = TVector2<T>(a);
		max = TVector2<T>(b);
    }
	TRect( const TVector2<double> &a, const TVector2<double> &b ){
		min = TVector2<T>(a);
		max = TVector2<T>(b);
    }
	TRect( const TRect<int> &r ){
		min = TVector2<T>(r.min);
		max = TVector2<T>(r.max);
    }
	TRect( const TRect<float> &r ){
		min = TVector2<T>(r.min);
		max = TVector2<T>(r.max);
    }
	TRect( const TRect<double> &r ){
		min = TVector2<T>(r.min);
		max = TVector2<T>(r.max);
    }

    TVector2<T> getSize() const {
		TVector2<T> ret_val = TVector2<T>(
			max[0] - min[0],
			max[1] - min[1]
		);
        return ret_val;
    }

    T getArea() const {
        return (max[0] - min[0] + 1) * (max[1] - min[1] + 1);
    }


    void setSize( const TVector2<T> &size ){
        max = min + size - TVector2<T>(1,1);
    }

    const TRect &intersect( const TRect &a ){
        min = TVector2<T>( MAX( min[0], a.min[0] ), MAX( min[1], a.min[1] ) );
        max = TVector2<T>( MIN( max[0], a.max[0] ), MIN( max[1], a.max[1] ) );
        return *this;
    }

    TRect grow( const TVector2<T> v ){
        return TRect( min - v, max + v );
    }

    TRect shrink( const TVector2<T> v ){
        return TRect( min + v, max - v );
    }

    bool hit( const TVector2<T> v ) const {
        return
            (v[0] >= min[0]) &&
			(v[0] <= max[0]) &&
			(v[1] >= min[1]) &&
			(v[1] <= max[1]);
    }

    const TRect &setPosition( const TVector2<T> &pos ){
        move( pos - min );
        return *this;
    }

    //  Translation
    const TRect &move( const TVector2<T> &v ){ min += v; max += v; return *this; }
    const TRect &operator +=( const TVector2<T> &v )       { min += v; max += v; return *this; }
          TRect  operator + ( const TVector2<T> &v ) const { return TRect( min+v, max+v ); }
    const TRect &operator -=( const TVector2<T> &v )       { min -= v; max -= v; }
          TRect  operator - ( const TVector2<T> &v ) const { return TRect( min-v, max-v ); }
};


#ifdef SWIG
%template(Rect)            TRect<float>;
%template(IntRect)         TRect<int>;
#endif


};  //  namespace Maths
};  //  namespace Teddy


#endif  //  TEDDY__MATHS__RECT__H

