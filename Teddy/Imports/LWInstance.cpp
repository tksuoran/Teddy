
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

	$Id: LWInstance.cpp,v 1.1 2002/02/16 12:41:39 tksuoran Exp $
*/


#include "Teddy/TeddyConfig.h"
#if defined( TEDDY_INCLUDE_LW_SCENE )


#include "Teddy/Imports/LWInstance.h"
#include "Teddy/Imports/LWModel.h"
#include "Teddy/Imports/LWMotion.h"
#include "Teddy/Imports/LWChannelEnvelope.h"
#include "Teddy/Maths/Quaternion.h"
#include "Teddy/SysSupport/Messages.h"
using namespace Teddy::SysSupport;
using namespace Teddy::Maths;


namespace Teddy   {
namespace Imports {


LWInstance::LWInstance(){
	this->motion           = NULL;
	this->next_bone        = 0;
	this->parent_object    = NULL;
	this->parent_object_id = 0xffffffff;
	this->last_po_time     = -666.666f;
	this->last_ro_time     = -666.666f;
	this->last_pi_time     = -666.666f;
	this->last_position    = Vector(0,0,0);
    this->last_rotation    = Matrix::IDENTITY;
	this->last_pivot       = Vector(0,0,0);
	this->pivot_position   = Vector(0,0,0);

}


void LWInstance::setParentObject( LWInstance *parent ){
	this->parent_object = parent;
}


void LWInstance::add( LWBone *bone ){
	bones.insert( make_pair(next_bone,bone) );
	next_bone++;
}


LWBone *LWInstance::getBone( int bone_num ){
	LWBone                  *bone = NULL;
	int_to_LWBone::iterator  b_it = bones.find( bone_num );
	if( b_it != bones.end() ){
		bone = (*b_it).second;
	}
	return bone;
}


void LWInstance::setModel( Model *m ){
	this->model = m;
}


Model *LWInstance::getModel(){
	return this->model;
}


void LWInstance::setModelName( const std::string &model_name ){
	this->model_name = model_name;
}


std::string &LWInstance::getModelName(){
	return this->model_name;
}


LWMotion *LWInstance::getMotion(){
	return this->motion;
}


void LWInstance::setMotion( LWMotion *motion ){
	this->motion = motion;
}

void LWInstance::setVisibility( int visibility ){
	this->visibility = visibility;
}


void LWInstance::setColor( int color ){
	this->color = color;
}


void LWInstance::setParentObjectId( unsigned long parent_object_id ){
	this->parent_object_id = parent_object_id;
}


unsigned long LWInstance::getParentObjectId(){
	return parent_object_id;
}


void LWInstance::setTime( float time ){
	Vector position = evalPosition( time );
	
//	position[0] = -position[0];
	
	model->setPosition( position );
	model->getAttitude() = evalRotation( time );
}


void LWInstance::setPivotPosition( Vector pivot_position ){
	this->pivot_position = pivot_position;
}


Vector &LWInstance::evalPosition( float time ){
	if( time == last_po_time ){
		return last_position;
	}
	last_po_time = time;

	//  Evaluate
	LWChannelEnvelope *x_env = motion->getChannel( LW_CHANNEL_X );
	LWChannelEnvelope *y_env = motion->getChannel( LW_CHANNEL_Y );
	LWChannelEnvelope *z_env = motion->getChannel( LW_CHANNEL_Z );

	double x = ( x_env != NULL ) ? x = x_env->eval( time ) : 0.0;
	double y = ( y_env != NULL ) ? y = y_env->eval( time ) : 0.0;
	double z = ( z_env != NULL ) ? z = z_env->eval( time ) : 0.0;

	last_position = Vector( x, y, z );

	if( parent_object != NULL ){
		last_position  = parent_object->evalRotation( time ) * last_position;
		last_position += parent_object->evalPosition( time );
	}
	last_position += evalPivot( time );

	return last_position;
}


Vector &LWInstance::evalPivot( float time ){
	if( time == last_pi_time ){
		return last_pivot;
	}
	last_pi_time = time;

	last_pivot = evalRotation( time ) * -pivot_position;
	return last_pivot;
}


Matrix &LWInstance::evalRotation( float time ){
	if( time == last_ro_time ){
		return last_rotation;
	}
	last_ro_time = time;

	//  Evaluate
	LWChannelEnvelope *h_env = motion->getChannel( LW_CHANNEL_H );
	LWChannelEnvelope *p_env = motion->getChannel( LW_CHANNEL_P );
	LWChannelEnvelope *b_env = motion->getChannel( LW_CHANNEL_B );

    double h = ( h_env != NULL ) ? h = h_env->eval( time ) : 0.0;
    double p = ( p_env != NULL ) ? p = p_env->eval( time ) : 0.0;
    double b = ( b_env != NULL ) ? b = b_env->eval( time ) : 0.0;

#if 1
    Quaternion 
    q  = Quaternion( Vector(0.0,0.0,1.0),  -b );
    q *= Quaternion( Vector(1.0,0.0,0.0),  -p );
	q *= Quaternion( Vector(0.0,1.0,0.0),  -h );
    last_rotation = q;
#else
    last_rotation.rotateYMatrix(  h );
    last_rotation.rotateX      (  p );
    last_rotation.rotateZ      (  b );
#endif

	if( parent_object != NULL ){
		last_rotation = parent_object->evalRotation( time ) * last_rotation;
	}

	return last_rotation;
}


};  //  namespace Imports
};  //  namespace Teddy


#endif  //  TEDDY_INCLUDE_LW_SCENE
