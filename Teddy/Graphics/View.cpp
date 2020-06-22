
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

	$Id: View.cpp,v 1.8 2002/02/16 16:38:11 tksuoran Exp $
*/


#include "Teddy/Graphics/Device.h"
#include "Teddy/TeddyConfig.h"
#include "Teddy/Graphics/Font.h"
#include "Teddy/Graphics/PsRenderer.h"
#include "Teddy/Graphics/Texture.h"
#include "Teddy/Graphics/View.h"
#include "Teddy/Maths/Matrix.h"
#include "Teddy/PhysicalComponents/WindowManager.h"
#include "Teddy/PhysicalComponents/Style.h"
#include "Teddy/SysSupport/Messages.h"
#include "Teddy/SysSupport/StdSDL.h"
#include "Teddy/SysSupport/StdIO.h"
#ifndef SWIG
#include <cstdlib>
#endif
using namespace Teddy::Maths;
using namespace Teddy::MixIn;
using namespace Teddy::PhysicalComponents;
using namespace Teddy::SysSupport;


namespace Teddy    {
namespace Graphics {


View *View::active = NULL;


const int View::OPT_FRAME                   = (1ul<<1ul);
const int View::OPT_FULLSCREEN              = (1ul<<2ul);
const int View::OPT_MULTI_WINDOW            = (1ul<<3ul);
const int View::OPT_SEPARATE_SPECULAR_COLOR = (1ul<<4ul);
const int View::OPT_FONT_FIX                = (1ul<<5ul);


//!  Displaying surface
/*virtual*/ void View::displayPs( const char *filename ){
#	if !defined( USE_TINY_GL )
    //  Initialize feedback
	long     max_len = 1024*1024;
	GLfloat *buffer  = new GLfloat[max_len];
	glFeedbackBuffer( max_len, GL_3D_COLOR, buffer );
	glRenderMode( GL_FEEDBACK );

    //  Drawing
	if( clear == true ){
		glClearColor( clear_color.rgba[0], clear_color.rgba[1], clear_color.rgba[2], clear_color.rgba[3] );
		glClearDepth( 1 );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	}
	current_texture = NULL;
	window_manager->draw();

    //  Proces feedback
	GLint len = glRenderMode( GL_RENDER );
	PsRenderer ps;
	ps.writePs( filename, buffer, len, true );
    delete[] buffer;
#	endif
}

//!  Displaying surface
/*virtual*/ void View::display(){

#	if !defined( USE_TINY_GL )
	if( clear == true ){
#	endif
		glClearColor( clear_color.rgba[0], clear_color.rgba[1], clear_color.rgba[2], clear_color.rgba[3] );
		glClearDepth( 1 );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
#	if !defined( USE_TINY_GL )
	}
#	endif

	current_texture = NULL;

	//	Draw layers
	window_manager->draw();

#	if defined( USE_TINY_GL )
	sdl_swgl_SwapBuffers();
#	else
	SDL_GL_SwapWindow(sdl_window);
#	endif

	//check();

	frames++;
	Uint32 clock_time = SDL_GetTicks();
/*	printf(
		"View::display(): %ld : %f\n",
		(unsigned long)(clock),
		clock_time
	);*/

	if( (clock_time - last_fps) > 1000 ){
		fps      = (float)(frames*1000) / (float)(clock_time - last_fps);
		frames   = 0;
		last_fps = clock_time;
	}
	last_frame = clock_time - last_time;
	last_time  = clock_time;
}


void View::setClearColor( const Color &clear_color ){
	this->clear_color = clear_color;
}


void View::setCull( unsigned long dir ){
	if( dir == 0 ){
        msg( M_INIT, "setCull back" );
		glCullFace ( GL_BACK );
		glFrontFace( GL_CW    );
	}else{
        msg( M_INIT, "setCull front" );
		glCullFace ( GL_FRONT );
		glFrontFace( GL_CW    );
		//glFrontFace( GL_CCW  );
	}
}


/*!
	\brief View constructor
	\param width Witdh of view in pixels
	\param height Height of view in pixels
	\param options Options: any combination of

	<ul>
		<li>View::OPT_FRAME
		<li>View::OPT_FULLSCREEN
		<li>View::OPT_MULTI_WINDOW
	</ul>
*/
View::View( int width, int height, Options options )
:
options(options)
{
	active      = this;
	clear       = true;
	clear_color = Color( 0.5f, 0.5, 0.5f, 1.0f );

#	if defined( USE_TINY_GL )
	/* Set video mode */
	sdl_surface = SDL_SetVideoMode(width, height, 16, SDL_DOUBLEBUF);
	if( sdl_surface == NULL ) {
		fmsg( M_GL, "Couldn't set %dx%d video mode: %s", width, height, SDL_GetError() );
	}

	sdl_swgl_Context *context = sdl_swgl_CreateContext();
	sdl_swgl_MakeCurrent( sdl_surface, context );
#	else
	/*
	 * Now, we want to setup our requested
	 * window attributes for our OpenGL window.
	 * We want *at least* 5 bits of red, green
	 * and blue. We also want at least a 16-bit
	 * depth buffer.
	 *
	 * The last thing we do is request a double
	 * buffered window. '1' turns on double
	 * buffering, '0' turns it off.
	 *
	 * Note that we do not use SDL_DOUBLEBUF in
	 * the flags to SDL_SetVideoMode. That does
	 * not affect the GL attribute state, only
	 * the standard 2D blitting setup.
	 */
	msg( M_INIT, "SDL_GL_SetAttribute..." );
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE,	   8 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE,    8 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE,	   8 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE,   24 );
//	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE,   32 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER,  1 );

	Uint32 sdl_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
	if( options.isDisabled(OPT_FRAME)      ){ sdl_flags |= SDL_WINDOW_BORDERLESS;    }
	if( options.isEnabled (OPT_FULLSCREEN) ){ sdl_flags |= SDL_WINDOW_FULLSCREEN_DESKTOP; }

	/*
	 * Set the video mode
	 */
	msg( M_INIT, "SDL_CreateWindow( %d, %d, 0x%x )...", width, height, sdl_flags );
	sdl_window = SDL_CreateWindow("Teddy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, sdl_flags);
	if( sdl_window == NULL ) {
		/*
		 * This could happen for a variety of reasons,
		 * including DISPLAY not being set, the specified
		 * resolution not being available, etc.
		 */
		fmsg( M_GL, "Video mode set failed: %s", SDL_GetError() );
	}else{
		msg( M_INIT, "Video mode ok..." );
	}

    sdl_gl_context = SDL_GL_CreateContext(sdl_window);
    SDL_GL_MakeCurrent(sdl_window, sdl_gl_context);

	int gl_depth_size;
	SDL_GL_GetAttribute( SDL_GL_DEPTH_SIZE,   &gl_depth_size );

	msg( M_INIT, "Got %d bits for depth buffer", gl_depth_size );
#	endif

	if( Font::default_font == &Font::dummy_font ){
		if( options.isEnabled (OPT_FONT_FIX) ){
			Font::default_font = new Font( "Data/gui/fonts.raw", Font::MODE_NO_BLEND );
		}else{
			Font::default_font = new Font( "Data/gui/fonts.raw", Font::MODE_NORMAL   );
		}
	}
	if( Style::default_style == NULL ){
		Style::default_style = new Style();
	}

	//glGetIntegerv( GL_VIEWPORT, viewport );

	gl_polygon_mode             = GL_FILL;
	gl_shade_model              = GL_FLAT;
	gl_blend_source_factor      = GL_SRC_ALPHA;
	gl_blend_destination_factor = GL_ONE_MINUS_SRC_ALPHA;
	gl_fog_mode                 = GL_LINEAR;
	gl_fog_color[0]             = 0;
	gl_fog_color[1]             = 0;
	gl_fog_color[2]             = 0;
	gl_fog_start                = 0;
	gl_fog_end                  = 1;
    gl_clear_depth              = 1;
    size                        = IntVector2( width, height );

	dmsg( M_WM, "view::getSize() = %d x %d", size[0], size[1] );

	ratio	                    = (float)width/(float)height;
	frames	                    = 0;
	last_frame                  = 0;
	last_time                   = 0;
	last_fps                    = 0;
	fps 	                    = 0;
	screen_width                = 0;
	screen_height               = 0;
	current_matrix_mode         = GL_MODELVIEW;
	current_texture             = NULL;
	current_element             = -1;

	glMatrixMode( GL_MODELVIEW );

	for( int i=0; i<256; i++ ){
		gl_feature[i] = false;
	}

	Color ambient   = Color::RED;
	Color diffuse   = Color::RED;
	Color specular  = Color::RED;
	Color emission  = Color::RED;
	float shininess = 1.0f;

//  glPointSize    ( 4.0f );
	glColor4f      ( 0.5f, 0.5f, 0.5f, 1.0f );
	glMaterialfv   ( GL_FRONT, GL_AMBIENT,   ambient .rgba );
	glMaterialfv   ( GL_FRONT, GL_DIFFUSE,   diffuse .rgba );
	glMaterialfv   ( GL_FRONT, GL_SPECULAR,  specular.rgba );
	glMaterialfv   ( GL_FRONT, GL_EMISSION,  emission.rgba );
	glMaterialf    ( GL_FRONT, GL_SHININESS, shininess );
	glColorMaterial( GL_FRONT_AND_BACK, GL_DIFFUSE );
//	glHint         ( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
	glHint         ( GL_POLYGON_SMOOTH_HINT, GL_FASTEST );
//	glHint         ( GL_LINE_SMOOTH_HINT,    GL_NICEST );
	glHint         ( GL_LINE_SMOOTH_HINT, GL_FASTEST );
	setCull        ( 0 );

#	if !defined( USE_TINY_GL )
	if( hasExtension("GL_EXT_separate_specular_color") ){
		if( options.isEnabled(OPT_SEPARATE_SPECULAR_COLOR) ){
			glLightModeli( GL_LIGHT_MODEL_COLOR_CONTROL_EXT, GL_SEPARATE_SPECULAR_COLOR_EXT );
			dmsg( M_INIT, "GL_LIGHT_MODEL_COLOR_CONTROL_EXT set to GL_SEPARATE_SPECULAR_COLOR_EXT" );
		}
	}

	//  EXT_vertex_shader
	//  NV_vertex_program
	//	ATI_fragment_shader
	if( hasExtension("GL_ARB_vertex_program"               ) ) dmsg( M_INIT, "GL_ARB_vertex_program"   );
	if( hasExtension("GL_ARB_fragment_program"             ) ) dmsg( M_INIT, "GL_ARB_fragment_program" );
	if( hasExtension("GL_EXT_vertex_shader"                ) ) dmsg( M_INIT, "GL_EXT_vertex_shader"    );
	if( hasExtension("GL_NV_vertex_program"                ) ) dmsg( M_INIT, "GL_NV_vertex_program"    );
	if( hasExtension("GL_NV_fragment_program"              ) ) dmsg( M_INIT, "GL_NV_fragment_program"  );
	if( hasExtension("GL_ATI_fragment_shader"              ) ) dmsg( M_INIT, "GL_ATI_fragment_shader"  );

	if( hasExtension("GL_EXT_rescale_normal"            ) ) dmsg( M_INIT, "GL_EXT_rescale_normal" );
	if( hasExtension("GL_EXT_cull_vertex"               ) ) dmsg( M_INIT, "GL_EXT_cull_vertex" );
	if( hasExtension("SGIX_reference_plane"             ) ) dmsg( M_INIT, "SGIX_reference_plane" );
	if( hasExtension("GL_SGIX_reference_plane"          ) ) dmsg( M_INIT, "GL_SGIX_reference_plane" );
	if( hasExtension("GL_IBM_texture_mirrored_repeat"   ) ) dmsg( M_INIT, "GL_IBM_texture_mirrored_repeat" );
	if( hasExtension("GL_EXT_texture_filter_anisotropic") ) dmsg( M_INIT, "GL_EXT_texture_filter_anisotropic" );
	if( hasExtension("GL_ARB_texture_compression"       ) ) dmsg( M_INIT, "GL_ARB_texture_compression" );
	if( hasExtension("GL_EXT_texture_compression_s3tc"  ) ) dmsg( M_INIT, "GL_EXT_texture_compression_s3tc" );
/*
GL_EXT_separate_specular_color
GL_RESCALE_NORMAL
GL_EXT_cull_vertex
SGIX_reference_plane 
GL_IBM_texture_mirrored_repeat
GL_EXT_texture_filter_anisotropic (GL_TEXTURE_MAX_ANISOTROPY_EXT)
GL_ARB_texture_compression
GL_EXT_texture_compression_s3tc
*/

	dmsg( M_INIT, "OpenGL vendor:     %s", getVendor    () );
	dmsg( M_INIT, "OpenGL renderer:   %s", getRenderer  () );
	dmsg( M_INIT, "OpenGL version:    %s", getVersion   () );
	//dmsg( M_INIT, "\nOpenGL extensions: %s\n", getExtensions() );
	fprintf( stdout, "\nOpenGL extensions: %s\n", getExtensions() );
	check();

/*	{
		int   ext_name_len = strlen( ext_name );	
		char *p            = getExtensions();
		char *end          = p + strlen( p );

		while( p < end ){
			int n = strcspn( p, " " );
			if( (ext_name_len            == n ) && 
				(strncmp(ext_name, p, n) == 0 )    )
			{
				return true;
			}
			p += (n + 1);
		}
	}*/


	glLightModeli( GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE );
	glLightModeli( GL_LIGHT_MODEL_TWO_SIDE,     GL_FALSE );
	setBlendFunc ( GL_ONE, GL_ONE );
#	endif
	check();
}


//!  View::display() calls active->display();
/*static*/ void View::displayOne(){
	active->display();
}


/*!
	\brief Return aspect ratio of View
	\return Aspect ratio of View
*/
float View::getRatio(){
	return ratio;
}

int View::getFrames(){
	return frames;
}


float View::getLastFrame(){
	return last_frame;
}


float View::getFps(){
	return fps;
}


float View::getLastTime(){
	return last_time;
}


int View::getScreenWidth(){
	return screen_width;
}


int View::getScreenHeight(){
	return screen_height;
}


//!  Return viewport
/*GLint *View::getViewport(){
	return viewport;
    }*/


void View::setState( const int feature, const bool state ){
	if( state ){
		enable( feature );
	}else{
		disable( feature );
	}
}


/*!
	Set clear status.
	If clear status is true, each frame is cleared before
	the components are drawn. Otherwise it is not cleared.
*/
void View::setClear( bool clear ){
	this->clear = clear;
}


//!  Return clear status
bool View::getClear(){
	return this->clear;
}


bool View::getState( const int feature ){
	GLenum code = getCode( feature );

#	if defined( USE_TINY_GL )
	if( gl_feature[feature] == true ){
		return true;
	}else{
		return false;
	}
#	else

	if( glIsEnabled(code) == GL_TRUE ){
		if( gl_feature[feature] == true ){
			return true;
		}else{
			dmsg( M_GL, "OpenGL says %s is enabled", feature_to_str(feature) );
			dmsg( M_GL, "But I thought it was disabled!" );
			dmsg( M_GL, "Check use of attribute stack" );
			gl_feature[feature] = true;
			return true;
		}
	}
	if( glIsEnabled(code) == GL_FALSE ){
		if( gl_feature[feature] == false ){
			return false;
		}else{
			dmsg( M_GL, "OpenGL says %s is disabled", feature_to_str(feature) );
			dmsg( M_GL, "But I thought it was enabled!" );
			dmsg( M_GL, "Check use of attribute stack" );
			gl_feature[feature] = false;
			return false;
		}
	}

#	endif

	return false;
}


//!  Enable OpenGL feature - only if not already enabled
void View::enable( const int feature ){
	if( gl_feature[feature] == false ){
		gl_feature[feature] = true;
		dmsg( M_GL, "%s enabled", feature_to_str(feature) );
		GLenum code = getCode( feature );
		glEnable( code );
	}
}


//!  Disable OpenGL feature - only if not already disabled
void View::disable( const int feature ){
	if( gl_feature[feature] == true ){
		gl_feature[feature] = false;
		dmsg( M_GL, "%s disabled", feature_to_str(feature) );
		GLenum code = getCode( feature );
		glDisable( code );
//	}else{
//		cout << feature_to_str(feature) << " not disabled; already disabled" << endl;
	}
}


//!  Surface reshape callback function
/*virtual*/ void View::reshape( int w, int h ){
	glViewport( 0, 0, (GLsizei)w, (GLsizei)h );
	//glGetIntegerv( GL_VIEWPORT, viewport );
    ratio = (GLfloat)w/(GLfloat)h;
    size  = Vector2( w, h );
	window_manager->update();
	displayOne();
}


const Teddy::Maths::TVector2<int> &View::getSize() const {
	dmsg( M_WM, "view::getSize() = %d x %d", size[0], size[1] );
    return size;
}


void View::setWindowManager( WindowManager *wm ){
	this->window_manager = wm;
}


Matrix View::getOrthoMatrix( float left, float right, float bottom, float top, float nearval, float farval ){
	float  x;
	float  y;
	float  z;
	float  tx;
	float  ty;
	float  tz;
	Matrix ortho_matrix;

	x  =  2 / (right -left   );
	y  =  2 / (top   -bottom );
	z  = -2 / (farval-nearval);
	tx = -(right +left   ) / (right -left   );
	ty = -(top   +bottom ) / (top   -bottom );
	tz = -(farval+nearval) / (farval-nearval);

#	define M(row,col)	ortho_matrix.m[col][row]
	M(0,0) = x;  M(0,1) = 0;  M(0,2) = 0;  M(0,3) = tx;
	M(1,0) = 0;  M(1,1) = y;  M(1,2) = 0;  M(1,3) = ty;
	M(2,0) = 0;  M(2,1) = 0;  M(2,2) = z;  M(2,3) = tz;
	M(3,0) = 0;  M(3,1) = 0;  M(3,2) = 0;  M(3,3) =  1;
#	undef M

	return ortho_matrix;
}

//!  View interface - Prepare Area for rendering 2D graphics
/*virtual*/ void View::begin2d(){
	check();
	Matrix om = getOrthoMatrix( 0, size[0], size[1], 0, 0.0f, 1.0f );

	disable            ( LIGHTING   );
	disable            ( DEPTH_TEST );
	disable            ( CULL_FACE  );
	disable            ( BLEND      );
	glViewport         ( 0, 0, size[0], size[1] );
	color              ( C_WHITE );
	setPolygonMode     ( GL_FILL );
	setProjectionMatrix( om );
	setModelViewMatrix ( Matrix::IDENTITY );
	//glTranslatef( 0.375, 0.375, 0.0 );
	check();
}


//!  View interface - End rendering 2D graphics
/*virtual*/ void View::end2d(){
}


//!  View interface - Prepare Area for rendering 3D graphics
void View::begin3d(){
}


//!  View interface - End rendering 3D graphics
void View::end3d(){
}


//!  Set gl polygon mode
void View::setPolygonMode( const unsigned int polygon_mode ){
	if( gl_polygon_mode != polygon_mode ){
		gl_polygon_mode = polygon_mode;

#		ifdef GRAPHICS_STATE_DEBUG
		if( polygon_mode == GL_FILL ){
			dmsg( M_GL, "polygon mode fill" );
		}else if( polygon_mode == GL_LINE ){
			dmsg( M_GL, "polygon mode line" );
		}else if( polygon_mode == GL_POINTS ){
			dmsg( M_GL, "polygon mode points" );
		}else{
			dmsg( M_GL, "unknown polygon mode \d ", (int)(polygon_mode) );
		}
#		endif

		glPolygonMode( GL_FRONT_AND_BACK, polygon_mode );
	}
}


//!  Set gl shade model
void View::setShadeModel( const unsigned int shade_model ){
	if( gl_shade_model != shade_model ){
		gl_shade_model = shade_model;
		glShadeModel( shade_model );
	}
}


//!  Set blending function
void View::setBlendFunc( const unsigned int sfactor, const unsigned int dfactor ){
#if !defined( USE_TINY_GL )
	if( gl_blend_source_factor      != sfactor ||
		gl_blend_destination_factor != dfactor    )
	{
		gl_blend_source_factor      = sfactor;
		gl_blend_destination_factor = dfactor;
		glBlendFunc( sfactor, dfactor );
	}
#endif
}


//!  Set fog mode
void View::setFogMode( const unsigned int mode ){
#	if !defined( USE_TINY_GL )
	if( gl_fog_mode != mode ){
		gl_fog_mode = mode;
		glFogi( GL_FOG_MODE, mode );
	}
#	endif
}


//!  Set fog color
void View::setFogColor( float *color ){
#	if !defined( USE_TINY_GL )
	glFogfv( GL_FOG_COLOR, color );
#	endif
}


//!  Set fog start
void View::setFogStart( float start ){
#	if !defined( USE_TINY_GL )
	if( gl_fog_start != start ){
		gl_fog_start = start;
		glFogf( GL_FOG_START, start );
	}
#	endif
}


//!  Set fog end
void View::setFogEnd( float end ){
#	if !defined( USE_TINY_GL )
	glFogf( GL_FOG_END, end );
#	endif
}


//!  Check if there are any OpenGL errors.
/*static*/ void View::check(){
#	if !defined( USE_TINY_GL )
	int e;

	e = glGetError();
	switch( e ){
	case GL_NO_ERROR: break;
    case GL_INVALID_VALUE:     emsg( M_GL, "OpenGL error: Invalid value" );     break;
    case GL_INVALID_ENUM:      emsg( M_GL, "OpenGL error: Invalid enum" );      break;
    case GL_INVALID_OPERATION: emsg( M_GL, "OpenGL error: Invalid operation" ); break;
    case GL_STACK_OVERFLOW:    emsg( M_GL, "OpenGL error: Stack overflow" );    break;
    case GL_STACK_UNDERFLOW:   emsg( M_GL, "OpenGL error: Stack underflow" );   break;
    case GL_OUT_OF_MEMORY:     emsg( M_GL, "OpenGL error: Out of memory" );     break;
	default: emsg( M_GL, "Unknown OpenGL error" ); break;
	}
#	endif
}


//!  Access sdl surface directly
SDL_Window *View::getWindow(){
	return sdl_window;
}


void View::printExtensions(){
}

//!  Is the extension supported?
bool View::hasExtension( const char *ext_name ){
	int   ext_name_len = strlen( ext_name );
	const char *p = getExtensions();
	if( p == NULL ){
        return false;
	}
	const char *end = p + strlen( p );

	while( p < end ){
		int n = strcspn( p, " " );
		if( (ext_name_len            == n ) && 
		    (strncmp(ext_name, p, n) == 0 )    )
		{
			return true;
		}
		p += (n + 1);
	}
	return false;
}


};  //  namespace Graphics
};  //  namespace Teddy

