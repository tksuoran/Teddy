
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

	$Id: ObjectManager.cpp,v 1.3 2002/03/12 10:44:29 tksuoran Exp $
*/


#include "Teddy/Application/BaseSimulationTimer.h"
#include "Teddy/Behaviour/ModelAnimator.h"
#include "Teddy/Graphics/View.h"
#include "Teddy/Imports/LWModel.h"               //  LWModel loads Lightwave objects
#include "Teddy/Imports/LWSceneParser.h"
#include "Teddy/Materials/Material.h"            //  Material texture lighting properties
#include "Teddy/Materials/Light.h"               //  Lightsource
#include "Teddy/Maths/Quaternion.h"
#include "Teddy/Models/Model.h"                  //  Object instance
#include "Teddy/Scenes/Scene.h"                  //  Collection of objects
#include "Teddy/Scenes/Camera.h"                 //  Observer point and attitude
#include "Teddy/SysSupport/FileScan.h"
#include "Teddy/SysSupport/Messages.h"
#include "Teddy/SysSupport/StdSDL.h"
#include "Teddy/SysSupport/StdIO.h"
#ifndef SWIG
#include <cstdlib>
#endif

#include "Display.h"
#include "EventManager.h"
#include "ObjectManager.h"
#include "UserInterface.h"
using namespace Teddy::Application;
using namespace Teddy::Behaviour;
using namespace Teddy::Imports;
using namespace Teddy::Materials;
using namespace Teddy::Maths;
using namespace Teddy::Models;
using namespace Teddy::Scenes;


ObjectManager::ObjectManager( Root *root )
:
Node(root)
{
	//  Create scene and camera
	scene        = new Scene ( "Test Scene"         );
	camera       = new Camera( "Test Camera", scene );

	{
		double h = rads( 0.0 );
		double p = rads( 0.0 );
		double b = rads( 0.0 );
		Quaternion 
		q  = Quaternion( Vector(0.0,0.0,1.0),  -b );
		q *= Quaternion( Vector(1.0,0.0,0.0),  -p );
		q *= Quaternion( Vector(0.0,1.0,0.0),  -h );
		camera->getAttitude() = q;
	}
	scene_parser = NULL;
	camera->setMirrorX ( true );
	camera->setFov     ( 60 );
	float near_clip =    0.2f;
	float far_clip  = 8000.0f;
	if( root->hasOpt("--near") ) near_clip = root->getOptFloat("--near");
	if( root->hasOpt("--far" ) ) far_clip  = root->getOptFloat("--far");
	camera->setNearFar( near_clip, far_clip );

    float lwgcc = 112.0f / 255.0f;
    Color lwgc  = Color( lwgcc, lwgcc, lwgcc );
	floor_mat   = new Material( lwgc );
    floor_mat->setMode    ( Material::RENDER_MODE_LINE );
    floor_mat->setLighting( Material::RENDER_LIGHTING_COLOR );
	floor     = new Grid( 16, 16, 1.0f, 1.0f );
	floor    ->setMaterial( floor_mat );
	floor    ->setPosition( 0, 0, 0 );	
    scene->add( floor );
}


/*virtual*/ void ObjectManager::addObjects(){
}


LWSceneParser *ObjectManager::getLWSceneParser(){
	return scene_parser;
}


bool ObjectManager::loadScene( void *ptr ){
	scene->getModels().clear();
	scene->getLights().clear();
	//scene->remove( floor );
	//delete floor;
	floor = NULL;

	char *scene_filename = (char *)( ptr );
	if( scene_filename != NULL ){
		LWSceneParser *tmp = new LWSceneParser( scene, camera, scene_filename, 0 );
		tmp->reset();
		BaseSimulationTimer *st = getSimulationTimer();
		st->add( tmp );
		scene_parser = tmp;
	}

#if 0
	UserInterface *ui      = getUserInterface();
	Display       *display = ui->getDisplay();
	
	display->bindController( camera );	  //  Check for leaks here
	display->setCamera     ( camera );
#endif

	//getUserInterface()->objectMenu();
    adjustToScene();
    floor = scene_parser->getGrid();
    if( floor != NULL ){
        floor->setMaterial( floor_mat );
        floor->setPosition( 0, 0.0, 0 );
        scene->add( floor );
    }
	float      v_grid = scene_parser->getGridSize      ();
	float      v_zoom = scene_parser->getViewZoomFactor();
	Quaternion v_rot  = scene_parser->getViewRotation  ();
	Vector     v_aim  =	scene_parser->getViewAimpoint  ();
	Vector     v_pos  = v_aim - v_rot.getViewAxis() * v_grid * 13.0f;	
	camera->setZoomFactor( v_zoom );
	camera->getAttitude  () = v_rot; 
    camera->setPosition  ( v_pos );

	return true;
}


void ObjectManager::adjustToScene(){
    getUserInterface()->getDisplay()->getCameraController()->adjustToScene();
    float max_size  = scene->getMaxObSize    ();
    float max_dist  = scene->getMaxObDistance();
    float scale     = max_dist + max_size;
    float near_clip = scale * 0.002;
    float far_clip  = 8.0f * scale;
	if( near_clip == 0.0 || far_clip == 0.0 ){
		dmsg( 
			M_MAT, 
			"near_clip = %8.4f far_clip = %8.4f scale = %12.6f", 
			near_clip,
			far_clip,
			scale
		);
	}else{
		camera->setNearFar( near_clip, far_clip );
	}
}



//  Load some lightwave objects
bool ObjectManager::scanLwo(){
	scene->remove( floor );
	delete floor;
	floor = NULL;

	FileScan lwos( "Data/lwo/*.lwo" );
	int      num = lwos.get_files().size();

	if( num == 0 ){
		return true;
	}

	list<char*>::iterator f_it = lwos.get_files().begin();
	char *fname;

	double   largest = 0;
	Model  **lwom    = new Model*[ num ];
	int      count   = 0;

	//	Read in all files
	while( f_it != lwos.get_files().end() ){
		{ fname = new char[ strlen((*f_it))+15 ];
#			if defined( _MSC_VER )
				sprintf( fname, "Data/lwo/%s",  *f_it );
#			else
				sprintf( fname, "%s",  *f_it );
#			endif

			lwom[count] = new LWModel( string(fname), 0 );
			if( lwom[count] != NULL ){
				double size = lwom[count]->getClipRadius();
				if( size > largest ){
					largest = size;
				}
			}
			delete fname;
		}
		count++;
		f_it++;
	}

	int    n       = (int)sqrt( (double)num );
	double offset  = (n * largest );
	double xcursor = -offset;
	double zcursor = -offset;
	for( int i=0; i<count; i++ ){		
		scene->add( lwom[i] );
		lwom[i]->setPosition( xcursor, 0, zcursor );
		xcursor += largest *2;
		if( xcursor > offset ){
			xcursor =- offset;
			zcursor += largest *2;
		}
	}
	delete[] lwom;

	Light *l = new Light( "LWLight" );
	/*
		<mrmuk> appears to be H: 45 deg, P: 35 deg, B: 0 deg
		<mrmuk> location (-2, 2, -2)
	*/
	{
		double h = rads( 45.0 );
		double p = rads( 35.0 );
		double b = rads(  0.0 );
		Quaternion 
		q  = Quaternion( Vector(0.0,1.0,0.0),  M_PI+h );
		q *= Quaternion( Vector(1.0,0.0,0.0),       p );
		q *= Quaternion( Vector(0.0,0.0,1.0),       b );
		l->getAttitude() = q;
	}
	l->setPosition( -2.0, 2.0, -2.0 );
	l->setAmbient ( Color::BLACK );
	l->setDiffuse ( Color::GRAY_75 );
	l->setSpecular( Color::WHITE   );
	l->setType( Light::TYPE_DIRECTIONAL );
	l->enable();
	scene->add( l );
    adjustToScene();

    float max_size  = scene->getMaxObSize    ();
    float max_dist  = scene->getMaxObDistance();
    float scale     = max_dist + max_size;

	floor = new Grid( 32, 32, scale/16.0f, scale/16.0f );
	floor->setMaterial( floor_mat );
	floor->setPosition( 0, 0, 0 );	
    scene->add( floor );

	{
		double h = rads( 0.0 );
		double p = rads( 0.0 );
		double b = rads( 0.0 );
		Quaternion 
		q  = Quaternion( Vector(0.0,0.0,1.0),  -b );
		q *= Quaternion( Vector(1.0,0.0,0.0),  -p );
		q *= Quaternion( Vector(0.0,1.0,0.0),  -h );
		camera->getAttitude() = q;
	}

	return true;
}
