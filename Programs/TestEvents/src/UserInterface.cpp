
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

	$Id: UserInterface.cpp,v 1.5 2002/03/12 10:44:29 tksuoran Exp $
*/


#include "Teddy/Graphics/View.h"                     //  Graphics device
#include "Teddy/Materials/Material.h"                //
#include "Teddy/PhysicalComponents/ActionButton.h"   //  EventListener can receive input messages
#include "Teddy/PhysicalComponents/Button.h"
#include "Teddy/PhysicalComponents/EventListener.h"  //  EventListener can receive input messages
#include "Teddy/PhysicalComponents/Label.h"          //  Simple text user interface component
#include "Teddy/PhysicalComponents/Layer.h"          //  Container for windows
#include "Teddy/PhysicalComponents/WindowManager.h"  //  manages all windows
#include "Teddy/PhysicalComponents/Style.h"          //
#include "Teddy/PhysicalComponents/MenuList.h"       //
#include "Teddy/PhysicalComponents/Dock.h"           //
#include "Teddy/PhysicalComponents/Popup.h"          //
#include "Teddy/SysSupport/Messages.h"
#include <cstdlib>                                   //  exit();

#include "Display.h"
#include "ObjectManager.h"
#include "Root.h"
#include "SimpleText.h"
#include "UserInterface.h"
using namespace Teddy::Application;
using namespace Teddy::Graphics;
using namespace Teddy::Materials;
using namespace Teddy::PhysicalComponents;
using namespace Teddy::Signals;
using namespace Teddy::SysSupport;


UserInterface::UserInterface( Root *root )
:
Node             ( root ),
BaseUserInterface( root )
{
}


/*!
	Create rest of the user interface
	\todo Access to superclass's protected members should be fixed (use methods)
*/
/*virtual*/ void UserInterface::addComponents(){
	View::check();
    ObjectManager *om = getObjectManager();

    menu = new Dock( "Menu", DOCK_HORIZONTAL );

    Area  *m_scene = new MenuList( "Scene MenuList" );
    Popup *p_scene = new Popup   ( "Scene", m_scene );

    menu->insert( p_scene );
    m_scene->insert( new ActionButton( "^                   ", functor(p_scene,&Popup::close) ) );
    m_scene->insert( new ActionButton( "addLights           ", functor(om,&ObjectManager::addLights             ) ) );
    m_scene->insert( new ActionButton( "addFloorAndBoxes    ", functor(om,&ObjectManager::addFloorAndBoxes      ) ) );
    m_scene->insert( new ActionButton( "addConesAndCylinders", functor(om,&ObjectManager::addConesAndCylinders  ) ) );
    m_scene->insert( new ActionButton( "addSpheresAndTorus  ", functor(om,&ObjectManager::addSpheresAndTorus    ) ) );
    m_scene->insert( new ActionButton( "addSolids           ", functor(om,&ObjectManager::addSolids             ) ) );
    m_scene->insert( new ActionButton( "addLwo              ", functor(om,&ObjectManager::addLwo                ) ) );
    m_scene->insert( new ActionButton( "addTrees            ", functor(om,&ObjectManager::addTrees              ) ) );
    m_scene->insert( new ActionButton( "addBallStacks       ", functor(om,&ObjectManager::addBallStacks         ) ) );
    m_scene->insert( new ActionButton( "addLSystems         ", functor(om,&ObjectManager::addLSystems           ) ) );
    m_scene->insert( new ActionButton( "addGlow             ", functor(om,&ObjectManager::addGlow               ) ) );
    m_scene->insert( new ActionButton( "addAxes             ", functor(om,&ObjectManager::addAxes               ) ) );
    m_scene->insert( new ActionButton( "addTeddyLogo        ", functor(om,&ObjectManager::addTeddyLogo          ) ) );
    m_scene->insert( new ActionButton( "Open New Window     ", functor(this,&UserInterface::sceneLoad  ) ) );
    m_scene->insert( new ActionButton( "(Save )",              functor(this,&UserInterface::sceneSave  ) ) );
    m_scene->insert( new ActionButton( "(Empty)",              functor(this,&UserInterface::sceneEmpty ) ) );
    m_scene->insert( new ActionButton( "Quit ",                functor(this,&UserInterface::sceneQuit  ) ) );

    Area  *m_select   = new MenuList( "Select"           );
    Popup *p_select   = new Popup   ( "Select", m_select );
    menu->insert( p_select   );
    m_select  ->insert( new ActionButton( "^",            functor(p_select,&Popup::close)                ) );
    m_select  ->insert( new ActionButton( "(Cameras)",   functor(this,&UserInterface::modifyParameters   ) ) );
    m_select  ->insert( new ActionButton( "(Objects)",   functor(this,&UserInterface::modifyParameters   ) ) );
    m_select  ->insert( new ActionButton( "(Lights)",    functor(this,&UserInterface::modifyParameters   ) ) );

    Area  *m_display   = new MenuList( "Display"            );
    Popup *p_display   = new Popup   ( "Display", m_display );
    menu->insert( p_display   );
    m_display  ->insert( new ActionButton( "^",            functor(p_display,&Popup::close)                ) );
    m_display  ->insert( new ActionButton( "Point",        functor(this,&UserInterface::displayPoint       ) ) );
    m_display  ->insert( new ActionButton( "Line",         functor(this,&UserInterface::displayLine        ) ) );
    m_display  ->insert( new ActionButton( "Fill",         functor(this,&UserInterface::displayFill        ) ) );
    m_display  ->insert( new ActionButton( "Fill Outline", functor(this,&UserInterface::displayFillOutline ) ) );
    m_display  ->insert( new ActionButton( "Textures",     functor(this,&UserInterface::displayTextures    ) ) );
    m_display  ->insert( new ActionButton( "No Textures" , functor(this,&UserInterface::displayNoTextures  ) ) );

    Area  *m_lights = new MenuList( "Lights"           );
    Popup *p_lights = new Popup   ( "Lights", m_lights );
    menu->insert( p_lights    );
    m_lights   ->insert( new ActionButton( "^",            functor(p_lights,&Popup::close                  ) ) );
    m_lights   ->insert( new ActionButton( "Color",        functor(this,&UserInterface::lightsColor        ) ) );
    m_lights   ->insert( new ActionButton( "Color",        functor(this,&UserInterface::lightsColor        ) ) );
    m_lights   ->insert( new ActionButton( "Simple",       functor(this,&UserInterface::lightsSimple       ) ) );
    m_lights   ->insert( new ActionButton( "(Full)",       functor(this,&UserInterface::lightsFull         ) ) );

    Area  *m_animation = new MenuList( "Animation"              );
    Popup *p_animation = new Popup   ( "Animation", m_animation );
	menu->insert( p_animation );
    m_animation->insert( new ActionButton( "^",            functor(p_animation,&Popup::close               ) ) );
    m_animation->insert( new ActionButton( "(Run)",        functor(this,&UserInterface::animationRun       ) ) );
    m_animation->insert( new ActionButton( "(Stop)",       functor(this,&UserInterface::animationStop      ) ) );

    Area  *m_create    = new MenuList( "Create"           );
    Popup *p_create    = new Popup   ( "Create", m_create );
    menu->insert( p_create );
    m_create   ->insert( new ActionButton( "^",            functor(p_create,&Popup::close                  ) ) );
    m_create   ->insert( new ActionButton( "(Box)",          functor(this,&UserInterface::createBox          ) ) );
    m_create   ->insert( new ActionButton( "(Capsule)",      functor(this,&UserInterface::createCapsule      ) ) );
    m_create   ->insert( new ActionButton( "(Cone)",         functor(this,&UserInterface::createCone         ) ) );
    m_create   ->insert( new ActionButton( "(Cylinder)",     functor(this,&UserInterface::createCylinder     ) ) );
    m_create   ->insert( new ActionButton( "(Sphere)",       functor(this,&UserInterface::createSphere       ) ) );
    m_create   ->insert( new ActionButton( "(Torus)",        functor(this,&UserInterface::createTorus        ) ) );

    Area  *m_modify    = new MenuList( "Modify"           );
    Popup *p_modify    = new Popup   ( "Modify", m_modify );
    menu->insert( p_modify );
    m_modify   ->insert( new ActionButton( "^",            functor(p_modify,&Popup::close   ) ) );
    m_modify   ->insert( new ActionButton( "(Parameters)",   functor(this,&UserInterface::modifyParameters   ) ) );
    m_modify   ->insert( new ActionButton( "(Move)",         functor(this,&UserInterface::modifyMove         ) ) );
    m_modify   ->insert( new ActionButton( "(Rotate)",       functor(this,&UserInterface::modifyRotate       ) ) );
    m_modify   ->insert( new ActionButton( "(Scale)",        functor(this,&UserInterface::modifyScale        ) ) );
    m_modify   ->insert( new ActionButton( "(Transform)",    functor(this,&UserInterface::modifyTransform    ) ) );
    m_modify   ->insert( new ActionButton( "(Clone)",        functor(this,&UserInterface::modifyClone        ) ) );
    m_modify   ->insert( new ActionButton( "(Remove)",       functor(this,&UserInterface::modifyRemove       ) ) );

	View::check();
    getLayer()->insert( menu );

    getWindowManager()->setHold( false );
	getView()->setClear( true );
    getLayer()->place();

    //view->setCull( 0 );
    //camera->setMirrorX( false );

	View::check();
    sceneLoad();
    lightsSimple();
	View::check();
    om->addLights();
	View::check();
    om->addFloorAndBoxes();
}


bool UserInterface::sceneLoad(){
    camera  = getObjectManager()->getCamera();
	display = new Display( root, camera );
	message = new SimpleText( root );
	display   ->bindController( getObjectManager()->getCamera() );

	//  Connect the display to the layer and add the layer to window manager
	getLayer()->addProjection( display );
	getLayer()->insert       ( message  );
	getLayer()->place        ();
    setProjection( display );

	//  Set some default values for the display window
	display->getMaster()->setOptions ( Material::RENDER_OPTION_ALL_M    );
    display->getMaster()->setMode    ( Material::RENDER_MODE_FILL       );
	display->getMaster()->setLighting( Material::RENDER_LIGHTING_COLOR    );
	display->getMaster()->disable    ( Material::RENDER_OPTION_TEXTURE_2D_M );
	display->getMaster()->setDiffuse ( Color::WHITE );
	getView()->setClear( true );

	if( root->hasOpt("--cursor"   ) ) getWindowManager()->showCursor();
	if( root->hasOpt("--no-cursor") ) getWindowManager()->hideCursor();
	if( (root->hasOpt("--bg-red"  ) == true) &&
	    (root->hasOpt("--bg-green") == true) &&
		(root->hasOpt("--bg-blue" ) == true)    )
	{
		float r = root->getOptFloat("--bg-red"  );
		float g = root->getOptFloat("--bg-green");
		float b = root->getOptFloat("--bg-blue" );
		display->setClearColor( Color(r,g,b,1) );
	}else{
		display->setClearColor( Color(0.20f,0.25f,0.30f,1.0f) );
	}
	return true;
}

bool UserInterface::sceneSave         (){return true;}
bool UserInterface::sceneEmpty        (){return true;}
bool UserInterface::sceneQuit         (){ exit(0); return true;}

bool UserInterface::displayPoint      (){ display->getMaster()->setMode( Material::RENDER_MODE_POINT        );  return true;}
bool UserInterface::displayLine       (){ display->getMaster()->setMode( Material::RENDER_MODE_LINE         );  return true;}
bool UserInterface::displayFill       (){ display->getMaster()->setMode( Material::RENDER_MODE_FILL         );  return true;}
bool UserInterface::displayFillOutline(){ display->getMaster()->setMode( Material::RENDER_MODE_FILL_OUTLINE );  return true;}
bool UserInterface::displayTextures   (){ display->getMaster()->enable ( Material::RENDER_OPTION_TEXTURE_2D_M );  return true;}
bool UserInterface::displayNoTextures (){ display->getMaster()->disable( Material::RENDER_OPTION_TEXTURE_2D_M );  return true;}

bool UserInterface::lightsColor       (){ display->getMaster()->setLighting( Material::RENDER_LIGHTING_COLOR  ); return true;}
bool UserInterface::lightsSimple      (){ display->getMaster()->setLighting( Material::RENDER_LIGHTING_SIMPLE ); return true;}
bool UserInterface::lightsFull        (){ display->getMaster()->setLighting( Material::RENDER_LIGHTING_FULL   ); return true;}

bool UserInterface::animationRun      (){return true;}
bool UserInterface::animationStop     (){return true;}

bool UserInterface::createBox         (){return true;}
bool UserInterface::createCapsule     (){return true;}
bool UserInterface::createCone        (){return true;}
bool UserInterface::createCylinder    (){return true;}
bool UserInterface::createSphere      (){return true;}
bool UserInterface::createTorus       (){return true;}

bool UserInterface::modifyParameters  (){return true;}
bool UserInterface::modifyMove        (){return true;}
bool UserInterface::modifyRotate      (){return true;}
bool UserInterface::modifyScale       (){return true;}
bool UserInterface::modifyTransform   (){return true;}
bool UserInterface::modifyClone       (){return true;}
bool UserInterface::modifyRemove      (){return true;}


void UserInterface::setDisplay( Display *display ){
	this->display = display;
}

Display *UserInterface::getDisplay(){
	return this->display;
}


