
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
#include "Teddy/Models/Line.h"
#include "Teddy/Models/Model.h"
#include "Teddy/Models/Vertex.h"
#include "Teddy/Models/Face.h"
#include "Teddy/Models/Cone.h"
#include "Teddy/Models/Sphere.h"
#include "Teddy/Models/Cylinder.h"
#include "Teddy/SysSupport/Exception.h"
#include "Teddy/SysSupport/Messages.h"
#include <cstdio>

#include "FrontierModel.h"
#include "FrontierFile.h"
using namespace Teddy::Materials;
using namespace Teddy::Models;


// Vertex types by first byte (b0):
//  case 0, 1, 2:   Normal vertex, b2 = x, b3 = y, b4 = z
//  case 3, 4:      2d average of vertices indexed by b3, b4
//  case 5, 6:      Negative of vertex indexed by b3
//  case 7, 8:      Like normal vertex but reflected pair x=0 not x=-x
//  case 9, a:      3d average of vertices indexed by b3, b4
//  case b, c:      2d average of vertices indexed by b3, b4
//  case d, e:      3d arith: vertex b2 + vertex b3 - vertex b4
//  case f, 10:     3d arith: vertex b3 + vertex b4
//  case 15, 16:    Animated vertex, data from vertex b2, time from b3, b4
//  default:        Animated vertex, data from current vertex
void FrontierModel::makeVertex(){
	int     b0;
	int     b1;
	int     b2;
	int     b3;
	int     b4;
	int     b5;
	int     mode_1;
	int     mode_2;
	int     x;
	int     y;
	int     z;
	int     w;
	Vector  t1;
	Vector  t2;
	Vector  t3;
	Vector  t4;
	Vertex *v1        = new Vertex();
	Vertex *v2        = new Vertex();
    bool    vertex_ok = true;

	mode_1 = b0 = f->get_byte_low( true );
	mode_2 = b1 = f->get_byte();

	switch( mode_1 ){
	case 0x00:	//  Normal vertex, b2 = x, b3 = y, b4 = z
	case 0x01:  //   Rest is signed byte triple coordinate
	case 0x02:
	case 0x15:  //  Unknown so far, seems to be normal point
		x  = b2 = f->read_Sint8();
		y  = b3 = f->read_Sint8();
		z  = b4 = f->read_Sint8();
		w  = b5 = f->read_Sint8();
		v1->setVertex( Vector( x, y, z) * vertex_scale );
		v2->setVertex( Vector(-x, y, z) * vertex_scale );
		break;

	case 0x03:  //  2d average of vertices indexed by b3, b4
	case 0x04:
	case 0x09:  //  3d average of vertices indexed by b3, b4
	case 0x0a:
	case 0x0b:  //  2d average of vertices indexed by b3, b4
	case 0x0c:
	case 0x11:  //  Interpolate halfway between coord ref #2 and ref #3
		x  = b2 = f->read_Sint8();
		y  = b3 = f->read_Uint8();
		z  = b4 = f->read_Uint8();
		w  = b5 = f->read_Sint8();
		vertex_ok &= getVertex(b3,t1);
		vertex_ok &= getVertex(b4,t2);
		t3 = (t1 + t2) * 0.5;

		v1->setVertex( t3 );
		v2->setVertex( t3 );
		v2->flipX();
		break;

	case 0x05:  //  Negative of vertex indexed by b3  Mirror coordinate ref #2 along Y- and Z-axes
	case 0x06:
		x  = b2 = f->read_Sint8();
		y  = b3 = f->read_Uint8();
		z  = b4 = f->read_Uint8();
		w  = b5 = f->read_Sint8();
		vertex_ok &= getVertex(b3,t1);
		t1 *= -1;
		v1->setVertex( t1 );
		v2->setVertex( t1 );
		v2->flipX();
		break;

	case 0x07:  //  Copy coordinate ref #2 [?]
	case 0x08:
		x  = b2 = f->read_Sint8();
		y  = b3 = f->read_Sint8();
		z  = b4 = f->read_Sint8();
		w  = b5 = f->read_Sint8();
		v1->setVertex(  Vector(  x, y, z ) * vertex_scale  );
		v2->setVertex(  Vector(  0, y, z ) * vertex_scale  );
		break;

	case 0x0d:  //  3d arith: vertex b2 + vertex b3 - vertex b4
	case 0x0e:
		x  = b2 = f->read_Uint8();
		y  = b3 = f->read_Uint8();
		z  = b4 = f->read_Uint8();
		w  = b5 = f->read_Sint8();
		vertex_ok &= getVertex(b2,t1);
		vertex_ok &= getVertex(b3,t2);
		vertex_ok &= getVertex(b4,t3);
		t4 = t1 + t2 - t3;
		v1->setVertex( t4 );
		v2->setVertex( t4 );
		v2->flipX();
		break;

	case 0x0f:  //  3d arith: vertex b3 + vertex b4
	case 0x10:
		x  = b2 = f->read_Sint8();
		y  = b3 = f->read_Uint8();
		z  = b4 = f->read_Uint8();
		w  = b5 = f->read_Sint8();
		vertex_ok &= getVertex(b3,t1);
		vertex_ok &= getVertex(b4,t2);
        t3 = t1 + t2;
		v1->setVertex( t1 );
		v2->setVertex( t1 );
		v2->flipX();
		break;

	default:
	case 0x13:  //  Linear interpolation between vertices b3, b4
	case 0x14:
	case 0x19:  //  Interpolate between coord ref #2 and ref #3 according to variable ref #1
		x  = b2 = f->read_Uint8();
		y  = b3 = f->read_Uint8();
		z  = b4 = f->read_Uint8();
		w  = b5 = f->read_Sint8();
		vertex_ok &= getVertex(b3,t1);
		vertex_ok &= getVertex(b4,t2);
		t3 = (t1 + t2) * 0.5;
		v1->setVertex( t3 );
		v2->setVertex( t3 );
		v2->flipX();
		break;
	}

	if( vertex_ok == true ){
		//		dprint( M_FFE, "Vertex %02d ok  %02x:  b1=  %02x  b2=  %02x  b3=  %02x  b4=  %02x  b5=  %02x\n", index, mode_1, b1, b2, b3, b4, b5 );
		Vector vv1 = v1->getVertex();
        Vector vv2 = v2->getVertex();
//		dprint( M_FFE, "Vertex %02d ok  % 9.4f % 9.4f % 9.4f\n", current_vertex_index,   vv1[0], vv1[1], vv1[2] );
//  	dprint( M_FFE, "Vertex %02d ok  % 9.4f % 9.4f % 9.4f\n", current_vertex_index+1, vv2[0], vv2[1], vv2[2] );
	}else{
		dprint( M_FFE, "Vertex %02d bad %02x:  b1=% 4d  b2=% 4d  b3=% 4d  b4=% 4d  b5=% 4d\n", current_vertex_index, mode_1, b1, b2, b3, b4, b5 );
		dprint( M_FFE, "%02x %02x %02x %02x %02x %02x\n", mode_1, b1, b2, b3, b4, b5 );
        f->dump(200,200);
		v1->setVertex( Vector(0,0,0) );
		v2->setVertex( Vector(0,0,0) );
	}
	this->vertices.insert( make_pair(current_vertex_index++,v1) );
	this->vertices.insert( make_pair(current_vertex_index++,v2) );
}


void FrontierModel::faceBegin(){
	face_open = true;
    face_good = true;
	face      = new Face();
}

void FrontierModel::faceInsertVertex( int index ){
	if( !face_open ){
		faceBegin();
	}
	Vertex *vertex = NULL;
	int_to_Vertex::iterator  v_it;

	v_it = vertices.find( index );
	if( v_it!=vertices.end() ){
		vertex = (*v_it).second;
	}
	if( (vertex!=NULL) && (face_good == true) ){
		face_num_vertices++;
		face->append( vertex );
		last_vertex_index = index;
		dprint( M_FFE, " %d ", index );
	}else{
		face_good = false;
		dprint( M_FFE, " VX %d/%d NULL ", index, vertices.size() );
	}
}


bool FrontierModel::getVertex( int index, Vector &v ){
	int_to_Vertex::iterator  v_it;

	v_it = vertices.find( index );
	if( v_it!=vertices.end() ){
		Vertex *vx = (*v_it).second;
		if( vx == NULL ){
			return false;
		}else{
			v = vx->getVertex();
			return true;
		}
	}else{
        return false;
	}
}


bool FrontierModel::getVertex( int index, Vertex **v ){
	int_to_Vertex::iterator  v_it;

	v_it = vertices.find( index );
	if( v_it!=vertices.end() ){
		*v = (*v_it).second;
		if( *v == NULL ){
			return false;
		}else{
			return true;
		}
	}else{
        *v = NULL;
        return false;
	}
}


void FrontierModel::faceInsertSpline( int pi1, int pi2, int ci1, int ci2 ){
	if( !face_open ){
		dprint( M_FFE, " Face not open " );
		return;
	}
	bool    spline_good = true;
	Vector  p1;
	Vector  p2;
	Vector  c1;
	Vector  c2;

	spline_good &= getVertex( pi1, p1 );
	spline_good &= getVertex( pi2, p2 );
	spline_good &= getVertex( ci1, c1 );
	spline_good &= getVertex( ci2, c2 );

	if( spline_good == false ){
		dprint( M_FFE, " Spline not good " );
		return;
	}

	for( int i=1; i<=16; i++ ){
		double u = (double)(i)/(16.0);

		Vector  a   = (p1) * (                ::pow(      u , 3.0 )  );
		Vector  b   = (c1) * (3.0 * (1.0-u) * ::pow(      u , 2.0 )  );
		Vector  c   = (c2) * (3.0 *      u  * ::pow( (1.0-u), 2.0 )  );
		Vector  d   = (p2) * (                ::pow( (1.0-u), 3.0 )  );
        Vector  sum = a+b+c+d;
		Vertex *v   = new Vertex( sum );
		face_num_vertices++;
		face->append( v );
	}
    dprint( M_FFE, " Spline OK " );
	last_vertex_index = pi2;
}


void FrontierModel::faceClose( int normal_index ){
	if( face_open && face_good ){
		face->makeNormal();
		add( face );
		face      = NULL;
		face_open = false;
		face_good = false;
		dprint( M_FFE, " Face OK " );
	}
}


