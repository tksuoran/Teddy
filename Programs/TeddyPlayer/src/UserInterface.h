
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

	$Id: UserInterface.h,v 1.1 2002/02/16 12:48:45 tksuoran Exp $
*/


#ifndef TEDDY_PLAYER__USER_INTERFACE__H
#define TEDDY_PLAYER__USER_INTERFACE__H


#include "Teddy/Application/BaseUserInterface.h"
#include "Teddy/Models/Model.h"
#include "Teddy/PhysicalComponents/Dock.h"

#include "Node.h"
using namespace Teddy::Application;


class Display;


//!  Inherit from default UserInterface class
class UserInterface 
: 
public Node,
public BaseUserInterface {
public:
	UserInterface( Root *root );

	virtual void addComponents();
		
	Display *getDisplay    ();
	void     sceneMenu     ();
	void	 objectMenu    ();

	bool     menu_items  ();
	bool     menu_objects();
	bool     menu_lights ();
	bool     menu_camera ();
	bool     menu_scene  ();
	bool     menu_lscript();
	bool     menu_display();

	bool     play          ();
	bool     stop          ();
	bool     reset         ();
	void     objectMenuItem( Teddy::Models::Model *model, Teddy::PhysicalComponents::Area *parent );

protected:
	Display                         *display;
	Teddy::PhysicalComponents::Dock *menu;
};


#endif  //  TEDDY_PLAYER__USER_INTERFACE__H

