
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

	$Id: Quaternion.h,v 1.5 2002/01/17 18:57:37 tksuoran Exp $
*/


#ifndef TEDDY__MATHS__QUATERNION__H
#define TEDDY__MATHS__QUATERNION__H


#include "Teddy/SysSupport/StdMaths.h"


namespace Teddy {
namespace Maths {


class Matrix;
template <typename T> class TVector;


/*!
	\author  Sean O'Neil

	This class implements a 4D quaternion. Several functions and operators are
	defined to make working with quaternions easier. Quaternions are often used to
	represent rotations, and have a number of advantages over other constructs.
	Their main disadvantage is that they are unintuitive.
	
	Note: This class is not templatized because integral data types don't make sense
	      and there's no need for double-precision.
          */
class Quaternion {
public:
	double v[4];

	// Constructors
	Quaternion();
	Quaternion( const float  h, const float  p, const float  b );
	Quaternion( const float  a, const float  b, const float  c, const float  d );
	Quaternion( const double a, const double b, const double c, const double d );
	Quaternion( const TVector<float> &v, const double f);
	Quaternion( const TVector<float> &v );
	Quaternion( const Quaternion     &q );
	Quaternion( const Matrix         &m );
	Quaternion( const double         *p );

	// Casting and unary operators
	            operator       double*();
	double     &operator           [] ( const int n );
	            operator const double*()              const;
	double      operator           [] ( const int n ) const;
	Quaternion  operator            - ()              const;

	// Equal and comparison operators
	void operator=( const TVector<float> &vec );
	void operator=( const Quaternion     &q   );
	void operator=( const Matrix         &m   );
	void operator=( const double         *p   );

	// Arithmetic operators (quaternion and scalar)
	Quaternion operator+( const double f ) const;
	Quaternion operator-( const double f ) const;
	Quaternion operator*( const double f ) const;
	Quaternion operator/( const double f ) const;
    const Quaternion &operator+=( const double f );
	const Quaternion &operator-=( const double f );
	const Quaternion &operator*=( const double f );
	const Quaternion &operator/=( const double f );

	// Arithmetic operators (quaternion and quaternion)
	Quaternion operator+( const Quaternion &q ) const;
	Quaternion operator-( const Quaternion &q ) const;
	Quaternion operator*( const Quaternion &q ) const;  //  Multiplying quaternions is a special operation
																															   
	const Quaternion &operator+=( const Quaternion &q );
	const Quaternion &operator-=( const Quaternion &q );
	const Quaternion &operator*=( const Quaternion &q );

	// Magnitude/normalize methods
	double magnitudeSquared() const;
	double magnitude       () const;
	void   normalize       ();

	// Advanced quaternion methods
	Quaternion     conjugate   () const;
	Quaternion     inverse     () const;
	Quaternion     unitInverse () const;
	TVector<float> rotateVector( TVector<float> &v ) const;
	void           setAxisAngle( const TVector<float> &vAxis, const double fAngle );
	void           getAxisAngle( TVector<float> &vAxis, double &fAngle) const;

	void rotate( const Quaternion &q );

	void rotate( const TVector<float> &vAxis, const double fAngle );
	TVector<float> getViewAxis () const;
	TVector<float> getUpAxis   () const;
	TVector<float> getRightAxis() const;
};


extern Quaternion slerp( const Quaternion &q1, const Quaternion &q2, const double t );


};  //  namespace Maths
};  //  namespace Teddy


#endif  //  TEDDY__MATHS__QUATERNION__H


