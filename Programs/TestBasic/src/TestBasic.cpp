
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


#include "Teddy/SysSupport/StdSDL.h"
#include "Teddy/Application/BaseObjectManager.h"
#include "Teddy/Application/BaseRoot.h"
#include "Teddy/Application/BaseSimulationTimer.h"
#include "Teddy/Application/BaseUserInterface.h"
#include "Teddy/Graphics/View.h"
#include "Teddy/Materials/Material.h"
#include "Teddy/MixIn/Tick.h"
#include "Teddy/Models/Grid.h"
#include "Teddy/PhysicalComponents/Layer.h"
#include "Teddy/PhysicalComponents/Projection.h"
#include "Teddy/Scenes/Camera.h"
#include "Teddy/Scenes/Scene.h"
#include "Teddy/SysSupport/Messages.h"
using namespace Teddy::Application;
using namespace Teddy::Graphics;
using namespace Teddy::Materials;
using namespace Teddy::MixIn;
using namespace Teddy::Models;
using namespace Teddy::PhysicalComponents;
using namespace Teddy::Scenes;


//  Class prototypes
class Root : public BaseRoot {
public:
	virtual void start( int argc, char **argv );
};


class ObjectManager : public BaseObjectManager, public Tick {
public:
	ObjectManager();
    virtual ~ObjectManager(){}
	virtual void tick();
protected:
	Model *grid;
};


class UserInterface : public BaseUserInterface {
public:
	UserInterface( Root *root ):BaseUserInterface(root){}
    virtual ~UserInterface(){}

	virtual void addComponents();
};


//  Globals
static ObjectManager       *object_manager   = NULL;
static BaseSimulationTimer *simulation_timer = NULL;
static UserInterface       *user_interface   = NULL;


//!  ObjectManager constructor
ObjectManager::ObjectManager(){
	scene  = new Scene ( "Test Scene"         );
	camera = new Camera( "Test Camera", scene );
	grid   = new Grid  ( 10, 10, 100, 100     );
	Material *grid_mat = new Material( Material::GRAY_75, Material::RENDER_LIGHTING_COLOR );

	camera->setPosition( 0.0f, 0.0f, 400.0f );
	camera->setNearFar ( 1.0f, 3000.0f );
	grid            ->setMaterial( grid_mat );
	scene           ->add        ( grid     );
	simulation_timer->add        ( this     );

#if 0
	Matrix rot;
	float a = -2.2f; // -2.0f + 0.2 * sin( (float)SDL_GetTicks()/1000.0 );
    rot.rotateYMatrix( 0 );
    rot.rotateX      ( a );
    rot.rotateZ      ( 0 );
	grid->getAttitude() = rot;
	for( int r=0; r<4; r++ ){
		emsg( M_DEBUG, "% 5.4f % 5.4f % 5.4f % 5.4f", rot.m[r][0], rot.m[r][1], rot.m[r][2], rot.m[r][3] );
	}
	Quaternion q = rot;
	emsg( M_DEBUG, "% 5.4f % 5.4f % 5.4f % 5.4f", q.v[0], q.v[1], q.v[2], q.v[3] );
#endif
}


//!  Animate the scene
void ObjectManager::tick(){
#if 1
	float y = fabs( 100 * sin( (float)SDL_GetTicks()/1000.0 ) );
	camera->setPosition( Vector(0.0f,y,0.0f) );
#endif
}


//!  Create all user interface components
void UserInterface::addComponents(){
	Projection *projection = new Projection( "TestBasic", object_manager->getCamera() );

	setProjection       ( projection );
	layer->addProjection( projection );
	layer->place        ();

	//  Set some default values for the projection window
	projection->setClearColor           ( Color(0.0f,0.25f,0.5f,1.0f) );
	projection->getMaster()->setOptions ( Material::RENDER_OPTION_ALL_M    );
	projection->getMaster()->setMode    ( Material::RENDER_MODE_FILL       );
	projection->getMaster()->setLighting( Material::RENDER_LIGHTING_SIMPLE );
	view->setClear( false );
}


/*virtual*/ void Root::start( int argc, char **argv ){
	BaseRoot::start( argc, argv );
	user_interface   = new UserInterface      ( this );
	simulation_timer = new BaseSimulationTimer();
	object_manager   = new ObjectManager      ();
	
	user_interface  ->addComponents();  //  Create UserInterface
	simulation_timer->start        ();  //  Start simulation timer
	user_interface  ->enterRunLoop ();  //  Enter run loop
}


//  Program startup
TEDDY_MAIN

