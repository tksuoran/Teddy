
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


#ifndef TEDDY__BEHAVIOUR__CONTROL__H
#define TEDDY__BEHAVIOUR__CONTROL__H


#include "Teddy/MixIn/Tick.h"
#include "Teddy/MixIn/Options.h"


namespace Teddy     {
namespace Behaviour {


class Control
	:
	public Teddy::MixIn::Options,
	public Teddy::MixIn::Tick
{
public:
	static const unsigned long RESERVED         ;
	static const unsigned long MORE             ;
	static const unsigned long LESS             ;
	static const unsigned long STOP             ;
	static const unsigned long ACTIVE           ;
	static const unsigned long INHIBIT          ;
	static const unsigned long DAMPEN_LINEAR    ;
	static const unsigned long DAMPEN_MULTIPLY  ;
	static const unsigned long DAMPEN_MASTER    ;

	static const unsigned long RESERVED_M       ;
	static const unsigned long MORE_M           ;
	static const unsigned long LESS_M           ;
	static const unsigned long STOP_M           ;
	static const unsigned long ACTIVE_M         ;
	static const unsigned long INHIBIT_M        ;
	static const unsigned long DAMPEN_LINEAR_M  ;
	static const unsigned long DAMPEN_MULTIPLY_M;
	static const unsigned long DAMPEN_MASTER_M  ;

	static const unsigned long CLEAR_M          ;

public:
	Control( double max_delta, double max, Teddy::MixIn::Options options, double dampen_const );

	//  Teddy::MixIn::Tick API
	virtual void tick();

	//  BaseControl API
	void   setValue     ( double value );
	double getValue     () const;
	double getMin       () const;
	double getMax       () const;
	double getDelta     () const;
	double getDampConst () const;
	void   setDelta     ( double max_delta    );
	void   setDampConst ( double dampen_const );
	void   adjust       ( double analog       );
	void   more         ( bool apply );
	void   less         ( bool apply );
	void   stop         ( bool apply );
	void   inhibit      ( bool apply );
	void   clear        ();
	void   dampen       ();

protected:
	double  dampen_const;  //!<  Multiplying dampening constant
	double  max_delta;     //!<  Maximum change
	double  min;           //!<  Mimimum value
	double  max;           //!<  Maximum value
	double  c_delta;       //!<  Currently active change
	double  c_value;       //!<  Current value
};


};  //  namespace Behaviour
};  //  namespace Teddy


#endif  //  TEDDY__BEHAVIOUR__CONTROL__H

