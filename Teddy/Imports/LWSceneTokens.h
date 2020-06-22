
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


#ifndef TEDDY__IMPORTS__LW_SCENE_TOKENS__H
#define TEDDY__IMPORTS__LW_SCENE_TOKENS__H


#include "Teddy/TeddyConfig.h"
#if defined( TEDDY_INCLUDE_LW_SCENE )


namespace Teddy   {
namespace Imports {


enum LwsToken {
	LWS_UNKNOWN                  ,
	LWS_ERROR                    ,
	LWS_EOF                      ,

	LWS_LWSC                     ,
	LWS_FIRST_FRAME              ,
	LWS_LAST_FRAME               ,
	LWS_FRAME_STEP               ,
	LWS_FRAMES_PER_SECOND        ,
	LWS_PREVIEW_FIRST_FRAME      ,
	LWS_PREVIEW_LAST_FRAME       ,
	LWS_PREVIEW_FRAME_STEP       ,
	LWS_CURRENT_FRAME            ,
	LWS_PLUGIN                   ,
	LWS_END_PLUGIN               ,

	//  Objects
	LWS_ADD_NULL_OBJECT          ,
	LWS_LOAD_OBJECT              ,
	LWS_LOAD_OBJECT_LAYER        ,
	LWS_SHOW_OBJECT              ,
	LWS_OBJECT_MOTION            ,
	LWS_OBJECT_DISSOLVE          ,
	LWS_SUBDIVISION_ORDER        ,
	LWS_SUB_PATCH_LEVEL          ,
	LWS_SHADOW_OPTIONS           ,
	LWS_DISTANCE_DISSOLVE        ,
	LWS_MAX_DISSOLVE_DISTANCE    ,
	LWS_PARTICLE_SIZE            ,
	LWS_LINE_SIZE                ,
	LWS_POLYGON_SIZE             ,
	LWS_UNSEEN_BY_RAYS           ,
	LWS_UNSEEN_BY_CAMERA         ,
	LWS_UNAFFECTED_BY_FOG        ,
	LWS_AFFECTED_BY_FOG          ,
	LWS_EXCLUDE_LIGHT            ,
	LWS_OBJ_POLYGON_EDGES        ,
	LWS_OBJ_EDGE_COLOR           ,
	LWS_POLYGON_EDGE_FLAGS       ,
	LWS_POLYGON_EDGE_THICKNESS   ,
	LWS_POLYGON_EDGES_Z_SCALE    ,
	LWS_EDGE_NOMINAL_DISTANCE    ,

	LWS_DISPLACEMENT_MAP         ,
	LWS_CLIP_MAP                 ,
	LWS_TEXTURE_IMAGE            ,
	LWS_TEXTURE_FLAGS            ,
	LWS_TEXTURE_AXIS             ,
	LWS_TEXTURE_SIZE             ,
	LWS_TEXTURE_CENTER           ,
	LWS_TEXTURE_FALLOFF          ,
	LWS_TEXTURE_VELOCITY         ,
	LWS_TEXTURE_AMPLITUDE        ,
	LWS_TEXTURE_VALUE            ,
	LWS_TEXTURE_INT              ,
	LWS_TEXTURE_FLOAT            ,

	//  (for lights and cameras too)
	LWS_PIVOT_POSITION           ,
	LWS_PARENT_ITEM              ,
	LWS_BEHAVIORS                ,
	LWS_NUM_CHANNELS             ,
	LWS_CHANNEL                  ,
	LWS_ENVELOPE                 ,
	LWS_KEY                      ,
	LWS_LOCKED_CHANNELS          ,
	LWS_PARENT_OBJECT            ,
	LWS_TARGET_OBJECT            ,
	LWS_GOAL_OBJECT              ,
	LWS_SCHEMATIC_POSITION       ,

	LWS_MORPH_AMOUNT             ,
	LWS_MORPH_TARGET             ,
	LWS_MORPH_SURFACES           ,

	LWS_USE_BONES_FROM           ,
	LWS_BONE_FALLOFF_TYPE        ,
	LWS_ADD_BONE                 ,
	LWS_BONE_NAME                ,
	LWS_SHOW_BONE                ,
	LWS_BONE_ACTIVE              ,
	LWS_BONE_REST_POSITION       ,
	LWS_BONE_REST_DIRECTION      ,
	LWS_BONE_REST_LENGTH         ,
	LWS_BONE_STRENGTH            ,
	LWS_SCALE_BONE_STRENGTH      ,
	LWS_BONE_LIMITED_RANGE       ,
	LWS_BONE_MIN_RANGE           ,
	LWS_BONE_MAX_RANGE           ,
	LWS_BONE_MOTION              ,
	LWS_H_CONTROLLER             ,
	LWS_P_CONTROLLER             ,
	LWS_B_CONTROLLER             ,
	LWS_H_LIMITS                 ,
	LWS_P_LIMITS                 ,
	LWS_B_LIMITS                 ,
	LWS_IK_ANCHOR                ,

	//  Lights - global
	LWS_AMBIENT_COLOR            ,
	LWS_AMBIENT_INTENSITY        ,
	LWS_GLOBAL_FLARE_INTENSITY   ,
	LWS_ENABLE_LENS_FLARES       ,
	LWS_ENABLE_SHADOW_MAPS       ,

	//  Lights
	LWS_ADD_LIGHT                ,
	LWS_SHOW_LIGHT               ,
	LWS_LIGHT_NAME               ,
	LWS_LIGHT_MOTION             ,
	LWS_LIGHT_COLOR              ,
	LWS_LIGHT_TYPE               ,
	LWS_LIGHT_FALLOFF_TYPE       ,
	LWS_LIGHT_RANGE              ,
	LWS_LIGHT_CONE_ANGLE         ,
	LWS_LIGHT_EDGE_ANGLE         ,
	LWS_LIGHT_INTENSITY          ,
	LWS_FALLOFF                  ,
	LWS_AFFECT_CAUSTICS          ,
	LWS_AFFECT_DIFFUSE           ,
	LWS_AFFECT_SPECULAR          ,
	LWS_AFFECT_OPEN_GL           ,
	LWS_USE_CONE_ANGLE           ,
	LWS_LENS_FLARE               ,
	LWS_FLARE_INTENSITY          ,
	LWS_FLARE_DISSOLVE           ,
	LWS_LENS_FLARE_FADE          ,
	LWS_LENS_FLARE_OPTIONS       ,
	LWS_FLARE_RAND_STREAK_INT    ,
	LWS_FLARE_RAND_STREAK_DENS   ,
	LWS_FLARE_RAND_STREAK_SHARP  ,
	LWS_SHADOW_TYPE              ,
	LWS_SHADOW_CASTING           ,
	LWS_SHADOW_MAP_SIZE          ,
	LWS_SHADOW_MAP_ANGLE         ,
	LWS_SHADOW_FUZZINESS         ,

	//  Cameras
	LWS_ADD_CAMERA               ,
	LWS_CAMERA_NAME              ,
	LWS_SHOW_CAMERA              ,
	LWS_CAMERA_MOTION            ,
	LWS_ZOOM_FACTOR              ,
	LWS_MOTION_BLUR              ,
	LWS_BLUR_LENGTH              ,
	LWS_DEPTH_OF_FIELD           ,
	LWS_FOCAL_DISTANCE           ,
	LWS_LENS_F_STOP              ,

	LWS_RESOLUTION_MULTIPLIER    ,
	LWS_RESOLUTION               ,
	LWS_FRAME_SIZE               ,
	LWS_CUSTOM_SIZE              ,
	LWS_FILM_SIZE                ,
	LWS_NTSC_WIDE_SCREEN         ,
	LWS_PIXEL_ASPECT             ,
	LWS_PIXEL_ASPECT_RATIO       ,
	LWS_CUSTOM_PIXEL_RATIO       ,
	LWS_LIMITED_REGION           ,
	LWS_MASK_POSITION            ,
	LWS_APERTURE_HEIGHT          ,
	LWS_REGION_LIMITS            ,
	LWS_SEGMENT_MEMORY           ,
	LWS_ANTI_ALIASING            ,
	LWS_ENHANCED_AA              ,
	LWS_FILTER_TYPE              ,
	LWS_ADAPTIVE_SAMPLING        ,
	LWS_ADAPTIVE_THRESHOLD       ,
	LWS_FIELD_RENDERING          ,
	LWS_REVERSE_FIELDS           ,

	//  Effects
	LWS_BG_IMAGE                 ,
	LWS_FG_IMAGE                 ,
	LWS_FG_ALPHA_IMAGE           ,
	LWS_FG_DISSOLVE              ,
	LWS_FG_FADER_ALPHA_MODE      ,
	LWS_IMAGE_SEQUENCE_INFO      ,
	LWS_FOREGROUND_KEY           ,
	LWS_LOW_CLIP_COLOR           ,
	LWS_HIGH_CLIP_COLOR          ,
	LWS_SOLID_BACKDROP           ,
	LWS_BACKDROP_COLOR           ,
	LWS_ZENITH_COLOR             ,
	LWS_SKY_COLOR                ,
	LWS_GROUND_COLOR             ,
	LWS_NADIR_COLOR              ,
	LWS_SKY_SQUEEZE_AMOUNT       ,
	LWS_GROUND_SQUEEZE_AMOUNT    ,
	LWS_FOG_TYPE                 ,
	LWS_FOG_MIN_DIST             ,
	LWS_FOG_MAX_DIST             ,
	LWS_FOG_MIN_AMOUNT           ,
	LWS_FOG_MAX_AMOUNT           ,
	LWS_FOG_COLOR                ,
	LWS_BACKDROP_FOG             ,
	LWS_DITHER_INTENSITY         ,
	LWS_ANIMATED_DITHER          ,
	LWS_SATURATION               ,
	LWS_GLOW_EFFECT              ,
	LWS_GLOW_INTENSITY           ,
	LWS_GLOW_RADIUS              ,

	//  Render
	LWS_RENDER_MODE              ,
	LWS_RAY_TRACE_EFFECTS        ,
	LWS_RAY_TRACE_OPTIMIZATION   ,
	LWS_RAY_RECURSION_LIMIT      ,
	LWS_DATA_OVERLAY             ,
	LWS_DATA_OVERLAY_LABEL       ,
	LWS_OUTPUT_FILENAME_FORMAT   ,
	LWS_SAVE_RGB                 ,
	LWS_SAVE_ALPHA               ,
	LWS_SAVE_ANIM_FILE_NAME      ,
	LWS_LOCK_ANIM_PALETTE_FRAME  ,
	LWS_BEGIN_ANIM_LOOP_FRAME    ,
	LWS_SAVE_RGB_IMAGES_PREFIX   ,
	LWS_RGB_IMAGE_FORMAT         ,
	LWS_SAVE_ALPHA_IMAGES_PREFIX ,
	LWS_ALPHA_IMAGE_FORMAT       ,
	LWS_ALPHA_MODE               ,
	LWS_SAVE_FRAMESTORES_COMMENT ,
	LWS_FULL_SCENE_PARAM_EVAL    ,

	//  Layout Options
	LWS_VIEW_CONFIGURATION       ,
	LWS_DEFINE_VIEW              ,
	LWS_VIEW_MODE                ,
	LWS_VIEW_AIMPOINT            ,
	LWS_VIEW_ROTATION            ,
	LWS_VIEW_ZOOM_FACTOR         ,

	LWS_LAYOUT_GRID              ,
	LWS_GRID_NUMBER              ,
	LWS_GRID_SIZE                ,
	LWS_CAMERA_VIEW_BG           ,
	LWS_SHOW_MOTION_PATH         ,
	LWS_SHOW_SAFE_AREAS          ,
	LWS_SHOW_BG_IMAGE            ,
	LWS_SHOW_FOG_RADIUS          ,
	LWS_SHOW_FOG_EFFECT          ,
	LWS_SHOW_REDRAW              ,
	LWS_SHOW_FIELD_CHART         ,

	LWS_CURRENT_OBJECT           ,
	LWS_CURRENT_LIGHT            ,
	LWS_CURRENT_CAMERA           ,
	LWS_MAP_EDITOR_DATA          ,
	LWS_GRAPH_EDITOR_FAVORITES   ,

	LWS_END_MARK
};


};  //  namespace Imports
};  //  namespace Teddy


#endif  //  TEDDY_INCLUDE_LW_SCENE
#endif  //  TEDDY__IMPORTS__LW_SCENE_TOKENS__H



