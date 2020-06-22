
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
using namespace Teddy::Imports;
using namespace Teddy::Materials;
using namespace Teddy::Models;
using namespace Teddy::Scenes;
using namespace Teddy::SysSupport;


bool ObjectManager::addLights(){
	Sphere *li_mesh = new Sphere( "Light Indicator", 50, 2*SD, 2*SD );
	for( int i=0; i<7; i++ ){
	//  Create some lightsources and add them to the scene
		Light *light     = new Light( "Lightsource" );
		Model *light_ind = new Model( "Light indicator",  li_mesh );	
		float  x  =   1600.0f - (3200.0f * (float)rand() ) / (float)RAND_MAX;
		float  y  =    600.0f - ( 200.0f * (float)rand() ) / (float)RAND_MAX;
		float  z  =   2000.0f - (4000.0f * (float)rand() ) / (float)RAND_MAX;
		float  a  =   1600.0f + (1200.0f * (float)rand() ) / (float)RAND_MAX;
		float  b  =   2000.0f + (1000.0f * (float)rand() ) / (float)RAND_MAX;
		float  c  =    300.0f - ( 200.0f * (float)rand() ) / (float)RAND_MAX;
		float  s  =    800.0f + (1200.0f * (float)rand() ) / (float)RAND_MAX;
		{
			float  h  = (360.0f * (float)i / 7.0f); //360.0f      * ((float)rand() / (float)RAND_MAX);
			float  s  = 0.9f + 0.1f * ((float)rand() / (float)RAND_MAX);
			float  v  = 0.8f + 0.2f * ((float)rand() / (float)RAND_MAX);
			float  r,g,b;
			
			Color::hsv2rgb( h,s,v, &r, &g, &b );

			light->setPosition( x, y, z );
			light->setAmbient ( Color::GRAY_25 );
			light->setDiffuse ( Color(r,g,b) );
			light->setSpecular( Color::GRAY_25 );
			//light->setSpotCutOff( 100.0 );
			light->setSpotExponent( 120.0 );
			float linear = 0.1000000f + 0.1000000f * ((float)rand() / (float)RAND_MAX);
			float cubic  = 0.0001000f + 0.0001000f * ((float)rand() / (float)RAND_MAX);
			float quad   = 0.0000005f + 0.0000005f * ((float)rand() / (float)RAND_MAX);

			light->setAttenuation( linear, cubic, quad );
			light->enable();
	

			light_ind->setMaterial( new Material(Color(r,g,b)) );
			light_ind->getMaterial()->setLighting( Material::RENDER_LIGHTING_COLOR );
			light_ind->setPosition( x, y, z );
		}

		scene->add( light );
		scene->add( light_ind );

		st->add(  new Orbiter( light_ind, Vector(x,y,z), Vector(a,0.0f,0.0f), Vector(0.0f,c,b),s,0.0f )  );
		st->add(  new Orbiter( light    , Vector(x,y,z), Vector(a,0.0f,0.0f), Vector(0.0f,c,b),s,0.0f )  );
	}
	return true;
}


