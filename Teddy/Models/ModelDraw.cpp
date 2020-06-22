
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


#include "Teddy/Materials/Material.h"
#include "Teddy/Models/Model.h"
#include "Teddy/Models/Geometry.h"
#include "Teddy/PhysicalComponents/Projection.h"
#include "Teddy/Scenes/Camera.h"
#include "Teddy/SysSupport/StdMaths.h"
#include "Teddy/SysSupport/Messages.h"
using namespace Teddy::Graphics;
using namespace Teddy::Materials;
using namespace Teddy::Scenes;
using namespace Teddy::SysSupport;


namespace Teddy  {
namespace Models {


//!  Apply Model material
void Model::doMaterial( Projection *p, Model *parent ){
	if( material == NULL ){
		if( parent != NULL ){
			parent->doMaterial( p );
		}else{
			p->doMaterial( &Material::RED );
		}
	}else{
		p->doMaterial( material );
	}
}


//!  Drawing the instance
/*virtual*/ void Model::draw( Projection *p, Model *parent ){
	Camera *c = p->getCamera();

	if( isEnabled(OPT_VISIBLE) == true ){
		bool setup = false;

        //  Draw self
		c->doObjectMatrix( p, getLocalToWorldMatrix() );
		if( c->cull(*this) == false ){
			if( geometry != NULL ){
				doMaterial( p, parent );
				setup = true;

//				dmsg( M_INIT, "Drawing %s", getName().c_str() );
				while( p->materialPass() ){
					geometry->draw( p );
				}
			}else{
//				dmsg( M_INIT, "Not drawing %s, has no geometry", getName().c_str() );
			}
		}else{
//			dmsg( M_INIT, "Not drawing %s, culled", getName().c_str() );
		}

        //  Draw children
		if( children.size() > 0 ){
			if( setup == false ){
				doMaterial( p, parent );
			}
			c->pushObjectMatrix();
			list<Model*>::iterator m_it = children.begin();
			while( m_it != children.end() ){
				(*m_it)->draw( p, material != NULL ? this : parent );
				m_it++;
			}
			c->popObjectMatrix();
		}
	}else{
//		dmsg( M_INIT, "Not drawing %s, not visible", getName().c_str() );
	}
}


};	//	namespace Models
};  //  namespace Teddy

