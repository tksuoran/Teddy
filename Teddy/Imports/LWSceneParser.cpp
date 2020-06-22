
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


#include "Teddy/Imports/LWBone.h"
#include "Teddy/Imports/LWCamera.h"
#include "Teddy/Imports/LWInstance.h"
#include "Teddy/Imports/LWLight.h"
#include "Teddy/Imports/LWModel.h"
#include "Teddy/Imports/LWSceneFile.h"
#include "Teddy/Imports/LWSceneParser.h"
#include "Teddy/Imports/LWSceneTokens.h"
#include "Teddy/Imports/LWModelLoader.h"
#include "Teddy/Materials/Material.h"
#include "Teddy/Models/Grid.h"
#include "Teddy/Models/Model.h"
#include "Teddy/Scenes/Scene.h"
#include "Teddy/SysSupport/Messages.h"
#include "Teddy/SysSupport/FileScan.h"
#include "Teddy/SysSupport/StdSDL.h"
using namespace Teddy::Materials;
using namespace Teddy::Models;
using namespace Teddy::Scenes;
using namespace Teddy::SysSupport;


namespace Teddy   {
namespace Imports {


const int LWSceneParser::OPT_GRID      = (1ul<<1ul);
const int LWSceneParser::OPT_DARK_GRID = (1ul<<2ul);


void LWSceneParser::postProcess(){
	unsigned long counter = 0;
	dmsg( M_LWS, "Postprocessing stage has %d objects to do.", objects.size() );
	int_to_LWInstance::iterator o_it = objects.begin();
	while( o_it != objects.end() ){
		dmsg( M_LWS, "Postprocessing object %d", ++counter );
		LWInstance *object = (*o_it).second;
		if( object != NULL ){
			std::string &model_name = object->getModelName();
			Model *model = NULL;
			if( model_name.size() > 0 ){
				//model = new LWModel( object->getModelName(), 0 );
				model = LWModelLoader::loadModel( object->getModelName() );
			}else{
				model = new Model("LWNULL");
			}
			object->setModel( model  );
			object->setTime ( 0      );
			resolveParent   ( object );
			scene->add      ( model  );
		}
		o_it++;
	}

    dmsg( M_LWS, "grid_number %d grid_size % 8.4f", grid_number, grid_size );
    this->grid = new Grid( grid_number, grid_number, grid_size, grid_size );
    dmsg( M_LWS, "grid done" );

	scene->setAmbientColor( ambient_color * amb_intensity );
	int_to_LWLight::iterator l_it = lights.begin();
	while( l_it != lights.end() ){
		LWLight *light = (*l_it).second;
		if( light != NULL ){
			dmsg( M_LWS, "Generating LightWave light" );
			light ->genLight();
			light ->setModel( light->getLight() );
			light ->setTime ( 0                 );
			scene ->add     ( light->getLight() );
			resolveParent   ( light             );
		}
		l_it++;
	}

	int_to_LWCamera::iterator c_it = cameras.begin();
	while( c_it != cameras.end() ){
		LWCamera *cam = (*c_it).second;
		if( cam != NULL ){
			cam->setCamera( camera );
			cam->setTime  ( 0 );
			resolveParent( cam );
		}
		c_it++;
	}
}


LWSceneParser::LWSceneParser( Scene *scene, Camera *camera, const char *fname, Options options )
:
options(options),
scene  (scene  ),
camera (camera )
{
	file        = NULL;
	lws_version = 0;
	next_object = 0;
	next_light  = 0;
	next_camera = 0;
	grid_number = 16;
	grid_size   = 1.0f;

	playing     = false;
	multiplier  = 0.001f;
	stop_time   = 0;
	start_time  = 0;

	zenith_color = Color::DARK_BLUE;
	sky_color    = Color::LIGHT_BLUE;
	ground_color = Color::LIGHT_CYAN;
    nadir_color  = Color::DARK_GREEN;
    grid         = NULL;

	readFile   ( fix_file_name("Data/lws/",fname) );
	postProcess();
	reset      ();
}


void LWSceneParser::reset(){
	stop_time  = 0;
	start_time = float(SDL_GetTicks()) * multiplier;
	update();
}


void LWSceneParser::stop(){
	if( playing == true ){
		playing   = false;
		stop_time = start_time - float(SDL_GetTicks()) * multiplier;
	}
}

void LWSceneParser::play(){
	if( playing == false ){
		playing    = true;
		start_time = float(SDL_GetTicks()) * multiplier + stop_time;
	}
}


void LWSceneParser::setMultiplier( float new_mult ){
	bool do_play = playing;
	stop();
	this->multiplier  = new_mult;
	if( do_play ){
		play();
	}
}


float LWSceneParser::getMultiplier(){
	return this->multiplier;
}


/*virtual*/ void LWSceneParser::tick(){
	if( playing == false ){
		return;
	}
	update();
}


float LWSceneParser::getTime(){
	return last_used_time;
}


void LWSceneParser::update(){
	float time = playing ? float(SDL_GetTicks()) * multiplier - start_time : stop_time;

	if( playing==true ){
		float max_time = 1.0f / float(frames_per_second) * float(preview_last_frame);
		if( time<0 ){
			if( multiplier<0 ){
				multiplier = -multiplier;
				stop();
				reset();
			}
			float time = playing ? float(SDL_GetTicks()) * multiplier - start_time : stop_time;
		}else if( time>max_time ){
			reset();
			time = float(SDL_GetTicks()) * multiplier - start_time;
		}
	}

	this->last_used_time = time;

	int_to_LWInstance::iterator o_it = objects.begin();
	while( o_it != objects.end() ){
		LWInstance *object = (*o_it).second;
		if( object != NULL ){
			object->setTime( time );
		}
		o_it++;
	}

	int_to_LWLight::iterator l_it = lights.begin();
	while( l_it != lights.end() ){
		LWLight *light = (*l_it).second;
		if( light != NULL ){
			light->setTime( time );
		}
		l_it++;
	}
/*
	int_to_LWCamera::iterator c_it = cameras.begin();
	while( c_it != cameras.end() ){
		LWCamera *cam = (*c_it).second;
		if( cam != NULL ){
			cam->setTime( time );
		}
		c_it++;
	}
	*/
}


Grid *LWSceneParser::getGrid(){
    return this->grid;
}


float LWSceneParser::getGridSize(){
	return this->grid_size;
}


Teddy::Maths::TVector<float> LWSceneParser::getViewAimpoint(){
	return this->view_aimpoint;
}


Teddy::Maths::Quaternion LWSceneParser::getViewRotation(){
	return this->view_rotation;
}


float LWSceneParser::getViewZoomFactor(){
	return this->view_zoom_factor;
}


void LWSceneParser::resolveParent( LWInstance *object ){
	unsigned long  all_bits  = object->getParentObjectId();
	if( all_bits == 0xffffffff ){
		return;
	}
	unsigned long  item_type = (0xf0000000 & all_bits) >> 28;
	unsigned long  item_num  = (0x0fffffff & all_bits);
	LWInstance    *parent    = NULL;

	switch( item_type ){

	case 1: {  //  Object
		int_to_LWInstance::iterator i_it = objects.find( item_num );
		if( i_it != objects.end() ){
			parent = (*i_it).second;
		}else{
			emsg( M_LWS, "Parent object %d not found", item_num );
		}
		break;
	}

	case 2: {  //  Light
		int_to_LWLight::iterator l_it = lights.find( item_num );
		if( l_it != lights.end() ){
			parent = (*l_it).second;
		}else{
			emsg( M_LWS, "Parent light %d not found", item_num );
		}
		break;
	}

	case 3: {  //  Camera
		int_to_LWCamera::iterator c_it = cameras.find( item_num );
		if( c_it != cameras.end() ){
			parent = (*c_it).second;
		}else{
			emsg( M_LWS, "Parent camera %d not found", item_num );
		}
		break;
	}

	case 4: {  //  Bone
		unsigned long  bone_num  = (0x0fff0000 & all_bits);
		unsigned long  obj_num   = (0x0000ffff & all_bits);
		int_to_LWInstance::iterator i_it = objects.find( obj_num );
		if( i_it != objects.end() ){
			LWInstance *obj = (*i_it).second;
			if( obj != NULL ){
				parent = obj->getBone( bone_num );
			}else{
				emsg( M_LWS, "Parent object %d found NULL", obj_num );
			}
		}else{
			emsg( M_LWS, "Parent object %d not found", obj_num );
		}
		break;
	}

	default:
		emsg( M_LWS, "Unknown item type %d", item_type );
		break;
	}

	object->setParentObject( parent );
}


void LWSceneParser::readFile( const char *fname ){
	dmsg( M_LWS, "Reading file %s", fname );
	file      = new LWSceneFile( fname ); 
	bool cont = true;

	if( file->isOk() == false ){
		emsg( M_LWS, "Read file %s not found", fname );
		return;
	}

	//  Read the file
	while( cont ){
		LwsToken token = file->read_token();

		switch( token ){
		//  Scene
		case LWS_LWSC                    : LWSC                   (); break;
		case LWS_FIRST_FRAME             : FirstFrame             (); break;
		case LWS_LAST_FRAME              : LastFrame              (); break;
		case LWS_FRAME_STEP              : FrameStep              (); break;
		case LWS_FRAMES_PER_SECOND       : FramesPerSecond        (); break;
		case LWS_PREVIEW_FIRST_FRAME     : PreviewFirstFrame      (); break;
		case LWS_PREVIEW_LAST_FRAME      : PreviewLastFrame       (); break;
		case LWS_PREVIEW_FRAME_STEP      : PreviewFrameStep       (); break;
		case LWS_CURRENT_FRAME           : CurrentFrame           (); break;
		case LWS_PLUGIN                  : Plugin                 (); break;
		case LWS_END_PLUGIN              : EndPlugin              (); break;

		//  Objects
		case LWS_ADD_NULL_OBJECT         : AddNullObject          (); break;
		case LWS_LOAD_OBJECT             : LoadObject             (); break;
		case LWS_LOAD_OBJECT_LAYER       : LoadObjectLayer        (); break;
		case LWS_SHOW_OBJECT             : ShowObject             (); break;
		case LWS_OBJECT_MOTION           : ObjectMotion           (); break;
		case LWS_OBJECT_DISSOLVE         : ObjectDissolve         (); break;
		case LWS_SUBDIVISION_ORDER       : SubdivisionOrder       (); break;
		case LWS_SUB_PATCH_LEVEL         : SubPatchLevel          (); break;
		case LWS_SHADOW_OPTIONS          : ShadowOptions          (); break;
		case LWS_DISTANCE_DISSOLVE       : DistanceDissolve       (); break;
		case LWS_MAX_DISSOLVE_DISTANCE   : MaxDissolveDistance    (); break;
		case LWS_PARTICLE_SIZE           : ParticleSize           (); break;
		case LWS_LINE_SIZE               : LineSize               (); break;
		case LWS_POLYGON_SIZE            : PolygonSize            (); break;
		case LWS_UNSEEN_BY_RAYS          : UnseenByRays           (); break;
		case LWS_UNSEEN_BY_CAMERA        : UnseenByCamera         (); break;
		case LWS_UNAFFECTED_BY_FOG       : UnaffectedByFog        (); break;
		case LWS_AFFECTED_BY_FOG         : AffectedByFog          (); break;
		case LWS_OBJ_POLYGON_EDGES       : ObjPolygonEdges        (); break;
		case LWS_OBJ_EDGE_COLOR          : ObjEdgeColor           (); break;
		case LWS_EXCLUDE_LIGHT           : ExcludeLight           (); break;
		case LWS_POLYGON_EDGE_FLAGS      : PolygonEdgeFlags       (); break;
		case LWS_POLYGON_EDGE_THICKNESS  : PolygonEdgeThickness   (); break;
		case LWS_POLYGON_EDGES_Z_SCALE   : PolygonEdgesZScale     (); break;
		case LWS_EDGE_NOMINAL_DISTANCE   : EdgeNominalDistance    (); break;

		case LWS_DISPLACEMENT_MAP        : DisplacementMap        (); break;
		case LWS_CLIP_MAP                : ClipMap                (); break;
		case LWS_TEXTURE_IMAGE           : TextureImage           (); break;
		case LWS_TEXTURE_FLAGS           : TextureFlags           (); break;
		case LWS_TEXTURE_AXIS            : TextureAxis            (); break;
		case LWS_TEXTURE_SIZE            : TextureSize            (); break;
		case LWS_TEXTURE_CENTER          : TextureCenter          (); break;
		case LWS_TEXTURE_FALLOFF         : TextureFalloff         (); break;
		case LWS_TEXTURE_VELOCITY        : TextureVelocity        (); break;
		case LWS_TEXTURE_AMPLITUDE       : TextureAmplitude       (); break;
		case LWS_TEXTURE_VALUE           : TextureValue           (); break;
		case LWS_TEXTURE_INT             : TextureInt             (); break;
		case LWS_TEXTURE_FLOAT           : TextureFloat           (); break;

		//  (for lights and cameras as well)
		case LWS_PIVOT_POSITION          : PivotPosition          (); break;
		case LWS_PARENT_ITEM             : ParentItem             (); break;
		case LWS_BEHAVIORS               : Behaviors              (); break;
		case LWS_NUM_CHANNELS            : NumChannels            (); break;
		case LWS_CHANNEL                 : Channel                (); break;
		case LWS_ENVELOPE                : Envelope               (); break;
		case LWS_KEY                     : Key                    (); break;
		case LWS_LOCKED_CHANNELS         : LockedChannels         (); break;
		case LWS_PARENT_OBJECT           : ParentObject           (); break;
		case LWS_TARGET_OBJECT           : TargetObject           (); break;
		case LWS_GOAL_OBJECT             : GoalObject             (); break;
		case LWS_SCHEMATIC_POSITION      : SchematicPosition      (); break;

		case LWS_MORPH_AMOUNT            : MorphAmount            (); break;
		case LWS_MORPH_TARGET            : MorphTarget            (); break;
		case LWS_MORPH_SURFACES          : MorphSurfaces          (); break;

		case LWS_USE_BONES_FROM          : UseBonesFrom           (); break;
		case LWS_BONE_FALLOFF_TYPE       : BoneFalloffType        (); break;
		case LWS_ADD_BONE                : AddBone                (); break;
		case LWS_BONE_NAME               : BoneName               (); break;
		case LWS_SHOW_BONE               : ShowBone               (); break;
		case LWS_BONE_ACTIVE             : BoneActive             (); break;
		case LWS_BONE_REST_POSITION      : BoneRestPosition       (); break;
		case LWS_BONE_REST_DIRECTION     : BoneRestDirection      (); break;
		case LWS_BONE_REST_LENGTH        : BoneRestLength         (); break;
		case LWS_BONE_STRENGTH           : BoneStrength           (); break;
		case LWS_SCALE_BONE_STRENGTH     : ScaleBoneStrength      (); break;
		case LWS_BONE_LIMITED_RANGE      : BoneLimitedRange       (); break;
		case LWS_BONE_MIN_RANGE          : BoneMinRange           (); break;
		case LWS_BONE_MAX_RANGE          : BoneMaxRange           (); break;
		case LWS_BONE_MOTION             : BoneMotion             (); break;
		case LWS_H_CONTROLLER            : HController            (); break;
		case LWS_P_CONTROLLER            : PController            (); break;
		case LWS_B_CONTROLLER            : BController            (); break;
		case LWS_H_LIMITS                : HLimits                (); break;
		case LWS_P_LIMITS                : PLimits                (); break;
		case LWS_B_LIMITS                : BLimits                (); break;
		case LWS_IK_ANCHOR               : IKAnchor               (); break;

		//  Lights - global
		case LWS_AMBIENT_COLOR           : AmbientColor           (); break;
		case LWS_AMBIENT_INTENSITY       : AmbientIntensity       (); break;
		case LWS_GLOBAL_FLARE_INTENSITY  : GlobalFlareIntensity   (); break;
		case LWS_ENABLE_LENS_FLARES      : EnableLensFlares       (); break;
		case LWS_ENABLE_SHADOW_MAPS      : EnableShadowMaps       (); break;

		//  Lights
		case LWS_ADD_LIGHT               : AddLight               (); break;
		case LWS_SHOW_LIGHT              : ShowLight              (); break;
		case LWS_LIGHT_NAME              : LightName              (); break;
		case LWS_LIGHT_MOTION            : LightMotion            (); break;
		case LWS_LIGHT_COLOR             : LightColor             (); break;
		case LWS_LIGHT_TYPE              : LightType              (); break;
		case LWS_LIGHT_FALLOFF_TYPE      : LightFalloffType       (); break;
		case LWS_LIGHT_RANGE             : LightRange             (); break;
		case LWS_LIGHT_CONE_ANGLE        : LightConeAngle         (); break;
		case LWS_LIGHT_EDGE_ANGLE        : LightEdgeAngle         (); break;
		case LWS_LIGHT_INTENSITY         : LightIntensity         (); break;
		case LWS_FALLOFF                 : Falloff                (); break;
		case LWS_AFFECT_CAUSTICS         : AffectCaustics         (); break;
		case LWS_AFFECT_DIFFUSE 	     : AffectDiffuse          (); break;
		case LWS_AFFECT_SPECULAR	     : AffectSpecular         (); break;
		case LWS_AFFECT_OPEN_GL 	     : AffectOpenGL           (); break;
		case LWS_USE_CONE_ANGLE          : UseConeAngle           (); break;
		case LWS_LENS_FLARE              : LensFlare              (); break;
		case LWS_FLARE_INTENSITY         : FlareIntensity         (); break;
		case LWS_FLARE_DISSOLVE          : FlareDissolve          (); break;
		case LWS_LENS_FLARE_FADE         : LensFlareFade          (); break;
		case LWS_LENS_FLARE_OPTIONS      : LensFlareOptions       (); break;
		case LWS_FLARE_RAND_STREAK_INT   : FlareRandStreakInt     (); break;
		case LWS_FLARE_RAND_STREAK_DENS  : FlareRandStreakDens    (); break;
		case LWS_FLARE_RAND_STREAK_SHARP : FlareRandStreakSharp   (); break;
		case LWS_SHADOW_TYPE             : ShadowType             (); break;
		case LWS_SHADOW_CASTING          : ShadowCasting          (); break;
		case LWS_SHADOW_MAP_SIZE         : ShadowMapSize          (); break;
		case LWS_SHADOW_MAP_ANGLE        : ShadowMapAngle         (); break;
		case LWS_SHADOW_FUZZINESS        : ShadowFuzziness        (); break;

		//  Cameras
		case LWS_ADD_CAMERA              : AddCamera              (); break;
		case LWS_CAMERA_NAME             : CameraName             (); break;
		case LWS_SHOW_CAMERA             : ShowCamera             (); break;
		case LWS_CAMERA_MOTION           : CameraMotion           (); break;
		case LWS_ZOOM_FACTOR             : ZoomFactor             (); break;
		case LWS_MOTION_BLUR             : MotionBlur             (); break;
		case LWS_BLUR_LENGTH             : BlurLength             (); break;
		case LWS_DEPTH_OF_FIELD          : DepthofField           (); break;
		case LWS_FOCAL_DISTANCE          : FocalDistance          (); break;
		case LWS_LENS_F_STOP             : LensFStop              (); break;

		case LWS_RESOLUTION_MULTIPLIER   : ResolutionMultiplier   (); break;
		case LWS_RESOLUTION              : Resolution             (); break;
		case LWS_FRAME_SIZE              : FrameSize              (); break;
		case LWS_CUSTOM_SIZE             : CustomSize             (); break;
		case LWS_FILM_SIZE               : FilmSize               (); break;
		case LWS_NTSC_WIDE_SCREEN        : NTSCWidescreen         (); break;
		case LWS_PIXEL_ASPECT            : PixelAspect            (); break;
		case LWS_PIXEL_ASPECT_RATIO      : PixelAspectRatio       (); break;
		case LWS_CUSTOM_PIXEL_RATIO      : CustomPixelRatio       (); break;
		case LWS_LIMITED_REGION          : LimitedRegion          (); break;
		case LWS_MASK_POSITION           : MaskPosition           (); break;
		case LWS_APERTURE_HEIGHT         : ApertureHeight         (); break;
		case LWS_REGION_LIMITS           : RegionLimits           (); break;
		case LWS_SEGMENT_MEMORY          : SegmentMemory          (); break;
		case LWS_ANTI_ALIASING           : Antialiasing           (); break;
		case LWS_ENHANCED_AA             : EnhancedAA             (); break;
		case LWS_FILTER_TYPE             : FilterType             (); break;
		case LWS_ADAPTIVE_SAMPLING       : AdaptiveSampling       (); break;
		case LWS_ADAPTIVE_THRESHOLD      : AdaptiveThreshold      (); break;
		case LWS_FIELD_RENDERING         : FieldRendering         (); break;
		case LWS_REVERSE_FIELDS          : ReverseFields          (); break;

		//  Effects
		case LWS_BG_IMAGE                : BGImage                (); break;
		case LWS_FG_IMAGE                : FGImage                (); break;
		case LWS_FG_ALPHA_IMAGE          : FGAlphaImage           (); break;
		case LWS_FG_DISSOLVE             : FGDissolve             (); break;
		case LWS_FG_FADER_ALPHA_MODE     : FGFaderAlphaMode       (); break;
		case LWS_IMAGE_SEQUENCE_INFO     : ImageSequenceInfo      (); break;
		case LWS_FOREGROUND_KEY          : ForegroundKey          (); break;
		case LWS_LOW_CLIP_COLOR          : LowClipColor           (); break;
		case LWS_HIGH_CLIP_COLOR         : HighClipColor          (); break;
		case LWS_SOLID_BACKDROP          : SolidBackdrop          (); break;
		case LWS_BACKDROP_COLOR          : BackdropColor          (); break;
		case LWS_ZENITH_COLOR            : ZenithColor            (); break;
		case LWS_SKY_COLOR               : SkyColor               (); break;
		case LWS_GROUND_COLOR            : GroundColor            (); break;
		case LWS_NADIR_COLOR             : NadirColor             (); break;
		case LWS_SKY_SQUEEZE_AMOUNT      : SkySqueezeAmount       (); break;
		case LWS_GROUND_SQUEEZE_AMOUNT   : GroundSqueezeAmount    (); break;
		case LWS_FOG_TYPE                : FogType                (); break;
		case LWS_FOG_MIN_DIST            : FogMinDist             (); break;
		case LWS_FOG_MAX_DIST            : FogMaxDist             (); break;
		case LWS_FOG_MIN_AMOUNT          : FogMinAmount           (); break;
		case LWS_FOG_MAX_AMOUNT          : FogMaxAmount           (); break;
		case LWS_FOG_COLOR               : FogColor               (); break;
		case LWS_BACKDROP_FOG            : BackdropFog            (); break;
		case LWS_DITHER_INTENSITY        : DitherIntensity        (); break;
		case LWS_ANIMATED_DITHER         : AnimatedDither         (); break;
		case LWS_SATURATION              : Saturation             (); break;
		case LWS_GLOW_EFFECT             : GlowEffect             (); break;
		case LWS_GLOW_INTENSITY          : GlowIntensity          (); break;
		case LWS_GLOW_RADIUS             : GlowRadius             (); break;

		//  Render
		case LWS_RENDER_MODE             : RenderMode             (); break;
		case LWS_RAY_TRACE_EFFECTS       : RayTraceEffects        (); break;
		case LWS_RAY_TRACE_OPTIMIZATION  : RayTraceOptimization   (); break;
		case LWS_RAY_RECURSION_LIMIT     : RayRecursionLimit      (); break;
		case LWS_DATA_OVERLAY            : DataOverlay            (); break;
		case LWS_DATA_OVERLAY_LABEL      : DataOverlayLabel       (); break;
		case LWS_OUTPUT_FILENAME_FORMAT  : OutputFilenameFormat   (); break;
		case LWS_SAVE_RGB                : SaveRGB                (); break;
		case LWS_SAVE_ALPHA              : SaveAlpha              (); break;
		case LWS_SAVE_ANIM_FILE_NAME     : SaveANIMFileName       (); break;
		case LWS_LOCK_ANIM_PALETTE_FRAME : LockANIMPaletteFrame   (); break;
		case LWS_BEGIN_ANIM_LOOP_FRAME   : BeginANIMLoopFrame     (); break;
		case LWS_SAVE_RGB_IMAGES_PREFIX  : SaveRGBImagesPrefix    (); break;
		case LWS_RGB_IMAGE_FORMAT        : RGBImageFormat         (); break;
		case LWS_SAVE_ALPHA_IMAGES_PREFIX: SaveAlphaImagesPrefix  (); break;
		case LWS_ALPHA_IMAGE_FORMAT      : AlphaImageFormat       (); break;
		case LWS_ALPHA_MODE              : AlphaMode              (); break;
		case LWS_SAVE_FRAMESTORES_COMMENT: SaveFramestoresComment (); break;
		case LWS_FULL_SCENE_PARAM_EVAL   : FullSceneParamEval     (); break;

		//  Layout Options
		case LWS_VIEW_CONFIGURATION      : ViewConfiguration      (); break;
		case LWS_DEFINE_VIEW             : DefineView             (); break;
		case LWS_VIEW_MODE               : ViewMode               (); break;
		case LWS_VIEW_AIMPOINT           : ViewAimpoint           (); break;
		case LWS_VIEW_ROTATION           : ViewRotation           (); break;
		case LWS_VIEW_ZOOM_FACTOR        : ViewZoomFactor         (); break;

		case LWS_LAYOUT_GRID             : LayoutGrid             (); break;
		case LWS_GRID_NUMBER             : GridNumber             (); break;
		case LWS_GRID_SIZE               : GridSize               (); break;
		case LWS_CAMERA_VIEW_BG          : CameraViewBG           (); break;
		case LWS_SHOW_MOTION_PATH        : ShowMotionPath         (); break;
		case LWS_SHOW_SAFE_AREAS         : ShowSafeAreas          (); break;
		case LWS_SHOW_BG_IMAGE           : ShowBGImage            (); break;
		case LWS_SHOW_FOG_RADIUS         : ShowFogRadius          (); break;
		case LWS_SHOW_FOG_EFFECT         : ShowFogEffect          (); break;
		case LWS_SHOW_REDRAW             : ShowRedraw             (); break;
		case LWS_SHOW_FIELD_CHART        : ShowFieldChart         (); break;

		case LWS_CURRENT_OBJECT          : CurrentObject          (); break;
		case LWS_CURRENT_LIGHT           : CurrentLight           (); break;
		case LWS_CURRENT_CAMERA          : CurrentCamera          (); break;
		case LWS_MAP_EDITOR_DATA         : GraphEditorData        (); break;
		case LWS_GRAPH_EDITOR_FAVORITES  : GraphEditorFavorites   (); break;

		case LWS_EOF:
			dmsg( M_LWS, "LWS_EOF" );
			cont = false;
			break;

		case LWS_ERROR:
			dmsg( M_LWS, "LWS_ERROR" );
			cont = false;
			break;

		case LWS_UNKNOWN:
			dmsg( M_LWS, "LWS_UNKNOWN" );
			break;

		default:
			dmsg( M_LWS, "default case" );
			break;
		}
	}
	dmsg( M_LWS, "Reading file %s done", fname );
}


};  //  namespace Imports
};  //  namespace Teddy


#if 0

//  Compute Hermite spline coeficients for t, where 0 <= t <= 1.
static void Hermite (
	double  t,
	double *h1,
	double *h2,
	double *h3,
	double *h4
){
	double t2;
	double t3;
	double z;

	t2 = t * t;
	t3 = t * t2;
	z  = 3.0 * t2 - t3 - t3;

	*h1 = 1.0 - z;
	*h2 = z;
	*h3 = t3 - t2 - t2 + t;
	*h4 = t3 - t2;
}


//  Compute the motion channel vector for the given step.  Step can be
//  fractional but values correspond to frames.
void MotionCalcStep (
	Motion  *mot,
	ChanVec  resVec,
	double   step
){
	KeyFrame *key0, *key1;
	double    t, h1, h2, h3, h4, res, d10;
	double    dd0a, dd0b, ds1a, ds1b;
	double    adj0, adj1, dd0, ds1;
	int       i, tlength;

	//  If there is but one key, the values are constant.
	if( mot->keys == 1 ){
        for( i=0; i<9; i++ ){
			resVec[i] = mot->keylist[0].cv[i];
		}
		return;
	}

	if( step > mot->steps ){
		step = mot->steps;
	}

	//  Get keyframe pair to evaluate.  This should be within the range
	//  of the motion or this will raise an illegal access.
	key0 = mot->keylist;
	while( step > key0[1].step ){
		key0 ++;
	}
	key1  = key0 + 1;
	step -= key0->step;

	// Get tween length and fractional tween position.
	tlength = key1->step - key0->step;
	t       = step / tlength;

	//  Precompute spline coefficients.
	if( !key1->linear ){
		Hermite (t, &h1, &h2, &h3, &h4);
		dd0a = (1.0 - key0->tens) * (1.0 + key0->cont) * (1.0 + key0->bias);
		dd0b = (1.0 - key0->tens) * (1.0 - key0->cont) * (1.0 - key0->bias);
		ds1a = (1.0 - key1->tens) * (1.0 - key1->cont) * (1.0 + key1->bias);
		ds1b = (1.0 - key1->tens) * (1.0 + key1->cont) * (1.0 - key1->bias);

		if( key0->step != 0 ){
		    adj0 = tlength / (double)(key1->step - (key0-1)->step);
		}
		if( key1->step != mot->steps ){
		    adj1 = tlength / (double)((key1+1)->step - key0->step);
		}
	}

	//  Compute the channel components.
	for( i=0; i<NUM_CHAN; i++ ){
		d10 = key1->cv[i] - key0->cv[i];

		if( !key1->linear ){
			if( key0->step == 0){
				dd0 = .5 * (dd0a + dd0b) * d10;
			}else{
				dd0 = adj0 * (dd0a * (key0->cv[i] - (key0-1)->cv[i]) + dd0b * d10);
			}

			if( key1->step == mot->steps ){
				ds1 = .5 * (ds1a + ds1b) * d10;
			}else{
				ds1 = adj1 * (ds1a * d10 + ds1b * ((key1+1)->cv[i] - key1->cv[i]));
			}

			res = key0->cv[i] * h1 + key1->cv[i] * h2 + dd0 * h3 + ds1 * h4;
		}else{
			res = key0->cv[i] + t * d10;
		}

		resVec[i] = res;
	}
}

#endif  //  0


#endif  //  TEDDY_INCLUDE_LW_SCENE
