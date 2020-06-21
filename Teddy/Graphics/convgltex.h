/*
 * SDL surface conversion to OpenGL texture formats
 *
 * Mattias Engdegård
 *
 * Use, modification and distribution of this source is allowed without
 * limitation, warranty or liability of any kind.
 */


#ifndef CONV_GL_TEX_H
#define CONV_GL_TEX_H


struct SDL_Surface;

extern SDL_Surface *conv_surf_gl   ( SDL_Surface *s, int want_alpha );
extern SDL_Surface *load_gl_texture( const char *file );


#endif  //  CONV_GL_H


