
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


/*!
	\file
	\brief   Wrapper for system math includes
*/


#ifndef TEDDY__SYS_SUPPORT__STD_MATHS__H
#define TEDDY__SYS_SUPPORT__STD_MATHS__H


#if defined(_MSC_VER)
# pragma warning(disable:4786)
#endif


#ifdef __cplusplus  /*  C/C++  */


/*
extern "C" {
#include <math.h>
#include <float.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
} */

#ifndef SWIG
#include <cmath>
#include <cfloat>
#include <climits>
#include <cstring>
#include <cstdlib>
#endif


namespace Teddy      {
namespace SysSupport {


#undef  M_PI
#undef  M_2_PI
#define M_PI          ( 3.14159265358979323846264338327950288419716939937510)
#define M_2_PI        ( 2*M_PI)
#define M_HALF_PI     (M_PI/2)
#define DEGS_PER_RAD  (57.29577951308232286465)
#define RADS_PER_DEG  ( 0.01745329251994329547)
#define degs(x)       (x*DEGS_PER_RAD)
#define rads(x)       (x*RADS_PER_DEG)

/*
#if !defined( min )
# define min(a,b) (a<b?a:b)
#endif
#if !defined( max )
# define max(a,b) (a>b?a:b)
#endif
*/

#if !defined(_MSC_VER)
# define acosf(x) (float)(acos(x))
# define cosf(x)  (float)(cos(x))
# define sinf(x)  (float)(sin(x))
# define sqrtf(x) (float)(sqrt(x))
#endif

#if defined(_MSC_VER)
# define isnan _isnan
#else
# ifndef isnan
#  define isnan __isnan
# endif
#endif


#ifndef MIN
#define MIN(a,b) ((a)<(b)?(a):(b))
#endif
#ifndef MAX
#define MAX(a,b) ((a)>(b)?(a):(b))
#endif


};  /*  namespace SysSupport  */
};  /*  namespace Teddy  */


#else  /*  C/C++ == C */

#ifndef SWIG
#include <math.h>
#include <float.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#endif
#undef  M_PI
#undef  M_2_PI
#define M_PI          ( 3.14159265358979323846264338327950288419716939937510)
#define M_2_PI        ( 2*M_PI)
#define M_HALF_PI     (M_PI/2)
#define DEGS_PER_RAD  (57.29577951308232286465)
#define RADS_PER_DEG  ( 0.01745329251994329547)
#define degs(x)       (x*DEGS_PER_RAD)
#define rads(x)       (x*RADS_PER_DEG)

/*
#if !defined( min )
# define min(a,b) (a<b?a:b)
#endif
#if !defined( max )
# define max(a,b) (a>b?a:b)
#endif
*/

#if !defined(_MSC_VER)
# define acosf(x) (float)(acos(x))
# define cosf(x)  (float)(cos(x))
# define sinf(x)  (float)(sin(x))
# define sqrtf(x) (float)(sqrt(x))
#endif

#if defined(_MSC_VER)
# define isnan _isnan
#else
# define isnan __isnan
#endif

#ifndef MIN
#define MIN(a,b) ((a)<(b)?(a):(b))
#endif
#ifndef MAX
#define MAX(a,b) ((a)>(b)?(a):(b))
#endif


#endif  /*  C/C++  */


#endif  /*  TEDDY__SYS_SUPPORT__STD_MATHS__H  */


