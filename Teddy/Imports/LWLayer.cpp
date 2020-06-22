
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


#include "Teddy/Imports/LWClip.h"
#include "Teddy/Imports/LWEnvelope.h"
#include "Teddy/Imports/LWFile.h"
#include "Teddy/Imports/LWLayer.h"
#include "Teddy/Imports/LWModel.h"
#include "Teddy/Imports/LWSurface.h"
#include "Teddy/Models/Model.h"
#include "Teddy/Models/Face.h"
#include "Teddy/Models/Geometry.h"
#include "Teddy/Models/Vertex.h"
#include "Teddy/SysSupport/Exception.h"
#include "Teddy/SysSupport/Messages.h"
#include "Teddy/SysSupport/StdMaths.h"
#include "Teddy/SysSupport/StdIO.h"
#include "Teddy/SysSupport/StdAlgo.h"
using namespace Teddy::SysSupport;


#define USE_LIGHTWAVE_SCALE   1
#define SCALE                 1


namespace Teddy   {
namespace Imports {


//!  Constructor for submeshes
LWLayer::LWLayer( LWModel *model, const std::string &name, U2 flags, Vector pivot, int parent )
:
	Model( name )
{
	this->f            = model->getFile();
	this->model        = model;
	this->pivot        = pivot;
	this->flags        = flags;
	this->parent_layer = parent;
	num_vertices       = 0;
	num_faces          = 0;
	num_surfaces       = 0;
	num_envelopes      = 0;
	num_clips          = 0;
	current_surface    = 0;
	bbox_min           = Vector(0,0,0);
	bbox_max           = Vector(0,0,0); 

	dmsg( M_LWO, "LWLayer constructor" );
}

void LWLayer::processLayer(){
	//  Read max file len
	while( f->bytesRead()-8 < f->getLen() ){
        dmsg( M_LWO, "calling processChunk()" );
		bool next_layer = processChunk();
		if( next_layer == true ){
			break;
		}
		
	}

	//  Post processing - smooth vertices

	list<Model*>::iterator m_it;
	m_it = children.begin();
	while( m_it != children.end() ){
		Model    *model = *m_it;
		Material *mat   = model->getMaterial();
		dmsg( M_LWO, "Surface with max smoothing angle % 6.2f", degs(mat->getMaxSmoothingAngle()) );
		model->getGeometry()->smooth(  mat->getMaxSmoothingAngle()  );
		m_it++;
	}
	
}


//!  Destructor
/*virtual*/ LWLayer::~LWLayer(){
	//	FIX
}


//!  Process a LWOB & LWO2 file chunks
bool LWLayer::processChunk(){
    dmsg( M_LWO, "processChunk() @ %lu", f->bytesRead() );
	bool next_layer = false;
	U4   chunk_id     = f->read_ID4();
	U4   chunk_length = f->read_U4();

	dmsg( M_LWO,
		"%s::%s (%lu) (%lu bytes)",
		did( f->getType() ),
		did( chunk_id ),
        chunk_id,
		chunk_length
	);

	f->pushDomain( chunk_length );

	switch( f->getType() ){
	case ID_LWOB:
	case ID_LWLO:
		switch( chunk_id ){
		case ID_PNTS: pointList  (); break;
		case ID_SRFS: surfaceList(); break;
		case ID_POLS: faceList   (); break;
		case ID_CRVS: curveList  (); break;
		case ID_PCHS: patchList  (); break;
		case ID_SURF: surface_sc (); break;
		default: break;
		}
		break;
	case ID_LWO2:
		switch( chunk_id ){
		case ID_PNTS: pointList                (); break;
		case ID_VMAP: vertexMapping_ID4_U2_S0_d(); break;
		case ID_POLS: polygonList              (); break;
		case ID_TAGS: model->tags_d            (); break;
		case ID_PTAG: polygonTags_ID4_d        (); break;
		case ID_ENVL: envelope_U4_sc           (); break;
		case ID_CLIP: clip_U4_sc               (); break;
		case ID_SURF: surf_S0_S0_sc            (); break;
		case ID_BBOX: boundingBox_VEC12_VEC12  (); break;
		case ID_DESC: descriptionLine_S0       (); break;
		case ID_TEXT: comments_S0              (); break;
		case ID_ICON: thumbnail_U2_U2_d        (); break;
		default: break;
		}
		break;
	default: break;
	}

	if( chunk_id == ID_LAYR ){
		next_layer = true;
		switch( f->getType() ){
		case ID_LWLO: model->layer_U2_U2_S0         (); break;  //  Actually LWLO only
		case ID_LWO2: model->layer_U2_U2_VEC12_S0_U2(); break;
		default: break;
		}
	}else{

	f->popDomain( true );

	}

	return next_layer;

}


LWModel *LWLayer::getModel(){
	return model;
}


LWClip *LWLayer::getClip( VX clip_index ){
	U4_to_LWClip::iterator  c_it = clips.find( clip_index );
	LWClip                 *clip = NULL;

	if( c_it != clips.end() ){
		clip = (*c_it).second;
	}
	return clip;
}


/*!
	\todo Make use of real pivot point

	LWOB and LOW2  PNTS { point-location[VEC12] * } 
	
	This chunk contains a list of the X, Y, and Z coordinates of all the points 
	in an object. Since each coordinate has three components, and each component 
	is stored as a four byte floating point number, the number of points in an 
	object can be determined by dividing the size in bytes of the PNTS chunk by 
	12. 
	
	By convention, the +X direction is to the right or east, the +Y direction is 
	upward, and the +Z direction is forward or north. For models of real-world 
	objects, the unit size is usually considered to be one meter. The 
	coordinates are specified relative to an object's pivot point. See the 
	LightWave Modeler manual for more information about LightWave 3D's geometric 
	conventions. 
	
	Points in the PNTS chunk are numbered in the order they occur, starting with 
	zero. This index is then used by polygons to define their vertices. The PNTS 
	chunk must be before the POLS, CRVS, and PCHS chunks in the file. 
*/
void LWLayer::pointList(){
	Vertex *vertex;
	U4      current_v_index = 0;
	U4      i;

	num_vertices = f->domainLeft()/12;

	for( i=0; i<num_vertices; i++ ){
		if( f->domainLeft()<3*4 ){
			emsg( M_LWO, "Not enough floats found in chunk for point" );
			break;
		}

		Vector vec = f->read_VEC12();
		vec += pivot;      //  FIX
		vec[2] = -vec[2];  //  FIX check this and matrix mirroring

		vertex = new Vertex( vec );

#		ifdef USE_LIGHTWAVE_SCALE
		*vertex *= SCALE; 
#		endif

		//vertex->setNormal( Vector(0,0,0) );
		this->vertices.insert( std::make_pair(current_v_index,vertex) );
		current_v_index++;
	}
    dmsg( M_LWO, "pointList() done through %d vertices", i-1 );
}


/*
	LWOB SRFS { surf-name[S0] * } 
	
	This chunk contains a list of the names of all the surfaces in an object. 
	Each surface name appears as a null-terminated character string. If the 
	length of the string (including the null) is odd, an extra null byte is 
	added. Surface names should be read from the file until as many bytes as the 
	chunk size specifies have been read. 
	
	In LightWave 3D terminology, a "surface" is defined as a named set of 
	shading attributes. Each polygon contains a reference to the surface used to 
	color the polygon. The names as listed in the SRFS chunk are numbered in the 
	order they occur, starting from 1, and this index is used by polygons to 
	define their surface. The SRFS chunk must be before the POLS, CRVS, and PCHS 
	chunks in the file.
*/
void LWLayer::surfaceList(){
	std::string  surface_name;
	LWSurface   *surface;
	Model       *model;
	char        *buffer;

	while( f->domainLeft() > 0 ){
		num_surfaces++;
		surface_name = f->read_S0();
		model        = new Model    ( surface_name );
		surface      = new LWSurface( this, model, surface_name );
		add( model );
		buffer = new char[16];
		sprintf( buffer, "SURFACE %d", (int)(num_surfaces) );
		surfaces.insert( std::make_pair(surface_name,surface) );
		models  .insert( std::make_pair(buffer,      model  ) );
		model->setMaterial( surface );  // ? FIX 
	}
}


/*!
	\todo Support for points and lines

	LWOB POLS { ( numvert[U2], vert[U2] # numvert, surf[I2] )* } 
	
	This chunk contains a list of all the polygons in an object. Each entry 
	consists of a short integer specifying the number of vertices in the polygon 
	followed by that many short integers specifying the vertices themselves (as 
	indices into the points list) followed by a short integer specifying which 
	surface is used by the polygon (as an index into the surfaces list). The 
	number of vertices in a polygon currently may vary from one to 200. The 
	vertex list for each polygon should begin at a convex vertex and proceed 
	clockwise as seen from the visible side of the polygon (LightWave 3D 
	polygons are single-sided, except for those whose surfaces have the 
	double-sided flag set). Polygons should be read from the file until as many 
	bytes as the chunk size specifies have been read. 
	
	Since the points in the PNTS chunk are referenced using two-byte integers, 
	the effective maximum number of points in a LightWave object file is 65,536. 
	This is an inherient limitation of this current format. 
	
	A negative surface number for a polygon indicates that the polygon has 
	detail polygons (which are drawn on top of the main polygon and may be 
	coplanar with it). In this case, the next number in the file is a short 
	integer specifying how many detail polygons belong to the current polygon. 
	This is followed by a list of those detail polygons, where each entry is of 
	the same format as described above for regular polygons (except that the 
	detail polygons cannot have details of their own). The list of regular 
	polygons then resumes. To determine which surface is used by a polygon with 
	a negative surface number, the absolute value of that number should be used. 
	Note, however, that detail polygons are mostly obsolete, so even though they 
	may be recognized by LightWave and old files contain them, they should be 
	ignored.
*/
void LWLayer::faceList(){
	Face   *face   = NULL;
	Vertex *vertex = NULL;
	Model  *model  = NULL;
	U4      num_vertices;
	U4      surface_index;
	U4      vertex_index;
	U4      i;
	bool    good;
	U4      bad_count   = 0;
	U4      point_count = 0;
	U4      line_count  = 0;

	while( f->domainLeft() > 0 ){
		num_vertices = f->read_U2();

		if( num_vertices<3 ){  //  FIX
			bad_count++;
			switch( num_vertices ){
			case 0: bad_count  ++; emsg( M_LWO, "Bad polygon - 0 vertices" ); break;
			case 1: bad_count  ++; point_count++; break;
			case 2: bad_count  ++; line_count ++; break;
			}
			for( i=0; i<num_vertices; i++ ){
				vertex_index = f->read_U2();
			}
			f->read_U2();
			continue;
		}

		face = new Face();
		good = true;

		for( i=0; i<num_vertices; i++ ){
			if( f->domainLeft()<2 ){
				emsg( M_LWO, "Not enough shorts found in chunk" );
				good = false;
				break;
			}
			vertex_index = f->read_U2();

			if( (vertex_index > this->num_vertices) ){
				emsg( M_LWO, "Not understood as vertex index %ld > %ld", vertex_index, num_vertices );
				good = false;
				break;
			}

			//	Find vertex for this index and insert to face
			U4_to_Vertex::iterator v_it = vertices.find( vertex_index );
			if( v_it!=vertices.end() ){
				vertex = (*v_it).second;
				if( vertex != NULL ){
					face->add( vertex );
				}else{
					emsg( M_LWO, "Vertex %ld pointer is NULL", vertex_index );
					good = false;
				}
			}else{
				emsg( M_LWO, "Vertex %ld not found", vertex_index );
				good = false;
			}

		}

		if( good ){
			surface_index = f->read_U2();
			if( surface_index > num_surfaces ){
				bad_count++;
				delete face;
				continue;
				//	FIX error
			}

			string_to_Model::iterator  m_it;
			char                       surface_name[16];

			sprintf( surface_name, "SURFACE %d", (int)(surface_index) );

			m_it = models.find( surface_name );
			if( m_it!=models.end() ){
				model = (*m_it).second;
				if( model==NULL ){
					emsg( M_LWO, "Model-surface %s found as NULL", surface_name );
					bad_count++;
					delete face;
					continue;
				}
				face->makeNormal();
				model->add( face );
				faces.insert( std::make_pair(num_faces,face) );
				num_faces++;
			}else{
				emsg( M_LWO, "Model-surface %s not found", surface_name );
				bad_count++;
				delete face;
				continue;
			}
		}else{
			bad_count++;
			delete face;
		}
	}

	if( bad_count > 0 ){
		dmsg( M_LWO, "%ld good polygons read %ld bad polygons skipped", num_faces, bad_count );
		if( point_count>0 ){
			dmsg( M_LWO, "%ld points, not yet supported", point_count );
		}
		if( line_count>0 ){
			dmsg( M_LWO, "%ld lines, not yet supported", line_count );
		}
	}
}


//!  LWOB Read curve list
void LWLayer::curveList(){
	//  FIX not implemented
}


//!  LWOB Read patch list
void LWLayer::patchList(){
	//  FIX not implemented
}


/*!
	LWOB SURF { name[S0], attributes[SUB-CHUNK] * } 
	
	Each SURF chunk describes the surface attributes of a particular surface. 
	These chunks begin with the name of the surface being described. Following 
	the name is a series of sub-chunks, which are like normal IFF chunks except 
	that their sizes are specified by short integers instead of longs. It is 
	likely that the variety of sub-chunks will grow as new surface attributes 
	are added to the program, but any unknown sub-chunks may be skipped over by 
	using the size. Sub-chunks should be read from the file until as many bytes 
	as the chunk size specifies have been read. 
*/
void LWLayer::surface_sc(){
	string_to_LWSurface::iterator  s_it;
	std::string                    surface_name;
	LWSurface                     *surface; 

	surface_name = f->read_S0();

	s_it = surfaces.find( surface_name );
	if( s_it != surfaces.end() ){
		surface = (*s_it).second;
		if( surface == NULL ){
			emsg( M_LWO, "NULL surface %s in surfacelist", surface_name.c_str() );
			return;
		}
	}else{
		surface = new LWSurface( this, this, surface_name );
	}
	
	while( f->domainLeft() > 0 ){
		surface->processSubChunk();
	}
	surface->endSurface();
}


/*!
	LWO2 Vertex Mapping 

	VMAP { type[ID4], dimension[U2], name[S0], ( vert[VX], value[F4] # dimension )* } 

	This chunk contains a set of floating point vectors associated with a set of vertices.
	Each one has a type which is a four-character ID code, a dimension and a name string.
	After that follows a list of vertex / vector pairs, with the vertex given by a vertex
	index in VX format and an array of "dimension" floating-point values. There can be any
	number of these chunks, although they should all have different types or names. 

	Some possible type codes are TXUV for UV mapping coordinates, MNVW for MetaNURBS
	vertex weights, MORF for vector offsets defining an alternate object shape, SPOT
	for alternate vertex positions, RGBA for coloring, etc. 
*/
void LWLayer::vertexMapping_ID4_U2_S0_d(){
	ID4         vmap_type = f->read_ID4();
	U2          vmap_dim  = f->read_U2();
	std::string vmap_name = f->read_S0();

	dmsg( M_LWO, "%s Vertex map %s", did(vmap_type), vmap_name.c_str() );

	while( f->domainLeft() > 0 ){
		VX vertex_id = f->read_VX();
		for( int i=0; i<vmap_dim; i++ ){
			F4 value = f->read_F4();
		}
		switch( vmap_type ){
		case ID_TXUV:
		case ID_MNUW:
		case ID_MORF:
		case ID_SPOT:
		case ID_RGBA:
		default:
			break;
		}

	}

}


/*!
	LWO2 Polygon List

	POLS { type[ID4], ( numvert+flags[U2], vert[VX] # numvert )* } 

	This chunk contains a list of polygons for the
	current layer. The 'type' code indicates the
	polygon type and can be FACE, CURV, PACH, or
	possibly other values. Each entry starts with
	a short integer specifying the number of vertices
	in the polygon. The 6 high-order bits of the
	number of vertices are flags bits with different
	meaning for each polygon type, so there are a
	maximum of 1023 vertices per polygon. The vertex
	list is the specified number of two or four byte
	VX vertex indices (relative to the most recent
	points list). The vertex list for each polygon
	should begin at a convex vertex and proceed
	clockwise as seen from the visible side of the
	polygon (LightWave 3D polygons are single-sided,
	except for those whose surfaces have the
	double-sided flag set). Polygons should be read
	from the file until as many bytes as the chunk
	size specifies have been read. 
*/
void LWLayer::polygonList(){
	Face   *face;
	Vertex *vertex;
	ID4     polygons_type = f->read_ID4();
	U4      vertex_index;
	int     i;
	bool    good;
	int     bad_count   = 0;
	int     point_count = 0;
	int     line_count  = 0;

	while( f->domainLeft() > 0 ){
		U2 data    = f->read_U2();
		U2 numvert = data & 0x03ff;
		U2 flags   = (data & ~numvert) >> 10;

		if( numvert<3 ){  //  FIX
			bad_count++;
			switch( num_vertices ){
			case 0: bad_count++; emsg( M_LWO, "Bad polygon - 0 vertices" ); break;
			case 1: bad_count++; point_count++; break;
			case 2: bad_count++; line_count++;  break;
			}
			for( i=0; i<numvert; i++ ){
				vertex_index = f->read_VX();
			}
			continue;
		}

		face = new Face();
		good = true;

		for( i=0; i<numvert; i++ ){

			if( f->domainLeft()<2 ){
				emsg( M_LWO, "Not enough bytes left in chunk" );
				good = false;
				break;
			}

			vertex_index = f->read_VX();
			if( vertex_index > this->num_vertices ){
				emsg( M_LWO, "Not understood as vertex index %ld > %ld", vertex_index, num_vertices );
				good = false;
				break;
			}

			U4_to_Vertex::iterator v_it = vertices.find( vertex_index);
			if( v_it!=vertices.end() ){
				vertex = (*v_it).second;
				if( vertex != NULL ){
					face->add( vertex );
				}else{
					emsg( M_LWO, "Vertex %ld pointer is NULL", vertex_index );
					good = false;
				}
			}else{
				emsg( M_LWO, "Vertex %ld not found", vertex_index );
				good = false;
			}
		}
		if( good ){
			face->makeNormal();
			faces.insert( pair<U4,Face*>(num_faces,face) );
			num_faces++;
		}else{
			bad_count++;
			delete face;
		}

/*
		switch( polygons_type ){
			case ID_FACE: break;
			case ID_CURV: break;
			case ID_PACH: break;
			default:
				break;
		}
*/
	}

	if( bad_count > 0 ){
		dmsg( M_LWO, "%ld good polygons read %d bad polygons skipped", num_faces, bad_count );
		if( point_count>0 ){
			dmsg( M_LWO, "%d points, not yet supported", point_count );
		}
		if( line_count>0 ){
			dmsg( M_LWO, "%d lines, not yet supported", line_count );
		}
	}
}


/*!
	LWO2 Polygon Tag Mapping 

	PTAG { type[ID4], ( poly[VX], tag[U2] )* } 

	This chunk contains the all the tags of a given
	type for some subset of the polygons defined in
	the preceding POLS chunk. The type of the tag
	association is given by the first element of the
	chunk and is an normal 4-character ID code. The
	rest of the chunk is a list of polygon/tag
	associations. The polygon is identified by its
	index into the previous POLS chunk, and the tag
	is given by its index into the previous TAGS chunk.
	Any number of polygons may be mapped with this
	type of tag, and mappings should be read from the
	file until as many bytes as the chunk size
	specifies have been read. 

	Polygon tags types and their values are extensible,
	but there are some pre-defined types. The SURF type
	tags each polygon with the name of its surface. In
	LightWave 3D terminology, a "surface" is defined as
	a named set of shading attributes and may be described
	in the object file in SURF chunks. Another pre-defined
	type is PART which describes what aspect of the model
	each polygon belongs to, and SMGP which names the
	smoothing group for each polygon. Not all polygons
	have a value for every tag type, and the behavior for
	polygon which lack a certain tag depends on the type. 
*/
void LWLayer::polygonTags_ID4_d(){
	string_to_LWSurface::iterator s_it;
	string_to_Model    ::iterator m_it;
	U4_to_Face         ::iterator f_it;
	
	Face        *face;
	LWSurface   *surface;
	LWModel     *root_model;
	Model       *model;
	VX           polygon_index;
	U4           tag_index;
	ID4          tag_type;
	std::string  tag_value;

	root_model = this->model;
	if( root_model == NULL ){
		emsg( M_LWO, "Can not access root Model" );
		return;
	}

	if( (f->getOptions() & LWFILE_OPTION_SKIP_MATERIAL_M) == LWFILE_OPTION_SKIP_MATERIAL_M ){
		surface = new LWSurface( this, this, "skipped materials" );
		model   = this;
		model->setMaterial( surface );  //  FIX
	}


	tag_type = f->read_ID4();

	while( f->domainLeft() > 0 ){

		polygon_index = f->read_VX();
		tag_index	  = f->read_U2();
		tag_value     = root_model->getTag( tag_index );

		switch( tag_type ){
		case ID_SURF:
			f_it = faces   .find( polygon_index );
			s_it = surfaces.find( tag_value 	);
			m_it = models  .find( tag_value     );

			//  We absolutely need the face to be added
			if( f_it != faces.end() ){
				face = (*f_it).second;
				if( face == NULL ){
					emsg( M_LWO, "FACE FOUND AS NULL" );
					break;
				}
			}else{
				emsg( M_LWO, "FACE NOT FOUND" );
				break;
			}

			//  If first polygon to be added to the surface,
			//  then the surface has not been created yet.
			if( !((f->getOptions() & LWFILE_OPTION_SKIP_MATERIAL_M) == LWFILE_OPTION_SKIP_MATERIAL_M) ){
				if( s_it == surfaces.end() ){
					surface = new LWSurface( this, NULL, tag_value );
					surfaces.insert( std::make_pair(tag_value,surface) );
				}else{
					surface = (*s_it).second;
				}

				//  Find mesh, create new if needed
				if( m_it == models.end() ){
					model = new Model( tag_value );
					models.insert( std::make_pair(tag_value,model) );
					model->setMaterial( surface );  // FIX
					this->add( model );  // == submeshes.push_back( mesh );
				}else{
					model = (*m_it).second;
				}

				//  Connection needed for texture coordinates
				surface->setModel( model );
			}
			model->add( face );

			break;

		default:
			dmsg( M_LWO, "UNKNOWN TAG" );
			break;
		}  //  switch( tag_type );
	}  //  while( f->domainLeft() > 0 )
}


/*!
	LWO2 Envelope Definition 

	ENVL { index[U4], attributes[SUB-CHUNK] * } 

	Each ENVL chunk defines the time-varying curve for a single parameter channel.
	The index is used to identify this envelope uniquely, and can have any non-zero
	value less than 0x1000000. Following the index is a series of sub-chunks, which
	are like normal IFF chunks except that their sizes are specified by short
	integers instead of longs. The number of sub-chunks may vary depending on the
	complexity of the envelope, so sub-chunks should be read from the file until as
	many bytes as the chunk size specifies have been read. New types of sub-chunks
	may be introduced as the program capabilities increase, but any unknown sub-chunks
	may be skipped over by using their size. 
*/
void LWLayer::envelope_U4_sc(){
	U4          envelope_index = f->read_U4();
	LWEnvelope *envelope       = new LWEnvelope( f );

	envelopes.insert( make_pair(num_envelopes,envelope) );  //  pair<U4,LWEnvelope*>(num_envelopes,envelope)
	num_envelopes++;
	while( f->domainLeft() > 0 ){
		envelope->processEnvelope();
	}
}


/*!
	LWO2 Image or Sequence Definition 

	CLIP { index[U4], attributes[SUB-CHUNK] * } 

	Each CLIP chunk defines a image which can be used for applying as a texture
	map in surfaces. The term 'clip' is used to describe these since they may be
	time-varying sequences or animations rather than just stills. The index
	identifies this clip uniquely and may be any non-zero value less than 0x1000000.
	The attributes which define the source imagery and modifiers follow as a variable
	list of sub-chunks
*/
void LWLayer::clip_U4_sc(){
	U4      clip_index = f->read_U4();
	LWClip *clip       = new LWClip( f );

	if( clip_index >= 0x1000000 ){
		emsg( M_LWO, "Clip index not below 0x1000000" );
	}

	clips.insert( make_pair(clip_index,clip) );
	num_clips++;
	while( f->domainLeft() > 0 ){
		clip->processClip();
	}
}


/*!
	\todo Material inheritance

	LWO2 Surface Definition 

	SURF { name[S0], source[S0], attributes[SUB-CHUNK] * } 

	Each SURF chunk describes the shading attributes of a particular surface.
	These chunks begin with the name of the surface being described plus the
	name of the source surface. If the source name is non-null, then this surface
	is derived from the source surface. The base attributes of the source surface
	can be overridden by this surface, and texture blocks can be added to the
	source surface. The material attributes follow as a variable list of sub-chunks. 
*/
void LWLayer::surf_S0_S0_sc(){
	string_to_LWSurface::iterator  s_it;
	std::string                    surface_name;
	std::string                    surface_source;
	LWSurface                     *surface; 

	surface_name   = f->read_S0();
	surface_source = f->read_S0();

	s_it = surfaces.find( surface_name );
	if( s_it != surfaces.end() ){
		surface = (*s_it).second;
		if( surface == NULL ){
			emsg( M_LWO, "NULL surface %s in surfacelist", surface_name.c_str() );
			return;
		}
	}else{
		dmsg( M_LWO, "New SURF" );
		surface = new LWSurface( this, NULL, surface_name.c_str() );
	}
	
	if( surface_source.length() > 0 ){
		dmsg( M_LWO, "LW Object loader: No material inheritance yet" );
		//  FIX copy material properties
	}
	while( f->domainLeft() > 0 ){
		surface->processSubChunk();
	}
	surface->endSurface();
}


/*!
	LWO2 Bounding Box 

	BBOX { min[VEC12], max[VEC12] } 

	This is an optional chunk which can be included to store the bounding box
	for the vertex data in a layer. The min and max vectors are the lower and
	upper corners of the bounding box. 
*/
void LWLayer::boundingBox_VEC12_VEC12(){
	bbox_min = f->read_VEC12();
	bbox_max = f->read_VEC12();
}


/*!
	LWO2 Description Line 

	DESC { description-line[S0] } 

	This is an optional chunk which can be used to hold an object description.
	This should be a simple line of upper and lowercase characters, punctuation
	and spaces which describes the contents of the object file. There should be
	no control characters in this text string and it should generally be kept
	short. 
*/
void LWLayer::descriptionLine_S0(){
	description_line = f->read_S0();
}


/*!
	LWO2 Commentary Text 

	TEXT { comment[S0] } 

	This is another optional chunk which can be used to hold comments about the
	object. The text is just like the DESC chunk, but it can be about any subject,
	it may contain newline characters and it does not need to be particularly short. 
*/
void LWLayer::comments_S0(){
	commentary_text = f->read_S0();
}


/*!
	LWO2 Thumbnail Icon Image 

	ICON { encoding[U2], width[U2], data[U1] * } 

	This optional chunk contains an iconic or thumbnail image for the object
	which can be used when viewing the file in a browser. The encoding is a
	code for the data format which can only be zero for now meaning uncompressed,
	unsigned bytes as RGB triples. The width specifies the number of pixels
	contained in each row of the image. The data consists of rows of pixels
	(RGB triples for now), and the height of the image is determined by the
	length of the data.
*/
void LWLayer::thumbnail_U2_U2_d(){
	U2 encoding = f->read_U2();
	U2 width    = f->read_U2();

	if( encoding != 0 ){
		dmsg( M_LWO, "Unknown thumbnail encoding" );
		return;
	}

	while( f->domainLeft() > 0 ){
		for( int x=0; x<width; x++ ){
			U1 red	 = f->read_U1();
			U1 green = f->read_U1();
			U1 blue  = f->read_U1();
			//  FIX store data to texture
		}
	}
}


};  //  namespace Imports
};  //  namespace Teddy


#endif  //  TEDDY_INCLUDE_LW_SCENE

#if 0

RedCone - bug

LWO: LWOB lwo file Data/lwo/redcone.lwo length 882
LWO: LWOB::SRFS (1397900883) (4 bytes)
LWO: LWOB::PNTS (1347310675) (312 bytes)
LWO: LWOB::POLS (1347374163) (480 bytes)
LWO: LWOB::SURF (1398100550) (50 bytes)
LWO: LWOB::SURF::COLR (4 bytes)
LWO: LWOB::SURF::FLAG (2 bytes)
LWO: LWOB::SURF::DIFF (2 bytes)
LWO: LWOB::SURF::VDIF (4 bytes)
LWO: LWOB::SURF::SMAN (4 bytes)

Greenball - no bug

LWO: LWOB lwo file Data/lwo/greenball.lwo length 8566
LWO: LWLayer constructor
LWO: LWOB::SRFS (1397900883) (6 bytes)
LWO: LWOB::PNTS (1347310675) (3192 bytes)
LWO: LWOB::POLS (1347374163) (5280 bytes)
LWO: LWOB::SURF (1398100550) (52 bytes)
LWO: LWOB::SURF::COLR (4 bytes)
LWO: LWOB::SURF::FLAG (2 bytes)
LWO: LWOB::SURF::DIFF (2 bytes)
LWO: LWOB::SURF::VDIF (4 bytes)
LWO: LWOB::SURF::SMAN (4 bytes)

#endif

