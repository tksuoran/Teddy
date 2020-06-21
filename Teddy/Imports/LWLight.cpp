
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

	$Id: LWLight.cpp,v 1.1 2002/02/16 12:41:39 tksuoran Exp $
*/


#include "Teddy/TeddyConfig.h"
#if defined( TEDDY_INCLUDE_LW_SCENE )


#include "Teddy/Imports/LWLight.h"
#include "Teddy/Imports/LWMotion.h"
#include "Teddy/Imports/LWModel.h"
#include "Teddy/Imports/LWMotion.h"
#include "Teddy/Imports/LWChannelEnvelope.h"
#include "Teddy/SysSupport/Messages.h"
using namespace Teddy::Graphics;
using namespace Teddy::Materials;
using namespace Teddy::SysSupport;


namespace Teddy   {
namespace Imports {


LWLight::LWLight():LWInstance(){
	light         = NULL;
	ambient_color = Color::BLACK;
	amb_intensity = 0.0;
}

void LWLight::setColor( double r, double g, double b ){
	this->color = Color( r, g, b );
	dmsg( M_LWS, "Light color %f, %f, %f", r, g, b );
	
}

void LWLight::setType                ( int    type                    ){ this->type                    = type;                    }
void LWLight::setFalloffType         ( int    falloff_type            ){ this->falloff_type            = falloff_type;            }
void LWLight::setRange               ( double range                   ){ this->range                   = range;                   }
void LWLight::setConeAngle           ( double cone_angle              ){ this->cone_angle              = cone_angle;              }
void LWLight::setEdgeAngle           ( double edge_angle              ){ this->edge_angle              = edge_angle;              }
void LWLight::setIntensity           ( double intensity               ){ this->intensity               = intensity;               }
void LWLight::setFalloff             ( double falloff                 ){ this->falloff                 = falloff;                 }
void LWLight::setAffectCaustics      ( int    affect_caustics         ){ this->affect_caustics         = affect_caustics;         }
void LWLight::setAffectDiffuse       ( int    affect_diffuse          ){ this->affect_diffuse          = affect_diffuse ;         }
void LWLight::setAffectSpecular      ( int    affect_specular         ){ this->affect_specular         = affect_specular;         }
void LWLight::setAffectOpenGL        ( int    affect_opengl           ){ this->affect_opengl           = affect_opengl  ;         }
void LWLight::setUseConeAngle        ( int    use_cone_angle          ){ this->use_cone_angle          = use_cone_angle         ; }
void LWLight::setLensFlare           ( int    lens_flare              ){ this->lens_flare              = lens_flare             ; }
void LWLight::setFlareIntensity      ( double flare_intensity         ){ this->flare_intensity         = flare_intensity;         }
void LWLight::setFlareDissolve       ( double flare_dissolve          ){ this->flare_dissolve          = flare_dissolve ;         }
void LWLight::setLensFlareFade       ( int    lens_flare_fade         ){ this->lens_flare_fade         = lens_flare_fade;         }
void LWLight::setLensFlareOptions    ( int    lens_flare_options      ){ this->lens_flare_options      = lens_flare_options;      }
void LWLight::setFlareRandStreakInt  ( double flare_rand_streak_int   ){ this->flare_rand_streak_int   = flare_rand_streak_int;   }
void LWLight::setFlareRandStreakDens ( double flare_rand_streak_dens  ){ this->flare_rand_streak_dens  = flare_rand_streak_dens;  }
void LWLight::setFlareRandStreakSharp( double flare_rand_streak_sharp ){ this->flare_rand_streak_sharp = flare_rand_streak_sharp; }
void LWLight::setShadowType          ( int    shadow_type             ){ this->shadow_type             = shadow_type            ; }
void LWLight::setShadowCasting       ( int    shadow_casting          ){ this->shadow_casting          = shadow_casting         ; }
void LWLight::setShadowMapSize       ( int    shadow_map_size         ){ this->shadow_map_size         = shadow_map_size        ; }
void LWLight::setShadowMapAngle      ( double shadow_map_angle        ){ this->shadow_map_angle        = shadow_map_angle       ; }
void LWLight::setShadowFuzziness     ( double shadow_fuzziness        ){ this->shadow_fuzziness        = shadow_fuzziness       ; }


Light *LWLight::getLight(){
	return this->light;
}


void LWLight::genLight(){
	light = new Light( getModelName() );
	dmsg( M_LWS, "genLight color     % 8.4f, % 8.4f, % 8.4f", color.rgba[0], color.rgba[1], color.rgba[2] );

	switch( type ){
	case 0: 
		light->setType( Light::TYPE_DIRECTIONAL ); break;  // distant
	case 1: 
		light->setType( Light::TYPE_POSITIONAL  ); break;  // point
	case 2: 
		break;  // spot
	case 3: 
		break;  // linear
	case 4: 
		break;  // area
	default: 
		break; //
	}

	// vihreä torni
	//   0, 65, 33  LW
	//   0,113, 57  Teddy

	// valkea kuningas
	//  49, 48, 49  LW
	//  90, 93, 90  Teddy

	light->setAmbient ( Color::BLACK );
	light->setDiffuse ( color );
	light->setSpecular( Color::WHITE );
	//light->setAttenuation  ( const float constant, const float linear, const float quadratic );
	//light->setSpotCutOff   ( const float cutoff_angle );
	//light->setSpotExponent ( const float exponent );
    //light->setSpotDirection( Teddy::Maths::Vector spot_direction );
	light->enable     ();
}


};  //  namespace Imports
};  //  namespace Teddy


#endif  //  TEDDY_INCLUDE_LW_SCENE
