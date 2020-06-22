
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

	$Id: Matrix.h,v 1.7 2002/02/16 12:41:39 tksuoran Exp $
*/


#ifndef TEDDY__MATHS__MATRIX_H
#define TEDDY__MATHS__MATRIX_H


#if defined(_MSC_VER)
# pragma warning(disable:4786)
#endif


#include "Teddy/Maths/Vector.h"
#include "Teddy/Maths/Vector4.h"
#include "Teddy/Maths/CrossVector4.h"
#include "Teddy/SysSupport/StdMaths.h"
using namespace Teddy::SysSupport;


namespace Teddy {
namespace Maths {


class Quaternion;


/*!
	\author  Sean O'Neil
	\brief   4x4 Matrix

	This class implements a 4x4 matrix. Several functions and operators are
	defined to make working with matrices easier. The values are kept in column-
	major order to make it easier to use with OpenGL. For performance reasons,
	most of the functions assume that all matrices are orthogonal, which means the
	bottom row is [ 0 0 0 1 ]. Since I plan to use the GL_PROJECTION matrix to
	handle the projection matrix, I should never need to use any other kind of
	matrix, and I get a decent performance boost by ignoring the bottom row.
	
	Note: This class is not templatized because integral data types don't make sense
	      and there's no need for double-precision.
*/
class Matrix {
public:
	static const Matrix IDENTITY;
	static const Matrix SWAP_XY;
	static const Matrix SWAP_XZ;
	static const Matrix SWAP_YZ;
	static const Matrix MIRROR_X;
	static const Matrix MIRROR_Y;
	static const Matrix MIRROR_Z;
public:
	// This class uses column-major order, as used by OpenGL
	// | m[0][0] m[1][0] m[2][0] m[3][0] |
	// | m[0][1] m[1][1] m[2][1] m[3][1] | 
	// | m[0][2] m[1][2] m[2][2] m[3][2] | 
	// | m[0][3] m[1][3] m[2][3] m[3][3] | 
	float m[4][4];

	Matrix(){}
	Matrix( const float       f  ){ *this = f;  }
	Matrix( const float      *pf ){ *this = pf; }
	Matrix( const Quaternion &q  ){ *this = q;  }

	// Init functions
	void zeroMatrix(){
		m[0][0] = m[0][1] = m[0][2] = m[0][3] =
		m[1][0] = m[1][1] = m[1][2] = m[1][3] =
		m[2][0] = m[2][1] = m[2][2] = m[2][3] =
		m[3][0] = m[3][1] = m[3][2] = m[3][3] = 0;
	}

	       operator     float* ()                                    { return &m[0][0]; }
	float &operator            () ( const int i, const int j )       { return m[i][j]; }
	       operator const float*  ()                           const { return &m[0][0]; }
	float  operator            () ( const int i, const int j ) const { return m[i][j]; }

	void operator=( const float k ){
	    float *f;

		for( f = &m[0][0]; f != (float *)m+16; f++ ){
			*f = k;
		}
	}

	void operator=( const float *pf ){
	    float *to = &m[0][0];

		for( int i=0; i<16; i++ ){
			to[i] = pf[i];
		}
	}

	void   operator=( const Quaternion &q );

	Matrix operator-() const {
		Matrix       mat;
	    const float *from = &    m[0][0];
	    float       *to   = &mat.m[0][0];

		for( int i=0; i<16; i++ ){
			to[i] = -from[i];
		}
		return mat;
	}

	      Matrix   operator* ( const Matrix  &mat ) const;
	const Matrix  &operator*=( const Matrix  &mat ){ *this = *this * mat; return *this; }
	      Vector   operator* ( const Vector  &vec ) const { return transformVector (vec); }
	      Vector4  operator* ( const Vector4 &vec ) const { return transformVector4(vec); }

	Vector transformVector( const Vector &vec ) const {
		// 9 muls, 9 adds
		// | m[0][0] m[1][0] m[2][0] m[3][0] |   | v.v[0] |   | m[0][0]*v.v[0]+m[1][0]*v.v[1]+m[2][0]*v.v[2]+m[3][0] |
		// | m[0][1] m[1][1] m[2][1] m[3][1] |   | v.v[1] |   | m[0][1]*v.v[0]+m[1][1]*v.v[1]+m[2][1]*v.v[2]+m[3][1] |
		// | m[0][2] m[1][2] m[2][2] m[3][2] | * | v.v[2] | = | m[0][2]*v.v[0]+m[1][2]*v.v[1]+m[2][2]*v.v[2]+m[3][2] |
		// | 0   0   0   1   |   | 1   |   | 1                           |
		return Vector(
			(m[0][0]*vec.v[0] + m[1][0]*vec.v[1] + m[2][0]*vec.v[2] + m[3][0]),
			(m[0][1]*vec.v[0] + m[1][1]*vec.v[1] + m[2][1]*vec.v[2] + m[3][1]),
			(m[0][2]*vec.v[0] + m[1][2]*vec.v[1] + m[2][2]*vec.v[2] + m[3][2])
		);
	}
	Vector4 transformVector4( const Vector4 &vec ) const {
		return Vector4(
			(m[0][0]*vec.v[0] + m[1][0]*vec.v[1] + m[2][0]*vec.v[2] + m[3][0]*vec.v[3]),
			(m[0][1]*vec.v[0] + m[1][1]*vec.v[1] + m[2][1]*vec.v[2] + m[3][1]*vec.v[3]),
			(m[0][2]*vec.v[0] + m[1][2]*vec.v[1] + m[2][2]*vec.v[2] + m[3][2]*vec.v[3]),
			(m[0][3]*vec.v[0] + m[1][3]*vec.v[1] + m[2][3]*vec.v[2] + m[3][3]*vec.v[3])
		);
	}

	Vector4 getRow    ( const int i                   ) const { return Vector4( m[i][0], m[i][1], m[i][2], m[i][3] ); }
	Vector4 getColumn ( const int i                   ) const { return Vector4( m[0][i], m[1][i], m[2][i], m[3][i] ); }
	void    setRow    ( const int i, const Vector4 &v )       { m[i][0] = (float)v[0]; m[i][1] = (float)v[1]; m[i][2] = (float)v[2]; m[i][3] = (float)v[3]; }
	void    setColumn ( const int i, const Vector4 &v )       { m[0][i] = (float)v[0]; m[1][i] = (float)v[1]; m[2][i] = (float)v[2]; m[3][i] = (float)v[3]; }
	Vector  get3Row   ( const int i                   ) const { return Vector ( m[i][0], m[i][1], m[i][2] ); }
	Vector  get3Column( const int i                   ) const { return Vector ( m[0][i], m[1][i], m[2][i] ); }
	void    set3Row   ( const int i, const Vector  &v )       { m[i][0] = (float)v[0]; m[i][1] = (float)v[1]; m[i][2] = (float)v[2]; }
	void    set3Column( const int i, const Vector  &v )       { m[0][i] = (float)v[0]; m[1][i] = (float)v[1]; m[2][i] = (float)v[2]; }

    //!  \warning Only works with uniform transformation matrices
	Vector uniformTransformNormal( const Vector &vec ) const {
		// 9 muls, 6 adds
		// | m[0][0] m[1][0] m[2][0] m[3][0] |   | v.v[0] |   | m[0][0]*v.v[0]+m[1][0]*v.v[1]+m[2][0]*v.v[2] |
		// | m[0][1] m[1][1] m[2][1] m[3][1] |   | v.v[1] |   | m[0][1]*v.v[0]+m[1][1]*v.v[1]+m[2][1]*v.v[2] |
		// | m[0][2] m[1][2] m[2][2] m[3][2] | * | v.v[2] | = | m[0][2]*v.v[0]+m[1][2]*v.v[1]+m[2][2]*v.v[2] |
		// | 0   0   0   1   |   | 1   |   | 1                       |
		return Vector(
			(m[0][0]*vec.v[0] + m[1][0]*vec.v[1] + m[2][0]*vec.v[2] ),
			(m[0][1]*vec.v[0] + m[1][1]*vec.v[1] + m[2][1]*vec.v[2] ),
			(m[0][2]*vec.v[0] + m[1][2]*vec.v[1] + m[2][2]*vec.v[2] )
		);
	}

	void modelMatrix( const Quaternion &q, const Vector &vFrom ){
		*this = q;
		m[3][0] = (float)vFrom.v[0];
		m[3][1] = (float)vFrom.v[1];
		m[3][2] = (float)vFrom.v[2];
	}

    void translateMatrix( const TVector<double> &v ){
		// | 1  0  0  x |
		// | 0  1  0  y |
		// | 0  0  1  z |
		// | 0  0  0  1 |
		m[0][1] = m[0][2] = m[0][3] =
		m[1][0] = m[1][2] = m[1][3] =
		m[2][0] = m[2][1] = m[2][3] = 0;
		m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1;
		m[3][0] = (float)v[0]; 
		m[3][1] = (float)v[1]; 
		m[3][2] = (float)v[2]; 
    }

	void translateMatrix( const Vector &v ){
		// | 1  0  0  x |
		// | 0  1  0  y |
		// | 0  0  1  z |
		// | 0  0  0  1 |
		m[0][1] = m[0][2] = m[0][3] =
		m[1][0] = m[1][2] = m[1][3] =
		m[2][0] = m[2][1] = m[2][3] = 0;
		m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1;
		m[3][0] = (float)v[0]; 
		m[3][1] = (float)v[1]; 
		m[3][2] = (float)v[2]; 
	}

	// Translate functions
	void translateMatrix( const float x, const float y, const float z ){
		// | 1  0  0  x |
		// | 0  1  0  y |
		// | 0  0  1  z |
		// | 0  0  0  1 |
		m[0][1] = m[0][2] = m[0][3] =
		m[1][0] = m[1][2] = m[1][3] =
		m[2][0] = m[2][1] = m[2][3] = 0;
		m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1;
		m[3][0] = x; 
		m[3][1] = y; 
		m[3][2] = z;
	}

	//void translateMatrix( const float *pf ){ translateMatrix( pf[0], pf[1], pf[2] ); }

	void translate( const float x, const float y, const float z ){
		// 9 muls, 9 adds
		// | m[0][0] m[1][0] m[2][0] m[3][0] |   | 1  0  0  x |   | m[0][0] m[1][0] m[2][0] m[0][0]*x+m[1][0]*y+m[2][0]*z+m[3][0] |
		// | m[0][1] m[1][1] m[2][1] m[3][1] |   | 0  1  0  y |   | m[0][1] m[1][1] m[2][1] m[0][1]*x+m[1][1]*y+m[2][1]*z+m[3][1] |
		// | m[0][2] m[1][2] m[2][2] m[3][2] | * | 0  0  1  z | = | m[0][2] m[1][2] m[2][2] m[0][2]*x+m[1][2]*y+m[2][2]*z+m[3][2] |
		// | 0   0   0   1   |   | 0  0  0  1 |   | 0   0   0   1                     |
		m[3][0] = m[0][0]*x + m[1][0]*y + m[2][0]*z + m[3][0];
		m[3][1] = m[0][1]*x + m[1][1]*y + m[2][1]*z + m[3][1];
		m[3][2] = m[0][2]*x + m[1][2]*y + m[2][2]*z + m[3][2];
	}

	void translate( const float *pf ){
		translate( pf[0], pf[1], pf[2] );
	}

	// Scale functions
	void scaleMatrix( const float x, const float y, const float z ){
		// | x  0  0  0 |
		// | 0  y  0  0 |
		// | 0  0  z  0 |
		// | 0  0  0  1 |
		m[0][1] = m[0][2] = m[0][3] =
		m[1][0] = m[1][2] = m[1][3] =
		m[2][0] = m[2][1] = m[2][3] =
		m[3][0] = m[3][1] = m[3][2] = 0;
		m[0][0] = x;
		m[1][1] = y;
		m[2][2] = z;
		m[3][3] = 1;
	}

	void scaleMatrix( const float *pf ){
		scaleMatrix( pf[0], pf[1], pf[2] );
	}

	void scale( const float x, const float y, const float z ){
		// 9 muls
		// | m[0][0] m[1][0] m[2][0] m[3][0] |   | x  0  0  0 |   | m[0][0]*x m[1][0]*y m[2][0]*z m[3][0] |
		// | m[0][1] m[1][1] m[2][1] m[3][1] |   | 0  y  0  0 |   | m[0][1]*x m[1][1]*y m[2][1]*z m[3][1] |
		// | m[0][2] m[1][2] m[2][2] m[3][2] | * | 0  0  z  0 | = | m[0][2]*x m[1][2]*y m[2][2]*z m[3][2] |
		// | 0   0   0   1   |   | 0  0  0  1 |   | 0     0     0     1   |
		m[0][0] *= x; m[1][0] *= y; m[2][0] *= z;
		m[0][1] *= x; m[1][1] *= y; m[2][1] *= z;
		m[0][2] *= x; m[1][2] *= y; m[2][2] *= z;
	}

	void scale( const float *pf ){
		scale( pf[0], pf[1], pf[2] );
	}

	// Rotate functions
	void rotateXMatrix( const float radians ){
		// | 1 0    0     0 |
		// | 0 fCos -fSin 0 |
		// | 0 fSin fCos  0 |
		// | 0 0    0     1 |
		m[0][1] = m[0][2] = m[0][3] = 
		m[1][0] = m[1][3] =
		m[2][0] = m[2][3] =
		m[3][0] = m[3][1] = m[3][2] = 0;
		m[0][0] = m[3][3] = 1;

		float fCos = cosf( radians );
		float fSin = sinf( radians );
		m[1][1] = m[2][2] = fCos;
		m[1][2] =  fSin;
		m[2][1] = -fSin;
	}

	void rotateX( const float radians ){
		// 12 muls, 6 adds, 2 trig function calls
		// | m[0][0] m[1][0] m[2][0] m[3][0] |   | 1 0    0     0 |   | m[0][0] m[1][0]*fCos+m[2][0]*fSin m[2][0]*fCos-m[1][0]*fSin m[3][0] |
		// | m[0][1] m[1][1] m[2][1] m[3][1] |   | 0 fCos -fSin 0 |   | m[0][1] m[1][1]*fCos+m[2][1]*fSin m[2][1]*fCos-m[1][1]*fSin m[3][1] |
		// | m[0][2] m[1][2] m[2][2] m[3][2] | * | 0 fSin fCos  0 | = | m[0][2] m[1][2]*fCos+m[2][2]*fSin m[2][2]*fCos-m[1][2]*fSin m[3][2] |
		// | 0   0   0   1   |   | 0 0    0     1 |   | 0   0                 0                 1   |
		float fTemp;
		float fCos = cosf( radians );
		float fSin = sinf( radians );

		fTemp   = m[1][0]*fCos + m[2][0]*fSin;
		m[2][0] = m[2][0]*fCos - m[1][0]*fSin;
		m[1][0] = fTemp;
		fTemp   = m[1][1]*fCos + m[2][1]*fSin;
		m[2][1] = m[2][1]*fCos - m[1][1]*fSin;
		m[1][1] = fTemp;
		fTemp   = m[1][2]*fCos + m[2][2]*fSin;
		m[2][2] = m[2][2]*fCos - m[1][2]*fSin;
		m[1][2] = fTemp;
	}

	void rotateYMatrix( const float radians ){
		// | fCos  0 fSin  0 |
		// | 0     1 0     0 |
		// | -fSin 0 fCos  0 |
		// | 0     0 0     1 |
		m[0][1] = m[0][3] = 
		m[1][0] = m[1][2] = m[1][3] = 
		m[2][1] = m[2][3] = 
		m[3][0] = m[3][1] = m[3][2] = 0;
		m[1][1] = m[3][3] = 1;

		float fCos = cosf( radians );
		float fSin = sinf( radians );
		m[0][0] = m[2][2] = fCos;
		m[0][2] = -fSin;
		m[2][0] =  fSin;
	}
	void rotateY( const float radians ){
		// 12 muls, 6 adds, 2 trig function calls
		// | m[0][0] m[1][0] m[2][0] m[3][0] |   | fCos  0 fSin  0 |   | m[0][0]*fCos-m[2][0]*fSin m[1][0] m[0][0]*fSin+m[2][0]*fCos m[3][0] |
		// | m[0][1] m[1][1] m[2][1] m[3][1] |   | 0     1 0     0 |   | m[0][1]*fCos-m[2][1]*fSin m[1][1] m[0][1]*fSin+m[2][1]*fCos m[3][1] |
		// | m[0][2] m[1][2] m[2][2] m[3][2] | * | -fSin 0 fCos  0 | = | m[0][2]*fCos-m[2][2]*fSin m[1][2] m[0][2]*fSin+m[2][2]*fCos m[3][2] |
		// | 0   0   0   1   |   | 0     0 0     1 |   | 0                 0   0                 1   |
		float fTemp;
		float fCos = cosf( radians );
		float fSin = sinf( radians );
		fTemp   = m[0][0]*fCos - m[2][0]*fSin;
		m[2][0] = m[0][0]*fSin + m[2][0]*fCos;
		m[0][0] = fTemp;
		fTemp   = m[0][1]*fCos - m[2][1]*fSin;
		m[2][1] = m[0][1]*fSin + m[2][1]*fCos;
		m[0][1] = fTemp;
		fTemp   = m[0][2]*fCos - m[2][2]*fSin;
		m[2][2] = m[0][2]*fSin + m[2][2]*fCos;
		m[0][2] = fTemp;
	}
	void rotateZMatrix( const float radians ){
		// | fCos -fSin 0 0 |
		// | fSin fCos  0 0 |
		// | 0    0     1 0 |
		// | 0    0     0 1 |
		m[0][2] = m[0][3] =
		m[1][2] = m[1][3] =
		m[2][0] = m[2][1] = m[2][3] =
		m[3][0] = m[3][1] = m[3][2] = 0;
		m[2][2] = m[3][3] = 1;

		float fCos = cosf( radians );
		float fSin = sinf( radians );
		m[0][0] = m[1][1] = fCos;
		m[0][1] =  fSin;
		m[1][0] = -fSin;
	}

	void rotateZ( const float radians ){
		// 12 muls, 6 adds, 2 trig function calls
		// | m[0][0] m[1][0] m[2][0] m[3][0] |   | fCos -fSin 0 0 |   | m[0][0]*fCos+m[1][0]*fSin m[1][0]*fCos-m[0][0]*fSin m[2][0] m[3][0] |
		// | m[0][1] m[1][1] m[2][1] m[3][1] |   | fSin fCos  0 0 |   | m[0][1]*fCos+m[1][1]*fSin m[1][1]*fCos-m[0][1]*fSin m[2][1] m[3][1] |
		// | m[0][2] m[1][2] m[2][2] m[3][2] | * | 0    0     1 0 | = | m[0][2]*fCos+m[1][2]*fSin m[1][2]*fCos-m[0][2]*fSin m[2][2] m[3][2] |
		// | 0   0   0   1   |   | 0    0     0 1 |   | 0                 0                 0   1   |
		float fTemp;
		float fCos = cosf( radians );
		float fSin = sinf( radians );
		fTemp   = m[0][0]*fCos + m[1][0]*fSin;
		m[1][0] = m[1][0]*fCos - m[0][0]*fSin;
		m[0][0] = fTemp;
		fTemp   = m[0][1]*fCos + m[1][1]*fSin;
		m[1][1] = m[1][1]*fCos - m[0][1]*fSin;
		m[0][1] = fTemp;
		fTemp   = m[0][2]*fCos + m[1][2]*fSin;
		m[1][2] = m[1][2]*fCos - m[0][2]*fSin;
		m[0][2] = fTemp;
	}

	void rotateMatrix( const Vector &vec, const double radians ){
		// 15 muls, 10 adds, 2 trig function calls
		float  fCos = (float)cos( radians );
		Vector vCos = vec * (1 - fCos);
		Vector vSin = vec * (float)sin( radians );

		m[0][3] = 
		m[1][3] = 
		m[2][3] = 
		m[3][0] = m[3][1] = m[3][2] = 0;
		m[3][3] = 1;

		m[0][0] = (float)((vec.v[0] * vCos.v[0]) + fCos);
		m[1][0] = (float)((vec.v[0] * vCos.v[1]) - (vSin.v[2]));
		m[2][0] = (float)((vec.v[0] * vCos.v[2]) + (vSin.v[1]));
		m[0][1] = (float)((vec.v[1] * vCos.v[0]) + (vSin.v[2]));
		m[1][1] = (float)((vec.v[1] * vCos.v[1]) + fCos);
		m[2][1] = (float)((vec.v[1] * vCos.v[2]) - (vSin.v[0]));
		m[0][2] = (float)((vec.v[2] * vCos.v[0]) - (vSin.v[1]));
		m[2][1] = (float)((vec.v[2] * vCos.v[1]) + (vSin.v[0]));
		m[2][2] = (float)((vec.v[2] * vCos.v[2]) + fCos);
	}

	void rotate( const Vector &vec, const double f ){
		// 51 muls, 37 adds, 2 trig function calls
		Matrix mat;
		mat.rotateMatrix( vec, f );
		*this *= mat;
	}

	void direction( const Vector &vec ){
		Vector z = vec;
        Vector h;
		z.normalize();
		if( z[0]< (sqrt(2.0)/2.0) ){
            h = Vector(1,0,0);
		}else{
            h = Vector(0,1,0);
		}
		Vector x = z ^ h;
		Vector y = z ^ x;
		x        = z ^ y;
		//x.normalize();
		//y.normalize();
		//z.normalize();
		setRow( 0, Vector4(x,0)     );
		setRow( 1, Vector4(y,0)     );
		setRow( 2, Vector4(z,0)     );
		setRow( 3, Vector4(0,0,0,1) );
	}

	bool invert(){
		Vector4 x  = getColumn( 0 );
		Vector4 y  = getColumn( 1 );
		Vector4 z  = getColumn( 2 );
		Vector4 w  = getColumn( 3 );
		Vector4 x1 = CrossVector4( y, z, w );
		Vector4 y1 = CrossVector4( z, w, x );
		Vector4 z1 = CrossVector4( w, x, y );
		Vector4 w1 = CrossVector4( x, y, z );
		float   lx = x | x1;
		float   ly = y | y1;
		float   lz = z | z1;
		float   lw = w | w1;

		if( !lx || !ly || !lz || !lw ){
			return false;
		}

		x1 *= 1.0f/lx;
		y1 *= 1.0f/ly;
		z1 *= 1.0f/lz;
		w1 *= 1.0f/lw;

		setRow( 0, x1 );
		setRow( 1, y1 );
		setRow( 2, z1 );
		setRow( 3, w1 );
		return true;
	}

	// For orthogonal matrices, I belive this also gives you the inverse.
	void transpose(){
#		define SWAP(a,b,c) c=a; a=b; b=c
		float f;
		SWAP(m[0][1], m[1][0], f);
		SWAP(m[0][2], m[2][0], f);
		SWAP(m[0][3], m[3][0], f);
		SWAP(m[1][2], m[2][1], f);
		SWAP(m[1][3], m[3][1], f);
		SWAP(m[2][3], m[3][2], f);
#		undef SWAP
	}

};


};  //  namespace Maths;
};  //  namespace Teddy;


#endif  //  TEDDY__MATHS__MATRIX_H

