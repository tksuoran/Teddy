
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


#ifndef TEDDY__SCENES__SCENE__H
#define TEDDY__SCENES__SCENE__H


#include "Teddy/Graphics/Color.h"
#include "Teddy/Materials/Light.h"
#include "Teddy/Maths/Vector.h"
#include "Teddy/MixIn/Named.h"
#include "Teddy/MixIn/Mutex.h"
#include "Teddy/SysSupport/StdList.h"


namespace Teddy  {
namespace Scenes {


class Camera;
class PostElement;


/*!
	\brief   Collections of Models, Lights and Cameras
	\bug     Destructors missing?
	\todo    Group instances by material
	\todo    Improve light management
	\todo    Improved sorting, especially for transluent surface support

	Scene contains Lights and ModelInstances. Scene is responsible of
	rendering the scene according to Camera / Projection Area /
	(Transform)View settings, and each individual ModelInstance settings.

	At the moment rendering the Scene is a very unoptimized
	process. Later on things to be drawn should be arranged
	by material etc.

	Because light management is currently very simple, all
	lights are applied before instances are drawn.

	At the moment the scene is drawn in a single pass. This
	pass asks camera to cull instance and then the instance
	to draw itself if it was not culled.

	Rendering transluent instances and elements is not yet implemented.
*/
class Scene : public Teddy::MixIn::Named, public Teddy::MixIn::Mutex {
public:
    Scene( const std::string &name );
	
    void   add         ( Teddy::Materials::Light       *l );
    void   add         ( Teddy::Scenes   ::PostElement *p );
    void   add         ( Teddy::Models   ::Model       *i );
    void   remove      ( Teddy::Materials::Light       *l );
    void   remove      ( Teddy::Scenes   ::PostElement *p );
    void   remove      ( Teddy::Models   ::Model       *i );

	void   setAmbientColor( Teddy::Graphics::Color ambient_color );

	int    getCullCount    ();
	int    getDrawCount    ();
	float  getMaxObSize    ();
	float  getMaxObDistance();

	void                            draw            ( Camera *c, Teddy::PhysicalComponents::Projection *p );
	void                            drawPostElements( Camera *c, Teddy::PhysicalComponents::Projection *p );
	Teddy::Models::Model           *pick            ( Camera *c, Teddy::PhysicalComponents::Projection *p );
    void                            update          ( Teddy::PhysicalComponents::Projection    *p );
    list<Teddy::Models   ::Model*> &getModels       ();
    list<Teddy::Materials::Light*> &getLights       ();

protected:
    list<Teddy::Materials::Light      *>  lights;
    list<Teddy::Models   ::Model      *>  models;
    list<Teddy::Scenes   ::PostElement*>  post_elements;
	Teddy::Graphics::Color                ambient_color;
	int                                   cull_count;
	int                                   draw_count;
	int                                   last_draw_count;
};


};  //  namespace Scenes
};  //  namespace Teddy


#endif  //  TEDDY__SCENES__SCENE__H

