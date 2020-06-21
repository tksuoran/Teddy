
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

	$Id: Device.h,v 1.4 2002/01/11 14:34:59 tksuoran Exp $
*/


/*!
	\file

	This header file includes correct version of OpenGL; either native OpenGL or TinyGL.
	This header file also makes Visual Studio to link with correct version of SDL libraries
	on Win32 environment.
*/


#ifndef TEDDY__GRAPHICS__DEVICE__H
#define TEDDY__GRAPHICS__DEVICE__H


#include "Teddy/TeddyConfig.h"

#ifndef SWIG


/*  Choose either OpenGL or TinyGL includes and definitions  */
#if defined (USE_TINY_GL)

/*  TinyGL on all platforms  */
# include "Teddy/TinyGL/gl_gl.h"
# include "Teddy/TinyGL/gl_sdlswgl.h"

#else

/*  OpenGL on Win32  */
# if defined (_WIN32)

#  ifndef APIENTRY
#	define GLUT_APIENTRY_DEFINED
#	if (_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED) || defined(__MINGW32__) /*not sure about cygwin*/
#	 define APIENTRY	__stdcall
#	else
#	 define APIENTRY
#	endif
#  endif

#  ifndef CALLBACK
#	if (defined(_M_MRX000) || defined(_M_IX86) || defined(_M_ALPHA) || defined(_M_PPC)) && !defined(MIDL_PASS)
#	 define CALLBACK __stdcall
#	else
#	 define CALLBACK
#	endif
#  endif

#  ifndef WINGDIAPI
#	define GLUT_WINGDIAPI_DEFINED
#	define WINGDIAPI __declspec(dllimport)
#  endif

#  if !defined(_WCHAR_T_DEFINED) && defined(_MSC_VER)
typedef unsigned short wchar_t;
#	define _WCHAR_T_DEFINED
#  endif

# endif  /*  Choose platform for OpenGL  */

#if defined (__APPLE__)  /*  Macintosh  */
# include <OpenGL/gl.h>
#else
# include <GL/gl.h>      /*  Rest  */
#endif

#endif   /*  Choose TinyGL or OpenGL  */


/*  ---------------------------------------------------------------------------------------------  */

#define GL_LIGHT_MODEL_COLOR_CONTROL_EXT  0x81F8
#define GL_SINGLE_COLOR_EXT               0x81F9
#define GL_SEPARATE_SPECULAR_COLOR_EXT    0x81FA

/*  ---------------------------------------------------------------------------------------------  */


/*  Visual Studio Linking with SDL and either OpenGL or TinyGL  */
#if defined( _MSC_VER )
# if defined( _DEBUG )
#  pragma comment (lib, "SDLD.lib"     )
#  pragma comment (lib, "SDLmainD.lib" )  //  WinMain@16
# else
#  pragma comment (lib, "SDL.lib"     )
#  pragma comment (lib, "SDLmain.lib" )   //  WinMain@16
# endif
# if defined( USE_OPEN_GL ) && !defined( USE_TINY_GL )
#  pragma comment (lib, "opengl32.lib")
# endif
#endif


#endif  /*  SWIG  */

#endif  /*  TEDDY__GRAPHICS__DEVICE__H  */

