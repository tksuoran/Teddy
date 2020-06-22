
/*
	TSGL - Teddy Space Game Library
	Copyright (C) 2002 Timo Suoranta
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


#if defined(_MSC_VER)
#pragma warning(disable:4305)  //  from const double to float
#endif


#include "Teddy/Application/BaseSimulationTimer.h"
#include "Teddy/Behaviour/Control.h"
#include "Teddy/Models/Model.h"
#include "ModelCamera.h"
#include "ObjectManager.h"
#include "Ship.h"
using namespace Teddy::Behaviour;
using namespace Teddy::Models;
using namespace Teddy::PhysicalComponents;


/*!
	\brief ModelCamera constructor
	\param ship The ship to/from which the camera initially looks
	\param Scene The scene in which the camera looks
	\param cabin_mesh Cabin mesh to be drawn if inside the ship
*/
ModelCamera::ModelCamera( Model *target, Root *root )
:
Node  ( root ),
Camera( target->getName(),root->getObjectManager()->getScene() ),
target( target )
{
	unsigned long opts = Control::DAMPEN_MULTIPLY_M;
	c_heading  = new Control( M_2_PI/20000.0, M_2_PI/200.0, opts, 0.90 );
	c_pitch    = new Control( M_2_PI/20000.0, M_2_PI/200.0, opts, 0.90 );
	c_roll     = new Control( M_2_PI/20000.0, M_2_PI/200.0, opts, 0.90 );
	c_distance = new Control( 1/1000.0, 0.2, opts, 0.80 );
	front();
	distance = 0;
	getSimulationTimer()->add( this );
}


/*virtual*/ void ModelCamera::tick(){
	c_heading ->tick();
	c_pitch   ->tick();
	c_roll    ->tick();
	c_distance->tick();
	heading  += c_heading ->getValue();
	pitch    += c_pitch   ->getValue();
	roll     += c_roll    ->getValue();
	double d_val = c_distance->getValue();
	distance += d_val;
	distance *= (1.0 + d_val );
}


/*!  
	\param p Projection Area to which draw the scene

	If distance to target ship is zero, the target ship is not
	drawn
*/
/*virtual*/ void ModelCamera::projectScene( Projection *p ){
	setPosition ( target->getPosition() );
	copyAttitude( *target );
	Camera::heading( -heading  );
	Camera::pitch  (  pitch    );
	Camera::roll   (  roll     );
	Camera::foward ( -distance );

	unsigned long tmp_options;

	if( distance == 0 ){
		tmp_options = target->getOptions();
		target->disable( Model::OPT_VISIBLE );
		Camera::projectScene( p );
		target->setOptions( tmp_options );
	}else{
		Camera::projectScene( p );
	}
}


//!  Front view
void ModelCamera::front(){
	heading = 0;
	pitch   = 0;
	roll    = 0;
	//setTitle  ( "Front View" );
}


//!  Left view
void ModelCamera::left(){
	heading = M_HALF_PI;
	pitch   = 0;
	roll    = 0;
	//setTitle  ( "Left View" );
}


//!  Right view
void ModelCamera::right(){
	heading = -M_HALF_PI;
	pitch   = 0;
	roll    = 0;
	//setTitle  ( "Right View" );
}


//!  Rear view
void ModelCamera::rear(){
	heading = M_PI;
	pitch   = 0;
	roll    = 0;
	//setTitle  ( "Rear View" );
}


//!  Top view
void ModelCamera::top(){
	heading = 0;
	pitch   = M_HALF_PI;
	roll    = 0;
	//setTitle  ( "Top View" );
}


//!  Bottom view
void ModelCamera::bottom(){
	heading = 0;
	pitch   = -M_HALF_PI;
	roll    = 0;
	//setTitle  ( "Bottom View" );
}


Model *ModelCamera::getTarget(){
	return target;
}


Control *ModelCamera::getHeading      (){ return c_heading;  }
Control *ModelCamera::getPitch        (){ return c_pitch;    }
Control *ModelCamera::getRoll         (){ return c_roll;     }
Control *ModelCamera::getDistance     (){ return c_distance; }
double   ModelCamera::getDistanceValue(){ return distance; }


