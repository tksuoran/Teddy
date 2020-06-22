
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


#include "Teddy/Models/Box.h"
#include "Teddy/Models/QuadStrip.h"
#include "Teddy/Models/Vertex.h"


namespace Teddy  {
namespace Models {


/*!
	\brief Box constructor
	\param name Name for new Box Model
	\param x_size X-Size of box (will expand to both minus and plus)
	\param y_size Y-Size of box (will expand to both minus and plus)
	\param z_size Z-Size of box (will expand to both minus and plus)
	\param x_div Number of subdivisions on X direction
	\param y_div Number of subdivisions on Y direction
	\param z_div Number of subdivisions on Z direction
*/
Box::Box(
	const std::string &name,
	const float        x_size,
	const float        y_size,
	const float        z_size,
	const int          x_div,
	const int          y_div,
	const int          z_div
)
:
Model( name )
{
	int x;
	int y;
	int z;

	//  Top and bottom
	for( x = -x_div; x < x_div; x++ ){
		float x1 =    x  * (x_size / x_div);
		float x2 = (1+x) * (x_size / x_div);
		QuadStrip *top = new QuadStrip();
		QuadStrip *bot = new QuadStrip();
		for( z = -z_div; z <= z_div; z++ ){
			float z1 = z * (z_size / z_div);
			top->add( new Vertex(x1, y_size,z1) );
			top->add( new Vertex(x2, y_size,z1) );
			bot->add( new Vertex(x2,-y_size,z1) );
			bot->add( new Vertex(x1,-y_size,z1) );
		}
		top->setNormal( 0.0f, 1.0f, 0.0f );
		bot->setNormal( 0.0f,-1.0f, 0.0f );
		top->enable( Element::EL_USE_ELEMENT_NORMAL );
		bot->enable( Element::EL_USE_ELEMENT_NORMAL );
		add( top );
		add( bot );
		QuadStrip *fro = new QuadStrip();
		QuadStrip *bac = new QuadStrip();
		for( y = -y_div; y <= y_div; y++ ){
			float y1 = y * (y_size / y_div);

			fro->add( new Vertex(x2,y1, z_size) );
			fro->add( new Vertex(x1,y1, z_size) );
			bac->add( new Vertex(x1,y1,-z_size) );
			bac->add( new Vertex(x2,y1,-z_size) );
		}
		fro->setNormal( 0.0f, 0.0f,  1.0f );
		bac->setNormal( 0.0f, 0.0f, -1.0f );
		fro->enable( Element::EL_USE_ELEMENT_NORMAL );
		bac->enable( Element::EL_USE_ELEMENT_NORMAL );
		add( fro );
		add( bac );
	}

	//  Left and right
	for( z = -z_div; z < z_div; z++ ){
		float z1 =    z  * (z_size / z_div);
		float z2 = (1+z) * (z_size / z_div);
		QuadStrip *lef = new QuadStrip();
		QuadStrip *rig = new QuadStrip();
		for( y = -y_div; y <= y_div; y++ ){
			float y1 = y * (y_size / y_div);
			lef->add( new Vertex(-x_size,y1,z2) );
			lef->add( new Vertex(-x_size,y1,z1) );
			rig->add( new Vertex( x_size,y1,z1) );
			rig->add( new Vertex( x_size,y1,z2) );
		}
		lef->setNormal( -1.0f, 0.0f, 0.0f );
		rig->setNormal(  1.0f, 0.0f, 0.0f );
		lef->enable( Element::EL_USE_ELEMENT_NORMAL );
		rig->enable( Element::EL_USE_ELEMENT_NORMAL );
		add( lef );
		add( rig );
	}

	setupClipRadius();
}


};  //  namespace Models
};  //  namespace Teddy

