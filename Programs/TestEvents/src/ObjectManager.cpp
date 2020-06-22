
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

	$Id: ObjectManager.cpp,v 1.6 2002/03/12 10:44:29 tksuoran Exp $
*/


#include "Teddy/TeddyConfig.h"

#include "Bouncer.h"
#include "Display.h"
#include "LSystem.h"
#include "ObjectManager.h"
#include "Orbiter.h"
#include "Tree.h"
#include "UserInterface.h"

#include "Teddy/Application/BaseSimulationTimer.h"
#include "Teddy/Behaviour/ModelAnimator.h"
#include "Teddy/Graphics/ImageFileTexture.h"  //  Image texture loader
#include "Teddy/Graphics/View.h"
#include "Teddy/Imports/LWModel.h"             //  LWMesh loads Lightwave objects
#include "Teddy/Imports/LWSceneParser.h"
#include "Teddy/Materials/Material.h"         //  Material texture lighting properties
#include "Teddy/Materials/Light.h"            //  Lightsource
#include "Teddy/Models/Model.h"
#include "Teddy/Models/Box.h"                 //  Box primitive object
#include "Teddy/Models/Cone.h"                //  Cone primitive object
#include "Teddy/Models/Cylinder.h"            //  Cylinder primitive object
#include "Teddy/Models/Grid.h"                //  Grid primitive object
#include "Teddy/Models/Solids.h"
#include "Teddy/Models/Sphere.h"              //  Sphere primitive object
#include "Teddy/Models/Torus.h"               //  Torus = donought primitive object
#include "Teddy/Models/Capsule.h"             //  Tube primitive object
#include "Teddy/Scenes/Camera.h"              //  Observer point and attitude
#include "Teddy/Scenes/PostElement.h"
#include "Teddy/Scenes/Scene.h"               //  Collection of objects
#include "Teddy/SysSupport/Messages.h"        //
#include "Teddy/SysSupport/StdSDL.h"
#include "Teddy/SysSupport/StdIO.h"

#ifndef SWIG
#include <cstdlib>
#endif

#include "Teddy/TeddyConfig.h"
#ifdef TEDDY_INCLUDE_FTGL	
#include "Teddy/Ftgl/FTGLExtrdFont.h"
#include "Teddy/Ftgl/FTGLOutlineFont.h"
#include "Teddy/Ftgl/FTGLPolygonFont.h"
#include "Teddy/Ftgl/FTGLTextureFont.h"
#include "Teddy/Ftgl/FTGLPixmapFont.h"
#include "Teddy/Ftgl/FTGLBitmapFont.h"
#endif

using namespace Teddy::Application;
using namespace Teddy::Behaviour;
#if defined( TEDDY_INCLUDE_LW_SCENE )
using namespace Teddy::Imports;
#endif
using namespace Teddy::Materials;
using namespace Teddy::Models;
using namespace Teddy::Scenes;
using namespace Teddy::SysSupport;


ObjectManager::ObjectManager( Root *root )
:
Node( root ),
material_backup( Material::BLUE )
//  Hmm check BaseObjectManager() default constructor
{
	//  Create scene and camera
	scene  = new Scene ( "Test Scene"         );
	camera = new Camera( "Test Camera", scene );
	camera->setFov    ( 70 );
	camera->setNearFar( 4, 4096 );

	if( root->hasOpt("--subdiv") ){
		SD = root->getOptInt("--subdiv");
	}else{
        SD = 2;
    }

	//  Selection
	selected_model = NULL;

	//  Set initial camera configuration (that is, position and attitude)
	camera->setPosition( DoubleVector(-1000, 400, 1000) );
	camera->heading    ( -45.0f );
	camera->setFov     (  80.0f );
	st = getSimulationTimer();

#if 0
    FTGLExtrdFont *ft_font = new FTGLExtrdFont;
    //const char * fontfile = "Data/arial.ttf";
    const char * fontfile = "Data/arial.ttf";
    if( !ft_font->Open( fontfile, false) ){
        fprintf( stderr, "Failed to open font %s", fontfile);
        exit(1);
    }

    if( !ft_font->FaceSize( 200) ){
        fprintf( stderr, "Failed to set size");
        exit(1);
    }

    ft_font->Depth(35);
    ft_font->CharMap(ft_encoding_unicode);

	Model *teddy_logo = ft_font->getModel( "Teddy" );
	teddy_logo->setMaterial( &Material::LIGHT_ORANGE );
	teddy_logo->setPosition( 0.0, 400.0, 0.0 );
    scene->add( teddy_logo );
#endif
}



bool ObjectManager::addFloorAndBoxes(){
	//  Make box shapes
	Box *box_mesh       = new Box( "Box shape",        200, 200,  100, 2*SD, 2*SD, 1*SD );
	Box *floor_box_mesh = new Box( "Floor box shape", 1200,  50, 2400, 4*SD,    1, 8*SD );

	View::check();
    //  Make box materials
	Material *textured_material1 = new Material(Material::WHITE,Material::RENDER_LIGHTING_SIMPLE);
	Material *textured_material2 = new Material(Material::WHITE,Material::RENDER_LIGHTING_SIMPLE);
	Texture  *texture1           = new ImageFileTexture( "Data/textures/texture9.jpg" );
	//Texture  *texture2           = new ImageFileTexture( "Data/textures/grid2.png" );
	Texture  *texture2           = new ImageFileTexture( "Data/textures/grid4.png" );
	texture2->setFilter( Texture::FILTER_NEAREST );
	texture2->doBind();

    //  Make box instances
	Model *box_obj1  = new Model( "Box one",   box_mesh       );
	Model *box_obj2  = new Model( "Box two",   box_mesh       );
	Model *floor_box = new Model( "Floor box", floor_box_mesh );

	//  Finish materials
	box_mesh->getGeometry()->makeCubicTextureCoordinates(
		Vector(   0,   0,   0 ),
		Vector( 400, 400, 400 )
	);

	floor_box_mesh->getGeometry()->makeCubicTextureCoordinates(
		Vector(   0,   0,   0 ),
		Vector( 200, 200, 200 )
	);
	textured_material1->setTexture( texture1 );
	textured_material2->setTexture( texture2 );

	box_obj2 ->setMaterial( textured_material1 );
	box_obj1 ->setMaterial( textured_material1 );
	floor_box->setMaterial( textured_material2 );

	box_obj1 ->setPosition( -400, 200, -500 );
	box_obj2 ->setPosition(  400, 200, -500 );
	floor_box->setPosition(    0, -50,    0 );

	Vector       zv = Vector(0,0,0);
	//const double k1 = rads( -0.5 );
	//const double k2 = rads(  0.5 );
	  const double k3 = rads( -0.4 );
	//const double k4 = rads(  0.4 );

	st->add(  new ModelAnimator( box_obj2, zv, k3,  0,  0 )  );

	scene->add( floor_box );
	//scene->add( box_obj1  );
    //scene->add( box_obj2  );
	return true;
}


//  Create some shapes                                Dimensions       Subdisions
bool ObjectManager::addConesAndCylinders(){
    //  Make shapes
	Cone    *cone_mesh     = new Cone   ( "Cone shape",     100,    0,  400, 4*SD, 4*SD );
	Cone    *cylinder_mesh = new Cone   ( "Cylinder shape", 100,  100,  200, 6*SD, 3*SD );
	Capsule *capsule_mesh  = new Capsule( "Tube shape",      40,   10,       3*SD, 3*SD );

	Matrix m_syz;  //  matrix to swap y and z
	m_syz.setRow( 0, Vector4(1,0,0,0) ); // nx = 1*x + 0*y + 0*z + 0
	m_syz.setRow( 1, Vector4(0,0,1,0) ); // ny = 0*x + 0*y + 1*z + 0
	m_syz.setRow( 2, Vector4(0,1,0,0) ); // nz = 0*x + 1*y + 0*z + 0
	m_syz.setRow( 3, Vector4(0,0,0,1) );
	cone_mesh    ->transformVertices( m_syz );
	cylinder_mesh->transformVertices( m_syz );

	Model *cone_obj1    = new Model( "Cone one",     cone_mesh     );
	Model *cone_obj2    = new Model( "Cone two",     cone_mesh     );
	Model *cyl_obj1     = new Model( "Cylinder one", cylinder_mesh );
	Model *cyl_obj2     = new Model( "Cylinder two", cylinder_mesh );
	Model *capsule_obj1 = new Model( "Capsule one",  capsule_mesh  );
	Model *capsule_obj2 = new Model( "Capsule two",  capsule_mesh  );

	Matrix mat;
	mat.rotateZMatrix( 0.5 );
	mat.rotateX( 1.0 );
	cone_obj1->transform( mat );

	cone_obj1   ->setMaterial( new Material(Color(1.0f,0.4f,0.2f)) );
	cone_obj2   ->setMaterial( new Material(Color(0.3f,1.0f,0.2f)) );
	cyl_obj1    ->setMaterial( &Material::ORANGE       );
	cyl_obj2    ->setMaterial( &Material::LIGHT_ORANGE );
	capsule_obj1->setMaterial( &Material::WHITE        );
	capsule_obj2->setMaterial( &Material::WHITE        );

	cone_obj1   ->setPosition( -400,   0,    0 );
	cone_obj2   ->setPosition(  400,   0,    0 );
	cyl_obj1    ->setPosition(  200,   0,  500 );
	cyl_obj2    ->setPosition(    0,   0, -500 );
	capsule_obj1->setPosition(    0, 400,    0 );
	capsule_obj2->setPosition(    0, 400,    0 );

	cone_obj1->add( capsule_obj1 );
	cone_obj2->add( capsule_obj2 );
	scene    ->add( cone_obj1    );
	scene    ->add( cone_obj2    );
	scene    ->add( cyl_obj1     );
	scene    ->add( cyl_obj2     );

	Vector       zv = Vector(0,0,0);
	const double k1 = rads( -0.5 );
	const double k2 = rads(  0.5 );

	st->add(  new ModelAnimator( capsule_obj1, zv, k2,  0,  0 )  );
	st->add(  new ModelAnimator( capsule_obj2, zv, k1,  0,  0 )  );
	return true;
}


//  Add spheres and a torus
bool ObjectManager::addSpheresAndTorus(){
	//  Make shapes
	Sphere *sphere_mesh1 = new Sphere( "Small Sphere shape",  50,      4*SD, 4*SD );
	Sphere *sphere_mesh2 = new Sphere( "Big Sphere shape",   150,      6*SD, 6*SD );
	Torus  *torus_mesh   = new Torus ( "Torus shape",        100, 90, 11*SD, 4*SD );

    //  Make instances
	Model *sphere_obj1 = new Model( "Sphere 1",   sphere_mesh1 );  //  .
	Model *sphere_obj2 = new Model( "Sphere 2",   sphere_mesh1 );  //	 > Small orbiting sphere
	Model *sphere_obj3 = new Model( "Sphere 3",   sphere_mesh1 );  //  /
	Model *sphere_obj4 = new Model( "Sphere 4",   sphere_mesh1 );  //  Bouncing sphere
	Model *sphere_obj5 = new Model( "Big Sphere", sphere_mesh2 );  //  Big sphere in the middle
	Model *torus_obj1  = new Model( "Torus",      torus_mesh   );

    //  Set materials
	sphere_obj1->setMaterial( &Material::LIGHT_YELLOW  );
	sphere_obj2->setMaterial( &Material::LIGHT_CYAN    );
	sphere_obj3->setMaterial( &Material::LIGHT_GREEN   );
	sphere_obj4->setMaterial( &Material::LIGHT_BLUE    );
	sphere_obj5->setMaterial( &Material::DARK_BLUE     );
	torus_obj1 ->setMaterial( &Material::BLACK         );

	//  Set objects' positions
	sphere_obj1->setPosition(    0, 250,  220 );
	sphere_obj2->setPosition(    0, 250, -220 );
	sphere_obj3->setPosition( -220, 250,    0 );
	sphere_obj4->setPosition(  220, 250,    0 );  //  Bouncing sphere
	sphere_obj5->setPosition(    0, 220,    0 );  //  Big sphere in the middle
	torus_obj1 ->setPosition(    0,  40,    0 );

    //  Add objects to scene
	sphere_obj5->add( sphere_obj1 );
	sphere_obj5->add( sphere_obj2 );
	sphere_obj5->add( sphere_obj3 );
	scene      ->add( sphere_obj4 );
	scene      ->add( sphere_obj5 );
	scene      ->add( torus_obj1  );

	st->add(  new Orbiter( sphere_obj1, Vector(0,  0,   0), Vector(200, 0,0), Vector(0,0,200), 300.0, 0.0*M_2_PI/3.0 )  );
	st->add(  new Orbiter( sphere_obj2, Vector(0,  0,   0), Vector(200, 0,0), Vector(0,0,200), 300.0, 1.0*M_2_PI/3.0 )  );
	st->add(  new Orbiter( sphere_obj3, Vector(0,  0,   0), Vector(200, 0,0), Vector(0,0,200), 300.0, 2.0*M_2_PI/3.0 )  );
    st->add(  new Bouncer( sphere_obj4, Vector(0.0f,250.0f,-500.0f), Vector(  0.0f, 5.0f,0.0f), Vector(0.0f,-0.1f, 0.0f)  )  );

	//  Modify some shapes
	//  Rotate torus from z axis to y axis
	Matrix m_syz;  //  matrix to swap y and z
	m_syz.setRow( 0, Vector4(1,0,0,0) ); // nx = 1*x + 0*y + 0*z + 0
	m_syz.setRow( 1, Vector4(0,0,1,0) ); // ny = 0*x + 0*y + 1*z + 0
	m_syz.setRow( 2, Vector4(0,1,0,0) ); // nz = 0*x + 1*y + 0*z + 0
	m_syz.setRow( 3, Vector4(0,0,0,1) );
	torus_mesh   ->transformVertices( m_syz );

    //  Scale the big sphere to a flat ellipsoid
	m_syz.setRow( 0, Vector4(1.0,0.0,0.0,0) );
	m_syz.setRow( 1, Vector4(0.0,0.2f,0.0,0) );
	m_syz.setRow( 2, Vector4(0.0,0.0,0.6f,0) );
	m_syz.setRow( 3, Vector4(0.0,0.0,0.0,1) );
	sphere_mesh2 ->transformVertices( m_syz );

	//  Scale the torus'
	//  Currently this doesn't work
    //  because cleartraversal is missing
	m_syz.setRow( 1, Vector4(0.0,2.0,0.0,0) );
	m_syz.setRow( 2, Vector4(0.0,0.0,1.0,0) );
	torus_mesh->transformVertices( m_syz );
	return true;
}


bool ObjectManager::addSolids(){
	const double r = 128.0;
	Model *so1 = new Cube                  ( r );
	Model *so2 = new Cuboctahedron         ( r );
	Model *so3 = new Dodecahedron          ( r );
	Model *so4 = new Icosahedron           ( r );
	Model *so5 = new Octahedron            ( r );
	Model *so6 = new Tetrahedron           ( r );
	Model *so7 = new TruncatedCube         ( r );
	Model *so8 = new TruncatedCuboctahedron( r );
	Model *so9 = new TruncatedOctahedron   ( r );
	so1->setMaterial( &Material::RED     ); 
	so2->setMaterial( &Material::ORANGE  ); 
	so3->setMaterial( &Material::YELLOW  ); 
	so4->setMaterial( &Material::GREEN   ); 
	so5->setMaterial( &Material::CYAN    ); 
	so6->setMaterial( &Material::BLUE    ); 
	so7->setMaterial( &Material::MAGENTA ); 
	so8->setMaterial( &Material::GRAY_75 ); 
	so9->setMaterial( &Material::GRAY_25 ); 
	so1->setPosition( -600, 200, 1100 );
	so2->setPosition( -300, 200, 1200 );
	so3->setPosition(  000, 200, 1300 );
	so4->setPosition(  300, 200, 1400 );
	so5->setPosition( -600, 200, 1500 );
	so6->setPosition( -300, 200, 1600 );
	so7->setPosition(  000, 200, 1700 );
	so8->setPosition(  300, 200, 1800 );
	so9->setPosition( -600, 200, 1900 );
	scene->add( so1 );
	scene->add( so2 );
	scene->add( so3 );
	scene->add( so4 );
	scene->add( so5 );
	scene->add( so6 );
	scene->add( so7 );
	scene->add( so8 );
	scene->add( so9 );
	return true;
}


bool ObjectManager::addAxes(){
	{
		Vector    p1  = Vector( 300,100,800 );
		Vector    p2  = Vector( 400,100,800 );
		Vector    dir = p2 - p1;
		double    len = dir.magnitude();
		Cylinder *cyl = new Cylinder( "Cylinder shape",  10,  len, 3*SD );
		Matrix m;  //  matrix to swap y and z
		m.direction( dir );
		cyl->transformVertices( m );
		Model *ci = new Model( "ci", cyl );
		ci->setPosition( p1 );
		ci->setMaterial( &Material::RED );
		scene->add( ci );
	}
	{
		Vector    p1  = Vector( 300,100,800 );
		Vector    p2  = Vector( 300,200,800 );
		Vector    dir = p2 - p1;
		double    len = dir.magnitude();
		Cylinder *cyl = new Cylinder( "Cylinder shape",  10,  len, 3*SD );
		Matrix m;  //  matrix to swap y and z
		m.direction( dir );
		cyl->transformVertices( m );
		Model *ci = new Model( "ci", cyl );
		ci->setPosition( p1 );
		ci->setMaterial( &Material::GREEN );
		scene->add( ci );
	}
	{
		Vector    p1  = Vector( 300,100,800 );
		Vector    p2  = Vector( 300,100,900 );
		Vector    dir = p2 - p1;
		double    len = dir.magnitude();
		Cylinder *cyl = new Cylinder( "Cylinder shape",  10,  len, 3*SD );
		Matrix m;  //  matrix to swap y and z
		m.direction( dir );
		cyl->transformVertices( m );
		Model *ci = new Model( "ci", cyl );
		ci->setPosition( p1 );
		ci->setMaterial( &Material::BLUE );
		scene->add( ci );
	}
	{
		Vector    p1  = Vector( 300,100,800 );
		Vector    p2  = Vector( 400,200,900 );
		Vector    dir = p2 - p1;
		double    len = dir.magnitude();
		Cylinder *cyl = new Cylinder( "Cylinder shape",  10,  len, 3*SD );
		Matrix m;  //  matrix to swap y and z
		m.direction( dir );
		cyl->transformVertices( m );
		Model *ci = new Model( "ci", cyl );
		ci->setPosition( p1 );
		ci->setMaterial( &Material::WHITE );
		scene->add( ci );
	}
	return true;
}


bool ObjectManager::addGlow(){
	//  Test postelement
	PostElement *pe1 = new PostElement( "Data/textures/gray.png"     ); scene->add( pe1 );
	PostElement *pe2 = new PostElement( "Data/textures/blue.png"     ); scene->add( pe2 );
	PostElement *pe3 = new PostElement( "Data/textures/darkcyan.png" ); scene->add( pe3 );
	PostElement *pe4 = new PostElement( "Data/textures/red.png"   ); scene->add( pe4 );
	Vector pos( 0, 400,400 );
	Vector dir( 0,   0, 1 );
	double s1 =  20.0;
	double s2 =   2.0*s1;
	double r1 =  50.0;
	double r2 =  30.0;
	double r3 =   1.0;
	double l1 =  30.0;
	double l2 =  35.0;
    double l3 =  40.0;
    Vector npo = pos;
	pe1->insert(  new Ellipsoid( npo, dir, r1*2,  1, l1*2 )  );
	pe2->insert(  new Ellipsoid( npo, dir, r2*2,  1, l2*2 )  );
	pe3->insert(  new Ellipsoid( npo, dir, r3*2,  1, l3*2 )  );
    npo = pos + Vector(  s1,  s2, 0.0 );
//	pe1->insert(  new Ellipsoid( npo, dir, r1,  1, l1 )  );
	pe4->insert(  new Ellipsoid( npo, dir, r2,  1, l2 )  );
//	pe3->insert(  new Ellipsoid( npo, dir, r3,  1, l3 )  );
    npo = pos + Vector( -s1,  s2, 0.0 );
//	pe1->insert(  new Ellipsoid( npo, dir, r1,  1, l1 )  );
	pe4->insert(  new Ellipsoid( npo, dir, r2,  1, l2 )  );
//	pe3->insert(  new Ellipsoid( npo, dir, r3,  1, l3 )  );
    npo = pos + Vector(  s1, -s2, 0.0 );
//	pe1->insert(  new Ellipsoid( npo, dir, r1,  1, l1 )  );
	pe4->insert(  new Ellipsoid( npo, dir, r2,  1, l2 )  );
//	pe3->insert(  new Ellipsoid( npo, dir, r3,  1, l3 )  );
    npo = pos + Vector( -s1, -s2, 0.0 );
//	pe1->insert(  new Ellipsoid( npo, dir, r1,  1, l1 )  );
	pe4->insert(  new Ellipsoid( npo, dir, r2,  1, l2 )  );
//	pe3->insert(  new Ellipsoid( npo, dir, r3,  1, l3 )  );
    npo = pos + Vector( -s2,   0.0, 0.0 );
//	pe1->insert(  new Ellipsoid( npo, dir, r1,  1, l1 )  );
	pe4->insert(  new Ellipsoid( npo, dir, r2,  1, l2 )  );
//	pe3->insert(  new Ellipsoid( npo, dir, r3,  1, l3 )  );
    npo = pos + Vector(  s2,    0.0, 0.0 );
//	pe1->insert(  new Ellipsoid( npo, dir, r1,  1, l1 )  );
	pe4->insert(  new Ellipsoid( npo, dir, r2,  1, l2 )  );
//	pe3->insert(  new Ellipsoid( npo, dir, r3,  1, l3 )  );
	return true;
}

//  Selectiop
void ObjectManager::selectModel( Model *model ){

	//  Restore previous object states
	if( selected_model != NULL ){
		Material *model_material = selected_model->getMaterial();
		if( model_material != NULL ){
			model_material->copy( material_backup );
		}
	}

	selected_model = model;
	if( model != NULL ){
		Material *model_material = selected_model->getMaterial();
		if( model_material != NULL ){
			material_backup.copy( *model_material );
			model_material->setBorder  ( Color::WHITE );
			model_material->setAmbient ( Color::WHITE );
			model_material->setDiffuse ( Color::WHITE );
			model_material->setLighting( Material::RENDER_LIGHTING_COLOR );
			model_material->setMode    ( Material::RENDER_MODE_LINE );
		}
	}
}


Model *ObjectManager::getSelectedModel(){
	return selected_model;
}
