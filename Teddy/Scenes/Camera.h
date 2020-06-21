
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
	
	$Id: Camera.h,v 1.8 2002/02/16 12:41:39 tksuoran Exp $
*/


#ifndef TEDDY__SCENES__CAMERA__H
#define TEDDY__SCENES__CAMERA__H


#include "Teddy/Maths/Vector.h"
#include "Teddy/Maths/Vector2.h"
#include "Teddy/Maths/Rect.h"
#include "Teddy/Maths/Plane.h"
#include "Teddy/Models/Model.h"
#include "Teddy/SysSupport/Types.h"


//  Forward declarations
namespace Teddy {
	namespace PhysicalComponents { class Projection; };
};


namespace Teddy  {
namespace Scenes {


class Scene;


#define MSD 32 //!<  ModelView Matrix stack depth


/*!
	\brief   Camera
	\warning Starfield is not working
	\warning Cull method needs checking, it does not work with picking
	\todo    docs
	\todo    GL_EXT_ cull_vertex 
*/
class Camera : public Teddy::Models::Model {
public:
    Camera( const std::string &name, Teddy::Scenes::Scene *scene );

	Teddy::Models::Model        *pick        ( Teddy::PhysicalComponents::Projection *p, const Teddy::Maths::TVector2<int> &pos );
	virtual void  projectScene( Teddy::PhysicalComponents::Projection *p );

	void     setMirrorX          ( const bool mirror_x );
	void     setNearFar          ( const float near_clip, const float far_clip );
	double   getNear             ();
    double   getFar              ();
	void     setZoomFactor       ( const float zoom_factor );
	float    getZoomFactor       () const;
	void     setFov              ( const float fov );
	float    getFov              () const;
	void     modFov              ( const float mod );
    void     setScene            ( Teddy::Scenes::Scene *scene );
	Scene   *getScene            () const;
	void     updatePlanes        ();
    bool     cull                ( const Teddy::Models::Model &mi );

    Teddy::Maths::Matrix           getFrustumMatrix    ( const float left, const float right, const float bottom, const float top, const float nearval, const float farval ) const;
	Teddy::Maths::Matrix           getPerspectiveMatrix( const float fovy, const float aspect, const float zNear,  const float zFar ) const;
    Teddy::Maths::Matrix           getPickMatrix       ( const Teddy::Maths::TVector2<int> &pos, const Teddy::Maths::TVector2<int> &size, const Teddy::Maths::TRect<int> &viewport ) const;
    Teddy::Maths::TVector4<float>  projectVector       ( const Teddy::Maths::TVector4<float> &v ) const;

	void     doProjection        ( Teddy::PhysicalComponents::Projection *p, const bool load_matrix = true );
	void     doCamera            ( Teddy::PhysicalComponents::Projection *p, const bool load_matrix = true );
    void     doObjectMatrix      ( Teddy::PhysicalComponents::Projection *p, const Teddy::Maths::Matrix &m, const bool load_matrix = true );
	void     pushObjectMatrix    ();
	void     popObjectMatrix     ();

	void     updateFrustum       ();
    bool     cullPoint           ( const Teddy::Maths::TVector<float> &v ) const;
    bool     cullSphere          ( const Teddy::Maths::TVector<float> &v, const float radius ) const;
    bool     cullAABox           ( const Teddy::Maths::TVector<float> &pos, const Teddy::Maths::TVector<float> &size );

#if 0
public:
	int         debug_index;
	double      debug_double[32][6];
	Vector      debug_vector[32];
    Matrix      debug_matrix[32];
#endif

protected:
    Teddy::Scenes::Scene                  *scene;                   //!<  Scene to draw
    Teddy::PhysicalComponents::Projection *active_projection;       //!<  Last active projection where to draw
    Teddy::Maths::Matrix                   to_screen_s_matrix;      //!<  To screen space -matrix
    Teddy::Maths::Matrix                   view_matrix;             //!<  Current/latest view matrix
    Teddy::Maths::Matrix                   projection_matrix;       //!<  Current/latest projection matrix
    Teddy::Maths::Matrix                   model_view_matrix[MSD];  //!<  ModelView Matrix stack
    Teddy::Maths::TRect<int>               rect;
    Teddy::Maths::Plane                    view_plane[6];           //!<  Camera view volume planes for clipping
	int                                    model_view_matrix_sp;    //!<  ModelView Matrix stack pointer
	double                                 near_clip;               //!<  Near clip plane z
	double                                 far_clip;                //!<  Far clip plane z
	double                                 fov;                     //!<  Field of vision
	float                                  zoom_factor;             //!<  Zoom Factor
	float	                               frustum[6][4];           // Holds The Current Frustum Plane Equations
	bool                                   mirror_x;                //!<  Mirror X
	bool                                   projection_dirty;        //!<  Projection needs to be redone?
};


};  //  namespace Scenes
};  //  namespace Teddy


#endif  //  TEDDY__SCENES__CAMERA_H

