
/*
	TSGL - Teddy Space Game Library
	Copyright (C) 2002 Timo Suoranta
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


//#include "UniverseDevelopmentKit/CMaster.h"
//#include "SpaceGame/CollisionGroup.h"
#include "Teddy/Graphics/View.h"
#include "Teddy/Materials/Material.h"
#include "Teddy/Scenes/Scene.h"

#include "ObjectManager.h"
#include "RoamAlgorithm.h"
#include "RoamInstance.h"
#include "RoamSphere.h"
using namespace Teddy::Scenes;
using namespace Teddy::Materials;


//!  Test ROAM object
void ObjectManager::addROAM(){
#if 0
	Material *mat;

	mat = new Material( "Roam material",
		RENDER_MODE_FILL,
		RENDER_LIGHTING_SIMPLE,
		RENDER_OPTION_CULL_FACE_M  |
		RENDER_OPTION_DEPTH_TEST_M |
		RENDER_OPTION_AMBIENT_M    |
		RENDER_OPTION_DIFFUSE_M    |
		RENDER_OPTION_SPECULAR_M   |
		RENDER_OPTION_EMISSION_M   |
		RENDER_OPTION_SHINYNESS_M  |
		RENDER_OPTION_NORMALIZE_M  |
//		RENDER_OPTION_BORDER_M	   |
		RENDER_OPTION_SMOOTH_M
	);
	mat->setShininess( 8.0f );
	mat->setAmbient  ( Color(0.1f,0.1f,0.1f) );
	mat->setDiffuse  ( Color(0.5f,0.5f,0.5f) );
	mat->setSpecular ( Color(0.3f,0.3f,0.3f) );
//	mat->setBorder	 ( Color(0.0f,0.0f,0.0f) );

	roam_update = true;
	roam_const	= 0.000006f;
	RoamAlgorithm *roam_algo = new RoamAlgorithm();
	RoamSphere *roam = new RoamSphere();
	roam_algo->init(19082000, 2000, 600.0f, 0, 32 );
	roam->init( roam_algo );
	roam->setClipRadius( 2000+600.0f );

	RoamInstance *mi_roam = new RoamInstance(
		"Roam Bubble",
		roam
	);
	mi_roam->setPosition( 0, 0, -2000 -600 -400 );
	mi_roam->setMaterial( mat );

	scene->addInstance( mi_roam );
	view->display();

//	solar_bodies_cg->insert( mi_roam );
#endif
}

