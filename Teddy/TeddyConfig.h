#ifndef TEDDY_CONFIG_H
#define TEDDY_CONFIG_H

/* Define if you have the ANSI C header files.  */
#define STDC_HEADERS 1

/* Define if you have the SDL_JoystickOpen function.  */
#undef HAVE_SDL_JOYSTICKOPEN

/* Library name */
#define LIB_NAME Teddy

/* Library version */
#define LIB_VERSION 1.0

/* Release version */
#define LIB_RELEASE 2.0

/* Define if Lightwave code is to be included. */
#define TEDDY_INCLUDE_LW_SCENE 1

/* Define if SDL_image library is available. */
#define HAVE_LIB_SDL_IMAGE 1

/* Define if png library is available. */
#define HAVE_LIB_PNG 1

/* Define if native OpenGL is being used. */
#define USE_OPEN_GL 1


#endif
