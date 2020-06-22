
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

	$Id: Messages.h,v 1.4 2002/01/11 14:35:03 tksuoran Exp $
*/


/*!
	\file
	\brief Error, warning, init and debug message routines
*/


#ifndef TEDDY__SYS_SUPPORT__MESSAGES__H
#define TEDDY__SYS_SUPPORT__MESSAGES__H


namespace Teddy      {
namespace SysSupport {


#define mkstr_(x) # x
#define mkstr(x) mkstr_( x )
#define MSG_HEAD mkstr( __FILE__ ) ": " mkstr( __LINE__ ) " "


extern int M_FATAL;   //!<  Fatal messages
extern int M_ERROR;   //!<  General messages
extern int M_WARN;    //!<  General warning messages
extern int M_DEBUG;   //!<  General debug messages
extern int M_INIT;    //!<  Initialization messages
extern int M_GL;      //!<  (Internal) graphics driver messages
extern int M_WM;      //!<  (Internal) window manager messages
extern int M_WMD;     //!<  (Internal) window manager drawing messages
extern int M_WME;     //!<  (Internal) window manager event   messages
extern int M_WML;     //!<  (Internal) window manager layout  messages
extern int M_MAT;     //!<  Material management messages
extern int M_MOD;     //!<  Model management messages
extern int M_SCN;     //!<  Scene management messages
extern int M_LWO;     //!<  LightWave object messages
extern int M_LWS;     //!<  LightWave scene messages
extern int M_TMAP;    //!<  Texture mapping messages
extern int M_VERT;    //!<  Vertex messages
extern int M_AUDIO;   //!<  Audio messages
extern int M_FFE;     //!<  Frontier messages
extern int M_NET;     //!<  Networking messages


extern void init_msg   ();
extern int  alloc_msg  ( const char *desc );
extern void enable_msg ( int type );
extern void disable_msg( int type );
extern void msg        ( int type, const char *format, ... );
extern void dmsg       ( int type, const char *format, ... );
extern void dprint     ( int type, const char *format, ... );
extern void emsg       ( int type, const char *format, ... );
extern void fmsg       ( int type, const char *format, ... );


};  //  namespace SysSupport
};  //  namespace Teddy


#endif  //  TEDDY__SYS_SUPPORT__MESSAGES__H

