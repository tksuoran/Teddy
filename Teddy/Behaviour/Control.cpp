
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

	$Id:  $
*/


#include "Teddy/Behaviour/Control.h"
using namespace Teddy::MixIn;

namespace Teddy     {
namespace Behaviour {


/*static*/ const unsigned long Control::RESERVED        = 0ul;
/*static*/ const unsigned long Control::MORE            = 1ul;
/*static*/ const unsigned long Control::LESS            = 2ul;
/*static*/ const unsigned long Control::STOP            = 3ul;
/*static*/ const unsigned long Control::ACTIVE          = 4ul;
/*static*/ const unsigned long Control::INHIBIT         = 5ul;
/*static*/ const unsigned long Control::DAMPEN_LINEAR   = 6ul;
/*static*/ const unsigned long Control::DAMPEN_MULTIPLY = 7ul;
/*static*/ const unsigned long Control::DAMPEN_MASTER   = 8ul;
														
/*static*/ const unsigned long Control::RESERVED_M        = (1ul<<Control::RESERVED       );
/*static*/ const unsigned long Control::MORE_M            = (1ul<<Control::MORE           );
/*static*/ const unsigned long Control::LESS_M            = (1ul<<Control::LESS           );
/*static*/ const unsigned long Control::STOP_M            = (1ul<<Control::STOP           );
/*static*/ const unsigned long Control::ACTIVE_M          = (1ul<<Control::ACTIVE         );
/*static*/ const unsigned long Control::INHIBIT_M         = (1ul<<Control::INHIBIT        );
/*static*/ const unsigned long Control::DAMPEN_LINEAR_M   = (1ul<<Control::DAMPEN_LINEAR  );
/*static*/ const unsigned long Control::DAMPEN_MULTIPLY_M = (1ul<<Control::DAMPEN_MULTIPLY);
/*static*/ const unsigned long Control::DAMPEN_MASTER_M   = (1ul<<Control::DAMPEN_MASTER  );

/*static*/ const unsigned long Control::CLEAR_M =
	Control::MORE_M    |  
	Control::LESS_M    |  
	Control::STOP_M    |  
	Control::ACTIVE_M  |  
	Control::INHIBIT_M;


//!  Constructor
Control::Control( double max_delta, double max, Options options, double dampen_const )
:
Options     (options),
//c_more      (false ),
//c_less      (false ),
//c_stop      (false ),
//c_active    (false ),
//c_inhibit   (false ),
//c_dampen_lin(dampen_lin),
//c_dampen_mul(dampen_mul),
dampen_const(dampen_const),
max_delta   (max_delta),
min         (-max ),
max         ( max ),
c_delta     (0),
c_value     (0)
{
}


void Control::setValue( double value ){
	c_value = value;
}


double Control::getValue() const {
	return c_value;
}


double Control::getMin() const {
	return min;
}


double Control::getMax() const {
	return max;
}


double Control::getDelta() const {
	return max_delta;
}


double Control::getDampConst() const {
	return dampen_const;
}


void Control::setDelta( double max_delta ){
	this->max_delta = max_delta;
}


void Control::setDampConst( double dampen_const ){
	this->dampen_const = dampen_const;
}


void Control::clear(){
	disable( Control::CLEAR_M );
//	c_more    = false;
//	c_less    = false;
//	c_stop    = false;
//	c_active  = false;
//	c_inhibit = false;
	c_delta   = 0;
	c_value   = 0;
}


//!  Update Control (Teddy::MixIn::Tick API)
/*virtual*/ void Control::tick(){
	static const double age = 10.0;

	if( isEnabled(Control::ACTIVE_M) && isDisabled(Control::INHIBIT_M) ){
		adjust( c_delta * age );
	}
	dampen();
}


//!  Adjust Control value
void Control::adjust( double delta ){
	c_value += delta;

	if( c_value>max ){
		c_value = max;
	}else if( c_value<min ){
		c_value = min;
	}
}


//!  Dampen Control
void Control::dampen(){
	static const double age = 10.0;

	if( isEnabled(Control::DAMPEN_MULTIPLY_M) ){

		c_value *= dampen_const;

	}else if( isEnabled(Control::DAMPEN_LINEAR_M) && isDisabled(Control::ACTIVE_M) ){

		if( c_value > max_delta ){
			c_value -= max_delta*age; 
			if( c_value < max_delta ){
				c_value = 0;
			}
		}else if( c_value < -max_delta ){
			c_value += max_delta*age;
			if( c_value > -max_delta ){
				c_value = 0;
			}
		}else{
			c_value *= dampen_const;
		}
	}
}


//!  Activate or deactivate more Control
void Control::more( bool apply ){
	if( apply ){
		enable( Control::MORE_M | Control::ACTIVE_M );
		c_delta  =  max_delta;
	}else{
		disable( Control::MORE_M );
		if( isEnabled(Control::LESS_M) ){
			c_delta  = -max_delta;
		}else{
			disable( Control::ACTIVE_M );
			c_delta  =  0;
		}
	}
}


//!  Activate or deactivate less Control
void Control::less( bool apply ){
	if( apply ){
		enable( Control::LESS_M | Control::ACTIVE_M );
		c_delta  = -max_delta;
	}else{
		disable( Control::LESS_M );
		if( isEnabled(Control::MORE_M) ){
			c_delta  =  max_delta;
		}else{
			disable( Control::ACTIVE_M );
			c_delta  =  0;
		}
	}
}


//!  Stop Control
void Control::stop( bool apply ){
	if( apply ){
		enable( Control::STOP_M );
		if( c_value > 0 ){
			c_delta  = -max_delta;
		}else if( c_value < 0 ){
			c_delta  =  max_delta;
		}
	}else{
		disable( Control::STOP_M );
		if( isEnabled(Control::LESS_M) && isDisabled(Control::MORE_M) ){
			c_delta = -max_delta;
		}else if( isEnabled(Control::MORE_M) && isDisabled(Control::LESS_M) ){
			c_delta =  max_delta;
		}
	}
}


};  //  namespace Behaviour
};  //  namespace Teddy

