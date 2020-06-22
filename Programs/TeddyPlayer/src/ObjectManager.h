
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


#ifndef TEDDY_PLAYER__OBJECT_MANAGER__H
#define TEDDY_PLAYER__OBJECT_MANAGER__H


#include "Teddy/Application/BaseObjectManager.h"
#include "Teddy/PhysicalComponents/EventListener.h"
#include "Node.h"


//  Forward declarations
namespace Teddy {
	namespace Imports   { class LWSceneParser; };
	namespace Materials { class Material;      };
	namespace Models    { class Model;         };
};
using namespace Teddy::Application;
using namespace Teddy::Imports;
using namespace Teddy::Materials;
using namespace Teddy::Models;


//!  ObjectManager
class ObjectManager 
: 
public Node,
public BaseObjectManager
{
public:
	ObjectManager( Root *root );
    virtual ~ObjectManager()
    {        
    }

	virtual void   addObjects      ();
	LWSceneParser *getLWSceneParser();
    bool           loadScene       ( void *ptr );
	bool           scanLwo         ();
    void           adjustToScene   ();

protected:
	LWSceneParser *scene_parser;
	Model         *floor;
	Material      *floor_mat;
};


#endif  //  TEDDY_PLAYER__OBJECT_MANAGER__H

