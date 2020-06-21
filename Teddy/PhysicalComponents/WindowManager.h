
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


#ifndef TEDDY__PHYSICAL_COMPONENTS__WINDOW_MANAGER__H
#define TEDDY__PHYSICAL_COMPONENTS__WINDOW_MANAGER__H


#include "Teddy/TeddyConfig.h"  //  for HAVE_SDL_JOYSTICK
#include "Teddy/Maths/Vector2.h"
#include "Teddy/PhysicalComponents/EventListener.h"
#include "Teddy/SysSupport/StdList.h"
#include "Teddy/SysSupport/StdSDL.h"


//  Forward declarations
namespace Teddy {
	namespace Graphics { class View;    };
	namespace Graphics { class Texture; };
}
using namespace Teddy::Graphics;
using namespace Teddy::Maths;


namespace Teddy              {
namespace PhysicalComponents {


class Area;
class Layer;


/*!
	\brief Window Manager
	\bug   Fix mouse cursor position when focus returns to sdl application

	WindowManager encapsulates window management such as
	positioning and depth ordering of windows in customizable
	way.
*/
class WindowManager : public EventListener {
public:
	WindowManager( View *view );
	virtual ~WindowManager();

	void  inputLoop  ();  //  never returns
	void  mouseKey   ( const int button, const int state, const int x,  const int y );
	void  mouseMotion( const int x,      const int y,     const int dx, const int dy );
	void  insert     ( Layer *layer );
	void  setFocus   ( EventListener *focus );
	void  setHold    ( bool apply );
	bool  getHold    () const;
	void  showCursor ();
	void  hideCursor ();
	void  draw       ();
	void  update     ();
	View *getView    ();

protected:
	View          *view;         //!<  Graphics View
	EventListener *focus;        //!<  Currently active Focus Area
	Texture       *cursor;       //!<  Mouse cursor
	SDL_Joystick  *joystick;     //!<  SDL Joystick
	list<Layer*>   layers;       //!<  Drawable Areas
	list<Area*>    focus_stack;  //!<  Focus stack
	bool           show_cursor;  //!<  Show mouse cursor?
	bool           hold;         //!<  Hold cursor still
	int            mouse_b[4];   //!<  Current mouse button states
	IntVector2     hold_pos;     //!<  Cursor hold coordinates
	IntVector2     mouse_pos;    //!<  Cursor coordinates (mouse)
};


};  //  namespace PhysicalComponents
};  //  namespace Teddy


#endif  //  TEDDY__PHYSICAL_COMPONENTS__WINDOW_MANAGER_H

