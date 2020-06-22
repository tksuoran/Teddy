
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


#include "Teddy/Imports/LWCamera.h"
#include "Teddy/Imports/LWMotion.h"
#include "Teddy/Imports/LWSceneFile.h"
#include "Teddy/Imports/LWSceneParser.h"


namespace Teddy   {
namespace Imports {





/*
ParentObject <object instance>

example:     ParentObject 4

This function provides LightWave with the camera's parent object in the 
hierarchical chain.  The value is equal to the parent objects position 
in the loading/creation sequence.  The example function would parent the 
camera to the fourth object instance in the scene file.  When the 
ParentObject function is active, all keyframe information for the camera 
becomes an offset from the parents information. 
*/

/*

TargetObject <object instance>

example:  TargetObject 3

This function provides LightWave with the camera's target object in the 
scene.  The value is equal to the target object's position in the 
loading/creation sequence.  The example function would target the 
camera at the third object instance in the scene file. 
*/


void LWSceneParser::AddCamera(){
	current_object = current_camera = new LWCamera();
	cameras.insert( make_pair(next_camera,current_camera) );
	next_camera++;
}

void LWSceneParser::CameraName(){
	/*char *camera_name = file->read_string();
	current_object->setModelName( camera_name );*/
}


/*
	ShowCamera <Refresh value> <Color value>

	example:     ShowCamera 0 5

	The ShowCamera function determines how the camera is going to be displayed 
	in Layout.  The above example would hide the camera until selected.  If it 
	were set to visible refresh, it would be purple when not selected.


	Refresh value

	This argument sets the camera display type in Layout.  

	<Refresh value>:	0 - No Refresh (Hide)
			1 - Refresh (Show)

	User:  This value is selected in the second column of the Scene Overview from 
	the Scene Menu.  	


	Color value

	This argument sets the color of the camera wireframe in Layout.  When the 
	camera is selected, the wireframe highlights to yellow. 

	<Color value>:	1 - Blue
		2 - Green
		3 - Light Blue
		4 - Red
		5 - Purple
		6 - Orange
		7 - Gray

	User: This value is selected in the first column of the Scene Overview from 
	the Scene Menu.
*/
void LWSceneParser::ShowCamera(){
	int refresh_value = file->read_int();
	int color_value   = file->read_int();
}


void LWSceneParser::CameraMotion(){
	current_motion = new LWMotion();
	current_object->setMotion( current_motion );
}


/*
	ZoomFactor <float> � (envelope)

	example:  ZoomFactor 3.200000

	The ZoomFactor function provides a floating point number that represents 
	the zoom amount of the camera's lens.  This function can be fluctuated over 
	time with an envelope.  If an envelope is chosen, the floating point value 
	is replaced with an envelope identifier.
*/
void LWSceneParser::ZoomFactor(){
	double zoom_factor = file->read_double();
}


/*
	MotionBlur <bit-field value>

	example:  MotionBlur 7

	The MotionBlur function determines the active motion blur functions for the 
	rendering process.  When particle blur or motion blur are selected, they 
	produce an additional BlurLength listing.

	The value is produced by calculating the decimal value of a 3 position 
	bit-field whose bits represent logical on/off switches that are numbered 
	left to right from 0 - 2.  The field's least-significant bit is the 
	rightmost bit.  Each motion blur option has a corresponding bit in this 
	bit-field.  When an option is selected, it's bit (or switch) is turned on.

	<bit position>:	0 - Particle Blur (Additional Listing)
			1 - Motion Blur (Additional Listing)
			2 - Dithered Motion Blur
*/
void LWSceneParser::MotionBlur(){
	int motion_blur = file->read_int();
}


/*
	Additional:  BlurLength <percentage> � (envelope)

	example:  BlurLength 0.500000

	The BlurLength function provides the amount of blur to be applied 
	during the rendering process.
*/
void LWSceneParser::BlurLength(){
	double blur_length = file->read_double();
}


/*
	DepthofField <flag>

	example:  DepthofField 1

	The DepthofField flag activates the depth of field function for the 
	rendering process.  This function, when activated, produces additional 
	FocalDistance and LensFStop listings.

	<flag>:	0 - Off (Listing)
		1 - On (Listing plus additional Listings)
*/
void LWSceneParser::DepthofField(){
	int depth_of_field = file->read_int();
}


/*
	Additional:  FocalDistance <Distance> � (envelope)

	example:  FocalDistance 25.0000

	The FocalDistance function provides the distance from the camera of 
	it's focal point.  This distance is given in meters.
*/
void LWSceneParser::FocalDistance(){
	double focal_distance = file->read_double();
}


/*
	Additional:  LensFStop <float> � (envelope)

	example:  LensFStop 4.000000

	The LensFStop function determines the range of in-focus items from 
	the focal point.  The larger the F-stop, the larger the focal range.
*/
void LWSceneParser::LensFStop(){
	double lens_f_stop = file->read_double();
}


void LWSceneParser::ResolutionMultiplier(){
	double resolution_multiplier = file->read_double();
}

void LWSceneParser::FrameSize(){
	int frame_width  = file->read_int();
	int frmae_height = file->read_int();
}


/*
	Resolution <value>

	example:  Resolution 1

	The Resolution function determines the resolution of the rendering in 
	the current scene.

	<value>:	-1 - Super Low Resolution
			 0 - Low Resolution
			 1 - Medium Resolution
			 2 - High Resolution
			 3 - Print Resolution
*/
void LWSceneParser::Resolution(){
	int resolution = file->read_int();
}


/*
	CustomSize <Horizontal resolution> <Vertical resolution>

	example:  Custom Size 1024 768

	The CustomSize function provides the horizontal and vertical pixel 
	resolutions for rendering.
*/
void LWSceneParser::CustomSize(){
	int horizontal_resolution = file->read_int();
	int vertical_resolution   = file->read_int();
}


/*
	FilmSize <value>

	example:  FilmSize 1

	The FilmSize function determines what type of film LightWave is going to 
	simulate during the rendering process.  This adjusts the optical qualities 
	in the cameras adjustment of zoom factor and depth of field.

	<value>:	 0 - Super 8 motion picture
			 1 - 16mm motion picture
			 2 - 35mm motion picture (Default)
			 3 - 65mm Super Panavision motion picture
			 4 - 65mm Imax motion picture
			 5 - Size 110 (pocket camera)
			 6 - Size 135 (35mm SLR)
			 7 - Size 120 (60 x 45 mm rollfilm camera)
			 8 - Size 120 (90 x 60 mm rollfilm camera)
			 9 - 1/3 " CCD video camera
			10 - 1/2" CCD video camera
*/
void LWSceneParser::FilmSize(){
	int film_size = file->read_int();
}


/*
	NTSCWidescreen <flag>

	example:  NTSCWidescreen 1

	The NTSCWidescreen flag activates a function that will compress the 
	rendered image horizontally.  When this image is displayed in the 
	NTSC Widescreen format it will display in the proper aspect.
*/
void LWSceneParser::NTSCWidescreen(){
	int ntsc_widescreen = file->read_int();
}


void LWSceneParser::PixelAspect(){
	double pixel_aspect = file->read_double();
}


/*
	PixelAspectRatio <value>

	example:  PixelAspectRatio 0

	The PixelAspectRatio function provides the aspect (shape) of the pixel 
	in a rendered image.

	<value>:	-1 - Custom (Produces Additional CustomPixelRatio Listing)
			 0 - D2 NTSC
			 1 - D1 NTSC
			 2 - Square Pixels
			 3 - D2 PAL
			 4 - D1 PAL

*/
void LWSceneParser::PixelAspectRatio(){
	int pixel_aspect_ratio = file->read_int();
}


/*
	Additional:  CustomPixelRatio <float>

	example:  CustomPixelRatio 1.000000

	The CustomPixelRatio function provides a custom pixel aspect for 
	rendering.  The floating point value is the height to width ratio 
	of the needed pixels. 
*/
void LWSceneParser::CustomPixelRatio(){
	double custom_pixel_ration = file->read_double();
}


/*
	LimitedRegion <flag>

	example:  LimitedRegion 1

	The LimitedRegion flag activates the limited region function to render a 
	portion of the full camera view.  This function, when activated, produces 
	an additional RegionLimits listing.

	<flag>:	0 - Off (No Listing)
		1 - On (Listing plus additional RegionLimits listing)
*/
void LWSceneParser::LimitedRegion(){
	int limited_region = file->read_int();
}


/*
	Additional:  RegionLimits <Left %><Right %><Top %><Bottom %>

	example: RegionLimits 0.50000 1.000000 0.500000 1.000000

	The RegionLimits function provides the dimensions of the area to be
 	rendered for the LimitedRegion function.  The values given are a 
	percentage of screen size.

	<% limits>:	Left 	- 	0.000000 to 0.990000
			Right 	- 	0.010000 to 1.000000
			Top 	- 	0.000000 to 0.990000
			Bottom 	- 	0.010000 to 1.000000
*/
void LWSceneParser::RegionLimits(){
	double left   = file->read_double();
	double right  = file->read_double();
	double top    = file->read_double();
	double bottom = file->read_double();
}

void LWSceneParser::MaskPosition(){
	int mask_x1 = file->read_int();
	int mask_y1 = file->read_int();
	int mask_x2 = file->read_int();
	int mask_y2 = file->read_int();
}


void LWSceneParser::ApertureHeight(){
	double aperture_height = file->read_double();
}


/*
	SegmentMemory <bytes>

	example: SegmentMemory 88000000

	The SegmentMemory determines the amount of memory to be allocated for the 
	rendering process.  If the amount of memory is too low, LightWave will 
	divide the rendering process into separate segments.
*/
void LWSceneParser::SegmentMemory(){
	int segment_memory = file->read_int();
}


/*
	Antialiasing <value>

	example:  Antialiasing  2

	The Antialiasing function determines the number of antialiasing (smoothing) 
	passes that will be used for rendering.

	<value>:	0 - Off
			1 - Low Antialiasing (5 passes)
			2 - Medium Antialiasing (9 passes)
			3 - High Antialiasing (17 passes)
*/
void LWSceneParser::Antialiasing(){
	int antialiasing = file->read_int();
}


void LWSceneParser::EnhancedAA(){
	int enchaced_aa = file->read_int();
}


/*
	FilterType<flag>

	example:  FilterType 1

	The FilterType flag activates the Soft Filter effect for the rendering process.

	<flag>:	0 - Off (No listing)
		1 - On (Listing)
*/
void LWSceneParser::FilterType(){
	int filter_type = file->read_int();
}


/*
	AdaptiveSampling <flag>

	example:  AdaptiveSampling 1

	The AdaptiveSampling flat activates adaptive sampling for the rendering 
	process.  This function, when activated, produces an additional 
	AdaptiveThreshold listing.

	<flag>:	0 - Off (Listing)
		1 - On (Listing plus additional AdaptiveThreshold listing)
*/
void LWSceneParser::AdaptiveSampling(){
	int adaptive_sampling = file->read_int();
}


/*
	Additional:  AdaptiveThreshold <int>

	TIS: appears to use doubles in LWSC 3

	example:  AdaptiveThreshold 8

	The AdaptiveThreshold function provides a value for the level of 
	adaptive sampling during the rendering process.  This value is a 
	threshold, or cutoff level, for the antialiasing process. 
*/
void LWSceneParser::AdaptiveThreshold(){
	double adaptive_treshold = file->read_double();
}


/*
	FieldRendering <flag>

	example:  FieldRendering 1

	The FieldRendering flag activates the field rendering function during the 
	rendering process.  This function, when activated, produces an additional 
	ReverseFields listing.

	<flag>:	0 - Off (Listing)
		1 - On (Listing plus additional ReverseFields listing)
*/
void LWSceneParser::FieldRendering(){
	int field_rendering = file->read_int();
}


/*
	Additional:  ReverseFields <flag>

	example:  ReverseFields 1

	The ReverseFields flag activates the reverse fields function.  
	This function shifts the order in which the fields are rendered.
*/
void LWSceneParser::ReverseFields(){
	int reverse_field = file->read_int();
}


};  //  namespace Imports
};  //  namespace Teddy


#endif  //  TEDDY_INCLUDE_LW_SCENE


/*

The Camera Section contains all of the information that relates to the 
camera in a LightWave Scene.

  There is only one (1) camera instance per scene file.

  The Target and Parent functions use a value that is equal to the order 
  in which the referenced object was loaded/created in the scene.  i.e. The 
  value given in the example: ParentObject 3  references the third object 
  instance in the scene file.


The following is a list of light functions that are listed in the order in 
which they appear in the scene file.

  Functions denoted with an asterisk (*) are required for all light loading 
  instances.
  Italicized entries denote function labels and not true function names.
  Indented entries denote an optional function of the preceding function.
  Optional functions will produce a listing only when activated by the user.

		ShowCamera *
		CameraMotion (identifier) *
		Number of Information Channels *
		Number of Keyframes *
		Keyframe Information *
		EndBehavior *
		LockedChannels
		ParentObject
		TargetObject
		ZoomFactor *
		RenderMode *
		RayTraceEffects *
		Resolution *
		CustomSize
		NTSCWidescreen
		PixelAspectRatio
			CustomPixelRatio
		LimitedRegion
			RegionLimits
		SegmentMemory *
		Antialiasing *
		FilterType
		AdaptiveSampling *
			AdaptiveThreshold
		FilmSize *
		FieldRendering *
			ReverseFields
		MotionBlur *
			BlurLength
		DepthofField *
			FocalDistance
			LensFStop
*/


