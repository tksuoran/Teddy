
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


#ifndef SPACE_GAME__FRONTIER_MODEL__H
#define SPACE_GAME__FRONTIER_MODEL__H


#include "Teddy/MixIn/Options.h"
#include "Teddy/Models/Model.h"
#include "Teddy/Models/Face.h"
#include "Teddy/SysSupport/StdMap.h"


typedef map<int, Teddy::Models::Vertex *, less<int> > int_to_Vertex;


class FrontierFile;


//!  Reverse-engineered Frontier First Encounters data file source object file parser
class FrontierModel : public Teddy::Models::Model {
public:
	static const int OPT_DEBUG;
	static const int OPT_REAL_SCALING;
	static const int OPT_DO_CHILDREN;
	static const int OPT_DO_TRIANGLES;
	static const int OPT_DO_MIRROR_TRIANGLES;
	static const int OPT_DO_QUADS;
	static const int OPT_DO_MIRROR_QUADS;
	static const int OPT_DO_LINES;
	static const int OPT_DO_SPLINES;
	static const int OPT_DO_POLYS;
	static const int OPT_DO_BALLS;
	static const int OPT_DO_ELLIPSOIDS;
	static const int OPT_DO_CYLINDERS;
	static const int OPT_DO_CONES;

public:
	FrontierModel( 
		FrontierFile               *f, 
		int                         ob_id, 
		Teddy::Materials::Material *m, 
		Teddy::MixIn::Options       ffe_options
	);

protected:
	long    low             ( int index );
	long    high            ( int index );
	void    readParams      ( int count );
	bool    getVertex       ( int index, Teddy::Maths::TVector<float> &v );
	bool    getVertex       ( int index, Teddy::Models::Vertex **v );

	void    faceBegin       ();
	void    faceInsertVertex( int index );
	void    faceInsertSpline( int p1, int p2, int c1, int c2 );
	void    faceClose       ( int normal_index = -1 );
	void    makeVertex      ();
	void    parseObject     ( const int object_index );
	void    parseVertices   ();
	void    parseNormals    ();
	void    parseSpecs      ();
	void    parseElements   ();

	void    pStop           ();
	void    pBeginSpline    ();
	void    pBeginLine      ();
	void    pContLine       ();
	void    pContSpline     ();
	void    pClose          ();
	void    pCircle         ();

	void    cStop              ();
	void    cDrawBall          ();
	void    cDrawLine          ();
	void    cDrawTriangle      ();
	void    cDrawQuad          ();
	void    cDrawPoly          ();
	void    cUnknown06         ();
	void    cDrawMirrorTriangle();
	void    cDrawMirrorQuad    ();
	void    cDrawEllipsoid     ();
	void    cDrawText          ();
	void    cFarClip           ();
	void    cNearClip          ();
	void    cMath              ();
	void    cChild             ();
	void    cUnknown0f         ();
	void    cDrawCylinder      ();
	void    cDrawCone          ();
	void    cUnknown12         ();
	void    cIfNotClip         ();
	void    cIfSetClip         ();
	void    cUnknown15         ();
	void    cDrawSpline        ();
	void    cUnknown17         ();
	void    cUnknown18         ();  //  BallArray?
	void    cUnknown19         ();
	void    cUnknown1a         ();  //  MaterialControl?
	void    cScaledChild       ();
	void    cTransform         ();  //  'rotate?'
	void    cUnknown1e         ();
	void    cUnknown1f         ();  //  GlobeStripe?

	//  Object struct
	char     *model_pointer;
	char     *vertex_pointer;
	Sint32    vertex_count;
	char     *normal_pointer;
	Uint32    normal_count;
	Uint32    scale;
	Uint32    unknown_3;
	Uint32    radius;
	Sint32    primitive_count;
	Uint32    unknown_4;
	Uint32    unknown_5;
	Uint32    unknown_6;
	Uint32    unknown_7;
	char     *collision_pointer;
	char     *spec_pointer;
	Uint32    unknown_8;
	Uint32    unknown_9;
	Sint32    current_vertex_index;
	double    vertex_scale;

	Teddy::MixIn::Options  options;

	unsigned long          par[256];               //  Parameter buffer
	unsigned long          header;
	int                    poly_pos;
	unsigned long          poly_low0;
	unsigned long          poly_command;

	FrontierFile          *f;
	Teddy::Models::Face   *face;
	bool                   face_open;
	bool                   face_good;
	int                    face_num_vertices;
	int                    last_vertex_index;
	int_to_Vertex          vertices;
	int_to_Vertex          normals;
	//list<Element*>::const_iterator  debug_selected_element_it;
};


#endif  //  SPACE_GAME__FRONTIER_MODEL__H

