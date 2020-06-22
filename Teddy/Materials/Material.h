
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


#ifndef TEDDY__MATERIALS__MATERIAL__H
#define TEDDY__MATERIALS__MATERIAL__H


#include "Teddy/Graphics/Color.h"
#include "Teddy/Graphics/View.h"
#include "Teddy/MixIn/Named.h"
#include "Teddy/MixIn/Options.h"
#include "SDL_types.h"


//  Forward declarations
namespace Teddy {
	namespace Graphics { class Texture; };
};
using namespace Teddy::Graphics;
using namespace Teddy::MixIn;


namespace Teddy     {
namespace Materials {


/*!
	\brief	 Surface rendering and lighting properties and textures
	\bug	 Destructors missing
	\todo	 Front face (sidedness)
	\todo	 Textures
	\todo	 Multiple Materials with weighting
	\todo	 Blending
	\todo	 Fog
*/
class Material : public Named, public Options {
public:
	static const unsigned long RENDER_MODE_POINT                   ;
	static const unsigned long RENDER_MODE_LINE                    ;
	static const unsigned long RENDER_MODE_FILL                    ;
	static const unsigned long RENDER_MODE_FILL_OUTLINE            ;

	static const unsigned long RENDER_LIGHTING_COLOR               ;
	static const unsigned long RENDER_LIGHTING_CUSTOM              ;
	static const unsigned long RENDER_LIGHTING_PRIMARY_LIGHT_ONLY  ;
	static const unsigned long RENDER_LIGHTING_SIMPLE              ;
	static const unsigned long RENDER_LIGHTING_FULL                ;

	static const unsigned long RENDER_OPTION_RESERVED              ;
	static const unsigned long RENDER_OPTION_SMOOTH                ;
	static const unsigned long RENDER_OPTION_CULL_FACE             ;
	static const unsigned long RENDER_OPTION_BLEND                 ;
	static const unsigned long RENDER_OPTION_FOG                   ;
	static const unsigned long RENDER_OPTION_NORMALIZE             ;
	static const unsigned long RENDER_OPTION_ALPHA_TEST            ;
	static const unsigned long RENDER_OPTION_DEPTH_TEST            ;
	static const unsigned long RENDER_OPTION_STENCIL_TEST          ;
	static const unsigned long RENDER_OPTION_SCISSOR_TEST          ;
	static const unsigned long RENDER_OPTION_TEXTURE_1D            ;
	static const unsigned long RENDER_OPTION_TEXTURE_2D            ;
	static const unsigned long RENDER_OPTION_TEXTURE_3D            ;
	static const unsigned long RENDER_OPTION_POINT_SMOOTH          ;
	static const unsigned long RENDER_OPTION_LINE_SMOOTH           ;
	static const unsigned long RENDER_OPTION_POLYGON_SMOOTH        ;
	static const unsigned long RENDER_OPTION_AMBIENT               ;
	static const unsigned long RENDER_OPTION_DIFFUSE               ;
	static const unsigned long RENDER_OPTION_SPECULAR              ;
	static const unsigned long RENDER_OPTION_EMISSION              ;
	static const unsigned long RENDER_OPTION_SHINYNESS             ;
	static const unsigned long RENDER_OPTION_BORDER                ;
	static const unsigned long RENDER_OPTION_REMOVE_HIDDEN         ;
	static const unsigned long RENDER_OPTION_FRUSTUM_CULL          ;
	static const unsigned long RENDER_OPTION_SORT_OBJECTS          ;
	static const unsigned long RENDER_OPTION_SORT_ELEMENTS         ;
	static const unsigned long RENDER_OPTION_COLOR_MATERIAL        ;
	static const unsigned long RENDER_OPTION_MASTER_LIGHTING_ONLY  ;

	static const unsigned long RENDER_OPTION_RESERVED_M            ;
	static const unsigned long RENDER_OPTION_SMOOTH_M              ;
	static const unsigned long RENDER_OPTION_CULL_FACE_M           ;
	static const unsigned long RENDER_OPTION_BLEND_M               ;
	static const unsigned long RENDER_OPTION_FOG_M                 ;
	static const unsigned long RENDER_OPTION_NORMALIZE_M           ;
	static const unsigned long RENDER_OPTION_ALPHA_TEST_M          ;
	static const unsigned long RENDER_OPTION_DEPTH_TEST_M          ;
	static const unsigned long RENDER_OPTION_STENCIL_TEST_M        ;
	static const unsigned long RENDER_OPTION_SCISSOR_TEST_M        ;
	static const unsigned long RENDER_OPTION_TEXTURE_1D_M          ;
	static const unsigned long RENDER_OPTION_TEXTURE_2D_M          ;
	static const unsigned long RENDER_OPTION_TEXTURE_3D_M          ;
	static const unsigned long RENDER_OPTION_POINT_SMOOTH_M        ;
	static const unsigned long RENDER_OPTION_LINE_SMOOTH_M         ;
	static const unsigned long RENDER_OPTION_POLYGON_SMOOTH_M      ;
	static const unsigned long RENDER_OPTION_AMBIENT_M             ;
	static const unsigned long RENDER_OPTION_DIFFUSE_M             ;
	static const unsigned long RENDER_OPTION_SPECULAR_M            ;
	static const unsigned long RENDER_OPTION_EMISSION_M            ;
	static const unsigned long RENDER_OPTION_SHINYNESS_M           ;
	static const unsigned long RENDER_OPTION_BORDER_M              ;
	static const unsigned long RENDER_OPTION_REMOVE_HIDDEN_M       ;
	static const unsigned long RENDER_OPTION_FRUSTUM_CULL_M        ;
	static const unsigned long RENDER_OPTION_SORT_OBJECTS_M        ;
	static const unsigned long RENDER_OPTION_SORT_ELEMENTS_M       ;
	static const unsigned long RENDER_OPTION_COLOR_MATERIAL_M      ;
	static const unsigned long RENDER_OPTION_MASTER_LIGHTING_ONLY_M;
	
	static const unsigned long RENDER_MODE_DEFAULT    ;
	static const unsigned long RENDER_LIGHTING_DEFAULT;
	static const unsigned long RENDER_OPTION_DEFAULT_M;
	static const unsigned long RENDER_OPTION_ALL_M    ;

	static char *render_option_to_str( int a );
	static void  init                ();
	static int   getFeature          ( int a );

private:
	static int   mode_to_feature[32];

public:
	Material( const Material &material );
	Material( const Material &material, Uint8 lighting );
	Material( const std::string &name );
	Material( const std::string &name, Uint8 mode, Uint8 lighting, unsigned long options );
	Material( const std::string &name, Color color );
	Material( Color color );
	Material( const std::string &name, const unsigned long options );
	virtual ~Material();

	void             copy( const Material &from );
	
	void             applyAmbient        ( Uint8 lighting );
	void             applyDiffuse        ( Uint8 lighting );
	void             applySpecular       ( Uint8 lighting );
	void             applyEmission       ( Uint8 lighting );
	void             applyShinyness      ( Uint8 lighting );
	void             applyBorder         ( Uint8 lighting );

	virtual void     setMode             ( Uint8  mode );
	virtual Uint8    getMode             () const;
	virtual void     setLighting         ( Uint8  lighting );
	virtual Uint8    getLighting         () const;

	virtual void     setEmission         ( const Color &e );
	virtual Color    getEmission         () const;
	virtual void     setAmbient          ( const Color &a );
	virtual Color    getAmbient          () const;
	virtual void     setDiffuse          ( const Color &d );
	virtual Color    getDiffuse          () const;
	virtual void     setSpecular         ( const Color &s );
	virtual Color    getSpecular         () const;
	virtual void     setShininess        ( float s );
	virtual float    getShininess        () const;
	virtual void     setBorder           ( const Color &s );
	virtual Color    getBorder           () const;
	virtual void     setPolygonOffset    ( const int offset );
	virtual int      getPolygonOffset    () const;
	virtual void     setMaxSmoothingAngle( const float angle );
	virtual float    getMaxSmoothingAngle() const;
	virtual Texture *getTexture          ();
	virtual void     setTexture          ( Texture *t, bool enable=false );

protected:
	Texture *texture;	
	Uint8    render_mode;
	Uint8    render_lighting;
	float    shininess;
	Color    ambient;
	Color    diffuse;
	Color    specular;
	Color    emission;
	Color    border;
	int      polygon_offset;
	float    max_smoothing_angle;

public:
	static Material BLACK;
	static Material GRAY_25;
	static Material GRAY_50;
	static Material GRAY_75;
	static Material WHITE;
	static Material RED;
	static Material YELLOW;
	static Material ORANGE;
	static Material GREEN;
	static Material CYAN;
	static Material BLUE;
	static Material MAGENTA;
	static Material DARK_ORANGE;
	static Material DARK_RED;
	static Material DARK_YELLOW;
	static Material DARK_GREEN;
	static Material DARK_CYAN;
	static Material DARK_BLUE;
	static Material DARK_MAGENTA;
	static Material LIGHT_ORANGE;
	static Material LIGHT_RED;
	static Material LIGHT_YELLOW;
	static Material LIGHT_GREEN;
	static Material LIGHT_CYAN;
	static Material LIGHT_BLUE;
	static Material LIGHT_MAGENTA;
};


};  //  namespace Materials
};  //  namespace Teddy


#endif  //  TEDDY__MATERIALS__MATERIAL_H

