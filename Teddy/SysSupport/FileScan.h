
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


#ifndef TEDDY__SYS_SUPPORT__FILE_SCAN__H
#define TEDDY__SYS_SUPPORT__FILE_SCAN__H


#include "Teddy/SysSupport/StdList.h"


namespace Teddy      {
namespace SysSupport {


extern const char *fix_file_name( const char *prefix, const char *file_name );


/*!
	\brief   Scan for pattern matching files (in single directory)
	\warning Minimal implementation
	\bug     Implementations for WIN32 and POSIX work differently?!
*/
class FileScan {
public:
	FileScan( const char *pattern );
	~FileScan();

	inline list<char*> &get_files(){
		return files;
	};
	inline const list<char *> &get_files() const {
		return files;
	};

private:
	list<char *> files;
};


};  //  namespace SysSupport
};  //  namespace Teddy


#endif	//	TEDDY__SYS_SUPPORT__FILE_SCAN__H

