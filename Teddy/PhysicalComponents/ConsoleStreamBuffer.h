
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


#ifndef TEDDY__PHYSICAL_COMPONENTS__CONSOLE_STREAM_BUFFER__H
#define TEDDY__PHYSICAL_COMPONENTS__CONSOLE_STREAM_BUFFER__H


#if 0
#include "Teddy/PhysicalComponents/Console.h"
#if defined(_MSC_VER)
# include <ostream>
#else  //  gcc
//# include <ostream.h>
#endif
using namespace std;


namespace Teddy              {
namespace PhysicalComponents {


/*!
	\brief ConsoleStreamBuffer
	\todo  docs
*/
class ConsoleStreamBuffer : public streambuf {
public:
	ConsoleStreamBuffer(){
		this->_con = NULL;
	}

	void setCon( Console *con ){
		this->_con = con;
	}
	virtual int overflow( int c );

private:
	Console *_con;
};


};  //  namespace PhysicalComponents
};  //  namespace Teddy


#endif

#endif  //  TEDDY__PHYSICAL_COMPONENTS__CONSOLE_STREAM_BUFFER__H

