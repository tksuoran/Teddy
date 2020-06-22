
/*
	TEDDY - General graphics application library
	Copyright (C) 1999-2020  Timo Suoranta
	tksuoran@gmail.com

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


#include "Teddy/SysSupport/Messages.h"
#ifndef SWIG
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#endif

namespace Teddy      {
namespace SysSupport {


#define MAX_MSG_TYPES 64
static bool        msg_enable[MAX_MSG_TYPES];
static const char *msg_desc  [MAX_MSG_TYPES];
static int         last_msg_type = 0;


int M_FATAL;
int M_ERROR;
int M_WARN;
int M_DEBUG;
int M_INIT;
int M_GL;
int M_WM;
int M_WMD;
int M_WME;
int M_WML;
int M_MAT;
int M_MOD;
int M_SCN;
int M_LWO;
int M_LWS;
int M_TMAP;
int M_VERT;
int M_AUDIO;
int M_FFE;
int M_NET;


#if defined(_MSC_VER)
# define MSG_DEST stdout
#else
# define MSG_DEST stderr
#endif

void init_msg(){
	for( int i=0; i<MAX_MSG_TYPES; i++ ){
		msg_enable[i] = false;
        msg_desc  [i] = NULL;
	}
	M_FATAL = alloc_msg( "Fatal: "   ); enable_msg ( M_FATAL );
	M_ERROR = alloc_msg( "Error: "   ); enable_msg ( M_ERROR );
	M_WARN  = alloc_msg( "Warning: " ); enable_msg ( M_WARN  );
	M_DEBUG = alloc_msg( "Debug: "   ); enable_msg ( M_DEBUG );
	M_INIT  = alloc_msg( "Init: "    ); enable_msg ( M_INIT  );
	M_GL    = alloc_msg( "GL: "      ); disable_msg( M_GL    );
	M_WM    = alloc_msg( "WM: "      ); disable_msg( M_WM    );
	M_WMD   = alloc_msg( "WMD: "     ); disable_msg( M_WMD   );
	M_WME   = alloc_msg( "WME: "     ); disable_msg( M_WME   );
	M_WML   = alloc_msg( "WML: "     ); disable_msg( M_WML   );
	M_MAT   = alloc_msg( "MAT: "     ); disable_msg( M_MAT   );
	M_MOD   = alloc_msg( "MOD: "     ); disable_msg( M_MOD   );
	M_LWO   = alloc_msg( "LWO: "     ); disable_msg( M_LWO   );
	M_LWS   = alloc_msg( "LWS: "     ); disable_msg( M_LWS   );
	M_TMAP  = alloc_msg( "TMAP: "    ); disable_msg( M_TMAP  );
	M_VERT  = alloc_msg( "VERT: "    ); disable_msg( M_VERT  );
	M_FFE   = alloc_msg( "FFE: "     ); disable_msg( M_FFE   );
	M_NET   = alloc_msg( "NET: "     ); disable_msg( M_NET   );
	M_SCN   = alloc_msg( "SCN: "     ); disable_msg( M_SCN   );
	M_AUDIO = alloc_msg( "AUD: "     ); disable_msg( M_AUDIO );
}


int alloc_msg( const char *desc ){
    msg_desc[last_msg_type] = desc;
    return last_msg_type++;
}


void enable_msg( int type ){
	if( (type >=0) && (type < last_msg_type) ){
		msg_enable[type] = true;
	}
	if( msg_desc[type] != NULL ){
//		printf( "Enabled '%s'\n", msg_desc[type] );
	}
}


void disable_msg( int type ){
	if( (type >=0) && (type < last_msg_type) ){
		msg_enable[type] = false;
	}
	if( msg_desc[type] != NULL ){
//		printf( "Disabled '%s'\n", msg_desc[type] );
	}
}


void msg( int type, const char *format, ... ){
	if( (type >=0) && (type < last_msg_type) ){
		if( msg_enable[type] == true ){
			va_list ap;

			va_start( ap, format );
			/*if( msg_desc[type] != NULL ){
			 printf( msg_desc[type] );
			 }*/
			vfprintf( MSG_DEST, format, ap );
			fprintf ( MSG_DEST, "\n" );
			va_end ( ap );
		}
	}
}


void dmsg( int type, const char *format, ... ){
	if( (type >=0) && (type < last_msg_type) ){
		if( msg_enable[type] == true ){
			va_list ap;

			va_start( ap, format );
			if( msg_desc[type] != NULL ){
				fprintf( MSG_DEST, msg_desc[type] );
			}
			vfprintf( MSG_DEST, format, ap );
			fprintf( MSG_DEST, "\n" );
			va_end ( ap );
		}
	}
}


void dprint( int type, const char *format, ... ){
	if( (type >=0) && (type < last_msg_type) ){
		if( msg_enable[type] == true ){
			va_list ap;
			va_start( ap, format );
			vfprintf( MSG_DEST, format, ap );
			va_end ( ap );
		}
	}
}


void emsg( int type, const char *format, ... ){
	if( (type >=0) && (type < last_msg_type) ){
		va_list ap;

		va_start( ap, format );
		if( msg_desc[type] != NULL ){
			fprintf( MSG_DEST, msg_desc[type] );
		}
		vfprintf( MSG_DEST, format, ap );
		fprintf ( MSG_DEST, "\n" );
		va_end ( ap );
	}
}


void fmsg( int type, const char *format, ... ){
	if( (type >=0) && (type < last_msg_type) ){
		va_list ap;

		va_start( ap, format );
		if( msg_desc[type] != NULL ){
			fprintf( MSG_DEST, msg_desc[type] );
		}
		vfprintf( MSG_DEST, format, ap );
		fprintf ( MSG_DEST, "\n" );
		va_end ( ap );
	}
	exit( 1 );
}


};  //  namespace SysSupport
};  //  namespace Teddy

