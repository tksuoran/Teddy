
/*
	TSGL - Teddy Space Game Library
	Copyright (C) 2002 Timo Suoranta
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


#ifndef SPACE_GAME__ROOT__H
#define SPACE_GAME__ROOT__H


#include "Teddy/Application/BaseRoot.h"


//  Forward declarations
namespace Teddy {
	namespace Application { class BaseAudioManager;    };
	namespace Application { class BaseSimulationTimer; };
};
using Teddy::Application::BaseAudioManager;
using Teddy::Application::BaseSimulationTimer;


class ActionManager;
class ObjectManager;
class UserInterface;


//!  Application Root
//!  Inherit from default root class
class Root : public Teddy::Application::BaseRoot {
public:
	virtual void                start             ( int argc, char **argv );
	virtual void                parseOptions      ();
	virtual void                setDefaultOptions ();
	inline ActionManager       *getActionManager  (){ return action_manager;   }
	inline BaseAudioManager    *getAudioManager   (){ return audio_manager;    }
	inline ObjectManager       *getObjectManager  (){ return object_manager;   }
	inline BaseSimulationTimer *getSimulationTimer(){ return simulation_timer; }
	inline UserInterface       *getUserInterface  (){ return user_interface;   }

protected:
	Options ffe_options;

private:
	ActionManager       *action_manager;
	BaseAudioManager    *audio_manager;
	ObjectManager       *object_manager;
	BaseSimulationTimer *simulation_timer;
	UserInterface       *user_interface;
};


#endif  //  SPACE_GAME__ROOT__H

