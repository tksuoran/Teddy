
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


#ifndef TEDDY__SYS_SUPPORT__ENDIAN_IO__H
#define TEDDY__SYS_SUPPORT__ENDIAN_IO__H


#include "Teddy/SysSupport/StdMaths.h"
#include <fstream>
using namespace std;


namespace Teddy      {
namespace SysSupport {


/*!
	\brief   Baseclass for endian sensitive file reading and writing

	A very very poor implementation for endian independent access
	to endian sensitive data,
*/
class EndianIO {
	enum { MSBfirst, LSBfirst } byte_order;

public:
	EndianIO();

	void set_bigendian   ();
	void set_littlendian ();
	bool q_MSBfirst      () const;
};


};  //  namespace SysSupport
};  //  namespace Teddy


#endif  //  TEDDY__SYS_SUPPORT__ENDIAN_IO__H

