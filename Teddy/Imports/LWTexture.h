
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

	$Id: LWTexture.h,v 1.4 2002/01/11 14:34:59 tksuoran Exp $
*/


#ifndef TEDDY__IMPORTS__LW_TEXTURE__H
#define TEDDY__IMPORTS__LW_TEXTURE__H


#include "Teddy/TeddyConfig.h"
#if defined( TEDDY_INCLUDE_LW_SCENE )


#include "Teddy/Imports/lwdef.h"
#include "Teddy/Graphics/Texture.h"
using namespace Teddy::Graphics;


namespace Teddy   {
namespace Imports {


class LWFile;
class LWSurface;


#define LW_TF_AXIS_X            (1<<0)
#define LW_TF_AXIS_Y            (1<<1)
#define LW_TF_AXIS_Z            (1<<2)
#define LW_TF_WORLD_COORDINATES (1<<3)
#define LW_TF_NEGATIVE_IMAGE    (1<<4)
#define LW_TF_PIXEL_BLENDING    (1<<5)
#define LW_TF_ANTIALISING       (1<<6)

#define LW_IMAGE_WRAP_BLACK         0
#define LW_IMAGE_WRAP_CLAMP         1
#define LW_IMAGE_WRAP_REPEAT        2  //  default
#define LW_IMAGE_WPAP_MIRROR_REPEAT 3
#define LW_IMAGE_WRAP_DEFAULT       LW_IMAGE_WRAP_REPEAT


/*!
	\brief   LWTexture
	\warning LWTextureLoader would be better name
	\todo    docs
*/
class LWTexture {
public:
	LWTexture( LWSurface *surface, int map_type );

	void processTexture();	//  Read in
	void applyTexture  ();  //  Apply to surface

public:
	void readTextureFlags_U2          ();  //  TFLG
	void readTextureSize_VEC12        ();  //  TSIZ
	void readTextureCenter_VEC12      ();  //  TCTR
	void readTextureFallOff_VEC12     ();  //  TFAL
	void readTextureVelocity_VEC12    ();  //  TVEL

	void readTextureReferenceObject_S0();  //  TREF
	void readTextureColor_COL4        ();  //  TCLR
	void readTextureValue_IP2         ();  //  TVAL
	void readBumpTextureAmplitude_FP4 ();  //  TAMP
	void readTextureAlgorithm_F4      ();  //  TFPn
	void readTextureAlgorithm_I2      ();  //  TIPb

	void readImageMap_FNAM0           ();  //  TIMG
	void readImageAlpha_FNAM0         ();  //  TALP
	void readImageWarpOptions_U2_U2   ();  //  TWRP
	void readAntialiasingStrength_FP4 ();  //  TAAS
	void readTextureOpacity_FP4       ();  //  TOPC

protected:
	LWFile    *f;                          //!<
	LWSurface *surface;                    //!<
	VEC12      texture_center;             //!<  TCTR
	VEC12      texture_size;               //!<  TSIZ
	U2         texture_projection_mode;    //!<  CTEX
	U2         texture_major_axis;         //!<  TFLG
	FNAM0      texture_image_map;          //!<  TIMG
	U2         texture_antialiasing_type;  //!<  TFLG
	U2         texture_pixel_blending;     //!<  TFLG
};


};  //  namespace Imports
};  //  namespace Teddy


#endif  //  TEDDY_INCLUDE_LW_SCENE
#endif  //  TEDDY__IMPORTS__LW_TEXTURE__H

