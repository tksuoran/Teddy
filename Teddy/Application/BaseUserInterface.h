
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


#ifndef TEDDY__APPLICATION__BASE_USER_INTERFACE__H
#define TEDDY__APPLICATION__BASE_USER_INTERFACE__H


//  Forward declarations
namespace Teddy {
	namespace Graphics           { class View;          };
	namespace PhysicalComponents { class Console;       };
	namespace PhysicalComponents { class Layer;         };
	namespace PhysicalComponents { class Projection;    };
	namespace PhysicalComponents { class WindowManager; };
};


namespace Teddy       {
namespace Application {


class BaseRoot;


//!  BaseUserInterface
class BaseUserInterface {
public:
	BaseUserInterface( BaseRoot *root );

	virtual void   addComponents   () = 0;
	void           enterRunLoop    ();

	Teddy::PhysicalComponents::Layer         *getLayer        ();
	Teddy::PhysicalComponents::Projection    *getProjection   ();
	Teddy::Graphics          ::View          *getView         ();
	Teddy::PhysicalComponents::WindowManager *getWindowManager();
	void                                      setProjection   ( Teddy::PhysicalComponents::Projection *projection );

protected:
	Teddy::PhysicalComponents::Layer         *layer;           //!<  Area container
	Teddy::PhysicalComponents::Projection    *projection;      //!<  Currently active projection window
	Teddy::Graphics          ::View          *view;            //!<  Rendering context
	Teddy::PhysicalComponents::WindowManager *window_manager;  //!<  Window manager
};


};  //  namespace Application
};  //  namespace Teddy


#endif  //  TEDDY__APPLICATION__BASE_USER_INTERFACE__H

