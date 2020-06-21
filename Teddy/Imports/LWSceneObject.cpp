
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

	$Id: LWSceneObject.cpp,v 1.1 2002/02/16 12:41:39 tksuoran Exp $
*/


#include "Teddy/TeddyConfig.h"
#if defined( TEDDY_INCLUDE_LW_SCENE )


#include "Teddy/Imports/LWBone.h"
#include "Teddy/Imports/LWCamera.h"
#include "Teddy/Imports/LWChannelEnvelope.h"
#include "Teddy/Imports/LWChannelKey.h"
#include "Teddy/Imports/LWInstance.h"
#include "Teddy/Imports/LWLight.h"
#include "Teddy/Imports/LWModel.h"
#include "Teddy/Imports/LWMotion.h"
#include "Teddy/Imports/LWSceneFile.h"
#include "Teddy/Imports/LWSceneParser.h"
#include "Teddy/SysSupport/Messages.h"
using namespace Teddy::SysSupport;


namespace Teddy   {
namespace Imports {


/*
	LoadObject  <object path + filename>  (Alternative: AddNullObject)

	example:      LoadObject Objects/Tutorial/LightBeam.lwo

	The LoadObject function is the first listing in all
	Object Segments. It provides LightWave with the path
	and filename for the object to be loaded. The object's
	path is generated by adding the current content directory
	to  the beginning of the given path and filename.  

	In this example if the current content directory were
	<c:/NewTek>, LightWave would attempt to load the file
	<c:/NewTek/Objects/Tutorial/LightBeam.lwo>.

	It is possible to have duplicate objects in a scene
	file. When the LoadObject function is called, and
	the object name already exists, a numbered suffix is 
	added to the duplicate object's name. This number is
	enclosed in parenthesis and follows the object name.  

	For example:  LightBeam.lwo (2) is the second instance
	of the LightBeam.lwo object in the current scene file.

	The added suffix is not saved in the scene file, and
	is used only as a user reference.

	User Interface:
	
	The LoadObject/AddNullObject listing is produced from
	the following functions on the Objects Panel; LoadObject,
	Load from Scene, and Add Null Object.

	The LoadObject/AddNullObject function is listed with all objects.
*/
void LWSceneParser::LoadObjectLayer(){
	int          layer      = file->read_int   ();
	std::string  model_name = file->read_string();
	dmsg( M_LWS, "LoadObjectLayer %d %s", layer, model_name.c_str() );

	current_object = new LWInstance();
	current_object->setModelName( model_name );
    dmsg( M_LWS, "objects.insert( make_pair(%d,%s) ) ...", next_object, model_name.c_str() );
    objects.insert( make_pair(next_object,current_object) );
    dmsg( M_LWS, "objects.insert( make_pair(%d,%s) ) done", next_object, model_name.c_str() );
	next_object++;
}


/*
	Alternative:  AddNullObject NullObject

	Alternative example:      AddNullObject NullObject

	The AddNullObject function will create a null object
	named "NullObject" in the current scene. NullObjects
	are treated as a normal object in the scene file.
 
	User Interface:
	
	The LoadObject/AddNullObject listing is produced from the 
	following functions on the Objects Panel; LoadObject,
	Load from Scene, and Add Null Object.

	The LoadObject/AddNullObject function is listed with all objects.
*/
void LWSceneParser::AddNullObject(){
	char *null_object_name = file->read_string();
	current_object = new LWInstance();
	objects.insert( make_pair(next_object,current_object) );
	next_object++;
}


void LWSceneParser::LoadObject(){}


/*
	ShowObject nvisibility ncolor

	Determines how the object is displayed in the interface.
	The visibility codes are

	0 - hidden
	1 - bounding box
	2 - vertices only
	3 - wireframe
	4 - front face wireframe
	5 - shaded solid
	6 - textured shaded solid

	The color used to draw bounding boxes, vertices and wireframes
	can be one of the following.

	0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 

	The default visibility and color are stored in the config file.
	If they haven't been altered by the user, they are textured
	shaded solid (6) and cyan (3) in LightWave 6.5.
*/
void LWSceneParser::ShowObject(){
	current_object->setVisibility( file->read_int() );
	current_object->setColor     ( file->read_int() );
}


/*
	ObjDissolve  <percentage> � (envelope)

	example:     ObjDissolve 0.500000

	The ObjDissolve function determines the object's
	dissolve level during the rendering process. The
	example would produce an object that is 50% dissolved 
	throughout the animation. The value is listed as a
	percentage out to six decimal places. If the value is
	left at the default of 0% dissolved, the function does
	not provide a listing in the scene file. The value of
	this function can be changed over time with an envelope.
	If an envelope is selected, the functions value is
	replaced with an envelope identifier. For more information
	on envelopes, see the Envelopes Section 1.4.

	User Interface:

	The ObjDissolve function is set from the Objects Panel.
*/
void LWSceneParser::ObjectDissolve(){
	double object_dissolve = file->read_double();
}


void LWSceneParser::SubdivisionOrder(){
	int subdivision_order = file->read_int();
}


void LWSceneParser::SubPatchLevel(){
	int a = file->read_int();
	int b = file->read_int();
}


/*
	ShadowOptions <bit-field value>

	example:     ShadowOptions 7

	The ShadowOptions function provides the shadowing
	characteristics for the current object.

	The bit-field value is produced by calculating the
	decimal value of a 3 position bit-field whose bits
	represent logical on/off switches that are number
	left to right from 0 to 2. The least-significant bit
	for this field is the rightmost bit. Each shadow option
	has a corresponding bit in the bit-field. When a
	shadow option is turned on, its bit (or switch) 
	is turned on.

	<bit position>:
		0 - Self Shadow
		1 - Cast Shadow
		2 - Receive Shadow 

	The ShadowOptions function produces a listing for all objects.

	User Interface:

	The shadow options function is set from 
	the bottom of the Objects Panel.
*/
void LWSceneParser::ShadowOptions(){
	int shadow_options = file->read_int();
}


/*
	DistanceDissolve <flag>

	example:     DistanceDissolve 1

	The DistanceDissolve flag turns the distance dissolve
	function on and off. This function produces a
	DistanceDissolve listing with a value of 1 and 
	adds the MaxDissolveDistance listing (see below)
	when turned on. When turned off, this function does
	not provide a listing in the scene file.

	<flag>:
		0 - Off (No Listing)
		1 - On  (Function listing plus additional MaxDissolveDistance listing)
*/
void LWSceneParser::DistanceDissolve(){
	int distance_dissolve = file->read_int();
}


/*
	Additional:     MaxDissolveDistance <distance>

	example:     MaxDissolveDistance 25.000000

	The MaxDissolveDistance function provides the distance
	from the camera that the object will be %100 dissolved.
	In the example shown, the object will be completely
	dissolved at 25 meters.

	User Interface:
	
	The DistanceDissolve functions are set from the 
	Objects Panel.
*/
void LWSceneParser::MaxDissolveDistance(){
	double max_distance_dissolve = file->read_double();
}


/*
	PolygonSize <percentage> � (envelope)

	example:     PolygonSize 0.350000

	The PolygonSize function provides a value that adjusts
	the polygon size of all polygons in the current object.
	The example would produce an object with all polygons
	35% of their original size. If the value is left at the
	default 100%, this function does not provide a listing in 
	the scene file. The value of this function can be changed
	over time with an envelope. If an envelope is selected,
	the functions value is replaced with an envelope identifier.
	For more information on envelopes, see the Envelopes
	Section 1.4. 

	User Interface:
	
	The PolygonSize function is set from the Objects Panel.
*/
void LWSceneParser::PolygonSize(){
	double polygon_size = file->read_double();
}


/*
	Particle/LineSize <value>

	example:  Particle/LineSize 1

	The Particle/LineSize function determines the size
	of a one and two point polygons when rendered.

	If the value is left at the default of Automatic, no
	function listing is produced in the scene file.

	<value>:
		0 - Automatic (No function listing)
		1-  Small
		2 - Medium
		3 - Large

	User Interface:

	The Particle/LineSize function is set from the 
	Particle/Line Size pop-up panel on the Objects Panel.
*/
void LWSceneParser::ParticleSize(){
	double size = file->read_double();
}
void LWSceneParser::LineSize(){
	double size = file->read_double();
}


void LWSceneParser::UnseenByRays(){
	int unseen_by_rays = file->read_int();
}


void LWSceneParser::UnseenByCamera(){
	int unseen_by_camera = file->read_int();
}


/*
	UnaffectedByFog <flag>

	example:  UnaffectedByFog 1

	The UnaffectedByFog flag activates the Unaffected by
	Fog function that will allow the current object to
	render normally when fog is turned on. This function
	produces a UnaffectedByFog listing with a value of 1
	when turned on. When turned off, this function does
	not produce a listing in the scene file.

	<flag>:
		0 - Off (No function listing)
		1 - On

	User Interface:
	
	The UnaffectedByFog function is set from the Objects Panel.
*/
void LWSceneParser::UnaffectedByFog(){
	int unaffected_by_fog = file->read_int();
}


void LWSceneParser::AffectedByFog(){
	int affected_by_fog = file->read_int();
}


void LWSceneParser::ExcludeLight(){
	int exclude_light = file->read_int();
}


/*
	ObjPolygonEdges <flag>

	example:     ObjPolygonEdges 1

	The ObjPolygonEdges flag activates the Polygon Edges
	function that renders all polygons with a visible
	outline. This function produces a ObjPolygonEdges
	listing with a value of 1 and adds an ObjEdgeColor 
	listing (see below) when turned on. When turned off,
	this function does not produce a listing in the scene file.

	<flag>:
		0 - Off (No function listing)
		1 - On  (Function listing plus additional listing)
*/
void LWSceneParser::ObjPolygonEdges(){
	int obj_polygon_edges = file->read_int();
}


/*
	Additional: ObjEdgeColor <red value> <green value> <blue value>

	example:     ObjEdgeColor 0 0 255

	The ObjEgdeColor function provides the RGB color
	values for the object's polygon edges.

	<color value range>:
		red value   - 0 - 255
		green value - 0 - 255
		blue value  - 0 - 255

	User Interface:
	
	The ObjPolygonEdges functions are set from the 
	Objects Panel.
*/
void LWSceneParser::ObjEdgeColor(){
	double red   = file->read_double();
	double green = file->read_double();
	double blue  = file->read_double();
}


void LWSceneParser::PolygonEdgeFlags(){
	int polygon_edge_flags = file->read_int();
}


void LWSceneParser::PolygonEdgeThickness(){
	double polygon_edge_thickness = file->read_double();
}


void LWSceneParser::PolygonEdgesZScale(){
	double polygon_edges_z_scale = file->read_double();
}


void LWSceneParser::EdgeNominalDistance(){
	double edge_nominal_distance = file->read_double();
}


//  for lights and cameras too


/*
	PivotPoint <x position> <y position> <z position>

	example:  PivotPoint 0 16.9 -11.6

	The PivotPoint function provides the x, y, and z
	positions for the pivot point of the object. This
	determines the center of rotation for the current
	object. The position values are given as a distance
	(meters) of offset from the original object center.

	User Interface:
	
	The PivotPoint values are set from the Move Pivot Point 
	mouse function in Layout.
*/
void LWSceneParser::PivotPosition(){
	double x = file->read_double();
	double y = file->read_double();
	double z = file->read_double();

	//z = -z;

	if( current_object != NULL ){
		current_object->setPivotPosition( Vector(x,y,z) );
	}else{
		emsg( M_LWS, "No current object for pivot point" );
	}
}


/*
	When a scene file needs to refer to specific items to establish item
	relationships (parenting, for example), it uses item numbers. Items
	are numbered in the order in which they appear in the file, starting
	with 0.

	Item numbers can be written in one of two ways, depending on which
	keyword they're used with. In general, if the type of the item
	(object, bone, light, camera) can be determined from the keyword
	alone, the item number will simply be the ordinal, written as a
	decimal integer. When the keyword can be used with items of more
	than one type, the item number is an unsigned integer written as
	an 8-digit hexadecimal string, the format produced by the C-language
	"%8X" print format specifier, and the high bits identify the item type.

	The first hex digit (most significant 4 bits) of the hex item number
	string identifies the item type.

	1 - Object
	2 - Light
	3 - Camera
	4 - Bone

	The other digits make up the item number, except in the case of
	bones. For bones, the next 3 digits (bits 16-27) are the bone
	number and the last 4 digits (bits 0-15) are the object number
	for the object the bone belongs to. Some examples:

	10000000 - the first object
	20000000 - the first light
	4024000A - the 37th bone (24 hex) in the 11th object (0A hex)
*/
void LWSceneParser::ParentItem(){
	unsigned long  all_bits = file->read_hex_int();

	if( current_object != NULL ){
		current_object->setParentObjectId( all_bits );
	}else{
		emsg( M_LWS, "Current object for ParentItem not found" );
	}
}


/*
	ObjectMotion
	NumChannels nchannels
	Channel nindex
	{ Envelope ... 

	The ObjectMotion keyword signals the start of the motion
	information for the object. Motions are stored in envelopes,
	one for each motion channel. There are 9 standard channels,
	numbered from 0 to 8.

	0, 1, 2 - (x, y, z) position
	3, 4, 5 - (heading, pitch, bank) rotation
	6, 7, 8 - (sx, sy, sz) scale factors along each axis

	The values of all of these are relative to the object's parent,
	if it has one.
*/
void LWSceneParser::ObjectMotion(){
	current_motion = new LWMotion();
	current_object->setMotion( current_motion );
}
void LWSceneParser::NumChannels(){
	num_channels = file->read_int();
}
void LWSceneParser::Channel(){
	int channel_id = file->read_int();
	current_channel_envelope = new LWChannelEnvelope( channel_id );
	current_motion->insert( current_channel_envelope );
	file->read_begin_scope();
}
void LWSceneParser::Envelope(){
	num_channel_keys = file->read_int();
}
void LWSceneParser::Key(){
	double value    = file->read_double();
	double time     = file->read_double();
	int    spantype = file->read_int();
	double p1       = file->read_double();
	double p2       = file->read_double();
	double p3       = file->read_double();
	double p4       = file->read_double();
	double p5       = file->read_double();
	double p6       = file->read_double();

	/*if( current_channel_envelope->getChannelId() == LW_CHANNEL_Z ){
		value = -value;
	}*/

	LWChannelKey *channel_key = new LWChannelKey(
		value,
		time,
		spantype,
		p1,
		p2,
		p3,
		p4,
		p5,
		p6      
	);
	current_channel_envelope->insert( channel_key );
}
void LWSceneParser::Behaviors(){
	int pre  = file->read_int();
	int post = file->read_int();
	current_channel_envelope->setBehaviors( pre, post );
	file->read_end_scope();
}


/*
	LockedChannels <bit-field value>

	example:     LockedChannels 4093

	The LockedChannels function determines the extent of the mouse control 
	from LightWave's Layout.  Separate independent channels of motion, 
	rotation, etc. can be locked off to restrict the mouse's  control on 
	the current object.  The mouse functions that it can effect are:  
	Move (X,Y,Z), Rotate(H,P,B), Scale/Stretch(X,Y,Z), and MovePivotPoint(X,Y,Z).

	The bit-field value is produced by calculating the decimal value of a 
	12 position bit-field whose bits represent logical on/off switches that 
	are number left to right from 0 - 11.  The least-significant bit for 
	this field is the rightmost bit.  Each channel has a corresponding bit 
	in the bit-field.  When a channel is locked, its bit (or switch) is 
	turned on.

	<bit positions>:	0 - Move X
				1 - Move Y
				2 - Move Z
				3 - Rotate Heading
				4 - Rotate Pitch
				5 - Rotate Bank
				6 - Scale X / Size X  (channels are connected)
				7 - Scale Y / Size Y (channels are connected)
				8 - Scale Z / Size Z (channels are connected)
				9 - MovePivotPoint X
				10 - Move Pivot Point Y
				11 - Move Pivot Point Z

	User Interface:

	The LockedChannels function is set from the Layout mouse 
	control area.
*/
void LWSceneParser::LockedChannels(){
	int locked_channels = file->read_int();
}


/*
	ParentObject <object instance>

	example:     ParentObject 4

	The ParentObject function provides LightWave with the
	current object's parent object in the hierarchical chain.
	The value is equal to the parent objects position in the
	loading sequence. The example function would parent the
	current object to the fourth object instance in the scen
	file. When the ParentObject function is active, all keyframe 
	information for the object becomes an offset from the
	parents information.

	User Interface:
	
	Objects hierarchies are created by selecting the parent 
	function from layout. The parent object is then selected 
	from the pop-up listing provided.
*/
void LWSceneParser::ParentObject(){
	LWInstance *parent_object    = NULL;
	int         parent_object_id = file->read_int();

	int_to_LWInstance::iterator i_it = objects.find( parent_object_id );
	if( i_it != objects.end() ){
		parent_object = (*i_it).second;
	}
	if( current_object != NULL ){
		current_object->setParentObject( parent_object );
	}
}


void LWSceneParser::TargetObject(){
	int target_object = file->read_int();
}


/*
	GoalObject <object instance>

	example:  GoalObject 5

	The GoalObject function provides LightWave with the current
	bone's goal object for an inverse kinematics chain.  The
	value is equal to the goal object position in the loading
	sequence. The example function would goal the current bone
	to the fifth object instance in the scene file.

	User Interface: 
	
	The GoalObject function is set from the IK options from
	Layout.
*/
void LWSceneParser::GoalObject(){
	int goal_object = file->read_int();
}


void LWSceneParser::SchematicPosition(){}


};  //  namespace Imports
};  //  namespace Teddy


#endif  //  TEDDY_INCLUDE_LW_SCENE

