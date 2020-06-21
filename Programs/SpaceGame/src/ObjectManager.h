
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

	$Id:  $
*/


#ifndef SPACE_GAME__OBJECT_MANAGER__H
#define SPACE_GAME__OBJECT_MANAGER__H


#include "Teddy/Application/BaseObjectManager.h"
#include "Teddy/Maths/Vector2.h"
#include "Teddy/MixIn/Tick.h"
#include "Teddy/SysSupport/StdList.h"

#include "Node.h"


//  Forward declarations
namespace Teddy {
	namespace Materials  { class Light;  };
	namespace Models     { class Model;  };
	namespace Scenes     { class Camera; };
	namespace Scenes     { class Scene;  };
	namespace SysSupport { class Clock;  };
};


class CollisionGroup;
class ModelCamera;
class PlayerController;
class Ship;
class ShipType;


//!  ObjectManager
class ObjectManager
:
public Node,
public Teddy::MixIn::Tick,
public Teddy::Application::BaseObjectManager
{
public:
	ObjectManager( Root *root );

	virtual void tick();

	void addObjects     ( Teddy::MixIn::Options ffe_options );
	void addLights      ( int num  =1, const bool animate=false );
	void addGrid        ( int xcount, int zcount, int xspace, int zspace );
	void addPrimitives  ();
	void loadLWO        ();
	void addFFE         ( Teddy::MixIn::Options ffe_options );
	void addROAM        ();
	void addRigidBodies ();
	void setActiveCamera( Teddy::Scenes::Camera *c );
	void rayCollision   ( Teddy::Models::Model  *model );
	void addDamage      ( Ship   *s );

	void modelRotate     ( const Teddy::Maths::TVector2<float> &delta );  // mouse move delta
	void modelScale      ( const Teddy::Maths::TVector2<float> &delta );  // mouse move delta
	void modelTranslateXZ( const Teddy::Maths::TVector2<float> &delta );  // mouse move delta
	void modelTranslateYZ( const Teddy::Maths::TVector2<float> &delta );  // mouse move delta
	void selectModel     ( const Teddy::Maths::TVector2<float> &pos   );

	Teddy::Scenes::Camera *getCamera          ();
	Teddy::Scenes::Scene  *getScene           ();
	PlayerController      *getPlayerController();
	ModelCamera           *getModelCamera     ();

protected:
	ModelCamera          *model_camera;       //!<  Player ship camera;
	Teddy::Models::Model *model;              //!<  Selected model from scene
	PlayerController     *player_controller;  //!<  Player ship
	list<Ship*>           damage_list;        //!<  List of ships to be damaged;
};


#endif  //  SPACE_GAME__OBJECT_MANAGER__H

