
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

	$Id: Named.cpp,v 1.5 2002/02/16 12:41:39 tksuoran Exp $
*/


#include "Teddy/MixIn/Named.h"
#include "Teddy/SysSupport/StdString.h"
#include "Teddy/SysSupport/StdIO.h"


namespace Teddy {
namespace MixIn {


//!  Named constructor without parameters
Named::Named(){
	name      = "unnamed";
}


//!  Named constructor with char * name parameter
Named::Named( const std::string &name ):name(name){
//    printf( "Named::Named( const std::string &name = %s )\n", getName().c_str() );
}


/*virtual*/ Named::~Named(){
}


//!  Name accessor
const std::string &Named::getName() const {
//    printf( "Named::getName() = %s\n", name.c_str() );
	return name;
}


//!  Name accessor for char * parameter
void Named::setName( const std::string &name ){
	this->name = name;
}


};  //  namespace MixIN
};  //  namespace Teddy

