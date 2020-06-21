
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

	$Id: LWLight.h,v 1.1 2002/02/16 12:41:39 tksuoran Exp $
*/


#include "Teddy/TeddyConfig.h"
#if defined( TEDDY_INCLUDE_LW_SCENE )


#include "Teddy/Imports/LWInstance.h"
#include "Teddy/Graphics/Color.h"
#include "Teddy/Materials/Light.h"


#ifndef TEDDY__IMPORTS__LW_LIGHT__H
#define TEDDY__IMPORTS__LW_LIGHT__H


namespace Teddy   {
namespace Imports {


class LWMotion;


class LWLight : public LWInstance {
public:
	LWLight();

	void  genLight  ();
	void  setColor  ( float r, float g, float b );

	Teddy::Materials::Light *getLight();
	void setColor               ( double r, double g, double b   );
	void setType                ( int    type                    );
	void setFalloffType         ( int    falloff_type            );
	void setRange               ( double range                   );
	void setConeAngle           ( double cone_angle              );
	void setEdgeAngle           ( double edge_angle              );
	void setIntensity           ( double intensity               );
	void setFalloff             ( double falloff                 );
	void setAffectCaustics      ( int    affect_caustics         );
	void setAffectDiffuse       ( int    affect_diffuse          );
	void setAffectSpecular      ( int    affect_specular         );
	void setAffectOpenGL        ( int    affect_opengl           );
	void setUseConeAngle        ( int    select                  );
	void setLensFlare           ( int    select                  );
	void setFlareIntensity      ( double flare_intensity         );
	void setFlareDissolve       ( double flare_dissolve          );
	void setLensFlareFade       ( int    lens_flare_fade         );
	void setLensFlareOptions    ( int    lens_flare_options      );
	void setFlareRandStreakInt  ( double flare_rand_streak_int   );
	void setFlareRandStreakDens ( double flare_rand_streak_dens  );
	void setFlareRandStreakSharp( double flare_rand_streak_sharp );
	void setShadowType          ( int    shadow_type             );
	void setShadowCasting       ( int    shadow_casting          );
	void setShadowMapSize       ( int    shadow_map_size         );
	void setShadowMapAngle      ( double shadow_map_angle        );
	void setShadowFuzziness     ( double shadow_fuzziness        );

protected:
	Teddy::Graphics ::Color  ambient_color;
	double                   amb_intensity;
	Teddy::Graphics ::Color  color;
	Teddy::Materials::Light *light;
	int    type                   ;
	int    falloff_type           ;
	double range                  ;
	double cone_angle             ;
	double edge_angle             ;
	double intensity              ;
	double falloff                ;
	int    affect_caustics        ;
	int    affect_diffuse         ;
	int    affect_specular        ;
	int    affect_opengl          ;
	int    use_cone_angle         ;
	int    lens_flare             ;
	double flare_intensity        ;
	double flare_dissolve         ;
	int    lens_flare_fade        ;
	int    lens_flare_options     ;
	double flare_rand_streak_int  ;
	double flare_rand_streak_dens ;
	double flare_rand_streak_sharp;
	int    shadow_type            ;
	int    shadow_casting         ;
	int    shadow_map_size        ;
	double shadow_map_angle       ;
	double shadow_fuzziness       ;


};


};  //  namespace Imports
};  //  namespace Teddy


#endif  //  TEDDY_INCLUDE_LW_SCENE
#endif  //  TEDDY__IMPORTS__LW_LIGHT__H


