
---- Notice for MingW ----


I have succesfully built Teddy and Teddy executables on MingW with
MSys environment. For more information about mingw and msys, see
http://www.mingw.org/

I installed the following mingw packages:
	  
	MingW-2.0.0-3.exe
	MSYS-1.0.8-2002-09-08-1.exe
	libjpeg-6b-1.zip
	libpng-1.0.6-20000724.zip
	libpng-devel-1.0.6-20000724.zip
	libpng-utils-1.0.6-20000724.zip
	libtiff-3.4-1.zip
	libtiff-devel-3.4-1.zip
	zlib-1.1.3-1.zip

Then in MSys I configure, make, make installed the following

	freetype-2.1.2.tar.gz (*)
	SDL-1.2.5.tar.gz
	(**)
	SDL_image-1.2.2.tar.gz
	SDL_mixer-1.2.4.tar.gz

Notice that (*) you should build freetype yourself and not use some
freetype package. At the time I installed my msys there was no
native msys package of freetype, and the package I found from the
net did NOT work correctly with msys.

Strictly speaking freetype is not yet required by Teddy, so you
might be able to make teddy build even without it.

Notice that at (**) point you will have to edit the /etc/profile
and close and reopen MSys shell so that the SDL.DLL is found by the
MSys as it was installed. The relevant part of the profile should be:

# My decision to add a . to the PATH and as the first item in the path list
# is to mimick the Win32 method of finding executables.
#
# I filter the PATH value setting in order to get ready for self hosting the
# MSYS runtime and wanting different paths searched first for files.
if [ $MSYSTEM == MINGW32 ]; then
  export PATH=".:/usr/local/bin:/usr/local/lib:/mingw/bin:/bin:$PATH"
else
  export PATH=".:/usr/local/bin:/usr/local/lib:/bin:/mingw/bin:$PATH"
fi

Notice the addition of /usr/local/lib to the PATH. This is where SDL.dll
is kept in MSys.
