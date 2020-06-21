
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

	$Id:  $
*/


#include "Teddy/Application/BaseSimulationTimer.h"
#include "Teddy/Graphics/Font.h"
#include "Teddy/Graphics/View.h"
#include "Teddy/Imports/LWSceneParser.h"
#include "Teddy/PhysicalComponents/GradientFill.h"
#include "Teddy/PhysicalComponents/Projection.h"
#include "Teddy/PhysicalComponents/Style.h"
#include "Teddy/Scenes/Camera.h"
#include "Teddy/Scenes/Scene.h"
#include "Teddy/SysSupport/StdIO.h"
#include "Teddy/SysSupport/Messages.h"

#include "ObjectManager.h"
#include "SimpleText.h"
using namespace Teddy::Graphics;
using namespace Teddy::PhysicalComponents;
using namespace Teddy::Scenes;
using namespace Teddy::SysSupport;


//!  Constructor
SimpleText::SimpleText( Root *root )
:
Node(root),
Area("")
{

    offset_self_size_relative = Vector2( -0.5f, 0.0f );
    offset_free_size_relative = Vector2(  0.5f, 0.0f );
    offset_pixels             = Vector2(  0.0f, 32.0f );
    //fill_base_pixels[0]       = style->button_font->getWidth () + style->padding[0]*2;;;
    fill_base_pixels[1]       = style->button_font->getHeight() + style->padding[1]*2;;
    fill_base_pixels[0] =
        40 * style->button_font->getWidth() +
        style->padding[0]*2;
    drawing_ordering = post_self;

/*	this->insert(
 new Teddy::PhysicalComponents::GradientFill(
 Color( 0.3f, 0.5f, 0.0f, 0.4f ),
 Color( 0.3f, 0.5f, 0.0f, 0.4f ),
 Color( 0.1f, 0.4f, 0.0f, 0.2f ),
 Color( 0.1f, 0.4f, 0.0f, 0.2f )
 )
 );
 */

}


//!  Draw
/*virtual*/ void SimpleText::drawSelf(){
    char  m[200];
    View *view = getView();  //  getView() is member of Area, super class of SimpleText

	float          time = 0.0f;
	LWSceneParser *p    = getObjectManager()->getLWSceneParser();
	if( p != NULL ){
		time = p->getTime();
	}
		
	sprintf(
		m,
		"Teddy %5.2f fps %d obj %d m. skip %8.2fs",
        view->getFps(),
        getObjectManager()->getScene()->getDrawCount(),
        Projection::material_skip_count,
		time
    );

    view->enable( View::BLEND      );
    view->enable( View::TEXTURE_2D );
    view->setBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    style->hilight_color.glApply();
    drawString( style->padding, m, style->button_font );
    view->disable( View::BLEND      );
    view->disable( View::TEXTURE_2D );
    view->disable( View::TEXTURE_2D );
}

