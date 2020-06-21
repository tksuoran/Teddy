
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

	$Id: ViewClient.h,v 1.4 2002/01/11 14:34:59 tksuoran Exp $
*/


#ifndef TEDDY__GRAPHICS__VIEW_CLIENT__H
#define TEDDY__GRAPHICS__VIEW_CLIENT__H


#include "Teddy/Graphics/Color.h"
#include "Teddy/Maths/Vector.h"
#include "Teddy/Maths/Vector2.h"


namespace Teddy    {
namespace Graphics {


class View;


//!  Base class for View users
class ViewClient {
public:
	ViewClient( View *view ):view(view){}
	virtual ~ViewClient(){}

	void  vertex            ( const float a, const float b ) const;
    void  vertex            ( const Teddy::Maths::TVector <int>    &v ) const;
	void  vertex            ( const Teddy::Maths::TVector <float>  &v ) const;
	void  vertex            ( const Teddy::Maths::TVector <double> &v ) const;
	void  vertex            ( const Teddy::Maths::TVector2<int>    &v ) const;
	void  vertex            ( const Teddy::Maths::TVector2<float>  &v ) const;
	void  vertex            ( const Teddy::Maths::TVector2<double> &v ) const;
	void  normal            ( const Teddy::Maths::TVector <int>    &n ) const;
	void  normal            ( const Teddy::Maths::TVector <float>  &n ) const;
	void  normal            ( const Teddy::Maths::TVector <double> &n ) const;
	void  normal            ( const Teddy::Maths::TVector2<int>    &n ) const;
	void  normal            ( const Teddy::Maths::TVector2<float>  &n ) const;
	void  normal            ( const Teddy::Maths::TVector2<double> &n ) const;
	void  texture           ( const Teddy::Maths::TVector <int>    &t ) const;
	void  texture           ( const Teddy::Maths::TVector <float>  &t ) const;
	void  texture           ( const Teddy::Maths::TVector <double> &t ) const;
	void  texture           ( const Teddy::Maths::TVector2<int>    &t ) const;
	void  texture           ( const Teddy::Maths::TVector2<float>  &t ) const;
	void  texture           ( const Teddy::Maths::TVector2<double> &t ) const;
	void  color             ( const float r, const float g, const float b, const float a = 1 );
    void  color             ( const Color &c );

	void  beginPoints       ();
	void  beginLines        ();
	void  beginLineStrip    ();
	void  beginLineLoop     ();
	void  beginTriangles    ();
	void  beginTriangleStrip();
	void  beginTriangleFan  ();
	void  beginQuads        ();
	void  beginQuadStrip    ();
	void  beginPolygon      ();
	void  end               ();
	void  begin2d           ();
	void  end2d             ();
	void  setView           ( View *view );
	View *getView           () const;

protected:
	View *view;
};


};  //  namespace Graphics
};  //  namespace Teddy


#endif  //  TEDDY__GRAPHICS__VIEW_CLIENT__H

