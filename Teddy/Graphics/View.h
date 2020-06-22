
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


#ifndef TEDDY__GRAPHICS__VIEW__H
#define TEDDY__GRAPHICS__VIEW__H


#include "Teddy/Maths/Matrix.h"
#include "Teddy/Maths/Vector2.h"
#include "Teddy/Maths/Vector.h"
#include "Teddy/Maths/Rect.h"
#include "Teddy/MixIn/Options.h"
#include "Teddy/Graphics/Color.h"
#include "Teddy/Graphics/Device.h"
#include "Teddy/SysSupport/StdSDL.h"
#ifdef HAVE_LIB_PNG
# include <png.h>
#endif


//  Forward declarations
namespace Teddy {
	namespace PhysicalComponents { class Layer;         };
	namespace PhysicalComponents { class WindowManager; };
};
struct SDL_Window;


namespace Teddy    {
namespace Graphics {


class Color;
class Font;
class Texture;


/*!
	\brief Root drawing device (context)

	View is a low level graphics device. A View must be
	created before any graphics related functions can be
	used.
*/
class View {
public:
	static const int OPT_FRAME;
	static const int OPT_FULLSCREEN;
	static const int OPT_MULTI_WINDOW;
	static const int OPT_SEPARATE_SPECULAR_COLOR;
	static const int OPT_FONT_FIX;

	static const unsigned long CULL_FACE     ;
	static const unsigned long BLEND         ;
	static const unsigned long FOG           ;
	static const unsigned long NORMALIZE     ;
	static const unsigned long ALPHA_TEST    ;
	static const unsigned long DEPTH_TEST    ;
	static const unsigned long STENCIL_TEST  ;
	static const unsigned long SCISSOR_TEST  ;
	static const unsigned long TEXTURE_1D    ;
	static const unsigned long TEXTURE_2D    ;
	static const unsigned long POINT_SMOOTH  ;
	static const unsigned long LINE_SMOOTH   ;
	static const unsigned long POLYGON_SMOOTH;
	static const unsigned long POINT_OFFSET  ;
	static const unsigned long LINE_OFFSET   ;
	static const unsigned long POLYGON_OFFSET;
	static const unsigned long LIGHTING      ;
	static const unsigned long LIGHT0        ;
	static const unsigned long LIGHT1        ;
	static const unsigned long LIGHT2        ;
	static const unsigned long LIGHT3        ;
	static const unsigned long LIGHT4        ;
	static const unsigned long LIGHT5        ;
	static const unsigned long LIGHT6        ;
	static const unsigned long LIGHT7        ;
	static const unsigned long COLOR_MATERIAL;

	static void          init();
	static const char   *feature_to_str( int a );
	static unsigned int  getCode(unsigned int a);

private:
	static unsigned int  feature_to_code[256];


public:
    View( int width, int height, Teddy::MixIn::Options options );

	//  View Interface
	void    reshape            ( int w, int h );
	void    display            ();
    void    displayPs          ( const char *filename );

    const Teddy::Maths::TVector2<int> &getSize      () const;
	float                        getRatio           ();
	int                          getFrames          ();
	float                        getLastFrame       ();
	float                        getFps             ();
	float                        getFpsTime         ();
	float                        getLastTime        ();

    void                  setWindowManager   ( Teddy::PhysicalComponents::WindowManager *wm );
    Teddy::Maths::Matrix  getOrthoMatrix     ( float left, float right, float bottom, float top, float nearval, float farval );

	void    setProjectionMatrix();  //!<  Set projection matrix to identity
	void    setProjectionMatrix( const Teddy::Maths::Matrix  &m );
	void    setModelViewMatrix ();  //!<  Set modelview matrix to identity
	void    setModelViewMatrix ( const Teddy::Maths::Matrix  &m );
	void    setTextureMatrix   ( const Teddy::Maths::Matrix  &m );
	void    setTexture         ( Texture *t );
	void    setCull            ( unsigned long dir );

	void    beginPoints        ();
	void    beginLines         ();
	void    beginLineStrip     ();
	void    beginLineLoop      ();
	void    beginTriangles     ();
	void    beginTriangleStrip ();
	void    beginTriangleFan   ();
	void    beginQuads         ();
	void    beginQuadStrip     ();
	void    beginPolygon       ();
	void    end                ();

    void    vertex             ( const Teddy::Maths::TVector<float>  &v, const Teddy::Maths::TVector2<float> &t ) const;
	void    vertex             ( const Teddy::Maths::TVector2<float> &v, const Teddy::Maths::TVector2<float> &t ) const;
	void    vertex             ( const float x, const float y ) const;

	void    vertex             ( const Teddy::Maths::TVector <int>    &v ) const;
	void    vertex             ( const Teddy::Maths::TVector <float>  &v ) const;
	void    vertex             ( const Teddy::Maths::TVector <double> &v ) const;
	void    vertex             ( const Teddy::Maths::TVector2<int>    &v ) const;
	void    vertex             ( const Teddy::Maths::TVector2<float>  &v ) const;
	void    vertex             ( const Teddy::Maths::TVector2<double> &v ) const;
	void    normal             ( const Teddy::Maths::TVector <int>    &n ) const;
	void    normal             ( const Teddy::Maths::TVector <float>  &n ) const;
	void    normal             ( const Teddy::Maths::TVector <double> &n ) const;
	void    normal             ( const Teddy::Maths::TVector2<int>    &n ) const;
	void    normal             ( const Teddy::Maths::TVector2<float>  &n ) const;
	void    normal             ( const Teddy::Maths::TVector2<double> &n ) const;
	void    texture            ( const Teddy::Maths::TVector <int>    &t ) const;
	void    texture            ( const Teddy::Maths::TVector <float>  &t ) const;
	void    texture            ( const Teddy::Maths::TVector <double> &t ) const;
	void    texture            ( const Teddy::Maths::TVector2<int>    &t ) const;
	void    texture            ( const Teddy::Maths::TVector2<float>  &t ) const;
	void    texture            ( const Teddy::Maths::TVector2<double> &t ) const;
	void    color              ( const float r, const float g, const float b, const float a = 1 ) const;
	void    color              ( const Color &c ) const;
	void    begin2d            ();
	void    end2d              ();

	void	    printExtensions    ();
	bool        hasExtension       ( const char *ext_name );
	const char *getExtensions      ();
	const char *getVendor          ();
	const char *getRenderer        ();
	const char *getVersion         ();
	int         getMaxTextureSize  ();
	int         getMaxLights       ();
	Teddy::Maths::TVector<int>  getMaxViewportDims ();

	void    drawString         ( const Teddy::Maths::TVector2<float> &pos, const char *str, Font *font );  // const?
	void    drawRect           ( const float x1, const float y1, const float x2, const float y2 );
	void    drawFillRect       ( const float x1, const float y1, const float x2, const float y2 );
	void    drawBiColRect      ( const float x1, const float y1, const float x2, const float y2, const Color &top_left, const Color &bottom_right );
	void    blit               ( const Teddy::Maths::TVector2<float> &pos, Texture *t );

	void    setClear           ( bool clear );
	void    setClearColor      ( const Color &clear_color );
	bool    getClear           ();
	void    begin3d            ();
	void    end3d              ();
	void    setState           ( const  int           feature, const bool  state );
	bool    getState           ( const  int           feature );
	void    enable             ( const  int           feature );
	void    disable            ( const  int           feature );
	void    setPolygonMode     ( const  unsigned int  polygon_mode );
	void    setShadeModel      ( const  unsigned int  shade_model );
	void    setFrontFace       ( const  unsigned int  front_face );
	void    setBlendFunc       ( const  unsigned int  sfactor, const unsigned int dfactor );
	void    setClearDepth      ( const  float         depth );
	void    setFogStart        ( const  float         start );
	void    setFogEnd          ( const  float         end );
	void    setFogMode         ( const  unsigned int  mode );
	void    setFogColor        ( float               *color );

    int     getScreenWidth();
    int     getScreenHeight();

	bool                   pngScreenshot   ( const char * const filename );
	SDL_Window            *getWindow       ();
	Teddy::MixIn::Options &getOptions      (){ return options; }

	static void  check           ();
#if defined( HAVE_LIB_PNG )
	static void  pngUserWriteData( png_structp png_ptr, png_bytep data, png_size_t length );
	static void  pngUserFlushData( png_structp png_ptr );
#endif

protected:
	Teddy::MixIn::Options                     options;
    SDL_Window                               *sdl_window;
    SDL_GLContext                             sdl_gl_context;
    Teddy::PhysicalComponents::WindowManager *window_manager;
    Texture                                  *current_texture;
    Teddy::Maths::TVector2<int>               size;
	int            current_element;
	int            current_matrix_mode;
    float          ratio;
	bool           clear;
	Color          clear_color;
	unsigned int   gl_blend_source_factor;
	unsigned int   gl_blend_destination_factor;
	unsigned int   gl_fog_mode;
	unsigned int   gl_polygon_mode;
	unsigned int   gl_shade_model;
	float          gl_fog_start;
	float          gl_fog_end;
	float          gl_fog_color[4];
	float          gl_clear_depth;
	bool           gl_feature[256];
	int            frames;
	unsigned long  last_frame;
	unsigned long  last_time;
	unsigned long  last_fps;
	float          fps;
	int            screen_width;
	int            screen_height;

protected:
    static View *active;
	static FILE *fp;      //!<  For png screenshot writer

	static void  displayOne  ();
	static void  reshapeOne  ( int w, int h );
};


};  //  namespace Graphics
};  //  namespace Teddy


#endif  //  TEDDY__GRAPHICS__VIEW__H

