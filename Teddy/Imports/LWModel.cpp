
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

	$Id:  $
*/


#include "Teddy/TeddyConfig.h"
#if defined( TEDDY_INCLUDE_LW_SCENE )


#include "Teddy/Imports/LWFile.h"
#include "Teddy/Imports/LWModel.h"
#include "Teddy/Imports/LWLayer.h"
#include "Teddy/Materials/Material.h"
#include "Teddy/Models/Model.h"
#include "Teddy/Models/Face.h"
#include "Teddy/Models/Vertex.h"
#include "Teddy/SysSupport/Exception.h"
#include "Teddy/SysSupport/FileScan.h"
#include "Teddy/SysSupport/Messages.h"
#include "Teddy/SysSupport/StdMaths.h"
#include "Teddy/SysSupport/StdIO.h"
#include "Teddy/SysSupport/StdAlgo.h"
using namespace Teddy::Materials;
using namespace Teddy::SysSupport;



#define USE_LIGHTWAVE_SCALE   1
#define SCALE                 1


namespace Teddy   {
namespace Imports {


//!  Constructor for submodels, simply calls Model constructor
LWModel::LWModel( const std::string &name ):Model(name){
	dmsg( M_LWO, "LWModel constructor" );
}


//!  Constructor which loads LightWave object file
LWModel::LWModel( const std::string &fname, Uint32 options )
:
Model(fix_file_name("Data/lwo/",fname.c_str() ))
{
	f        = NULL;
	num_tags = 0;
	setMaterial( &Material::BLACK );

	std::string final_file_name = fix_file_name( "Data/lwo/", fname.c_str() );
	FILE *f_test = fopen( final_file_name.c_str(), "r" );
	if( f_test == NULL ){
		emsg( M_LWO, "Could not open file %s", final_file_name.c_str() );
		return;
	}else{
		fclose( f_test );
	}
	
	try{
		f = new LWFile( final_file_name, options );

		f->pushDomain( 8 );              // Master domain only allows reading of first 8 bytes of FORM and length
		ID4 form     = f->read_ID4();    // FORM
		f->setLen    ( f->read_U4 () );
		f->pushDomain( f->getLen  () );  // file length-8; File data domain allows reading of rest of the file
		f->setType   ( f->read_ID4() );  // LWOB, LWLO, LWO2
		
		dmsg( M_LWO,
			"%s lwo file %s length %lu ",
			did( f->getType() ),
			final_file_name.c_str(),
			f->getLen()
		);
		
		LWLayer *new_layer = new LWLayer( this, fname, 0, Vector(0,0,0), -1 );
		layers.insert( std::make_pair(0,new_layer) );
		add( new_layer );  //  add to submeshes
		new_layer->processLayer();
/*		float lr = new_layer->getClipRadius();
		if( lr > this->getClipRadius() ){
			this->setClipRadius( lr );
		}*/

	}catch( .../*Exception &e*/ ){
		dmsg( M_LWO, "Exception" );
	}

	if( f != NULL ){
		f->close();
	}

	setupClipRadius();
}


//!  Destructor
/*virtual*/ LWModel::~LWModel(){
	// FIX
}



LWFile *LWModel::getFile() const {
	return f;
}

LWLayer *LWModel::getLayer( int layer_number ){
	U4_to_LWLayer::iterator  l_it  = layers.find( layer_number );
	LWLayer                 *layer = NULL;

	if( l_it != layers.end() ){
		layer = (*l_it).second;
		if( layer == NULL ){
			emsg( M_LWO, "Layer found as NULL" );
		}
	}else{
		emsg( M_LWO, "Layer not found" );
	}
	return layer;
}


/*!  LWLO LAYR Chunk

	An LAYR chunk must precede each set of PNTS, POLS and CRVS data
	chunks and indicates to which layer those data belong.	An LAYR
	chunk consists of two unsigned short values and a string.  The first
	is the layer number which should be from 1 to 10 to operate
	correctly in Modeler.  This restriction may be lifted in future
	versions of the format.  The second value is a bitfield where only
	the lowest order bit is defined and all others should be zero.	This
	bit is one if this is an active layer and zero if it is a background
	layer.	The string which follows is the name of the layer and should
	be null-terminated and padded to even length.
*/
void LWModel::layer_U2_U2_S0(){
	U2	         layer_number = f->read_U2();
	U2	         layer_flags  = f->read_U2();
	std::string  layer_name   = f->read_S0();
	
	dmsg( M_LWO, "LAYER %s number %u", layer_name.c_str(), layer_number );

	LWLayer *new_layer = new LWLayer(
		this,
		layer_name,
		layer_flags,
		Vector(0,0,0),
		-1
	);
	layers.insert( make_pair(layer_number,new_layer) );
	add( new_layer );  //  add to submeshes
	f->popDomain( true );
	new_layer->processLayer();
	float lr = new_layer->getClipRadius();
	if( lr > getClipRadius() ){
		setClipRadius( lr );
	}
}


/*!
	LWO2 Start Layer 

	LAYR { number[U2], flags[U2], pivot[VEC12], name[S0], parent[U2] } 

	Signals the start of a new layer. All the data chunks
	which follow will be included in this layer until
	another layer chunk is encountered. If data is encountered
	before a layer chunk, it goes into an arbitrary layer.
	If the least significant bit of flags is set, the layer
	is hidden. The parent index indicates the default parent
	for this layer and can be -1 or missing to indicate no
	parent. 
*/
void LWModel::layer_U2_U2_VEC12_S0_U2(){
	U2           layer_number = f->read_U2();
	U2           layer_flags  = f->read_U2();
	Vector       layer_pivot  = f->read_VEC12();
	std::string  layer_name   = f->read_S0();
	U2           layer_parent = 1;

	if( f->domainLeft() >= 2 ){
		int lp = f->read_I2();
		if( lp>1 ){
			layer_parent = lp;
		}
	}

	dmsg( M_LWO, "LAYER %s number %u parent %u",
		layer_name.c_str(),
		layer_number,
		layer_parent
	);

	LWLayer *new_layer = new LWLayer( this, layer_name, layer_flags, layer_pivot, layer_parent );
	layers.insert( std::make_pair(layer_number,new_layer) );
	add( new_layer );  //  add to submeshes

	f->popDomain( true );

	new_layer->processLayer();
	float lr = new_layer->getClipRadius();
	if( lr > this->getClipRadius() ){
		this->setClipRadius( lr );
	}
}


/*!
	LWO2 Tag Strings 

	TAGS { tag-string[S0] * }
	 
	This chunk lists the tags strings that can be associated with polygons by the PTAG chunk.
	Strings should be read until as many bytes as the chunk size specifies have been read, and
	each string is assigned an index starting from zero. 
*/
void LWModel::tags_d(){
	while( f->domainLeft() > 0 ){	
		std::string tag = f->read_S0();
		tags.insert( std::make_pair(num_tags,tag) );
		num_tags++;
	}
	dmsg( M_LWO, "Tags found: %lu", num_tags );
}


std::string LWModel::getTag( VX tag_index ){
	U4_to_string::iterator  t_it      = tags.find( tag_index );
	std::string             tag_value;

	if( t_it != tags.end() ){
		tag_value  = (*t_it).second;
	}else{
		emsg( M_LWO, "Tag not found" );
	}

	return tag_value;
}


};  //  namespace Imports
};  //  namespace Teddy


#endif  //  TEDDY_INCLUDE_LW_SCENE

