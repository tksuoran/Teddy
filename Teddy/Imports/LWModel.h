
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


#ifndef TEDDY__IMPORTS__LW_MODEL__H
#define TEDDY__IMPORTS__LW_MODEL__H


#include "Teddy/TeddyConfig.h"
#if defined( TEDDY_INCLUDE_LW_SCENE )


#include "Teddy/Maths/Vector.h"
#include "Teddy/Models/Model.h"
#include "Teddy/Imports/lwdef.h"
#include "Teddy/SysSupport/Types.h"
#include "Teddy/SysSupport/StdMap.h"
#include <cstring>
using namespace Teddy::Models;


namespace Teddy   {
namespace Imports {


class LWFile;
class LWLayer;


typedef std::map<U4, LWLayer   *> U4_to_LWLayer;
typedef std::map<U4, std::string> U4_to_string;


/*!
	\brief   LightWave object file loader
	\warning Many features are not yet implemented
	\todo    Detail polygons
	\todo    Points
	\todo    Lines
	\todo    Polygon tessalation
	\todo    Layers
	\todo    Texture and Image maps
	\bug     Destructors missing

	This class implements loader for LightWave object files.
	It is a subclass of Meodel that contains no Elements,
	only submodels. Each Layer that is encountered in the file
	is placed into a submesh. If the file has data for arbitrary
	layer, eg., there is data before layer, a default layer 1
	is created and data is placed there.

	Data in layers is organized by surfaces. For each surface
	found in the file a submesh for the layer is created and
	LWSurface is created. Thus each layer mesh contains no
	Elements, just submeshes.

	The LightWave object file format spesification is available
	from NewTek internet pages. Parts LightWave object file format
	specifications are placed into comments into source-code. 
*/
class LWModel : public Model {
public:
	LWModel( const std::string &fname, Uint32 options );
	virtual ~LWModel();

	LWFile      *getFile                () const;
	LWLayer     *getLayer               ( int layer_number );
	std::string  getTag                 ( VX  tag_index    );
	void         layer_U2_U2_S0         ();  //  LWLO::LAYR
	void         layer_U2_U2_VEC12_S0_U2();  //  LWO2::LAYR
	void         tags_d                 ();  //  TAGS

protected:
	LWModel( const std::string &name );

protected:
	LWFile        *f;
	U4_to_LWLayer  layers;    //!<  Layers of Lightwave Object
	U4_to_string   tags;
	U4             num_tags;
};


};  //  namespace Imports
};  //  namespace Teddy


#endif  //  TEDDY_INCLUDE_LW_SCENE
#endif  //  TEDDY__IMPORTS__LW_MODEL__H

