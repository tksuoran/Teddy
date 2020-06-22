
/*
	TEDDY - General graphics application library
	Copyright (C) 1999, 2000, 2001	Timo Suoranta
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


#include "Teddy/SysSupport/StdSDL.h"
#include "Teddy/Application/BaseSimulationTimer.h"
#include "Teddy/Graphics/Font.h"
#include "Teddy/Graphics/View.h"
#include "Teddy/PhysicalComponents/GradientFill.h"
#include "Teddy/PhysicalComponents/Projection.h"
#include "Teddy/PhysicalComponents/Style.h"
#include "Teddy/Scenes/Camera.h"
#include "Teddy/Scenes/Scene.h"

#include "ObjectManager.h"
#include "SimpleText.h"
using namespace Teddy::Graphics;
using namespace Teddy::PhysicalComponents;
using namespace Teddy::Scenes;


//!  Constructor
SimpleText::SimpleText( Root *root )
:
Node(root),
Area("")
{

    offset_self_size_relative = Vector2( -0.5f, 0.0f );
    offset_free_size_relative = Vector2(  0.5f, 0.0f );
    offset_pixels             = Vector2(  0.0f, 32.0f );
    fill_base_pixels[0]       = style->button_font->getWidth () + style->padding[0]*2;;;
    fill_base_pixels[1]       = style->button_font->getHeight() + style->padding[1]*2;;
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

    sprintf(
            m,
            "Teddy %5.2f fps %d obj %d m. skip",
            view->getFps(),
            getObjectManager()->getScene()->getDrawCount(),
            Projection::material_skip_count
            //getObjectManager()->getCamera()->getDebugDouble()
           );
    fill_base_pixels[0]       =
        strlen(m) * style->button_font->getWidth() +
        //		62 * style->button_font->getWidth() +
        style->padding[0]*2;
    /*	constraint.local_y_fill_pixels =
     (6 + 8 * getObjectManager()->getCamera()->debug_index) * style->button_font->getWidth() +
     style->inner_y_space_pixels*2;-*/

    //place();
    view->enable( View::BLEND );
    view->enable( View::TEXTURE_2D );
    view->setBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    style->hilight_color.glApply();
    drawString( style->padding, m, style->button_font );
    view->disable( View::BLEND );
    view->disable( View::TEXTURE_2D );
    //glRasterPos2i( 200 , 200 );

#if 0
    Camera *c =	getObjectManager()->getCamera();
    for( int i=0; i<c->debug_index; i++ ){
        Matrix dm = c->debug_matrix[i];
        int row;
        for( row=0; row<4; row++ ){
            sprintf(
                    m,
                    " % 9.2f % 9.2f % 9.2f % 9.2f",
                    dm.m[0][row],
                    dm.m[1][row],
                    dm.m[2][row],
                    dm.m[3][row]
            );
            drawString(
                       style->button_font,
                       m,
                       style->inner_x_space_pixels,
                       style->glyph_y_pixels * (row+2+i*7)
            );
        }
        char  m2[2000];
        sprintf(
                m2,
                " % 9.2lf % 9.2lf % 9.2lf % 9.2lf % 9.2lf % 9.2lf",
                c->debug_double[i][0],
                c->debug_double[i][1],
                c->debug_double[i][2],
                c->debug_double[i][3],
                c->debug_double[i][4],
                c->debug_double[i][5]
        );
        drawString(
                   style->button_font,
                   m2,
                   style->inner_x_space_pixels,
                   style->glyph_y_pixels * (6+i*7)
        );
    }

#endif

    view->disable( View::TEXTURE_2D );
}

