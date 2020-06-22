
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


#ifndef TEDDY__MATERIALS__LIGHT__H
#define TEDDY__MATERIALS__LIGHT__H


#include "Teddy/Maths/Vector.h"
#include "Teddy/Models/Model.h"
#include "Teddy/Graphics/Color.h"


//  Forward declarations
namespace Teddy {
	namespace PhysicalComponents { class Projection; };
};



namespace Teddy     {
namespace Materials {


/*!
	\brief   Lightsource
	\warning Very incomplete
	\bug     Poor id and enable/disable management
	\todo    Destructors

	Lights are used to lit objects in Scene. At the moment
	this class implements a simple OpenGL light wrapper
	with minimum featurs.

	Light is positional by default unless set to directional
	by setType
*/
class Light : public Teddy::Models::Model {
public:
	static const unsigned long TYPE_DIRECTIONAL;
	static const unsigned long TYPE_POSITIONAL;
public:
	Light( const std::string &name );

	void          setType         ( const unsigned long type );
	void          setAmbient      ( const Teddy::Graphics::Color &a );
	void          setDiffuse      ( const Teddy::Graphics::Color &d );
	void          setSpecular     ( const Teddy::Graphics::Color &s );
	void          setAttenuation  ( const float constant, const float linear, const float quadratic );
	void          setSpotCutOff   ( const float cutoff_angle );
	void          setSpotExponent ( const float exponent );
    void          setSpotDirection( Teddy::Maths::Vector spot_direction );
	void          enable          ();
	void          disable         ();
    virtual void  applyLight      ( Teddy::PhysicalComponents::Projection *p );

	//  Light special tick
	void          orbit           ( float radius, float speed, int axis );

protected:
	unsigned long                 type;
	int                           id;
    Teddy::Graphics::Color        ambient;
	Teddy::Graphics::Color        diffuse;
	Teddy::Graphics::Color        specular;
	unsigned int                  flags;

	float                         constant_attenuation;
	float                         linear_attenuation;
	float                         quadratic_attenuation;
	float                         spot_cutoff_angle;
	float                         spot_exponent;
	Teddy::Maths::TVector<float>  spot_direction;

	bool                          orbit_active;
	float                         orbit_radius;
	float                         orbit_speed;
	int                           orbit_axis;
		
	static unsigned int           light_id    [8];  //  FIX (query number of available lights from OpenGL)
	static int                    light_status[8];
};


};  //  namespace Materials
};  //  namespace Teddy


#endif  //  TEDDY__MATERIALS__LIGHT__H

