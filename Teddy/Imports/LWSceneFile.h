
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

	$Id: LWSceneFile.h,v 1.2 2002/02/16 16:38:11 tksuoran Exp $
*/


#ifndef TEDDY__IMPORTS__LW_SCENE_FILE__H
#define TEDDY__IMPORTS__LW_SCENE_FILE__H


#include "Teddy/TeddyConfig.h"
#if defined( TEDDY_INCLUDE_LW_SCENE )


#include "Teddy/Imports/LWSceneTokens.h"
#include "Teddy/SysSupport/Types.h"
#include "Teddy/SysSupport/StdMap.h"
#include "Teddy/SysSupport/StdIO.h"


namespace Teddy   {
namespace Imports {


struct less_str {
	bool operator()( char *a, char *b ) const {
		if( strcmp(a,b) < 0 ){
			return true;
		}else{
			return false;
		}
	}
};


typedef map<char*, LwsToken, less_str> string_to_token;


//!  LWSceneFile
class LWSceneFile {
public:
	LWSceneFile( const char *fname );
	~LWSceneFile();

	LwsToken       read_token      ();
	int            read_int        ();
	unsigned long  read_hex_int    ();
	double         read_double     ();
	char          *read_string     ();
	bool           read_begin_scope();
	bool           read_end_scope  ();

	void           skip            ();
	void           open            ( const char *fname );
	bool           isOk            ();
	void           close           ();

protected:
	void           mapTokens       ();
	void           mapToken        ( char *key, LwsToken token );

protected:
	FILE            *file;
	string_to_token  token_map;
};


};  //  namespace Imports
};  //  namespace Teddy


#endif  //  TEDDY_INCLUDE_LW_SCENE
#endif  //  TEDDY__IMPORTS__LW_SCENE_FILE__H


