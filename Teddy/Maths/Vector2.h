
/*
	TEDDY - General graphics application library
	Copyright (C) 1999-2020  Timo Suoranta
	tksuoran@gmail.com

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
*/


#ifndef TEDDY__MATHS__VECTOR_2__H
#define TEDDY__MATHS__VECTOR_2__H


#include "Teddy/SysSupport/StdMaths.h"
#include "Teddy/SysSupport/StdIO.h"


namespace Teddy {
namespace Maths {


/*
	\class   Vector
	\author  Sean O'Neil

	This template class implements a simple 2D vector with v[0] and v[1] coordinates.
	Several functions and operators are defined to make working with vectors easier,
	and because it's templatized, any numeric type can be used with it. Macros are
	defined for the most common types.
*/
#ifndef SWIG
#define Vector2        TVector2<float>
#define DoubleVector2  TVector2<double>
#define IntVector2     TVector2<int>

#ifndef VECTOR_EPSILON
#define VECTOR_EPSILON 0.00001
#endif
#endif


/*!
	\brief   Template Class TVector2
	\author  Sean O'Neil

	This template class implements a simple 2D vector with v[0] and v[1] coordinates.
	Several functions and operators are defined to make working with vectors easier,
	and because it's templatized, any numeric type can be used with it. Macros are
	defined for the most common types.
*/
template <typename T> class TVector2
{
public:
	T v[2];

	// Constructors
	TVector2(){}
	TVector2( const int a, const int b ){
		v[0] = T(a);
		v[1] = T(b);
    }
	TVector2( const float a, const float b ){
		v[0] = T(a);
		v[1] = T(b);
    }
	TVector2( const double a, const double b ){
		v[0] = T(a);
		v[1] = T(b);
    }

    TVector2( const TVector2<double> &v  ){ this->v[0] = (T)(v.v[0]); this->v[1] = (T)(v.v[1]); }
    TVector2( const TVector2<float>  &v  ){ this->v[0] = (T)(v.v[0]); this->v[1] = (T)(v.v[1]); }
    TVector2( const TVector2<int>    &v  ){ this->v[0] = (T)(v.v[0]); this->v[1] = (T)(v.v[1]); }

	// Casting and unary operators
	T           &operator               [] ( const int n )       { 
		if( n>1 ){
			printf( "Vector2::operator[] ERROR\n" );
		}
		return (&v[0])[n]; 
	}
	T            operator               [] ( const int n ) const { 
		if( n>1 ){
			printf( "Vector2::operator[] ERROR\n" );
		}
		return (&v[0])[n]; 
	}
	TVector2<T>  operator                - ()              const { return TVector2<T>(-v[0], -v[1]); }

	// Equal and comparison operators
//	void operator= ( const T            t   )       { v[0] = v[1] = t; }
//	void operator= ( const T           *pt  )       { v[0] = pt[0]; v[1] = pt[1]; }
	void operator= ( const TVector2<T> &vec )       { v[0] = vec.v[0]; v[1] = vec.v[1]; }
	bool operator==(       TVector2<T> &vec ) const { return (v[0] == vec.v[0]) && (v[1] == vec.v[1]); }
	bool operator!=(       TVector2<T> &vec ) const { return !(*this == vec); }

	// Arithmetic operators (vector with scalar)
	      TVector2<T>  operator+ ( const T t ) const { return TVector2<T>(v[0]+t, v[1]+t); }
	      TVector2<T>  operator- ( const T t ) const { return TVector2<T>(v[0]-t, v[1]-t); }
	      TVector2<T>  operator* ( const T t ) const { return TVector2<T>(v[0]*t, v[1]*t); }
	      TVector2<T>  operator/ ( const T t ) const { return TVector2<T>(v[0]/t, v[1]/t); }
	const TVector2<T> &operator+=( const T t )       { v[0] += t; v[1] += t; return *this; }
	const TVector2<T> &operator-=( const T t )       { v[0] -= t; v[1] -= t; return *this; }
	const TVector2<T> &operator*=( const T t )       { v[0] *= t; v[1] *= t; return *this; }
	const TVector2<T> &operator/=( const T t )       { v[0] /= t; v[1] /= t; return *this; }

	// Arithmetic operators (vector with vector)
	      TVector2<T>  operator+ ( const TVector2<T> &vec ) const { return TVector2<T>(v[0]+vec.v[0], v[1]+vec.v[1]); }
	      TVector2<T>  operator- ( const TVector2<T> &vec ) const { return TVector2<T>(v[0]-vec.v[0], v[1]-vec.v[1]); }
	      TVector2<T>  operator* ( const TVector2<T> &vec ) const { return TVector2<T>(v[0]*vec.v[0], v[1]*vec.v[1]); }
	      TVector2<T>  operator/ ( const TVector2<T> &vec ) const { return TVector2<T>(v[0]/vec.v[0], v[1]/vec.v[1]); }
	const TVector2<T> &operator+=( const TVector2<T> &vec )       { v[0] += vec.v[0]; v[1] += vec.v[1]; return *this; }
	const TVector2<T> &operator-=( const TVector2<T> &vec )       { v[0] -= vec.v[0]; v[1] -= vec.v[1]; return *this; }
	const TVector2<T> &operator*=( const TVector2<T> &vec )       { v[0] *= vec.v[0]; v[1] *= vec.v[1]; return *this; }
	const TVector2<T> &operator/=( const TVector2<T> &vec )       { v[0] /= vec.v[0]; v[1] /= vec.v[1]; return *this; }

	// Dot and cross product operators
	      T            operator| ( const TVector2<T> &vec ) const { return v[0]*vec.v[0] + v[1]*vec.v[1]; }

	// Magnitude/distance methods
	T           magnitudeSquared()                         const { return v[0]*v[0] + v[1]*v[1]; }
	T           magnitude       ()                         const { return (T)sqrt(magnitudeSquared()); }
	T           distanceSquared ( const TVector2<T> &vec ) const { return (*this - vec).magnitudeSquared(); }
	T           distance        ( const TVector2<T> &vec ) const { return (*this - vec).magnitude(); }
	TVector2<T> midpoint        ( const TVector2<T> &vec ) const { return Vector((*this - vec) / 2 + v); }
	TVector2<T> average         ( const TVector2<T> &vec ) const { return Vector((*this + vec) / 2); }

	// Advanced methods (should only be used with float or double types)
	void        normalize()                               { *this /= magnitude(); }
	double      angle    ( const TVector2<T> &vec ) const { return acos(*this | vec); }
	TVector2<T> reflect  ( const TVector2<T> &n   ) const {
		T t = (T)magnitude();
		TVector2<T> v = *this / t;
		return (v - n * (2 * (v | n))) * t;
	}

};


// Returns the direction vector between two points
template <class T> inline TVector2<T> directionVector( const TVector2<T> &p1, const TVector2<T> &p2 ){
	TVector2<T> vec = p2 - p1;
	vec.normalize();
	return vec;
}


};  //  namespace Maths
};  //  namespace Teddy


#endif  //  TEDDY__MATHS__VECTOR_2__H

