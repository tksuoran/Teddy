
/*
	TEDDY - General graphics application library
	Copyright (C) 1999, 2000, 2001	Timo Suoranta
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

	$Id: LSystem.cpp,v 1.5 2002/02/16 12:47:30 tksuoran Exp $
*/


#include "LSystem.h"

#include "Teddy/Models/Vertex.h"
#include "Teddy/Models/Cylinder.h"
#include "Teddy/Models/Face.h"
#include "Teddy/Models/Line.h"
#include "Teddy/Models/LineGeometry.h"
#include "Teddy/SysSupport/StdString.h"
#include "Teddy/SysSupport/Messages.h"
#include "Teddy/SysSupport/StdString.h"
#include "Teddy/SysSupport/StdIO.h"
#include "Teddy/SysSupport/StdAlgo.h"
using namespace Teddy::Models;


#define SD 4


LSystem::LSystem()
:
Model( "LSystem" )
{
	cur_data     = "";
	current_face = NULL;

	//setGeometry( new LineGeometry() );

	//  Default rules expand each char to itself, a -> a and b -> b etc.
	for( int i=0; i<256; i++ ){
		rules[i] += (unsigned char)(i);
	}
	polygons = new Model( "lsystem polygons" );
	polygons->setGeometry( new Geometry() );
	add( polygons );
}


/*virtual*/ LSystem::~LSystem(){
//	delete[] rules;
}


void LSystem::setAxiom( const char *axiom ){
	this->cur_data = axiom;
}


void LSystem::setRule( unsigned char c, const char *rule ){
	rules[c] = rule;
}


void LSystem::setAngle( float angle ){
	current_state.angle = angle;
}


void LSystem::setLength( float length ){
	current_state.length = length;
}


void LSystem::setThickness( float thickness ){
	current_state.thickness = thickness;
}


void LSystem::polyBegin(){
	if( current_face == NULL ){
		current_face = new Face();
	}
}


void LSystem::polyEnd(){
	if( current_face != NULL ){
		polygons->add( current_face );
		current_face = NULL;
	}
}


void LSystem::heading( float direction ){
	if( use_param ){
		current_state.heading( direction*param );
	}else{
		current_state.heading( direction*current_state.angle );
	}
}


void LSystem::pitch( float direction ){
	if( use_param ){
		current_state.pitch( direction*param );
	}else{
		current_state.pitch( direction*current_state.angle );
	}
}


void LSystem::roll( float direction ){
	if( use_param ){
		current_state.roll( direction*param );
	}else{
		current_state.roll( direction*current_state.angle );
	}
}


void LSystem::length( float val ){
	if( use_param ) val = param;

	current_state.length *= val;
}


void LSystem::angle( float val ){
	if( use_param ) val = param;

	current_state.angle *= val;
}


void LSystem::thickness( float val ){
	if( use_param ) val = param;

	current_state.thickness *= val;
}


void LSystem::randomDir( float val ){
	//  FIX not yet implemented
}


void LSystem::rollHoriz( float val ){
	//  FIX not yet implemented
}


void LSystem::gravity( float val ){
	//  FIX not yet implemented
}


void LSystem::move( float length, bool draw, bool vertex ){
	if( use_param ){
		length = param;
	}else{
		length *= current_state.length;
	}


	Vector delta = current_state.direction * length;

	if( draw == true ){
		Vertex *start = new Vertex( current_state.position ); 
		Vertex *end   = new Vertex( current_state.position + delta );
		//		Line   *line  = new Line( start, end );
		//		this->insert( line );

		//this->insert( start );
		//this->insert( end   );

		//  Adjust clipping if needed
        /*
		float l;
		l = start->getVertex().magnitude(); if( l>getClipRadius() ) setClipRadius( l );
		l = end  ->getVertex().magnitude(); if( l>getClipRadius() ) setClipRadius( l );
*/
		Vector p1 = start->getVertex();
		Vector p2 = end  ->getVertex();
//		p1 *= 100.0;
//      p2 *= 100.0;

		Vector    dir = p2 - p1;
		double    len = dir.magnitude();
		double    rad = current_state.thickness;
		printf( "." );
        fflush( stdout );
		Cylinder *cyl = new Cylinder( "Cylinder shape", rad, len, 3 );
		Matrix rot;
        Matrix tra;
        rot.direction      ( dir );
		tra.translateMatrix( p1  );
        Matrix m = tra * rot;
		cyl->transformVertices( m );
        cyl->setClipRadius( sqrt(len*len+rad*rad) );
		add( cyl );
	}

	current_state.position += delta;

	if( vertex == true && current_face != NULL ){
		Vertex *poly_vertex = new Vertex( current_state.position );
		current_face->add( poly_vertex );
	}
}


void LSystem::push(){
	state_stack.push( current_state );
}


void LSystem::pop(){
	current_state = state_stack.top();
	state_stack.pop();
}

