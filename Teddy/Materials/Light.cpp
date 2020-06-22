
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


#include "Teddy/Graphics/Device.h"
#include "Teddy/Materials/Light.h"
#include "Teddy/Graphics/View.h"
#include "Teddy/PhysicalComponents/Projection.h"
#include "Teddy/SysSupport/Timer.h"
#include "Teddy/Scenes/Camera.h"
#include "Teddy/SysSupport/StdIO.h"
#include "Teddy/SysSupport/Messages.h"
using namespace Teddy::Graphics;
using namespace Teddy::Materials;
using namespace Teddy::PhysicalComponents;
using namespace Teddy::Scenes;
using namespace Teddy::SysSupport;


namespace Teddy     {
namespace Materials {


/*!
	\brief Reservation status for OpenGL lights
	\bug   This really needs a lot of fixing.
*/
unsigned int Light::light_id    [8] = { GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3, GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7 };
int          Light::light_status[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

/*static*/ const unsigned long Light::TYPE_DIRECTIONAL = 0;
/*static*/ const unsigned long Light::TYPE_POSITIONAL  = 1;


void Light::setType( const unsigned long type ){
	this->type = type;
}

//!  Default constructor for light with name only
Light::Light( const std::string &name ):Model(name){
	type = Light::TYPE_POSITIONAL;
	orbit_active = false;
	id = 10000;
	for( int i=0; i<8; i++ ){
		if( light_status[i] == 0 ){
			light_status[i] = 1;
			id = i;
			break;
		}
	}
	if( id == 10000 ){
		printf( "Light::Light could not allocate GL light id\n" );
		return;
	}
	ambient  = Color::BLACK;
	diffuse  = Color::WHITE;
	specular = Color::BLACK;

	float pos[4];

	pos[0] = 0;  //  position.r;
	pos[1] = 0;  //  position.s;
	pos[2] = 0;  //  position.t;
	pos[3] = 1;

	View::check();
	glLightfv( light_id[id], GL_POSITION, pos );
	View::check();
}


void Light::setAttenuation( const float constant, const float linear, const float quadratic ){
	View::check();
	constant_attenuation  = constant;
	linear_attenuation    = linear;
	quadratic_attenuation = quadratic;
	glLightf( light_id[id], GL_CONSTANT_ATTENUATION,  constant_attenuation  );
	glLightf( light_id[id], GL_LINEAR_ATTENUATION,    linear_attenuation    );
	glLightf( light_id[id], GL_QUADRATIC_ATTENUATION, quadratic_attenuation );
	View::check();
}


void Light::setSpotCutOff( const float cutoff_angle ){
	View::check();
	spot_cutoff_angle = cutoff_angle;
	glLightf( light_id[id], GL_SPOT_CUTOFF, spot_cutoff_angle );
	View::check();
}

void Light::setSpotExponent( const float exponent ){
	spot_exponent = exponent;
	glLightf( light_id[id], GL_SPOT_EXPONENT, spot_exponent );
}

void Light::setSpotDirection( Vector spot_direction ){
	this->spot_direction = spot_direction;
}


void Light::orbit( float radius, float speed, int axis ){
	orbit_active = true;
	orbit_radius = radius;
	orbit_speed  = speed;
	orbit_axis   = axis;
}


//!  Set light ambient component
void Light::setAmbient( const Color &a ){
	ambient = a;
	dmsg( M_LWS, "Light::setAmbient ambient  % 8.4f, % 8.4f, % 8.4f", ambient.rgba[0], ambient.rgba[1], ambient.rgba[2] );
}


//!  Set light diffuse component
void Light::setDiffuse( const Color &d ){
	diffuse = d;
}


//!  Set light specular component
void Light::setSpecular( const Color &s ){
	specular = s;
}


//!  Enable individual light
void Light::enable(){
	View::check();
	glEnable( light_id[id] );
	View::check();
}


//!  Disable individual light
void Light::disable(){
	View::check();
	glDisable( light_id[id] );
	View::check();
}


//!  Apply light
/*virtual*/ void Light::applyLight( Projection *p ){
	if( id==10000 ){ return; }

	Camera *camera = p->getCamera();
	float   pos[4];

	View::check(); glPushMatrix();
	camera->doCamera( p, true );

	if( type == Light::TYPE_POSITIONAL ){
		Vector  vec    = getPosition();
		pos[0] = vec.v[0];
		pos[1] = vec.v[1];
		pos[2] = vec.v[2];
		pos[3] = 1;

		float dir[4];

		dir[0] = spot_direction[0];
		dir[1] = spot_direction[1];
		dir[2] = spot_direction[2];

		View::check(); glLightfv( light_id[id], GL_POSITION,       pos );
		View::check(); glLightfv( light_id[id], GL_SPOT_DIRECTION, dir );
		View::check(); glLightfv( light_id[id], GL_AMBIENT,        ambient.rgba );
		View::check(); glLightfv( light_id[id], GL_DIFFUSE,        diffuse.rgba );
		View::check(); glLightfv( light_id[id], GL_SPECULAR,       specular.rgba );
	}else{
		Vector  vec = this->getAttitude().getViewAxis();
		pos[0] = vec.v[0];
		pos[1] = vec.v[1];
		pos[2] = vec.v[2];
		pos[3] = 0;
		View::check(); glLightfv( light_id[id], GL_POSITION, pos           );
		View::check(); glLightfv( light_id[id], GL_AMBIENT,  ambient.rgba  );
		View::check(); glLightfv( light_id[id], GL_DIFFUSE,  diffuse.rgba  );
		View::check(); glLightfv( light_id[id], GL_SPECULAR, specular.rgba );
	}

	View::check(); glPopMatrix();
	View::check();
}


};  //  namespace Materials
};  //  namespace Teddy


