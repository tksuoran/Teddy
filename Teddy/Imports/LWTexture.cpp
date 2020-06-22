
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


#if defined(_MSC_VER)
#	pragma warning(disable:4786)
#endif


#include "Teddy/Imports/LWFile.h"
#include "Teddy/Imports/LWLayer.h"
#include "Teddy/Imports/LWSurface.h"
#include "Teddy/Imports/LWModel.h"
#include "Teddy/Imports/LWTexture.h"
#include "Teddy/Models/Geometry.h"
#include "Teddy/Graphics/ImageFileTexture.h"
#include "Teddy/Graphics/PixFileTexture.h"
#include "Teddy/SysSupport/FileScan.h"
#include "Teddy/SysSupport/StdIO.h"
#include "Teddy/SysSupport/Messages.h"
using namespace Teddy::Materials;


namespace Teddy   {
namespace Imports {


LWTexture::LWTexture( LWSurface *surface, int map_type ){
	this->f       = surface->getLayer()->getModel()->getFile();
	this->surface = surface;
	switch( map_type ){
	case LW_PLANAR_IMAGE_MAP     : texture_projection_mode = LW_PROJECTION_PLANAR     ; break;
	case LW_CYLINDRICAL_IMAGE_MAP: texture_projection_mode = LW_PROJECTION_CYLINDRICAL; break;
	case LW_SPHERICAL_IMAGE_MAP  : texture_projection_mode = LW_PROJECTION_SPHERICAL  ; break;
	case LW_CUBIC_IMAGE_MAP      : texture_projection_mode = LW_PROJECTION_CUBIC      ; break;
	default: emsg( M_LWO, "Unknown projection mode" ); break;
	}
	texture_center            = Vector(0,0,0);        //!<  TCTR
	texture_size              = Vector(1,1,1);        //!<  TSIZ
//	texture_projection_mode   = LW_PLANAR_IMAGE_MAP;  //!<  CTEX
	texture_major_axis        = TEXTURE_AXIS_X;       //!<  TFLG
	texture_antialiasing_type = 0;                    //!<  TFLG
	texture_pixel_blending    = 0;					  //!<  TFLG
}


void LWTexture::applyTexture(){
	//  We need to get the texture name; only still images are supported
	LWLayer *layer = dynamic_cast<LWLayer*>( surface->getLayer() );
	if( layer == NULL ){
		emsg( M_LWO, "Layer for texture not found" );
		return;
	}

	Model *model = surface->getModel();
	if( model == NULL ){
		emsg( M_LWO, "Model for texture not found" );
	}

	std::string texture_file_name = texture_image_map;
	std::string final_file_name   = fix_file_name( "Data/textures/", texture_file_name.c_str() );
	int         final_length      = final_file_name.length();
	Texture *t;
	t = new ImageFileTexture( final_file_name );
	if( t->isBad() ){
		delete t;
		std::string final_file_name   = fix_file_name( "Data/pix/", texture_file_name.c_str() );
		int         final_length      = final_file_name.length();
		final_file_name[ final_length-3 ] = 'p';
		final_file_name[ final_length-2 ] = 'i';
		final_file_name[ final_length-1 ] = 'x';
		dmsg( M_LWO, "Look for texture file '%s'", final_file_name.c_str() );
		t = new PixFileTexture( final_file_name );
	}
	if( t->isBad() ){
		emsg( M_LWO, "Texture not found '%s'",  final_file_name.c_str() );
		return;
	}

	if( texture_pixel_blending != 0 ){
		t->setMagFilter( Texture::FILTER_LINEAR );
	}else{
		t->setMagFilter( Texture::FILTER_NEAREST );
	}
	if( texture_antialiasing_type != 0 ){
		t->setMinFilter( Texture::FILTER_LINEAR );
	}else{
		t->setMinFilter( Texture::FILTER_LINEAR_MIPMAP_LINEAR );
	}

	surface->setTexture( t, true );

	//  Choose projection mode
	switch( texture_projection_mode ){
	case LW_PROJECTION_PLANAR:
		model->getGeometry()->makePlanarTextureCoordinates(
			texture_center,
			texture_size,
			texture_major_axis
		);
		dmsg( M_TMAP, "Planar Image Map done" );
		break;

	case LW_PROJECTION_CYLINDRICAL:
		model->getGeometry()->makeCylindricalTextureCoordinates(
			texture_center,
			texture_size,
			texture_major_axis
		);
		dmsg( M_TMAP, "Cylindrical Image Map done" );
		break;

	case LW_PROJECTION_SPHERICAL:
		model->getGeometry()->makeSphericalTextureCoordinates(
			texture_center,
			texture_size,
			texture_major_axis
		);
		dmsg( M_TMAP, "Spherical Image Map done" );
		break;

	case LW_PROJECTION_CUBIC:
		model->getGeometry()->makeCubicTextureCoordinates(
			texture_center,
			texture_size
		);
		dmsg( M_TMAP, "Cubic Image Map done" );
		break;

	case LW_PROJECTION_FRONT:
		dmsg( M_TMAP, "Front projection not yet implemented" );
		break;

	case LW_PROJECTION_UV:
		dmsg( M_TMAP, "UV projection not yet implemented" );
		break;

	default:
		dmsg( M_TMAP, "Unknown projection mode" );
		break;
	}

}


/*
void LWTexture::processTexture(){
	ID4 chunk_type   = f->read_ID4();
	U2  chunk_length = f->read_U2();

	f->pushDomain( chunk_length );

	switch( chunk_type ){
		case ID_TFLG: readTextureFlags_U2          (); break;
		case ID_TSIZ: readTextureSize_VEC12        (); break;
		case ID_TCTR: readTextureCenter_VEC12      (); break;
		case ID_TFAL: readTextureFallOff_VEC12     (); break;
		case ID_TVEL: readTextureVelocity_VEC12    (); break;
		case ID_TREF: readTextureReferenceObject_S0(); break;
		case ID_TCLR: readTextureColor_COL4        (); break;
		case ID_TVAL: readTextureValue_IP2         (); break;
		case ID_TAMP: readBumpTextureAmplitude_FP4 (); break;
		case ID_TFP : readTextureAlgorithm_F4      (); break;  // ns not yet handled
		case ID_TIP : readTextureAlgorithm_I2      (); break;
		case ID_TSP : readTextureAlgorithm_F4      (); break;  // obsolete
		case ID_TFRQ: readTextureAlgorithm_I2      (); break;  // obsolete
		case ID_TIMG: readImageMap_FNAM0           (); break;
		case ID_TALP: readImageAlpha_FNAM0         (); break;
		case ID_TWRP: readImageWarpOptions_U2_U2   (); break;
		case ID_TAAS: readAntialiasingStrength_FP4 (); break;
		case ID_TOPC: readTextureOpacity_FP4       (); break;
		default: break;
	}

	f->popDomain( true );

} */

void LWTexture::readTextureFlags_U2(){
	int count = 0;
	U2  flags = f->read_U2();	

	dmsg( M_TMAP, "TMap flags 0x%x", flags );

	if( (flags & LW_TF_AXIS_X) == LW_TF_AXIS_X ){
		texture_major_axis = TEXTURE_AXIS_X;
		dmsg( M_TMAP, "TMap axis x" );
	}

	if( (flags & LW_TF_AXIS_Y) == LW_TF_AXIS_Y ){
		texture_major_axis = TEXTURE_AXIS_Y;
		dmsg( M_TMAP, "TMap axis y" );
	}
	if( (flags & LW_TF_AXIS_Z) == LW_TF_AXIS_Z ){
		texture_major_axis = TEXTURE_AXIS_Z;
		dmsg( M_TMAP, "TMap axis z" );
	}

	//if( flags & LW_TF_WORLD_COORDINATES ){}
	//if( flags & LW_TF_NEGATIVE_IMAGE ){}
	if( flags & LW_TF_PIXEL_BLENDING ){
		texture_antialiasing_type = 1;
	}
	if( flags & LW_TF_ANTIALISING ){
		texture_pixel_blending = 1;
	}
}

void LWTexture::readTextureSize_VEC12(){
	texture_size = f->read_VEC12();
}

void LWTexture::readTextureCenter_VEC12(){
	texture_center = f->read_VEC12();
}

void LWTexture::readTextureFallOff_VEC12(){
}

void LWTexture::readTextureVelocity_VEC12(){
}

void LWTexture::readTextureReferenceObject_S0(){
}

void LWTexture::readTextureColor_COL4(){
}

void LWTexture::readTextureValue_IP2(){
}

void LWTexture::readBumpTextureAmplitude_FP4(){
}

void LWTexture::readTextureAlgorithm_F4(){
}

void LWTexture::readTextureAlgorithm_I2(){
}

void LWTexture::readImageMap_FNAM0(){
	texture_image_map = f->read_FNAM0();
}

void LWTexture::readImageAlpha_FNAM0(){
	//char *image_alpha = f->read_FNAM0();
}

void LWTexture::readImageWarpOptions_U2_U2(){
}

void LWTexture::readAntialiasingStrength_FP4(){
}

void LWTexture::readTextureOpacity_FP4(){
}


};  //  namespace Imports
};  //  namespace Teddy


#endif  //  TEDDY_INCLUDE_LW_SCENE
