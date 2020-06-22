
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


#include "Teddy/PhysicalComponents/Area.h"
#include "Teddy/PhysicalComponents/Style.h"
#include "Teddy/Graphics/View.h"
#include "Teddy/SysSupport/Messages.h"
#include "Teddy/SysSupport/StdIO.h"
#ifndef SWIG
#include <cassert>
#endif
using namespace Teddy::Graphics;


namespace Teddy              {
namespace PhysicalComponents {


/*virtual*/ const Vector2 &Area::doSize( const Vector2 &ref ){
    dmsg( M_WML, "%s->Area::doSize( %f x %f )", this->getName().c_str(), ref[0], ref[1] );
    beginSize( ref );
    list<Area*>::iterator a_it = areas.begin();
    while( a_it != areas.end() ){
        callSize( *a_it );
        a_it++;
    }
    endSize();
    dmsg( M_WML, "  %s->size = %f x %f", this->getName().c_str(), size[0], size[1] );
    return size;
}


/*virtual*/ void Area::beginSize( const Vector2 &ref ){
    dmsg( M_WML, "%s->Area::beginSize( %f x %f )", this->getName().c_str(), ref[0], ref[1] );
    size  = fill_base_pixels + ref * fill_free_size_relative;
	size[0] = (float)ceil( (double)size[0] );
	size[1] = (float)ceil( (double)size[1] );
    //size -= style->padding * 2;
    dmsg( M_WML, "  %s->size = %f x %f", this->getName().c_str(), size[0], size[1] );
}


/*virtual*/ void Area::callSize( Area *a ){
    dmsg( M_WML, "%s->Area::callSize( %s )", this->getName().c_str(), a->getName().c_str() );
    a->doSize( size );
}


/*virtual*/ void Area::endSize(){
    dmsg( M_WML, "%s->Area::endSize() size = %f x %f", this->getName().c_str(), size[0], size[1] );
}


/*virtual*/ const Vector2 &Area::doPlace( const Rect &ref ){
    dmsg( M_WML, "%s->Area::doPlace( %f, %f .. %f, %f )", this->getName().c_str(), ref.min[0], ref.min[1], ref.max[0], ref.max[1] );
    dmsg( M_WML, "  %s->size = %f x %f", this->getName().c_str(), size[0], size[1] );
    beginPlace( ref );
    list<Area*>::iterator a_it = areas.begin();
    while( a_it != areas.end() ){
        callPlace( *a_it );
        a_it++;
    }
    endPlace();
    return size;
}


/*virtual*/ void Area::beginPlace( const Rect &ref ){
    dmsg( M_WML, "%s->Area::beginPlace( %f, %f .. %f, %f )", this->getName().c_str(), ref.min[0], ref.min[1], ref.max[0], ref.max[1] );
    dmsg( M_WML, "  %s->size = %f x %f", this->getName().c_str(), size[0], size[1] );
    rect.min = ref.min + offset_pixels + ref.getSize() * offset_free_size_relative + size * offset_self_size_relative;
	rect.min[0] = (float)ceil( (double)rect.min[0] );
	rect.min[1] = (float)ceil( (double)rect.min[1] );
	rect.max = rect.min + size;
    if( isEnabled(Area::USE_CLIP_TO_REFERENCE) ){
        rect.intersect( ref );
    }

    in_rect = rect.shrink( style->padding );

}


/*virtual*/ void Area::callPlace( Area *a ){
    dmsg( M_WML, "%s->Area::callPlace( %s )", this->getName().c_str(), a->getName().c_str() );
    a->doPlace( rect );
}


/*virtual*/ void Area::endPlace(){
}


};  //  namespace PhysicalComponents
};  //  namespace Teddy

