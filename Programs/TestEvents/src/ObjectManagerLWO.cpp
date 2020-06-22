
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


bool ObjectManager::addTeddyLogo(){
#if defined( TEDDY_INCLUDE_LW_SCENE )
	LWModel *teddy_model = new LWModel( "Data/lwo/teddy.lwo", 0 );

    //  matrix to swap y and z, and scale by 200
	Matrix m_syz;
	double s = 300.0;
	m_syz.setRow( 0, Vector4(s,0,0,0) );
	m_syz.setRow( 1, Vector4(0,0,s,0) );
	m_syz.setRow( 2, Vector4(0,s,0,0) );
	m_syz.setRow( 3, Vector4(0,0,0,1) );
	teddy_model->transformVertices( m_syz );

/*	Material *t_mat = new Material( Color(0.70f,0.75f,0.80f) );
	t_mat->setSpecular( Color(0.8f,0.8f,1.0f) );
	t_mat->setShininess(100.0f );
	teddy_model->setMaterial( t_mat, true );*/
/*	teddy_model->setMaterial( &Material::WHITE );*/

	teddy_model->setPosition(  0, 500,  0 );
	scene->add( teddy_model );
#endif
	return true;
}

					
//  Load some lightwave objects
bool ObjectManager::addLwo(){
#if defined( TEDDY_INCLUDE_LW_SCENE )

	LWModel *lwo_cubeoctahedron = new LWModel( "Data/lwo/cubeoctahedron.lwo", 0 );
	LWModel *lwo_dodecahedron   = new LWModel( "Data/lwo/dodecahedron.lwo"  , 0 );
	LWModel *lwo_donought       = new LWModel( "Data/lwo/donought.lwo"      , 0 );
	LWModel *lwo_edged_sphere   = new LWModel( "Data/lwo/edged_sphere.lwo"  , 0 );
	LWModel *lwo_sphere         = new LWModel( "Data/lwo/sphere.lwo"        , 0 );

	lwo_cubeoctahedron->setPosition( -800, 100,  800 );
	lwo_dodecahedron  ->setPosition( -400, 100,  800 );
	lwo_donought      ->setPosition(    0, 100,  800 );
	lwo_edged_sphere  ->setPosition(  400, 100,  800 );
	lwo_sphere        ->setPosition(  800, 100,  800 );

	Vector       zv = Vector(0,0,0);
	// const double k1 = rads( -0.5 );
	// const double k2 = rads(  0.5 );
	// const double k3 = rads( -0.4 );
	// const double k4 = rads(  0.4 );

    /*
	st->add(  new BaseModelAnimator( lwo_cubeoctahedron, zv,  0,  0, k2 )  );
	st->add(  new BaseModelAnimator( lwo_edged_sphere,   zv, k3,  0,  0 )  );
	st->add(  new BaseModelAnimator( lwo_donought,       zv, k4,  0,  0 )  );
    st->add(  new BaseModelAnimator( lwo_sphere,         zv,  0, k2,  0 )  );
    */

	scene->add( lwo_cubeoctahedron );
	scene->add( lwo_dodecahedron   );
	scene->add( lwo_donought       );
	scene->add( lwo_edged_sphere   );
	scene->add( lwo_sphere         );
#endif
	return true;
}


