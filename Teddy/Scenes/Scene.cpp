
/*
	TEDDY - General graphics application library
	Copyright (C) 1999-2002  Timo Suoranta
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
	
	$Id: Scene.cpp,v 1.7 2002/02/16 12:41:39 tksuoran Exp $
*/


#include "Teddy/Graphics/View.h"
#include "Teddy/Materials/Light.h"
#include "Teddy/Materials/Material.h"
#include "Teddy/Models/Geometry.h"
#include "Teddy/PhysicalComponents/Projection.h"
#include "Teddy/Scenes/Camera.h"
#include "Teddy/Scenes/PostElement.h"
#include "Teddy/Scenes/Scene.h"
#include "Teddy/SysSupport/Messages.h"
#include "Teddy/SysSupport/StdMaths.h"
#include "Teddy/SysSupport/StdIO.h"
#include "Teddy/SysSupport/StdAlgo.h"
#ifndef SWIG
#include <cstdlib>
#endif
using namespace Teddy::Graphics;
using namespace Teddy::Materials;
using namespace Teddy::Models;
using namespace Teddy::PhysicalComponents;
using namespace std;


namespace Teddy  {
namespace Scenes {


//!  Constructor
Scene::Scene( const std::string &name )
:
	Named( name )
{
	cull_count      = 0;
	draw_count      = 0;
	last_draw_count = 0;
	ambient_color   = Color::GRAY_25;
}


int Scene::getDrawCount(){
	return last_draw_count;
}


//!  Add new Light to Scene
void Scene::add( Light *l ){
	lights.push_back( l );
}


//!  Add new PostElement to Scene
void Scene::add( PostElement *p ){
	post_elements.push_back( p );
}


//!  Add new ModelInstance to Scene
void Scene::add( Model *m ){
	models.push_back( m );
}


void Scene::remove( Light *l ){
	lights.remove( l );
}

void Scene::remove( PostElement *p ){
	post_elements.remove( p );
}

void Scene::remove( Model *m ){
	models.remove( m );
}


/*!
	Update Modelss in scene
	This is required when any Material control property of Projection is changed.
*/
void Scene::update( Projection *p ){
//	Disabled; not needed in immediate drawing
/*	list<ModelInstance*>::iterator i_it = instances.begin();
	while( i_it != instances.end() ){
		(*i_it)->update( p );
		i_it++;
	}*/
}


//!  Return instance list
list<Model*> &Scene::getModels(){
	return models;
}

list<Light*> &Scene::getLights(){
	return lights;
}


void Scene::setAmbientColor( Teddy::Graphics::Color ambient_color ){
	this->ambient_color = ambient_color;
}


//!  Draw scene to OpenGL viewport
void Scene::draw( Camera *c, Projection *p ){
	View                         *view   = p->getView();
	list<Light      *>::iterator  l_it;
	list<PostElement*>::iterator  p_it;
	list<Model      *>::iterator  m_it;
	cull_count = 0;

	//	Apply lights 
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, ambient_color.rgba );
	switch( p->getMaster()->getLighting() ){

	case 1/*RENDER_LIGHTING_COLOR*/:
		//	No lights appleid
		break;

	case 2/*RENDER_LIGHTING_CUSTOM*/:
		//	FIX Not yet implemented
		break;

	case 3/*RENDER_LIGHTING_PRIMARY_LIGHT_ONLY*/:
		//	Only OpenGL primary light is applied
		l_it = lights.begin();
		if( l_it != lights.end() ){
			(*l_it)->applyLight( p );
		}
		break;

	case 5/*RENDER_LIGHTING_FULL*/:
		//	FIX Not yet implemented; fall through
	case 4/*RENDER_LIGHTING_SIMPLE*/:
		//	Render all enabled OpenGL lights
		l_it = lights.begin();
		while( l_it != lights.end() ){
			(*l_it)->applyLight( p );
			l_it++;
		}
		break;


	default:
		//  Unknown lighting mode
		break;
	}

	//  Render objects
	m_it = models.begin();
	while( m_it != models.end() ){
		Model *m = *m_it;
		if( m != c ){
			m->draw( p );
		}
		m_it++;
	}
	last_draw_count = Geometry::draw_count;

    drawPostElements( c, p );
}


int Scene::getCullCount(){
	return cull_count;
}


//!  Draw scene to OpenGL viewport
void Scene::drawPostElements( Camera *c, Projection *p ){
	View                         *view   = p->getView();
	list<PostElement*>::iterator  p_it;

	//  Render PostElements
	c->doProjection     ( p, true );
//	c->doCamera         ( p, false );
	view->enable        ( View::BLEND );
	view->setShadeModel ( GL_SMOOTH );
	view->setPolygonMode( GL_FILL );
	view->setBlendFunc  ( GL_ONE, GL_ONE );
	view->disable       ( View::LIGHTING      );
	view->disable       ( View::DEPTH_TEST     );
	view->disable       ( View::CULL_FACE      );
	view->disable       ( View::POLYGON_OFFSET );

//	view->setProjectionMatrix( Matrix::Identity );
	view->setModelViewMatrix ( Matrix::IDENTITY );

	p_it = post_elements.begin();
	while( p_it != post_elements.end() ){
		(*p_it)->draw( p );
		p_it++;
	}
}


//!  Return Modele close to given view coordinates  3
Model  *Scene::pick( Camera *c, Projection *p ){
	Model                  *m_lookup[1024];
	Model                  *pick = NULL;
	View                   *view;
	GLuint                  hits[1024];
	list<Model*>::iterator  m_it;

	glSelectBuffer( 1024, hits );

	glRenderMode( GL_SELECT );
	view = p->getView();	
	p->pickState( true );
//	view->setPolygonMode( GL_FILL );
//	view->setPolygonMode( GL_FILL );
//	view->enable( CULL_FACE );
	glInitNames();
	glPushName( 0 );

	int name        = 1;
	int pick_drawn	= 0;
	int pick_culled = 0;
	int pick_hidden = 0;

	m_it = models.begin();
	while( m_it != models.end() ){
		Model *m = (*m_it);
		m_lookup[name] = m;
		glLoadName( name++ );
//		real r2 = mi->distanceSqr( Vector::NullVector );
//		if( r2 < mi->getClipRange() ){
		if( m != c ){
/*			if( c->cull( mi ) ){
				pick_culled++;
			}else{
				mi->draw( p );
				pick_drawn++;
			}*/
			m->draw( p );
			pick_drawn++;
		}else{
			pick_hidden++;
		}

		m_it++;
	}
	GLuint  num_hits = glRenderMode( GL_RENDER );
	GLuint *ptr      = hits;
	GLuint  names;
	GLuint  z_min;
	GLuint  z_max;
	GLuint  hit_name;
	GLuint  nearest = 0xffffffff;
	//printf( "Pick: drawn %d culled %d hidden %d hits %d\n", pick_drawn, pick_culled, pick_hidden, num_hits );
	for( GLuint i=0; i<num_hits; i++ ){
		names = *ptr++;
		z_min = *ptr++;
		z_max = *ptr++;
		for( GLuint j=0; j<names; j++ ){
			hit_name = *ptr++;
			if( z_min<nearest ){
				nearest = z_min;
				pick	= m_lookup[hit_name];
			}
		}		
	}
	p->pickState( false );
/*	if( pick != NULL ){
		printf( "Picked %s\n", pick->getName().c_str() );
	}else{
		printf( "NULL pick\n" );
	}*/
	return pick;
}


//  FIX works because/even though model clip radius is not correct
float Scene::getMaxObSize(){
	float                  max_ob_size = 0.0f;
	list<Model*>::iterator m_it        = models.begin();
	while( m_it != models.end() ){
		Model *model = *m_it;
		max_ob_size = MAX(
			max_ob_size,
			model->getClipRadius() 
		);
		m_it++;
	}
	return max_ob_size;
}


//  Approximation, does not consider children
float Scene::getMaxObDistance(){
	float                  max_ob_dist = 0.0f;
	list<Model*>::iterator m_it        = models.begin();
	while( m_it != models.end() ){
		Model        *model   = *m_it;
		DoubleVector  ob_pos  = model->getPosition();
		float         ob_dist = (float)ob_pos.magnitude();
		max_ob_dist = MAX(
			max_ob_dist,
			ob_dist 
		);
		m_it++;
	}
	return max_ob_dist;
}


};  //  namespace Scenes
};  //  namespace Teddy


