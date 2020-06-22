
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


#include "Teddy/Materials/Material.h"
#include "Teddy/Models/Model.h"
#include "Teddy/PhysicalComponents/Projection.h"
#include "Teddy/Scenes/Camera.h"
#include "Teddy/SysSupport/StdMaths.h"
#include "Teddy/SysSupport/StdSDL.h"
#include "Teddy/SysSupport/StdIO.h"
using namespace Teddy::Graphics;
using namespace Teddy::Materials;
using namespace Teddy::Maths;
using namespace Teddy::Scenes;


namespace Teddy  {
namespace Models {


Quaternion &Model::getAttitude(){
	return attitude;
}

/*virtual*/ void Model::setPosition( const double x, const double y, const double z ){
	position.v[0] = x;
	position.v[1] = y;
	position.v[2] = z;
}


//!  Get position relative to parent.
TVector<double>  Model::getPosition() const {
	return position;
}


//!  Set position relative to parent
/*virtual*/ void Model::setPosition( const TVector<double> &v ){
	position = v;
}


void Model::translate( const TVector<double> &v ){
	position += v;
}


/*!
	\brief Return distance to another Model
	\param obj The other Model to which the distance is calculated
	\note  Distance between object centers is calculated. The actual
	distance is usually a little less. You might want to substract
	clip radius of both Models in some cases from the given
	distance.
*/
double Model::distanceTo( const Model &other ) const {
	return position.distance( other.position );
}


/*!
	\brief Return distance to other position
	\param pos Position in world cooridates to which distance is calculated
	\note  Distance is calculated from object center to the given point.
*/
double Model::distanceTo( const TVector<double> &pos ) const {
	return position.distance( pos );
}


/*!
	\brief Return vector to other Model
	\param obj The other Model to which the delta vector is returned
*/
TVector<double> Model::vectorTo( const Model &other ) const {
	return other.position - position;
}


/*!
	\brief Copy orientation (attitude) from other Model
	\param other The source Model of the orientation
*/
void Model::copyAttitude( const Model &other ){
	attitude = other.attitude;
}


void Model::transform( const Matrix &m ){
	attitude *= m;
}


/*!
	\brief Concatenate roll
	\param radians Rotation angle in radians

	Model is rotated around roll axis (Z) by angle degrees.
*/
void Model::roll( const double radians ){
	attitude.rotate( attitude.getViewAxis(), radians );
}


/*!
	\brief Concatenate pitch
	\param radians Rotation angle in radians

	Model is rotated around pitch axis (X) by angle degrees.
*/
void Model::pitch( const double radians ){
	attitude.rotate( attitude.getRightAxis(), radians );
}


/*!
	\brief Concatenate heading
	\param radians Rotation angle in radians

	Model is rotated around heading axis (Y) by angle degrees.
*/
void Model::heading( const double radians ){
	attitude.rotate( attitude.getUpAxis(), radians );
}


/*!
	\brief Move Model foward
	\param len Amount of translation

	Model is translated along its view axis (Z)
	by len units.
*/
void Model::foward( const double len ){
	translate( attitude.getViewAxis() * len );
}


/*!
	\brief Translate Model by (x,y,z)
	\param x Translation in world X axis
	\param y Translation in world Y axis
	\param z Translation in world Z axis

	Model is translated in world coordinates by (x, y, z).
*/
/*void Model::translate( const double x, const double y, const double z ){
	translate( Vector(x,y,z) );
}*/


};	//	namespace Models
};  //  namespace Teddy

