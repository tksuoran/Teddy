
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


#include "Teddy/Graphics/View.h"
#include "Teddy/Materials/Material.h"
#include "Teddy/Models/Model.h"
#include "Teddy/PhysicalComponents/Console.h"
#include "Teddy/Scenes/Scene.h"
#include "Teddy/SysSupport/Messages.h"

#include "ObjectManager.h"
#include "FrontierFile.h"
#include "FrontierBitmap.h"
#include "FrontierModel.h"
using namespace Teddy::Graphics;
using namespace Teddy::Models;
using namespace Teddy::Materials;
using namespace Teddy::Scenes;
using namespace Teddy::PhysicalComponents;
using namespace Teddy::SysSupport;


//!  Add FFE ships
void ObjectManager::addFFE( Options ffe_options ){
	Material *ffe_mat = new Material(
		"Frontier Test Material",
		Material::RENDER_MODE_LINE,
		Material::RENDER_LIGHTING_COLOR,
		Material::RENDER_OPTION_DEPTH_TEST_M |
		Material::RENDER_OPTION_DIFFUSE_M    
	);
	ffe_mat->setAmbient  ( Color::BLACK );
	ffe_mat->setDiffuse  ( Color::GRAY_75 );
	ffe_mat->setSpecular ( Color::WHITE );
	ffe_mat->setShininess( 8.0f );

	FrontierFile  *f  =  new FrontierFile( "ffedat.asm", 0 );
	FrontierModel *m;

	if( ffe_options.isEnabled(FrontierModel::OPT_DEBUG) ){
		enable_msg( M_FFE );
	}
	dmsg( M_FFE, "Parsing FFE Objects:" );

	if( root->hasOpt("--ship")){

		m  = new FrontierModel(  f, root->getOptInt("--ship"), ffe_mat, ffe_options  );
		m->setPosition( Vector(  0,0,-200) );
		m->setMaterial( NULL );
		scene->add( m );

	}else if( root->hasOpt("--selected-only")){

		m  = new FrontierModel(  f,  23, ffe_mat, ffe_options );  //  Eagle long range fighter
		m->setPosition( Vector(  0,0,-200) ); scene->add( m );
		m  = new FrontierModel(  f,  31, ffe_mat, ffe_options );  //  Saker III
		m->setPosition( Vector(-200,0,-200) ); scene->add( m );
		m  = new FrontierModel (  f,  38, ffe_mat, ffe_options );  //  Cobra Mk III
		m->setPosition( Vector(-100,0,-200) ); scene->add( m );
		m  = new FrontierModel (  f,  46, ffe_mat, ffe_options );  //  Turner Class
		m->setPosition( Vector( 100,0,-200) ); scene->add( m );
		m  = new FrontierModel (  f, 440, ffe_mat, ffe_options );  //  Turner Class
		m->setPosition( Vector( 200,0,-200) ); scene->add( m );
		m  = new FrontierModel (  f,  56, ffe_mat, ffe_options  );  //  Imperial Courier
		m->setPosition( Vector(-200,0,0) ); scene->add( m );
		m  = new FrontierModel (  f,  65, ffe_mat, ffe_options );  //  Imperial Explorer
		m->setPosition( Vector(-100,0,0) ); scene->add( m );
		m  = new FrontierModel (  f,  66, ffe_mat, ffe_options );  //  IMRA Command Ship
		m->setPosition( Vector(   0,0,0) ); scene->add( m );
		m  = new FrontierModel (  f,  71, ffe_mat, ffe_options );  //  Long range cruiser
		m->setPosition( Vector( 100,0,0) ); scene->add( m );
		m  = new FrontierModel (  f, 108, ffe_mat, ffe_options );  //  Turner Class
		m->setPosition( Vector( 200,0,0) ); scene->add( m );

	}else{

		int i = 4;
		for( int x=0; x<21; x++ ){
			for( int z=0; z<22; z++ ){
				i++;
				m  = new FrontierModel (  f, i, ffe_mat, ffe_options  );
				m->setPosition( Vector( (x-12)*240.0, 0.0, (z-12)*240.0 ) );
				scene->add( m );
				msg( M_FFE, "OBJECT %d == %s", i, m->getName().c_str() );
			}
		}
	}

}

