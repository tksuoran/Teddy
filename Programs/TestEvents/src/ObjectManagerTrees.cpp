
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


using namespace Teddy::Application;
using namespace Teddy::Behaviour;
using namespace Teddy::Materials;
using namespace Teddy::Models;
using namespace Teddy::Scenes;
using namespace Teddy::SysSupport;


bool ObjectManager::addTrees(){
	BaseSimulationTimer *st = getSimulationTimer();
    //  Make tree shape
	Tree *tree_mesh1 = new Tree( st, 4*SD, SD,        4, 300.0f,  60.0f, 60.0f );
	Tree *tree_mesh2 = new Tree( st, 4*SD, SD + SD/2, 6, 700.0f, 100.0f, 60.0f );

	srand( 2000 );
	int i;
	Material *m1 = new Material( Color(0.30f,0.50f,0.10f) );
	Material *m2 = new Material( Color(0.50f,0.60f,0.10f) );
	Material *m3 = new Material( Color(0.10f,0.30f,0.00f) );
	Material *m4 = new Material( Color(0.15f,0.40f,0.10f) );
	Material *m5 = new Material( Color(0.70f,0.60f,0.30f) );
	Material *m6 = new Material( Color(0.00f,0.30f,0.30f) );
	Material *m7 = new Material( Color(0.40f,0.60f,0.50f) );
	m1->setSpecular( Color(0.9f,0.7f,0.6f) );
	m2->setSpecular( Color(0.9f,0.7f,0.6f) );
	m3->setSpecular( Color(0.9f,0.7f,0.6f) );
	m4->setSpecular( Color(0.5f,0.7f,0.6f) );
	m5->setSpecular( Color(0.5f,0.7f,0.6f) );
	m6->setSpecular( Color(0.5f,0.7f,0.6f) );
	m7->setSpecular( Color(0.5f,0.7f,0.6f) );
	m1->setShininess(100.0f );
	m2->setShininess(100.0f );
	m3->setShininess(100.0f );
	m4->setShininess(100.0f );
	m5->setShininess( 40.0f );
	m6->setShininess( 40.0f );
	m7->setShininess( 40.0f );

	for( i=0; i<40; i++ ){
		Model *tree_obj;
		int    mesh_type = (int)((2.0f * (float)rand() ) / (float)RAND_MAX);
		int    mesh_mat  = (int)((8.0f * (float)rand() ) / (float)RAND_MAX);
		float  x_pos     = 1200.0f - (2400.0f * (float)rand() ) / (float)RAND_MAX;
		float  z_pos     = 1200.0f + (1200.0f * (float)rand() ) / (float)RAND_MAX;
		float  rot_angs  = 0.004f - (0.008f * (float)rand() ) / (float)RAND_MAX;

		switch( mesh_type ){
		case 0:
			tree_obj = new Model( "", tree_mesh1 );
			break;
		case 1:
		default:
			tree_obj = new Model( "", tree_mesh2 );
			break;
		}

		switch( mesh_mat ){
		case 0 : tree_obj->setMaterial( m1 ); break;
		case 1 : tree_obj->setMaterial( m2 ); break;
		case 2 : tree_obj->setMaterial( m3 ); break;
		case 3 : tree_obj->setMaterial( m4 ); break;
		case 4 : tree_obj->setMaterial( m5 ); break;
		case 5 : tree_obj->setMaterial( m6 ); break;
		default: tree_obj->setMaterial( m7 ); break;
		}
		tree_obj->setPosition( x_pos, 0, z_pos );

		Vector zv = Vector(0,0,0);

		st->add(
			new ModelAnimator(
				tree_obj, 
				zv, 
				rot_angs,  
				0,  
				0 
			)  
		);

		getScene()->add( tree_obj );
	}
	return true;
}

