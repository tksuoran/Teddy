
/*
	TSGL - Teddy Space Game Library
	Copyright (C) 2002 Timo Suoranta
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


#include "Teddy/TeddyConfig.h"
#include "Teddy/Application/BaseSimulationTimer.h"
#include "Teddy/Behaviour/ModelController.h"
#include "Teddy/Graphics/View.h"
#include "Teddy/Imports/LWModel.h"
#include "Teddy/Materials/Material.h"
#include "Teddy/Materials/Light.h"
#include "Teddy/Maths/Vector.h"
#include "Teddy/Maths/Vector4.h"
#include "Teddy/Models/Line.h"
#include "Teddy/Models/Vertex.h"
#include "Teddy/Models/Grid.h"
#include "Teddy/PhysicalComponents/ConsoleStream.h"
#include "Teddy/PhysicalComponents/Projection.h"
#include "Teddy/Scenes/Camera.h"
#include "Teddy/Scenes/PostElement.h"
#include "Teddy/Scenes/Scene.h"
#include "Teddy/SysSupport/Messages.h"
#include "Teddy/SysSupport/StdIO.h"

#include "ComputerController.h"
#include "ObjectManager.h"
#include "PlayerController.h"
#include "ModelCamera.h"
#include "Ship.h"
#include "ShipType.h"
#include "UserInterface.h"
using namespace Teddy::Application;
using namespace Teddy::Behaviour;
using namespace Teddy::Graphics;
using namespace Teddy::Imports;
using namespace Teddy::Materials;
using namespace Teddy::PhysicalComponents;
using namespace Teddy::Scenes;
using namespace Teddy::Maths;


//!  ObjectManager constructor
ObjectManager::ObjectManager( Root *root )
:
Node             ( root ),
BaseObjectManager(      )
{
	model = NULL;
}


//!  Initialize objects == scene
void ObjectManager::addObjects( Options ffe_options ){
	scene = new Scene( "Test scene" );

	Model    *cobra_mesh      = new LWModel ( "Data/lwo/cobra_with_texture.lwo", 0 );
	ShipType *cobra_ship_type = new ShipType( "Cobra Mk III",  cobra_mesh );
	Ship     *player_ship     = new Ship    ( "Cobra Mk III",  cobra_ship_type, root );
	player_controller = new PlayerController( player_ship, root );

	player_ship->setPosition( Vector(0,100,200) );

	model_camera = new ModelCamera( player_ship, root );
	camera = model_camera;

	if( root->hasOpt("--ai") ){
		Model    *viper_mesh      = new LWModel ( "Data/lwo/VIPER.lwo",              0 );
		ShipType *viper_ship_type = new ShipType( "Viper",         viper_mesh );
		Ship     *wingman_s1      = new Ship    ( "Wingman 1",     viper_ship_type, root );
		Ship     *wingman_s2      = new Ship    ( "Wingman 2",     viper_ship_type, root );
		ComputerController *wingman_1 = new ComputerController( wingman_s1, root );
		ComputerController *wingman_2 = new ComputerController( wingman_s2, root );
		wingman_1->setTarget( player_ship, Vector(-400,0,-300) );
		wingman_2->setTarget( player_ship, Vector( 400,0,-300) );
		wingman_1->warpToPosition();
		wingman_2->warpToPosition();
	}


/*	Quaternion ca    = camera->getAttitude();
    Matrix     m     = ca;
	Vector     right = ca.getRightAxis();
	Vector     up    = ca.getUpAxis   ();
	Vector     view  = ca.getViewAxis ();
    Vector4    row0  = m.getRow( 0 );
    Vector4    row1  = m.getRow( 1 );
	Vector4    row2  = m.getRow( 2 );
	dprint( M_INIT, "Quaternion:\n" );
	dprint( M_INIT, "Right = % 9.4f, %9.4f, %9.4f\n", right[0], right[1], right[2] );
	dprint( M_INIT, "Up    = % 9.4f, %9.4f, %9.4f\n", up   [0], up   [1], up   [2] );
	dprint( M_INIT, "View  = % 9.4f, %9.4f, %9.4f\n", view [0], view [1], view [2] );
	dprint( M_INIT, "Matrix:\n" );
	dprint( M_INIT, "Row0  = % 9.4f, %9.4f, %9.4f\n", row0 [0], row0 [1], row0 [2] );
	dprint( M_INIT, "Row1  = % 9.4f, %9.4f, %9.4f\n", row1 [0], row1 [1], row1 [2] );
	dprint( M_INIT, "Row2  = % 9.4f, %9.4f, %9.4f\n", row2 [0], row2 [1], row2 [2] );
	{
		Quaternion ca    = m;
		Vector     right = ca.getRightAxis();
		Vector     up    = ca.getUpAxis   ();
		Vector     view  = ca.getViewAxis ();
		dprint( M_INIT, "Quaternion:\n" );
		dprint( M_INIT, "Right = % 9.4f, %9.4f, %9.4f\n", right[0], right[1], right[2] );
		dprint( M_INIT, "Up    = % 9.4f, %9.4f, %9.4f\n", up   [0], up   [1], up   [2] );
		dprint( M_INIT, "View  = % 9.4f, %9.4f, %9.4f\n", view [0], view [1], view [2] );
	}*/

	addGrid( 80, 80, 100, 100 );

	if( root->hasOpt("--lights") ) addLights( 4, false );
	if( root->hasOpt("--lwo"   ) ) loadLWO();
	if( root->hasOpt("--ffe"   ) ) addFFE( ffe_options );
//	if( root->hasOpt("--roam") ){
//	addROAM();
//	}
//	addRigidBodies();
}


/*!
	\brief Add preset light(s) to scene
	\todo  Fix this UGLY code....!!
*/
void ObjectManager::addLights( int num, const bool animate ){
#	define LX 20000
#	define LY 50000
#	define LZ 20000
	Light *light;

	light = new Light( "Player Light" );
	light->setAmbient ( Color(0.6f,0.6f,0.6f) );
	light->setDiffuse ( Color(0.6f,0.6f,0.6f) );
	light->setSpecular( Color(0.6f,0.6f,0.6f) );
	light->setPosition( 0, 0, 0 );
	light->setSpotCutOff( 25.0f );
	light->setSpotExponent( 32.0f );
	light->enable();
	scene->add( light );
//	ply_light = light;
	
	if( num>1 ){
		light = new Light( "Light 1" );
		light->setAmbient ( Color(0.4f,0.4f,0.4f) );
		light->setDiffuse ( Color(0.4f,0.4f,0.4f) );
		light->setSpecular( Color(0.4f,0.4f,0.4f) );
		light->setPosition( LX, LY, 0 );
		light->enable();
		scene->add( light );
		if( animate ){
//			light->tick_translation = Vector( 2.0, 0.0, 0.0 );
			light->orbit( 8000, 15000, 0 );
		}
	}

	if( num>2 ){
		light = new Light( "Light 2" );
		light->setAmbient ( Color(0.4f,0.4f,0.4f) );
		light->setDiffuse ( Color(0.4f,0.4f,0.4f) );
		light->setSpecular( Color(0.4f,0.4f,0.4f) );
		light->setPosition(  0, LY, LZ );
		light->enable();
		scene->add( light );
		if( animate ){
//			light->tick_translation = Vector( 0.0, -20.0, 0.0 );
			light->orbit( 6000, 30000, 1 );
		}
	}

	if( num>3 ){
		light = new Light( "Light 3" );
		light->setAmbient ( Color(0.4f,0.4f,0.4f) );
		light->setDiffuse ( Color(0.4f,0.4f,0.4f) );
		light->setSpecular( Color(0.4f,0.4f,0.4f) );
		light->setPosition( 0, -LY, 0 );
		light->enable();
		scene->add( light );
		if( animate ){
//			light->tick_translation = Vector( -2.0, -1.0, 10.0 );
			light->orbit( 7000, 50000, 2 );
		}
	}

	if( num>4 ){
		light = new Light( "Light 4" );
		light->setAmbient ( Color::GRAY_50 );
		light->setDiffuse ( Color::GRAY_50 );
		light->setSpecular( Color::GRAY_50 );
		light->setPosition( -LX, LY, LZ );
		light->enable();
		scene->add( light );
//		if( animate ){
//			light->tick_translation = Vector( 40.0, 20.0, 1.0 );
			light->orbit( 15000, 700, 3 );
//		}
	}

	if( num>5 ){
		light = new Light( "Light 5" );
		light->setAmbient ( Color(0,0,0.2f) );
		light->setDiffuse ( Color(0,0,0.2f) );
		light->setSpecular( Color(0,0,0.2f) );
		light->setPosition( LX, LY, 0 );
		light->enable();
		scene->add( light );
		light->orbit( 50000, 71, 5 );
	}
	if( num>6 ){
		light = new Light( "Light 6" );
		light->setAmbient ( Color::BLACK );
		light->setDiffuse ( Color::LIGHT_BLUE );
		light->setSpecular( Color::LIGHT_BLUE );
		light->setPosition( -LX, -LY, 0 );
		light->enable();
		scene->add( light );
		light->orbit( 25000, 300, 4 );
	}
}


//!  Add simple grid to scene
void ObjectManager::addGrid( int xcount, int zcount, int xspace, int zspace ){
	Grid     *grid = new Grid( xcount/2, zcount/2, xspace*2, zspace*2 );
	Material *mat  = new Material( Material::DARK_RED, Material::RENDER_LIGHTING_COLOR );

	mat->setDiffuse( Color(0.5f,0.40f,0.65f) );
	grid->setPosition( 0, 0.0f, 0 );
	grid->setMaterial( mat  );
	scene->add( grid );

}


//!  \todo doc
PlayerController *ObjectManager::getPlayerController(){
	return this->player_controller;
}


//!  \todo doc
ModelCamera *ObjectManager::getModelCamera(){
	return this->model_camera;
}


//!  translate model on XZ plane
void ObjectManager::modelTranslateXZ( const Vector2 &delta ){
	if( model==NULL ){
		return;
	}

//	model->translate( Vector( -x_delta, 0.0, -y_delta ) );
	Vector pos = model->getPosition();
	pos += Vector( delta[0]*0.1, 0.0, delta[1]*0.1 );
	model->setPosition( pos );
}


//!  translate model on YZ plane
void ObjectManager::modelTranslateYZ( const Vector2 &delta ){
	if( model==NULL ){
		return;
	}

//	model->translate( Vector( -x_delta, -y_delta, 0.0 ) );
	Vector pos = model->getPosition();
	pos += Vector( delta[0]*0.1, delta[1]*0.1, 0.0 );
	model->setPosition( pos );
}


//!  rotate model
void ObjectManager::modelRotate( const Vector2 &delta ){
	if( model==NULL ){
		return;
	}
	model->heading( delta[0]*4.0f );
	model->pitch  ( delta[1]*4.0f );
}


//!  scale model
void ObjectManager::modelScale( const Vector2 &delta ){
	if( model==NULL ){
		return;
	}
		
	double dist = 0.3*delta[1];
	if( dist<0 ){
		dist = 1/sqrt(1-(dist/10));
	}else{
		dist = sqrt(1+(dist/10));
	}
		
	model->roll (  rads( delta[0]*0.3)  );
	model->pitch(  rads( delta[1]*0.3)  );
}


//!  Mouse buttonpress event
void ObjectManager::selectModel( const Vector2 &pos ){
	static char             sel_line[80];
	Model                  *pick;
	list<Model*>::iterator  m_it;
	Ship                   *ship;

	pick = getUserInterface()->getProjection()->pick( pos );
	ship = dynamic_cast<Ship*>( pick );

	if( ship != NULL ){
		ModelAnimator   *old_animator   = player_controller->getAnimator();
		ModelController *old_controller = ship             ->getAnimator()->getController();
		Model           *old_model      = old_animator     ->getModel   ();
		Ship            *old_ship       = dynamic_cast<Ship*>( old_model );

/*		if( old_ship != ship ){
			old_ship->lock();
			ship    ->lock();

			if( old_controller != NULL ){
				delete old_controller;
			}
			if( old_ship != NULL ){
				old_ship->getAnimator()->setController( NULL );
			}

			player_controller->getAnimator()->setInstance( ship );
			player_camera    ->setShip( ship );

			ship    ->unlock();
			old_ship->unlock();
		}*/
	}

	/*
	if( pick != NULL ){
		model = pick;
		player_ship->setTarget( model );
	}*/
}


void ObjectManager::addDamage( Ship *s ){
	damage_list.push_back( s );
}


/*virtual*/ void ObjectManager::tick(){
	Model *player_model = player_controller->getAnimator()->getModel();
	Ship  *player_ship  = dynamic_cast<Ship*>( player_model );
	if( player_ship == NULL ){
		return;
	}

	damage_list.clear();

	list<Model*>::iterator i_it = scene->getModels().begin();
	while( i_it != scene->getModels().end() ){
		Model *other = *i_it;
		Ship  *ship  = dynamic_cast<Ship*>( other );

		//  Test collision with player
		if( other != player_ship ){
			other      ->lock();
			player_ship->lock();
#if 0
			if( player_ship->testCollision(other) == true ){
				player_ship->collide( other );
				if( ship != NULL ){
					addDamage( ship );
				}
			}
#endif
			player_ship->unlock();
			other      ->unlock();
		}

		i_it++;
	}

	//  Apply damage list
	scene->lock();
	list<Ship*>::iterator s_it = damage_list.begin();
	while( s_it != damage_list.end() ){
		Ship *ship = *s_it;
		ship->damage();
		s_it++;
	}
	scene->unlock();

}


void ObjectManager::rayCollision( Model *source ){
#if 0
	Vector  origin    = source->getPosition();
	Vector  direction = source->getAttitude().getViewAxis();

	list<Model*>::iterator i_it = scene->getModels().begin();
	while( i_it != scene->getModels().end() ){
		Model *mi   = *i_it;
		Ship  *ship = dynamic_cast<Ship*>( mi );

		//  Test collision with player
		if( mi != source ){
			if( mi->rayCollision(origin,direction) == true ){
				if( ship != NULL ){
					addDamage( ship );
				}
				//getAudioManager()->playHitEm();
			}
		}

		i_it++;
	}
#endif
}


//!  Get camera
Camera *ObjectManager::getCamera(){
	return camera;
}


//!  Get scene
Scene *ObjectManager::getScene(){
	return scene;
}


