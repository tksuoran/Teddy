
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

	$Id: Area.cpp,v 1.5 2002/03/12 10:46:07 tksuoran Exp $
*/


#include "Teddy/PhysicalComponents/Area.h"
#include "Teddy/PhysicalComponents/ActionButton.h"
#include "Teddy/PhysicalComponents/EventListener.h"
#include "Teddy/PhysicalComponents/Projection.h"
#include "Teddy/PhysicalComponents/Style.h"
#include "Teddy/Graphics/View.h"
#include "Teddy/Graphics/Font.h"
#include "Teddy/SysSupport/Messages.h"
#include "Teddy/SysSupport/StdIO.h"
#ifndef SWIG
#include <cassert>
#endif
using namespace Teddy::Graphics;
using namespace Teddy::SysSupport;


namespace Teddy              {
namespace PhysicalComponents {


/*static*/ const unsigned long Area::CLIP_LAYOUT     = (1L<<0L);  //!<  Area::  
/*static*/ const unsigned long Area::CLIP_RENDERING  = (1L<<1L);  //!<  Area::  
/*static*/ const unsigned long Area::CLEAR           = (1L<<2L);  //!<  Projecti
/*static*/ const unsigned long Area::PICK            = (1L<<3L);  //!<  Projecti

/*static*/ const unsigned long Area::USE_OFFSET_SELF_SIZE_RELATIVE = (1L<<8L)  ;
/*static*/ const unsigned long Area::USE_OFFSET_FREE_SIZE_RELATIVE = (1L<<9L)  ;
/*static*/ const unsigned long Area::USE_FILL_MAX_PIXELS           = (1L<<10L) ;
/*static*/ const unsigned long Area::USE_FILL_FREE_SIZE_RELATIVE   = (1L<<11L) ;
/*static*/ const unsigned long Area::USE_CLIP_TO_REFERENCE         = (1L<<12L) ;


WindowManager *Area::default_window_manager = NULL;


/*static*/ void Area::setDefaultWindowManager( WindowManager *wm ){
	Area::default_window_manager = wm;
}


//!  Constructor
Area::Area( std::string &name )
:
Named     (name),
Options   (  0 ),
ViewClient(NULL)
{
	style            = Style::default_style;
	parent           = NULL;
	drawing_ordering = pre_self;
	event_ordering   = post_self;
	window_manager   = default_window_manager;
    offset_pixels             = Vector2( 0, 0 );  //!<  offset in pixels
    offset_self_size_relative = Vector2( 0, 0 );  //!<  offset relative to self size
    offset_free_size_relative = Vector2( 0, 0 );  //!<  offset relative to remaining free size
	fill_base_pixels          = Vector2( 0, 0 );  //!<
    fill_free_size_relative   = Vector2( 0, 0 );  //!<
}


Area::Area( const std::string &name )
:
Named     (name),
Options   (  0 ),
ViewClient(NULL)
{
	style          = Style::default_style;
	parent         = NULL;
	drawing_ordering = pre_self;
	event_ordering   = post_self;
	window_manager = default_window_manager;
    offset_pixels             = Vector2( 0, 0 );  //!<  offset in pixels
    offset_self_size_relative = Vector2( 0, 0 );  //!<  offset relative to self size
    offset_free_size_relative = Vector2( 0, 0 );  //!<  offset relative to remaining free size
	fill_base_pixels          = Vector2( 0, 0 );  //!<
    fill_free_size_relative   = Vector2( 0, 0 );  //!<
}


Area::Area()
:
Named     (),
Options   (  0 ),
ViewClient(NULL)
{
	style          = Style::default_style;
	parent         = NULL;
	drawing_ordering = pre_self;
	event_ordering   = post_self;
	window_manager = default_window_manager;
    offset_pixels             = Vector2( 0, 0 );  //!<  offset in pixels
    offset_self_size_relative = Vector2( 0, 0 );  //!<  offset relative to self size
    offset_free_size_relative = Vector2( 0, 0 );  //!<  offset relative to remaining free size
	fill_base_pixels          = Vector2( 0, 0 );  //!<
    fill_free_size_relative   = Vector2( 0, 0 );  //!<
}


//!  Destructor
/*virtual*/ Area::~Area(){
}


//!  Area Input Interface - Get Hit Area, NULL if none
/*virtual*/ Area *Area::getHit( const Vector2 &pos ){
    const char *name = getName().c_str();

    if( areas.empty() ){
        dmsg( M_WME, "Trying Area %s (no children)", name );
    }else{
        dmsg( M_WME, "Trying Area %s", name );
    }

	//	If we are last to draw, we could be hit?
    if( event_ordering == pre_self ){
        if( rect.hit(pos) ){
			dmsg( M_WME, "Hit Area Pre" );
			return this;
		}
	}

    //if( !areas.empty() ){
        dmsg( M_WME, "Begin area children of %s", name );
        list<Area*>::iterator a_it = areas.begin();
        while( a_it != areas.end() ){
            Area *hit = (*a_it)->getHit( pos );
            if( hit != NULL ){
                return hit;
            }
            a_it++;
        }
        dmsg( M_WME, "End Area Children of %s", name );
    //}

	//	If we are last to draw, we could be hit?
	if( event_ordering == post_self ){
		if( rect.hit(pos) ){
			dmsg( M_WME, "Hit Area Post" );
			return this;
		}
	}

	//  No hit found
	return NULL;
}


//!  Set parent Area
/*virtual*/ void Area::setParent( Area *parent, View *view ){
	this->parent = parent;
	setView( view );

	//	Place flat areas
	list<Area*>::iterator a_it = areas.begin();
	while( a_it != areas.end() ){
		if( (*a_it)->getParent() != NULL ){
			(*a_it)->setParent( this, view );
		}
		a_it++;
	}
}


//!  Parent accessor
Area *Area::getParent(){
	return this->parent;
}


const Rect &Area::getRect() const {
    return rect;
};


const Vector2 &Area::getSize() const {
    return size;
}


//!  Area Layout interface - Insert Area to Layer
/*virtual*/ void Area::insert( Area *area ){
    if( area == NULL ){
        dmsg( M_WM, "Area::insert() Area *area == NULL");
        return;
    }
    areas.push_back( area );
	area->setParent( this, this->view );
}


//!  Remove child from Area
/*virtual*/ bool Area::remove( Area *child ){
	list<Area*>::iterator a_it = areas.begin();
	while( a_it != areas.end() ){
		if( *a_it == child ){
			this->areas.remove( child );
            dmsg( M_WM, "Area::remove succeeded\n" );
			return true;
		}
		a_it++;
    }
    dmsg( M_WM, "Area::remove FAILED\n" );
    return false;
}


};  //  namespace PhysicalComponents
};  //  namespace Teddy

