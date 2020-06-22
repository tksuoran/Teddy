
/*
	TEDDY - General graphics application library
	Copyright (C) 1999, 2000, 2001	Timo Suoranta
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


#ifndef SPACEGAME__NODE__H
#define SPACEGAME__NODE__H


#include "Root.h"


class Node {
public:
	Node( Root *root );

	inline ActionManager       *getActionManager  (){ return root->getActionManager  (); }
	inline BaseAudioManager    *getAudioManager   (){ return root->getAudioManager   (); }
	inline ObjectManager       *getObjectManager  (){ return root->getObjectManager  (); }
	inline BaseSimulationTimer *getSimulationTimer(){ return root->getSimulationTimer(); }
	inline UserInterface       *getUserInterface  (){ return root->getUserInterface  (); }

protected:
	Root *root;
};


#endif  //  SPACEGAME__NODE__H

