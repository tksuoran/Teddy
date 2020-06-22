
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
#include "Teddy/Graphics/Texture.h"
#include "Teddy/Materials/Material.h"
#include "Teddy/PhysicalComponents/Projection.h"
#include "Teddy/SysSupport/Messages.h"
#include "Teddy/SysSupport/StdIO.h"
using namespace Teddy::Graphics;
using namespace Teddy::SysSupport;


namespace Teddy     {
namespace Materials {


/*static*/ const unsigned long Material::RENDER_MODE_POINT                   =0x01;
/*static*/ const unsigned long Material::RENDER_MODE_LINE                    =0x02;
/*static*/ const unsigned long Material::RENDER_MODE_FILL                    =0x03;
/*static*/ const unsigned long Material::RENDER_MODE_FILL_OUTLINE            =0x04;

/*static*/ const unsigned long Material::RENDER_LIGHTING_COLOR               =0x01;
/*static*/ const unsigned long Material::RENDER_LIGHTING_CUSTOM              =0x02;
/*static*/ const unsigned long Material::RENDER_LIGHTING_PRIMARY_LIGHT_ONLY  =0x03;
/*static*/ const unsigned long Material::RENDER_LIGHTING_SIMPLE              =0x04;
/*static*/ const unsigned long Material::RENDER_LIGHTING_FULL                =0x05;

/*static*/ const unsigned long Material::RENDER_OPTION_RESERVED              = 0l ;
/*static*/ const unsigned long Material::RENDER_OPTION_SMOOTH                = 1l ;
/*static*/ const unsigned long Material::RENDER_OPTION_CULL_FACE             = 2l ;
/*static*/ const unsigned long Material::RENDER_OPTION_BLEND                 = 3l ;
/*static*/ const unsigned long Material::RENDER_OPTION_FOG                   = 4l ;
/*static*/ const unsigned long Material::RENDER_OPTION_NORMALIZE             = 5l ;
/*static*/ const unsigned long Material::RENDER_OPTION_ALPHA_TEST            = 6l ;
/*static*/ const unsigned long Material::RENDER_OPTION_DEPTH_TEST            = 7l ;
/*static*/ const unsigned long Material::RENDER_OPTION_STENCIL_TEST          = 8l ;
/*static*/ const unsigned long Material::RENDER_OPTION_SCISSOR_TEST          = 9l ;
/*static*/ const unsigned long Material::RENDER_OPTION_TEXTURE_1D            =10l ;
/*static*/ const unsigned long Material::RENDER_OPTION_TEXTURE_2D            =11l ;
/*static*/ const unsigned long Material::RENDER_OPTION_TEXTURE_3D            =12l ;
/*static*/ const unsigned long Material::RENDER_OPTION_POINT_SMOOTH          =13l ;
/*static*/ const unsigned long Material::RENDER_OPTION_LINE_SMOOTH           =14l ;
/*static*/ const unsigned long Material::RENDER_OPTION_POLYGON_SMOOTH        =15l ;
/*static*/ const unsigned long Material::RENDER_OPTION_AMBIENT               =16l ;
/*static*/ const unsigned long Material::RENDER_OPTION_DIFFUSE               =17l ;
/*static*/ const unsigned long Material::RENDER_OPTION_SPECULAR              =18l ;
/*static*/ const unsigned long Material::RENDER_OPTION_EMISSION              =19l ;
/*static*/ const unsigned long Material::RENDER_OPTION_SHINYNESS             =20l ;
/*static*/ const unsigned long Material::RENDER_OPTION_BORDER                =21l ;
/*static*/ const unsigned long Material::RENDER_OPTION_REMOVE_HIDDEN         =22l ;
/*static*/ const unsigned long Material::RENDER_OPTION_FRUSTUM_CULL          =23l ;
/*static*/ const unsigned long Material::RENDER_OPTION_SORT_OBJECTS          =24l ;
/*static*/ const unsigned long Material::RENDER_OPTION_SORT_ELEMENTS         =25l ;
/*static*/ const unsigned long Material::RENDER_OPTION_COLOR_MATERIAL        =26l ;
/*static*/ const unsigned long Material::RENDER_OPTION_MASTER_LIGHTING_ONLY  =27l ;

/*static*/ const unsigned long Material::RENDER_OPTION_RESERVED_M            = (1l<<RENDER_OPTION_RESERVED             )  ;
/*static*/ const unsigned long Material::RENDER_OPTION_SMOOTH_M              = (1l<<RENDER_OPTION_SMOOTH               )  ;
/*static*/ const unsigned long Material::RENDER_OPTION_CULL_FACE_M           = (1l<<RENDER_OPTION_CULL_FACE            )  ;
/*static*/ const unsigned long Material::RENDER_OPTION_BLEND_M               = (1l<<RENDER_OPTION_BLEND                )  ;
/*static*/ const unsigned long Material::RENDER_OPTION_FOG_M                 = (1l<<RENDER_OPTION_FOG                  )  ;
/*static*/ const unsigned long Material::RENDER_OPTION_NORMALIZE_M           = (1l<<RENDER_OPTION_NORMALIZE            )  ;
/*static*/ const unsigned long Material::RENDER_OPTION_ALPHA_TEST_M          = (1l<<RENDER_OPTION_ALPHA_TEST           )  ;
/*static*/ const unsigned long Material::RENDER_OPTION_DEPTH_TEST_M          = (1l<<RENDER_OPTION_DEPTH_TEST           )  ;
/*static*/ const unsigned long Material::RENDER_OPTION_STENCIL_TEST_M        = (1l<<RENDER_OPTION_STENCIL_TEST         )  ;
/*static*/ const unsigned long Material::RENDER_OPTION_SCISSOR_TEST_M        = (1l<<RENDER_OPTION_SCISSOR_TEST         )  ;
/*static*/ const unsigned long Material::RENDER_OPTION_TEXTURE_1D_M          = (1l<<RENDER_OPTION_TEXTURE_1D           )  ;
/*static*/ const unsigned long Material::RENDER_OPTION_TEXTURE_2D_M          = (1l<<RENDER_OPTION_TEXTURE_2D           )  ;
/*static*/ const unsigned long Material::RENDER_OPTION_TEXTURE_3D_M          = (1l<<RENDER_OPTION_TEXTURE_3D           )  ;
/*static*/ const unsigned long Material::RENDER_OPTION_POINT_SMOOTH_M        = (1l<<RENDER_OPTION_POINT_SMOOTH         )  ;
/*static*/ const unsigned long Material::RENDER_OPTION_LINE_SMOOTH_M         = (1l<<RENDER_OPTION_LINE_SMOOTH          )  ;
/*static*/ const unsigned long Material::RENDER_OPTION_POLYGON_SMOOTH_M      = (1l<<RENDER_OPTION_POLYGON_SMOOTH       )  ;
/*static*/ const unsigned long Material::RENDER_OPTION_AMBIENT_M             = (1l<<RENDER_OPTION_AMBIENT              )  ;
/*static*/ const unsigned long Material::RENDER_OPTION_DIFFUSE_M             = (1l<<RENDER_OPTION_DIFFUSE              )  ;
/*static*/ const unsigned long Material::RENDER_OPTION_SPECULAR_M            = (1l<<RENDER_OPTION_SPECULAR             )  ;
/*static*/ const unsigned long Material::RENDER_OPTION_EMISSION_M            = (1l<<RENDER_OPTION_EMISSION             )  ;
/*static*/ const unsigned long Material::RENDER_OPTION_SHINYNESS_M           = (1l<<RENDER_OPTION_SHINYNESS            )  ;
/*static*/ const unsigned long Material::RENDER_OPTION_BORDER_M              = (1l<<RENDER_OPTION_BORDER               )  ;
/*static*/ const unsigned long Material::RENDER_OPTION_REMOVE_HIDDEN_M       = (1l<<RENDER_OPTION_REMOVE_HIDDEN        )  ;
/*static*/ const unsigned long Material::RENDER_OPTION_FRUSTUM_CULL_M        = (1l<<RENDER_OPTION_FRUSTUM_CULL         )  ;
/*static*/ const unsigned long Material::RENDER_OPTION_SORT_OBJECTS_M        = (1l<<RENDER_OPTION_SORT_OBJECTS         )  ;
/*static*/ const unsigned long Material::RENDER_OPTION_SORT_ELEMENTS_M       = (1l<<RENDER_OPTION_SORT_ELEMENTS        )  ;
/*static*/ const unsigned long Material::RENDER_OPTION_COLOR_MATERIAL_M      = (1l<<RENDER_OPTION_COLOR_MATERIAL       )  ;
/*static*/ const unsigned long Material::RENDER_OPTION_MASTER_LIGHTING_ONLY_M= (1l<<RENDER_OPTION_MASTER_LIGHTING_ONLY )  ;


/*static*/ const unsigned long Material::RENDER_MODE_DEFAULT     = Material::RENDER_MODE_FILL_OUTLINE;
/*static*/ const unsigned long Material::RENDER_LIGHTING_DEFAULT = Material::RENDER_LIGHTING_SIMPLE;
/*static*/ const unsigned long Material::RENDER_OPTION_DEFAULT_M =
	RENDER_OPTION_CULL_FACE_M    | 
	RENDER_OPTION_DEPTH_TEST_M   | 
	RENDER_OPTION_DIFFUSE_M      | 
	RENDER_OPTION_FRUSTUM_CULL_M;
/*static*/ const unsigned long Material::RENDER_OPTION_ALL_M =
	RENDER_OPTION_SMOOTH_M         | 
	RENDER_OPTION_CULL_FACE_M      | 
	RENDER_OPTION_BLEND_M          | 
	RENDER_OPTION_FOG_M            | 
	RENDER_OPTION_NORMALIZE_M      | 
	RENDER_OPTION_ALPHA_TEST_M     | 
	RENDER_OPTION_DEPTH_TEST_M     | 
	RENDER_OPTION_STENCIL_TEST_M   | 
	RENDER_OPTION_SCISSOR_TEST_M   | 
	RENDER_OPTION_TEXTURE_1D_M     | 
	RENDER_OPTION_TEXTURE_2D_M     | 
	RENDER_OPTION_TEXTURE_3D_M     | 
	RENDER_OPTION_POINT_SMOOTH_M   | 
	RENDER_OPTION_LINE_SMOOTH_M    | 
	RENDER_OPTION_POLYGON_SMOOTH_M | 
	RENDER_OPTION_AMBIENT_M        | 
	RENDER_OPTION_DIFFUSE_M        | 
	RENDER_OPTION_SPECULAR_M       | 
	RENDER_OPTION_EMISSION_M       | 
	RENDER_OPTION_SHINYNESS_M      | 
	RENDER_OPTION_BORDER_M         | 
	RENDER_OPTION_REMOVE_HIDDEN_M  | 
	RENDER_OPTION_FRUSTUM_CULL_M   | 
	RENDER_OPTION_SORT_OBJECTS_M   | 
	RENDER_OPTION_SORT_ELEMENTS_M  | 
	RENDER_OPTION_COLOR_MATERIAL_M;


/*static*/ int   Material::mode_to_feature[32];

/*static*/ char *Material::render_option_to_str( int a ){
	switch( a ){
	case RENDER_OPTION_RESERVED      : return "RENDER_OPTION_RESERVED      ";
	case RENDER_OPTION_SMOOTH        : return "RENDER_OPTION_SMOOTH        ";
	case RENDER_OPTION_CULL_FACE     : return "RENDER_OPTION_CULL_FACE     ";
	case RENDER_OPTION_BLEND         : return "RENDER_OPTION_BLEND         ";
	case RENDER_OPTION_FOG           : return "RENDER_OPTION_FOG           ";
	case RENDER_OPTION_NORMALIZE     : return "RENDER_OPTION_NORMALIZE     ";
	case RENDER_OPTION_ALPHA_TEST    : return "RENDER_OPTION_ALPHA_TEST    ";
	case RENDER_OPTION_DEPTH_TEST    : return "RENDER_OPTION_DEPTH_TEST    ";
	case RENDER_OPTION_STENCIL_TEST  : return "RENDER_OPTION_STENCIL_TEST  ";
	case RENDER_OPTION_SCISSOR_TEST  : return "RENDER_OPTION_SCISSOR_TEST  ";
	case RENDER_OPTION_TEXTURE_1D    : return "RENDER_OPTION_TEXTURE_1D    ";
	case RENDER_OPTION_TEXTURE_2D    : return "RENDER_OPTION_TEXTURE_2D    ";
	case RENDER_OPTION_TEXTURE_3D    : return "RENDER_OPTION_TEXTURE_3D    ";
	case RENDER_OPTION_POINT_SMOOTH  : return "RENDER_OPTION_POINT_SMOOTH  ";
	case RENDER_OPTION_LINE_SMOOTH   : return "RENDER_OPTION_LINE_SMOOTH   ";
	case RENDER_OPTION_POLYGON_SMOOTH: return "RENDER_OPTION_POLYGON_SMOOTH";
	case RENDER_OPTION_AMBIENT       : return "RENDER_OPTION_AMBIENT       ";
	case RENDER_OPTION_DIFFUSE       : return "RENDER_OPTION_DIFFUSE       ";
	case RENDER_OPTION_SPECULAR      : return "RENDER_OPTION_SPECULAR      ";
	case RENDER_OPTION_EMISSION      : return "RENDER_OPTION_EMISSION      ";
	case RENDER_OPTION_SHINYNESS     : return "RENDER_OPTION_SHINYNESS     ";
	case RENDER_OPTION_BORDER        : return "RENDER_OPTION_BORDER        ";
	case RENDER_OPTION_REMOVE_HIDDEN : return "RENDER_OPTION_REMOVE_HIDDEN ";
	case RENDER_OPTION_FRUSTUM_CULL  : return "RENDER_OPTION_FRUSTUM_CULL  ";
	case RENDER_OPTION_SORT_OBJECTS  : return "RENDER_OPTION_SORT_OBJECTS  ";
	case RENDER_OPTION_SORT_ELEMENTS : return "RENDER_OPTION_SORT_ELEMENTS ";
	case RENDER_OPTION_COLOR_MATERIAL: return "RENDER_OPTION_COLOR_MATERIAL";
	default:
		return "unknown";
		break;
	}
}

/*static*/ void  Material::init(){
	dmsg( M_INIT, "init_materials..." );
	mode_to_feature[RENDER_OPTION_RESERVED      ] = 0;
	mode_to_feature[RENDER_OPTION_SMOOTH        ] = 0;
	mode_to_feature[RENDER_OPTION_CULL_FACE     ] = View::CULL_FACE       ;
	mode_to_feature[RENDER_OPTION_BLEND         ] = View::BLEND           ;
	mode_to_feature[RENDER_OPTION_FOG           ] = View::FOG             ;
	mode_to_feature[RENDER_OPTION_NORMALIZE     ] = View::NORMALIZE       ;
	mode_to_feature[RENDER_OPTION_ALPHA_TEST    ] = View::ALPHA_TEST      ;
	mode_to_feature[RENDER_OPTION_DEPTH_TEST    ] = View::DEPTH_TEST      ;
	mode_to_feature[RENDER_OPTION_STENCIL_TEST  ] = View::STENCIL_TEST    ;
	mode_to_feature[RENDER_OPTION_SCISSOR_TEST  ] = View::SCISSOR_TEST    ;
	mode_to_feature[RENDER_OPTION_TEXTURE_1D    ] = View::TEXTURE_1D      ;
	mode_to_feature[RENDER_OPTION_TEXTURE_2D    ] = View::TEXTURE_2D      ;
	mode_to_feature[RENDER_OPTION_TEXTURE_3D    ] = 0;
	mode_to_feature[RENDER_OPTION_POINT_SMOOTH  ] = View::POINT_SMOOTH    ;
	mode_to_feature[RENDER_OPTION_LINE_SMOOTH   ] = View::LINE_SMOOTH     ;
	mode_to_feature[RENDER_OPTION_POLYGON_SMOOTH] = View::POLYGON_SMOOTH  ;
	mode_to_feature[RENDER_OPTION_AMBIENT       ] = 0;
	mode_to_feature[RENDER_OPTION_DIFFUSE       ] = 0;
	mode_to_feature[RENDER_OPTION_SPECULAR      ] = 0;
	mode_to_feature[RENDER_OPTION_EMISSION      ] = 0;
	mode_to_feature[RENDER_OPTION_SHINYNESS     ] = 0;
	mode_to_feature[RENDER_OPTION_BORDER        ] = 0;
	mode_to_feature[RENDER_OPTION_REMOVE_HIDDEN ] = 0;
	mode_to_feature[RENDER_OPTION_FRUSTUM_CULL  ] = 0;
	mode_to_feature[RENDER_OPTION_SORT_OBJECTS  ] = 0;
	mode_to_feature[RENDER_OPTION_SORT_ELEMENTS ] = 0;
	mode_to_feature[RENDER_OPTION_COLOR_MATERIAL] = View::COLOR_MATERIAL  ;
}

/*static*/ int   Material::getFeature( int a ){
	return mode_to_feature[a];
}



//	Note:
//
//	Color::BLACK etc. cannot be used here,
//	because they might not be constructed yet!
Material Material::BLACK         = Material( "Default Black Material",         Color(C_BLACK         )  );
Material Material::GRAY_25       = Material( "Default Gray 25 Material",       Color(C_GRAY_25       )  );
Material Material::GRAY_50       = Material( "Default Gray 50 Material",       Color(C_GRAY_50       )  );
Material Material::GRAY_75       = Material( "Default Gray 75 Material",       Color(C_GRAY_75       )  );
Material Material::WHITE         = Material( "Default White Material",         Color(C_WHITE         )  );
Material Material::ORANGE        = Material( "Default Orange Material",        Color(C_ORANGE        )  );
Material Material::RED           = Material( "Default Red Material",           Color(C_RED           )  );
Material Material::YELLOW        = Material( "Default Yellow Material",        Color(C_YELLOW        )  );
Material Material::GREEN         = Material( "Default Green Material",         Color(C_GREEN         )  );
Material Material::CYAN          = Material( "Default Cyan Material",          Color(C_CYAN          )  );
Material Material::BLUE          = Material( "Default Blue Material",          Color(C_BLUE          )  );
Material Material::MAGENTA       = Material( "Default Magenta Material",       Color(C_MAGENTA       )  );
Material Material::DARK_ORANGE   = Material( "Default Dark Orange Material",   Color(C_DARK_ORANGE   )  );
Material Material::DARK_RED      = Material( "Default Dark Red Material",      Color(C_DARK_RED      )  );
Material Material::DARK_YELLOW   = Material( "Default Dark Yellow Material",   Color(C_DARK_YELLOW   )  );
Material Material::DARK_GREEN    = Material( "Default Dark Green Material",    Color(C_DARK_GREEN    )  );
Material Material::DARK_CYAN     = Material( "Default Dark Cyan Material",     Color(C_DARK_CYAN     )  );
Material Material::DARK_BLUE     = Material( "Default Dark Blue Material",     Color(C_DARK_BLUE     )  );
Material Material::DARK_MAGENTA  = Material( "Default Dark Magenta Material",  Color(C_DARK_MAGENTA  )  );
Material Material::LIGHT_ORANGE  = Material( "Default Light Orange Material",  Color(C_LIGHT_ORANGE  )  );
Material Material::LIGHT_RED     = Material( "Default Light Red Material",     Color(C_LIGHT_RED     )  );
Material Material::LIGHT_YELLOW  = Material( "Default Light Yellow Material",  Color(C_LIGHT_YELLOW  )  );
Material Material::LIGHT_GREEN   = Material( "Default Light Green Material",   Color(C_LIGHT_GREEN   )  );
Material Material::LIGHT_CYAN    = Material( "Default Light Cyan Material",    Color(C_LIGHT_CYAN    )  );
Material Material::LIGHT_BLUE    = Material( "Default Light Blue Material",    Color(C_LIGHT_BLUE    )  );
Material Material::LIGHT_MAGENTA = Material( "Default Light Magenta Material", Color(C_LIGHT_MAGENTA )  );


//!  Constructor with name
Material::Material( const std::string &name )
:
Named  (name),
Options(0)
{
	this->shininess       = 0;
	this->ambient         = Color( C_BLACK );
	this->diffuse         = Color( C_BLACK );
	this->specular        = Color( C_BLACK );
	this->emission        = Color( C_BLACK );
	this->render_mode     = RENDER_MODE_FILL;
	this->render_lighting = RENDER_LIGHTING_SIMPLE;
	this->texture         = NULL;
	this->polygon_offset  = 0;
	this->max_smoothing_angle = 60.0f;
}

//!  Constructor with name and options
Material::Material( const std::string &name, const unsigned long options )
:
Named  (name),
Options(options)
{
	this->shininess       = 0;
	this->ambient         = Color( C_BLACK );
	this->diffuse         = Color( C_BLACK );
	this->specular        = Color( C_BLACK );
	this->emission        = Color( C_BLACK );
	this->render_mode     = RENDER_MODE_FILL;
	this->render_lighting = RENDER_LIGHTING_SIMPLE;
	this->texture         = NULL;
	this->polygon_offset  = 0;
	this->max_smoothing_angle = 60.0f;
}

void Material::copy( const Material &from ){
	this->shininess = from.shininess;
	this->ambient   = from.ambient;
	this->diffuse   = from.diffuse;
	this->specular  = from.specular;
	this->emission  = from.emission;
	this->border    = from.border;
	this->render_lighting     = from.render_lighting;
	this->render_mode         = from.render_mode;
	this->polygon_offset      = from.polygon_offset;
	this->max_smoothing_angle = from.max_smoothing_angle;
	this->texture             = from.texture;
	this->options             = from.options;
}



//!  Constructor with name, lighting and shading modes
Material::Material( const std::string &name, Uint8 mode, Uint8 lighting, unsigned long options )
:
Named          ( name     ),
Options        ( options  ),
texture        ( NULL     ),
render_mode    ( mode     ),
render_lighting( lighting ),
shininess      ( 0        ),
ambient        ( Color(C_BLACK  ) ),
diffuse        ( Color(C_GRAY_50) ),
specular       ( Color(C_BLACK  ) ),
emission       ( Color(C_BLACK  ) ),
border         ( Color(C_GRAY_50) ),
polygon_offset      ( 0     ),
max_smoothing_angle ( 60.0f )
{
}


//!  Copyconstructor
Material::Material( const Material &m )
:
Named  ( m.name ),
Options( m.options )
{
	this->shininess       = m.shininess;
	this->ambient         = m.ambient;
	this->diffuse         = m.diffuse;
	this->specular        = m.specular;
	this->emission        = m.emission;
	this->border          = m.border;
	this->render_mode     = m.render_mode;
	this->render_lighting = m.render_lighting;
	this->texture         = m.texture;
	this->polygon_offset  = 0;
	this->max_smoothing_angle = 60.0f;
}


//!  Copyconstructor with lighting mode change
Material::Material( const Material &m, Uint8 lighting )
:
Named  ( m.name    ),
Options( m.options )
{
	this->shininess       = m.shininess;
	this->ambient         = m.ambient;
	this->diffuse         = m.diffuse;
	this->specular        = m.specular;
	this->emission        = m.emission;
	this->border          = m.border;
	this->render_mode     = m.render_mode;
	this->render_lighting = lighting;
	this->texture         = m.texture;
	this->polygon_offset  = 0;
	this->max_smoothing_angle = 60.0f;
}


//!  Constructor with name and ambient/diffuse color
Material::Material( const std::string &name, Color color )
:
Named  (name),
Options(
	RENDER_OPTION_CULL_FACE_M  |
	RENDER_OPTION_DEPTH_TEST_M |
	RENDER_OPTION_AMBIENT_M    |
	RENDER_OPTION_DIFFUSE_M    |
	RENDER_OPTION_SPECULAR_M   |
	RENDER_OPTION_EMISSION_M   |
	RENDER_OPTION_SHINYNESS_M  |
	RENDER_OPTION_SMOOTH_M
)
{

	this->shininess       = 40.0f;
	this->ambient         = Color( C_BLACK );
	this->diffuse         = color;
	this->specular        = Color( C_WHITE );
	this->emission        = Color( C_BLACK );
	this->border          = Color( C_GRAY_75 );
	this->render_mode     = RENDER_MODE_FILL;
	this->render_lighting = RENDER_LIGHTING_SIMPLE;
	this->texture         = NULL;
	this->polygon_offset  = 0;
	this->max_smoothing_angle = 60.0f;
}


//!  Constructor with ambient/diffuse color
Material::Material( Color color )
:
Named  (""),
Options(
	RENDER_OPTION_CULL_FACE_M  |
	RENDER_OPTION_DEPTH_TEST_M |
	RENDER_OPTION_AMBIENT_M    |
	RENDER_OPTION_DIFFUSE_M    |
	RENDER_OPTION_SPECULAR_M   |
	RENDER_OPTION_EMISSION_M   |
	RENDER_OPTION_SHINYNESS_M  |
	RENDER_OPTION_SMOOTH_M
)
{

	this->shininess       = 40.0f;
	this->ambient         = Color( C_BLACK );
	this->diffuse         = color;
	this->specular        = Color( C_WHITE );
	this->emission        = Color( C_BLACK );
	this->border          = Color( C_GRAY_75 );
	this->render_mode     = RENDER_MODE_FILL;
	this->render_lighting = RENDER_LIGHTING_SIMPLE;
	this->texture         = NULL;
	this->polygon_offset  = 0;
	this->max_smoothing_angle = 60.0f;
}


//!  Destructor
Material::~Material(){
}


//!  FIX
void Material::applyAmbient( Uint8 lighting ){
	switch( lighting ){
	case RENDER_LIGHTING_COLOR:   break;
	case RENDER_LIGHTING_CUSTOM:  break;
		break;
	case RENDER_LIGHTING_PRIMARY_LIGHT_ONLY:
		//	Fall through
	case RENDER_LIGHTING_FULL:
		//	FIX Not yet implemented, fall through
	case RENDER_LIGHTING_SIMPLE:
		glMaterialfv( GL_FRONT, GL_AMBIENT, ambient.rgba );
#		ifdef DEBUG_MATERIALS
		printf( << "Ambient %d, %d, %d\n", ambient.rgba[0], ambient.rgba[1], ambient.rgba[2] );
#		endif
		break;
	default:
		printf( "Unknown lighting mode\n" );
		break;
	}
}


//!  FIX
void Material::applyDiffuse( Uint8 lighting ){
//	cout << "applyDiffuse " << (int)(lighting) << endl;
	switch( lighting ){
	case RENDER_LIGHTING_COLOR:
		diffuse.glApply();
//		cout << "applyDiffuse " << diffuse.rgba[0] << ", " << diffuse.rgba[1] << ", " << diffuse.rgba[2] << endl;
		break;
	case RENDER_LIGHTING_CUSTOM:  break;
	case RENDER_LIGHTING_PRIMARY_LIGHT_ONLY:
		//	Fall through
	case RENDER_LIGHTING_FULL:
		//	FIX Not yet implemented, fall through
	case RENDER_LIGHTING_SIMPLE:
		glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse.rgba );
#		ifdef DEBUG_MATERIALS
		printf( "applyDiffuse %d, %d, %d\n", diffuse.rgba[0], diffuse.rgba[1], diffuse.rgba[2] );
#		endif
		break;
	default:
		printf( "Unknown lighting mode\n" );
		break;
	}
}


//!  FIX
void Material::applySpecular( Uint8 lighting ){
	switch( lighting ){
	case RENDER_LIGHTING_COLOR:   break;
	case RENDER_LIGHTING_CUSTOM:  break;
		break;
	case RENDER_LIGHTING_PRIMARY_LIGHT_ONLY:
		//	Fall through
	case RENDER_LIGHTING_FULL:
		//	FIX Not yet implemented, fall through
	case RENDER_LIGHTING_SIMPLE:
		glMaterialfv( GL_FRONT, GL_SPECULAR, specular.rgba );
#		ifdef DEBUG_MATERIALS
		printf( "Specular %d, %d, %d\n", specular.rgba[0], specular.rgba[1], specular.rgba[2] );
#		endif
		break;
	default:
		printf( "Unknown lighting mode\n" );
		break;
	}
}


//!  FIX
void Material::applyEmission( Uint8 lighting ){
	switch( lighting ){
	case RENDER_LIGHTING_COLOR:   break;
	case RENDER_LIGHTING_CUSTOM:  break;
		break;
	case RENDER_LIGHTING_PRIMARY_LIGHT_ONLY:
		//	Fall through
	case RENDER_LIGHTING_FULL:
		//	FIX Not yet implemented, fall through
	case RENDER_LIGHTING_SIMPLE:
		glMaterialfv( GL_FRONT, GL_EMISSION, emission.rgba );
#		ifdef DEBUG_MATERIALS
		printf( "Emission %d, %d, %d\n", emission.rgba[0], emission.rgba[1], emission.rgba[2] );
#		endif
		break;
	default:
		printf( "Unknown lighting mode\n" );
		break;
	}
}


//!  FIX
void Material::applyBorder( Uint8 lighting ){
	switch( lighting ){
	case RENDER_LIGHTING_COLOR:
		border.glApply();
		break;
	case RENDER_LIGHTING_CUSTOM:  break;
	case RENDER_LIGHTING_PRIMARY_LIGHT_ONLY:
		//	Fall through
	case RENDER_LIGHTING_FULL:
		//	FIX Not yet implemented, fall through
	case RENDER_LIGHTING_SIMPLE:
		glMaterialfv( GL_FRONT, GL_DIFFUSE, border.rgba );
#		ifdef DEBUG_MATERIALS
		printf( "Border Diffuse %d, %d, %d\n", border.rgba[0], border.rgba[1], border.rgba[2] );
#		endif
		break;
	default:
		printf( "Unknown lighting mode\n" );
		break;
	}
}


//!  FIX
void Material::applyShinyness( Uint8 lighting ){
	switch( lighting ){
	case RENDER_LIGHTING_COLOR:
	case RENDER_LIGHTING_CUSTOM:
		break;
	case RENDER_LIGHTING_PRIMARY_LIGHT_ONLY:
		//	Fall through
	case RENDER_LIGHTING_FULL:
		//	FIX Not yet implemented, fall through
	case RENDER_LIGHTING_SIMPLE:
		glMaterialf( GL_FRONT, GL_SHININESS, shininess );
#		ifdef DEBUG_MATERIALS
		printf( "Shininess %f\n", shininess );
#		endif
		break;
	default:
		printf( "Unknown lighting mode\n" );
		break;
	}
}


//!  Set Render mode
void Material::setMode( Uint8 mode ){
	this->render_mode = mode;
}


//!  Get Render mode
Uint8 Material::getMode() const {
	return this->render_mode;
}


//!  Set Render Lighting mode
void Material::setLighting( Uint8 lighting ){
	this->render_lighting = lighting;
}


//!  Get Render Lighting mode
Uint8 Material::getLighting() const {
	return this->render_lighting;
}


//!  Set Material emission component
void Material::setEmission( const Color &e ){
	this->emission = e;
}


//!  Get Material emission component
Color Material::getEmission() const {
	return this->emission;
}


//!  Set Material ambient component
void Material::setAmbient( const Color &a ){
	this->ambient = a;
}


//!  Get Material ambient component
Color Material::getAmbient() const {
	return this->ambient;
}


//!  Set diffuse component
void Material::setDiffuse( const Color &d ){
	this->diffuse = d;
}


//!  Get Material diffuse component
Color Material::getDiffuse() const {
	return this->diffuse;
}


//!  Set Material specular component
void Material::setSpecular( const Color &s ){
	this->specular = s;
}


//!  Get Material specular component
Color Material::getSpecular() const {
	return this->specular;
}


//!  Set Material border component
void Material::setBorder( const Color &b ){
	this->border = b;
}


//!  Get Material border component
Color Material::getBorder() const {
	return this->border;
}


//!  Get Material Texture
Texture *Material::getTexture(){
	return this->texture;
}


//!  Set Material Texture
void Material::setTexture( Texture *t, bool enable ){
	this->texture = t;
	if( enable && texture->isGood() ){
		this->enable( RENDER_OPTION_TEXTURE_2D_M );
	}
}


//!  Set Material shininess
void Material::setShininess( float s ){
	this->shininess = s;
}


//!  Get shininess
float Material::getShininess() const {
	return this->shininess;
}


/*virtual*/ void Material::setPolygonOffset( const int offset ){
	this->polygon_offset = offset;
}


/*virtual*/ int Material::getPolygonOffset() const {
	return polygon_offset;
}


/*virtual*/ void Material::setMaxSmoothingAngle( const float angle ){
	this->max_smoothing_angle = angle;
}


/*virtual*/ float Material::getMaxSmoothingAngle() const {
	return max_smoothing_angle;
}


};  //  namespace Materials
};  //  namespace Teddy

