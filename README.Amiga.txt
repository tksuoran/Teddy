
---- Notice for Amiga ----

I had to do some manual modifications to Makefile to make
this to build on amiga:

- change Teddy/TeddyConfig.h so that it has
  #define USE_OPEN_GL 1
  (Hmm, I actually had a BUG there in the version which I
   compiled, I wonder what that affected..)
- remove Teddy/TinyGL from teddy makefile SOURCE_DIRS
- remove -fPIC from CFLAGS and CXXFLAGS for teddy Makefile
- remove -include .depend from teddy and teddytests Makefiles
  (shortens compile time)
  
- if you get undefined symbols during linking, rearrange
  the libs in the link command line (in Makefile) so that
  first there is SDL_image, SDL_mixer, SDL, then others,
  and last -ljpeg -lpng -lz.. something like that. Plus that
  first try that all libs are only listed once. If that doesn't
  help then try listing some libs again to the end of the list.
  If there is undefined symbol to pthreads atexit, try commenting
  out atexit call (DIRTY)
  
There might have been others, but I don't remember now, sorry..

