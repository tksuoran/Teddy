
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

	$Id: UserInterface.cpp,v 1.2 2002/03/12 10:44:29 tksuoran Exp $
*/


#include "Teddy/Graphics/View.h"                        //  Graphics device
#include "Teddy/Imports/LWSceneParser.h"
#include "Teddy/Materials/Material.h"                   //
#include "Teddy/PhysicalComponents/ActionButton.h"
#include "Teddy/PhysicalComponents/Dock.h"
#include "Teddy/PhysicalComponents/EventListener.h"     //  EventListener can receive input messages
#include "Teddy/PhysicalComponents/Label.h"             //  Simple text user interface component
#include "Teddy/PhysicalComponents/Layer.h"             //  Container for windows
#include "Teddy/PhysicalComponents/MenuList.h"
#include "Teddy/PhysicalComponents/Popup.h"
#include "Teddy/PhysicalComponents/WindowManager.h"     //  manages all windows
#include "Teddy/PhysicalComponents/Style.h"             //  
#include "Teddy/Scenes/Scene.h"
#include "Teddy/Signals/Functor.h"
#include "Teddy/SysSupport/FileScan.h"
#include "Teddy/SysSupport/Messages.h"

#include "Display.h"
#include "ObjectManager.h"
#include "Root.h"
#include "SimpleText.h"
#include "UserInterface.h"
using namespace Teddy::Application;
using namespace Teddy::Graphics;
using namespace Teddy::Imports;
using namespace Teddy::Materials;
using namespace Teddy::PhysicalComponents;;
using namespace Teddy::Scenes;
using namespace Teddy::SysSupport;
using namespace Teddy::Signals;


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
	Camera     *camera     = getObjectManager()->getCamera();
	SimpleText *message    = new SimpleText( root );
	display                = new Display   ( root, camera );
	display->bindController( getObjectManager()->getCamera() );	

	//  Connect the display to the layer and add the layer to window manager
	//getWindowManager()->setHold( false );
    menu = new Dock( "TeddyPlayer Menu", DOCK_HORIZONTAL );
	getLayer()->insert( menu );
	sceneMenu();

	menu->insert( new ActionButton( "Items"  ,  functor(this,&UserInterface::menu_items   ) ) );
	menu->insert( new ActionButton( "Objects",  functor(this,&UserInterface::menu_objects ) ) );
	menu->insert( new ActionButton( "Lights" ,  functor(this,&UserInterface::menu_lights  ) ) );
	menu->insert( new ActionButton( "Camera" ,  functor(this,&UserInterface::menu_camera  ) ) );
	menu->insert( new ActionButton( "Scene"  ,  functor(this,&UserInterface::menu_scene   ) ) );
	menu->insert( new ActionButton( "LScript",  functor(this,&UserInterface::menu_lscript ) ) );
	menu->insert( new ActionButton( "Display",  functor(this,&UserInterface::menu_display ) ) );
														
#if 0
    Area  *m_animation = new MenuList( "Animation Menu" );
    Popup *p_animation = new Popup   ( "Animation Menu", m_animation );
    menu->insert( p_animation );
	dmsg( M_INIT, "befor m_animation->insert( new ActionButton( \"^\",         functor(p_animation,&Popup::close) ) );" );
    //m_animation->insert( new ActionButton( "^",         functor(p_animation,&Popup::close) ) );
	dmsg( M_INIT, "after m_animation->insert( new ActionButton( \"^\",         functor(p_animation,&Popup::close) ) );" );
    //m_animation->insert( new ActionButton( "Play (p)",  functor(this,&UserInterface::play) ) );
	dmsg( M_INIT, "2" );
    m_animation->insert( new ActionButton( "Stop (s)",  functor(this,&UserInterface::stop) ) );
	dmsg( M_INIT, "3" );
    m_animation->insert( new ActionButton( "Reset (r)", functor(this,&UserInterface::reset) ) );
#endif

	dmsg( M_INIT, "getLayer()->addProjection( display );" );

	getLayer()->addProjection( display );
	getLayer()->insert       ( message  );
	getLayer()->place        ();
	setProjection( display );

	dmsg( M_INIT, "display->getMaster()->setOptions ( Material::RENDER_OPTION_ALL_M    );" );

	//  Set some default values for the display window
	display->getMaster()->setOptions ( Material::RENDER_OPTION_ALL_M    );
	display->getMaster()->setMode    ( Material::RENDER_MODE_FILL       );
	display->getMaster()->setLighting( Material::RENDER_LIGHTING_SIMPLE );
	display->getMaster()->setDiffuse ( Color::WHITE );
    getView()->setCull      ( 1 );
	const float lwb = 145.0f / 255.0f;
    getView()->setClearColor(  Color(lwb,lwb,lwb,1.0f) );
	getView()->setClear     ( true );
    //getView()->setClear( false );

	if( root->hasOpt("--cursor"   ) ) getWindowManager()->showCursor();
	if( root->hasOpt("--no-cursor") ) getWindowManager()->hideCursor();

    display->setClearColor( Color::GRAY_50 );

	dmsg( M_INIT, "void UserInterface::addComponents() done" );

}


Display *UserInterface::getDisplay(){
	return display;
}


void UserInterface::objectMenu(){
	Scene *scene         = getObjectManager()->getScene();
    Area  *object_list   = new MenuList( "Objects" );
    Popup *object_list_p = new Popup   ( "Objects", object_list );

    object_list->insert( new ActionButton( "^", functor(object_list_p,&Popup::close) ) );

	menu->insert( object_list_p );

	list<Model*>           &models = scene->getModels();
	list<Model*>::iterator  m_it   = models.begin();
	while( m_it != models.end() ){
		Model *model = *m_it;
		objectMenuItem( model, object_list );
		m_it++;
	}
	getLayer()->place();
}


void UserInterface::objectMenuItem( Model *model, Area *parent ){
    MenuList *child_list   = new MenuList( model->getName() );
    Popup    *child_list_p = new Popup   ( model->getName(), child_list );
	parent->insert( child_list_p );
    child_list->insert( new ActionButton( model->getName(), functor(child_list_p,&Popup::close) ) );

	list<Model*>           &children = model->getChildren();
	list<Model*>::iterator  c_it     = children.begin();
	while( c_it != children.end() ){
		Model *child = *c_it;
		objectMenuItem( child, child_list );
		c_it++;
	}
}

void UserInterface::sceneMenu(){
	dmsg( M_INIT, MSG_HEAD "Scanning for LightWave scene files..." );

	FileScan scenes( "Data/lws/*.lws" );
	int                    num     = scenes.get_files().size();
	list<char*>::iterator  f_it    = scenes.get_files().begin();
	ObjectManager         *om      = getObjectManager();
    Area                  *m_scene = new MenuList( "File" );
    Popup                 *p_scene = new Popup   ( "File", m_scene );
	menu   ->insert( p_scene );


	dmsg( M_INIT, "Found %d scenes", num );

    m_scene->insert( new ActionButton( "^", functor(p_scene,&Popup::close) ) );
	m_scene->insert( new ActionButton( "Scan LightWave Objects", functor(om,&ObjectManager::scanLwo) ) );

	//	Read in all files and slice them to lines
	while( f_it != scenes.get_files().end() ){
		char *fname = new char[ strlen((*f_it))+10 ];
#		if defined( _MSC_VER )
		sprintf( fname, "Data/lws/%s",  *f_it );
#		else
		sprintf( fname, "%s",  *f_it );
#		endif

		msg( M_INIT, fname );
	    m_scene->insert(
			new ActionButton(  fname, functor(om,&ObjectManager::loadScene), fname  )
		);
		f_it++;
	}

	dmsg( M_INIT, "LightWave scene menu finished" );
	getLayer()->place();
	dmsg( M_INIT, "getLayer()->place(); done" );
}	


bool UserInterface::play(){
	LWSceneParser *lwsc = getObjectManager()->getLWSceneParser();
	if( lwsc != NULL ){
		lwsc->play();
	}
	return true;
}


bool UserInterface::stop(){
	LWSceneParser *lwsc = getObjectManager()->getLWSceneParser();
	if( lwsc != NULL ){
		lwsc->stop();
	}
	return true;
}


bool UserInterface::reset(){
	LWSceneParser *lwsc = getObjectManager()->getLWSceneParser();
	if( lwsc != NULL ){
		lwsc->reset();
	}
	return true;
}


bool UserInterface::menu_items  (){ return true; }
bool UserInterface::menu_objects(){ return true; }
bool UserInterface::menu_lights (){ return true; }
bool UserInterface::menu_camera (){ return true; }
bool UserInterface::menu_scene  (){ return true; }
bool UserInterface::menu_lscript(){ return true; }
bool UserInterface::menu_display(){ return true; }

