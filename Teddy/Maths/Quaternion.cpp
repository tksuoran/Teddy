
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


#include "Teddy/Maths/Quaternion.h"
#include "Teddy/Maths/Matrix.h"
#include "Teddy/SysSupport/Messages.h"
using namespace Teddy::SysSupport;


namespace Teddy {
namespace Maths {


#define DELTA 1e-6f

#define QUATERNION_EPSILON 1e-6f




Quaternion::Quaternion(){
}

Quaternion::Quaternion( const float h, const float p, const float b ){
	*this  = Quaternion( Vector(0.0,0.0,1.0),  -b );
    *this *= Quaternion( Vector(1.0,0.0,0.0),  -p );
	*this *= Quaternion( Vector(0.0,1.0,0.0),  -h );
}

Quaternion::Quaternion( const float a, const float b, const float c, const float d ){
	v[0] = a;
	v[1] = b;
	v[2] = c;
	v[3] = d;
}
Quaternion::Quaternion( const double a, const double b, const double c, const double d ){
	v[0] = a;
	v[1] = b;
	v[2] = c;
	v[3] = d;
}
Quaternion::Quaternion( const Vector     &v, const double f){setAxisAngle(v, f); }
Quaternion::Quaternion( const Vector     &v ){ *this = v; }
Quaternion::Quaternion( const Quaternion &q ){ *this = q; }
Quaternion::Quaternion( const Matrix     &m ){ *this = m; }
Quaternion::Quaternion( const double     *p ){ *this = p; }

// Casting and unary operators
            Quaternion::operator       double*()                    { return v; }
double     &Quaternion::operator           [] ( const int n )       { return v[n]; }
            Quaternion::operator const double*()              const { return v; }
double      Quaternion::operator           [] ( const int n ) const { return v[n]; }
Quaternion  Quaternion::operator            - ()              const { return Quaternion(-v[0], -v[1], -v[2], -v[3]); }

// Equal and comparison operators
void Quaternion::operator=( const Vector     &vec ){ v[0] = vec.v[0]; v[1] = vec.v[1]; v[2] = vec.v[2]; v[3] =    0; }
void Quaternion::operator=( const Quaternion &q   ){ v[0] = q  .v[0]; v[1] = q  .v[1]; v[2] = q  .v[2]; v[3] = q.v[3]; }
void Quaternion::operator=( const double     *p   ){ v[0] = p[0]; v[1] = p[1]; v[2] = p[2]; v[3] = p[3]; }

// Arithmetic operators (quaternion and scalar)
Quaternion Quaternion::operator+( const double f ) const { return Quaternion(v[0]+f, v[1]+f, v[2]+f, v[3]+f); }
Quaternion Quaternion::operator-( const double f ) const { return Quaternion(v[0]-f, v[1]-f, v[2]-f, v[3]-f); }
Quaternion Quaternion::operator*( const double f ) const { return Quaternion(v[0]*f, v[1]*f, v[2]*f, v[3]*f); }
Quaternion Quaternion::operator/( const double f ) const { return Quaternion(v[0]/f, v[1]/f, v[2]/f, v[3]/f); }
const Quaternion &Quaternion::operator+=( const double f ){ v[0]+=f; v[1]+=f; v[2]+=f; v[3]+=f; return *this; }
const Quaternion &Quaternion::operator-=( const double f ){ v[0]-=f; v[1]-=f; v[2]-=f; v[3]-=f; return *this; }
const Quaternion &Quaternion::operator*=( const double f ){ v[0]*=f; v[1]*=f; v[2]*=f; v[3]*=f; return *this; }
const Quaternion &Quaternion::operator/=( const double f ){ v[0]/=f; v[1]/=f; v[2]/=f; v[3]/=f; return *this; }

// Arithmetic operators (quaternion and quaternion)
Quaternion Quaternion::operator+( const Quaternion &q ) const { return Quaternion(v[0]+q.v[0], v[1]+q.v[1], v[2]+q.v[2], v[3]+q.v[3]); }
Quaternion Quaternion::operator-( const Quaternion &q ) const { return Quaternion(v[0]-q.v[0], v[1]-q.v[1], v[2]-q.v[2], v[3]-q.v[3]); }
																														   
const Quaternion &Quaternion::operator+=( const Quaternion &q ){ v[0]+=q.v[0]; v[1]+=q.v[1]; v[2]+=q.v[2]; v[3]+=q.v[3]; return *this; }
const Quaternion &Quaternion::operator-=( const Quaternion &q ){ v[0]-=q.v[0]; v[1]-=q.v[1]; v[2]-=q.v[2]; v[3]-=q.v[3]; return *this; }
const Quaternion &Quaternion::operator*=( const Quaternion &q ){ *this = *this * q; return *this; }

// Magnitude/normalize methods
double Quaternion::magnitudeSquared() const { return v[0]*v[0] + v[1]*v[1] + v[2]*v[2] + v[3]*v[3]; }
double Quaternion::magnitude       () const { return sqrt( magnitudeSquared() ); }
void   Quaternion::normalize       ()       { *this /= magnitude(); }

// Advanced quaternion methods
Quaternion Quaternion::conjugate   () const { return Quaternion(-v[0], -v[1], -v[2], v[3]); }
Quaternion Quaternion::inverse     () const { return conjugate() / magnitudeSquared(); }
Quaternion Quaternion::unitInverse () const { return conjugate(); }

void Quaternion::rotate( const Quaternion &q ){ *this = q * *this; }

void Quaternion::rotate( const Vector &vAxis, const double fAngle ){
	Quaternion q;
	q.setAxisAngle( vAxis, fAngle );
	rotate( q );
}

/*Vector getViewAxis() const {
	// 6 muls, 7 adds
	double x2 = v[0] + v[0];
	double y2 = v[1] + v[1];
	double z2 = v[2] + v[2];
	double xx = v[0] * x2; double xz = v[0] * z2;
	double yy = v[1] * y2; double yz = v[1] * z2;
	double wx = v[3] * x2; double wy = v[3] * y2;
	return -Vector(xz+wy, yz-wx, 1-(xx+yy));
}*/

Vector Quaternion::getViewAxis() const {
	// 6 muls, 7 adds
	double x2 = v[0] + v[0];
	double y2 = v[1] + v[1];
	double z2 = v[2] + v[2];
	double xx = v[0] * x2; double xz = v[0] * z2;
	double yy = v[1] * y2; double yz = v[1] * z2;
	double wx = v[3] * x2; double wy = v[3] * y2;
	return -Vector(xz+wy, yz-wx, 1-(xx+yy));
}

Vector Quaternion::getUpAxis() const {
	// 6 muls, 7 adds
	double x2 = v[0] + v[0];
	double y2 = v[1] + v[1];
	double z2 = v[2] + v[2];
	double xx = v[0] * x2; double xy = v[0] * y2;
	double yz = v[1] * z2; double zz = v[2] * z2;
	double wx = v[3] * x2; double wz = v[3] * z2;
	return Vector(xy-wz, 1-(xx+zz), yz+wx);
}

Vector Quaternion::getRightAxis() const {
	// 6 muls, 7 adds
	double x2 = v[0] + v[0];
	double y2 = v[1] + v[1];
	double z2 = v[2] + v[2];
	double xy = v[0] * y2; double xz = v[0] * z2;
	double yy = v[1] * y2; double zz = v[2] * z2;
	double wy = v[3] * y2; double wz = v[3] * z2;
	return Vector(1-(yy+zz), xy+wz, xz-wy);
}


///


Vector Quaternion::rotateVector( Vector &vec ) const {
	return Vector( *this * Quaternion(vec) * unitInverse() );
}


void Quaternion::setAxisAngle( const Vector &vAxis, const double radians ){
	// 4 muls, 2 trig function calls
/*	double d     = radians * 0.5; 
	double sinus = sin( d );
	v[0] = vAxis.v[0] * sinus;
	v[1] = vAxis.v[1] * sinus;
	v[2] = vAxis.v[2] * sinus;
	v[3] = cos( d );*/
	double d = radians * 0.5;

	*this = vAxis * sin( d );
	v[3]  = cos( d );
}


void Quaternion::getAxisAngle( Vector &vAxis, double &radians ) const {
	// 4 muls, 1 div, 2 trig function calls
	radians = acos( v[3] );
	vAxis   = *this / sin( radians );
	radians *= 2;
}


#if 0
void Quaternion::operator=( const Matrix &m ){
	// Check the sum of the diagonal
	double tr = m(0, 0) + m(1, 1) + m(2, 2);
	emsg( M_DEBUG, "tr = % 10.7f", tr );
	if( tr > 0.0f ){
		// The sum is positive
		// 4 muls, 1 div, 6 adds, 1 trig function call
		double s = sqrt(tr + 1);
		v[3] = s * 0.5;
		s    = 0.5 / s;
		v[0] = (m(1, 2) - m(2, 1)) * s;
		v[1] = (m(2, 0) - m(0, 2)) * s;
		v[2] = (m(0, 1) - m(1, 0)) * s;
	}else{
		// The sum is negative
		// 4 muls, 1 div, 8 adds, 1 trig function call
		const int nIndex[3] = {1, 2, 0};
		int i;
		int j;
		int k;
		i = 0;
		if( m(1, 1) > m(i, i) ) i = 1;
		if( m(2, 2) > m(i, i) ) i = 2;
		j = nIndex[i];
		k = nIndex[j];

		double s = sqrtf((m(i, i) - (m(j, j) + m(k, k))) + 1);
		(*this)[i] = s * 0.5;
		if( s != 0.0 ) s = 0.5 / s;
		(*this)[j] = (m(i, j) + m(j, i)) * s;
		(*this)[k] = (m(i, k) + m(k, i)) * s;
		(*this)[3] = (m(j, k) - m(k, j)) * s;
	}
}
#else
void Quaternion::operator=( const Matrix &m ){
	// Check the sum of the diagonal
	double tr = m.m[0][0] + m.m[1][1] + m.m[2][2];
	if( tr > 0.0 ){
		// The sum is positive
		// 4 muls, 1 div, 6 adds, 1 trig function call
		double s = sqrt(tr + 1.0);
		//emsg( M_DEBUG, "s = % 10.7f", s );
		v[3] = s * 0.5;
		s    = 0.5 / s;
		v[0] = (m.m[1][2] - m.m[2][1]) * s;
		v[1] = (m.m[2][0] - m.m[0][2]) * s;
		v[2] = (m.m[0][1] - m.m[1][0]) * s;
		//emsg( M_DEBUG, "s = % 10.7f", s );
		//emsg( M_DEBUG, "% 10.7f % 10.7f % 10.7f % 10.7f ", v[0], v[1], v[2], v[3] );
	}else{
		// The sum is negative
		// 4 muls, 1 div, 8 adds, 1 trig function call
		const int nIndex[3] = {1, 2, 0};
		int i;
		int j;
		int k;
		i = 0;
		if( m.m[1][1] > m.m[i][i] ) i = 1;
		if( m.m[2][2] > m.m[i][i] ) i = 2;
		j = nIndex[i];
		k = nIndex[j];

		//emsg( M_DEBUG, "i = %d", i );
		double s = sqrt((m.m[i][i] - (m.m[j][j] + m.m[k][k])) + 1);
		//emsg( M_DEBUG, "s = % 10.7f", s );
		(*this)[i] = s * 0.5;
		if( s != 0.0 ) s = 0.5 / s;
		//emsg( M_DEBUG, "s = % 10.7f", s );
		(*this)[j] = (m.m[i][j] + m.m[j][i]) * s;
		(*this)[k] = (m.m[i][k] + m.m[k][i]) * s;
		(*this)[3] = (m.m[j][k] - m.m[k][j]) * s;
	}
}
#endif

Quaternion Quaternion::operator*( const Quaternion &q ) const {
	// 12 muls, 30 adds
	double E = (v[0] + v[2])*(q.v[0] + q.v[1]);
	double F = (v[2] - v[0])*(q.v[0] - q.v[1]);
	double G = (v[3] + v[1])*(q.v[3] - q.v[2]);
	double H = (v[3] - v[1])*(q.v[3] + q.v[2]);
	double A = F - E;
	double B = F + E;
	return Quaternion(
		(v[3] + v[0])*(q.v[3] + q.v[0]) + (A - G - H) * 0.5,
		(v[3] - v[0])*(q.v[1] + q.v[2]) + (B + G - H) * 0.5,
		(v[1] + v[2])*(q.v[3] - q.v[0]) + (B - G + H) * 0.5,
		(v[2] - v[1])*(q.v[1] - q.v[2]) + (A + G + H) * 0.5
	);
}


//!  Spherical linear interpolation between two quaternions
Quaternion slerp( const Quaternion &q1, const Quaternion &q2, const double t ){
	// Calculate the cosine of the angle between the two
	double scale0;
	double scale1;
	double cosinus = q1.v[0] * q2.v[0] + q1.v[1] * q2.v[1] + q1.v[2] * q2.v[2] + q1.v[3] * q2.v[3];

	// If the angle is significant, use the spherical interpolation
	if( (1 - fabs(cosinus)) > DELTA ){
		double temp  = acos( fabs(cosinus) );
		double sinus = sin ( temp );
		scale0 = sin( ( - t) * temp) / sinus;
		scale1 = sin(     t  * temp) / sinus;
	}else{  //  Else use the cheaper linear interpolation
		scale0 = 1 - t;
		scale1 = t;
	}

	if( cosinus < 0 ) scale1 = -scale1;

	// Return the interpolated result
	return (q1 * scale0) + (q2 * scale1);
}


};  //  namespace Maths
};  //  namespace Teddy


