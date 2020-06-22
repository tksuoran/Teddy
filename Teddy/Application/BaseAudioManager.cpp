
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


#include "Teddy/TeddyConfig.h"
#include "Teddy/Application/BaseAudioManager.h"
#include "Teddy/Application/BaseRoot.h"
#include "Teddy/SysSupport/Messages.h"
#include "Teddy/SysSupport/StdIO.h"
using namespace Teddy::SysSupport;
using namespace Teddy::MixIn;


#if defined( HAVE_LIB_SDL_MIXER ) && !defined( DISABLE_AUDIO )

# include "SDL_mixer.h"
# if defined( _MSC_VER )
#  if defined( _DEBUG )
#   pragma comment (lib, "SDL_mixerD.lib")
#  else
#   pragma comment (lib, "SDL_mixer.lib")
#  endif
# endif


#else
# include "Teddy/SysSupport/StdIO.h"
#endif


namespace Teddy       {
namespace Application {


const int BaseAudioManager::OPT_MASTER  = (1ul<<1ul);  //  unused
const int BaseAudioManager::OPT_SAMPLES = (1ul<<2ul);
const int BaseAudioManager::OPT_MIDI    = (1ul<<3ul);
const int BaseAudioManager::OPT_CD      = (1ul<<4ul);  //  unused


BaseAudioManager::BaseAudioManager( const Options &options )
:
options(options)
{
/*
#	if defined( _WIN32 ) && !defined( DISABLE_AUDIO )
	if( this->options.isEnabled(OPT_MIDI) == true ){
		::native_midi_init();
		msg( "native_midi_loadsong..." );
		char *mus_fname = "audio/adblue.mid";
		NativeMidiSong *music = ::native_midi_loadsong( mus_fname );
		if( music != NULL ){
			::native_midi_start( music );
		}else{
			msg( M_AUDIO, "Could not load %s", mus_fname );
		}
	}
#	endif
*/
#	if defined( HAVE_LIB_SDL_MIXER ) && !defined( DISABLE_AUDIO )
//	signal( SIGINT,  exit );
//	signal( SIGTERM, exit );

	/* Open the audio device */
	if( Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) < 0 ){
		emsg( M_AUDIO, MSG_HEAD "Couldn't open audio: %s", SDL_GetError() );
		return;
	}else{
//		Mix_QuerySpec( &audio_rate, &audio_format, &audio_channels );
/*		printf(
			"Opened audio at %d Hz %d bit %s\n",
			audio_rate,
			(audio_format&0xFF),
			(audio_channels > 1) ? "stereo" : "mono"
		);*/
	}

#	else
	dmsg( M_AUDIO, "%s", "SDL_mixer was not available when built - Audio disabled" );
#	endif
}


void BaseAudioManager::playWav( void *chunk ){
#	if defined( HAVE_LIB_SDL_MIXER ) && !defined( DISABLE_AUDIO )
	if( options.isEnabled(OPT_SAMPLES) == true ){
		Mix_PlayChannel( -1, (Mix_Chunk*)chunk, 0 );
	}else{
	}
#	endif
}


Options &BaseAudioManager::getOptions(){
	return options;
}


};  //  namespace SpaceGame
};  //  namespace Teddy

