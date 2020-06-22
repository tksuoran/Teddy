
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

	$Id: Features.cpp,v 1.4 2002/01/11 14:34:59 tksuoran Exp $
*/


#include "Teddy/Graphics/View.h"
#include "Teddy/Graphics/Device.h"
#include "Teddy/SysSupport/Messages.h"
using namespace Teddy::SysSupport;


namespace Teddy    {
namespace Graphics {


/*static*/ const unsigned long View::CULL_FACE      =  1;
/*static*/ const unsigned long View::BLEND          =  2;
/*static*/ const unsigned long View::FOG            =  3;
/*static*/ const unsigned long View::NORMALIZE      =  4;
/*static*/ const unsigned long View::ALPHA_TEST     =  5;
/*static*/ const unsigned long View::DEPTH_TEST     =  6;
/*static*/ const unsigned long View::STENCIL_TEST   =  7;
/*static*/ const unsigned long View::SCISSOR_TEST   =  8;
/*static*/ const unsigned long View::TEXTURE_1D     =  9;
/*static*/ const unsigned long View::TEXTURE_2D     = 10;
/*static*/ const unsigned long View::POINT_SMOOTH   = 11;
/*static*/ const unsigned long View::LINE_SMOOTH    = 12;
/*static*/ const unsigned long View::POLYGON_SMOOTH = 13;
/*static*/ const unsigned long View::POINT_OFFSET   = 14;
/*static*/ const unsigned long View::LINE_OFFSET    = 15;
/*static*/ const unsigned long View::POLYGON_OFFSET = 16;
/*static*/ const unsigned long View::LIGHTING       = 19;
/*static*/ const unsigned long View::LIGHT0         = 20;
/*static*/ const unsigned long View::LIGHT1         = 21;
/*static*/ const unsigned long View::LIGHT2         = 22;
/*static*/ const unsigned long View::LIGHT3         = 23;
/*static*/ const unsigned long View::LIGHT4         = 24;
/*static*/ const unsigned long View::LIGHT5         = 25;
/*static*/ const unsigned long View::LIGHT6         = 26;
/*static*/ const unsigned long View::LIGHT7         = 27;
/*static*/ const unsigned long View::COLOR_MATERIAL = 28;
							   						
							   
/*static*/ unsigned int View::feature_to_code[256];


//!  Initialize graphics device feature mapping
/*static*/ void View::init(){
	dmsg( M_INIT,  "init_graphics_device..." );
	feature_to_code[CULL_FACE     ] = GL_CULL_FACE     ;
	feature_to_code[BLEND         ] = GL_BLEND         ;
	feature_to_code[FOG           ] = GL_FOG           ;
	feature_to_code[NORMALIZE     ] = GL_NORMALIZE     ;
	feature_to_code[ALPHA_TEST    ] = GL_ALPHA_TEST    ;
	feature_to_code[DEPTH_TEST    ] = GL_DEPTH_TEST    ;
	feature_to_code[STENCIL_TEST  ] = GL_STENCIL_TEST  ;
	feature_to_code[SCISSOR_TEST  ] = GL_SCISSOR_TEST  ;
	feature_to_code[TEXTURE_1D    ] = GL_TEXTURE_1D    ;
	feature_to_code[TEXTURE_2D    ] = GL_TEXTURE_2D    ;
	feature_to_code[POINT_SMOOTH  ] = GL_POINT_SMOOTH  ;
	feature_to_code[LINE_SMOOTH   ] = GL_LINE_SMOOTH   ;
	feature_to_code[POLYGON_SMOOTH] = GL_POLYGON_SMOOTH;
	feature_to_code[POINT_OFFSET  ] = GL_POLYGON_OFFSET_POINT;
	feature_to_code[LINE_OFFSET   ] = GL_POLYGON_OFFSET_LINE;
	feature_to_code[POLYGON_OFFSET] = GL_POLYGON_OFFSET_FILL;
	feature_to_code[LIGHTING      ] = GL_LIGHTING      ;
	feature_to_code[LIGHT0        ] = GL_LIGHT0        ;
	feature_to_code[LIGHT1        ] = GL_LIGHT1        ;
	feature_to_code[LIGHT2        ] = GL_LIGHT2        ;
	feature_to_code[LIGHT3        ] = GL_LIGHT3        ;
	feature_to_code[LIGHT4        ] = GL_LIGHT4        ;
	feature_to_code[LIGHT5        ] = GL_LIGHT5        ;
	feature_to_code[LIGHT6        ] = GL_LIGHT6        ;
	feature_to_code[LIGHT7        ] = GL_LIGHT7        ;
	feature_to_code[COLOR_MATERIAL] = GL_COLOR_MATERIAL;
}

//#define getCode(a) feature_to_code[a]
/*static*/ unsigned int View::getCode( unsigned int a ){
	return feature_to_code[a];
}


//!  Return description for graphics feature
/*static*/ const char *View::feature_to_str( int a ){
	switch( a ){
	case CULL_FACE     : return "CULL_FACE     ";
	case BLEND         : return "BLEND         ";
	case FOG           : return "FOG           ";
	case NORMALIZE     : return "NORMALIZE     ";
	case ALPHA_TEST    : return "ALPHA_TEST    ";
	case DEPTH_TEST    : return "DEPTH_TEST    ";
	case STENCIL_TEST  : return "STENCIL_TEST  ";
	case SCISSOR_TEST  : return "SCISSOR_TEST  ";
	case TEXTURE_1D    : return "TEXTURE_1D    ";
	case TEXTURE_2D    : return "TEXTURE_2D    ";
	case POINT_SMOOTH  : return "POINT_SMOOTH  ";
	case LINE_SMOOTH   : return "LINE_SMOOTH   ";
	case POLYGON_SMOOTH: return "POLYGON_SMOOTH";
	case POINT_OFFSET  : return "POINT_OFFSET  ";
	case LINE_OFFSET   : return "LINE_OFFSET   ";
	case POLYGON_OFFSET: return "POLYGON_OFFSET";
	case LIGHTING      : return "LIGHTING      ";
	case LIGHT0        : return "LIGHT0        ";
	case LIGHT1        : return "LIGHT1        ";
	case LIGHT2        : return "LIGHT2        ";
	case LIGHT3        : return "LIGHT3        ";
	case LIGHT4        : return "LIGHT4        ";
	case LIGHT5        : return "LIGHT5        ";
	case LIGHT6        : return "LIGHT6        ";
	case LIGHT7        : return "LIGHT7        ";
	case COLOR_MATERIAL: return "COLOR_MATERIAL";
	default:
		return "unknown";
		break;
	}
}


};  //  namespace Graphics
};  //  namespace Teddy

