
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


#include "Teddy/Graphics/ImageFileTexture.h"
#include "Teddy/Graphics/View.h"
#include "Teddy/Imports/LWModel.h"
#include "Teddy/Materials/Material.h"
#include "Teddy/Models/Box.h"
#include "Teddy/Models/Cone.h"
#include "Teddy/Models/Model.h"
#include "Teddy/Models/Sphere.h"
#include "Teddy/Models/Torus.h"
#include "Teddy/Models/Capsule.h"
#include "Teddy/Models/Vertex.h"
#include "Teddy/Scenes/Scene.h"
#include "Teddy/SysSupport/FileScan.h"

#include "ObjectManager.h"
//using namespace Teddy::Imports;
using namespace Teddy::Materials;
using namespace Teddy::Models;
using namespace Teddy::Scenes;


//!  Add primitive objects to scene
void ObjectManager::addPrimitives(){
	Material *m1 = new Material( "Test Material m1" );
	m1->setEmission( Color(0,0,0) );
	m1->setAmbient ( Color(0.3f,0.2f,0.1f) );
	m1->setDiffuse ( Color(0.3f,0.2f,0.1f) );
	m1->setSpecular( Color(0.4f,0.4f,0.8f) );
	m1->setBorder  ( Color(0,0,1) );
	m1->setMode    ( Material::RENDER_MODE_FILL );
	m1->setLighting( Material::RENDER_LIGHTING_SIMPLE );
	m1->setOptions (
		Material::RENDER_OPTION_CULL_FACE_M  |
		Material::RENDER_OPTION_DEPTH_TEST_M |
		Material::RENDER_OPTION_AMBIENT_M    |
		Material::RENDER_OPTION_DIFFUSE_M    |
		Material::RENDER_OPTION_SPECULAR_M   |
		Material::RENDER_OPTION_EMISSION_M   |
		Material::RENDER_OPTION_SHINYNESS_M  |
		Material::RENDER_OPTION_SMOOTH_M
	);
	m1->setShininess( 8.0f );

	//  Add Torus
	Torus *torus = new Torus( "Torus", 1000.0, 200.0, 5, 4 );
	torus->setPosition( 1000.0, 1000, 0 );
	torus->setMaterial( &Material::RED );
	scene->add( torus );

	//  Add Tube
/*	Capsule       *capsule = new Capsule( "Capsule", 20.0, 5.0, 21, 24 );
	ModelInstance *mi_tube = new ModelInstance( "Capsule", tube );
	mi_tube->setPosition( -30.0, 0.0, 0.0 );
	mi_tube->setMaterial( &Material::YELLOW );
	scene->add( mi_tube );*/

	// Add Cone
/*	Cone		  *cone    = new Cone( "Cone", 10.0f, 3.0f, 10.0f, 17, 11 );
	ModelInstance *mi_cone = new ModelInstance( "Cone", cone );
	mi_cone->setPosition( 30.0, 0.0, -30.0	);
	mi_cone->setMaterial( m1 );
	scene->add( mi_cone );*/

	// Add Sphere
/*	Sphere		  *sphere	 = new Sphere( "Sphere", 10.0f, 17, 17 );
	ModelInstance *mi_sphere = new ModelInstance( "Sphere", sphere );
	mi_sphere->setPosition( -15.0, 0.0, -40.0 );
	mi_sphere->setMaterial( &Material::WHITE );
//		mi_sphere->getMaterial()->setTexture( new SdlTexture( "mars.jpg" ), true );
	scene->add( mi_sphere );*/

	// Add Box
	Box *box = new Box( "Box", 800, 400, 400, 8, 4, 4 );
	box->setPosition( -1000, 1000, 0 );
	box->setMaterial( &Material::CYAN );
	scene->add( box );
//1	view->display();
}

