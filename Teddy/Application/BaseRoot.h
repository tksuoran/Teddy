
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

	$Id:  $
*/


#ifndef TEDDY__APPLICATION__BASE_ROOT__H
#define TEDDY__APPLICATION__BASE_ROOT__H


#include "Teddy/MixIn/Options.h"
;


namespace Teddy       {
namespace Application {


//!  Program root
class BaseRoot {
public:
	BaseRoot();
    virtual ~BaseRoot();

	void                   start            ( int argc, char **argv );
	virtual void           setDefaultOptions();
	virtual void           parseOptions     ();

	int                    getScreenWidth   ();
	int                    getScreenHeight  ();
	Teddy::MixIn::Options &getScreenOptions ();
	Teddy::MixIn::Options &getAudioOptions  ();
	bool                   hasOpt           ( const char *key );
	const char            *getOptString     ( const char *key );
	int                    getOptInt        ( const char *key );
	float                  getOptFloat      ( const char *key );
	const char            *getArg           ( int   i );

protected:
	int                     argc;
	char                  **argv;
	Teddy::MixIn::Options   screen_options;
	Teddy::MixIn::Options   audio_options;
	int                     screen_width;
	int                     screen_height;
};


};  //  namespace Application
};  //  namespace Teddy


#if !defined( __MINGW32__ )	&& !defined(_MSC_VER)

#define TEDDY_MAIN                     \
extern "C" {                           \
	int main( int argc, char **argv ){ \
		Root *root = new Root();       \
        root->start( argc, argv );     \
        return 0;                      \
	}                                  \
}

#else

#define TEDDY_MAIN                     \
extern "C" {                           \
	int SDL_main( int argc, char **argv ){ \
		Root *root = new Root();       \
        root->start( argc, argv );     \
        return 0;                      \
	}                                  \
}

#endif

#endif  //  TEDDY__APPLICATION__BASE_ROOT__H


