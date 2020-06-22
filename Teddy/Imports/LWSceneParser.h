
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


#ifndef TEDDY__IMPORTS__LW_SCENE_PARSER_H
#define TEDDY__IMPORTS__LW_SCENE_PARSER_H


#include "Teddy/TeddyConfig.h"
#if defined( TEDDY_INCLUDE_LW_SCENE )


#include "Teddy/Graphics/Color.h"
#include "Teddy/Imports/LWSceneTokens.h"
#include "Teddy/MixIn/Options.h"
#include "Teddy/MixIn/Tick.h"
#include "Teddy/Models/Grid.h"
#include "Teddy/Scenes/Scene.h"
#include "Teddy/SysSupport/StdMap.h"


namespace Teddy   {
namespace Imports {


class LWBone;
class LWCamera;
class LWChannelEnvelope;
class LWInstance;
class LWLight;
class LWMotion;
class LWSceneFile;


/*
struct less_str {
	bool operator()( char *a, char *b ) const {
		if( strcmp(a,b) < 0 ){
			return true;
		}else{
			return false;
		}
	}
};*/


typedef map<int,   LWInstance*> int_to_LWInstance;
typedef map<int,   LWLight   *> int_to_LWLight;
typedef map<int,   LWCamera  *> int_to_LWCamera;


/*!
	\brief Parses Lightwave scene files
	\todo  Lights
	\todo  FOV

	This is very beta version of Lightwave Scene player.
	Only very simply features are present at the moment.
*/
class LWSceneParser : public Teddy::MixIn::Tick {
public:
	static const int OPT_GRID;
	static const int OPT_DARK_GRID;

public:
    LWSceneParser( Teddy::Scenes::Scene *scene, Teddy::Scenes::Camera *camera, const char *fname, Teddy::MixIn::Options options );

	void         reset        ();
	void         play         ();
	void         stop         ();
	void         update       ();
	void         setMultiplier( float multiplier );
	float        getMultiplier();
	float        getTime      ();
	virtual void tick         ();

	Teddy::Graphics::Color        getZenithColor   ();
	Teddy::Graphics::Color        getSkyColor      ();
	Teddy::Graphics::Color        getGroundColor   ();
    Teddy::Graphics::Color        getNadirColor    ();
    Teddy::Models::Grid          *getGrid          ();
	float                         getGridSize      ();
	Teddy::Maths::TVector<float>  getViewAimpoint  ();
	Teddy::Maths::Quaternion      getViewRotation  ();
	float                         getViewZoomFactor();

protected:
	void readFile   ( const char *fname );
	void postProcess();

protected:
	//  Playback
	bool                   playing;
	float                  multiplier;
	float                  stop_time;
	float                  start_time;
	float                  last_used_time;

	//  Parsing
    Teddy::MixIn::Options  options;
	LWSceneFile           *file;
    int                    lws_version;
    Teddy::Models::Grid   *grid;

	//  Scenes
	int                    first_frame;
	int                    last_frame;
	int                    frame_step;
	int                    frames_per_second;
	int                    preview_first_frame;
	int                    preview_last_frame;
	int                    preview_frame_step;
	int                    current_frame;

	//  Objects
    Teddy::Scenes::Scene   *scene;
	Teddy::Scenes::Camera  *camera;
	LWInstance             *current_object;            //  Current object
	LWMotion               *current_motion;            //  Current motion for current object
	int                     num_channels;              //  Number of channels in current motion
	int                     read_channels;             //  Number of channels processed
	LWChannelEnvelope      *current_channel_envelope;  //  Current channel envelope of current motion
	int                     num_channel_keys;          //  Number of keys in current channel envelope
	int                     read_channel_keys;         //  Number of channel keys processed
	LWBone                 *current_bone;              //  Current bone

	void                    resolveParent( LWInstance *object );

	//  Lights - global
    Teddy::Graphics::Color  ambient_color;
	double                  amb_intensity;       //  envelope not yet supported
	bool                    enable_lens_flare;   //  default true
	bool                    enable_shadow_maps;  //  default true

	//  Lights
	LWLight                *current_light;

	//  Cameras
	LWCamera               *current_camera;

	//  Options (Layout)
	int                           grid_number;
	float                         grid_size;
	Teddy::Maths::TVector<float>  view_aimpoint;
	Teddy::Maths::Quaternion      view_rotation;
	float                         view_zoom_factor;

	//  Effects
	Teddy::Graphics::Color  zenith_color;
	Teddy::Graphics::Color  sky_color;
	Teddy::Graphics::Color  ground_color;
	Teddy::Graphics::Color  nadir_color;

	//  Containers
	int                     next_object;
	int                     next_light;
	int                     next_camera;
	int_to_LWInstance       objects;
	int_to_LWLight          lights;
	int_to_LWCamera         cameras;

protected:
	//  Scenes
	void LWSC();
	void FirstFrame();
	void LastFrame();
	void FrameStep();
	void FramesPerSecond();
	void PreviewFirstFrame();
	void PreviewLastFrame();
	void PreviewFrameStep();
	void CurrentFrame();
	void Plugin();
	void EndPlugin();
	
	//  Objects
	void AddNullObject();
	void LoadObject();
	void LoadObjectLayer();
	void ShowObject();
	void ObjectMotion();
	void ObjectDissolve();
	void SubdivisionOrder();
	void SubPatchLevel();
	void ShadowOptions();
	void DistanceDissolve();
	void MaxDissolveDistance();
	void ParticleSize();
	void LineSize();
	void PolygonSize();
	void UnseenByRays();
	void UnseenByCamera();
	void UnaffectedByFog();
	void AffectedByFog();
	void ExcludeLight();
	void ObjPolygonEdges();
	void ObjEdgeColor();
	void PolygonEdgeFlags();
	void PolygonEdgeThickness();
	void PolygonEdgesZScale();
	void EdgeNominalDistance();

	void DisplacementMap();
	void ClipMap();
	void TextureImage();
	void TextureFlags();
	void TextureAxis();
	void TextureSize();
	void TextureCenter();
	void TextureFalloff();
	void TextureVelocity();
	void TextureAmplitude();
	void TextureValue();
	void TextureInt();
	void TextureFloat();

	//  (for lights and
	void PivotPosition();
	void ParentItem();
	void Behaviors();
	void NumChannels();
	void Channel();
	void Envelope();
	void Key();
	void LockedChannels();
	void ParentObject();
	void TargetObject();
	void GoalObject();
	void SchematicPosition();

	void MorphAmount();
	void MorphTarget();
	void MorphSurfaces();

	void UseBonesFrom();
	void BoneFalloffType();
	void AddBone();
	void BoneName();
	void ShowBone();
	void BoneActive();
	void BoneRestPosition();
	void BoneRestDirection();
	void BoneRestLength();
	void BoneStrength();
	void ScaleBoneStrength();
	void BoneLimitedRange();
	void BoneMinRange();
	void BoneMaxRange();
	void BoneMotion();
	void HController();
	void PController();
	void BController();
	void HLimits();
	void PLimits();
	void BLimits();
	void IKAnchor();

	//  Lights - global
	void AmbientColor();
	void AmbIntensity();
	void AmbientIntensity();
	void GlobalFlareIntensity();
	void EnableLensFlares();
	void EnableShadowMaps();

	//  Lights
	void AddLight();
	void ShowLight();
	void LightName();
	void LightMotion();
	void LightColor();
	void LightType();
	void LightFalloffType();
	void LightRange();
	void LightConeAngle();
	void LightEdgeAngle();
	void LightIntensity();
	void Falloff();
	void AffectCaustics();
	void AffectDiffuse();
	void AffectSpecular();
	void AffectOpenGL();
	void ConeAngle();
	void EdgeAngle();
	void UseConeAngle();
	void LensFlare();
	void FlareIntensity();
	void FlareDissolve();
	void LensFlareFade();
	void LensFlareOptions();
	void FlareRandStreakInt();
	void FlareRandStreakDens();
	void FlareRandStreakSharp();
	void ShadowType();
	void ShadowCasting();
	void ShadowMapSize();
	void ShadowMapAngle();
	void ShadowFuzziness();

	//  Cameras
	void AddCamera();
	void CameraName();
	void ShowCamera();
	void CameraMotion();
	void ZoomFactor();
	void MotionBlur();
	void BlurLength();
	void DepthofField();
	void FocalDistance();
	void LensFStop();

	void ResolutionMultiplier();
	void Resolution();
	void FrameSize();
	void CustomSize();
	void FilmSize();
	void NTSCWidescreen();
	void PixelAspect();
	void PixelAspectRatio();
	void CustomPixelRatio();
	void LimitedRegion();
	void MaskPosition();
	void ApertureHeight();
	void RegionLimits();
	void SegmentMemory();
	void Antialiasing();
	void EnhancedAA();
	void FilterType();
	void AdaptiveSampling();
	void AdaptiveThreshold();
	void FieldRendering();
	void ReverseFields();

	//  Effects
	void BGImage();
	void FGImage();
	void FGAlphaImage();
	void FGDissolve();
	void FGFaderAlphaMode();
	void ImageSequenceInfo();
	void ForegroundKey();
	void LowClipColor();
	void HighClipColor();
	void SolidBackdrop();
	void BackdropColor();
	void ZenithColor();
	void SkyColor();
	void GroundColor();
	void NadirColor();
	void SkySqueezeAmount();
	void GroundSqueezeAmount();
	void FogType();
	void FogMinDist();
	void FogMaxDist();
	void FogMinAmount();
	void FogMaxAmount();
	void FogColor();
	void BackdropFog();
	void DitherIntensity();
	void AnimatedDither();
	void Saturation();
	void GlowEffect();
	void GlowIntensity();
	void GlowRadius();
	
	//  Render
	void RenderMode();
	void RayTraceEffects();
	void RayTraceOptimization();
	void RayRecursionLimit();
	void DataOverlay();
	void DataOverlayLabel();
	void OutputFilenameFormat();
	void SaveRGB();
	void SaveAlpha();
	void SaveANIMFileName();
	void LockANIMPaletteFrame();
	void BeginANIMLoopFrame();
	void SaveRGBImagesPrefix();
	void RGBImageFormat();
	void SaveAlphaImagesPrefix();
	void AlphaImageFormat();
	void AlphaMode();
	void SaveFramestoresComment();
	void FullSceneParamEval();

	//  Layout Options
	void ViewConfiguration();
	void DefineView();
	void ViewMode();
	void ViewAimpoint();
	void ViewRotation();
	void ViewZoomFactor();

	void LayoutGrid();
	void GridNumber();
	void GridSize();
	void CameraViewBG();
	void ShowMotionPath();
	void ShowSafeAreas();
	void ShowBGImage();
	void ShowFogRadius();
	void ShowFogEffect();
	void ShowRedraw();
	void ShowFieldChart();

	void CurrentObject();
	void CurrentLight();
	void CurrentCamera();
	void GraphEditorData();
	void GraphEditorFavorites();
};


};  //  namespace Imports
};  //  namespace Teddy


#endif  //  TEDDY_INCLUDE_LW_SCENE
#endif  //  TEDDY__IMPORTS__LW_SCENE_PARSER_H

