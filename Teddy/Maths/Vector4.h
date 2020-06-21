
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

	$Id: Vector4.h,v 1.5 2002/01/17 18:57:37 tksuoran Exp $
*/


#ifndef TEDDY__MATHS__VECTOR_4_H
#define TEDDY__MATHS__VECTOR_4_H


#include "Teddy/Maths/Vector.h"
#include "Teddy/SysSupport/StdMaths.h"


namespace Teddy {
namespace Maths {


/*!
	\class   Vector4
	\author  Sean O'Neil

	This template class implements a simple 4D vector with x, y, z, and w
	coordinates. Like TVector, it is templatized and macros are defined for the
	most common types.
*/
#ifndef SWIG
#define Vector4         TVector4<float>
#define IntVector4      TVector4<int>
#define FloatVector4    TVector4<float>
#define DoubleVector4   TVector4<double>
#define ByteVector4     TVector4<unsigned char>
#define VECTOR4_EPSILON 0.00001
#endif


/**
 *  \brief Template Class: TVector4
 *
 *  This template class implements a simple 4D vector with x, y, z, and w
 *  coordinates. Like TVector, it is templatized and macros are defined for the
 *  most common types.
 */
template <typename T> class TVector4 {
public:
	T v[4];

public:
	//  Constructors
	TVector4(){}

	TVector4( const T a, const T b, const T c, const T d ){
		v[0] = a;
		v[1] = b;
		v[2] = c;
		v[3] = d;
	}

	TVector4( const T            t              ){ *this = t;   }
	TVector4( const T           *pt             ){ *this = pt;  }
	TVector4( const TVector<T>  &vec            ){ *this = vec; }
	TVector4( const TVector<T>  &vec, const T t ){ v[0] = vec.v[0]; v[1] = vec.v[1]; v[2] = vec.v[2]; v[3] = t; }
	TVector4( const TVector4<T> &vec            ){ *this = vec; }

	//  Casting and unary operators
	             operator       T* ()                    { return v; }
	T           &operator       [] ( const int n )       { return v[n]; }
	             operator const T* ()              const { return v; }
	T            operator       [] ( const int n ) const { return v[n]; }
	TVector4<T>  operator        - ()              const { return TVector4<T>(-v[0], -v[1], -v[2], -v[3]); }

	//  Equal and comparison operators
	void operator =( const T            t   )       { v[0] = v[1] = v[2] = v[3] = t; }
	void operator =( const T           *pt  )       { v[0] = pt[0]; v[1] = pt[1]; v[2] = pt[2]; v[3] = pt[3]; }
	void operator =( const TVector <T> &vec )       { v[0] = vec.v[0]; v[1] = vec.v[1]; v[2] = vec.v[2]; v[3] = 0; }
	void operator =( const TVector4<T> &vec )       { v[0] = vec.v[0]; v[1] = vec.v[1]; v[2] = vec.v[2]; v[3] = vec.v[3]; }

	bool operator==( const TVector4<T> &vec ) const {
		return (
			Abs(v[0] - vec.v[0]) <= (T)VECTOR4_EPSILON && 
			Abs(v[1] - vec.v[1]) <= (T)VECTOR4_EPSILON && 
			Abs(v[2] - vec.v[2]) <= (T)VECTOR4_EPSILON && 
			Abs(v[3] - vec.v[3]) <= (T)VECTOR4_EPSILON
		);
	}

	bool operator!=( const TVector4<T> &vec ) const {
		return !(*this == v);
	}

	//  Arithmetic operators (vector with scalar)
	      TVector4<T>  operator+ ( const T t ) const { return TVector4<T>(v[0]+t, v[1]+t, v[2]+t, v[3]+t); }
	      TVector4<T>  operator- ( const T t ) const { return TVector4<T>(v[0]-t, v[1]-t, v[2]-t, v[3]-t); }
	      TVector4<T>  operator* ( const T t ) const { return TVector4<T>(v[0]*t, v[1]*t, v[2]*t, v[3]*t); }
	      TVector4<T>  operator/ ( const T t ) const { return TVector4<T>(v[0]/t, v[1]/t, v[2]/t, v[3]/t); }
	const TVector4<T> &operator+=( const T t )       { v[0] += t; v[1] += t; v[2] += t; v[3] += t; return *this; }
	const TVector4<T> &operator-=( const T t )       { v[0] -= t; v[1] -= t; v[2] -= t; v[3] -= t; return *this; }
	const TVector4<T> &operator*=( const T t )       { v[0] *= t; v[1] *= t; v[2] *= t; v[3] *= t; return *this; }
	const TVector4<T> &operator/=( const T t )       { v[0] /= t; v[1] /= t; v[2] /= t; v[3] /= t; return *this; }

	//  Arithmetic operators (vector with vector)
	      TVector4<T>  operator+ ( const TVector4<T> &vec ) const { return TVector4<T>(v[0]+vec.v[0], v[1]+vec.v[1], v[2]+vec.v[2], v[3]+vec.v[3]); }
	      TVector4<T>  operator- ( const TVector4<T> &vec ) const { return TVector4<T>(v[0]-vec.v[0], v[1]-vec.v[1], v[2]-vec.v[2], v[3]-vec.v[3]); }
	      TVector4<T>  operator* ( const TVector4<T> &vec ) const { return TVector4<T>(v[0]*vec.v[0], v[1]*vec.v[1], v[2]*vec.v[2], v[3]*vec.v[3]); }
	      TVector4<T>  operator/ ( const TVector4<T> &vec ) const { return TVector4<T>(v[0]/vec.v[0], v[1]/vec.v[1], v[2]/vec.v[2], v[3]/vec.v[3]); }
	const TVector4<T> &operator+=( const TVector4<T> &vec )       { v[0] += vec.v[0]; v[1] += vec.v[1]; v[2] += vec.v[2]; v[3] += vec.v[3]; return *this; }
	const TVector4<T> &operator-=( const TVector4<T> &vec )       { v[0] -= vec.v[0]; v[1] -= vec.v[1]; v[2] -= vec.v[2]; v[3] -= vec.v[3]; return *this; }
	const TVector4<T> &operator*=( const TVector4<T> &vec )       { v[0] *= vec.v[0]; v[1] *= vec.v[1]; v[2] *= vec.v[2]; v[3] *= vec.v[3]; return *this; }
	const TVector4<T> &operator/=( const TVector4<T> &vec )       { v[0] /= vec.v[0]; v[1] /= vec.v[1]; v[2] /= vec.v[2]; v[3] /= vec.v[3]; return *this; }

    //  Dot product
	T                  operator| ( const TVector4<T> &vec ) const { return v[0]*vec[0] + v[1]*vec[1] + v[2]*vec[2] + v[3]*vec[3]; }

	//  Magnitude/normalize methods
	T    magnitudeSquared() const { return v[0]*v[0] + v[1]*v[1] + v[2]*v[2] + v[3]*v[3]; }
	T    magnitude       () const { return (T)sqrt( magnitudeSquared() ); }
	void normalize       ()       { *this /= magnitude(); }
};


#ifdef SWIG
%template(Vector4)         TVector4<float>;
%template(IntVector4)      TVector4<int>;
%template(FloatVector4)    TVector4<float>;
%template(DoubleVector4)   TVector4<double>;
#endif


};  //  namespace Maths
};  //  namespace Teddy


#endif  //  TEDDY__MATHS__VECTOR_4_H

