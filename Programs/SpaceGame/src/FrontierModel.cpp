
/*
	TSGL - Teddy Space Game Library
	Copyright (C) 2002 Timo Suoranta
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


#include "Teddy/Materials/Material.h"
#include "Teddy/Models/Model.h"
#include "Teddy/Models/Vertex.h"
#include "Teddy/Models/Face.h"
#include "Teddy/SysSupport/Exception.h"
#include "Teddy/SysSupport/Messages.h"
#include <cstdio>

#include "FrontierModel.h"
#include "FrontierFile.h"
using namespace Teddy::Materials;
using namespace Teddy::Models;


/*static*/ const int FrontierModel::OPT_DEBUG               = (1ul<< 1ul);
/*static*/ const int FrontierModel::OPT_REAL_SCALING        = (1ul<< 2ul);
/*static*/ const int FrontierModel::OPT_DO_CHILDREN         = (1ul<< 3ul);
/*static*/ const int FrontierModel::OPT_DO_TRIANGLES        = (1ul<< 4ul);
/*static*/ const int FrontierModel::OPT_DO_MIRROR_TRIANGLES = (1ul<< 5ul);
/*static*/ const int FrontierModel::OPT_DO_QUADS            = (1ul<< 6ul);
/*static*/ const int FrontierModel::OPT_DO_MIRROR_QUADS     = (1ul<< 7ul);
/*static*/ const int FrontierModel::OPT_DO_LINES            = (1ul<< 8ul);
/*static*/ const int FrontierModel::OPT_DO_SPLINES          = (1ul<< 9ul);
/*static*/ const int FrontierModel::OPT_DO_POLYS            = (1ul<<10ul);
/*static*/ const int FrontierModel::OPT_DO_BALLS            = (1ul<<11ul);
/*static*/ const int FrontierModel::OPT_DO_ELLIPSOIDS       = (1ul<<12ul);
/*static*/ const int FrontierModel::OPT_DO_CYLINDERS        = (1ul<<13ul);
/*static*/ const int FrontierModel::OPT_DO_CONES            = (1ul<<14ul);


//!  Constructor
FrontierModel::FrontierModel( FrontierFile *f, int ob_id, Material *m, Options ffe_options )
:Model(name)
{
    this->setMaterial( m );
    this->options = ffe_options;
	this->f       = f;

	try {
		parseObject  ( ob_id-1 );
		parseSpecs   ();
		parseVertices();
		parseNormals ();
		parseElements();
	}catch( Exception &e ){
		dprint( M_FFE, "\n%s\n", e.tellMsg() );
	}

	this->setupClipRadius();
}


//!  Parse object structure from file
void FrontierModel::parseObject( const int object_index ){
	char *object_pointer = "";
	int   i;

	//  Seek to object directory
	f->reset();
	f->seek( "DATA_004681:" );
	f->get_label_def();

	//  Skip until we are at correct object index
	for( i=0; i<object_index+2; i++ ){
		object_pointer = f->get_label_ref();
	}
	strcat( object_pointer,  ":" );

	f->reset();
	f->seek( object_pointer );
	f->get_label_def();

	model_pointer     = f->get_label_ref();
	vertex_pointer    = f->get_label_ref();
	vertex_count      = f->read_Uint32	();
	normal_pointer    = f->get_label_ref();
	normal_count      = f->read_Uint32	();  //  normals + 2
	scale             = f->read_Uint32	();
	unknown_3         = f->read_Uint32	();
	radius            = f->read_Uint32	();
	primitive_count   = f->read_Uint32	();
	unknown_4         = f->read_Uint32	();
	unknown_5         = f->read_Uint32	();
	unknown_6         = f->read_Uint32	();
	unknown_7         = f->read_Uint32	();
	collision_pointer = f->get_label_ref();
	spec_pointer      = f->get_label_ref();
	unknown_8         = f->read_Uint32	();
	unknown_9         = f->read_Uint32	();

	if( options.isEnabled(OPT_REAL_SCALING) ){
		//	dprint( M_FFE, " SCALE %d ", scale );
		vertex_scale = double(0.0002)*(double)(1<<scale);
	}else{
		vertex_scale = 1;
	}

	strcat( model_pointer,     ":" );
	strcat( vertex_pointer,    ":" );
	strcat( normal_pointer,    ":" );
	strcat( collision_pointer, ":" );
	strcat( spec_pointer,      ":" );
}


void FrontierModel::parseSpecs(){
	char *name_pointer = "";
	int   i;

	if( strcmp( spec_pointer, "NULL:" ) == 0 ){
		dmsg( M_FFE, "Object has no ship specifications" );
		return;
	}

	f->reset(); //  Rewind to start of file
	f->seek( spec_pointer );
	f->get_label_def();

	Uint16  foward_thrust     = f->read_Uint16();  // 0 1
	Uint16  reverse_thrust    = f->read_Uint16();  // 2 3
	Uint8   gm                = f->read_Uint8();   // 4
	Uint8   sm                = f->read_Uint8();   // 5
	Uint16  mass              = f->read_Uint16();  // 6 7
	Uint16  internal_capacity = f->read_Uint16();  // 8 9
	Uint16  price             = f->read_Uint16();  // a b  10 11
	Uint16  zoom_factor       = f->read_Uint16();  // c d  12 13
	Uint8   id                = f->read_Uint8();   // e	  14
	Uint8   s_unknown_1       = f->read_Uint8();   // f	  15
	Uint8   crew              = f->read_Uint8();   // 10   16
	Uint8   s_unknown_2       = f->read_Uint8();   // 11   17
	Uint8   missiles          = f->read_Uint8();   // 12   18
	Uint8   s_unknown_3       = f->read_Uint8();   // 13   19
	Uint8   drive             = f->read_Uint8();   // 14   20
	Uint8   integral_drive    = f->read_Uint8();   // 15   21
	f->reset();                  //  Rewind to start of file
	f->seek( "DATA_004682:" );	 //  Seek to name directory
	for( i=0; i<id+2; i++ ){
		name_pointer = f->get_label_ref();
	}
	strcat( name_pointer, ":" );
	f->reset();                   //  Rewind to start of file
	f->seek( name_pointer );
	f->get_label_def();
	char *object_name = f->get_string();
	setName( object_name );
	dprint( M_FFE, "Object %s\n", object_name );
}


//!
void FrontierModel::parseVertices(){
//	Vertex *v1;
//	Vertex *v2;
//	int     i;

	f->reset();
	f->seek( vertex_pointer );
	f->get_label_def();
	dprint( M_FFE, "Reading %d = %xh vertices from %s\n", vertex_count, vertex_count, vertex_pointer );
	try {
		current_vertex_index = 0;
		while( current_vertex_index<vertex_count ){
			makeVertex();
		}
	}catch( Exception &e ){
		dmsg( M_FFE, e.tellMsg() );
		throw( Exception("Exception while reading object vertices" )  );
	}
}


//!  Parse normals
void FrontierModel::parseNormals(){
	try{
		if( strcmp( normal_pointer, "NULL:" ) != 0 ){
			f->reset();
			f->seek( normal_pointer );
			f->get_label_def();
			int i = 0;
			this->normals.insert( pair<int,Vertex*>(i,new Vertex(0, 1,0)) ); i++;
			this->normals.insert( pair<int,Vertex*>(i,new Vertex(0,-1,0)) ); i++;
			while( f->get_type() == FF_BYTE ){
				long    b0 = f->get_byte_low( false );
				long    b1 = f->get_byte();
				long    x  = f->read_Sint8();
				long    y  = f->read_Sint8();
				long    z  = f->read_Sint8();
				long    w  = f->read_Sint8();
				Vertex *v1 = new Vertex(  x, y, z );
				Vertex *v2 = new Vertex( -x, y, z );
				v1->normalize();
				v2->normalize();
				this->normals.insert( pair<int,Vertex*>(i,v1) ); i++;
				this->normals.insert( pair<int,Vertex*>(i,v2) ); i++;
			}
		}
	}catch( Exception &e ){
		dprint( M_FFE, "\nException while reading normals\n" );
		dmsg( M_FFE, e.tellMsg() );
		throw( Exception("Exception while reading normals") );
	}
}


// Following parameters are WORDS.
// LowParam1 stands for "low byte of parameter 1"
// HighParam2 for "high byte of parameter 2", etc.
void FrontierModel::readParams( int word_count ){
	for( int i=0; i<word_count*2; ){
		par[i++] = f->get_byte_low( true ); poly_pos++;
		par[i++] = f->get_byte_low( true ); poly_pos++;
		dprint( M_FFE, " %02lx:%02lx", par[i-2], par[i-1] );
	}
}
long FrontierModel::low( int index ){
	return par[(2*index)-2];
}
long FrontierModel::high( int index ){
	return par[(2*index)-1];
}


void FrontierModel::parseElements(){
	unsigned long h_a;
	unsigned long h_b;
	unsigned long command;
	unsigned long material;

	//	Read in elements
	f->reset();
	f->seek( model_pointer );
	f->get_label_def();
    f->seek( 1 );

	dmsg( M_FFE, "%s", model_pointer );
	while( true ){
		try {
			h_a = f->get_byte_low( true );
			h_b = f->get_byte_low( true );
		}catch( Exception &e ){
			dprint( M_FFE, "\n%s", e.tellMsg() );
			throw( Exception("Exception while reading object command header") );
		}
		header   = (h_b<<8) + (h_a);  
		command  = header & 0x001f;   //  Each command is held in the LOWER 5 BITS of the FIRST WORD of the command;
		material = header & 0xffe0;   //  The upper 11 bits are MATERIAL PARAMETERS.

		dprint( M_FFE, " %02lx:%02lx (%02lx)  ", h_b, h_a, command );
		try {
			switch( command ){
			case 0x00: cStop              (); break;
			case 0x01: cDrawBall          (); break;
			case 0x02: cDrawLine          (); break;
			case 0x03: cDrawTriangle      (); break;
			case 0x04: cDrawQuad          (); break;
			case 0x05: cDrawPoly          (); break;
			case 0x06: cUnknown06         (); break;
			case 0x07: cDrawMirrorTriangle(); break;
			case 0x08: cDrawMirrorQuad    (); break;
			case 0x09: cDrawEllipsoid     (); break;
			case 0x0a: cDrawText          (); break;
			case 0x0b: cFarClip           (); break;
			case 0x0c: cNearClip          (); break;
			case 0x0d: cMath              (); break;
			case 0x0e: cChild             (); break;
			case 0x0f: cUnknown0f         (); break;
			case 0x10: cDrawCylinder      (); break;
			case 0x11: cDrawCone          (); break;
			case 0x12: cUnknown12         (); break;
			case 0x13: cIfNotClip         (); break;
			case 0x14: cIfSetClip         (); break;
			case 0x15: cUnknown15         (); break;
			case 0x16: cDrawSpline        (); break;
			case 0x17: cUnknown17         (); break;
			case 0x18: cUnknown18         (); break;  //  BallArray?
			case 0x19: cUnknown19         (); break;
			case 0x1a: cUnknown1a         (); break;  //  MaterialControl?
			case 0x1b: cScaledChild       (); break;
			case 0x1c: cTransform         (); break;  //  'rotate?'
			case 0x1d: cMath              (); break;
			case 0x1e: cUnknown1e         (); break;
			case 0x1f: cUnknown1f         (); break;  //  GlobeStripe?
			default:
				dprint( M_FFE, " -Unknown command %x\n", command );
				break;
			}
		}catch( Exception &e ){
			dprint( M_FFE, "\n%s", e.tellMsg() );
			throw( Exception("Exception while interpreting object command" )  );
		}
	}
}

