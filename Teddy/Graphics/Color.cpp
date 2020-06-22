
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


#include "Teddy/Graphics/Color.h"
#include "Teddy/Graphics/Device.h"
#include "Teddy/SysSupport/StdIO.h"


namespace Teddy    {
namespace Graphics {


Color Color::BLACK         = Color( C_BLACK         );
Color Color::WHITE         = Color( C_WHITE         );
Color Color::RED           = Color( C_RED           );
Color Color::GREEN         = Color( C_GREEN         );
Color Color::BLUE          = Color( C_BLUE          );
Color Color::GRAY          = Color( C_GRAY          );
Color Color::CYAN          = Color( C_CYAN          );
Color Color::MAGENTA       = Color( C_MAGENTA       );
Color Color::YELLOW        = Color( C_YELLOW        );
Color Color::ORANGE        = Color( C_ORANGE        );
Color Color::DARK_RED      = Color( C_DARK_RED      );
Color Color::DARK_GREEN    = Color( C_DARK_GREEN    );
Color Color::DARK_BLUE     = Color( C_DARK_BLUE     );
Color Color::DARK_CYAN     = Color( C_DARK_CYAN     );
Color Color::DARK_MAGENTA  = Color( C_DARK_MAGENTA  );
Color Color::DARK_YELLOW   = Color( C_DARK_YELLOW   );
Color Color::DARK_ORANGE   = Color( C_DARK_ORANGE   );
Color Color::LIGHT_RED     = Color( C_LIGHT_RED     );
Color Color::LIGHT_GREEN   = Color( C_LIGHT_GREEN   );
Color Color::LIGHT_BLUE    = Color( C_LIGHT_BLUE    );
Color Color::LIGHT_CYAN    = Color( C_LIGHT_CYAN    );
Color Color::LIGHT_MAGENTA = Color( C_LIGHT_MAGENTA );
Color Color::LIGHT_YELLOW  = Color( C_LIGHT_YELLOW  );
Color Color::LIGHT_ORANGE  = Color( C_LIGHT_ORANGE  );
Color Color::GRAY_25       = Color( C_GRAY_25       );
Color Color::GRAY_50       = Color( C_GRAY_50       );
Color Color::GRAY_75       = Color( C_GRAY_75       );


//!  Default Color constructor
Color::Color(){
	this->rgba[0] = 0;
	this->rgba[1] = 0;
	this->rgba[2] = 0;
	this->rgba[3] = 1;
}


/*!
	\brief Color constructor with given rgb components
	\param r Red, normal values 0..1
	\param g Green, normal values 0..1
	\param b Blue, normal values 0..1
*/
Color::Color( const float r, const float g, const float b ){
	this->rgba[0] = r;
	this->rgba[1] = g;
	this->rgba[2] = b;
	this->rgba[3] = 1;
}


/*!
	\brief Color constructor with given rgba components
	\param r Red, normal values 0..1
	\param g Green, normal values 0..1
	\param b Blue, normal values 0..1
	\param a Alpha, normal values 0..1
*/
Color::Color( const float r, const float g, const float b, const float a ){
	this->rgba[0] = r;
	this->rgba[1] = g;
	this->rgba[2] = b;
	this->rgba[3] = a;
}


/*!
	\brief Color constructor with given rgba components in array
	\param rgba Pointer to C array of four floats for red, green, blue and alpha. 
*/
Color::Color( const float rgba[4] ){
	this->rgba[0] = rgba[0];
	this->rgba[1] = rgba[1];
	this->rgba[2] = rgba[2];
	this->rgba[3] = rgba[3];
}


//!  Debugging information
void Color::debug(){
//	cout << "( " << rgba[0] << ", " << rgba[1] << ", " << rgba[2] << "; " << rgba[3] << " )";
}


//!  Apply color to OpenGL state
void Color::glApply() const {
	glColor4fv( rgba );
}


/*!
	\brief   Add two colors together
	\param   c The other Color to be added to this Color
	\return  Sum of the two colors
	\warning There is no check for overflows
*/
Color Color::operator+( const Color &c ) const {
	return Color(
		rgba[0] + c.rgba[0],
		rgba[1] + c.rgba[1],
		rgba[2] + c.rgba[2],
		rgba[3] + c.rgba[3]
	);
}


/*!
	\brief   Add two colors together
	\param   c The other Color to be added to this Color
	\return  Sum of the two colors
	\warning There is no check for overflows
*/
Color &Color::operator+=( const Color &c ){
	rgba[0] += c.rgba[0];
	rgba[1] += c.rgba[1];
	rgba[2] += c.rgba[2];
	rgba[3] += c.rgba[3];
	return *this;
}


/*!
	\brief   Substract other Color from this Color
	\param   c The other Color to be substracted from this Color
	\return  LHS color minus the RHS color
	\warning There is no check for underflows
*/
Color Color::operator-( const Color &c ) const {
	return Color(
		rgba[0] - c.rgba[0],
		rgba[1] - c.rgba[1],
		rgba[2] - c.rgba[2],
		rgba[3] - c.rgba[3]
	);
}


/*!
	\brief   Substract other Color from this Color
	\param   c The other Color to be substracted from this Color
	\return  The original color minus the other color
	\warning There is no check for underflows
*/
Color &Color::operator-=( const Color &c ){
	rgba[0] -= c.rgba[0];
	rgba[1] -= c.rgba[1];
	rgba[2] -= c.rgba[2];
	rgba[3] -= c.rgba[3];
	return *this;
}


/*!
	\brief   Multiply this Color with a scalar
	\param   k Scalar value with which each Color component is multiplied
	\return	 The LHS Color multiplied by the RHS scalar
	\warning There is no checking for overflows
*/
Color Color::operator*( const float &k ) const {
	return Color(
		rgba[0] * k,
		rgba[1] * k,
		rgba[2] * k,
		rgba[3] * k
	);
}


/*!
	\brief   Multiply this Color with a scalar
	\param   k Scalar value with which each Color component is multiplied
	\return	 The original Color multiplied by the RHS scalar
	\warning There is no checking for overflows
*/
Color &Color::operator*=( const float &k ){
	rgba[0] *= k;
	rgba[1] *= k;
	rgba[2] *= k;
	rgba[3] *= k;
	return( *this );
}



// Needed by rgb2hsv()
float Color::maxrgb( float r, float g, float b ){
  float max;
  
  if( r > g){
    max = r;
  }else{
    max = g;
  }
  if( b > max ){
    max = b;
  }
  return max;
}


// Needed by rgb2hsv()
float Color::minrgb( float r, float g, float b ){
  float min;
  
  if( r < g ){
    min = r;
  }else{
    min = g;
  }
  if( b < min ){
    min = b;
  }
  return min;
}

/* Taken from "Fund'l of 3D Computer Graphics", Alan Watt (1989)
   Assumes (r,g,b) range from 0.0 to 1.0
   Sets h in degrees: 0.0 to 360.;
      s,v in [0.,1.]
*/
void Color::rgb2hsv( float r, float g, float b, float *hout, float *sout, float *vout ){
  float h=0;
  float s=1.0;
  float v=1.0;
  float max_v,min_v,diff,r_dist,g_dist,b_dist;
  float undefined = 0.0;

  max_v = maxrgb(r,g,b);
  min_v = minrgb(r,g,b);
  diff  = max_v - min_v;
  v     = max_v;

  if( max_v != 0 ){
    s = diff/max_v;
  }else{
    s = 0.0;
  }
  if( s == 0 ){
    h = undefined;
  }else {
    r_dist = (max_v - r)/diff;
    g_dist = (max_v - g)/diff;
    b_dist = (max_v - b)/diff;
    if( r == max_v ){
      h = b_dist - g_dist;
    }else{
		if( g == max_v ){
			h = 2 + r_dist - b_dist;
		}else{
			if( b== max_v ){
				h = 4 + g_dist - r_dist;
			}else{
				printf("rgb2hsv::How did I get here?\n");
			}
		}
	}
    h *= 60;
    if( h < 0){
      h += 360.0;
	}
  }
  *hout = h;
  *sout = s;
  *vout = v;
}

/* Taken from "Fund'l of 3D Computer Graphics", Alan Watt (1989)
   Assumes H in degrees, s,v in [0.,1.0];
   (r,g,b) range from 0.0 to 1.0
*/
void Color::hsv2rgb( float hin, float s, float v, float *rout, float *gout, float *bout ){
  float h;																		 
  float r=0;
  float g=0;
  float b=0;
  float f,p,q,t;
  int   i;

  h = hin;
  if( s == 0 ) {
    r = v;
    g = v;
    b = v;
  }else {
	  if(h == 360.){
		h = 0.0;
	  }
    h /= 60.;
    i = (int) h;
    f = h - i;
    p = v*(1-s);
    q = v*(1-(s*f));
    t = v*(1-s*(1-f));
    switch(i) {
    case 0:
      r = v;
      g = t;
      b = p;
      break;
    case 1:
      r = q;
      g = v;
      b = p;
      break;
    case 2:
      r = p;
      g = v;
      b = t;
      break;
    case 3:
      r = p;
      g = q;
      b = v;
      break;
    case 4:
      r = t;
      g = p;
      b = v;
      break;
    case 5:
      r = v;
      g = p;
      b = q;
      break;
    default:
      r = 1.0;
      b = 1.0;
      b = 1.0;
      //printf("hsv2rgb::How did I get here?\n");
      // printf("h: %f, s: %f, v: %f; i:  %d\n",hin,s,v,i);
      break;
    }
  }
  *rout = r;
  *gout = g;
  *bout = b;
}


};  //  namespace Graphics
};  //  namespace Teddy
