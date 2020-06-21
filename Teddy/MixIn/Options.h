
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

	$Id: Options.h,v 1.6 2002/03/12 10:46:06 tksuoran Exp $
*/


#ifndef TEDDY__MIX_IN__OPTIONS_H
#define TEDDY__MIX_IN__OPTIONS_H


namespace Teddy {
namespace MixIn {


//!  Options object mix in
class Options {
public:
	Options();
    Options( const unsigned long options );
    virtual ~Options();

	void           setOptions  ( const unsigned long options );
	unsigned long  getOptions  () const;
	unsigned long  operator &  ( const Options &other );
	unsigned long  operator |  ( const Options &other );
	Options       &operator &= ( const Options &other );
	Options       &operator |= ( const Options &other );
	Options       &operator ^= ( const Options &other );
	void           enable      ( const unsigned long options );
	void           disable     ( const unsigned long options );
	void           toggle      ( const unsigned long options );
	bool           isEnabled   ( const unsigned long options );
	const char    *isEnabledStr( const unsigned long options );
	bool           isDisabled  ( const unsigned long options );

protected:
	unsigned long options;
};


};  //  namespace MixIn
};  //  namespace Teddy


#endif  //  TEDDY__MIX_IN__OPTIONS_H

