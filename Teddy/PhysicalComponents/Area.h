
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

	$Id: Area.h,v 1.6 2002/03/12 10:46:07 tksuoran Exp $
*/


#ifndef TEDDY__PHYSICAL_COMPONENTS__AREA__H
#define TEDDY__PHYSICAL_COMPONENTS__AREA__H


#include "Teddy/Graphics/ViewClient.h"
#include "Teddy/Maths/Vector.h"
#include "Teddy/Maths/Rect.h"
#include "Teddy/MixIn/Named.h"
#include "Teddy/MixIn/Options.h"
#include "Teddy/SysSupport/StdList.h"
#include "Teddy/SysSupport/Types.h"


//  Forward declarations
namespace Teddy {
	namespace Graphics           { class Font;          };
	namespace PhysicalComponents { class WindowManager; };
}
using namespace Teddy::Maths;
using namespace Teddy::Graphics;
using namespace Teddy::MixIn;


namespace Teddy              {
namespace PhysicalComponents {


class EventListener;
class Projection;
class Style;

/*!
	\brief   Base class for physical userinterface components

	Area is the basic base class for all Physical Components.

	Area provides a drawing context. Drawing is not
	currently clipped.

	Area can contain subareas, thus areas can be hierarchial.
	When Area is drawn, all subareas are also drawn.

	Area knows how to determine size and position for
	itself. This is called layout. The layout is
	determined through LayoutConstraints when place
	method is called.

	setPos() and setSize() methods are protected low level
	methods; to actually set position or size of area you
	must use LayoutConstraint of that Area. At the moment
	it is public member, but that will change later.

	Notice that you should use drawSelf() method for drawing
	in subclasses and leave draw() method as it is. The draw()
	method will take care of rendering children as well.

	Area can also be interactive such that they can be operated
	with input device. Area is not interactive by default.
	To make Area interactive, it must be registered (as potential
	focus area) to WindowManager. See WindowManager for details on this.

	Visual Area properties link font, color and size should be
	stored in Style.
*/
class Area :
public Named,
public Options,
public ViewClient
{
public:
	static const unsigned long CLIP_LAYOUT   ;
	static const unsigned long CLIP_RENDERING;
	static const unsigned long CLEAR         ;
	static const unsigned long PICK          ;
	static const unsigned long USE_OFFSET_SELF_SIZE_RELATIVE;
	static const unsigned long USE_OFFSET_FREE_SIZE_RELATIVE;
	static const unsigned long USE_FILL_MAX_PIXELS          ;
	static const unsigned long USE_FILL_FREE_SIZE_RELATIVE  ;
	static const unsigned long USE_CLIP_TO_REFERENCE        ;

public:
    Area();
    Area( std::string &name ); //  cant be const for Area( "blah" ) to work
    Area( const std::string &name ); //  cant be const for Area( "blah" ) to work
	virtual ~Area();

	enum e_ordering {
		pre_self,      //!<  Draw self first, before children
		post_self,     //!<  Draw self last, after children
		separate_self  //!<  Separate drawSelf() invovation
    };

    //  Area
	virtual Area  *getHit       ( const Vector2 &pos );
    virtual void   insert       ( Area *area );
    virtual bool   remove       ( Area *area );
	virtual void   setParent    ( Area *parent, View *view = NULL );
	Area          *getParent    ();
	View          *getView      () const;  //!<  Return View of Area
    const Rect    &getRect      () const;
    const Vector2 &getSize      () const;
//	int           *getViewport  ();
// 	virtual void   moveDelta    ( const Vector2 &delta );
//  virtual void   sizeDelta    ( const Vector2 &delta );
    static void    setDefaultWindowManager( WindowManager *wm );

	//	AreaDraw
	virtual void  draw         ();
	virtual void  drawSelf     ();  //!<  Will render only self
    virtual void  drawString   ( const Vector2 &pos, const char *str, Font *font );
	virtual void  drawRect     ( const float x1, const float y1, const float x2, const float y2 );
	virtual void  drawFillRect ( const float x1, const float y1, const float x2, const float y2 );
	virtual void  drawBiColRect( const float x1, const float y1, const float x2, const float y2, const Color &top_left, const Color &bottom_right );
	virtual void  drawVertex   ( const float x1, const float y1 );

    //  AreaLayout
    virtual const Vector2 &doSize    ( const Vector2 &ref );
	virtual void           beginSize ( const Vector2 &ref );
    virtual void           callSize  ( Area *a );
	virtual void           endSize   ();
    virtual const Vector2 &doPlace   ( const Rect &ref );
	virtual void           beginPlace( const Rect &ref );
    virtual void           callPlace ( Area *a );
    virtual void           endPlace  ();

public:
    Vector2        offset_pixels;              //!<  offset in pixels
    Vector2        offset_self_size_relative;  //!<  offset relative to self size
    Vector2        offset_free_size_relative;  //!<  offset relative to remaining free size
	Vector2        fill_base_pixels;           //!<
    Vector2        fill_free_size_relative;    //!<

protected:
	WindowManager *window_manager;             //!<  Window manager
	Style         *style;                      //!<  Style spesification object
	Area          *parent;                     //!<  Parent Area hosting this Area
	list<Area*>    areas;                      //!<  Child Areas
    e_ordering     drawing_ordering;           //!<  Draw before or after children?
	e_ordering     event_ordering;             //!<  Consume event before or after children?


    Vector2        size;                       //!<
    Rect           rect;                       //!<
    Rect           in_rect;

    static WindowManager *default_window_manager;
};


};  //  namespace PhysicalComponents
};  //  namespace Teddy


#endif  //  TEDDY__PHYSICAL_COMPONENTS__AREA__H

