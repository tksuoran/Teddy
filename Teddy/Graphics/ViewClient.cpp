
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

	$Id: ViewClient.cpp,v 1.4 2002/01/11 14:34:59 tksuoran Exp $
*/


#include "Teddy/Graphics/View.h"
#include "Teddy/Graphics/ViewClient.h"


namespace Teddy    {
namespace Graphics {


void ViewClient::color( const float r, const float g, const float b, const float a ){
	view->color( r, g, b, a );
}


void ViewClient::color( const Color &c ){
	view->color( c );
}


void  ViewClient::vertex ( const float a, const float b ) const { view->vertex(a,b); }
void  ViewClient::vertex ( const Teddy::Maths::TVector <int>    &v ) const { view->vertex (v); }
void  ViewClient::vertex ( const Teddy::Maths::TVector <float>  &v ) const { view->vertex (v); }
void  ViewClient::vertex ( const Teddy::Maths::TVector <double> &v ) const { view->vertex (v); }
void  ViewClient::vertex ( const Teddy::Maths::TVector2<int>    &v ) const { view->vertex (v); }
void  ViewClient::vertex ( const Teddy::Maths::TVector2<float>  &v ) const { view->vertex (v); }
void  ViewClient::vertex ( const Teddy::Maths::TVector2<double> &v ) const { view->vertex (v); }
void  ViewClient::normal ( const Teddy::Maths::TVector <int>    &n ) const { view->normal (n); }
void  ViewClient::normal ( const Teddy::Maths::TVector <float>  &n ) const { view->normal (n); }
void  ViewClient::normal ( const Teddy::Maths::TVector <double> &n ) const { view->normal (n); }
void  ViewClient::normal ( const Teddy::Maths::TVector2<int>    &n ) const { view->normal (n); }
void  ViewClient::normal ( const Teddy::Maths::TVector2<float>  &n ) const { view->normal (n); }
void  ViewClient::normal ( const Teddy::Maths::TVector2<double> &n ) const { view->normal (n); }
void  ViewClient::texture( const Teddy::Maths::TVector <int>    &t ) const { view->texture(t); }
void  ViewClient::texture( const Teddy::Maths::TVector <float>  &t ) const { view->texture(t); }
void  ViewClient::texture( const Teddy::Maths::TVector <double> &t ) const { view->texture(t); }
void  ViewClient::texture( const Teddy::Maths::TVector2<int>    &t ) const { view->texture(t); }
void  ViewClient::texture( const Teddy::Maths::TVector2<float>  &t ) const { view->texture(t); }
void  ViewClient::texture( const Teddy::Maths::TVector2<double> &t ) const { view->texture(t); }


void ViewClient::beginPoints(){
	view->beginLines();
}


void ViewClient::beginLines(){
	view->beginLines();
}


void ViewClient::beginLineStrip(){
	view->beginLines();
}


void ViewClient::beginLineLoop(){
	view->beginLineLoop();
}


void ViewClient::beginTriangles(){
	view->beginTriangles();
}


void ViewClient::beginTriangleFan(){
	view->beginTriangleFan();
}


void ViewClient::beginTriangleStrip(){
	view->beginTriangleStrip();
}


void ViewClient::beginQuads(){
	view->beginQuads();
}


void ViewClient::beginQuadStrip(){
	view->beginQuadStrip();
}


void ViewClient::beginPolygon(){
	view->beginPolygon();
}


void ViewClient::end(){
	view->end();
}


void ViewClient::setView( View *view ){
	this->view = view;
}


View *ViewClient::getView() const {
	return this->view;
}


};  //  namespace Graphics
};  //  namespace Teddy

