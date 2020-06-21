
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
#include "BallStack.h"
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


bool ObjectManager::addBallStacks(){
    //  Make BallStack shape
	BallStack *BallStack_mesh1 = new BallStack( 4,  40.0f, 0.8f );
	BallStack *BallStack_mesh2 = new BallStack( 6,  10.0f, 2.0f );
	BallStack *BallStack_mesh3 = new BallStack( 9, 100.0f, 0.5f );

	srand( 2000 );
	int i;
	Material *m1 = new Material( Color::WHITE );
	m1->setSpecular( Color::WHITE );
	m1->setShininess(100.0f );
	for( i=0; i<60; i++ ){
		Model *BallStack_obj;
		int    mesh_type  = (int)((3.0f * (float)rand() ) / (float)RAND_MAX);
		float  x_pos      =   1600.0f - (3200.0f * (float)rand() ) / (float)RAND_MAX;
		float  z_pos      =  (2000.0f - (4000.0f * (float)rand() ) / (float)RAND_MAX);
		float  jump_speed =	 4.0f + (12.0f * (float)rand() ) / (float)RAND_MAX;

		switch( mesh_type ){
		case 0:
			BallStack_obj = new Model( "", BallStack_mesh1 );
			break;
		case 1:
			BallStack_obj = new Model( "", BallStack_mesh2 );
			break;
		case 2:
		default:
			BallStack_obj = new Model( "", BallStack_mesh3 );
			break;
		}

		BallStack_obj->setMaterial( m1 );
		BallStack_obj->setPosition( x_pos, 0, z_pos );
	    st->add(  
			new Bouncer( 
				BallStack_obj, 
				Vector(  x_pos,0.0f,z_pos), 
				Vector(  0.0f, jump_speed,0.0f), 
				Vector(0.0f,-0.1f, 0.0f)  
			)  
		);

		getScene()->add( BallStack_obj );
	}
	return true;
}

