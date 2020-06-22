
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


#ifndef TEDDY__PHYSICAL_COMPONENTS__PROJECTION__H
#define TEDDY__PHYSICAL_COMPONENTS__PROJECTION__H


#include "Teddy/Maths/Matrix.h"
#include "Teddy/MixIn/Options.h"
#include "Teddy/PhysicalComponents/Area.h"


//  Forward declarations
namespace Teddy {
	namespace Scenes    { class Camera;   };
	namespace Models    { class Model;    };
	namespace Graphics  { class Texture;  };
	namespace Materials { class Material; };
};

using namespace Teddy::Graphics;
using namespace Teddy::Materials;
using namespace Teddy::Maths;
using namespace Teddy::Models;
using namespace Teddy::Scenes;


namespace Teddy              {
namespace PhysicalComponents {


/*!
	\brief   Areas that need projection matrix

	Each projection area maintains it own rendering preferences.
	Those are independent of potential Material properties of
	ModelInstances which can be viewed in the Projection area.

	While some of the projection properties are default values,
	which can be overridden by material properties, others may
	override any material properties. For example, if projection
	is set to use wireframe rendering, no material property can
	override this - all modelinstances are drawn in wireframe
	mode.

	Projection is responsible for implementing and applying
	Material properties.
*/
class Projection : public Area {
public:
    Projection( const std::string &name, Camera *camera );
	virtual ~Projection();

	void           setProjectionMatrix  ();  //!<  Set projection matrix to identity
	void           setProjectionMatrix  ( Matrix &m );
	void           setModelViewMatrix   ();  //!<  Set modelview matrix to identity
	void           setModelViewMatrix   ( Matrix &m );
    Model         *pick                 ( const Vector2 &pos );
    float          getRatio();

	//  Area Input Interface
	virtual Area  *getHit               ( const Vector2 &pos );
	virtual void   drawSelf             ();  //!<  Will render only self

	Material      *getMaster            ();
	Options       &getSelect            ();
	void           setSelect            ( unsigned long select );
	void           enableSelect         ( unsigned long select );
	void           disableSelect        ( unsigned long select );
	void           setClearColor        ( Color c );
	Color          getClearColor        ();

	//  Projection Interface - Accessors
	Camera        *getCamera            ();
	void           setCamera            ( Camera *c = NULL );

	//  Projection Interface - Material control
	void           doMaterial           ( Material *m );
	void           materialReapplyActive();
	bool           materialPass         ();

	//  Projection Interface - Pick control
	void           pickState            ( const bool state );

	void           applyFillOutline     ();
	void           applyRemoveHidden    ();
	void           applyFrustumCull     ();
	void           applySortInstances   ();
	void           applySortElements    ();

public:
	static int material_skip_count;

protected:
	Camera   *camera;                         //<!  Attached camera (determines Scene)
	Material *active_material;                //<!  Currently active Material (last applied)
	Texture  *active_texture;                 //<!  Currently active Texture (last applied)
	Area     *frame;                          //<!  Window frame
	Material *master_material;                //<!  Override settings
	Uint8     render_pass;                    //<!  Current / last render pass
	Uint8     render_pass_count;              //<!  How manys render passes have been decided
	Options   render_options_selection_mask;  //<!  If bit 1 then render option is set from active material
	Color     clear_color;                    //<!  
};


};  //  namespace PhysicalComponents
};  //  namespace Teddy


#endif  //  TEDDY__PHYSICAL_COMPONENTS__PROJECTION__H

