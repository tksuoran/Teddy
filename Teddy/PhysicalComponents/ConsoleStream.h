
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


#ifndef TEDDY__PHYSICAL_COMPONENTS__CONSOLE_STREAM__H
#define TEDDY__PHYSICAL_COMPONENTS__CONSOLE_STREAM__H


#if 0
#include "Teddy/PhysicalComponents/ConsoleStreamBuffer.h"
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
	\brief ConsoleStream
	\todo  docs
*/
class ConsoleStream : public ostream {
public:
	ConsoleStream()
	:
	ostream( csb = new ConsoleStreamBuffer() ), ios( 0 )
	{
	}

	void setCon( Console *con ){
		csb->setCon( con );
	}

protected:
	ConsoleStreamBuffer *csb;
};


};  //  namespace PhysicalComponents
};  //  namespace Teddy
#endif


#endif  //  TEDDY__PHYSICAL_COMPONENTS__CONSOLE_STREAM__H

