
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


#ifndef TEDDY__APPLICATION__BASE_OBJECT_MANAGER__H
#define TEDDY__APPLICATION__BASE_OBJECT_MANAGER__H


//  Forward declarations
namespace Teddy {
	namespace Scenes     { class Camera; };
	namespace Scenes     { class Scene;  };
	namespace SysSupport { class Clock;  };
};
using namespace Teddy::Scenes;
using namespace Teddy::SysSupport;


namespace Teddy       {
namespace Application {


//!  BaseObjectManager
class BaseObjectManager {
public:
	BaseObjectManager();

	Camera *getCamera();
	Scene  *getScene ();

	void setCamera( Camera *camera );
	void setScene ( Scene  *scene  );

protected:
	Scene  *scene;   //!<  Container for renderable 3D objects
	Camera *camera;  //!<  Camera
};


};  //  namespace Application
};  //  namespace Teddy


#endif  //  TEDDY__APPLICATION__BASE_OBJECT_MANAGER__H

