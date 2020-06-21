
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

	$Id: Camera.cpp,v 1.8 2002/02/16 12:41:39 tksuoran Exp $
*/


#include "Teddy/TeddyConfig.h"
#include "Teddy/Graphics/View.h"
#include "Teddy/Graphics/PsRenderer.h"
#include "Teddy/Models/Model.h"
#include "Teddy/Models/Geometry.h"
#include "Teddy/PhysicalComponents/Projection.h"
#include "Teddy/Scenes/Camera.h"
#include "Teddy/Scenes/Scene.h"
#include "Teddy/SysSupport/Messages.h"
#include "Teddy/SysSupport/StdMaths.h"
using namespace Teddy::Graphics;
using namespace Teddy::Models;
using namespace Teddy::PhysicalComponents;
using namespace Teddy::SysSupport;


namespace Teddy  {
namespace Scenes {


/*!
	\brief Camera constructor
	\param name Name for the Camera
	\param scene Scene which to view through this Camera
*/
Camera::Camera( const std::string &name, Scene *scene )
:
Model      ( name    ),
scene      ( scene   ),
near_clip  (    2    ),
far_clip   ( 4096    ),
fov        (   80    ),
zoom_factor(    1.0f )
{
	for( int i=0; i<MSD; i++ ){
		model_view_matrix[i] = Matrix::IDENTITY;
	}
	model_view_matrix_sp = 0;
	active_projection    = NULL;
	mirror_x             = false;
	projection_dirty     = true;
}


void Camera::setMirrorX( const bool mirror_x ){
	this->mirror_x = mirror_x;
    msg( M_INIT, "SetMirror %s", mirror_x?"true":"false" );
}

/*!
	\brief Calculate and apply perpective camera projection
	\todo  Optimize: This does not need to be recalculted always
*/
void Camera::doProjection( Projection *p, const bool load_matrix ){
	projection_matrix = getPerspectiveMatrix( fov, p->getRatio(), near_clip, far_clip );
	if( mirror_x ){
		projection_matrix = projection_matrix * Matrix::MIRROR_X;
	}
	if( load_matrix == true ){		
		p->setProjectionMatrix( projection_matrix );
		glMatrixMode( GL_MODELVIEW );
	}
	updatePlanes();
}


/*!
	\brief   Calculate and apply camera projection according to Projection
	\param   p Projection to which this Camera will project it's scene
	\param   load_matrix If true, the camera matrix is loaded to OpenGL
	\warning This might not be thread safe
*/
void Camera::doCamera( Projection *p, const bool load_matrix ){
	//  YUneed origo camera fix
	//	view_matrix = getViewMatrix();
	view_matrix = getWorldToLocalMatrix();

	if( load_matrix == true ){
		p->setModelViewMatrix( view_matrix );
	}
}


void Camera::pushObjectMatrix(){
	model_view_matrix_sp++;
}


void Camera::popObjectMatrix(){
	model_view_matrix_sp--;
}


//!  Apply object matrix
void Camera::doObjectMatrix( Projection *p, const Matrix &m, const bool load_matrix ){
	if( model_view_matrix_sp>0 ){
		model_view_matrix[model_view_matrix_sp] = 
			model_view_matrix[model_view_matrix_sp-1] * m;
	}else{
		model_view_matrix[model_view_matrix_sp] = view_matrix * m;
	}
	to_screen_s_matrix = projection_matrix * model_view_matrix[model_view_matrix_sp];
	if( load_matrix == true ){
		p->setModelViewMatrix( model_view_matrix[model_view_matrix_sp] );
	}
}


//!  Project vector from world coordinates to screen coordinates
Vector4 Camera::projectVector( const Vector4 &v ) const{
	return to_screen_s_matrix.transformVector4( v );
}


//!  Draw the scene as seen from the camera
/*virtual*/ void Camera::projectScene( Projection *p ){
	View *view              = p->getView();
    this->active_projection = p;
    this->rect              = IntRect( p->getRect() );

	Geometry::draw_count = 0;
//	debug_index = 0;

//  Update and load projection matrix
//	if( projection_dirty ){
		doProjection( p );
//		projection_dirty = false;
//	}

	doCamera( p );

	//  Draw Scene
	scene->lock  ();
	scene->draw  ( this, p );
	scene->unlock();
}


/*!
	\brief  Return depth-nearest modelinstance on view at spesified coordinates
	\return NULL if no modelinstance found, otherwise pointer to modelinstance
*/
Model *Camera::pick( Projection *p, const IntVector2 &pos ){
    Vector2 pick_pos  = pos;
    Vector2 pick_size = Vector2( 3.0, 3.0 );
	projection_matrix =
        getPickMatrix       ( pick_pos, pick_size, p->getRect()            ) *
		getPerspectiveMatrix( fov,      p->getRatio(), near_clip, far_clip );
	p->setProjectionMatrix( projection_matrix );

	doCamera( p, true );
	return scene->pick( this, p );
}	


void Camera::setNearFar( const float near_clip, const float far_clip ){
	this->near_clip = near_clip;
	this->far_clip  = far_clip;
}


double Camera::getNear(){
    return this->near_clip;
}


double Camera::getFar(){
    return this->far_clip;
}


//!  Set field of vision
void Camera::setFov( const float fov ){
	this->fov         = fov;
	this->zoom_factor = 1 / tan( fov/2 );
/*	this->fov = 2 * atan( 1 / zoom_factor );

	          fov       = 2 * atan( 1/zf )
	          fov / 2   =     atan( 1/zf )
  	     tan( fov / 2 ) = 1 / zf
	zf * tan( fov / 2 ) = 1
	zf                  = 1 / tan( fov / 2 )*/
}


void Camera::modFov( const float mod ){
	fov += mod;
	this->zoom_factor = 1 / tan( rads(fov)/2 );
}


//!  Return field of vision
float Camera::getFov() const {
	return fov;
}

void Camera::setZoomFactor( const float zoom_factor ){
	this->zoom_factor = zoom_factor;
	this->fov = degs( 2 * atan( 1 / zoom_factor ) );
}

float Camera::getZoomFactor() const {
	return this->zoom_factor;
}


//!  Set Scene for camera
void Camera::setScene( Scene *scene ){
	this->scene = scene;
}


//!  Return Scene of camera
Scene *Camera::getScene() const {
	return scene;
}


//!  Return true if modelinstance is outside the view frustum
bool Camera::cull( const Model &model ){
	Matrix m   = model_view_matrix[model_view_matrix_sp];
	Vector loc = m * Vector(0,0,0);
	float  rad = model.getClipRadius();

	double d0 = view_plane[0].distance( loc ) + rad;
	double d1 = view_plane[1].distance( loc ) + rad;
	double d2 = view_plane[2].distance( loc ) + rad;
	double d3 = view_plane[3].distance( loc ) + rad;
	double d4 = view_plane[4].distance( loc ) + rad;
	double d5 = view_plane[5].distance( loc ) + rad;
	
/*	debug_double[debug_index][0] = d0;
	debug_double[debug_index][1] = d1;
	debug_double[debug_index][2] = d2;
	debug_double[debug_index][3] = d3;
	debug_double[debug_index][4] = d4;
	debug_double[debug_index][5] = d5;
	debug_matrix[ debug_index ] = m;
	debug_index++;
	if( debug_index > 4 ) debug_index = 4;*/

	if( d0 < 0 ) return true;
	if( d1 < 0 ) return true;
	if( d2 < 0 ) return true;
	if( d3 < 0 ) return true;
	if( d4 < 0 ) return true;
	if( d5 < 0 ) return true;
	return false;
}


//!  Calculate frustum matrix
Matrix Camera::getFrustumMatrix( const float left, const float right, const float bottom, const float top, const float nearval, const float farval ) const {
	float x, y, a, b, c, d;
	Matrix frustum_matrix;

	x =  (nearval + nearval) / (right  - left   );
	y =  (nearval + nearval) / (top    - bottom );
	a =  (right   + left   ) / (right  - left   );
	b =  (top     + bottom ) / (top    - bottom );
	c = -(farval  + nearval) / (farval - nearval);
	d = -(2 * farval * nearval) / (farval - nearval);

#	define M(row,col) frustum_matrix.m[col][row]
	M(0,0) = x;  M(0,1) = 0;  M(0,2) =  a;  M(0,3) = 0;
	M(1,0) = 0;  M(1,1) = y;  M(1,2) =  b;  M(1,3) = 0;
	M(2,0) = 0;  M(2,1) = 0;  M(2,2) =  c;  M(2,3) = d;
	M(3,0) = 0;  M(3,1) = 0;  M(3,2) = -1;  M(3,3) = 0;
#	undef M

	return frustum_matrix;
}


//!  Calculate perspective projection matrix
Matrix Camera::getPerspectiveMatrix( const float fovy, const float aspect, const float zNear, const float zFar ) const {
	float xmin, xmax, ymin, ymax;

	/*this->zoom_factor = 1 / tan( fov/2 );*/
	ymax =  zNear * tan( fovy * M_PI / 360.0 );
	ymin = -ymax;
	xmin =  ymin * aspect;
	xmax =  ymax * aspect;

	return getFrustumMatrix( xmin, xmax, ymin, ymax, zNear, zFar );
}


//!  Calculate pick matrix
Matrix Camera::getPickMatrix( const IntVector2 &pick_pos, const IntVector2 &pick_size, const IntRect &viewport ) const {
	Matrix pick_matrix;

    Vector2 scale     = viewport.getSize() / pick_size;
    //	sx =  viewport[2] / width;
    //	sy =  viewport[3] / height;
    Vector2 offset    = viewport.min - pick_pos;
    Vector2 translate = (viewport.getSize() + offset + offset) / pick_size;
	//tx = (viewport[2] + 2 * (viewport[0] - x )) / width;
	//ty = (viewport[3] + 2 * (viewport[1] - y )) / height;

#	define M(row,col) pick_matrix.m[col][row]
	M(0, 0) = scale[0];      //  sx;
	M(0, 1) =  0;
	M(0, 2) =  0;
	M(0, 3) = translate[0];  //  tx;
	M(1, 0) =  0;
	M(1, 1) = scale[1];      //  sy;
	M(1, 2) =  0;
	M(1, 3) = translate[1];  //  ty;
	M(2, 0) =  0;
	M(2, 1) =  0;
	M(2, 2) =  1;
	M(2, 3) =  0;
	M(3, 0) =  0;
	M(3, 1) =  0;
	M(3, 2) =  0;
	M(3, 3) =  1;
#	undef M

	return pick_matrix;
}


//!  Calculate view frustum planes
void Camera::updatePlanes(){
	Matrix m = projection_matrix;
	m.transpose();
	Vector4 v1 = m.transformVector4(  Vector4(-1, 0, 0, 1 )  );
	Vector4 v2 = m.transformVector4(  Vector4( 1, 0, 0, 1 )  );
	Vector4 v3 = m.transformVector4(  Vector4( 0,-1, 0, 1 )  );
	Vector4 v4 = m.transformVector4(  Vector4( 0, 1, 0, 1 )  );
	Vector4 v5 = m.transformVector4(  Vector4( 0, 0,-1, 1 )  );
	Vector4 v6 = m.transformVector4(  Vector4( 0, 0, 1, 1 )  );
	v1 /= sqrt( v1[0] * v1[0] + v1[1] * v1[1] + v1[2] * v1[2] );
	v2 /= sqrt( v2[0] * v2[0] + v2[1] * v2[1] + v2[2] * v2[2] );
	v3 /= sqrt( v3[0] * v3[0] + v3[1] * v3[1] + v3[2] * v3[2] );
	v4 /= sqrt( v4[0] * v4[0] + v4[1] * v4[1] + v4[2] * v4[2] );
	v5 /= sqrt( v5[0] * v5[0] + v5[1] * v5[1] + v5[2] * v5[2] );
	v6 /= sqrt( v6[0] * v6[0] + v6[1] * v6[1] + v6[2] * v6[2] );
	view_plane[0] = v1;
	view_plane[1] = v2;
	view_plane[2] = v3;
	view_plane[3] = v4;
	view_plane[4] = v5;
	view_plane[5] = v6;
}


void Camera::updateFrustum(){  // Extracts The Current View Frustum Plane Equations
	float  proj[16];           // For Grabbing The PROJECTION Matrix
	float  modl[16];           // For Grabbing The MODELVIEW Matrix
	float  clip[16];           // Result Of Concatenating PROJECTION and MODELVIEW
	float  t;                  // Temporary Work Variable
	
	glGetFloatv( GL_PROJECTION_MATRIX, proj );  // Grab The Current PROJECTION Matrix
	glGetFloatv( GL_MODELVIEW_MATRIX,  modl );  // Grab The Current MODELVIEW Matrix

	// Concatenate (Multiply) The Two Matricies
	clip[ 0] = modl[ 0] * proj[ 0] + modl[ 1] * proj[ 4] + modl[ 2] * proj[ 8] + modl[ 3] * proj[12];
	clip[ 1] = modl[ 0] * proj[ 1] + modl[ 1] * proj[ 5] + modl[ 2] * proj[ 9] + modl[ 3] * proj[13];
	clip[ 2] = modl[ 0] * proj[ 2] + modl[ 1] * proj[ 6] + modl[ 2] * proj[10] + modl[ 3] * proj[14];
	clip[ 3] = modl[ 0] * proj[ 3] + modl[ 1] * proj[ 7] + modl[ 2] * proj[11] + modl[ 3] * proj[15];

	clip[ 4] = modl[ 4] * proj[ 0] + modl[ 5] * proj[ 4] + modl[ 6] * proj[ 8] + modl[ 7] * proj[12];
	clip[ 5] = modl[ 4] * proj[ 1] + modl[ 5] * proj[ 5] + modl[ 6] * proj[ 9] + modl[ 7] * proj[13];
	clip[ 6] = modl[ 4] * proj[ 2] + modl[ 5] * proj[ 6] + modl[ 6] * proj[10] + modl[ 7] * proj[14];
	clip[ 7] = modl[ 4] * proj[ 3] + modl[ 5] * proj[ 7] + modl[ 6] * proj[11] + modl[ 7] * proj[15];

	clip[ 8] = modl[ 8] * proj[ 0] + modl[ 9] * proj[ 4] + modl[10] * proj[ 8] + modl[11] * proj[12];
	clip[ 9] = modl[ 8] * proj[ 1] + modl[ 9] * proj[ 5] + modl[10] * proj[ 9] + modl[11] * proj[13];
	clip[10] = modl[ 8] * proj[ 2] + modl[ 9] * proj[ 6] + modl[10] * proj[10] + modl[11] * proj[14];
	clip[11] = modl[ 8] * proj[ 3] + modl[ 9] * proj[ 7] + modl[10] * proj[11] + modl[11] * proj[15];

	clip[12] = modl[12] * proj[ 0] + modl[13] * proj[ 4] + modl[14] * proj[ 8] + modl[15] * proj[12];
	clip[13] = modl[12] * proj[ 1] + modl[13] * proj[ 5] + modl[14] * proj[ 9] + modl[15] * proj[13];
	clip[14] = modl[12] * proj[ 2] + modl[13] * proj[ 6] + modl[14] * proj[10] + modl[15] * proj[14];
	clip[15] = modl[12] * proj[ 3] + modl[13] * proj[ 7] + modl[14] * proj[11] + modl[15] * proj[15];


	// Extract the RIGHT clipping plane
	frustum[0][0] = clip[ 3] - clip[ 0];
	frustum[0][1] = clip[ 7] - clip[ 4];
	frustum[0][2] = clip[11] - clip[ 8];
	frustum[0][3] = clip[15] - clip[12];

	// Normalize it
	t = (float) sqrt( frustum[0][0] * frustum[0][0] + frustum[0][1] * frustum[0][1] + frustum[0][2] * frustum[0][2] );
	frustum[0][0] /= t;
	frustum[0][1] /= t;
	frustum[0][2] /= t;
	frustum[0][3] /= t;


	// Extract the LEFT clipping plane
	frustum[1][0] = clip[ 3] + clip[ 0];
	frustum[1][1] = clip[ 7] + clip[ 4];
	frustum[1][2] = clip[11] + clip[ 8];
	frustum[1][3] = clip[15] + clip[12];

	// Normalize it
	t = (float) sqrt( frustum[1][0] * frustum[1][0] + frustum[1][1] * frustum[1][1] + frustum[1][2] * frustum[1][2] );
	frustum[1][0] /= t;
	frustum[1][1] /= t;
	frustum[1][2] /= t;
	frustum[1][3] /= t;


	// Extract the BOTTOM clipping plane
	frustum[2][0] = clip[ 3] + clip[ 1];
	frustum[2][1] = clip[ 7] + clip[ 5];
	frustum[2][2] = clip[11] + clip[ 9];
	frustum[2][3] = clip[15] + clip[13];

	// Normalize it
	t = (float) sqrt( frustum[2][0] * frustum[2][0] + frustum[2][1] * frustum[2][1] + frustum[2][2] * frustum[2][2] );
	frustum[2][0] /= t;
	frustum[2][1] /= t;
	frustum[2][2] /= t;
	frustum[2][3] /= t;


	// Extract the TOP clipping plane
	frustum[3][0] = clip[ 3] - clip[ 1];
	frustum[3][1] = clip[ 7] - clip[ 5];
	frustum[3][2] = clip[11] - clip[ 9];
	frustum[3][3] = clip[15] - clip[13];

	// Normalize it
	t = (float) sqrt( frustum[3][0] * frustum[3][0] + frustum[3][1] * frustum[3][1] + frustum[3][2] * frustum[3][2] );
	frustum[3][0] /= t;
	frustum[3][1] /= t;
	frustum[3][2] /= t;
	frustum[3][3] /= t;


	// Extract the FAR clipping plane
	frustum[4][0] = clip[ 3] - clip[ 2];
	frustum[4][1] = clip[ 7] - clip[ 6];
	frustum[4][2] = clip[11] - clip[10];
	frustum[4][3] = clip[15] - clip[14];

	// Normalize it
	t = (float) sqrt( frustum[4][0] * frustum[4][0] + frustum[4][1] * frustum[4][1] + frustum[4][2] * frustum[4][2] );
	frustum[4][0] /= t;
	frustum[4][1] /= t;
	frustum[4][2] /= t;
	frustum[4][3] /= t;


	// Extract the NEAR clipping plane.  This is last on purpose (see pointinfrustum() for reason)
	frustum[5][0] = clip[ 3] + clip[ 2];
	frustum[5][1] = clip[ 7] + clip[ 6];
	frustum[5][2] = clip[11] + clip[10];
	frustum[5][3] = clip[15] + clip[14];

	// Normalize it
	t = (float) sqrt( frustum[5][0] * frustum[5][0] + frustum[5][1] * frustum[5][1] + frustum[5][2] * frustum[5][2] );
	frustum[5][0] /= t;
	frustum[5][1] /= t;
	frustum[5][2] /= t;
	frustum[5][3] /= t;
}


/*!
	\brief Test If A Point Is In The Frustum.
	\todo  Optimization: remember which plane caused false last time and test it first
*/
bool Camera::cullPoint( const Vector &v ) const {
	for( int p = 0; p < 6; p++ ){
        if( frustum[p][0] * v[0] + frustum[p][1] * v[1] + frustum[p][2] * v[2] + frustum[p][3] <= 0 ){
			return false;
		}
	}
	return true;
}


/*
	\brief Test If A Sphere Is In The Frustum
	\todo  Optimization: remember which plane caused false last time and test it first
*/
bool Camera::cullSphere( const Vector &v, float radius ) const {
	for( int p=0; p<6; p++ ){
		if( frustum[p][0] * v[0] + frustum[p][1] * v[1] + frustum[p][2] * v[2] + frustum[p][3] <= -radius ){
			return false;
		}
	}
	return true;
}


/*!
	\brief Test If A box Is In The Frustum
	\todo  Optimization: for each corner remember which plane caused continue last time and test it first
*/
bool Camera::cullAABox( const Vector &pos, const Vector &size ){
    for( int p=0; p<6; p++ ){
        Vector min = pos - size;
        Vector max = pos + size;
        if( frustum[p][0] * min[0] + frustum[p][1] * min[1] + frustum[p][2] * min[2] + frustum[p][3] > 0 ) continue;
		if( frustum[p][0] * max[0] + frustum[p][1] * min[1] + frustum[p][2] * min[2] + frustum[p][3] > 0 ) continue;
		if( frustum[p][0] * min[0] + frustum[p][1] * max[1] + frustum[p][2] * min[2] + frustum[p][3] > 0 ) continue;
		if( frustum[p][0] * max[0] + frustum[p][1] * max[1] + frustum[p][2] * min[2] + frustum[p][3] > 0 ) continue;
		if( frustum[p][0] * min[0] + frustum[p][1] * min[1] + frustum[p][2] * max[2] + frustum[p][3] > 0 ) continue;
		if( frustum[p][0] * max[0] + frustum[p][1] * min[1] + frustum[p][2] * max[2] + frustum[p][3] > 0 ) continue;
        if( frustum[p][0] * min[0] + frustum[p][1] * max[1] + frustum[p][2] * max[2] + frustum[p][3] > 0 ) continue;
		if( frustum[p][0] * max[0] + frustum[p][1] * max[1] + frustum[p][2] * max[2] + frustum[p][3] > 0 ) continue;
		return false;
	}
	return true;
}


};  //  namespace Scenes
};  //  namespace Teddy

