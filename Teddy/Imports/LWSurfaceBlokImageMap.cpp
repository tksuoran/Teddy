
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

	$Id: LWSurfaceBlokImageMap.cpp,v 1.6 2002/02/16 16:38:11 tksuoran Exp $
*/


#include "Teddy/TeddyConfig.h"
#if defined( TEDDY_INCLUDE_LW_SCENE )


#if defined(_MSC_VER)
#	pragma warning(disable:4786)
#endif


#include "Teddy/Imports/LWClip.h"
#include "Teddy/Imports/LWFile.h"
#include "Teddy/Imports/LWLayer.h"
#include "Teddy/Imports/LWModel.h"
#include "Teddy/Imports/LWSurface.h"
#include "Teddy/Imports/LWSurfaceBlok.h"
#include "Teddy/Models/Geometry.h"
#include "Teddy/Graphics/Texture.h"
#include "Teddy/Graphics/ImageFileTextureLoader.h"
#include "Teddy/SysSupport/Messages.h"
#include "Teddy/SysSupport/FileScan.h"
#include "Teddy/SysSupport/StdMaths.h"
#include "Teddy/SysSupport/StdIO.h"
using namespace Teddy::Graphics;
using namespace Teddy::SysSupport;


namespace Teddy   {
namespace Imports {


void LWSurfaceBlok::applyImageMap(){
	//  Disabled image maps are easy to handle
	if( enable == 0 ){
		return;
	}

	//  At the moment only color textures are supported
	if( texture_channel != ID_COLR ){
		dmsg( M_LWO,
			"Texture channel %s not supported; only COLR channel is supported.",
			did( texture_channel )
		);
	}

	//  We need to get the texture name; only still images are supported
	LWLayer *layer = dynamic_cast<LWLayer*>( surface->getLayer() );
	if( layer == NULL ){
		emsg( M_LWO, "Layer not found" );
		return;
	}

	Model *model = surface->getModel();
	if( model == NULL ){
		emsg( M_LWO, "Model not found" );
	}

	LWClip *clip = layer->getClip( texture_image_map );
	if( clip == NULL ){
		emsg( M_LWO,
			"Texture image map %d not found",
			texture_image_map
		);
		return;
	}

	std::string texture_file_name = clip->still_image;
	std::string final_file_name   = fix_file_name( "Data/textures/", texture_file_name.c_str() );
	dmsg( M_LWO, "Look for texture file '%s'", final_file_name.c_str() );
	//Texture *t = new ImageFileTexture( final_file_name );
	Texture *t = ImageFileTextureLoader::loadTexture( final_file_name );

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

	t->doBind();
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


};  //  namespace Imports
};  //  namespace Teddy


#endif  //  TEDDY_INCLUDE_LW_SCENE

