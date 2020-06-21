
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

	$Id: LWSceneFile.cpp,v 1.2 2002/02/16 16:38:11 tksuoran Exp $
*/


#include "Teddy/TeddyConfig.h"
#if defined( TEDDY_INCLUDE_LW_SCENE )


#include "Teddy/Imports/LWSceneFile.h"
#include "Teddy/SysSupport/Messages.h"
#include "Teddy/SysSupport/StdIO.h"
#ifndef SWIG
#include <cctype>
#endif
using namespace Teddy::SysSupport;


namespace Teddy   {
namespace Imports {


//!  Constructor
LWSceneFile::LWSceneFile( const char *name ){
	mapTokens();
	file = NULL;
	open( name );
}


//!  Destructor
LWSceneFile::~LWSceneFile(){
	close();
}


bool LWSceneFile::isOk(){
	return file!=NULL ? true : false;
}


//!	 Open lightwave file stream
void LWSceneFile::open( const char *name ){
	file = fopen( name, "r" );
}


//!  Close stream
void LWSceneFile::close(){
	if( file != NULL ){
		fclose( file );
		file = NULL;
	}
}


LwsToken LWSceneFile::read_token(){
	string_to_token::iterator  t_it;
	char                       tmp[1024];
	int                        count;

	if( feof(file) != 0 ){
		return LWS_EOF;
	}

	count = fscanf( file, "%s", tmp );
	t_it  = token_map.find( tmp );

	if( count != 1 ){
		dmsg( M_LWS, "read_token() count == %d", count );
		return LWS_ERROR;
	}else if( t_it != token_map.end() ){
		//dmsg( M_LWS, "%s recognized", tmp );
		return (*t_it).second;
	}else{
		dmsg( M_LWS, "%s UNKNOWN", tmp );
		return read_token();
	}
}


void LWSceneFile::skip(){
	for(;;){
		int c = fgetc(file);
		if( (c == EOF) || (c == '\n') ){
			return;
		}
	}
}

bool LWSceneFile::read_begin_scope(){
	int  c;
	bool good = true;
	
	for(;;){
		c = fgetc( file );
		if( c == '{' ){
			return good;
		}else if( isspace(c) == 0 ){
			good = true;
		}
	}
}


bool LWSceneFile::read_end_scope(){
	int  c;
	bool good = true;
	
	for(;;){
		c = fgetc( file );
		if( c == '}' ){
			return good;
		}else if( isspace(c) == 0 ){
			good = true;
		}
	}
}


int LWSceneFile::read_int(){
	int a;
	int count;

	if( feof(file) != 0 ){
		return 0;
	}

	count = fscanf( file, "%d", &a );
	if( count != 1 ){
		return 0;
	}else{
		return a;
	}
}

unsigned long LWSceneFile::read_hex_int(){
	unsigned long a;
	int           count;

	if( feof(file) != 0 ){
		return 0;
	}

	count = fscanf( file, "%8lX", &a );
	if( count != 1 ){
		return 0;
	}else{
		return a;
	}
}



double LWSceneFile::read_double(){
	float a;
	int   count;

	if( feof(file) != 0 ){
		return 0;
	}

	count = fscanf( file, "%f", &a );
	if( count != 1 ){
		return 0;
	}else{
		return (double)a;
	}
}


char *LWSceneFile::read_string(){
	char *line  = new char[128];
	int   count = fscanf( file, "%s", line );

	if( count != 1 ){
		return 0;
	}else{
		return line;
	}
}


/*protected*/ void LWSceneFile::mapToken( char *key, LwsToken token ){
	token_map.insert( make_pair(key,token) );
}


void LWSceneFile::mapTokens(){

	//  Scenes
	mapToken( "LWSC"                  , LWS_LWSC                     );
	mapToken( "FirstFrame"            , LWS_FIRST_FRAME              );
	mapToken( "LastFrame"             , LWS_LAST_FRAME               );
	mapToken( "FrameStep"             , LWS_FRAME_STEP               );
	mapToken( "FramesPerSecond"       , LWS_FRAMES_PER_SECOND        );
	mapToken( "PreviewFirstFrame"     , LWS_PREVIEW_FIRST_FRAME      );
	mapToken( "PreviewLastFrame"      , LWS_PREVIEW_LAST_FRAME       );
	mapToken( "PreviewFrameStep"      , LWS_PREVIEW_FRAME_STEP       );
	mapToken( "CurrentFrame"          , LWS_CURRENT_FRAME            );
	mapToken( "Plugin"                , LWS_PLUGIN                   );
	mapToken( "EndPlugin"             , LWS_END_PLUGIN               );

	//  Objects
	mapToken( "AddNullObject"         , LWS_ADD_NULL_OBJECT          );
	mapToken( "LoadObject"            , LWS_LOAD_OBJECT              );
	mapToken( "LoadObjectLayer"       , LWS_LOAD_OBJECT_LAYER        );
	mapToken( "ShowObject"            , LWS_SHOW_OBJECT              );
	mapToken( "ObjectMotion"          , LWS_OBJECT_MOTION            );
	mapToken( "ObjectDissolve"        , LWS_OBJECT_DISSOLVE          );
	mapToken( "SubdivisionOrder"      , LWS_SUBDIVISION_ORDER        );
	mapToken( "SubPatchLevel"         , LWS_SUB_PATCH_LEVEL          );
	mapToken( "ShadowOptions"         , LWS_SHADOW_OPTIONS           );
	mapToken( "DistanceDissolve"      , LWS_DISTANCE_DISSOLVE        );
	mapToken( "MaxDissolveDistance"   , LWS_MAX_DISSOLVE_DISTANCE    );
	mapToken( "ParticleSize"          , LWS_PARTICLE_SIZE            );
	mapToken( "LineSize"              , LWS_LINE_SIZE                );
	mapToken( "PolygonSize"           , LWS_POLYGON_SIZE             );
	mapToken( "UnseenByRays"          , LWS_UNSEEN_BY_RAYS           );
	mapToken( "UnseenByCamera"        , LWS_UNSEEN_BY_CAMERA         );
	mapToken( "UnaffectedByFog"       , LWS_UNAFFECTED_BY_FOG        );
	mapToken( "AffectedByFog"         , LWS_AFFECTED_BY_FOG          );
	mapToken( "ExcludeLight"          , LWS_EXCLUDE_LIGHT            );
	mapToken( "ObjPolygonEdges"       , LWS_OBJ_POLYGON_EDGES        );
	mapToken( "ObjEdgeColor"          , LWS_OBJ_EDGE_COLOR           );
	mapToken( "PolygonEdgeFlags"      , LWS_POLYGON_EDGE_FLAGS       );
	mapToken( "PolygonEdgeThickness"  , LWS_POLYGON_EDGE_THICKNESS   );
	mapToken( "PolygonEdgesZScale"    , LWS_POLYGON_EDGES_Z_SCALE    );
	mapToken( "EdgeNominalDistance"   , LWS_EDGE_NOMINAL_DISTANCE    );

	mapToken( "DisplacementMap"       , LWS_DISPLACEMENT_MAP         );
	mapToken( "ClipMap"               , LWS_CLIP_MAP                 );
	mapToken( "TextureImage"          , LWS_TEXTURE_IMAGE            );
	mapToken( "TextureFlags"          , LWS_TEXTURE_FLAGS            );
	mapToken( "TextureAxis"           , LWS_TEXTURE_AXIS             );
	mapToken( "TextureSize"           , LWS_TEXTURE_SIZE             );
	mapToken( "TextureCenter"         , LWS_TEXTURE_CENTER           );
	mapToken( "TextureFalloff"        , LWS_TEXTURE_FALLOFF          );
	mapToken( "TextureVelocity"       , LWS_TEXTURE_VELOCITY         );
	mapToken( "TextureAmplitude"      , LWS_TEXTURE_AMPLITUDE        );
	mapToken( "TextureValue"          , LWS_TEXTURE_VALUE            );
	mapToken( "TextureInt"            , LWS_TEXTURE_INT              );
	mapToken( "TextureFloat"          , LWS_TEXTURE_FLOAT            );

	//  (for lights and cameras as well)
	mapToken( "PivotPosition"         , LWS_PIVOT_POSITION           );
	mapToken( "ParentItem"            , LWS_PARENT_ITEM              );
	mapToken( "Behaviors"             , LWS_BEHAVIORS                );
	mapToken( "NumChannels"           , LWS_NUM_CHANNELS             );
	mapToken( "Channel"               , LWS_CHANNEL                  );
	mapToken( "Envelope"              , LWS_ENVELOPE                 );
	mapToken( "Key"                   , LWS_KEY                      );
	mapToken( "LockedChannels"        , LWS_LOCKED_CHANNELS          );
	mapToken( "ParentObject"          , LWS_PARENT_OBJECT            );
	mapToken( "TargetObject"          , LWS_TARGET_OBJECT            );
	mapToken( "GoalObject"            , LWS_GOAL_OBJECT              );
	mapToken( "SchematicPosition"     , LWS_SCHEMATIC_POSITION       );

	mapToken( "MorphAmount"           , LWS_MORPH_AMOUNT             );
	mapToken( "MorphTarget"           , LWS_MORPH_TARGET             );
	mapToken( "MorphSurfaces"         , LWS_MORPH_SURFACES           );

	mapToken( "UseBonesFrom"          , LWS_USE_BONES_FROM           );
	mapToken( "BoneFalloffType"       , LWS_BONE_FALLOFF_TYPE        );
	mapToken( "AddBone"               , LWS_ADD_BONE                 );
	mapToken( "BoneName"              , LWS_BONE_NAME                );
	mapToken( "ShowBone"              , LWS_SHOW_BONE                );
	mapToken( "BoneActive"            , LWS_BONE_ACTIVE              );
	mapToken( "BoneRestPosition"      , LWS_BONE_REST_POSITION       );
	mapToken( "BoneRestDirection"     , LWS_BONE_REST_DIRECTION      );
	mapToken( "BoneRestLength"        , LWS_BONE_REST_LENGTH         );
	mapToken( "BoneStrength"          , LWS_BONE_STRENGTH            );
	mapToken( "ScaleBoneStrength"     , LWS_SCALE_BONE_STRENGTH      );
	mapToken( "BoneLimitedRange"      , LWS_BONE_LIMITED_RANGE       );
	mapToken( "BoneMinRange"          , LWS_BONE_MIN_RANGE           );
	mapToken( "BoneMaxRange"          , LWS_BONE_MAX_RANGE           );
	mapToken( "BoneMotion"            , LWS_BONE_MOTION              );
	mapToken( "HController"           , LWS_H_CONTROLLER             );
	mapToken( "PController"           , LWS_P_CONTROLLER             );
	mapToken( "BController"           , LWS_B_CONTROLLER             );
	mapToken( "HLimits"               , LWS_H_LIMITS                 );
	mapToken( "PLimits"               , LWS_P_LIMITS                 );
	mapToken( "BLimits"               , LWS_B_LIMITS                 );
	mapToken( "IKAnchor"              , LWS_IK_ANCHOR                );

	//  Lights - global
	mapToken( "AmbientColor"          , LWS_AMBIENT_COLOR            );
	mapToken( "AmbientIntensity"      , LWS_AMBIENT_INTENSITY        );
	mapToken( "GlobalFlareIntensity"  , LWS_GLOBAL_FLARE_INTENSITY   );
	mapToken( "EnableLensFlares"      , LWS_ENABLE_LENS_FLARES       );
	mapToken( "EnableShadowMaps"      , LWS_ENABLE_SHADOW_MAPS       );

	//  Lights
	mapToken( "AddLight"              , LWS_ADD_LIGHT                );
	mapToken( "ShowLight"             , LWS_SHOW_LIGHT               );
	mapToken( "LightName"             , LWS_LIGHT_NAME               );
	mapToken( "LightMotion"           , LWS_LIGHT_MOTION             );
	mapToken( "LightColor"            , LWS_LIGHT_COLOR              );
	mapToken( "LightType"             , LWS_LIGHT_TYPE               );
	mapToken( "LightFalloffType"      , LWS_LIGHT_FALLOFF_TYPE       );
	mapToken( "LightRange"            , LWS_LIGHT_RANGE              );
	mapToken( "LightConeAngle"        , LWS_LIGHT_CONE_ANGLE         );
	mapToken( "LightEdgeAngle"        , LWS_LIGHT_EDGE_ANGLE         );
	mapToken( "LightIntensity"        , LWS_LIGHT_INTENSITY          );
	mapToken( "Falloff"               , LWS_FALLOFF                  );
	mapToken( "AffectCaustics"        , LWS_AFFECT_CAUSTICS          );
	mapToken( "AffectDiffuse"         , LWS_AFFECT_DIFFUSE           );
	mapToken( "AffectSpecular"        , LWS_AFFECT_SPECULAR          );
	mapToken( "AffectOpenGL"          , LWS_AFFECT_OPEN_GL           );
	mapToken( "UseConeAngle"          , LWS_USE_CONE_ANGLE           );
	mapToken( "LensFlare"             , LWS_LENS_FLARE               );
	mapToken( "FlareIntensity"        , LWS_FLARE_INTENSITY          );
	mapToken( "FlareDissolve"         , LWS_FLARE_DISSOLVE           );
	mapToken( "LensFlareFade"         , LWS_LENS_FLARE_FADE          );
	mapToken( "LensFlareOptions"      , LWS_LENS_FLARE_OPTIONS       );
	mapToken( "FlareRandStreakInt"    , LWS_FLARE_RAND_STREAK_INT    );
	mapToken( "FlareRandStreakDens"   , LWS_FLARE_RAND_STREAK_DENS   );
	mapToken( "FlareRandStreakSharp"  , LWS_FLARE_RAND_STREAK_SHARP  );
	mapToken( "ShadowType"            , LWS_SHADOW_TYPE              );
	mapToken( "ShadowCasting"         , LWS_SHADOW_CASTING           );
	mapToken( "ShadowMapSize"         , LWS_SHADOW_MAP_SIZE          );
	mapToken( "ShadowMapAngle"        , LWS_SHADOW_MAP_ANGLE         );
	mapToken( "ShadowFuzziness"       , LWS_SHADOW_FUZZINESS         );

	//  Cameras
	mapToken( "AddCamera"             , LWS_ADD_CAMERA               );
	mapToken( "CameraName"            , LWS_CAMERA_NAME              );
	mapToken( "ShowCamera"            , LWS_SHOW_CAMERA              );
	mapToken( "CameraMotion"          , LWS_CAMERA_MOTION            );
	mapToken( "ZoomFactor"            , LWS_ZOOM_FACTOR              );
	mapToken( "MotionBlur"            , LWS_MOTION_BLUR              );
	mapToken( "BlurLength"            , LWS_BLUR_LENGTH              );
	mapToken( "DepthofField"          , LWS_DEPTH_OF_FIELD           );
	mapToken( "FocalDistance"         , LWS_FOCAL_DISTANCE           );
	mapToken( "LensFStop"             , LWS_LENS_F_STOP              );

	mapToken( "ResolutionMultiplier"  , LWS_RESOLUTION_MULTIPLIER    );
	mapToken( "Resolution"            , LWS_RESOLUTION               );
	mapToken( "FrameSize"             , LWS_FRAME_SIZE               );
	mapToken( "CustomSize"            , LWS_CUSTOM_SIZE              );
	mapToken( "FilmSize"              , LWS_FILM_SIZE                );
	mapToken( "NTSCWidescreen"        , LWS_NTSC_WIDE_SCREEN         );
	mapToken( "PixelAspect"           , LWS_PIXEL_ASPECT             );
	mapToken( "PixelAspectRatio"      , LWS_PIXEL_ASPECT_RATIO       );
	mapToken( "CustomPixelRatio"      , LWS_CUSTOM_PIXEL_RATIO       );
	mapToken( "LimitedRegion"         , LWS_LIMITED_REGION           );
	mapToken( "MaskPosition"          , LWS_MASK_POSITION            );
	mapToken( "ApertureHeight"        , LWS_APERTURE_HEIGHT          );
	mapToken( "RegionLimits"          , LWS_REGION_LIMITS            );
	mapToken( "SegmentMemory"         , LWS_SEGMENT_MEMORY           );
	mapToken( "Antialiasing"          , LWS_ANTI_ALIASING            );
	mapToken( "EnhancedAA"            , LWS_ENHANCED_AA              );
	mapToken( "FilterType"            , LWS_FILTER_TYPE              );
	mapToken( "AdaptiveSampling"      , LWS_ADAPTIVE_SAMPLING        );
	mapToken( "AdaptiveThreshold"     , LWS_ADAPTIVE_THRESHOLD       );
	mapToken( "FieldRendering"        , LWS_FIELD_RENDERING          );
	mapToken( "ReverseFields"         , LWS_REVERSE_FIELDS           );

	//  Effects
	mapToken( "BGImage"               , LWS_BG_IMAGE                 );
	mapToken( "FGImage"               , LWS_FG_IMAGE                 );
	mapToken( "FGAlphaImage"          , LWS_FG_ALPHA_IMAGE           );
	mapToken( "FGDissolve"            , LWS_FG_DISSOLVE              );
	mapToken( "FGFaderAlphaMode"      , LWS_FG_FADER_ALPHA_MODE      );
	mapToken( "ImageSequenceInfo"     , LWS_IMAGE_SEQUENCE_INFO      );
	mapToken( "ForegroundKey"         , LWS_FOREGROUND_KEY           );
	mapToken( "LowClipColor"          , LWS_LOW_CLIP_COLOR           );
	mapToken( "HighClipColor"         , LWS_HIGH_CLIP_COLOR          );
	mapToken( "SolidBackdrop"         , LWS_SOLID_BACKDROP           );
	mapToken( "BackdropColor"         , LWS_BACKDROP_COLOR           );
	mapToken( "ZenithColor"           , LWS_ZENITH_COLOR             );
	mapToken( "SkyColor"              , LWS_SKY_COLOR                );
	mapToken( "GroundColor"           , LWS_GROUND_COLOR             );
	mapToken( "NadirColor"            , LWS_NADIR_COLOR              );
	mapToken( "SkySqueezeAmount"      , LWS_SKY_SQUEEZE_AMOUNT       );
	mapToken( "GroundSqueezeAmount"   , LWS_GROUND_SQUEEZE_AMOUNT    );
	mapToken( "FogType"               , LWS_FOG_TYPE                 );
	mapToken( "FogMinDist"            , LWS_FOG_MIN_DIST             );
	mapToken( "FogMaxDist"            , LWS_FOG_MAX_DIST             );
	mapToken( "FogMinAmount"          , LWS_FOG_MIN_AMOUNT           );
	mapToken( "FogMaxAmount"          , LWS_FOG_MAX_AMOUNT           );
	mapToken( "FogColor"              , LWS_FOG_COLOR                );
	mapToken( "BackdropFog"           , LWS_BACKDROP_FOG             );
	mapToken( "DitherIntensity"       , LWS_DITHER_INTENSITY         );
	mapToken( "AnimatedDither"        , LWS_ANIMATED_DITHER          );
	mapToken( "Saturation"            , LWS_SATURATION               );
	mapToken( "GlowEffect"            , LWS_GLOW_EFFECT              );
	mapToken( "GlowIntensity"         , LWS_GLOW_INTENSITY           );
	mapToken( "GlowRadius"            , LWS_GLOW_RADIUS              );

	//  Render
	mapToken( "RenderMode"            , LWS_RENDER_MODE              );
	mapToken( "RayTraceEffects"       , LWS_RAY_TRACE_EFFECTS        );
	mapToken( "RayTraceOptimization"  , LWS_RAY_TRACE_OPTIMIZATION   );
	mapToken( "RayRecursionLimit"     , LWS_RAY_RECURSION_LIMIT      );
	mapToken( "DataOverlay"           , LWS_DATA_OVERLAY             );
	mapToken( "DataOverlayLabel"      , LWS_DATA_OVERLAY_LABEL       );
	mapToken( "OutputFilenameFormat"  , LWS_OUTPUT_FILENAME_FORMAT   );
	mapToken( "SaveRGB"               , LWS_SAVE_RGB                 );
	mapToken( "SaveAlpha"             , LWS_SAVE_ALPHA               );
	mapToken( "SaveANIMFileName"      , LWS_SAVE_ANIM_FILE_NAME      );
	mapToken( "LockANIMPaletteFrame"  , LWS_LOCK_ANIM_PALETTE_FRAME  );
	mapToken( "BeginANIMLoopFrame"    , LWS_BEGIN_ANIM_LOOP_FRAME    );
	mapToken( "SaveRGBImagesPrefix"   , LWS_SAVE_RGB_IMAGES_PREFIX   );
	mapToken( "RGBImageFormat"        , LWS_RGB_IMAGE_FORMAT         );
	mapToken( "SaveAlphaImagesPrefix" , LWS_SAVE_ALPHA_IMAGES_PREFIX );
	mapToken( "AlphaImageFormat"      , LWS_ALPHA_IMAGE_FORMAT       );
	mapToken( "AlphaMode"             , LWS_ALPHA_MODE               );
	mapToken( "SaveFramestoresComment", LWS_SAVE_FRAMESTORES_COMMENT );
	mapToken( "FullSceneParamEval"    , LWS_FULL_SCENE_PARAM_EVAL    );

	//  Layout Options
	mapToken( "ViewConfiguration"     , LWS_VIEW_CONFIGURATION       );
	mapToken( "DefineView"            , LWS_DEFINE_VIEW              );
	mapToken( "ViewMode"              , LWS_VIEW_MODE                );
	mapToken( "ViewAimpoint"          , LWS_VIEW_AIMPOINT            );
	mapToken( "ViewRotation"          , LWS_VIEW_ROTATION            );
	mapToken( "ViewZoomFactor"        , LWS_VIEW_ZOOM_FACTOR         );

	mapToken( "LayoutGrid"            , LWS_LAYOUT_GRID              );
	mapToken( "GridNumber"            , LWS_GRID_NUMBER              );
	mapToken( "GridSize"              , LWS_GRID_SIZE                );
	mapToken( "CameraViewBG"          , LWS_CAMERA_VIEW_BG           );
	mapToken( "ShowMotionPath"        , LWS_SHOW_MOTION_PATH         );
	mapToken( "ShowSafeAreas"         , LWS_SHOW_SAFE_AREAS          );
	mapToken( "ShowBGImage"           , LWS_SHOW_BG_IMAGE            );
	mapToken( "ShowFogRadius"         , LWS_SHOW_FOG_RADIUS          );
	mapToken( "ShowFogEffect"         , LWS_SHOW_FOG_EFFECT          );
	mapToken( "ShowRedraw"            , LWS_SHOW_REDRAW              );
	mapToken( "ShowFieldChart"        , LWS_SHOW_FIELD_CHART         );

	mapToken( "CurrentObject"         , LWS_CURRENT_OBJECT           );
	mapToken( "CurrentLight"          , LWS_CURRENT_LIGHT            );
	mapToken( "CurrentCamera"         , LWS_CURRENT_CAMERA           );
	mapToken( "GraphEditorData"       , LWS_MAP_EDITOR_DATA          );
	mapToken( "GraphEditorFavorites"  , LWS_GRAPH_EDITOR_FAVORITES   );
}


};  //  namespace Imports
};  //  namespace Teddy


#endif  //  TEDDY_INCLUDE_LW_SCENE

