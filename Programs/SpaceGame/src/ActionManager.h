
/*
	TSGL - Teddy Space Game Library
	Copyright (C) 2002 Timo Suoranta
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


#ifndef SPACE_GAME__ACTION_MANAGER_H
#define SPACE_GAME__ACTION_MANAGER_H


#include "Node.h"


//!  ActionManager
class ActionManager : public Node {
public:
	ActionManager( Root *root );

	//  Actions
	void quit                 ();

	void scannerCycle         ();
	void renderModePoint      ();
	void renderModeLine       ();
	void renderModeFill       ();
	void renderModeFillOutline();
	void cullFaceEnable       ();
	void cullFaceDisable      ();
	void depthTestEnable      ();
	void depthTestDisable     ();
	void lightingOn           ();
	void lightingOff          ();
	void blendOn              ();
	void blendOff             ();
	void fovNormal            ();
	void fovWide              ();
	void antialiseOn          ();
	void antialiseOff         ();
};


#endif  //  SPACE_GAME__ACTION_MANAGER_H

