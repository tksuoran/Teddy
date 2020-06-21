
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

	$Id: FileScan.cpp,v 1.6 2002/02/16 16:38:11 tksuoran Exp $
*/


#include "Teddy/SysSupport/FileScan.h"

#ifndef SWIG
#if defined( _WIN32 )
# include <windows.h>
#else
# include <cstdio>
# include <sys/types.h>
# include <errno.h>
# include <glob.h>
#endif
#endif


namespace Teddy      {
namespace SysSupport {


const char *fix_file_name( const char *prefix, const char *file_name ){
	if( strlen(file_name)==0 ){
		return NULL;
	}
	if( file_name == NULL ){
		return NULL;
	}

	const char *walker = file_name;

	//  Scan for end of string
	while( *walker != 0 ){
		walker++;
	}

	//  Scan to last /, if any
	while( walker != file_name ){
		walker--;
		if( *walker == '/' || *walker == '\\' ){
			walker++;
			break;
		}
	}

	if( prefix != NULL ){
		const char *fixed_file_name = walker;
		int   final_length    = strlen( fixed_file_name ) + strlen( prefix ) + 1;
		char *final_file_name = new char[ final_length];
		sprintf( final_file_name, "%s%s", prefix, fixed_file_name );
		return final_file_name;
	}else{
		return walker+1;
	}
}


FileScan::~FileScan(){
	list<char*>::iterator f_it = files.begin();

	while( f_it != files.end() ){
		char *fname = *f_it;
		delete[] fname;
		f_it++;
	}

}

#if defined( _WIN32 )  //  PLATFORM SELECTION - WIN32


FileScan::FileScan( const char *mask ){
	WIN32_FIND_DATA fData;
	HANDLE          search;

	search = FindFirstFile( mask, &fData );

	if( search == INVALID_HANDLE_VALUE ){
		return;
	}

	do{
		char *fnam = new char[ strlen(fData.cFileName)+2 ];
		strcpy(fnam, fData.cFileName );
		files.push_back(fnam);
	}while( FindNextFile( search, &fData ) );
}


#elif 1  // PLATFORM SELECTION - ASSUME POSIX


// FIXME: this could use some better error handling...
FileScan::FileScan( const char *pattern ) : files() {
	glob_t g;

#	ifdef GLOB_TILDE
	int r = glob( pattern, GLOB_MARK|GLOB_TILDE, NULL, &g );
#	else
	int r = glob( pattern, GLOB_MARK, NULL, &g );
#	endif

	if( r!=0 ){
		//fprintf(  stderr, "glob(3) failed for \"%s\": %s\n", pattern, strerror(errno)  );
		exit( EXIT_FAILURE );
	}

	for( int i=0; (long)(i)<(long)(g.gl_pathc); i++ ){
		char *fnam = new char[ strlen(g.gl_pathv[i]) + 2 ];
		strcpy(fnam, g.gl_pathv[i] );
		files.push_back(fnam);
	}
	globfree( &g );
}


#else

#error "Target has no implementation for FileScan class"

#endif  // PLATFORM_SELECTION


};  //  namespace SysSupport
};  //  namespace Teddy

