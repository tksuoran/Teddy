
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
*/


/*!
	\file
	\brief  Teddy example program for objects

	This is example program demonstrates some
	primitive object shapes and object methods.

	The program does the following things:

	<ul>
	<li>creates a single camera which looks at the scene
	<li>creates a timer which bounces the camera up and down	
	<li>creates one scene and puts following objects to it
		<ul>
		<li>two boxes
		<li>a big sphere
		<li>four smaller spheres
		<li>two cones with tubes on tips
		<li>two cylinders
		<li>a torus
	<li>the camera and smaller spheres are animated
	</ul>
*/


#include "Teddy/Application/BaseRoot.h"
#include "Teddy/Application/BaseSimulationTimer.h"
#include "Teddy/Graphics/View.h"
#include "Teddy/Materials/Material.h"
#include "Teddy/Materials/Light.h"
#include "Teddy/Models/Model.h"
#include "Teddy/Models/Box.h"
#include "Teddy/Models/Cone.h"
#include "Teddy/Models/Cylinder.h"
#include "Teddy/Models/Grid.h"
#include "Teddy/Models/Ring.h"
#include "Teddy/Models/Sphere.h"
#include "Teddy/Models/Torus.h"
#include "Teddy/Models/Capsule.h"
#include "Teddy/PhysicalComponents/Layer.h"
#include "Teddy/PhysicalComponents/Projection.h"
#include "Teddy/PhysicalComponents/WindowManager.h"
#include "Teddy/Scenes/Scene.h"
#include "Teddy/Scenes/Camera.h"
#include "Teddy/Teddy.h"
#include "Teddy/SysSupport/Messages.h"
#include "Teddy/SysSupport/Timer.h"
#include "Teddy/SysSupport/StdSDL.h"
using namespace Teddy::Application;
using namespace Teddy::Graphics;
using namespace Teddy::Materials;
using namespace Teddy::Models;
using namespace Teddy::PhysicalComponents;
using namespace Teddy::Scenes;
using namespace Teddy::SysSupport;


class Root
: 
public BaseRoot,
public Tick {
public:
	virtual void start( int argc, char **argv );

	virtual void tick ();
	
public:
	Camera *camera;
	Model  *grid_obj;
	Model  *box_obj1;
	Model  *box_obj2;
	Model  *cone_obj1;
	Model  *cone_obj2;
	Model  *cyl_obj1;
	Model  *cyl_obj2;
	Model  *sphere_obj1;
	Model  *sphere_obj2;
	Model  *sphere_obj3;
	Model  *sphere_obj4;
	Model  *sphere_obj5;
	Model  *torus_obj1;
	Model  *capsule_obj1;
	Model  *capsule_obj2;
};


TEDDY_MAIN


/*virtual*/ void Root::start( int argc, char **argv ){
	BaseRoot::start( argc, argv );
	//  View must be first opened before much else can be done
	View          *view       = new View( getScreenWidth(), getScreenHeight(), getScreenOptions() );

	//  WindowManager manages all input events and contains are render contexts
	WindowManager *wm         = new WindowManager( view );

	//  Layer contains a set of rendering contexts
	Layer         *layer      = new Layer     ( "Root Layer",  view   );

	//  Scene is container for ModelInstances
	Scene         *scene      = new Scene     ( "Test Scene"         );

	//  Camera which can display the scene
	this ->        camera     = new Camera    ( "Test Camera", scene );

#if 1
    view->setCull( 0 );
    camera->setMirrorX( false );
#else
    view->setCull( 1 );
    camera->setMirrorX( true );
#endif

	//  Finally, Projection is a rendering context which can display a camera
	Projection    *projection = new Projection( "Test Window", camera );

	//  Connect the projection to the layer and add the layer to window manager
	wm   ->insert          ( layer      );
	view ->setWindowManager( wm         );
	layer->addProjection   ( projection );
	layer->place           ();

	//  Set some default values for the projection window
	projection->setClearColor           ( Color(0.5f,0.5f,0.5f,1.0f) );
	projection->getMaster()->setOptions ( Material::RENDER_OPTION_ALL_M );
	projection->getMaster()->setMode    ( Material::RENDER_MODE_FILL );
	projection->getMaster()->setLighting( Material::RENDER_LIGHTING_SIMPLE );

	//  Set camera properties
	camera->setNearFar( 16.0, 2048.0 );
	camera->heading   ( rads(-45.0) );
	camera->pitch     ( rads(-20.0) );

	//  Create object shapes
	Grid     *grid_mesh     = new Grid    ( 20, 20, 100, 100 );
	Box      *box_mesh      = new Box     ( "Box shape",          200, 200, 100         );
	Cone     *cone_mesh     = new Cone    ( "Cone shape",         100, 0, 400,  20, 20  );
	Cylinder *cylinder_mesh = new Cylinder( "Cylinder shape",     100, 200,     20      );
	Ring     *ring_mesh     = new Ring    ( "Ring shape",         110, 150,     30      );
	Sphere   *sphere_mesh1  = new Sphere  ( "Small Sphere shape",  50, 15,      15      );
	Sphere   *sphere_mesh2  = new Sphere  ( "Big Sphere shape",   150, 20,      20      );
	Torus    *torus_mesh    = new Torus   ( "Torus shape",        150, 40,      28, 18  );
	Capsule  *capsule_mesh  = new Capsule ( "Capsule shape",       40, 10,      14, 14  );

	Matrix m_syz;  //  matrix to swap y and z
	m_syz.setRow( 0, Vector4(1,0,0,0) ); // nx = 1*x + 0*y + 0*z + 0
	m_syz.setRow( 1, Vector4(0,0,1,0) ); // ny = 0*x + 0*y + 1*z + 0
	m_syz.setRow( 2, Vector4(0,1,0,0) ); // nz = 0*x + 1*y + 0*z + 0
	m_syz.setRow( 3, Vector4(0,0,0,1) );
	cone_mesh    ->transformVertices( m_syz );
	cylinder_mesh->transformVertices( m_syz );
	torus_mesh   ->transformVertices( m_syz );

	//  Create object instances
	grid_obj     = new Model( "Grid",         grid_mesh     );
	box_obj1     = new Model( "Box one",      box_mesh      );
	box_obj2     = new Model( "Box two",      box_mesh      );
	cone_obj1    = new Model( "Cone one",     cone_mesh     );
	cone_obj2    = new Model( "Cone two",     cone_mesh     );
	cyl_obj1     = new Model( "Cylinder one", cylinder_mesh );
	cyl_obj2     = new Model( "Cylinder two", cylinder_mesh );
	sphere_obj1  = new Model( "Sphere 1",     sphere_mesh1  );
	sphere_obj2  = new Model( "Sphere 2",     sphere_mesh1  );
	sphere_obj3  = new Model( "Sphere 3",     sphere_mesh1  );
	sphere_obj4  = new Model( "Sphere 4",     sphere_mesh1  );
	sphere_obj5  = new Model( "Big Sphere",   sphere_mesh2  );
	torus_obj1   = new Model( "Torus",        torus_mesh    );
	capsule_obj1 = new Model( "Capsule One",  capsule_mesh  );
	capsule_obj2 = new Model( "Capsule Two",  capsule_mesh  );

	//  Set objects' materials
	grid_obj    ->setMaterial( new Material(Material::GRAY_75,Material::RENDER_LIGHTING_COLOR)  );
	box_obj1    ->setMaterial( &Material::BLUE          );
	box_obj2    ->setMaterial( &Material::LIGHT_BLUE    );
	cone_obj1   ->setMaterial( &Material::RED           );
	cone_obj2   ->setMaterial( &Material::GREEN         );
	cyl_obj1    ->setMaterial( &Material::ORANGE        );
	cyl_obj2    ->setMaterial( &Material::LIGHT_ORANGE  );
	sphere_obj1 ->setMaterial( &Material::LIGHT_YELLOW  );
	sphere_obj2 ->setMaterial( &Material::LIGHT_CYAN    );
	sphere_obj3 ->setMaterial( &Material::LIGHT_GREEN   );
	sphere_obj4 ->setMaterial( &Material::LIGHT_BLUE    );
	sphere_obj5 ->setMaterial( &Material::DARK_BLUE     );
	torus_obj1  ->setMaterial( &Material::BLACK         );
	capsule_obj1->setMaterial( &Material::WHITE         );
	capsule_obj2->setMaterial( &Material::WHITE         );

	//  Set objects' positions
	grid_obj    ->setPosition(    0,   0,    0 );
	box_obj1    ->setPosition( -400, 200, -500 );
	box_obj2    ->setPosition(  400, 200, -500 );
	cone_obj1   ->setPosition( -400,   0,    0 );
	cone_obj2   ->setPosition(  400,   0,    0 );
	cyl_obj1    ->setPosition(  200,   0,  400 );
	cyl_obj2    ->setPosition(    0,   0, -400 );
	sphere_obj5 ->setPosition(    0, 150,    0 );  //  radius 150
	torus_obj1  ->setPosition(    0,  40,    0 );
	capsule_obj1->setPosition( -400, 400,    0 );
	capsule_obj2->setPosition(  400, 400,    0 );

	//  Add objects to the scene
	scene->add( grid_obj     );
	scene->add( box_obj1     );
	scene->add( box_obj2     );
	scene->add( cone_obj1    );
	scene->add( cone_obj2    );
	scene->add( cyl_obj1     );
	scene->add( cyl_obj2     );
	scene->add( sphere_obj1  );
	scene->add( sphere_obj2  );
	scene->add( sphere_obj3  );
	scene->add( sphere_obj4  );
	scene->add( sphere_obj5  );
	scene->add( torus_obj1   );
	scene->add( capsule_obj1 );
	scene->add( capsule_obj2 );

	//  Create lightsource and add it to the scene
	Light *light = new Light( "Lightsource" );
	scene->setAmbientColor( Color::BLACK );
	light->setAmbient ( Color::GRAY_25 );
	light->setDiffuse ( Color::WHITE );
	light->setSpecular( Color::WHITE );
	light->setPosition( -3000, 2000, 2000 );
	//light->setType( Light::TYPE_DIRECTIONAL );
	light->setType( Light::TYPE_POSITIONAL );
	//light->setAttenuation( 0.0f, 0.0f, 0.0f );
	light->enable();
	scene->add( light );

	//  To enable animation, we create a simulation timer
	BaseSimulationTimer *simulation_timer = new BaseSimulationTimer();

	//  Register this instance to the simulation timer
	//  That will make our tick() method being called 100 timer per second
	//  when the timer is running
	simulation_timer->add( this );

	//  Start the simulation timer
	simulation_timer->start();

	//  Enter Teddy loop.
	wm->inputLoop();
	//  Since we have no event handlers, we can only
	//  do things in the simulation timer after this.
}


/*!
	This is the timer update function implementation.
	Variables frame_age, sys_time and sync are provided by Teddy.
*/
/*virtual*/ void Root::tick(){
	float clock_time = SDL_GetTicks();
	float k1         = clock_time * (1.0f/2000.0f);
	float k2         = clock_time * (1.0f/ 333.0f);
	float k3         = clock_time * (1.0f/ 270.0f);
	float k4         = clock_time * (1.0f/ 350.0f);
	float x;
	float y;
	float z;

	//  Calculate new positions for camera and spheres
	y = 450 + 150 * sin( k2 );
	camera->setPosition( Vector(-400.0f,y,400.0f) );

	y = 50 + fabs(  200 * sin( k3 )  );
	x = 220 * cos( k2 );
	z = 200 * sin( k2 );
	sphere_obj1->setPosition( x, y, z );

	x = 220 * cos( M_2_PI / 3 + k2 );
	z = 200 * sin( M_2_PI / 3 + k2 );
	sphere_obj2->setPosition( x, y, z );

	x = 220 * cos( 2 * M_2_PI / 3 + k2 );
	z = 200 * sin( 2 * M_2_PI / 3 + k2 );
	sphere_obj3->setPosition( x, y, z );

	y = 250 + fabs(  200 * sin( k4 )  );
	sphere_obj4->setPosition( 0, y, -400 );

	//  Rotate tubes
	capsule_obj1->heading( rads( 5) );
	capsule_obj2->heading( rads(-1) );
}

