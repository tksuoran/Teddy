
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


#ifndef TEDDY__IMPORTS__LW_LAYER__H
#define TEDDY__IMPORTS__LW_LAYER__H


#include "Teddy/TeddyConfig.h"
#if defined( TEDDY_INCLUDE_LW_SCENE )


#include "Teddy/Maths/Vector.h"
#include "Teddy/Models/Model.h"
#include "Teddy/Imports/lwdef.h"
#include "Teddy/SysSupport/StdMap.h"
#include "Teddy/SysSupport/Types.h"
#include <cstring>


//  Forward declarations
namespace Teddy {
	namespace Models { class Face;   };
	namespace Models { class Vertex; };
};
using namespace Teddy::Models;
using namespace Teddy::SysSupport;


namespace Teddy   {
namespace Imports {


class LWClip;
class LWEnvelope;
class LWFile;
class LWModel;
class LWSurface;


typedef std::map<std::string, Model     *> string_to_Model;
typedef std::map<std::string, LWSurface *> string_to_LWSurface;
typedef std::map<U4,          Vertex    *> U4_to_Vertex;
typedef std::map<U4,          Face      *> U4_to_Face;
typedef std::map<U4,          LWEnvelope*> U4_to_LWEnvelope;
typedef std::map<U4,          LWClip    *> U4_to_LWClip;


/*!
	\brief LWLayer
	\todo  docs
*/
class LWLayer : public Model {
public:
	LWLayer( LWModel *model, const std::string &name, U2 flags, Vector pivot, int parent );
	virtual ~LWLayer();

	LWClip  *getClip     ( VX clip_index );
	LWModel *getModel    ();
	void     processLayer();  //!<  Returns true if next layer

protected:
	bool processChunk    ();  //!<  returns true if next layer is needed

	//  LWOB & LWLO
	void pointList                 ();  //  LWOB::PNTS & LWO2::PNTS
	void polygonList               ();  //  LWO2::POLS
	void faceList                  ();  //  LWOB::POLS
	void surfaceList               ();  //  SRFS
	void curveList                 ();  //  CRVS
	void patchList                 ();  //  PCHS
	void surface_sc                ();  //  SURF

	//  LWO2
	void vertexMapping_ID4_U2_S0_d ();  //  VMAP
	void polygonTags_ID4_d         ();  //  PTAG
	void envelope_U4_sc            ();  //  ENVL
	void clip_U4_sc                ();  //  CLIP
	void surf_S0_S0_sc             ();  //  SURF
	void boundingBox_VEC12_VEC12   ();  //  BBOX
	void descriptionLine_S0        ();  //  DESC
	void comments_S0               ();  //  TEXT
	void thumbnail_U2_U2_d         ();  //  ICON

protected:
	int      parent_layer;  //!<  Parent layer number
	Vector   pivot;         //!<  Pivot point of layer
	U2       flags;         //!<  Layer flags
	LWFile  *f;
	LWModel *model;         //!<  Model which contains this Layer

	std::string          description_line;
	std::string          commentary_text;	
	string_to_Model      models;
	string_to_LWSurface  surfaces;
	U4_to_Vertex         vertices;  //!<  These are shared among surfaces
	U4_to_Face           faces;
	U4_to_LWEnvelope     envelopes;
	U4_to_LWClip         clips;
	U4                   num_vertices;
	U4                   num_faces;
	U4                   num_surfaces;
	U4                   num_envelopes;
	U4                   num_clips;
	U4                   current_surface;
	Vector               bbox_min;
	Vector               bbox_max;
};


};  //  namespace Imports
};  //  namespace Teddy


#endif  //  TEDDY_INCLUDE_LW_SCENE
#endif  //  TEDDY__IMPORTS__LW_LAYER__H

