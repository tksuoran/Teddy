
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


#ifndef TEDDY__IMPORTS__LW_INSTANCE__H
#define TEDDY__IMPORTS__LW_INSTANCE__H


#include "Teddy/TeddyConfig.h"
#if defined( TEDDY_INCLUDE_LW_SCENE )


#if defined(_MSC_VER)
#pragma warning(disable:4786)
#endif


#include "Teddy/Maths/Vector.h"
#include "Teddy/Models/Model.h"
#include "Teddy/SysSupport/StdMap.h"
using namespace Teddy::Maths;
using namespace Teddy::Models;


namespace Teddy   {
namespace Imports {


class LWBone;
class LWModel;
class LWMotion;


typedef std::map<int, LWBone*> int_to_LWBone;


#define LWI_VISIBILITY_HIDDEN                0
#define LWI_VISIBILITY_BOUNDING_BOX          1
#define LWI_VISIBILITY_VERTICES_ONLY         2
#define LWI_VISIBILITY_WIREFRAME             3
#define LWI_VISIBILITY_FRONT_FACE_WIREFRAME  4
#define LWI_VISIBILITY_SHADED_SOLID          5
#define LWI_VISIBILITY_TEXTURED_SHADED_SOLID 6


class LWInstance {
public:
	LWInstance();

	void            add              ( LWBone *bone );
	LWBone         *getBone          ( int bone_num );
	void            setModel         ( Model *mi );
	Model          *getModel         ();
	void            setModelName     ( const std::string &model_name );
	std::string    &getModelName     ();
	LWMotion       *getMotion        ();
	void            setMotion        ( LWMotion *motion );
	void            setVisibility    ( int visibility   );
	void            setColor         ( int color        );
	void            setParentObjectId( unsigned long parent_object_id );
	unsigned long   getParentObjectId();
	Vector         &evalPosition     ( float time );
    Matrix         &evalRotation     ( float time );
	Vector         &evalPivot        ( float time );
	void            setTime          ( float time );
	void            setPivotPosition ( Vector pivot_position );
	void            setParentObject  ( LWInstance *parent );

protected:
	unsigned long  parent_object_id;
	LWInstance    *parent_object;
	LWMotion      *motion;
	Model         *model;
	std::string    model_name;
	int_to_LWBone  bones;
	int            next_bone;
	int            visibility;  // old refresh value
	int            color;
	float          last_po_time;
	float          last_ro_time;
	float          last_pi_time;
	Vector         pivot_position;
    Vector         last_position;
    Matrix         last_rotation;
	Vector         last_pivot;
};


};  //  namespace Imports
};  //  namespace Teddy


#endif  //  TEDDY_INCLUDE_LW_SCENE
#endif  //  TEDDY__IMPORTS__LW_INSTANCE_H

