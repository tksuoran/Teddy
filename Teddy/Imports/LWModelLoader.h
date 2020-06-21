
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


#ifndef TEDDY__IMPORTS__LW_MODEL_LOADER__H
#define TEDDY__IMPORTS__LW_MODEL_LOADER__H


#include "Teddy/TeddyConfig.h"
#if defined( TEDDY_INCLUDE_LW_SCENE )


#include "Teddy/Imports/LWModel.h"
#include "Teddy/SysSupport/Types.h"
#include "Teddy/SysSupport/StdMap.h"
#include "Teddy/SysSupport/StdString.h"
using namespace Teddy::Models;


namespace Teddy   {
namespace Imports {


//typedef std::map<std::string, Teddy::MixIn::CountedPointer<Model> > string_to_model;
typedef std::map<std::string, Model*       > string_to_model;
typedef std::map<Model*,      unsigned long> model_to_long;


class LWModelLoader {
public:
	static Model *loadModel( const std::string &name );

protected:
	static string_to_model  loaded_models;
	static model_to_long    model_counters;
};


};  //  namespace Imports
};  //  namespace Teddy


#endif  //  TEDDY_INCLUDE_LW_SCENE
#endif  //  TEDDY__IMPORTS__LW_MODEL_LOADER__H

