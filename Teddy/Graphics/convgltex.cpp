
/*!
	\file
	\brief  SDL surface conversion to OpenGL texture formats
	\author Mattias Engdeg�rd
	
	Use, modification and distribution of this source is allowed
	without limitation, warranty or liability of any kind.
*/


#include "Teddy/TeddyConfig.h"
#include <SDL.h>
#ifdef HAVE_LIB_SDL_IMAGE
#	include <SDL_image.h>
#endif
#include <cstring>


/*!
	\brief Convert surface for OpenGL
	\bug   Crashes with some tga images if SDL_FreeSurface(s) is enabled

	Convert a surface into one suitable as an OpenGL texture;
	in RGBA format if want_alpha is nonzero, or in RGB format otherwise.
	
	The surface may have a colourkey, which is then translated to an alpha
	channel if RGBA is desired.
	
	Return the resulting texture, or NULL on error. The original surface is
	always freed.
*/
SDL_Surface *conv_surf_gl( SDL_Surface *s, int want_alpha ){
    Uint32       rmask;
	Uint32       gmask;
	Uint32       bmask;
	Uint32       amask;
    SDL_Surface *conv;
    int          bpp = want_alpha ? 32 : 24;

    //  SDL interprets each pixel as a 24 or 32-bit number, so our
    //  masks must depend on the endianness (byte order) of the
    //  machine.
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000 >> (32 - bpp);
    gmask = 0x00ff0000 >> (32 - bpp);
    bmask = 0x0000ff00 >> (32 - bpp);
    amask = 0x000000ff >> (32 - bpp);
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = want_alpha ? 0xff000000 : 0;
#endif

    //  Check if the surface happens to be in the right format
    if(
		(s->format->BitsPerPixel == bpp  ) &&
		(s->format->Rmask        == rmask) &&
		(s->format->Gmask        == gmask) &&
		(s->format->Bmask        == bmask) &&
		(s->format->Amask        == amask) 
		/*!(s->flags & SDL_SRCCOLORKEY)*/ )
	{
		//  No conversion needed
		return s;
    }

    //  Wrong format, conversion necessary

    //  SDL surfaces are created with lines padded to start at 32-bit boundaries
    //  which suits OpenGL well (as long as GL_UNPACK_ALIGNMENT remains
    //  unchanged from its initial value of 4)
    conv = SDL_CreateRGBSurface(
		SDL_SWSURFACE, 
		s->w, 
		s->h, 
		bpp,
		rmask, 
		gmask, 
		bmask, 
		amask
	);
    if( !conv ){
		SDL_FreeSurface( conv );
		return NULL;
    }

	//  SDL sets the SDL_SRCALPHA flag on all surfaces with an
	//  alpha channel. We need to clear that flag for the copy,
	//  since SDL would attempt to alpha-blend our image otherwise */
    // SDL1: if( want_alpha ){
	// SDL1: 	SDL_SetAlpha( s, 0, 255 );
    // SDL1: }
    SDL_SetSurfaceBlendMode(s, SDL_BLENDMODE_NONE); // SDL2

    //  Do the conversion. If the source surface has a colourkey, then it
    //  will be used in the blit. We use the fact that newly created software
    //  surfaces are zero-filled, so the pixels not blitted will remain
    //  transparent.
    if( SDL_BlitSurface(s,NULL,conv,NULL) < 0 ){
		//  Blit error
		SDL_FreeSurface( conv );
		conv = NULL;
    }

	//tksuoran: This causes to crash with some images
	//SDL_FreeSurface(s);

    return conv;
}


/*!
	A sample use of conv_surf_gl():

	Load an image from a file, and convert it to RGB or RGBA format,
	depending on the image.

	Return the resulting surface, or NULL on error
*/
SDL_Surface *load_gl_texture( const char *file ){
#ifdef HAVE_LIB_SDL_IMAGE
	SDL_Surface *s = IMG_Load(file);
#else
    SDL_Surface *s = NULL;
#endif
    if( s==NULL ){
		return NULL;
	}
    //return conv_surf_gl(s, s->format->Amask || (s->flags & SDL_SRCCOLORKEY));
    return conv_surf_gl(s, s->format->Amask);
}

