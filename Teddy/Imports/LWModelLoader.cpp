
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


#include "Teddy/Imports/LWModelLoader.h"
#include "Teddy/SysSupport/StdAlgo.h"
#include "Teddy/SysSupport/Messages.h"
using namespace Teddy::Materials;
using namespace Teddy::SysSupport;



#define USE_LIGHTWAVE_SCALE   1
#define SCALE                 1


namespace Teddy   {
namespace Imports {


/*static*/ string_to_model  LWModelLoader::loaded_models;
/*static*/ model_to_long    LWModelLoader::model_counters;


/*static*/ Model *LWModelLoader::loadModel( const std::string &name ){
	string_to_model::iterator  m_it  = loaded_models.find( name );
	Model                     *model = NULL;
	if( m_it != loaded_models.end() ){
		dmsg( M_LWS, "Using already loaded model for %s", name.c_str() );
		model = (*m_it).second;
	}else{
		dmsg( M_LWS, "Loading model %s for first time", name.c_str() );
		model = new LWModel( name, 0 );
		loaded_models.insert( std::make_pair(name,model) );
	}

	model_to_long::iterator l_it = model_counters.find( model );
	if( l_it == model_counters.end() ){
		//  add to map
		model_counters.insert( std::make_pair(model,1) );
	}else{
		// increase count
		(*l_it).second++;
		dmsg( M_LWS, "Reuse count %ul", (*l_it).second );
	}

	std::ostringstream model_name_stream;
	model_name_stream << name; //  FIX add number
	std::string model_name = model_name_stream.str();
	return new Model( model_name, model );
}


};  //  namespace Imports
};  //  namespace Teddy


#endif  //  TEDDY_INCLUDE_LW_SCENE

