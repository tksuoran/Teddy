
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
#include "Teddy/Maths/Quaternion.h"
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
using namespace Teddy::Maths;
using namespace Teddy::Models;	


void FrontierModel::cDrawLine(){
	// 02 -- Line [param1] <param2>
	// Display a line with material parameters. Line is from LowParam1 to HighParam1.
	readParams( 2 );
	if( options.isEnabled(OPT_DO_LINES) ){
		bool    line_ok = true;
		Vertex *v1      = NULL;
		Vertex *v2      = NULL;
		line_ok &= getVertex( low (2), &v1 );
		line_ok &= getVertex( high(2), &v2 );
		if( line_ok ){
			Vector vv1 = v1->getVertex(); dprint( M_FFE, "\n% 3d % 9.4f % 9.4f %9.4f\n", low(2), vv1[0], vv1[1], vv1[2] );
			Vector vv2 = v2->getVertex(); dprint( M_FFE, "% 3d % 9.4f % 9.4f %9.4f\n",  high(2), vv2[0], vv2[1], vv2[2] );
			Line *l = new Line( v1, v2 );
			add( l );
			dprint(M_FFE, " -DrawLine OK\n" );
		}else{
			dprint(M_FFE, " -DrawLine BAD\n" );
		}
	}else{
		dprint(M_FFE, " -(DrawLine)\n" );
	}
}


void FrontierModel::cDrawSpline(){
	// 16 -- Bezier Curve [param1] [param2] [param3]
	// Draw a Bezier curve from HighParam1 to LowParam2 using HighParam2 and
	// LowParam1 as control points. HighParam3 seems unused, LowParam3 points to
	// Normal denominator. Draw a single bezier curve as a line instead as part of a
	// plane; see the suspension bridge for an example. The orbit ellipse on solar
	// system maps are also plain bezier curves.

	// Basic spline: (0x)16, 00, m1, m2, v2, v4, v1, v3, n, 00
	// Used for powerlines etc. m1, m2 are the material word (should be simple
	// colour), v1 and v4 are end vertices, v2 and v3 are control points, n is
	// normal index for lighting only (no culling).

	readParams( 4 );
	if( options.isEnabled(OPT_DO_SPLINES) ){
		bool    line_ok = true;
		Vertex *v1      = NULL;
		Vertex *v2      = NULL;
		line_ok &= getVertex( low (3), &v1 );
		line_ok &= getVertex( high(2), &v2 );
		if( line_ok ){
			Vector vv1 = v1->getVertex(); dprint( M_FFE, "\n% 3d % 9.4f % 9.4f %9.4f\n", low(2), vv1[0], vv1[1], vv1[2] );
			Vector vv2 = v2->getVertex(); dprint( M_FFE, "% 3d % 9.4f % 9.4f %9.4f\n",  high(2), vv2[0], vv2[1], vv2[2] );
			Line *l = new Line( v1, v2 );
			add( l );
			dprint( M_FFE, " -DrawSpline OK\n" );
		}else{
			dprint( M_FFE, " -DrawSpline BAD\n" );
		}
	}else{
		dprint( M_FFE, " -(DrawSpline)\n" );
	}
}



void FrontierModel::cDrawTriangle(){
	// 03 -- Triangle [param1] [param2] <param3>
	// Display a triangle with material parameters. Coordinates are LowParam1,
	// HighParam1, and HighParam2. LowParam2 is Normal determinator [see further on].
	readParams( 3 );
	if( options.isEnabled(OPT_DO_TRIANGLES) ){
		faceBegin();
		faceInsertVertex( low (2) );
		faceInsertVertex( high(3) );
		faceInsertVertex( high(2) );
		faceClose( low(3) );
		dprint( M_FFE, " -DrawTriangle\n" );
	}else{
		dprint( M_FFE, " -(DrawTriangle)\n" );
	}
}

void FrontierModel::cDrawMirrorTriangle(){
	// 07 -- Mirrored Triangle [param1] <param2> <param3>
	// Phew. A comprehensible one. Display TWO triangles; one with the original
	// coordinates LowParam1, HighParam1, and HighParam2, the other one with the
	// mirrored equivalents of these points. Watch out! That means that the other
	// coordinates are (LowParam1 XOR 1), (HighParam1 XOR 1) and (HighParam2 XOR 1),
	// since these coordinates might be odd as well as even and it does NOT mean
	// "this coordinate plus one". Take my word for it. LowParam2 is again the
	// Normal determinator.
	readParams( 3 );
	if( options.isEnabled(OPT_DO_MIRROR_TRIANGLES) ){
		faceBegin();
		faceInsertVertex( low (2) );
		faceInsertVertex( high(2) );
		faceInsertVertex( high(3) );
		faceClose( low(3) );
		faceBegin();
		faceInsertVertex( low (2)^1 );
		faceInsertVertex( high(2)^1 );
		faceInsertVertex( high(3)^1 );
		faceClose( low(3)^1 );
		dprint( M_FFE, " -DrawMirroredTriangle\n" );
	}else{
		dprint( M_FFE, " -(DrawMirroredTriangle)\n" );
	}
}


void FrontierModel::cDrawQuad(){
	// 04 -- Quad [param1] [param2] [param3] <param4>
	// Display a quadrilateral (nice word innit? It's a four sided section).
	// Coordinates are LowParam1, HighParam1, LowParam2, and HighParam2. Param3
	// contains the Normal determinator.
	readParams( 4 );
	if( options.isEnabled(OPT_DO_QUADS) ){
		bool quad_ok = true;
        Vector v1;
        Vector v2;
        Vector v3;
        Vector v4;
		quad_ok &= getVertex( low (2), v1 );
		quad_ok &= getVertex( high(2), v2 );
		quad_ok &= getVertex( low (3), v3 );
		quad_ok &= getVertex( high(3), v4 );
		if( quad_ok ){
			Vector n1 = normalVector( v2, v3, v4 );
			Vector n2 = normalVector( v3, v4, v1 );
			double dp = n1 | n2;
			faceBegin();
			if( dp > 0 ){
				dprint( M_FFE, " -DrawQuad POS\n" );
				faceInsertVertex( low (2) );
				faceInsertVertex( high(2) );
				faceInsertVertex( low (3) );
				faceInsertVertex( high(3) );
			}else{
				dprint( M_FFE, " -DrawQuad NEG\n" );
				faceInsertVertex( low (2) );
				faceInsertVertex( low (3) );
				faceInsertVertex( high(2) );
				faceInsertVertex( high(3) );
			}
			faceClose( low(4) );
		}else{
			dprint( M_FFE, " -DrawQuad BAD\n" );
		}
	}else{
		dprint( M_FFE, " -(DrawQuad)\n" );
	}
}


void FrontierModel::cDrawMirrorQuad(){
	// 08 -- Mirrored Quad [param1] [param2] [param3] <param4>
	// Display a quadrilateral with coordinates LowParam1, HighParam1, LowParam2, and
	// HighParam2, and a mirrored quad in the same vein as described for the
	// mirrored triangle (07).
	readParams( 4 );
	if( options.isEnabled(OPT_DO_MIRROR_QUADS) ){
		faceBegin();
		faceInsertVertex( low (2) );
		faceInsertVertex( high(3) );
		faceInsertVertex( high(2) );
		faceInsertVertex( low (3) );
		faceClose( low(4) );
		faceBegin();
		faceBegin();
		faceInsertVertex( low (2)^1 );
		faceInsertVertex( high(3)^1 );
		faceInsertVertex( high(2)^1 );
		faceInsertVertex( low (3)^1 );
		faceClose( low(4)^1 );
		dprint( M_FFE, " -DrawMirrorQuad\n" );
	}else{
		dprint( M_FFE, " -(DrawMirrorQuad)\n" );
	}
}


void FrontierModel::pStop(){
	// Type 0x0: Length 2 bytes. Terminates stream.
	// Surface will be closed off if not already terminated.
	if( options.isEnabled(OPT_DO_POLYS) ){
		faceClose();
		dprint( M_FFE, " -PStop- " );
	}else{
		dprint( M_FFE, " -(PStop)- " );
	}
}


void FrontierModel::pBeginSpline(){
	// Type 0x2: Length 6 bytes. Format v1:02  v2:v1  v4:v3
	// Starts a surface with a spline. v1 and v4 are end points, v2 and v3 are
	// intermediate control points. Note that the first byte is a copy of the
	// third. Only the third is used for processing, but the first can be used
	// as the depth-sort index.
	readParams( 2 );
	if( options.isEnabled(OPT_DO_POLYS) ){
		faceBegin();
		faceInsertSpline( high(1), low(2), low(1), high(2) );
		dprint( M_FFE, " -PBeginSpline- " );
	}else{
		dprint( M_FFE, " -(PBeginSpline)- " );
	}
}


void FrontierModel::pBeginLine(){
	// Type 0x4: Length 4 bytes. Format v1:04  v2:00
	// Starts a surface with a line. v1 and v2 are end points.
	readParams( 1 );
	if( options.isEnabled(OPT_DO_POLYS) ){
		faceBegin();
		faceInsertVertex( poly_low0 );
		faceInsertVertex( low(1)    );
		dprint( M_FFE, " -PBeginLine- " );
	}else{
		dprint( M_FFE, " -(PBeginLine)- " );
	}
}


void FrontierModel::pContLine(){
	// Type 0x6: Length 2 bytes. Format v2, 06
	// Continues a surface with a line. v1 is taken from the previous element
	// in the stream. v1 and v2 are end points.
	if( options.isEnabled(OPT_DO_POLYS) ){
		faceInsertVertex( poly_low0 );
		dprint( M_FFE, " -PContLine- " );
	}else{
		dprint( M_FFE, " -(PContLine)- " );
	}
}


void FrontierModel::pContSpline(){
	// Type 0x8: Length 4 bytes. Format v2:08, v4:v3
	// Continues a surface with a spline. v1 is taken from the previous element
	// in the stream. v1 and v4 are end points, v2 and v3 are intermediate
	// control points.
	if( options.isEnabled(OPT_DO_POLYS) ){
		readParams( 1 );
		faceInsertSpline( last_vertex_index, low(1), poly_low0, high(1) );
		dprint( M_FFE, " -PContSpline- " );
	}else{
		dprint( M_FFE, " -(PContSpline)- " );
	}
}


void FrontierModel::pClose(){
	// Type 0xa: Length 2 bytes. Format 00, 0a
	// Terminates a surface, completing with a line as necessary. Note that
	// multiple surfaces can be defined in a single stream as a result.
	if( options.isEnabled(OPT_DO_POLYS) ){
		faceClose();
		dprint( M_FFE, " -PClose- " );
	}else{
		dprint( M_FFE, " -(PClose)- " );
	}
}


void FrontierModel::cDrawPoly(){
	readParams( 1 );  //  Material
	readParams( 1 );
	int poly_bytes  = high(1);
	int poly_normal = low (1);
	poly_pos        = 0;

	while( poly_pos < poly_bytes ){
		readParams( 1 );
		poly_low0    = low (1);
		poly_command = high(1);
		switch( poly_command ){
		case 0x00: pStop       (); break;
		case 0x02: pBeginSpline(); break;
		case 0x04: pBeginLine  (); break;
		case 0x06: pContLine   (); break;
		case 0x08: pContSpline (); break;
		case 0x0a: pClose      (); break;
		case 0x0c: pCircle     (); break;
		default: dprint( M_FFE, " ?\n" ); break;
		}
	}
	dprint( M_FFE, " -DrawPoly\n" );
}


void FrontierModel::cStop(){
	// 00 -- Stop
	// Stop executing immediately. There may or may not be data in the 11 upper bits
	// but I've found no proper use for them.
	dprint( M_FFE, " -Stop\n" );
}


void FrontierModel::cDrawCylinder(){
	// 10 -- Cylinder [param1] [param2] [param3]
	// Draw a cylinder from LowParam1 to HighParam1. I have no idea about radii and
	// such. The cylinder may have different radii for its start and end, but the
	// end caps are never filled in.
	readParams( 3 );
	if( options.isEnabled(OPT_DO_CYLINDERS) ){
		bool   cylinder_ok = true;
		Vector v1;
		Vector v2;
		cylinder_ok &= getVertex( low (1), v1 );  //  From
		cylinder_ok &= getVertex( high(1), v2 );  //  To
		if( cylinder_ok ){
			Vertex *vx1 = new Vertex( v1 );
			Vertex *vx2 = new Vertex( v2 );
			//getVertex( low (1), &vx1 );
			//getVertex( high(1), &vx2 );
			Vector vv1 = vx1->getVertex(); dprint( M_FFE, "\nvv1 = % 9.4f % 9.4f %9.4f\n", vv1[0], vv1[1], vv1[2] );
			Vector vv2 = vx2->getVertex(); dprint( M_FFE, "vv2 = % 9.4f % 9.4f %9.4f\n",   vv2[0], vv2[1], vv2[2] );
			Line *l = new Line( vx1, vx2 );
//  		dprint( M_FFE, "\nv1 = % 9.4f % 9.4f %9.4f\n", v1[0], v1[1], v1[2] );
//			dprint( M_FFE, "v2 = % 9.4f % 9.4f %9.4f\n",   v2[0], v2[1], v2[2] );
			add( l );
#if 1
			Vector  direction = v2 - v1;    //  From v1 to v2
			double  len       = direction.magnitude(); direction.normalize();
			Cone   *co        = new Cone( "", 2.0, 2.0, len, 8, 8, false, false );

			Matrix m;
			m.direction( direction );
			co->transformVertices( m );

			Matrix      translation;
			translation.translateMatrix( v1 );
			co->transformVertices( translation );

			co->setupClipRadius();
			add( co );
#endif
			dprint( M_FFE, " -DrawCylinder\n" );
		}
	}else{
		dprint( M_FFE, " -(DrawCylinder)\n" );
	}
}


void FrontierModel::cDrawCone(){
	// 11 -- Cone [param1] [param2] [param3] [param4] [param5] <param6>
	// Draw a cone from LowParam1 to HighParam1. By observation, it seems to be
	// possible to adjust both start and end radius, as well as the color of both
	// the top and bottom circle of the cone, i.e. it is the same as 10h but with
	// filled end caps.
	readParams( 6 );
	if( options.isEnabled(OPT_DO_CONES) ){
		bool   cone_ok = true;
		Vector v1;
		Vector v2;
		cone_ok &= getVertex( low (2), v1 );  //  From
		cone_ok &= getVertex( high(2), v2 );  //  To
		if( cone_ok ){
			Vertex *vx1 = new Vertex( v1 );
			Vertex *vx2 = new Vertex( v2 );
			//getVertex( low (1), &vx1 );
			//getVertex( high(1), &vx2 );
			Vector vv1 = vx1->getVertex(); dprint( M_FFE, "\nvv1 = % 9.4f % 9.4f %9.4f\n", vv1[0], vv1[1], vv1[2] );
			Vector vv2 = vx2->getVertex(); dprint( M_FFE, "vv2 = % 9.4f % 9.4f %9.4f\n",   vv2[0], vv2[1], vv2[2] );
			Line *l = new Line( vx1, vx2 );
//  		dprint( M_FFE, "\nv1 = % 9.4f % 9.4f %9.4f\n", v1[0], v1[1], v1[2] );
//			dprint( M_FFE, "v2 = % 9.4f % 9.4f %9.4f\n",   v2[0], v2[1], v2[2] );
			add( l );
#if 1
			Vector  direction = v2 - v1;    //  From v1 to v2
			double  len       = direction.magnitude(); direction.normalize();
			Cone   *co        = new Cone( "", 2.0, 2.0, len, 8, 8, false, false );

			Matrix m;
			m.direction( direction );
			co->transformVertices( m );

			Matrix      translation;
			translation.translateMatrix( v1 );
			co->transformVertices( translation );

			co->setupClipRadius();
			add( co );
#endif
			dprint( M_FFE, " -DrawCone\n" );
		}
	}else{
		dprint( M_FFE, " -(DrawCone)\n" );
	}
}


void FrontierModel::cDrawBall(){
	// 01 -- Ball [param1] [param2] <param3]
	// Display a ball with material parameters. Param1 is the radius (rather silly; the low-
	// and high-byte should be reversed), HighParam2 is the coordinate to display at. Other
	// values unknown. This command is frequently used to depict lights -- see the description
	// of "materials" for the how and why. Param1 depicts a variable instead of a fixed number
	// when bit #7 of param1 is set -- this is how lights grow and shrink.
	readParams( 3 );
	if( options.isEnabled(OPT_DO_BALLS) ){
/*
	bool     ball_ok = true;
	Vertex  *v1      = NULL;
	ball_ok &= getVertex( high(3), &v1 );
	if( ball_ok ){
		Vector vv1 = v1->getVertex(); dprint( M_FFE, "\n% 3d % 9.4f % 9.4f %9.4f\n", low(2), vv1[0], vv1[1], vv1[2] );
		int r1 = low (2);
		int r2 = high(2);
		int r = (r1<<8) + (r2);
		// double fr = (double)(r)/(double)(255.0);
        double fr = M_PI;
		Sphere *ball = new Sphere( "", fr, 10, 10 );
        Matrix m;
		m.translateMatrix( vv1[0], vv1[1], vv1[2] );
		ball->transformVertices( &m );
		ball->setupClipRadius();
		this->insert( ball );
        dprint( M_FFE, " Ball OK %d %d % 9.4f ", r1, r2, fr );
	}else{
        dprint( M_FFE, " Ball BAD " );
		}*/
	}else{
		dprint( M_FFE, " -(DrawBall)\n" );
	}
}


void FrontierModel::cDrawEllipsoid(){
	// 09 -- Pine [param1] [param2] [param3]
	// I called this a pine because I first got to grips with it on an object I
	// referred to as "14 Pine trees". Itsa kinda pear shaped object, larger side on
	// HighParam1, pointy side on LowParam1. Param2 apparently relates to the
	// thickness of the circumference. This object pops up not only as a pine tree
	// but also as a chimney flame and, more distinguishable, as engine flares. When used
	// as engine flare or chimney flame, one of the end points moves about randomly; when
	// used as a tree it does not. There should be a flag somewhere...

	// Thrust-jet effect: 09, 00, m1, m2, v1, v2, s1, s2
	// m1 and m2 are the material word, usually 0xee, 0x20. v1 and v2 are
	// vertices for start and end of the thrust jet - v2 is generally a linear
	// animated vertex. s1 and s2 are a size word, probably representing the
	// width of the jet.

	readParams( 3 );
	if( options.isEnabled(OPT_DO_ELLIPSOIDS) ){
		dprint( M_FFE, " -DrawEllipsoid\n" );
	}else{
		dprint( M_FFE, " -(DrawEllipsoid)\n" );
	}
}


void FrontierModel::pCircle(){
	// Type 0xc: Length 4 bytes. Format vc, 0c, n, r
	// Creates a complete 3d circle surface (ellipse in 2d) using two splines.
	// vc is centre vertex index, n is surface normal index, r is radius in
	// model units.
	readParams( 1 );
	dprint( M_FFE, " -(PCircle)- " );
}


void FrontierModel::cDrawText(){
	// 0A -- Text [param1] [param2] [param3] <param4>
	// Yes, Text!  HighParam1 is the scale, but bit #4 is used for "2nd Font
	// Selection" (see "Text and Fonts" below). Apparently the scale range is 0..15.
	// LowParam1 is the Normal for the text.
	// LowParam2 is the location of the text, and, presumably, HighParam2 is some sort
	// of orientation. Param3 is interesting: values from 4000h..406Fh denote a
	// fixed text string from the same place as the Ship Description (see Section 6).
	// Value 3016h seems to be the current ships ID, or, in the case of space
	// stations and bases, the base name. Value 3022h is used with the Cargo Pod;
	// apparently this would hold a string such as "Hydrogen" or "Robots", or
	//"Fertilizer" or "Narcotics" in the more aggressive games.
	readParams( 4 );
	dprint( M_FFE, " -(DrawText)\n" );
}


void FrontierModel::cChild(){
	// 0E -- Sub-Object [param1] (opt. [param2] [param3])
	// A very nice one: the remaining 11 bits of the command form a number between
	// 0..239, and yes: this points to one of the other objects. It should be
	// inserted on coordinate #LowParam1, and rotated and twisted according to
	// HighParam1 (see later on rotation). Funny thing: if bit #15 of param1 is set,
	// the next two words are coordinates which are to be inserted in the sub-object.
	int ob = header>>5;
	readParams( 1 );
	if( high(1) & 0x80 == 0x80 ){
		readParams( 2 );
	}

	if( options.isEnabled(OPT_DO_CHILDREN) ){

		bool   child_ok = true;
		Vector offset;
		child_ok &= getVertex( low(1), offset );
		if( child_ok ){
			f->push();
			Model *child = new FrontierModel( f, ob, this->getMaterial(), options  );  //  Eagle long range fighter
			Matrix m;
			m.translateMatrix( offset );
			child->transformVertices( m );
			child->setupClipRadius();
			add( child );
			f->pop();
		}
		dprint( M_FFE, " -Child( %d )\n", ob );
	}else{
		dprint( M_FFE, " -(Child %d )\n", ob );
	}
}


void FrontierModel::cScaledChild(){
	// 1B -- Scaled Subobject [param1] [param2] <param3> <param4> (opt. [param4] [param5])
	// This is the Scaled version of 0E (Sub-object); param1 is the same as with 0E
	// but param #2 seems to consist of two bytes determining the amount of scaling.
	// To be honest, I don't have a clue. If the highest bit of param1 is set, two
	// more parameters follow.
	int ob = header>>5;
	readParams( 3 );
	if( low(1) & 0x80 == 0x80 ){
		readParams( 2 );
	}

	if( options.isEnabled(OPT_DO_CHILDREN) ){
		bool   child_ok = true;
		Vector offset;
		child_ok &= getVertex( low(1), offset );
		if( child_ok ){
			dprint( M_FFE, "\nBeginScaledChild( %d )\n", ob );
			f->push();
			Model *child = new FrontierModel( f, ob, this->getMaterial(), options );
			Matrix m;
			m.translateMatrix( offset );
			child->transformVertices( m );
			child->setupClipRadius();
			add( child );
			f->pop();
			dprint( M_FFE, "\nEndScaledChild( %d )\n", ob );
		}else{
			dprint( M_FFE, " -ScaledChild( %d ) BAD\n", ob );
		}
	}else{
		dprint( M_FFE, " -(ScaledChild %d )\n", ob );
	}
}


void FrontierModel::cTransform(){
	// 1C -- Rotate? [param1]
	// For quite some time I've interpreted this as some kind of rotation. I just
	// don't know how to apply it. The command appears frequently just before text
	// (cmd. 0A) which is positioned onto an arbitrarily slanted plane. Here is a
	// part of the Cobra Mk 1 definition (the output is from a parser program I
	// wrote; the first number is a line number):

	// 312   191c 0000; rotate?
	// 316   833c 0554; rotate?
	// 320   888a 060a 4646 3016; Ship i.d. at #70, scale 6
	// 328   191c 0040; rotate?
	// 332   833c 0554; rotate?
	// 336   888a 060b 4648 3016; Ship i.d. at #72, scale 6

	// You'll notice that the first rotate? command (line 312) and the third (line
	// 328) are quite similar but opposite; the 2nd and 4th are equal. This complies
	// with what I know of the text on the Cobra Mk 1, which is on both left and
	// right top sides, and, of course, rotated rather than mirrored.
	readParams( 3 );
	dprint( M_FFE, " -(Transform?)\n" );
}


void FrontierModel::cFarClip(){
	// 0B -- Skip If Further [param1] / Skip if Invisible [param1]
	// If bit #15 of Param1 is NOT set: Take Param1 as an unsigned distance, and
	// compare it to the current distance. If you are further than that, skip the
	// remaining 11 bits times 2 bytes after the command. If bit #15 IS set:
	// the rest of Param1 identifies a Normal vector. Skip if this normal is not
	// visible. Clear? "006b 5b8c" means "skip the next 6 bytes if further than
	// 23436", "008b 8004" means "skip the next 8 bytes if Normal #4 is not visible.
	readParams( 1 );
	dprint( M_FFE, " -(FarClip)\n" );
}


void FrontierModel::cNearClip(){
	// 0C -- Skip If Nearer [param1] / Skip if Visible [param1]
	// The counterpart of cmd 0B. This time, just skip the number of bytes if you
	// are nearer than Param1, or the normal determined by Param1 is visible.
	readParams( 1 );
	// If bit #15 of Param1 is NOT set: Take Param1 as an unsigned distance, and
	// compare it to the current distance. If you are nearer than that, skip the
	// remaining 11 bits times 2 bytes after the command. If bit #15 IS set:
	// the rest of Param1 identifies a Normal vector. Skip if this normal is
	// visible. Clear? "006c 5b8c" means "skip the next 6 bytes if nearer than
	// 23436", "008c 8004" means "skip the next 8 bytes if Normal #4 is visible.
	dprint( M_FFE, " -(NearClip)\n" );
}


void FrontierModel::cIfNotClip(){
	// 13 -- Skip If Not [param1]
	// Skip 2*(high 11 bits) if NOT (Variable LowParam1 AND HighParam1). This pops
	// up frequently in describing space ships; the variable for equipment to be
	// tested seems to be 97h, and 81h seems to have something to do with the
	// landing gear.
	readParams( 1 );
	dprint( M_FFE, " -(IfNotClip)\n" );
}


void FrontierModel::cIfSetClip(){
	// 14 -- Skip If [param1]
	// Skip 2*(high 11 bits) if (Variable LowParam1 AND HighParam1). The counterpart
	// / of cmd 13, skipping if the bits are set. Primarily used in the same regions as
	// cmd 13.
	readParams( 1 );
	dprint( M_FFE, " -(IfSetClip)\n" );
}


void FrontierModel::cMath(){
	// 0D -- Math [param1] / 1D -- Math [param1]
	// Now THIS is an interesting one. This is a math operation command, and the
	// command itself resides in the low byte, high 4 bits of the operand (hence
	// the grouping with 1D). The high byte of the operand is the destination
	// variable, Param1 holds a source variable and/or a numeric parameter (details
	// yet to be revealed). The mathematical operations possible are:

	// 0   dest = source1 + source2
	// 1   dest = source1 - source2
	// 2   dest = source1 * source2
	// 3   dest = source1 / source2
	// 4   dest = source1 SHR source2
	// 5   dest = source1 SHL source2
	// 6   dest = source1 IF source1 > source2
	// 7   dest = source1 IF source1 < source2
	// 8   dest = source1 * source2
	// 9   dest = source1 SAR source2
	// 10  Unknown so far
	// 11  dest = source1 IF source1 > source2 ELSE 0
	// 12  dest = source1 IF source1 < source2 ELSE 0
	// 13  dest = source1 * SIN source2
	// 14  dest = source1 * COS source2
	// 15  dest = source1 AND source2

	// One of the sources might be 40h or 41h -- apparently this is some 'zero'
	// value, used for simple assignments.
	readParams( 1 );
	dprint( M_FFE, " -(Math)\n" );
}


void FrontierModel::cUnknown06(){
	// 06 -- Irritating Value #1 [parameters 0 or more]
	// I have absolute no idea what this this is supposed to do. The most common
	// appearance seems to be FFE6h, somewhere at the start of an object definition.
	// Inbetween other commands 0006h pops up everywhere, serving only to annoy me.
	// Other values found are 4546h, 4586h, and 4686h (Lifter), 40C6h (Lifter
	// engine), and 4386h (Osprey). Even worse, in the Eagle Long Range Fighter it
	// appears to have a parameter (first as a sequence E406h FFE1h, later as E686h
	// FFFDh), as well as in the Imperial Courier (E606h FFE1h) and on a couple of
	// other places. I only can assume that the high-word high-nibbles 20h, 60h, and
	// E0h are to be blamed. When voting for most irritable value this might rank
	// high (but it gets worse!).
	/*			switch( header ){
	 case 0xe406: // ffe1
	 case 0xe686: // fffd
	 case 0xe606: // ffe1
	 readParams( 1 );
	 break;
	 default:
	 break;
	 }*/
	dprint( M_FFE, " -(Unknown 0x06)\n" );
}


void FrontierModel::cUnknown0f(){
	// 0F -- I Got No Idea
	// This command occurs only on the hexagonal factory (#162) and the clock face
	// (#231).
	//readParams( 1 );
	dprint( M_FFE, " -(Unknown 0x0f)\n" );
}


void FrontierModel::cUnknown12(){
	// 12 -- Unknown <param1>
	// Seems to have no parameters. Doesn't seem to occur much, anyway.
	readParams( 1 );
	dprint( M_FFE, " -(Unknown 0x12)\n" );
}


void FrontierModel::cUnknown15(){
	// 15 -- Unknown
	// Seems to have no parameters. Occurs a lot, but not in any predictable way.
	dprint( M_FFE, " -(Unknown 0x15)\n" );
}
void FrontierModel::cUnknown17(){
	// 17 -- Unused
	// Well AFAIK.
	readParams( 1 );
	dprint( M_FFE, " -(Unknown 0x17)\n" );
}

void FrontierModel::cUnknown18(){
	// 18 -- Ball Array [param1] [opt. more params]
	// This one is fun! LowParam1 determines the radius, the next byte values are
	// coordinates of a single ball, up to a 7Fh closing value. Word padding is done
	// when necessary by a second 7Fh value.
	dprint( M_FFE, " -(Unknown 0x18)\n" );
}


void FrontierModel::cUnknown19(){
	// 19 -- Unknown.
	// Seems to have no parameters.
	dprint( M_FFE, " -(Unknown 0x19)\n" );
}


void FrontierModel::cUnknown1a(){
	// 1A -- Unknown [param1] (opt. [param2] [param3] .. [param8])
	// Actually, Irritating Value #2. This one seems to have 1 parameter, and if
	// the highest bit of that parameter is set it has another 7 more. The values
	// seem to consist of RGB colors and somehow connects with the colors used on
	// the object. In that case param1 holds a variable number, and is (apparently)
	// used to change the color of selected objects to one of the 7 in the array.
	readParams( 1 );

	if( low(1) & 0x80 == 0x80 ){
		readParams( 8 );
		dprint( M_FFE, " -CASE 1A- " );
	}else{
		dprint( M_FFE, " -MON 1A- " );
	}
	dprint( M_FFE, " -(Material control?)\n" );
}


void FrontierModel::cUnknown1e(){
	// 1E -- Unknown
	// No known parameters. Occurs very little. No further information.
	dprint( M_FFE, " -(Unknown 0x1e)\n" );
}


void FrontierModel::cUnknown1f(){
	// 1F -- Unknown [lots and lots of parameters]
	// Occurs frequently on stars and planets. Other than that, I don't have a clue.
	// The number of parameters is 2*([original value] >> 5)+4. It seems some way of
	// defining a colored globe, including any marks on them. Most planets and stars
	// consist of this one command only.
	dprint( M_FFE, " -(Unknown 0x1f)\n" );
}

