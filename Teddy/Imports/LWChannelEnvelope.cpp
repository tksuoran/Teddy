
/*
	TEDDY - General graphics application library
	Copyright (C) 1999-2020  Timo Suoranta
	tksuoran@gmail.com

		Adapted from

		interp.c and envelope.h from lwsdk7.zip
		Interpolation (and extrapolation) of LightWave envelopes.
		Ernie Wright  16 Nov 00

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


#include "Teddy/TeddyConfig.h"
#if defined( TEDDY_INCLUDE_LW_SCENE )


#include "Teddy/SysSupport/StdMaths.h"
#include "Teddy/Imports/LWChannelEnvelope.h"
#include "Teddy/Imports/LWChannelKey.h"
#include "Teddy/SysSupport/Messages.h"
using namespace Teddy::SysSupport;


namespace Teddy   {
namespace Imports {


LWChannelEnvelope::LWChannelEnvelope( int channel_id )
:
	channel_id     ( channel_id ),
	steps          ( 0 ),
	pre_behavior   ( 0 ),
	post_behavior  ( 0 ),
	last_time      ( -666 ),
	last_value     ( 0 )
{
}


int LWChannelEnvelope::getChannelId(){
	return this->channel_id;
}


void LWChannelEnvelope::insert( LWChannelKey *channel_key ){
	keys.push_back( channel_key );
}


void LWChannelEnvelope::setBehaviors( int pre, int post ){
	this->pre_behavior  = pre;
	this->post_behavior = post;
}


#include <cstdlib>
#include "Teddy/SysSupport/StdMaths.h"


#define SHAPE_TCB      0
#define SHAPE_HERM     1
#define SHAPE_BEZI     2
#define SHAPE_LINE     3
#define SHAPE_STEP     4
#define SHAPE_BEZ2     5

#define BEH_RESET      0
#define BEH_CONSTANT   1
#define BEH_REPEAT     2
#define BEH_OSCILLATE  3
#define BEH_OFFSET     4
#define BEH_LINEAR     5



/*!
	range()

	Given the value v of a periodic function, returns the equivalent value
	v2 in the principal interval [lo, hi].  If i isn't NULL, it receives
	the number of wavelengths between v and v2.

	v2 = v - i * (hi - lo)

	For example, range( 3 pi, 0, 2 pi, i ) returns pi, with i = 1.
*/
float range( float v, float lo, float hi, int *i ){
	float v2;
	float r = hi - lo;
	
	if( r == 0.0 ){
		if ( i ) *i = 0;
		return lo;
	}
	
	v2 = v - r * ( float ) floor(( v - lo ) / r );
	if ( i ){
		*i = -( int )(( v2 - v ) / r + ( v2 > v ? 0.5 : -0.5 ));
	}
	
	return v2;
}


/*!
	hermite()

	Calculate the Hermite coefficients.
*/
static void hermite( float t, float *h1, float *h2, float *h3, float *h4 ){
	float t2;
	float t3;
	
	t2 = t * t;
	t3 = t * t2;
	
	*h2 = 3.0f * t2 - t3 - t3;
	*h1 = 1.0f - *h2;
	*h4 =  t3 - t2;
	*h3 = *h4 - t2 + t;
}


/*!
	bezier()

	Interpolate the value of a 1D Bezier curve.
*/
static float bezier( float x0, float x1, float x2, float x3, float t ){
	float a;
	float b;
	float c;
	float t2;
	float t3;
	
	t2 = t  * t;
	t3 = t2 * t;
	
	c  = 3.0f * ( x1 - x0 );
	b  = 3.0f * ( x2 - x1 ) - c;
	a  = x3 - x0 - c - b;
	
	return a * t3 + b * t2 + c * t + x0;
}


/*!
	bez2_time()

	Find the t for which bezier() returns the input time.  The handle
	endpoints of a BEZ2 curve represent the control points, and these have
	(time, value) coordinates, so time is used as both a coordinate and a
	parameter for this curve type.
*/
float bez2_time( float x0, float x1, float x2, float x3, float time, float *t0, float *t1 ){
	float v, t;
	
	t = *t0 + ( *t1 - *t0 ) * 0.5f;
	v = bezier( x0, x1, x2, x3, t );
	if( fabs( time - v ) > .0001f ){
		if( v > time ){
		   *t1 = t;
		}else{
		   *t0 = t;
		}
		return bez2_time( x0, x1, x2, x3, time, t0, t1 );
	}else{
		return t;
	}
}


/*!
	bez2()

	Interpolate the value of a BEZ2 curve.
*/
float bez2( LWChannelKey *key0, LWChannelKey *key1, float time ){
	float x;
	float y;
	float t;
	float t0 = 0.0f;
	float t1 = 1.0f;

	x = (key0->time  + ( key0->shape == SHAPE_BEZ2 )) ? key0->p3 : ( key1->time - key0->time ) / 3.0f;
	t = bez2_time     ( key0->time, x, key1->time + key1->p1, key1->time, key0->time, &t0, &t1 );
	y = (key0->value + ( key0->shape == SHAPE_BEZ2 )) ? key0->p4 : key0->p2 / 3.0f;

	return bezier( key0->value, y, key1->p2 + key1->value, key1->value, t );
}


/*
	outgoing()

	Return the outgoing tangent to the curve at key0.  The value returned
	for the BEZ2 case is used when extrapolating a linear pre behavior and
	when interpolating a non-BEZ2 span.
*/
float outgoing( LWChannelKey *prev, LWChannelKey *key0, LWChannelKey *key1 ){
	float a;
	float b;
	float d;
	float t;
	float out;

	switch( key0->shape ){
		case SHAPE_TCB:
			a = ( 1.0f - key0->tension() ) * ( 1.0f + key0->continuity() ) * ( 1.0f + key0->bias() );
			b = ( 1.0f - key0->tension() ) * ( 1.0f - key0->continuity() ) * ( 1.0f - key0->bias() );
			d = key1->value - key0->value;

			if( prev ){
				t   = ( key1->time - key0->time ) / ( key1->time - prev->time );
				out = t * ( a * ( key0->value - prev->value ) + b * d );
			}else{
				out = b * d;
			}
			break;
		
		case SHAPE_LINE:
			d = key1->value - key0->value;
			if( prev ){
				t   = ( key1->time - key0->time ) / ( key1->time - prev->time );
				out = t * ( key0->value - prev->value + d );
			}else{
				out = d;
			}
			break;
		
		case SHAPE_BEZI:
		case SHAPE_HERM:
			out = key0->p5;
			if( prev ){
				out *= ( key1->time - key0->time ) / ( key1->time - prev->time );
			}
			break;
		
		case SHAPE_BEZ2:
			out = key0->p4 * ( key1->time - key0->time );
			if( fabs( key0->p3 ) > 1e-5f ){
				out /= key0->p3;
			}else{
				out *= 1e5f;
			}
			break;
		
		case SHAPE_STEP:
		default:
			out = 0.0f;
			break;
	}
	
	return out;
}


/*
	incoming()

	Return the incoming tangent to the curve at key1.  The value returned
	for the BEZ2 case is used when extrapolating a linear post behavior.
*/
float incoming( LWChannelKey *key0, LWChannelKey *key1, LWChannelKey *next ){
	float a;
	float b;
	float d;
	float t;
	float in;
	
	switch ( key1->shape ){
		case SHAPE_LINE:
			d = key1->value - key0->value;
			if( next ){
				t = ( key1->time - key0->time ) / ( next->time - key0->time );
				in = t * ( next->value - key1->value + d );
			}else{
				in = d;
			}
			break;
		
		case SHAPE_TCB:
			a = ( 1.0f - key1->tension() ) * ( 1.0f - key1->continuity() ) * ( 1.0f + key1->bias() );
			b = ( 1.0f - key1->tension() ) * ( 1.0f + key1->continuity() ) * ( 1.0f - key1->bias() );
			d = key1->value - key0->value;
			
			if( next ){
				t  = ( key1->time - key0->time ) / ( next->time - key0->time );
				in = t * ( b * ( next->value - key1->value ) + a * d );
			}else{
				in = a * d;
			}
			break;
		
		case SHAPE_BEZI:
		case SHAPE_HERM:
			in = key1->p4;
			if( next ){
				in *= ( key1->time - key0->time ) / ( next->time - key0->time );
			}
			break;
			return in;
		
		case SHAPE_BEZ2:
			in = key1->p2 * ( key1->time - key0->time );
			if( fabs( key1->p1 ) > 1e-5f ){
				in /= key1->p1;
			}else{
				in *= 1e5f;
			}
			break;
		
		case SHAPE_STEP:
		default:
			in = 0.0f;
			break;
	}
	
	return in;
}


/*!
	evalEnvelope()

	Given a list of keys and a time, returns the interpolated value of the
	envelope at that time.
*/
float LWChannelEnvelope::eval( float time ){
	if( time==last_time ){
		return last_value;
	}else{
		last_time = time;
	}

	LWChannelKey *prev = NULL;
	LWChannelKey *key0 = NULL;
	LWChannelKey *key1 = NULL;
	LWChannelKey *next = NULL;
	LWChannelKey *skey = NULL;
	LWChannelKey *ekey = NULL;
	float  t;
	float  in;
	float  out;
	float  offset = 0.0f;
	int    noff;

	if( keys.size() == 0 ){
		last_value = 0;
		return last_value;
	}

	//  Get the first key
	list<LWChannelKey*>::iterator k_it = keys.begin();

	//  If there's no key, the value is 0
	if( k_it == keys.end() ){
		last_value = 0;
		return last_value;
	}


	//  Get the endpoints of the interval being evaluated
	ekey = skey = key0 = *k_it; k_it++;

	if( keys.size() == 1 ){
		last_value = key0->value;
		return last_value;
	}

	//  If there's only one key, the value is constant
	if( k_it == keys.end() ){
		last_value = key0->value;
		return last_value;
	}

	if( k_it != keys.end() ){
		prev = ekey;
		ekey = next = *k_it; k_it++;
	}
	while( k_it != keys.end() ){
		prev = ekey;
		ekey = *k_it;
		k_it++;
	}


	//  Use pre-behavior if time is before first key time
	if( time < skey->time ){
		switch( this->pre_behavior ){
		case BEH_RESET:
			last_value = 0;
			return last_value;
		
		case BEH_CONSTANT:
			last_value = skey->value;
			return last_value;
		
		case BEH_REPEAT:
			last_time = time = range( time, skey->time, ekey->time, NULL );
			break;
		
		case BEH_OSCILLATE:
			last_time = time = range( time, skey->time, ekey->time, &noff );
			if( noff % 2 ){
				last_time = time = ekey->time - skey->time - time;
			}
			break;
		
		case BEH_OFFSET:
			last_time = time = range( time, skey->time, ekey->time, &noff );
			offset    = noff * ( ekey->value - skey->value );
			break;
		
		case BEH_LINEAR:
			out        = outgoing( NULL, skey, next ) / ( next->time - skey->time );
			last_value = out * ( time - skey->time ) + skey->value;;
			return last_value;

		default:
			last_value = 0;
			return last_value;
		}
	}

	//  Use post-behavior if time is after last key time
	else if( time > ekey->time ){
		switch( post_behavior ){
		case BEH_RESET:
			last_value = 0;
			return last_value;
		
		case BEH_CONSTANT:
			last_value = ekey->value;
			return last_value;
		
		case BEH_REPEAT:
			time = range( time, skey->time, ekey->time, NULL );
			break;
		
		case BEH_OSCILLATE:
			last_time = time = range( time, skey->time, ekey->time, &noff );
			if( noff % 2 ){
			   last_time = time = ekey->time - skey->time - time;
			}
			break;
		
		case BEH_OFFSET:
			last_time = time = range( time, skey->time, ekey->time, &noff );
			offset    = noff * ( ekey->value - skey->value );
			break;
		
		case BEH_LINEAR:
			in = incoming( prev, ekey, NULL ) / ( ekey->time - prev->time );
			last_value = in * ( time - ekey->time ) + ekey->value;
			return last_value;

		default:
			last_value = 0;
			return last_value;
		}
	}


	//  Get the endpoints of the interval being evaluated
	k_it = keys.begin();
	prev = NULL;
	key0 = NULL;
	key1 = NULL;
	next = NULL;
	while( k_it != keys.end() ){
		prev =  key0;
		key0 =  key1;
		key1 = *k_it;
		k_it++;
		if( time <= key1->time ){
			if( key0 == NULL ){
				key0 = key1;
				if( k_it != keys.end() ){
					key1 = *k_it;
				}
			}
			break;
		}
	}
	if( k_it != keys.end() ){
		next = *k_it;
	}

/*	debug_msg(
		"%9.4f <= %9.4f <= %9.4f",
		key0 != NULL ? key0->time : 0,
		time,
		key1 != NULL ? key1->time : 0
	);*/

	//  Check for singularities first
	if( time == key0->time ){
		last_value = key0->value + offset;
		return last_value;
	}else if( time == key1->time ){
		last_value = key1->value + offset;
		return last_value;
	}

	if( (key0 == NULL) || (key1 == NULL) ){
		emsg( M_LWO, "Channel Interpolation error" );
		return 0;
	}
	
	//  Get interval length, time in [0, 1]
	t = ( time - key0->time ) / ( key1->time - key0->time );
	
	//  Interpolate
	switch( key1->shape ){
	case SHAPE_TCB:
	case SHAPE_BEZI:
	case SHAPE_HERM:
		out = outgoing( prev, key0, key1 );
		in  = incoming( key0, key1, next );
		float h1;
		float h2;
		float h3;
		float h4;
		hermite( t, &h1, &h2, &h3, &h4 );
		last_value = h1 * key0->value + h2 * key1->value + h3 * out + h4 * in + offset;
		return last_value;
	
	case SHAPE_BEZ2:
		last_value = bez2( key0, key1, time ) + offset;
		return last_value;
	
	case SHAPE_LINE:
		last_value = key0->value + t * ( key1->value - key0->value ) + offset;
		return last_value;
	
	case SHAPE_STEP:
		last_value = key0->value + offset;
		return last_value;
	
	default:
		last_value = offset;
		return last_value;
	}
}


};  //  namespace Imports
};  //  namespace Teddy


#endif  //  TEDDY_INCLUDE_LW_SCENE


/*
Envelopes

An envelope defines a function of time. For any animation time,
an envelope's parameters can be combined to generate a value at
that time. Envelopes are used to store position coordinates,
rotation angles, scale factors, camera zoom, light intensity,
texture parameters, and anything else that can vary over time.

The envelope function is a piecewise polynomial curve. The
function is tabulated at specific points, called keys. The
curve segment between two adjacent keys is called a span, and
values on the span are calculated by interpolating between the
keys. The interpolation can be linear, cubic, or stepped, and
it can be different for each span. The value of the function
before the first key and after the last key is calculated by
extrapolation.

In scene files, an envelope is stored in a block named Envelope
that contains one or more nested Key blocks and one Behaviors block.

   { Envelope
     nkeys
     Key value time spantype p1 p2 p3 p4 p5 p6
     Key ...
     Behaviors pre post
   }

The nkeys value is an integer, the number of Key blocks in
the envelope. Envelopes must contain at least one Key block.
The contents of a Key block are as follows. 

value 

The key value, a floating-point number. The units and limits
of the value depend on what parameter the envelope represents. 

time 

The time in seconds, a float. This can be negative, zero or
positive. Keys are listed in the envelope in increasing time
order. 

spantype 

The curve type, an integer. This determines the kind of
interpolation that will be performed on the span between
this key and the previous key, and also indicates what
interpolation parameters are stored for the key. 

0 - TCB (Kochanek-Bartels) 
1 - Hermite 
2 - 1D Bezier (obsolete, equivalent to Hermite) 
3 - Linear 
4 - Stepped 
5 - 2D Bezier 

p1...p6 Curve parameters. The data depends on the span type. 

TCB, Hermite, 1D Bezier 

The first three parameters are tension(), continuity() and bias().
The fourth and fifth parameters are the incoming and outgoing
tangents. The sixth parameter is ignored and should be 0. Use
the first three to evaluate TCB spans, and the other two to
evaluate Hermite spans. 

2D Bezier 

The first two parameters are the incoming time and value,
and the second two are the outgoing time and value. 

The Behaviors block contains two integers.

pre, post 

Pre- and post-behaviors. These determine how the envelope
is extrapolated at times before the first key and after
the last one. 

0 - Reset          Sets the value to 0.0. 
1 - Constant       Sets the value to the value at the nearest key. 
2 - Repeat         Repeats the interval between the first and last keys (the primary interval). 
3 - Oscillate      Like Repeat, but alternating copies of the primary interval are time-reversed. 
4 - Offset Repeat  Like Repeat, but offset by the difference between the values of the first and last keys. 
5 - Linear         Linearly extrapolates the value based on the tangent at the nearest key. 

The source code in the sample/envelope directory of the LightWave plug-in SDK demonstrates
how envelopes are evaluated.
*/

