
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
using namespace Teddy::Imports;
using namespace Teddy::Materials;
using namespace Teddy::Models;
using namespace Teddy::Scenes;
using namespace Teddy::SysSupport;


bool ObjectManager::addLSystems(){
	LSystem *lsystem2 = new LSystem();
	LSystem *lsystem3 = new LSystem();

	//  Tree
	lsystem2->setAxiom    ( "T"   );
	lsystem2->setLength   ( 10.0f );
	lsystem2->setThickness( 40.0f );
	lsystem2->setRule  ( 'T', "CCA" );
	lsystem2->setRule  ( 'A', "CBD>(94)CBD>(132)BD" );
	lsystem2->setRule  ( 'B', "[&CDCD$A]"       );
	lsystem2->setRule  ( 'D', "[g(5)Lg(5)L]"    );
	//  lsystem2->setRule  ( 'C', "!(0.95)~(5)tF"   );
	lsystem2->setRule  ( 'C', "!(0.80)~(5)tF"   );
	lsystem2->setRule  ( 'F', "'(1.25)F'(0.8)"  );
	lsystem2->setRule  ( 'L', "[~f(20)c(2){+(30)f(20)-(120)f(20)-(120)f(20)}]" );
	lsystem2->setRule  ( 'f', "'(0.7071)" );
	lsystem2->setRule  ( 'z', "_"         );
	lsystem2->setAngle ( 20.0 );
	lsystem2->expand   ( 10   );
	lsystem2->generate ();

	//  Plant
	lsystem3->setAxiom    ( "x"   );
	lsystem3->setLength   (  1.0f );
	lsystem2->setThickness(  5.0f );
	lsystem3->setRule  ( 'x', "<(5)F[++x][--x]<(5)'(1.1)F[++x][--x]'(0.9)F>(5)[+x][-x]'(0.9)F>(5)[x]" );
	lsystem3->setRule  ( 'F', "<(10)FFF>(10)" );
	lsystem3->setAngle ( 30.0f );
	lsystem3->expand   (  4    );
	lsystem3->generate ();

	//  Create objects
	Model *lsystem_obj2a = new Model( "Tree 1", lsystem2 );
	Model *lsystem_obj2b = new Model( "Tree 2", lsystem2 );
	Model *lsystem_obj2c = new Model( "Tree 3", lsystem2 );
	Model *lsystem_obj3  = new Model( "Plant",  lsystem3 );

	lsystem_obj2a->setMaterial( &Material::LIGHT_ORANGE );
	lsystem_obj2b->setMaterial( &Material::LIGHT_ORANGE );
	lsystem_obj2c->setMaterial( &Material::LIGHT_ORANGE );
	lsystem_obj3 ->setMaterial( &Material::LIGHT_GREEN );

	lsystem_obj2a->setPosition(    0,    0,  100 );
	lsystem_obj2b->setPosition(  300,    0,    0 );
	lsystem_obj2c->setPosition( -100,    0, -200 );
	lsystem_obj3 ->setPosition(    0,    0, 1200 );

	scene->add( lsystem_obj2a );
	scene->add( lsystem_obj2b );
	scene->add( lsystem_obj2c );
	scene->add( lsystem_obj3  );
	return true;
}

