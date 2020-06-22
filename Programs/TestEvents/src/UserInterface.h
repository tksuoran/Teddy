
/*
	TEDDY - General graphics application library
	Copyright (C) 1999, 2000, 2001	Timo Suoranta
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

	$Id: UserInterface.h,v 1.4 2002/02/16 12:47:30 tksuoran Exp $
*/


#ifndef TEST_EVENTS__USER_INTERFACE__H
#define TEST_EVENTS__USER_INTERFACE__H


#include "Teddy/TeddyConfig.h"
#include "Teddy/Application/BaseUserInterface.h"
#include "Teddy/PhysicalComponents/Area.h"
#include "Teddy/Scenes/Camera.h"

#include "Node.h"
#include "Display.h"
namespace Teddy {
    namespace PhysicalComponents {
        class Popup;
    };
};


using namespace Teddy::Scenes;
using namespace Teddy::Application;


//!  Inherit from default UserInterface class
class UserInterface 
: 
public Node,
public BaseUserInterface
{
public:
	UserInterface( Root *root );

    virtual void  addComponents();
	void          setDisplay( Display *display );
	Display      *getDisplay();

    //  libsigc++ callback methods
    bool sceneLoad         ();
    bool sceneSave         ();
    bool sceneEmpty        ();
    bool sceneQuit         ();
    bool displayPoint      ();
    bool displayLine       ();
    bool displayFill       ();
    bool displayFillOutline();
    bool displayTextures   ();
    bool displayNoTextures ();
    bool lightsColor       ();
    bool lightsSimple      ();
    bool lightsFull        ();
    bool animationRun      ();
    bool animationStop     ();
    bool createBox         ();
    bool createCapsule     ();
    bool createCone        ();
    bool createCylinder    ();
    bool createSphere      ();
    bool createTorus       ();
    bool modifyParameters  ();
    bool modifyMove        ();
    bool modifyRotate      ();
    bool modifyScale       ();
    bool modifyTransform   ();
    bool modifyClone       ();
    bool modifyRemove      ();

protected:
    Camera   *camera;
	Display  *display;
	Teddy::PhysicalComponents::Area *message;
    Teddy::PhysicalComponents::Area *menu;
};


#endif  //  TEST_EVENTS__USER_INTERFACE__H

