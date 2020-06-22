
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
#if defined( TEDDY_INCLUDE_LW_SCENE )


#include "Teddy/Imports/LWSceneFile.h"
#include "Teddy/Imports/LWSceneParser.h"


namespace Teddy   {
namespace Imports {


void LWSceneParser::ViewConfiguration(){
	int view_configuration = file->read_int();
}


void LWSceneParser::DefineView(){
	int define_view = file->read_int();
}


/*
	ViewMode <value>

	example:  ViewMode 5

	The ViewMode function determines the default viewing mode from Layout when 
	the scene file is loaded.

	<value>:
		0 - Front
		1 - Top
		2 - Side
		3 - Perspective
		4 - Light
		5 - Camera
*/
void LWSceneParser::ViewMode(){
	int view_mode = file->read_int();
}


/*
	ViewAimpoint <x position> <y position> <z position>

	example:  ViewAimpoint 0.000000 0.000000 0.000000

	The ViewAimpoint function provides the position information for the 
	default viewing mode from Layout when the scene file is loaded.
*/
void LWSceneParser::ViewAimpoint(){
	double x = file->read_double();
	double y = file->read_double();
	double z = file->read_double();
	view_aimpoint = Vector( x, y, z );
}


/*
	ViewDirection <heading angle> <pitch angle> <bank angle>

	example:  ViewDirection 0.000000 -0.175433 0.000000

	The ViewDirection provides the rotation information for the default 
	viewing mode from Layout when the scene file is loaded.
*/
void LWSceneParser::ViewRotation(){
	double h = file->read_double();
	double p = file->read_double();
	double b = file->read_double();
//	view_rotation = Quaternion( rads(h), rads(p), rads(b) );
	Quaternion q;
    q  = Quaternion( Vector(0.0,1.0,0.0), M_PI + rads(h) );
    q *= Quaternion( Vector(1.0,0.0,0.0),      - rads(p) );
    q *= Quaternion( Vector(0.0,0.0,1.0),      - rads(b) );
	view_rotation = q;
}


/*
	ViewZoomFactor <float>

	example:  ViewZoomFactor 3.200000

	The ViewZoomFactor function provides the zoom factor for the default 
	viewing mode from Layout when the scene file is loaded.
*/
void LWSceneParser::ViewZoomFactor(){
	this->view_zoom_factor = file->read_double();
}


/*
	LayoutGrid <value>

	example:  LayoutGrid 8

	The LayoutGrid function determines the number of grid squares in Layout.

	<value>:
		0 - Off
		1 - 2 x 2
		2 - 4 x 4
		3 - 6 x 6
		4 - 8 x 8
		5 - 10 x 10
		6 - 12 x 12
		7 - 14 x 14
		8 - 16 x 16
*/
void LWSceneParser::LayoutGrid(){
	int layout_grid = file->read_int();
	grid_number = layout_grid * 2;
}


void LWSceneParser::GridNumber(){
	grid_number = file->read_int();
}

/*
	GridSize <float>

	example:  GridSize 1.000000

	The GridSize function  provides the value, in meters, for the grid square 
	size in Layout.
*/
void LWSceneParser::GridSize(){
	grid_size = file->read_double();
}

void LWSceneParser::CameraViewBG(){
	int camera_view_bg = file->read_int();
}


/*
	ShowMotionPath <flag>

	example:  ShowMotionPath 1

	The ShowMotionPath flag controls the display of the motion paths in Layout.

	<flag>:
		0 - Off
		1 - On
*/
void LWSceneParser::ShowMotionPath(){
	int show_motion_path = file->read_int();
}


/*
	ShowSafeAreas <flag>

	example:  ShowSafeAreas 1

	The ShowSafeAreas flag controls the display of the safe areas overlay in Layout.

	<flag>:
		0 - Off
		1 - On (Display Safe Area Chart)
*/
void LWSceneParser::ShowSafeAreas(){
	int show_safe_areas = file->read_int();
}


/*
	ShowBGImage <value>

	example:  ShowBGImage 2

	The ShowBGImage function activates the display of a background image or 
	preview anim.

	<value>:
		0 - Blank
		1 - BG Image
		2 - Preview
*/
void LWSceneParser::ShowBGImage(){
	int show_bg_image = file->read_int();
}

/*
	ShowFogRadius <flag>

	example:  ShowFogRadius 1

	The ShowFogRadius flag activates the display of the fog radius in Layout.

	<flag>:
		0 - Off
		1 - On (Display Fog Radius)
*/
void LWSceneParser::ShowFogRadius(){
	int show_fog_radius = file->read_int();
}


void LWSceneParser::ShowFogEffect(){
	int show_fog_effect = file->read_int();
}

/*
	ShowRedraw <flag>

	example:  ShowRedraw 0

	The ShowRedraw flag activates the display of the object polygon redraw 
	in Layout.

	<flag>:
		0 - Off
		1 - On (Display Object Polygon Redraw)
*/
void LWSceneParser::ShowRedraw(){
	int show_redraw = file->read_int();
}


/*
	ShowFieldChart <flag>

	example:  ShowFieldChart 1

	The ShowFieldChart flag activates the display of the Camera Field Chart 
	in Layout.

	<flag>:
		0 - Off
		1 - On (Display Field Chart)
*/
void LWSceneParser::ShowFieldChart(){
	int show_field_chart = file->read_int();
}

void LWSceneParser::CurrentObject(){
	int current_object = file->read_int();
}

void LWSceneParser::CurrentLight(){
	int current_light = file->read_int();
}

void LWSceneParser::CurrentCamera(){
	int current_camera = file->read_int();
}

void LWSceneParser::GraphEditorData(){}
void LWSceneParser::GraphEditorFavorites(){
	file->read_begin_scope();
	file->read_end_scope();
}


};  //  namespace Imports
};  //  namespace Teddy


#endif  //  TEDDY_INCLUDE_LW_SCENE


/*

  The Options Section contains the information that relates to environment 
  settings for LightWave's Layout.


		ViewMode
		ViewAimpoint
		ViewDirection
		ViewZoomFactor
		LayoutGrid
		GridSize
		ShowMotionPath
		ShowSafeAreas
		ShowBGImage
		ShowFogRadius
		ShowRedraw
		ShowFieldChart
*/

