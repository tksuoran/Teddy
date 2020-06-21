
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

	$Id: Matrix.cpp,v 1.6 2002/01/22 19:30:05 tksuoran Exp $
*/


#include "Teddy/Maths/Matrix.h"
#include "Teddy/Maths/Quaternion.h"


namespace Teddy {
namespace Maths {


static const float a_identity_matrix[] = {
	1,0,0,0, 
	0,1,0,0,
	0,0,1,0,
	0,0,0,1
};
static const float a_swap_xy_matrix[] = {
	0,1,0,0, 
	1,0,0,0,
	0,0,1,0,
	0,0,0,1
};
static const float a_swap_xz_matrix[] = {
	0,0,1,0, 
	0,1,0,0,
	1,0,0,0,
	0,0,0,1
};
static const float a_swap_yz_matrix[] = {
	1,0,0,0, 
	0,0,1,0,
	0,1,0,0,
	0,0,0,1
};
static const float a_mirror_x_matrix[] = {
   -1, 0, 0, 0, 
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};
static const float a_mirror_y_matrix[] = {
	1, 0, 0, 0, 
	0,-1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};
static const float a_mirror_z_matrix[] = {
	1, 0, 0, 0, 
	0, 1, 0, 0,
	0, 0,-1, 0,
	0, 0, 0, 1
};
static const float *const mat_i   = &a_identity_matrix[0];
static const float *const mat_sxy = &a_swap_xy_matrix [0];
static const float *const mat_sxz = &a_swap_xz_matrix [0];
static const float *const mat_syz = &a_swap_yz_matrix [0];
static const float *const mat_mx  = &a_mirror_x_matrix[0];
static const float *const mat_my  = &a_mirror_y_matrix[0];
static const float *const mat_mz  = &a_mirror_z_matrix[0];
/*static*/ const Matrix Matrix::IDENTITY( mat_i );
/*static*/ const Matrix Matrix::SWAP_XY ( mat_sxy );
/*static*/ const Matrix Matrix::SWAP_XZ ( mat_sxz );
/*static*/ const Matrix Matrix::SWAP_YZ ( mat_syz );
/*static*/ const Matrix Matrix::MIRROR_X( mat_mx );
/*static*/ const Matrix Matrix::MIRROR_Y( mat_my );
/*static*/ const Matrix Matrix::MIRROR_Z( mat_mz );


void Matrix::operator=( const Quaternion &q ){
	// 9 muls, 15 adds
	double x2 = q.v[0] + q.v[0];
	double y2 = q.v[1] + q.v[1];
	double z2 = q.v[2] + q.v[2];
	double xx = q.v[0] * x2;  double xy = q.v[0] * y2;  double xz = q.v[0] * z2;
	double yy = q.v[1] * y2;  double yz = q.v[1] * z2;  double zz = q.v[2] * z2;
	double wx = q.v[3] * x2;  double wy = q.v[3] * y2;  double wz = q.v[3] * z2;

	m[0][3] = 
	m[1][3] = 
	m[2][3] = 
	m[3][0] = m[3][1] = m[3][2] = 0; 
	m[3][3] = 1;
	m[0][0] = (float)(1-(yy+zz));  m[1][0] = (float)(xy+wz);      m[2][0] = (float)(xz-wy);
	m[0][1] = (float)(xy-wz);      m[1][1] = (float)(1-(xx+zz));  m[2][1] = (float)(yz+wx);
	m[0][2] = (float)(xz+wy);      m[1][2] = (float)(yz-wx);      m[2][2] = (float)(1-(xx+yy));
}

Matrix Matrix::operator*( const Matrix &mat ) const {
	// 36 muls, 27 adds
	// | m[0][0] m[1][0] m[2][0] m[3][0] |   | mat.m[0][0] mat.m[1][0] mat.m[2][0] mat.m[3][0] |   | m[0][0]*mat.m[0][0]+m[1][0]*mat.m[0][1]+m[2][0]*mat.m[0][2] m[0][0]*mat.m[1][0]+m[1][0]*mat.m[1][1]+m[2][0]*mat.m[1][2] m[0][0]*mat.m[2][0]+m[1][0]*mat.m[2][1]+m[2][0]*mat.m[2][2] m[0][0]*mat.m[3][0]+m[1][0]*mat.m[3][1]+m[2][0]*mat.m[3][2]+m[3][0] |
	// | m[0][1] m[1][1] m[2][1] m[3][1] |   | mat.m[0][1] mat.m[1][1] mat.m[2][1] mat.m[3][1] |   | m[0][1]*mat.m[0][0]+m[1][1]*mat.m[0][1]+m[2][1]*mat.m[0][2] m[0][1]*mat.m[1][0]+m[1][1]*mat.m[1][1]+m[2][1]*mat.m[1][2] m[0][1]*mat.m[2][0]+m[1][1]*mat.m[2][1]+m[2][1]*mat.m[2][2] m[0][1]*mat.m[3][0]+m[1][1]*mat.m[3][1]+m[2][1]*mat.m[3][2]+m[3][1] |
	// | m[0][2] m[1][2] m[2][2] m[3][2] | * | mat.m[0][2] mat.m[1][2] mat.m[2][2] mat.m[3][2] | = | m[0][2]*mat.m[0][0]+m[1][2]*mat.m[0][1]+m[2][2]*mat.m[0][2] m[0][2]*mat.m[1][0]+m[1][2]*mat.m[1][1]+m[2][2]*mat.m[1][2] m[0][2]*mat.m[2][0]+m[1][2]*mat.m[2][1]+m[2][2]*mat.m[2][2] m[0][2]*mat.m[3][0]+m[1][2]*mat.m[3][1]+m[2][2]*mat.m[3][2]+m[3][2] |
	// | 0   0   0   1   |   | 0     0     0     1     |   | 0                             0                             0                             1                                 |
	Matrix mRet;

	mRet.m[0][0] = m[0][0]*mat.m[0][0] + m[1][0]*mat.m[0][1] + m[2][0]*mat.m[0][2] + m[3][0]*mat.m[0][3];
	mRet.m[1][0] = m[0][0]*mat.m[1][0] + m[1][0]*mat.m[1][1] + m[2][0]*mat.m[1][2] + m[3][0]*mat.m[1][3];
	mRet.m[2][0] = m[0][0]*mat.m[2][0] + m[1][0]*mat.m[2][1] + m[2][0]*mat.m[2][2] + m[3][0]*mat.m[2][3];
	mRet.m[3][0] = m[0][0]*mat.m[3][0] + m[1][0]*mat.m[3][1] + m[2][0]*mat.m[3][2] + m[3][0]*mat.m[3][3];

	mRet.m[0][1] = m[0][1]*mat.m[0][0] + m[1][1]*mat.m[0][1] + m[2][1]*mat.m[0][2] + m[3][1]*mat.m[0][3];
	mRet.m[1][1] = m[0][1]*mat.m[1][0] + m[1][1]*mat.m[1][1] + m[2][1]*mat.m[1][2] + m[3][1]*mat.m[1][3];
	mRet.m[2][1] = m[0][1]*mat.m[2][0] + m[1][1]*mat.m[2][1] + m[2][1]*mat.m[2][2] + m[3][1]*mat.m[2][3];
	mRet.m[3][1] = m[0][1]*mat.m[3][0] + m[1][1]*mat.m[3][1] + m[2][1]*mat.m[3][2] + m[3][1]*mat.m[3][3];

	mRet.m[0][2] = m[0][2]*mat.m[0][0] + m[1][2]*mat.m[0][1] + m[2][2]*mat.m[0][2] + m[3][2]*mat.m[0][3];
	mRet.m[1][2] = m[0][2]*mat.m[1][0] + m[1][2]*mat.m[1][1] + m[2][2]*mat.m[1][2] + m[3][2]*mat.m[1][3];
	mRet.m[2][2] = m[0][2]*mat.m[2][0] + m[1][2]*mat.m[2][1] + m[2][2]*mat.m[2][2] + m[3][2]*mat.m[2][3];
	mRet.m[3][2] = m[0][2]*mat.m[3][0] + m[1][2]*mat.m[3][1] + m[2][2]*mat.m[3][2] + m[3][2]*mat.m[3][3];

	mRet.m[0][3] = m[0][3]*mat.m[0][0] + m[1][3]*mat.m[0][1] + m[2][3]*mat.m[0][2] + m[3][3]*mat.m[0][3];
	mRet.m[1][3] = m[0][3]*mat.m[1][0] + m[1][3]*mat.m[1][1] + m[2][3]*mat.m[1][2] + m[3][3]*mat.m[1][3];
	mRet.m[2][3] = m[0][3]*mat.m[2][0] + m[1][3]*mat.m[2][1] + m[2][3]*mat.m[2][2] + m[3][3]*mat.m[2][3];
	mRet.m[3][3] = m[0][3]*mat.m[3][0] + m[1][3]*mat.m[3][1] + m[2][3]*mat.m[3][2] + m[3][3]*mat.m[3][3];

	return mRet;
}


};  //  namespace Maths
};  //  namespace Teddy

