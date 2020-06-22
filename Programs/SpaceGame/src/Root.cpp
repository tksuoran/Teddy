
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


#include "Teddy/TeddyConfig.h"
#include "Teddy/Teddy.h"
#include "Teddy/Application/BaseSimulationTimer.h"
#include "Teddy/Application/BaseAudioManager.h"
#include "Teddy/Graphics/View.h"
#include "Teddy/SysSupport/Messages.h"
#include <cstdlib>
#include <cstring>

#include "ActionManager.h"
#include "FrontierModel.h"
#include "ObjectManager.h"
#include "UserInterface.h"
#include "Root.h"
using Teddy::Application::BaseAudioManager;
using Teddy::Application::BaseSimulationTimer;
using Teddy::Graphics::View;
using namespace Teddy::SysSupport;


/*virtual*/ void Root::start( int agrc, char **argv ){
	BaseRoot::start( agrc, argv );
	user_interface   = new UserInterface      ( this );  //  Opens view
	object_manager   = new ObjectManager      ( this );  //  Creates scene and camera
	action_manager   = new ActionManager      ( this );
	simulation_timer = new BaseSimulationTimer();
	object_manager  ->addObjects   ( ffe_options );  //  Add objects to scene
	user_interface  ->addComponents();  //  Create UserInterface
	simulation_timer->start        ();  //  Start simulation timer
	user_interface  ->enterRunLoop ();  //  Enter run loop
}


/*virtual*/ void Root::parseOptions(){
    printf( "\nparseOptions()\n" );
	if( hasOpt("--ffe-debug")               ) ffe_options.enable( FrontierModel::OPT_DEBUG               );
	if( hasOpt("--ffe-real-scaling")        ) ffe_options.enable( FrontierModel::OPT_REAL_SCALING        );
	if( hasOpt("--ffe-do-children" )        ) ffe_options.enable( FrontierModel::OPT_DO_CHILDREN         );
	if( hasOpt("--ffe-do-triangles")        ) ffe_options.enable( FrontierModel::OPT_DO_TRIANGLES        );
	if( hasOpt("--ffe-do-mirror-triangles") ) ffe_options.enable( FrontierModel::OPT_DO_MIRROR_TRIANGLES );
	if( hasOpt("--ffe-do-quads")            ) ffe_options.enable( FrontierModel::OPT_DO_QUADS            );
	if( hasOpt("--ffe-do-mirror-quads")     ) ffe_options.enable( FrontierModel::OPT_DO_MIRROR_QUADS     );
	if( hasOpt("--ffe-do-lines")            ) ffe_options.enable( FrontierModel::OPT_DO_LINES            );
	if( hasOpt("--ffe-do-splines")          ) ffe_options.enable( FrontierModel::OPT_DO_SPLINES          );
	if( hasOpt("--ffe-do-polys")            ) ffe_options.enable( FrontierModel::OPT_DO_POLYS            );
	if( hasOpt("--ffe-do-balls")            ) ffe_options.enable( FrontierModel::OPT_DO_BALLS            );
	if( hasOpt("--ffe-do-ellipsoids")       ) ffe_options.enable( FrontierModel::OPT_DO_ELLIPSOIDS       );
	if( hasOpt("--ffe-do-cylinders")        ) ffe_options.enable( FrontierModel::OPT_DO_CYLINDERS        );
	if( hasOpt("--ffe-do-cones")            ) ffe_options.enable( FrontierModel::OPT_DO_CONES            );

	if( hasOpt("--no-ffe-debug")               ) ffe_options.disable( FrontierModel::OPT_DEBUG               );
	if( hasOpt("--no-ffe-real-scaling")        ) ffe_options.disable( FrontierModel::OPT_REAL_SCALING        );
	if( hasOpt("--no-ffe-do-children" )        ) ffe_options.disable( FrontierModel::OPT_DO_CHILDREN         );
	if( hasOpt("--no-ffe-do-triangles")        ) ffe_options.disable( FrontierModel::OPT_DO_TRIANGLES        );
	if( hasOpt("--no-ffe-do-mirror-triangles") ) ffe_options.disable( FrontierModel::OPT_DO_MIRROR_TRIANGLES );
	if( hasOpt("--no-ffe-do-quads")            ) ffe_options.disable( FrontierModel::OPT_DO_QUADS            );
	if( hasOpt("--no-ffe-do-mirror-quads")     ) ffe_options.disable( FrontierModel::OPT_DO_MIRROR_QUADS     );
	if( hasOpt("--no-ffe-do-lines")            ) ffe_options.disable( FrontierModel::OPT_DO_LINES            );
	if( hasOpt("--no-ffe-do-splines")          ) ffe_options.disable( FrontierModel::OPT_DO_SPLINES          );
	if( hasOpt("--no-ffe-do-polys")            ) ffe_options.disable( FrontierModel::OPT_DO_POLYS            );
	if( hasOpt("--no-ffe-do-balls")            ) ffe_options.disable( FrontierModel::OPT_DO_BALLS            );
	if( hasOpt("--no-ffe-do-ellipsoids")       ) ffe_options.disable( FrontierModel::OPT_DO_ELLIPSOIDS       );
	if( hasOpt("--no-ffe-do-cylinders")        ) ffe_options.disable( FrontierModel::OPT_DO_CYLINDERS        );
	if( hasOpt("--no-ffe-do-cones")            ) ffe_options.disable( FrontierModel::OPT_DO_CONES            );

}


/*virtual*/ void Root::setDefaultOptions(){
    printf( "\nsetDefaultOptions()\n" );
	BaseRoot::setDefaultOptions();  //  super::setDefaultOptions()

    ffe_options.setOptions(
//		FrontierModel::OPT_DEBUG               |
//		FrontierModel::OPT_REAL_SCALING        |
//		FrontierModel::OPT_DO_CHILDREN         |
		FrontierModel::OPT_DO_TRIANGLES        |
		FrontierModel::OPT_DO_MIRROR_TRIANGLES |
		FrontierModel::OPT_DO_QUADS            |
		FrontierModel::OPT_DO_MIRROR_QUADS     |
//		FrontierModel::OPT_DO_LINES            |
//		FrontierModel::OPT_DO_SPLINES          |
		FrontierModel::OPT_DO_POLYS            |
//		FrontierModel::OPT_DO_BALLS            |
//		FrontierModel::OPT_DO_ELLIPSOIDS       |
//		FrontierModel::OPT_DO_CYLINDERS        |
//		FrontierModel::OPT_DO_CONES            |
        0
	);
}

