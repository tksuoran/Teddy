
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

	$Id: Vector.h,v 1.5 2002/01/17 18:57:37 tksuoran Exp $
*/


#ifndef TEDDY__MATHS__VECTOR__H
#define TEDDY__MATHS__VECTOR__H


#include "Teddy/Maths/Quaternion.h"
#include "Teddy/SysSupport/StdMaths.h"


namespace Teddy {
namespace Maths {


/*
	\class   Vector
	\author  Sean O'Neil

	This template class implements a simple 3D vector with v[0], v[1], and v[2] coordinates.
	Several functions and operators are defined to make working with vectors easier,
	and because it's templatized, any numeric type can be used with it. Macros are
	defined for the most common types.
*/
#ifndef SWIG
#define Vector       TVector<float>
#define IntVector    TVector<int>
#define FloatVector  TVector<float>
#define DoubleVector TVector<double>
#define CByteVector  TVector<unsigned char>

#define VECTOR_EPSILON 0.00001
#endif


/*!
	\brief   Template Class TVector
	\author  Sean O'Neil

	This template class implements a simple 3D vector with v[0], v[1], and v[2] coordinates.
	Several functions and operators are defined to make working with vectors easier,
	and because it's templatized, any numeric type can be used with it. Macros are
	defined for the most common types.
    */


template <typename T> class TVector {
public:
	T v[3];

	// Constructors
	TVector(){}
/*	TVector( const T a, const T b, const T c ){
		v[0] = a;
		v[1] = b;
		v[2] = c;
    }*/
    TVector( const int a, const int b, const int c ){
        v[0] = T(a);
        v[1] = T(b);
        v[2] = T(c);
    }
    TVector( const float a, const float b, const float c ){
        v[0] = T(a);
        v[1] = T(b);
        v[2] = T(c);
    }
    TVector( const double a, const double b, const double c ){
        v[0] = T(a);
        v[1] = T(b);
        v[2] = T(c);
    }

	TVector( const T            t  ){ *this = t;  }
	TVector( const T           *pt ){ *this = pt; }
    TVector( const TVector<double> &v  ){ this->v[0] = (T)(v.v[0]); this->v[1] = (T)(v.v[1]); this->v[2] = (T)(v.v[2]); }
    TVector( const TVector<float>  &v  ){ this->v[0] = (T)(v.v[0]); this->v[1] = (T)(v.v[1]); this->v[2] = (T)(v.v[2]); }
    TVector( const TVector<int>    &v  ){ this->v[0] = (T)(v.v[0]); this->v[1] = (T)(v.v[1]); this->v[2] = (T)(v.v[2]); }
//	TVector( const TVector <T> &v  ){ *this = v;  }
    TVector( const Quaternion  &q  ){ v[0] = (T)q.v[0]; v[1] = (T)q.v[1]; v[2] = (T)q.v[2]; }

	// Casting and unary operators
//	            operator TVector<float>  ()                    { return TVector<float>((float)v[0], (float)v[1], (float)v[2]); }
//	            operator TVector<double> ()                    { return TVector<double>((double)v[0], (double)v[1], (double)v[2]); }
	            operator              T* ()                    { return &v[0]; }
	T          &operator              [] ( const int n )       { return (&v[0])[n]; }
	            operator const        T* ()              const { return &v[0]; }
	T           operator              [] ( const int n ) const { return (&v[0])[n]; }
	TVector<T>  operator               - ()              const { return TVector<T>(-v[0], -v[1], -v[2]); }

	// Equal and comparison operators
	void operator= ( const T            t   )       { v[0] = v[1] = v[2] = t; }
	void operator= ( const T           *pt  )       { v[0] = pt[0]; v[1] = pt[1]; v[2] = pt[2]; }
	void operator= ( const TVector <T> &vec )       { v[0] = vec.v[0]; v[1] = vec.v[1]; v[2] = vec.v[2]; }
	//bool operator==( const TVector <T> &vec ) const { return (Abs(v[0] - vec.v[0]) <= (T)0.00001f && Abs(v[1] - vec.v[1]) <= 0.00001f && Abs(v[2] - vec.v[2]) <= 0.00001f); }
	//bool operator!=( const TVector <T> &vec ) const { return !(*this == vec); }

	int getMaxIndex() const {
		double l0 = Abs( v[0] );
		double l1 = Abs( v[1] );
		double l2 = Abs( v[2] );
		if( (l0 > l1) && (l0 > l2) ){
			return 0;
		}else if( (l1 > l0) && (l1 > l2) ){
            return 1;
		}else{
            return 2;
		}
	}

	// Arithmetic operators (vector with scalar)
	      TVector<T>  operator+ ( const T t ) const { return TVector<T>(v[0]+t, v[1]+t, v[2]+t); }
	      TVector<T>  operator- ( const T t ) const { return TVector<T>(v[0]-t, v[1]-t, v[2]-t); }
	      TVector<T>  operator* ( const T t ) const { return TVector<T>(v[0]*t, v[1]*t, v[2]*t); }
	      TVector<T>  operator/ ( const T t ) const { return TVector<T>(v[0]/t, v[1]/t, v[2]/t); }
	const TVector<T> &operator+=( const T t )       { v[0] += t; v[1] += t; v[2] += t; return *this; }
	const TVector<T> &operator-=( const T t )       { v[0] -= t; v[1] -= t; v[2] -= t; return *this; }
	const TVector<T> &operator*=( const T t )       { v[0] *= t; v[1] *= t; v[2] *= t; return *this; }
	const TVector<T> &operator/=( const T t )       { v[0] /= t; v[1] /= t; v[2] /= t; return *this; }

	// Arithmetic operators (vector with vector)
	      TVector<T>  operator+ ( const TVector<T> &vec ) const { return TVector<T>(v[0]+vec.v[0], v[1]+vec.v[1], v[2]+vec.v[2]); }
	      TVector<T>  operator- ( const TVector<T> &vec ) const { return TVector<T>(v[0]-vec.v[0], v[1]-vec.v[1], v[2]-vec.v[2]); }
	      TVector<T>  operator* ( const TVector<T> &vec ) const { return TVector<T>(v[0]*vec.v[0], v[1]*vec.v[1], v[2]*vec.v[2]); }
	      TVector<T>  operator/ ( const TVector<T> &vec ) const { return TVector<T>(v[0]/vec.v[0], v[1]/vec.v[1], v[2]/vec.v[2]); }
	const TVector<T> &operator+=( const TVector<T> &vec )       { v[0] += vec.v[0]; v[1] += vec.v[1]; v[2] += vec.v[2]; return *this; }
	const TVector<T> &operator-=( const TVector<T> &vec )       { v[0] -= vec.v[0]; v[1] -= vec.v[1]; v[2] -= vec.v[2]; return *this; }
	const TVector<T> &operator*=( const TVector<T> &vec )       { v[0] *= vec.v[0]; v[1] *= vec.v[1]; v[2] *= vec.v[2]; return *this; }
	const TVector<T> &operator/=( const TVector<T> &vec )       { v[0] /= vec.v[0]; v[1] /= vec.v[1]; v[2] /= vec.v[2]; return *this; }

	// Dot and cross product operators
	      T           operator| ( const TVector<T> &vec ) const { return v[0]*vec.v[0] + v[1]*vec.v[1] + v[2]*vec.v[2]; }
	      TVector<T>  operator^ ( const TVector<T> &vec ) const { return TVector<T>(v[1]*vec.v[2] - v[2]*vec.v[1], v[2]*vec.v[0] - v[0]*vec.v[2], v[0]*vec.v[1] - v[1]*vec.v[0]); }
	const TVector<T> &operator^=( const TVector<T> &vec )       { *this = *this ^ vec; return *this; }

	// Magnitude/distance methods
	T          magnitudeSquared()                        const { return v[0]*v[0] + v[1]*v[1] + v[2]*v[2]; }
	T          magnitude       ()                        const { return (T)sqrt(magnitudeSquared()); }
	T          distanceSquared ( const TVector<T> &vec ) const { return (*this - vec).magnitudeSquared(); }
	T          distance        ( const TVector<T> &vec ) const { return (*this - vec).magnitude(); }
	TVector<T> midpoint        ( const TVector<T> &vec ) const { return Vector((*this - vec) / 2 + v); }
	TVector<T> average         ( const TVector<T> &vec ) const { return Vector((*this + vec) / 2); }

	// Advanced methods (should only be used with float or double types)
	void       normalize()                              { *this /= magnitude(); }
	double     angle    ( const TVector<T> &vec ) const { return acos( *this | vec ); }
/*		double dp = *this | vec;
		if( dp == -1.0 ){
			return M_PI;
		}else if( dp == 1.0 ){
			return 0.0;
		}else{
			return fabs( acos(dp) );
		}
	}*/
	TVector<T> reflect  ( const TVector<T> &n   ) const {
		T t = (T)magnitude();
		TVector<T> v = *this / t;
		return (v - n * (2 * (v | n))) * t;
	}

	TVector<T> rotate( const T tAngle, const Vector &n ) const {
		T cosinus = (T)cos( tAngle );
		T sininus = (T)sin( tAngle );
		return TVector<T>(*this * tCos + ((n * *this) * (1 - tCos)) * n + (*this ^ n) * tSin);
	}
};

// Returns the normal vector of two vectors (the normalized cross product)
template <class T> inline TVector<T> normalVector( const TVector<T> &v1, const TVector<T> &v2 ){
	TVector<T> v = v1 ^ v2;
	v.normalize();
	return v;
}

// Returns the normal vector of a triangle or 3 points on a plane (assumes counter-clockwise orientation)
template <class T> inline TVector<T> normalVector( const TVector<T> &p1, const TVector<T> &p2, const TVector<T> &p3 ){
	return normalVector( p2-p1, p3-p1 );
}

// Returns the direction vector between two points
template <class T> inline TVector<T> directionVector( const TVector<T> &p1, const TVector<T> &p2 ){
	TVector<T> vec = p2 - p1;
	vec.normalize();
	return vec;
}


#ifdef SWIG
%template(Vector2)         TVector2<float>;
%template(DoubleVector2)   TVector2<double>;
%template(IntVector2)      TVector2<int>;
#endif


};  //  namespace Maths
};  //  namespace Teddy


#endif  //  TEDDY__MATHS__VECTOR__H

