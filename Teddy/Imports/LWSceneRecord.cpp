
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


/*
	RenderMode <value>

	example:  RenderMode 2

	The RenderMode function determines the type of rendering for the scene.

	<value>:
		0 - WireFrame
		1 - Quickshade
		2 - Realistic (Default)
*/
void LWSceneParser::RenderMode(){
	int render_mode = file->read_int();
}


/*
	RayTraceEffects <bit-field value>

	example:  RayTraceEffects 7

	The RayTraceEffects function determines the ray trace options for the scene.

	The value is produced by calculating the decimal value of a 3 position 
	bit-field whose bits represent logical on/off switches that are numbered 
	left to right from 0 - 2.  The field's least-significant bit is the 
	rightmost bit.  Each ray trace option has a corresponding bit in this 
	bit-field.  When an option is selected, it's bit (or switch) is turned on.

	<bit position>:
		0 - Trace Shadows
		1 - Trace Reflection
		2 - Trace Refraction
*/
void LWSceneParser::RayTraceEffects(){
	int ray_trace_effects = file->read_int();
}


void LWSceneParser::RayTraceOptimization(){
	int ray_trace_optimization = file->read_int();
}


void LWSceneParser::RayRecursionLimit(){
	int ray_recursion_limit = file->read_int();
}


/*
	DataOverlay <flag>

	example:  DataOverlay 1

	The DataOverlay flag activates the data overlay function that overlays a 
	string provide by the DataOverlayLabel function on the rendered frames.

	<flag>:
		0 - Off (No Listing)
		1 - On
*/
void LWSceneParser::DataOverlay(){
	int data_overlay = file->read_int();
}


/*
	DataOverlayLabel <string>

	example:  DataOverlayLabel Scene1_4/16/95

	The DataOverlayLabel function provides the string to be used by the 
	DataOverlay function.
*/
void LWSceneParser::DataOverlayLabel(){
	file->skip();
	//char *data_overlay_label = file->read_string();
}


void LWSceneParser::OutputFilenameFormat(){
	file->skip();
	//int output_filename_format = file->read_int();
}


void LWSceneParser::SaveRGB(){
	int save_rgb = file->read_int();
}


void LWSceneParser::SaveAlpha(){
	int save_alpha = file->read_int();
}


/*
	SaveANIMFileName <image path + filename>

	example:  SaveANIMFileName Anims\LogoAnim

	The SaveANIMFileName function provides the path and filename for the 
	animation to be saved during rendering.

	In this example, if the current content directory is <c:\NewTek>, 
	LightWave would attempt to save the anim file as <c:\NewTek\Anims\LogoAnim>.

	Some animation formats produce additional function listings.
*/
void LWSceneParser::SaveANIMFileName(){
	char *anim_file_name = file->read_string();
}


/*
	Additional:  LockANIMPaletteFrame <frame number>

	example:  LockANIMPaletteFrame 12

	The LockANIMPaletteFrame function provides the frame number to be 
	rendered for the palette information.  The palette of all frames 
	rendered in the animation will then use the given frames palette.
*/
void LWSceneParser::LockANIMPaletteFrame(){
	int lock_anim_palette_frame = file->read_int();
}


/*
	Additional:  BeginANIMLoopFrame <frame number>

	example:  BeginANIMLoopFrame 15

	The BeginANIMLoopFrame function provides the frame number to loop the 
	animation from.  After the animation is completed, it would continue 
	looping from the given frame to the end of the animation.
*/
void LWSceneParser::BeginANIMLoopFrame(){
	int begin_anim_loop_frame = file->read_int();
}


/*
	SaveRGBImagesPrefix<image path + filename>

	example:  SaveRGBImagesPrefix Images\LogoFrames

	The SaveRGBImagesPrefix function provides the path and filename prefix 
	for the images to be saved during rendering.  A frame number and optional 
	file extension will be added to this filename.  This additional information 
	is provided by the Output Filename Format config file listing and the 
	RGBImageFormat function.  

	In this example, if the current content directory is <c:\NewTek>, the 
	Output Filename Format is set to Name001.xxx, and the Image Format is 
	24-bit Targa,  LightWave would attempt to save the first image file as 
	<c:\NewTek\Images\LogoFrames001.tga>.
*/
void LWSceneParser::SaveRGBImagesPrefix(){
	char *rgb_images_prefix = file->read_string();
}


/*
	Additional:  RGBImageFormat <value>

	example:  RGBImageFormat 2

	The RGBImageFormat function determines which file format will be 
	used in the image saving process.

	<value>:
		0 - 24-bit IFF (.IFF)
		1 - 24-bit RAW (.RAW)
		2 - 24-bit Targa (.TGA)
*/
void LWSceneParser::RGBImageFormat(){
	int rgb_image_format = file->read_int();
}


/*
	SaveAlphaImagesPrefix<image path + filename>

	example:  SaveAlphaImagesPrefix Images\LogoAlpha

	The SaveAlphaImagesPrefix function provides the path and filename prefix 
	for the alpha images to be saved during rendering.  A frame number and 
	optional file extension will be added to this filename.  This additional 
	information is provided by the Output  Filename Format config file listing 
	and the AlphaImageFormat function.  

	In this example, if the current content directory is <c:\NewTek>, the 
	Output Filename Format is set to Name001.xxx, and the Alpha Image Format 
	is 24-bit IFF,  LightWave would attempt to save the first image file as 
	<c:\NewTek\Images\LogoAlpha001.tga>.
*/
void LWSceneParser::SaveAlphaImagesPrefix(){
	char *alpha_images_prefix = file->read_string();
}


/*
	Additional:  AlphaImageFormat <value>

	example:  AlphaImageFormat 1

	The AlphaImageFormat function determines which file format will 
	be used in the image saving process.

	<value>:
		0 - 8-bit IFF (.IFF)
		1 - 24-bit IFF (.IFF)
*/
void LWSceneParser::AlphaImageFormat(){
	int alpha_image_format = file->read_int();
}


/*
	AlphaMode <value>

	example:  AlphaMode 1

	The AlphaMode functions determines which type of alpha image is 
	going to be produced during the rendering process.

	<value>:
		0 - Normal Alpha
		1 - Fader Alpha Mode
*/
void LWSceneParser::AlphaMode(){
	int alpha_mode = file->read_int();
}


/*
	SaveFramestoresComment <image path + filename>

	example:  SaveFramestoreComment  Images\Frame

	The SaveFramestoreComment function provides the path and
	filename prefix for the framestores to be saved during
	rendering.  A frame number and optional file extension
	will be added to this filename.  

	In this example, if the current content directory i
	<c:\NewTek>, LightWave would attempt to save the first
	image file as <c:\NewTek\Images\001.FS.Frame>.
*/
void LWSceneParser::SaveFramestoresComment(){
	char *framestores_comment = file->read_string();
}


void LWSceneParser::FullSceneParamEval(){
	int full_scene_param_evel = file->read_int();
}


};  //  namespace Imports
};  //  namespace Teddy


#endif  //  TEDDY_INCLUDE_LW_SCENE


/*
The effects section contains the information on the saving of animations, 
RGB images and Alpha images.

Record functions produce a listing only when activated by the user.

The file saving process is not active when the scene is loaded into
LightWave.  The file name is available to the record functions.  The user 
must activate the save function manually to begin the saving process.

	SaveANIMFileName
		LockANIMPaletteFrame
		BeginANIMLoopFrame
	SaveRGBImagesPrefix
		RGBImageFormat
	SaveAlphaImagesPrefix
		AlphaImageFormat
		AlphaMode
	SaveFramestoresComment
*/

