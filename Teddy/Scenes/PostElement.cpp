
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
	
	$Id: PostElement.cpp,v 1.5 2002/01/14 09:14:15 tksuoran Exp $
*/


#include "Teddy/TeddyConfig.h"
#include "Teddy/Scenes/PostElement.h"
#include "Teddy/Graphics/View.h"
#include "Teddy/Graphics/ImageFileTexture.h"
#include "Teddy/Maths/Vector2.h"
#include "Teddy/Maths/Vector4.h"
#include "Teddy/PhysicalComponents/Projection.h"
#include "Teddy/Scenes/Camera.h"
#include "Teddy/SysSupport/StdList.h"
#include "Teddy/SysSupport/StdIO.h"
using namespace Teddy::Graphics;
using namespace Teddy::Materials;
using namespace Teddy::Maths;
using namespace Teddy::PhysicalComponents;
using namespace Teddy::Scenes;


namespace Teddy  {
namespace Scenes {


PostElement::PostElement( char *filename ){
	txt = new ImageFileTexture( filename );
}


/*virtual*/ PostElement::~PostElement(){
}


void PostElement::insert( Ellipsoid *e ){
	ellipsoids.push_back( e );
}


/*virtual*/ void PostElement::draw( Projection *p ){
#if 0
    Camera *camera = p->getCamera();
	View   *view   = p->getView();
    double  n      = camera->getNear();

	//view->enable( DEPTH_TEST );
	if( txt != NULL ){
		txt->apply();
        view->enable( TEXTURE_2D );
	}else{
        view->disable( TEXTURE_2D );
	}
    view->disable     ( DEPTH_TEST );
    view->enable      ( BLEND );
    //glDepthMask     ( GL_FALSE );
	view->setBlendFunc( GL_ONE, GL_ONE );
    view->setModelViewMatrix();
	p->color( C_WHITE );

	list<Ellipsoid*>::iterator e_it = ellipsoids.begin();
	while( e_it != ellipsoids.end() ){
		Ellipsoid *e   = *e_it;
        Matrix     cam = camera->getWorldToLocalMatrix();

        Vector viewLocation(  cam * Vector4(e->location,1.0)  );
        Vector viewForward (  cam * Vector4(e->forward, 0.0)  );
        Vector center      ( viewLocation );
        Vector top         ( center + viewForward * e->front );
        Vector bottom      ( center - viewForward * e->rear  );

		float z = min( top[2], bottom[2] ) - e->radius;
        //  This test is not right.. The whole z might not be right?
		if( z < n ){
            top    *= (z / top   [2]);
            center *= (z / center[2]);
            bottom *= (z / bottom[2]);

            Vector2 delta( top[0] - bottom[0], top[1] - bottom[1] );
            float offset = delta.magnitude();
			if( offset > 0 ){
                delta /= offset;
			}else{
				//delta.set( 0, 1 );
				delta[0] = 0;
				delta[1] = 0; //.set( 0, 1 );
			}

            Vector2 right( delta[1] * e->radius, -delta[0] * e->radius );
            Vector2 up   ( delta[0] * e->radius,  delta[1] * e->radius );

			p->beginQuadStrip();
			p->texture( 0.0f, 0.0f ); p->vertex( top   [0] - right[0] + up[0], top   [1] - right[1] + up[1], top   [2] );
			p->texture( 1.0f, 0.0f ); p->vertex( top   [0] + right[0] + up[0], top   [1] + right[1] + up[1], top   [2] );
			p->texture( 0.0f, 0.5f ); p->vertex( center[0] - right[0]        , center[1] - right[1]        , center[2] );
			p->texture( 1.0f, 0.5f ); p->vertex( center[0] + right[0]        , center[1] + right[1]        , center[2] );
			p->texture( 0.0f, 1.0f ); p->vertex( bottom[0] - right[0] - up[0], bottom[1] - right[1] - up[1], bottom[2] );
			p->texture( 1.0f, 1.0f ); p->vertex( bottom[0] + right[0] - up[0], bottom[1] + right[1] - up[1], bottom[2] );
			p->end();
		}
		e_it++;
	}
    //glDepthMask( GL_TRUE );
#endif
}


};  //  namespace Scenes
};  //  namespace Teddy  

