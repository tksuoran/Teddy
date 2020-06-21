
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

	$Id: Options.cpp,v 1.6 2002/03/12 10:46:06 tksuoran Exp $
*/


#include "Teddy/MixIn/Options.h"


namespace Teddy {
namespace MixIn {


//!  Options constructor
Options::Options(){
	options = 0;
}


//!  Options constructor
Options::Options( const unsigned long options ){
	this->options = options;
}


/*virtual*/ Options::~Options(){
}


//!  Set flags
void Options::setOptions( const unsigned long options ){
	this->options = options;
}


//!  Get render options flags
unsigned long Options::getOptions() const {
	return this->options;
}


//!  Enable Flags
void Options::enable( const unsigned long options ){
	this->options |= options;
}


//!  Disable flags
void Options::disable( const unsigned long options ){
	this->options &= ~options;
}


//!  Toggle options
void Options::toggle( const unsigned long options ){
	this->options ^= options;
}


unsigned long Options::operator &( const Options &other ){
	return options & other.getOptions();
}


unsigned long Options::operator |( const Options &other ){
	return options | other.getOptions();
}


Options &Options::operator &=( const Options &other ){
	options &= other.getOptions();
	return *this;
}


Options &Options::operator |=( const Options &other ){
	options |= other.getOptions();
	return *this;
}


Options &Options::operator ^=( const Options &other ){
	options ^= other.getOptions();
	return *this;
}


//!  Return true if all selected options are enabled
bool Options::isEnabled( const unsigned long options ){
	if( (this->options & options) == options ){
		return true;
	}else{
		return false;
	}
}


const char *Options::isEnabledStr( const unsigned long options ){
	if( isEnabled(options) ){
		return "enabled";
	}else{
		return "disabled";
	}
}


//!  Return true if all selected options are disabled
bool Options::isDisabled( const unsigned long options ){
	if( (this->options & options) == 0 ){
		return true;
	}else{
		return false;
	}
}


};  //  namespace MixIn
};  //  namespace Teddy

