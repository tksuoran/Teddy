
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


#if defined( _WIN32 ) && defined(_MSC_VER)
# include <windows.h>
# include <io.h>
# include <fcntl.h>
#endif
#include "Teddy/TeddyConfig.h"
#include "Teddy/Application/BaseAudioManager.h"
#include "Teddy/Application/BaseRoot.h"
#include "Teddy/Graphics/View.h"
#include "Teddy/Materials/Material.h"
#include "Teddy/SysSupport/Messages.h"
#include "Teddy/Teddy.h"
#include "Teddy/SysSupport/StdSDL.h"
#ifndef SWIG
#include <cstdlib>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#endif
using namespace Teddy::SysSupport;
using namespace Teddy::Graphics;


namespace Teddy       {
namespace Application {


BaseRoot::BaseRoot(){
}


/*virtual*/ BaseRoot::~BaseRoot(){
}


/*virtual*/ void BaseRoot::start( int argc, char **argv ){
	this->argc = argc;
    this->argv = argv;
	init_msg         ();
	setDefaultOptions();
	parseOptions     ();

#	if defined(_WIN32) && defined(_MSC_VER) //&& defined(DEBUG_CONSOLE)
	if( hasOpt("--con") ){
		int hCrt;
		FILE *hf;

		AllocConsole();
		hCrt = _open_osfhandle(
			(long) GetStdHandle(STD_OUTPUT_HANDLE),
			_O_TEXT
		);
		hf = _fdopen( hCrt, "w" );
		*stdout = *hf;
		setvbuf( stdout, NULL, _IONBF, 0 );
	}
#	endif

	unsigned long sdl_init_flags = 0;
	sdl_init_flags |= SDL_INIT_VIDEO;
	sdl_init_flags |= SDL_INIT_AUDIO;
	sdl_init_flags |= SDL_INIT_TIMER;
	sdl_init_flags |= SDL_INIT_NOPARACHUTE;
#if defined( HAVE_SDL_JOYSTICKOPEN )
	sdl_init_flags |= SDL_INIT_JOYSTICK;
#endif

	if( SDL_Init(sdl_init_flags) < 0 ){
		fmsg( M_FATAL, MSG_HEAD "Unable to initialize SDL: %s\n", SDL_GetError() );
    }else{
        //  This caused undefined symbol on Amiga once,
        //  that time I simply commented it out, dirty..
		atexit( SDL_Quit );
	}

	Teddy::Materials::Material::init();  //  Initialize high-level graphics features
	Teddy::Graphics ::View    ::init();  //  Initialize graphics features

}


/*virtual*/ void BaseRoot::setDefaultOptions(){
	screen_width  = 640;
	screen_height = 480;

	screen_options.setOptions( View::OPT_FRAME | View::OPT_MULTI_WINDOW | View::OPT_SEPARATE_SPECULAR_COLOR );
#if !defined( DISABLE_AUDIO )
	audio_options .setOptions( BaseAudioManager::OPT_SAMPLES );
#else
	audio_options .setOptions( 0 );
#endif

}


/*virtual*/ void BaseRoot::parseOptions(){
	if( hasOpt("--width")            ) screen_width  = getOptInt("--width");
	if( hasOpt("--height")           ) screen_height = getOptInt("--height");
	if( hasOpt("--fullscreen")       ) screen_options.enable ( View::OPT_FULLSCREEN   );
	if( hasOpt("--no-fullscreen")    ) screen_options.disable( View::OPT_FULLSCREEN   );
	if( hasOpt("--multi-window")     ) screen_options.enable ( View::OPT_MULTI_WINDOW );
	if( hasOpt("--no-multi-window")  ) screen_options.disable( View::OPT_MULTI_WINDOW );
	if( hasOpt("--frame")            ) screen_options.enable ( View::OPT_FRAME        );
	if( hasOpt("--no-frame")         ) screen_options.disable( View::OPT_FRAME        );
	if( hasOpt("--ssc")              ) screen_options.enable ( View::OPT_SEPARATE_SPECULAR_COLOR );
	if( hasOpt("--no-ssc")           ) screen_options.disable( View::OPT_SEPARATE_SPECULAR_COLOR );
	if( hasOpt("--font-fix")         ) screen_options.enable ( View::OPT_FONT_FIX );
	if( hasOpt("--no-font-fix")      ) screen_options.disable( View::OPT_FONT_FIX );

#if !defined( DISABLE_AUDIO )
	if( hasOpt("--audio-samples")    ) audio_options.enable  ( BaseAudioManager::OPT_SAMPLES );
	if( hasOpt("--no-audio-samples") ) audio_options.disable ( BaseAudioManager::OPT_SAMPLES );
	if( hasOpt("--audio-midi")       ) audio_options.enable  ( BaseAudioManager::OPT_MIDI    );
	if( hasOpt("--no-audio-midi")    ) audio_options.disable ( BaseAudioManager::OPT_MIDI    );
#endif

	if( hasOpt("--debug-init") ) enable_msg ( M_INIT  );
	if( hasOpt("--debug-gl"  ) ) enable_msg ( M_GL    );
	if( hasOpt("--debug-wm"  ) ) enable_msg ( M_WM    );
	if( hasOpt("--debug-wmd" ) ) enable_msg ( M_WMD   );
	if( hasOpt("--debug-wme" ) ) enable_msg ( M_WME   );
	if( hasOpt("--debug-wml" ) ) enable_msg ( M_WML   );
	if( hasOpt("--debug-mat" ) ) enable_msg ( M_MAT   );
	if( hasOpt("--debug-mod" ) ) enable_msg ( M_MOD   );
	if( hasOpt("--debug-lwo" ) ) enable_msg ( M_LWO   );
	if( hasOpt("--debug-lws" ) ) enable_msg ( M_LWS   );
	if( hasOpt("--debug-tmap") ) enable_msg ( M_TMAP  );
	if( hasOpt("--debug-vert") ) enable_msg ( M_VERT  );
	if( hasOpt("--debug-ffe" ) ) enable_msg ( M_FFE   );
	if( hasOpt("--debug-net" ) ) enable_msg ( M_NET   );
	if( hasOpt("--debug-scn" ) ) enable_msg ( M_SCN   );
	if( hasOpt("--debug-aud" ) ) enable_msg ( M_AUDIO );

	if( hasOpt("--no-debug-init") ) disable_msg ( M_INIT  );
	if( hasOpt("--no-debug-gl"  ) ) disable_msg ( M_GL    );
	if( hasOpt("--no-debug-wm"  ) ) disable_msg ( M_WM    );
	if( hasOpt("--no-debug-wmd" ) ) disable_msg ( M_WMD   );
	if( hasOpt("--no-debug-wme" ) ) disable_msg ( M_WME   );
	if( hasOpt("--no-debug-wml" ) ) disable_msg ( M_WML   );
	if( hasOpt("--no-debug-mat" ) ) disable_msg ( M_MAT   );
	if( hasOpt("--no-debug-mod" ) ) disable_msg ( M_MOD   );
	if( hasOpt("--no-debug-lwo" ) ) disable_msg ( M_LWO   );
	if( hasOpt("--no-debug-lws" ) ) disable_msg ( M_LWS   );
	if( hasOpt("--no-debug-tmap") ) disable_msg ( M_TMAP  );
	if( hasOpt("--no-debug-vert") ) disable_msg ( M_VERT  );
	if( hasOpt("--no-debug-ffe" ) ) disable_msg ( M_FFE   );
	if( hasOpt("--no-debug-net" ) ) disable_msg ( M_NET   );
	if( hasOpt("--no-debug-scn" ) ) disable_msg ( M_SCN   );
	if( hasOpt("--no-debug-aud" ) ) disable_msg ( M_AUDIO );
}


Options &BaseRoot::getAudioOptions(){
	return audio_options;
}


Options &BaseRoot::getScreenOptions(){
	return screen_options;
}


const char *BaseRoot::getOptString( const char *key ){
	const char *val = "";
	for( int i=1; i<argc; i++ ){
		if( strcmp(argv[i],key) == 0 ){
			if( argc > i+1 ){
				val = argv[i+1];
			}
		}
	}
	return val;
}


int BaseRoot::getOptInt( const char *key ){
	int i_val = 0;
	for( int i=1; i<argc; i++ ){
		if( strcmp(argv[i],key) == 0 ){
			if( argc > i+1 ){
				i_val = atoi( argv[i+1] );
			}
		}
	}
	return i_val;
}


float BaseRoot::getOptFloat( const char *key ){
	float f_val = 0;
	for( int i=1; i<argc; i++ ){
		if( strcmp(argv[i],key) == 0 ){
			if( argc > i+1 ){
				f_val = float(  atof( argv[i+1] )  );
			}
		}
	}
	return f_val;
}


const char *BaseRoot::getArg( int i ){
	return ( argc>=i ) ? argv[i] : "";
}


bool BaseRoot::hasOpt( const char *key ){
	for( int i=1; i<argc; i++ ){
		if( strcmp(argv[i],key) == 0 ){
			return true;
		}
	}
	return false;
}


int BaseRoot::getScreenWidth(){
	return screen_width;
}


int BaseRoot::getScreenHeight(){
	return screen_height;
}


};  //  namespace Application
};  //  namespace Teddy

