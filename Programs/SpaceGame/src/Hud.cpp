
/*
	TSGL - Teddy Space Game Library
	Copyright (C) 2002 Timo Suoranta
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


#include "Teddy/TeddyConfig.h"
#include "Teddy/Behaviour/ModelAnimator.h"
#include "Teddy/Graphics/View.h"
#include "Teddy/Graphics/ImageFileTexture.h"
#include "Teddy/Maths/Vector.h"
#include "Teddy/Models/Model.h"
#include "Teddy/PhysicalComponents/GradientFill.h"
#include "Teddy/PhysicalComponents/Style.h"
#include "Teddy/Scenes/Camera.h"
#include "Teddy/Scenes/Scene.h"
#include "Teddy/SysSupport/StdIO.h"

#include "Hud.h"
#include "Root.h"
#include "ObjectManager.h"
#include "PlayerController.h"
#include "RoamInstance.h"
#include "RoamSphere.h"
#include "ShipType.h"
using namespace Teddy::Application;
using namespace Teddy::Behaviour;
using namespace Teddy::Graphics;
using namespace Teddy::Models;
using namespace Teddy::PhysicalComponents;
using namespace Teddy::Scenes;


//!  Constructor
Hud::Hud( Root *root )
:
Node(root ),
Area("Hud")
{
	this->root    = root;
	target_matrix = NULL;

    fill_free_size_relative   = Vector2(   1.0f,  0.0f );
    offset_pixels             = Vector2(  10.0f, 24.0f );

#if defined( _DEBUG )
    fill_base_pixels          = Vector2( -20.0f,  95.0f );
#else
    fill_base_pixels          = Vector2( -20.0f,  50.0f );
#endif

#if !defined( USE_TINY_GL )
	this->insert(
		new Teddy::PhysicalComponents::GradientFill(  
			Color( 0.3f, 0.5f, 0.0f, 0.8f ),
			Color( 0.3f, 0.5f, 0.0f, 0.8f ),
			Color( 0.1f, 0.4f, 0.0f, 0.5f ),
			Color( 0.1f, 0.4f, 0.0f, 0.5f )
		)
	);

//	WindowFrame *f1 = new WindowFrame( "Heads Up Display" );
//	this->insert( f1 );
		
#endif

	drawing_ordering = post_self;
}


//!  Set HUD target matrix
void Hud::setTargetMatrix( Matrix *target ){
	this->target_matrix = target;
}


extern double speed;


//!  Drawing code - FIX ugly code...
void Hud::drawSelf(){
	char            hud[100];
	const char     *name;
	char           *unit;
	ShipController *controller = getObjectManager()->getPlayerController();
	ModelAnimator  *animator   = controller->getAnimator();
	Model          *model      = animator  ->getModel   ();
	Model          *target     = controller->getTarget  ();
	float           dst        = 0;
	float           distance   = 0;
	double          radius     = 0;
	double          angle      = 0;
	double          kal_h      = 0;

	view->enable      ( View::BLEND );  
	view->enable      ( View::TEXTURE_2D );
	view->setBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	if( target != NULL ){
		name     = target->getName().c_str();
		distance = model->distanceTo( *target );
		dst      = distance;
		unit     = "m";
		if( fabs(distance)>1000.0f ){
			distance *= 0.001f;
			unit      = "km";
		}
		if( fabs(distance)>1000.0f ){
			distance *= 0.001f;
			unit      = "tkm";
		}
		if( fabs(distance)>1000.0f ){
			distance *= 0.001f;
			unit      = "Mkm";
		}
	}else{
		name = "-";
		unit = "";
	}		 

	float alpha = 0.9f;

#if 0
	for( int i=0; i<10; i++ ){
		average_priority_class[i] = alpha * average_priority_class[i] + (1-alpha) * (float)(priority_class[i]);
	}
#endif
	color( 0.5f, 1.0f, 0.5f, 1.0f );

	sprintf(
		hud,
		"Teddy SpaceGame %d.%d % 6.1f fps % 6.1f ms Alt: % 6.1f Target: %s %.3f %s",
		0,
		0,
		view->getFps(),
		view->getLastFrame(),
		0.0f, // roam_height,
		name,
		distance,
		unit
	);
	drawString( Vector2( 5.0f,8.0f), hud, style->small_font);

	float  speed      = animator->getSpeed() * 100.0f;
	char  *speed_unit = "m/s";
	if( fabs(speed) < 0.1f ){
		speed      *= 100.0f;
		speed_unit  = "cm/s";
	}
	if( fabs(speed) < 0.1f ){
		speed      *= 10.0f;
		speed_unit  = "mm/s";
	}
	if( fabs(speed) > 1000.0f ){
		speed      *= 0.001f;
		speed_unit  = "km/s";
	}
	if( fabs(speed) > 1000.0f ){
		speed      *= 0.001f;
		speed_unit  = "tkm/s";
	}
	if( fabs(speed) > 1000.0f ){
		speed      *= 0.001f;
		speed_unit  = "Mkm/s";
	}

	color( 1.0f, 0.8f, 0.3f, 1.0f );
	sprintf(
		hud,
		"Pitch: % 2.2f Roll % 2.2f Speed %.3f %s",
		animator->getPitch() * 1000,
		animator->getRoll()  * 1000,
		speed,
		speed_unit
	);
	drawString( Vector2(5.0f, 17.0f), hud, style->small_font );

#ifdef _DEBUG
	int row;
//	drawString( style->small_font, "Debug Matrix:", 50, 50 );
	if( target_matrix != NULL ){
		for( row=0; row<4; row++ ){
			sprintf(
				hud,
				" % 7.2f % 7.2f % 7.2f % 7.2f",
				target_matrix->m[0][row],
				target_matrix->m[1][row],
				target_matrix->m[2][row],
				target_matrix->m[3][row]
			);
			drawString( Vector2(5.0f, 50.0f+10.0f*(float)row), hud, style->small_font );
		}
	}

#if 0

	color( 0.8f, 1.0f, 0.8f, 1.0f );
	sprintf( hud, "X: % 10.3f", (float)ship->getPosition().x ); drawString( style->small_font, hud, 280, 50 );
	sprintf( hud, "Y: % 10.3f", (float)ship->getPosition().y ); drawString( style->small_font, hud, 280, 60 );
	sprintf( hud, "Z: % 10.3f", (float)ship->getPosition().z ); drawString( style->small_font, hud, 280, 70 );

#else

	if( target != NULL ){
		Vector tpos   = target->getPosition();
		Vector cpos   = model->getPosition();
		Vector delta  = tpos - cpos;
		Vector cview  = model->getAttitude().getViewAxis();
		Vector cup    = model->getAttitude().getUpAxis();
		Vector cright = model->getAttitude().getRightAxis();
		delta .normalize();
		float  view_dp  = cview  | delta;
		float  up_dp    = cup    | delta;
		float  right_dp = cright | delta;
//		float  brk_dst  = controller->getBrakeDistance();

		color( 0.8f, 1.0f, 0.8f, 1.0f );
		sprintf( hud, "V: %- 6.2f", view_dp  ); drawString( Vector2(280.0f, 50.0f), hud, style->small_font );
		sprintf( hud, "U: %- 6.2f", up_dp    ); drawString( Vector2(280.0f, 60.0f), hud, style->small_font );
		sprintf( hud, "R: %- 6.2f", right_dp ); drawString( Vector2(280.0f, 70.0f), hud, style->small_font );
//		sprintf( hud, "U: %- 6.2f", ship->getPitchDistance() ); drawString( style->small_font, hud, 280, 60 );
//		sprintf( hud, "R: %- 6.2f", ship->getRollDistance () ); drawString( style->small_font, hud, 280, 70 );
//		sprintf( hud, "D: %- 6.2f", brk_dst  ); drawString( style->small_font, hud, 280, 80 );

	}
#endif

#if 0
	view->color( 0.6f, 0.8f, 1.0f, 1.0f );
	char c = (roam_update==true)?'T':'F';
	sprintf( hud, "Err: % 5.4f %c",   (float)roam_const*1000.0f, c ); drawString( style->small_font, hud, 400, 50 );
	sprintf( hud, "Tri: % 7d",        roam_triangle_count          ); drawString( style->small_font, hud, 400, 60 );
	sprintf( hud, "D/C: % 3d / % 3d", Scene::drawn, Scene::culled  ); drawString( style->small_font, hud, 400, 70 );
#endif

#endif

	view->disable( View::TEXTURE_2D );

	color( 0.0f, 0.0f, 0.0f, 70.5f );
	drawFillRect( 40-20-1, 30-2,  44+20+1, 40+1 );
	drawFillRect(100-20-1, 30-2, 104+20+1, 40+1 );
	drawFillRect(200   -1, 30-2, 400   +1, 40+1 );

	color( 1.0f, 1.0f, 0.0f, 0.95f );
	drawRect ( 40-20-2, 30-3,  44+20+2, 40+2 );
	drawRect (100-20-2, 30-3, 104+20+2, 40+2 );
	drawRect (200     , 30-3, 400     , 40+2 );

	color( 1.0f, 1.0f, 1.0f, 1.0f );
	beginLines();
	vertex(  42, 30 );
	vertex(  42, 40 );
	vertex( 102, 30 );
	vertex( 102, 40 );
	vertex( 300, 30 );
	vertex( 300, 40 );
	end();


	color( 0.25f, 1.0f, 0.25f, 0.75f );

	double max_roll  = controller->getRotateView ()->getMax  ();
	double max_pitch = controller->getRotateRight()->getValue();

	int roll  = (int)(animator->getRoll () * 20 / max_roll  + 0.5);
	int pitch = (int)(animator->getPitch() * 20 / max_pitch + 0.5);
	int spd   = (int)(animator->getSpeed() * 15 + 0.5);
	drawFillRect(  40 + roll , 30,  44 + roll , 40 );
	drawFillRect( 100 + pitch, 30, 104 + pitch, 40 );
	if( spd == 0 ){
		spd = 1;
	}
	if( spd > 0 ){
		color( 0.5f, 1.0f, 0.25f, 0.75f );
	}else{
		color( 1.0f, 0.5f, 0.25f, 0.75f );
	}
	drawFillRect( 300 , 30, 300 + spd, 40 );

}

