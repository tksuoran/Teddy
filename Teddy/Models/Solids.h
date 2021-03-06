
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


#ifndef TEDDY__MODELS__SOLIDS__H
#define TEDDY__MODELS__SOLIDS__H


#include "Teddy/Models/Model.h"


namespace Teddy  {
namespace Models {


class Cube                      : public Model { public: Cube                      ( double r ); };
class Cuboctahedron             : public Model { public: Cuboctahedron             ( double r ); };
class Dodecahedron              : public Model { public: Dodecahedron              ( double r ); };
class Icosahedron               : public Model { public: Icosahedron               ( double r ); };
class Octahedron                : public Model { public: Octahedron                ( double r ); };
class Tetrahedron               : public Model { public: Tetrahedron               ( double r ); };
class TruncatedCube             : public Model { public: TruncatedCube             ( double r ); };
class TruncatedCuboctahedron    : public Model { public: TruncatedCuboctahedron    ( double r ); };
class TruncatedOctahedron       : public Model { public: TruncatedOctahedron       ( double r ); };
class Rhomicuboctahedron        : public Model { public: Rhomicuboctahedron        ( double r ); };
class Rhombicosidodecahedron    : public Model { public: Rhombicosidodecahedron    ( double r ); };
class TruncatedDodecahedron     : public Model { public: TruncatedDodecahedron     ( double r ); };
class TruncatedIcosahedron      : public Model { public: TruncatedIcosahedron      ( double r ); };
class TruncatedIcosidodecahedron: public Model { public: TruncatedIcosidodecahedron( double r ); };
class TruncatedTetrahedron      : public Model { public: TruncatedTetrahedron      ( double r ); };


};  //  namespace Models
};  //  namespace Teddy;


#endif  //  TEDDY__MODELS__SOLIDS__H

