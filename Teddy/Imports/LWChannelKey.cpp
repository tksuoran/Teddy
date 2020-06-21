
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

	$Id: LWChannelKey.cpp,v 1.1 2002/02/16 12:41:39 tksuoran Exp $
*/


#include "Teddy/TeddyConfig.h"
#if defined( TEDDY_INCLUDE_LW_SCENE )


#include "Teddy/Imports/LWChannelKey.h"


namespace Teddy   {
namespace Imports {


LWChannelKey::LWChannelKey(
	float value,
	float time,
	int   shape,
	float p1,
	float p2,
	float p3,
	float p4,
	float p5,
	float p6
)
:
value(value),
time (time ),
shape(shape),
p1   (p1   ),
p2   (p2   ),
p3   (p3   ),
p4   (p4   ),
p5   (p5   ),
p6   (p6   )
{
}


/*

In scene files, an envelope is stored in a block named Envelope that
contains one or more nested Key blocks and one Behaviors block.

   { Envelope
     nkeys
     Key value time spantype p1 p2 p3 p4 p5 p6
     Key ...
     Behaviors pre post
   }

The nkeys value is an integer, the number of Key blocks in the envelope.
Envelopes must contain at least one Key block. The contents of a Key block
are as follows. 

value  The key value, a floating-point number. The units and limits of the
       value depend on what parameter the envelope represents. 

time   The time in seconds, a float. This can be negative, zero or positive.
       Keys are listed in the envelope in increasing time order. 

spantype  The curve type, an integer. This determines the kind of interpolation
          that will be performed on the span between this key and the previous
		  key, and also indicates what interpolation parameters are stored for
		  the key. 

0 - TCB (Kochanek-Bartels) 
1 - Hermite 
2 - 1D Bezier (obsolete, equivalent to Hermite) 
3 - Linear 
4 - Stepped 
5 - 2D Bezier 

p1...p6   Curve parameters. The data depends on the span type. 

TCB, Hermite, 1D Bezier

The first three parameters are tension, continuity and bias. The fourth and fifth
parameters are the incoming and outgoing tangents. The sixth parameter is ignored
and should be 0. Use the first three to evaluate TCB spans, and the other two to
evaluate Hermite spans. 

2D Bezier 

The first two parameters are the incoming time and value, and the second two are
the outgoing time and value. The Behaviors block contains two integers.

pre, post 

Pre- and post-behaviors. These determine how the envelope is extrapolated at
times before the first key and after the last one. 

0 - Reset         Sets the value to 0.0. 
1 - Constant      Sets the value to the value at the nearest key. 
2 - Repeat        Repeats the interval between the first and last keys (the primary interval). 
3 - Oscillate     Like Repeat, but alternating copies of the primary interval are time-reversed. 
4 - Offset Repeat Like Repeat, but offset by the difference between the values of the first and last keys. 
5 - Linear        Linearly extrapolates the value based on the tangent at the nearest key. */


};  //  namespace Imports   
};  //  namespace Teddy


#endif  //  TEDDY_INCLUDE_LW_SCENE


