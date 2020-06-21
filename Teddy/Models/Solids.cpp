
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


#include "Teddy/Models/Solids.h"
#include "Teddy/Models/Vertex.h"
#include "Teddy/SysSupport/StdMaths.h"


namespace Teddy  {
namespace Models {


static const double sq2 = sqrt( 2.0 );
static const double sq3 = sqrt( 3.0 );
static const double sq5 = sqrt( 5.0 );


Cube::Cube( double r )
:Model("Cube")
{
	Vertex *p[8];
	p[0] = new Vertex(-r / sq3,  r / sq3,  r / sq3); //Points
	p[1] = new Vertex( r / sq3,  r / sq3,  r / sq3);
	p[2] = new Vertex( r / sq3, -r / sq3,  r / sq3);
	p[3] = new Vertex(-r / sq3, -r / sq3,  r / sq3);
	p[4] = new Vertex(-r / sq3,  r / sq3, -r / sq3);
	p[5] = new Vertex( r / sq3,  r / sq3, -r / sq3);
	p[6] = new Vertex( r / sq3, -r / sq3, -r / sq3);
	p[7] = new Vertex(-r / sq3, -r / sq3, -r / sq3);

    addQuad(  p[0], p[1], p[2], p[3]  ); //Squares
	addQuad(  p[0], p[3], p[7], p[4]  );
	addQuad(  p[0], p[4], p[5], p[1]  );
	addQuad(  p[6], p[7], p[4], p[5]  );
	addQuad(  p[6], p[5], p[1], p[2]  );
	addQuad(  p[6], p[2], p[3], p[7]  );
	setupClipRadius();
}


Cuboctahedron::Cuboctahedron( double r )
:Model("Cuboctahedron")
{
	Vertex *p[12];

	p[ 0] = new Vertex(      0,      r,            0 ); //Points
	p[ 1] = new Vertex(  r / 2,  r / 2,  r * sq2 / 2 );
	p[ 2] = new Vertex(  r / 2,  r / 2, -r * sq2 / 2 );
	p[ 3] = new Vertex(      r,      0,            0 );
	p[ 4] = new Vertex(  r / 2, -r / 2,  r * sq2 / 2 );
	p[ 5] = new Vertex(  r / 2, -r / 2, -r * sq2 / 2 );
	p[ 6] = new Vertex(      0,     -r,            0 );
	p[ 7] = new Vertex( -r / 2, -r / 2,  r * sq2 / 2 );
	p[ 8] = new Vertex( -r / 2, -r / 2, -r * sq2 / 2 );
	p[ 9] = new Vertex(     -r,      0,            0 );
	p[10] = new Vertex( -r / 2,  r / 2,  r * sq2 / 2 );
	p[11] = new Vertex( -r / 2,  r / 2, -r * sq2 / 2 );

	//  Color::YELLOW
	addQuad( p[ 1], p[4], p[ 7], p[10] ); //Squares
	addQuad( p[ 4], p[3], p[ 5], p[ 6] );
	addQuad( p[ 1], p[3], p[ 2], p[ 0] );
	addQuad( p[ 2], p[5], p[ 8], p[11] );
	addQuad( p[10], p[9], p[11], p[ 0] );
	addQuad( p[ 7], p[6], p[ 8], p[ 9] );

	//  Color::BLUE
	addTri( p[ 0], p[1], p[10] ); //Triangles
	addTri( p[ 3], p[4], p[ 1] );
	addTri( p[ 4], p[6], p[ 7] );
	addTri( p[10], p[7], p[ 9] );
	addTri( p[ 0], p[2], p[11] );
	addTri( p[ 3], p[5], p[ 2] );
	addTri( p[ 5], p[6], p[ 8] );
	addTri( p[11], p[8], p[ 9] );

    setupClipRadius();
}


Dodecahedron::Dodecahedron( double r )
:Model("Dodecahedron")
{
	double a = 2.0 / (sq3 + sq3 * sq5);
	double b = 1.0 / (3.0 * a);

    Vertex *p[20];
	p[ 0] = new Vertex( r / sq3,  r / sq3,  r / sq3); //Points
	p[ 1] = new Vertex( r / sq3,  r / sq3, -r / sq3);
	p[ 2] = new Vertex( r / sq3, -r / sq3,  r / sq3);
	p[ 3] = new Vertex( r / sq3, -r / sq3, -r / sq3);
	p[ 4] = new Vertex(-r / sq3,  r / sq3,  r / sq3);
	p[ 5] = new Vertex(-r / sq3,  r / sq3, -r / sq3);
	p[ 6] = new Vertex(-r / sq3, -r / sq3,  r / sq3);
	p[ 7] = new Vertex(-r / sq3, -r / sq3, -r / sq3);
	p[ 8] = new Vertex(       0,  r * a,  r * b);
	p[ 9] = new Vertex(       0,  r * a, -r * b);
	p[10] = new Vertex(       0, -r * a,  r * b);
	p[11] = new Vertex(       0, -r * a, -r * b);
	p[12] = new Vertex( r * a,  r * b,        0);
	p[13] = new Vertex( r * a, -r * b,        0);
	p[14] = new Vertex(-r * a,  r * b,        0);
	p[15] = new Vertex(-r * a, -r * b,        0);
	p[16] = new Vertex( r * b,        0,  r * a);
	p[17] = new Vertex( r * b,        0, -r * a);
	p[18] = new Vertex(-r * b,        0,  r * a);
	p[19] = new Vertex(-r * b,        0, -r * a);

    addPenta( p[10], p[ 8], p[4], p[18], p[6] ); //Pentagons
	addPenta( p[10], p[ 8], p[0], p[16], p[2] );
	addPenta( p[11], p[ 9], p[1], p[17], p[3] );
	addPenta( p[ 9], p[11], p[7], p[19], p[5] );
	addPenta( p[17], p[16], p[2], p[13], p[3] );
	addPenta( p[17], p[16], p[0], p[12], p[1] );
	addPenta( p[19], p[18], p[6], p[15], p[7] );
	addPenta( p[19], p[18], p[4], p[14], p[5] );
	addPenta( p[12], p[14], p[4], p[ 8], p[0] );
	addPenta( p[12], p[14], p[5], p[ 9], p[1] );
	addPenta( p[13], p[15], p[6], p[10], p[2] );
	addPenta( p[13], p[15], p[7], p[11], p[3] );

    setupClipRadius();
}


Icosahedron::Icosahedron( double r )
:Model("Icosahedron")
{
	double a = 2.0 / (1.0 + sq5);
	double b = sqrt((3.0 + sq5) / (1.0 + sq5));
	a /= b;

    Vertex *p[12];
	p[ 0] = new Vertex(      0,  r * a,  r / b ); //Points
	p[ 1] = new Vertex(      0,  r * a, -r / b );
	p[ 2] = new Vertex(      0, -r * a,  r / b );
	p[ 3] = new Vertex(      0, -r * a, -r / b );
	p[ 4] = new Vertex(  r * a,  r / b,      0 );
	p[ 5] = new Vertex(  r * a, -r / b,      0 );
	p[ 6] = new Vertex( -r * a,  r / b,      0 );
	p[ 7] = new Vertex( -r * a, -r / b,      0 );
	p[ 8] = new Vertex(  r / b,      0,  r * a );
	p[ 9] = new Vertex(  r / b,      0, -r * a );
	p[10] = new Vertex( -r / b,      0,  r * a );
	p[11] = new Vertex( -r / b,      0, -r * a );

    
	addTri( p[1], p[ 4], p[ 6]); //Triangles
	addTri( p[0], p[ 6], p[ 4]);
	addTri( p[0], p[ 2], p[10]);
	addTri( p[0], p[ 8], p[ 2]);
	addTri( p[1], p[ 3], p[ 9]);
	addTri( p[1], p[11], p[ 3]);
	addTri( p[2], p[ 5], p[ 7]);
	addTri( p[3], p[ 7], p[ 5]);
	addTri( p[6], p[10], p[11]);
	addTri( p[7], p[11], p[10]);
	addTri( p[4], p[ 9], p[ 8]);
	addTri( p[5], p[ 8], p[ 9]);
	addTri( p[0], p[10], p[ 6]);
	addTri( p[0], p[ 4], p[ 8]);
	addTri( p[1], p[ 6], p[11]);
	addTri( p[1], p[ 9], p[ 4]);
	addTri( p[3], p[11], p[ 7]);
	addTri( p[3], p[ 5], p[ 9]);
	addTri( p[2], p[ 7], p[10]);
	addTri( p[2], p[ 8], p[ 5]);

    setupClipRadius();
}


Octahedron::Octahedron( double r )
:Model("Octahedron")
{
    Vertex *p[6];
	p[0] = new Vertex( 0,  r,  0); //Points
	p[1] = new Vertex( 0, -r,  0);
	p[2] = new Vertex(-r,  0,  0);
	p[3] = new Vertex( 0,  0, -r);
	p[4] = new Vertex( r,  0,  0);
	p[5] = new Vertex( 0,  0,  r);

	addTri( p[0], p[2], p[3] ); //Triangles
	addTri( p[0], p[3], p[4] );
	addTri( p[0], p[4], p[5] );
	addTri( p[0], p[5], p[2] );
	addTri( p[1], p[2], p[3] );
	addTri( p[1], p[3], p[4] );
	addTri( p[1], p[4], p[5] );
	addTri( p[1], p[5], p[2] );

    setupClipRadius();
}


Tetrahedron::Tetrahedron( const double r )
:Model("Tetrahedron")
{
    Vertex *p[4];
	p[0] = new Vertex(                 0,          r,                  0   ); //Points
	p[1] = new Vertex(                 0,   -r / 3.0,  r * 2.0 * sq2 / 3.0 );
	p[2] = new Vertex(-r * sq3 * sq2 / 3.0, -r / 3.0,       -r * sq2 / 3.0 );
	p[3] = new Vertex( r * sq3 * sq2 / 3.0, -r / 3.0,       -r * sq2 / 3.0 );

	addTri( p[0], p[1], p[2] ); //Triangles
	addTri( p[0], p[1], p[3] );
	addTri( p[0], p[2], p[3] );
	addTri( p[1], p[2], p[3] );

    setupClipRadius();
}


TruncatedCube::TruncatedCube( double r )
:Model("TruncatedCube")
{
	double a = (1.0 + sq2) / (2.0 * sqrt(5.0 / 2.0 + sq2));
	double b = 1.0 / (2.0 * sqrt(5.0 / 2.0 + sq2));

    Vertex *p[24];
	p[ 0] = new Vertex( r * b,  r * a,  r * a); //Points
	p[ 1] = new Vertex( r * a,  r * b,  r * a);
	p[ 2] = new Vertex( r * a, -r * b,  r * a);
	p[ 3] = new Vertex( r * b, -r * a,  r * a);
	p[ 4] = new Vertex(-r * b, -r * a,  r * a);
	p[ 5] = new Vertex(-r * a, -r * b,  r * a);
	p[ 6] = new Vertex(-r * a,  r * b,  r * a);
	p[ 7] = new Vertex(-r * b,  r * a,  r * a);
	p[ 8] = new Vertex( r * a,  r * a,  r * b);
	p[ 9] = new Vertex( r * a, -r * a,  r * b);
	p[10] = new Vertex(-r * a, -r * a,  r * b);
	p[11] = new Vertex(-r * a,  r * a,  r * b);
	p[12] = new Vertex( r * a,  r * a, -r * b);
	p[13] = new Vertex( r * a, -r * a, -r * b);
	p[14] = new Vertex(-r * a, -r * a, -r * b);
	p[15] = new Vertex(-r * a,  r * a, -r * b);
	p[16] = new Vertex( r * b,  r * a, -r * a);
	p[17] = new Vertex( r * a,  r * b, -r * a);
	p[18] = new Vertex( r * a, -r * b, -r * a);
	p[19] = new Vertex( r * b, -r * a, -r * a);
	p[20] = new Vertex(-r * b, -r * a, -r * a);
	p[21] = new Vertex(-r * a, -r * b, -r * a);
	p[22] = new Vertex(-r * a,  r * b, -r * a);
	p[23] = new Vertex(-r * b,  r * a, -r * a);

	//  Material::BLUE
	addTri( p[ 0], p[ 1], p[ 8] ); //Triangles
	addTri( p[ 2], p[ 3], p[ 9] );
	addTri( p[ 4], p[ 5], p[10] );
	addTri( p[ 6], p[ 7], p[11] );
	addTri( p[16], p[17], p[12] );
	addTri( p[18], p[19], p[13] );
	addTri( p[20], p[21], p[14] );
	addTri( p[22], p[23], p[15] );

	//  Material::YELLOW
	addOcta( p[ 0], p[ 1], p[ 2], p[ 3], p[ 4], p[ 5], p[ 6], p[ 7] ); //Octagons
	addOcta( p[ 1], p[ 2], p[ 9], p[13], p[18], p[17], p[12], p[ 8] );
	addOcta( p[ 3], p[ 4], p[10], p[14], p[20], p[19], p[13], p[ 9] );
	addOcta( p[ 5], p[ 6], p[11], p[15], p[22], p[21], p[14], p[10] );
	addOcta( p[ 7], p[ 0], p[ 8], p[12], p[16], p[23], p[15], p[11] );
	addOcta( p[16], p[17], p[18], p[19], p[20], p[21], p[22], p[23] );

    setupClipRadius();
}


TruncatedCuboctahedron::TruncatedCuboctahedron( double r )
:Model("TruncatedCuboctahedron")
{
    Vertex *p[24];
	p[ 0] = new Vertex(-r / (sq2 * sq3),  r / (sq2 * sq3),  r *  sq2 / sq3 ); // Points
	p[ 1] = new Vertex( r / (sq2 * sq3),  r / (sq2 * sq3),  r *  sq2 / sq3 );
	p[ 2] = new Vertex( r / (sq2 * sq3), -r / (sq2 * sq3),  r *  sq2 / sq3 );
	p[ 3] = new Vertex(-r / (sq2 * sq3), -r / (sq2 * sq3),  r *  sq2 / sq3 );
	p[ 4] = new Vertex(-r / (sq2 * sq3),  r *  sq2 / sq3 ,  r / (sq2 * sq3));
	p[ 5] = new Vertex(-r / (sq2 * sq3),  r *  sq2 / sq3 , -r / (sq2 * sq3));
	p[ 6] = new Vertex( r / (sq2 * sq3),  r *  sq2 / sq3 , -r / (sq2 * sq3));
	p[ 7] = new Vertex( r / (sq2 * sq3),  r *  sq2 / sq3 ,  r / (sq2 * sq3));
	p[ 8] = new Vertex( r *  sq2 / sq3 ,  r / (sq2 * sq3),  r / (sq2 * sq3));
	p[ 9] = new Vertex( r *  sq2 / sq3 ,  r / (sq2 * sq3), -r / (sq2 * sq3));
	p[10] = new Vertex( r *  sq2 / sq3 , -r / (sq2 * sq3), -r / (sq2 * sq3));
	p[11] = new Vertex( r *  sq2 / sq3 , -r / (sq2 * sq3),  r / (sq2 * sq3));
	p[12] = new Vertex( r / (sq2 * sq3),  r / (sq2 * sq3),  r / (sq2 * sq3));
	p[13] = new Vertex( r / (sq2 * sq3),  r / (sq2 * sq3), -r / (sq2 * sq3));
	p[14] = new Vertex(-r / (sq2 * sq3),  r / (sq2 * sq3), -r / (sq2 * sq3));
	p[15] = new Vertex(-r / (sq2 * sq3),  r / (sq2 * sq3),  r / (sq2 * sq3));
	p[16] = new Vertex(-r *  sq2 / sq3 , -r / (sq2 * sq3),  r / (sq2 * sq3));
	p[17] = new Vertex(-r *  sq2 / sq3 , -r / (sq2 * sq3), -r / (sq2 * sq3));
	p[18] = new Vertex(-r *  sq2 / sq3 ,  r / (sq2 * sq3), -r / (sq2 * sq3));
	p[19] = new Vertex(-r *  sq2 / sq3 ,  r / (sq2 * sq3),  r / (sq2 * sq3));
	p[20] = new Vertex(-r / (sq2 * sq3),  r / (sq2 * sq3), -r *  sq2 / sq3 );
	p[21] = new Vertex( r / (sq2 * sq3),  r / (sq2 * sq3), -r *  sq2 / sq3 );
	p[22] = new Vertex( r / (sq2 * sq3), -r / (sq2 * sq3), -r *  sq2 / sq3 );
	p[23] = new Vertex(-r / (sq2 * sq3), -r / (sq2 * sq3), -r *  sq2 / sq3 );

	addTri( p[ 0], p[19], p[ 4] ); //Triangles
	addTri( p[ 1], p[ 7], p[ 8] );
	addTri( p[ 2], p[11], p[12] );
	addTri( p[ 3], p[15], p[16] );
	addTri( p[20], p[ 5], p[18] );
	addTri( p[21], p[ 9], p[ 6] );
	addTri( p[22], p[13], p[10] );
	addTri( p[23], p[17], p[14] );

	//  Material::YELLOW
	addQuad( p[ 0], p[ 1], p[ 2], p[ 3] ); //Squares
	addQuad( p[ 4], p[ 5], p[ 6], p[ 7] );
	addQuad( p[ 8], p[ 9], p[10], p[11] );
	addQuad( p[12], p[13], p[14], p[15] );
	addQuad( p[16], p[17], p[18], p[19] );
	addQuad( p[20], p[21], p[22], p[23] );

	//  Material::GREEN
	addQuad( p[ 0], p[ 4], p[ 7], p[ 1] );
	addQuad( p[ 1], p[ 8], p[11], p[ 2] );
	addQuad( p[ 2], p[12], p[15], p[ 3] );
	addQuad( p[ 3], p[16], p[19], p[ 0] );
	addQuad( p[20], p[ 5], p[ 6], p[21] );
	addQuad( p[21], p[ 9], p[10], p[22] );
	addQuad( p[22], p[13], p[14], p[23] );
	addQuad( p[23], p[17], p[18], p[20] );

	setupClipRadius();
}


TruncatedOctahedron::TruncatedOctahedron( double r )
:Model("TruncatedOctahedron")
{
    Vertex *p[24];
	p[ 0] = new Vertex(           0,      r / sq5,  r * 2 / sq5); //Points
	p[ 1] = new Vertex(     r / sq5,            0,  r * 2 / sq5);
	p[ 2] = new Vertex(           0,     -r / sq5,  r * 2 / sq5);
	p[ 3] = new Vertex(    -r / sq5,            0,  r * 2 / sq5);
	p[ 4] = new Vertex(           0,  r * 2 / sq5,      r / sq5);
	p[ 5] = new Vertex(    -r / sq5,  r * 2 / sq5,            0);
	p[ 6] = new Vertex(           0,  r * 2 / sq5,     -r / sq5);
	p[ 7] = new Vertex(     r / sq5,  r * 2 / sq5,            0);
	p[ 8] = new Vertex( r * 2 / sq5,            0,      r / sq5);
	p[ 9] = new Vertex( r * 2 / sq5,      r / sq5,            0);
	p[10] = new Vertex( r * 2 / sq5,            0,     -r / sq5);
	p[11] = new Vertex( r * 2 / sq5,     -r / sq5,            0);
	p[12] = new Vertex(           0, -r * 2 / sq5,      r / sq5);
	p[13] = new Vertex(     r / sq5, -r * 2 / sq5,            0);
	p[14] = new Vertex(           0, -r * 2 / sq5,     -r / sq5);
	p[15] = new Vertex(    -r / sq5, -r * 2 / sq5,            0);
	p[16] = new Vertex(-r * 2 / sq5,            0,      r / sq5);
	p[17] = new Vertex(-r * 2 / sq5,     -r / sq5,            0);
	p[18] = new Vertex(-r * 2 / sq5,            0,     -r / sq5);
	p[19] = new Vertex(-r * 2 / sq5,      r / sq5,            0);
	p[20] = new Vertex(           0,      r / sq5, -r * 2 / sq5);
	p[21] = new Vertex(     r / sq5,            0, -r * 2 / sq5);
	p[22] = new Vertex(           0,     -r / sq5, -r * 2 / sq5);
	p[23] = new Vertex(    -r / sq5,            0, -r * 2 / sq5);

	//  Material::YELLOW
	addQuad( p[ 0], p[ 1], p[ 2], p[ 3] ); //Squares
	addQuad( p[ 4], p[ 5], p[ 6], p[ 7] );
	addQuad( p[ 8], p[ 9], p[10], p[11] );
	addQuad( p[12], p[13], p[14], p[15] );
	addQuad( p[16], p[17], p[18], p[19] );
	addQuad( p[20], p[21], p[22], p[23] );

	addHexa( p[ 0], p[ 4], p[ 7], p[ 9], p[ 8], p[ 1] ); //Hexagons
	addHexa( p[ 1], p[ 8], p[11], p[13], p[12], p[ 2] );
	addHexa( p[ 2], p[12], p[15], p[17], p[16], p[ 3] );
	addHexa( p[ 3], p[16], p[19], p[ 5], p[ 4], p[ 0] );
	addHexa( p[20], p[ 6], p[ 7], p[ 9], p[10], p[21] );
	addHexa( p[21], p[10], p[11], p[13], p[14], p[22] );
	addHexa( p[22], p[14], p[15], p[17], p[18], p[23] );
	addHexa( p[23], p[18], p[19], p[ 5], p[ 6], p[20] );

    setupClipRadius();
}


/*
Rhomicuboctahedron        ::Rhomicuboctahedron        (){}
Rhombicosidodecahedron    ::Rhombicosidodecahedron    (){}
TruncatedDodecahedron     ::TruncatedDodecahedron     (){}
TruncatedIcosahedron      ::TruncatedIcosahedron      (){}
TruncatedIcosidodecahedron::TruncatedIcosidodecahedron(){}
TruncatedTetrahedron      ::TruncatedTetrahedron      (){}
*/


};  //  namespace Models
};  //  namespace Teddy

