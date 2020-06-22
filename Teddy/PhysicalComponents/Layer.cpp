
/*
	TEDDY - General graphics application library
	Copyright (C) 1999-2020  Timo Suoranta
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
#include "Teddy/PhysicalComponents/EventListener.h"
#include "Teddy/PhysicalComponents/Layer.h"
#include "Teddy/PhysicalComponents/Projection.h"
#include "Teddy/SysSupport/Messages.h"
using namespace Teddy::Graphics;


namespace Teddy              {
namespace PhysicalComponents {


//!  Constructor
Layer::Layer( std::string name, View *view ):Area(name){
	//GLint *viewp    = view->getViewport();
	this->parent    = NULL;
	this->view      = view;
	this->drawing_ordering = post_self;
	IntVector2 vs   = view->getSize();
	IntVector2 ziv  = IntVector2(0,0);
    this->rect      = Rect( ziv, vs );
	this->size      = rect.getSize();
	dmsg( M_WM, "Layer constructor done." );
}


//!  Area Input Interface - Get Hit Area, NULL if none
/*virtual*/ Area *Layer::getHit( const Vector2 &pos ){
    EventListener *e    = dynamic_cast<EventListener*>( this );
    const char    *name = getName().c_str();
	if( e != NULL ){
		dmsg( M_WME, "Trying layer %s - Listening for events", name  );
	}else{
		dmsg( M_WME, "Trying layer %s - not listening for events", name );
	}
	Area *hit = NULL;

	//	If we are first to draw, we could be hit?
	if( event_ordering == pre_self && e != NULL ){
		if( rect.hit(pos) ){
			dmsg( M_WME, "Hit this layer first" );
			return this;
		}
	}

    //  Test Children for hits
    if( !areas.empty() ){
        dmsg( M_WME, "Begin try children of layer %s", name );
        list<Area*>::iterator a_it = areas.begin();
        while( a_it != areas.end() ){
            hit = (*a_it)->Area::getHit( pos );
            if( hit != NULL ){
                dmsg( M_WME, "Hit child Area" );
                return hit;
            }
            a_it++;
        }
        dmsg( M_WME, "End try children of layer %s", name );
    }

	//  Test Projection areas for hits
    //if( !projs.empty() ){
        dmsg( M_WME, "Begin try projections of %s", name );
        list<Projection*>::iterator p_it = projs.begin();
        while( p_it != projs.end() ){
            hit = (*p_it)->getHit( pos );
            if( hit != NULL ){
                dmsg( M_WME, "Hit Projection Area" );
                return hit;
            }
            p_it++;
        }
        dmsg( M_WME, "End try projections of %s", name );
    //}

	//	If we are last to draw, we could be hit?
	if( event_ordering == post_self && e != NULL ){
		if( rect.hit(pos) ){
			dmsg( M_WME, "Hit this last" );
			return this;
		}
	}
	return hit;
}


//!  Set View
void Layer::update( View *view ){ // refresh/update, on resize for example
    dmsg( M_WML, "" );
    dmsg( M_WML, "Layer::update() ..." );
    rect = Rect( IntVector2(0,0), view->getSize() );
	size = rect.getSize();
    //layout_state.x1 = viewp[2] - viewp[0];
    //layout_state.y1 = viewp[3] - viewp[1];
	place();
    dmsg( M_WML, "Layer::update() done" );
}


//!  Draw Layer Self; draw Projection component
/*virtual*/ void Layer::drawSelf(){
	list<Projection*>::iterator p_it = projs.begin();
	while( p_it != projs.end() ){
		(*p_it)->drawSelf();
		p_it++;
	}
}

//!  Set Projection
void Layer::addProjection( Projection *p ){
	if( p!=NULL ){
		projs.push_back( p );
		p->setParent( this, this->view );
		this->insert( p );
	}
}


//!  Area Layout Interface
/*virtual*/ void Layer::place(){
    list<Area*>::iterator a_it = areas.begin();
    while( a_it != areas.end() ){
        (*a_it)->doSize( rect.getSize() );
        a_it++;
    }

    a_it = areas.begin();
    while( a_it != areas.end() ){
        (*a_it)->doPlace( rect );
        a_it++;
    }

	list<Projection*>::iterator p_it = projs.begin();
	while( p_it != projs.end() ){
		(*p_it)->doSize ( rect.getSize() );
		(*p_it)->doPlace( rect );
		p_it++;
    }
}


//!  Draw area recursively - draw all areas in layer
/*virtual*/ void Layer::drawLayer(){
	if( view == NULL ){
        dmsg( M_WM, "drawLayer() NULL view" );
		return;
	}else{
        dmsg( 
			M_WM, 
			"layer %s drawLayer() size %f x %f", 
			getName().c_str(),
			size[0],
			size[1]
		);
	}
	drawSelf();

	view->begin2d();
	list<Area*>::iterator a_it = areas.begin();
    while( a_it != areas.end() ){
        Area *a = *a_it;
        const char *name = a->getName().c_str();
        dmsg( M_WM, "drawLayer() calling draw for area %s", name );
 		a->draw();
		a_it++;
	}
	view->end2d();
}


};  //  namespace PhysicalComponents
};  //  namespace Teddy

