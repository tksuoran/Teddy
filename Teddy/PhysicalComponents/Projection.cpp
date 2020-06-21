
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

	$Id: Projection.cpp,v 1.6 2002/03/12 10:46:07 tksuoran Exp $
*/


#include "Teddy/TeddyConfig.h"
#include "Teddy/Graphics/Texture.h"
#include "Teddy/Graphics/View.h"
#include "Teddy/Materials/Material.h"
#include "Teddy/PhysicalComponents/EventListener.h"
#include "Teddy/PhysicalComponents/Projection.h"
#include "Teddy/Scenes/Camera.h"
#include "Teddy/SysSupport/Messages.h"
#include "Teddy/SysSupport/StdIO.h"
#ifndef SWIG
#include "cassert"
#endif
using namespace Teddy::Graphics;
using namespace Teddy::Scenes;


namespace Teddy              {
namespace PhysicalComponents {


int Projection::material_skip_count = 0;


//! Constructor
Projection::Projection( const std::string &name, Camera *camera )
:
Area  ( name   ),
camera( camera )
{
    options           = Area::CLEAR | Area::CLIP_RENDERING;
	drawing_ordering  = separate_self;  //  Separate drawSelf() invocation
	active_material   = NULL;
	active_texture    = NULL;
    clear_color       = Color::BLACK;
    render_pass_count = 0;
	master_material   = new Material( "Projection master material", Material::RENDER_OPTION_ALL_M );
	master_material->setMode    ( Material::RENDER_MODE_FILL_OUTLINE );
	master_material->setLighting( Material::RENDER_LIGHTING_SIMPLE );
	master_material->setAmbient ( Color::GRAY_25 );
	master_material->setDiffuse ( Color::GRAY_50 );
	master_material->setSpecular( Color::GRAY_25 );
	master_material->setBorder  ( Color::BLACK   );
    setSelect( Material::RENDER_OPTION_ALL_M );

    fill_free_size_relative = Vector2( 1.0f, 1.0f );
}


//!  Destructor
/*virtual*/ Projection::~Projection(){
}


//!  Area Input Interface - Get Hit Area, NULL if none
/*virtual*/ Area *Projection::getHit( const Vector2 &pos ){
	dmsg( M_WM, "Try Projection Area" );

	if( rect.hit(pos) ){
		dmsg( M_WM, "Hit Projection Area" );
		return this;
	}

/*	wm_debug_msg( "Begin Layer Children" );
	list<Area*>::iterator a_it = areas.begin();
	while( a_it != areas.end() ){
		Area *hit = (*a_it)->getHit( x, y );
		if( hit != NULL ){
			return hit;
		}
		a_it++;
	}
	wm_debug_msg( "End Layer Children" );*/

	return NULL;
}


//!  Apply Material to Projection.
void Projection::doMaterial( Material *m ){
	render_pass = 0;

	if( render_pass_count==1 ){
		if( (active_material==m) || (m==NULL) ){
			//dmsg( M_MAT, "already active material %s reset", m->getName().c_str() );
			material_skip_count++;
			return;
		}
	}

	render_pass_count = 1;

	if( isEnabled(Area::PICK) ){
		return;
	}

	if( m == NULL ){
		dmsg( M_MAT, "NULL material" );
	}

	active_material = m;

	//dmsg( M_MAT, "Activating material %s", m->getName().c_str() );

	materialReapplyActive();
}


//!  Apply material
void Projection::materialReapplyActive(){
	Material *m = active_material;

	Uint8 l = MIN( m->getLighting(), master_material->getLighting() );
	if( l >= Material::RENDER_LIGHTING_PRIMARY_LIGHT_ONLY ){
		view->enable( View::LIGHTING );
	}else{
		view->disable( View::LIGHTING );
	}

	//	Apply rendering options
	Uint32 mask_select = m->getOptions() & render_options_selection_mask.getOptions();
	Uint32 mask_enable = mask_select & master_material->getOptions();
	for( int i=0; i<32; i++ ){
//		bool no_master = (render_options_selection_mask.getOptions() >> i ) & 1 == 1;
		bool select    = (mask_select>>i) & 1 == 1;  // true if select material, false if select projection
		bool enable    = (mask_enable>>i) & 1 == 1;  // true if enabled, false if disabled
		Material *selected_material = select ? m : master_material;

		if( Material::getFeature(i) != 0 ){
			view->setState( Material::getFeature(i), enable );
		}else if( render_options_selection_mask.isDisabled(Material::RENDER_OPTION_MASTER_LIGHTING_ONLY_M) ){
			switch( i ){
			case 16l/*Material::RENDER_OPTION_AMBIENT*/:   selected_material->applyAmbient  (l); break;
			case 17l/*Material::RENDER_OPTION_DIFFUSE*/:   selected_material->applyDiffuse  (l); break;
			case 18l/*Material::RENDER_OPTION_SPECULAR*/:  selected_material->applySpecular (l); break;
			case 19l/*Material::RENDER_OPTION_EMISSION*/:  selected_material->applyEmission (l); break;
			case 20l/*Material::RENDER_OPTION_SHINYNESS*/: selected_material->applyShinyness(l); break;
//			case Material::RENDER_OPTION_REMOVE_HIDDEN:  if( select ){ applyRemoveHidden (); } break;
//			case Material::RENDER_OPTION_FRUSTUM_CULL:   if( select ){ applyFrustumCull  (); } break;
//			case Material::RENDER_OPTION_SORT_INSTANCES: if( select ){ applySortInstances(); } break;
//			case Material::RENDER_OPTION_SORT_ELEMENTS:  if( select ){ applySortElements (); } break;
			default:
				break;
			}
		}
	}  //  for all features

	unsigned long master_mode = master_material->getMode();

    if( master_mode == Material::RENDER_MODE_FILL_OUTLINE ){
        //printf( "materialReapplyActive() render_pass_count = 2\n" );
		render_pass_count = 2;
    }else{
        if( render_pass_count != 1 ){
            dmsg( M_MAT, "materialReapplyActive() render_pass_count = 1\n" );
            render_pass_count = 1;
        }

	}
}


//!  Apply single material application pass
bool Projection::materialPass(){
	render_pass++;

	if( render_pass <= render_pass_count ){

		if( isEnabled(Area::PICK) ){
			return true;
		}

		if( active_material == NULL ){
			false;
		}

		float    polygon_offset = 2;
		Texture *t              = NULL;

		if( active_material->getPolygonOffset() == 1 ){
			polygon_offset -= 1;
		}

/*&& (t != active_texture)*/
		
		switch( render_pass ){
		case 1: {
			//	Apply polygon rendering mode
			switch(  MIN( active_material->getMode(), master_material->getMode() )  ){
			case 1/*Material::RENDER_MODE_POINT*/:        view->setPolygonMode( GL_POINT ); break;
			case 2/*Material::RENDER_MODE_LINE*/:         view->setPolygonMode( GL_LINE  ); break;
			case 3/*Material::RENDER_MODE_FILL*/:         view->setPolygonMode( GL_FILL  ); break;
			case 4/*Material::RENDER_MODE_FILL_OUTLINE*/: view->setPolygonMode( GL_FILL  ); break;
			default: break;
			}

			t = active_material->getTexture();
			if( 
				(t!=NULL)            && 
				(t->isGood()==true)  && 
				master_material->isEnabled(Material::RENDER_OPTION_TEXTURE_2D_M) 
			){
				active_texture = t;
				view->setTexture( t );
				view->enable( View::TEXTURE_2D );
			}else{
				view->disable( View::TEXTURE_2D );
			}

		} break;

		case 2: {
			if( master_material->getMode() == Material::RENDER_MODE_FILL_OUTLINE ){
				polygon_offset += -1;
			}

			Uint32 mask_select = *active_material & render_options_selection_mask;

			bool select = (mask_select>>Material::RENDER_OPTION_BORDER) & 1 == 1;  // true if select material, false if select projection

			//	Borders are rendered without lighting.
			view->disable       ( View::POLYGON_OFFSET );
			view->disable       ( View::LIGHTING       );
			view->disable       ( View::TEXTURE_2D     );
			view->setPolygonMode( GL_LINE        );

			//	..using either material or projection color setting
			if( select ){
				active_material->applyBorder( Material::RENDER_LIGHTING_COLOR );
			}else{
				master_material->applyBorder( Material::RENDER_LIGHTING_COLOR );
			}

		} break;

		default:
			break;
		}

		if( polygon_offset != 0 ){
			view->enable( View::POLYGON_OFFSET );
			glPolygonOffset( 2, polygon_offset );
		}else{
			view->disable( View::POLYGON_OFFSET );
		}

		return true;
	}else{
		return false;
	}
}


//!  Drawing code
/*virtual*/ void Projection::drawSelf(){
	glViewport( (int)rect.min[0], (int)(view->getSize()[1]-rect.max[1]), (int)size[0], (int)size[1] );

	if( isEnabled(Area::CLIP_RENDERING) ){
#		if !defined( USE_TINY_GL )
		glScissor( (int)rect.min[0], (int)(view->getSize()[1]-rect.max[1]), (int)size[0], (int)size[1] );
		view->enable( View::SCISSOR_TEST );
#		endif
	}

#	if !defined( USE_TINY_GL )
	if( isEnabled(Area::CLEAR) ){
		glClearDepth( 1 );
		glClearColor( clear_color.rgba[0], clear_color.rgba[1], clear_color.rgba[2], clear_color.rgba[3] );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//		glClear( GL_DEPTH_BUFFER_BIT );

	}
#	endif

	//  Set projection global settings

	if( render_options_selection_mask.isEnabled(Material::RENDER_OPTION_MASTER_LIGHTING_ONLY_M) ){
		Uint8 l = master_material->getLighting();
		if( render_options_selection_mask.isDisabled(Material::RENDER_OPTION_AMBIENT_M  ) ){ master_material->applyAmbient  (l); }
		if( render_options_selection_mask.isDisabled(Material::RENDER_OPTION_DIFFUSE_M  ) ){ master_material->applyDiffuse  (l); }
		if( render_options_selection_mask.isDisabled(Material::RENDER_OPTION_SPECULAR_M ) ){ master_material->applySpecular (l); }
		if( render_options_selection_mask.isDisabled(Material::RENDER_OPTION_EMISSION_M ) ){ master_material->applyEmission (l); }
		if( render_options_selection_mask.isDisabled(Material::RENDER_OPTION_SHINYNESS_M) ){ master_material->applyShinyness(l); }
	}

	//	Make sure first material is always applied
	active_material = NULL;
	view->disable( View::TEXTURE_2D );
	material_skip_count = 0;
	camera->projectScene( this );

#if !defined( USE_TINY_GL )
	view->disable( View::SCISSOR_TEST );
	glScissor( 0, 0, view->getSize()[0], view->getSize()[1] );
#endif
}


//!  Camera get accessor
Camera *Projection::getCamera(){
	return this->camera;
}


//!  Camera set accessor
void Projection::setCamera( Camera *c ){
	this->camera = c;
}


//!  \todo doc
Options &Projection::getSelect(){
	return render_options_selection_mask;
}


//!  \todo doc
void Projection::setSelect( unsigned long select ){
	render_options_selection_mask = select;
}


//!  \todo doc
void Projection::enableSelect( unsigned long select ){
	render_options_selection_mask |= select;
}


//!  \todo doc
void Projection::disableSelect( unsigned long select ){
	render_options_selection_mask &= ~select;
}


//!  Enable and or disable pick mode
void Projection::pickState( const bool state ){
	if( state == true ){
		enable ( Area::PICK );
	}else{
		disable( Area::PICK );
	}

	active_material = NULL;
	active_texture  = NULL;
}


//!  \todo doc
Material *Projection::getMaster(){
	return master_material;
}


//!  \todo doc
void Projection::setClearColor( Color c ){
	this->clear_color = c;
}


//!  \todo doc
Color Projection::getClearColor(){
	return this->clear_color;
}


//!  \todo doc
void Projection::setProjectionMatrix(){
	view->setProjectionMatrix();
}


//!  \todo doc
void Projection::setProjectionMatrix( Matrix &m ){
	view->setProjectionMatrix( m );
}


//!  \todo doc
void Projection::setModelViewMatrix(){
	view->setModelViewMatrix();
}


//!  \todo doc
void Projection::setModelViewMatrix( Matrix &m ){
	view->setModelViewMatrix( m );
}


//!  \todo doc
Model *Projection::pick( const Vector2 &pos ){
	Vector2 my_pos( pos );
	my_pos[1] = this->view->getSize()[1] - pos[1];
	return camera->pick( this, my_pos );
}


float Projection::getRatio(){
    return size[0] / size[1];
}


};  //  namespace PhysicalComponents
};  //  namespace Teddy

