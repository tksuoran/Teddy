
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


#include "Teddy/PhysicalComponents/Dock.h"
#include "Teddy/PhysicalComponents/Style.h"
#include "Teddy/SysSupport/Messages.h"
using namespace Teddy::SysSupport;


#if defined( _MSC_VER )
# include <limits>
#else
extern "C" {
#include <limits.h>
}
#endif


namespace Teddy              {
namespace PhysicalComponents {


//!  Constructor
Dock::Dock( std::string name, const int axis )
:
Area    (  name  )/*,
axis_sum(  axis  ),
axis_max( 1-axis )*/
{
	axis_sum = axis;
	axis_max = 1 - axis;
	event_ordering = separate_self;
    dmsg( M_WML, "  %s->axis_sum = %d, axis_max = %d", this->getName().c_str(), axis_sum, axis_max );
}


/*virtual*/ Dock::~Dock(){
}


/*virtual*/ void Dock::beginSize( const Vector2 &ref ){
    dmsg( M_WML, "%s->Dock::beginSize( %f x %f )", this->getName().c_str(), ref[0], ref[1] );
    dmsg( M_WML, "  %s->axis_sum = %d, axis_max = %d", this->getName().c_str(), axis_sum, axis_max );
    size = style->padding;
}


/*virtual*/ void Dock::callSize( Area *a ){
    dmsg( M_WML, "%s->Dock::callSize( %s ) = %...", this->getName().c_str(), a->getName().c_str() );
    Vector2 sub_size  = a->doSize( size );
    dmsg( M_WML, "  %s->Dock::callSize( %s ) = %f x %f", this->getName().c_str(), a->getName().c_str(), sub_size[0], sub_size[1] );
    size[axis_sum]   += sub_size[axis_sum] + style->padding[axis_sum];
    size[axis_max]    = MAX( size[axis_max], sub_size[axis_max] );
    dmsg( M_WML, "  %s->size = %f x %f", this->getName().c_str(), a->getName().c_str(), size[0], size[1] );
}


/*virtual*/ void Dock::endSize(){
    size[axis_max] += 2 * style->padding[axis_max];
//    size[axis_sum] += style->padding[axis_sum];
    dmsg( M_WML, "%s->Dock::endSize( %f x %f )", this->getName().c_str(), size[0], size[1] );
}


/*virtual*/ void Dock::beginPlace( const Rect &ref ){
    dmsg( M_WML, "%s->Dock::beginPlace()", getName().c_str() );
    rect.min = ref.min  + offset_pixels + ref.getSize() * offset_free_size_relative + size * offset_self_size_relative;
    rect.max = rect.min + size;

    if( isEnabled(Area::USE_CLIP_TO_REFERENCE) ){
        rect.intersect( ref );
    }

    in_rect = rect.shrink( style->padding );

    cursor_start = rect.min + style->padding;
    cursor_end   = rect.max - style->padding;
}


/*virtual*/ void Dock::callPlace( Area *a ){
    dmsg( M_WML, "%s->Dock::callPlace( %s )", this->getName().c_str(), a->getName().c_str() );
    dmsg( M_WML, "  cursor_start = %f, %f", cursor_start[0], cursor_start[1] );
    Vector2 sub_size = a->doPlace( Rect(cursor_start,cursor_end) );
    cursor_start[axis_sum] += sub_size[axis_sum] + style->padding[axis_sum];
    dmsg( M_WML, "  cursor_start = %f, %f", cursor_start[0], cursor_start[1] );
}


};  //  namespace PhysicalComponents'
};  //  namespace Teddy

