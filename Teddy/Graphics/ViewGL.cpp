
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

	$Id: ViewGL.cpp,v 1.5 2002/02/16 12:41:39 tksuoran Exp $
*/


#include "Teddy/TeddyConfig.h"
#include "Teddy/Graphics/Color.h"
#include "Teddy/Graphics/Device.h"
#include "Teddy/Graphics/Texture.h"
#include "Teddy/Graphics/View.h"
#include "Teddy/SysSupport/Messages.h"
using namespace Teddy::Maths;
using namespace Teddy::SysSupport;


namespace Teddy    {
namespace Graphics {


void View::beginPoints(){
	if( current_element != -1 ){
		msg( M_GL, "current element" );
	}
	glBegin( GL_POINTS );
	current_element = GL_POINTS;
}


void View::beginLines(){
	if( current_element != -1 ){
		msg( M_GL, "current element" );
	}
	glBegin( GL_LINES );
	current_element = GL_LINES;
}


void View::beginLineStrip(){
	if( current_element != -1 ){
		msg( M_GL, "current element" );
	}
	glBegin( GL_LINE_STRIP );
	current_element = GL_LINE_STRIP;
}


void View::beginLineLoop(){
	if( current_element != -1 ){
		msg( M_GL, "current element" );
	}
	glBegin( GL_LINE_LOOP );
	current_element = GL_LINE_LOOP;
}

void View::beginTriangles(){
	if( current_element != -1 ){
		msg( M_GL, "current element" );
	}
	glBegin( GL_TRIANGLES );
	current_element = GL_TRIANGLES;
}


void View::beginTriangleStrip(){
	if( current_element != -1 ){
		msg( M_GL, "current element" );
	}
	glBegin( GL_TRIANGLE_STRIP );
	current_element = GL_TRIANGLE_STRIP;
}


void View::beginTriangleFan(){
	if( current_element != -1 ){
		msg( M_GL, "current element" );
	}
	glBegin( GL_TRIANGLE_FAN );
	current_element = GL_TRIANGLE_FAN;
}


void View::beginQuads(){
	if( current_element != -1 ){
		msg( M_GL, "current element" );
	}
	glBegin( GL_QUADS );
	current_element = GL_QUADS;
}


void View::beginQuadStrip(){
	if( current_element != -1 ){
		msg( M_GL, "current element" );
	}
	glBegin( GL_QUAD_STRIP );
	current_element = GL_QUAD_STRIP;
}


void View::beginPolygon(){
	if( current_element != -1 ){
		msg( M_GL, "current element" );
	}
	glBegin( GL_POLYGON );
	current_element = GL_POLYGON;
}


void View::end(){
	if( current_element == -1 ){
		msg( M_GL, "current element" );
	}
	glEnd();
	current_element = -1;
}


void View::setProjectionMatrix(){
	if( current_matrix_mode != GL_PROJECTION ){
		glMatrixMode( GL_PROJECTION );
		current_matrix_mode = GL_PROJECTION;
	}
    glLoadIdentity();
	//glLoadMatrixf( m );
	//glScalef(1.0f, 1.0f, -1.0f);
}


void View::setProjectionMatrix( const Matrix &m ){
	if( current_matrix_mode != GL_PROJECTION ){
		glMatrixMode( GL_PROJECTION );
		current_matrix_mode = GL_PROJECTION;
	}
	glLoadMatrixf( m );
	//glScalef(1.0f, 1.0f, -1.0f);
}


void View::setModelViewMatrix(){
	if( current_matrix_mode != GL_MODELVIEW ){
		glMatrixMode( GL_MODELVIEW );
		current_matrix_mode = GL_MODELVIEW;
	}
    glLoadIdentity();
	//glLoadMatrixf( m );
}


void View::setModelViewMatrix( const Matrix &m ){
	if( current_matrix_mode != GL_MODELVIEW ){
		glMatrixMode( GL_MODELVIEW );
		current_matrix_mode = GL_MODELVIEW;
	}
	glLoadMatrixf( m );
}


void View::setTextureMatrix( const Matrix &m ){
	if( current_matrix_mode != GL_TEXTURE ){
		glMatrixMode( GL_TEXTURE );
		current_matrix_mode = GL_TEXTURE;
	}
	glLoadMatrixf( m );
}


void View::color( float r, float g, float b, float a ) const {
	glColor4f( r, g, b, a );
}


void View::color( const Color &c ) const {
	glColor4fv( c.rgba );
}


void View::vertex( const float x, const float y ) const {
	glVertex2f( x, y );
}


void View::vertex( const TVector<int> &v ) const {
#	if defined( USE_TINY_GL )
	glVertex3f( float(v[0]), float(v[1]), float(v[2]) );
#	else
	glVertex3iv( v );
#	endif
}


void View::vertex( const TVector<float> &v ) const {
#	if defined( USE_TINY_GL )
	glVertex3f( float(v[0]), float(v[1]), float(v[2]) );
#	else
	glVertex3fv( v );
#	endif
}


void View::vertex( const TVector<double> &v ) const {
#	if defined( USE_TINY_GL )
	glVertex3f( float(v[0]), float(v[1]), float(v[2]) );
#	else
	glVertex3dv( v );
#	endif
}


void View::vertex( const TVector2<int> &v ) const {
#	if defined( USE_TINY_GL )
	glVertex2f( float(v[0]), float(v[1]) );
#	else
	glVertex2i( v[0], v[1] );
	//glVertex2iv( v );
#	endif
}


void View::vertex( const TVector2<float> &v ) const {
	glVertex2f( v[0], v[1] );
	//glVertex2fv( v );
}


void View::vertex( const TVector2<double> &v ) const {
#	if defined( USE_TINY_GL )
	glVertex2f( float(v[0]), float(v[1]) );
#	else
	glVertex2d( v[0], v[1] );
	//glVertex2dv( v );
#	endif
}


void View::normal( const TVector<int> &n ) const {
#	if defined( USE_TINY_GL )
	glNormal3f( float(n[0]), float(n[1]), float(n[2]) );
#	else
	glNormal3iv( n );
#	endif
}


void View::normal( const TVector<float> &n ) const {
#	if defined( USE_TINY_GL )
	glNormal3f( float(n[0]), float(n[1]), float(n[2]) );
#	else
	glNormal3fv( n );
#	endif
}


void View::normal( const TVector<double> &n ) const {
#	if defined( USE_TINY_GL )
	glNormal3f( float(n[0]), float(n[1]), float(n[2]) );
#	else
	glNormal3dv( n );
#	endif
}


void View::normal( const TVector2<int> &n ) const {
#	if defined( USE_TINY_GL )
	glNormal3f( float(n[0]), float(n[1]), float(n[2]) );
#	else
    //	glNormal2iv( n );
    glNormal3i( n[0], n[1], 1 );
#	endif
}


void View::normal( const TVector2<float> &n ) const {
    //glNormal2fv( n );
    glNormal3f( n[0], n[1], 1 );
}


void View::normal( const TVector2<double> &n ) const {
#	if defined( USE_TINY_GL )
	glNormal3f( float(n[0]), float(n[1]), 1.0f );
#	else
    glNormal3d( n[0], n[1], 1 );
#	endif
    //glNormal2dv( n );
}


void View::texture( const TVector<int> &t ) const {
#	if defined( USE_TINY_GL )
	glTexCoord2f( float(t[0]), float(t[1]) );
#	else
	glTexCoord3i( t[0], t[1], t[2] );
	//glTexCoord3iv( t );
#	endif
}


void View::texture( const TVector<float> &t ) const {
#	if defined( USE_TINY_GL )
	glTexCoord2f( float(t[0]), float(t[1]) );
#	else
	glTexCoord3f( t[0], t[1], t[2] );
	//glTexCoord3fv( t );
#	endif
}


void View::texture( const TVector<double> &t ) const {
#	if defined( USE_TINY_GL )
	glTexCoord2f( float(t[0]), float(t[1]) );
#	else
	glTexCoord3d( t[0], t[1], t[2] );
	//glTexCoord3dv( t );
#	endif
}


void View::texture( const TVector2<int> &t ) const {
#	if defined( USE_TINY_GL )
	glTexCoord2f( float(t[0]), float(t[1]) );
#	else
	glTexCoord2i( t[0], t[1] );
	//glTexCoord2iv( t );
#	endif
}


void View::texture( const TVector2<float> &t ) const {
#	if defined( USE_TINY_GL )
	glTexCoord2f( float(t[0]), float(t[1]) );
#	else
	glTexCoord2f( t[0], t[1] );
	//glTexCoord3f( t[0], t[1], 0.0f );
	//glTexCoord2fv( t );
#endif
}


void View::texture( const TVector2<double> &t ) const {
#	if defined( USE_TINY_GL )
	glTexCoord2f( float(t[0]), float(t[1]) );
#	else
	glTexCoord2d( t[0], t[1] );
	//glTexCoord2dv( t );
#	endif
}



const char *View::getExtensions(){
#	if defined( USE_OPEN_GL )
//#error poo
		return (const char *)glGetString( GL_EXTENSIONS );
#	else
		return "";
#	endif
}


const char *View::getVendor(){
#	if defined( USE_OPEN_GL )
		return (const char *)glGetString( GL_VENDOR );
#	else
		return "Inbuilt Software";
#	endif
}


const char *View::getRenderer(){
#	if defined( USE_OPEN_GL )
	return (const char *)glGetString( GL_RENDERER );
#	endif
#	if defined( USE_TINY_GL )
	return "TinyGL";
#	endif
    return "";
}


const char *View::getVersion(){
#	if defined( USE_OPEN_GL )
	return (const char *)glGetString( GL_VERSION );
#	endif
#	if defined( USE_TINY_GL )
	return "1.0";
#	endif
    return "";
}


int View::getMaxTextureSize(){
	GLint max_texture_size = 0;
	glGetIntegerv( GL_MAX_TEXTURE_SIZE, &max_texture_size );
	return max_texture_size;
}


int View::getMaxLights(){
	GLint max_lights = 0;
	glGetIntegerv( GL_MAX_LIGHTS, &max_lights );
	return max_lights;
}


/*
void View::getMaxViewportDims( int &width, int &height ){
	GLint dims[2] = { 0, 0 };
	glGetIntegerv( GL_MAX_VIEWPORT_DIMS, dims );
	width  = dims[0];
	height = dims[1];
}*/


void View::setTexture( Texture *t ){
	if( current_texture != t ){
		current_texture = t;
		t->apply();
	}
}


};  //  namespace Graphics
};  //  namespace Teddy

