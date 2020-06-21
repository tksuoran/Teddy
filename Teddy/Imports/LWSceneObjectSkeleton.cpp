
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

	$Id: LWSceneObjectSkeleton.cpp,v 1.1 2002/02/16 12:41:39 tksuoran Exp $
*/


#include "Teddy/TeddyConfig.h"
#if defined( TEDDY_INCLUDE_LW_SCENE )


#include "Teddy/Imports/LWBone.h"
#include "Teddy/Imports/LWSceneFile.h"
#include "Teddy/Imports/LWSceneParser.h"


namespace Teddy   {
namespace Imports {


/*
	Metamorph <percentage> ¦ (envelope)

	example:     Metamorph 0.500000

	The Metamorph function provides LightWave with the
	information needed to morph the current object into
	a target object that is provided in the MorphTarget
	function.

	The value is the percentage of change between the
	current object and its target. The function's value
	can be changed over time with an envelope. If an
	envelope is chosen, the functions value is replaced 
	with an envelope identifier. For more information on
	envelopes, see the Envelopes Section 1.4.

	When the Metamorph function is selected, two additional
	function listings are necessary. These are listed below:
*/
void LWSceneParser::MorphAmount(){
	double metamorph = file->read_double();
}


/*
	Additional:     MorphTarget  <object instance>

	example:     MorphTarget 2

	The MorphTarget function provides the morph target's
	object position in the object listing.
*/
void LWSceneParser::MorphTarget(){
	int morph_target = file->read_int();
}


/*	
	Additional:     MorphSurfaces  <flag>

	example:     MorphSurfaces 1

	The MorphSurfaces flag activates the morphing of
	the surface attributes. 

 	 <flag>:
		0 - Off
		1 - On

	User Interface:
	
	The Metamorph functions are set from the Objects Panel.
*/
void LWSceneParser::MorphSurfaces(){
	int morph_surfaces = file->read_int();
}


void LWSceneParser::UseBonesFrom(){
	int use_bones_from = file->read_int();
}


void LWSceneParser::BoneFalloffType(){
	int bone_falloff_type = file->read_int();
}


/*
	AddBone

	example:  AddBone

	The AddBone function is the first function called in
	an object skeleton. It is called for each instance of
	a bone loading. This function will add a bone to the
	current object and produce a series of function listings
	for this bone.
*/
void LWSceneParser::AddBone(){
	current_object = current_bone = new LWBone();
}


/*
	BoneName  Bone ¦ <string>

	example:  BoneName FootBone

	The BoneName function provides a name for the bone
	created with the AddBone function. If the user renames
	the bone using the Rename Bone function from the Object
	Skeleton control panel the string is listed following
	the function name. If the user does not rename the bone,
	it is given the default name of Bone. If multiple bones
	instances have the same name, duplicate bones are given
	a numbered suffix to the name during the loading/creation
	process. This number is enclosed in parenthesis and
	follows the bone name.  

	An example:  FootBone (2) is the second instance of a
	bone with the name FootBone. The suffix is not saved in
	the scene file, and is used only as a user reference.
*/
void LWSceneParser::BoneName(){
	char *bone_name = file->read_string();
}


/*
	ShowBone  <refresh value> <color value> 

	example:     ShowBone 1 2

	The ShowBone function determines how the bone is
	going to be displayed in Layout. The above example
	would display this (as opposed to hiding it) as
	a green bone.

	 Refresh value

	This argument sets the bones display type in Layout.

	<Refresh value>:	0 - No Refresh (Hide)
				1 - Refresh (Show)

	User Interface:  The refresh value is selected in the
	second column of the Scene Overview from the Scene Menu.  	

	 Color value

	This argument sets the color of the bone when not
	selected in Layout. When selected, all items highlight
	to yellow.

	<Color value>:
		1 - Blue
		2 - Green
		3 - Light Blue
		4 - Red
		5 - Purple
		6 - Orange
		7 - Gray

	User Interface:
	
	The color value is selected in the first column of the 
	Scene Overview from the Scene Menu.
*/
void LWSceneParser::ShowBone(){
	int refresh_value = file->read_int();
	int color_value   = file->read_int();
}


/*
	BoneActive <flag>

	example:  BoneActive 1

	The BoneActive flag activates the bone in layout and
	will allow it to begin deforming the object's geometry.
	This function produces a BoneActive listing with a value
	of 1 when turned on. When turned off, this function 
	does not produce a listing in the scene file.

	<flag>:	0 - Off (No function listing)
		1 - On

	User Interface:
	
	This function is set from the Object Skeleton control 
	panel or by the keyboard shortcut of <r> for rest.

	The BoneActive function is listed for all bones.
*/
void LWSceneParser::BoneActive(){
	int bone_active = file->read_int();
}


/*
	BoneRestPosition <x position> <y position> <z position>

	example:  BoneRestPosition 0.500000 0.200000 1.35000

	The BoneRestPosition function provides the initial
	rest x, y, z position of the bone. In this position,
	the bone does not influence (distort) the object geometry.  

	User Interface:
	
	The BoneRestPosition function is set from the 
	Object Skeleton control panel or by the keyboard 
	shortcut of <r> for rest.

	The BoneRestPosition function is listed for all bones.
*/
void LWSceneParser::BoneRestPosition(){
	double x = file->read_double();
	double y = file->read_double();
	double z = file->read_double();
}


/*
	BoneRestDirection <Heading angle> <Pitch angle> <Bank angle>

	example:  BoneRestDirection 39.000000 7.900000 0.000000

	The BoneRestDirection function provides the initial
	rest H, P, B rotations of the bone. In this position,
	the bone does not influence (distort) the object geometry.

	User Interface:
	
	The BoneRestDirection function is set from the Object 
	Skeleton control panel or by the keyboard shortcut of <r> 
	for rest.

	The BoneRestDirection function is listed for all bones.
*/
void LWSceneParser::BoneRestDirection(){
	double h = file->read_double();
	double p = file->read_double();
	double b = file->read_double();
}


/*
	BoneRestLength <float>

	example:  BoneRestLength 1.078000

	The BoneRestLength function provides the initial rest
	length of the bone. This is the "size" of the bone in Layout.

	User Interface:
	
	The BoneRestLength function is set from the Rest Length 
	field on the Object Skeleton control panel or by the 
	Rest Length mouse control in Layout.

	The BoneRestLength function is listed for all bones.
*/
void LWSceneParser::BoneRestLength(){
	double bone_rest_length = file->read_double();
}


/*
	BoneStrength <float>

	example:  BoneStrength 2.500000

	The BoneStrength function provides the strength of a bone
	that is separate from it's rest length. This functions
	value is used when the ScaleBoneStrength flag is turned
	off (0). When the ScaleBoneStrength function is turned on, 
	the bone strength is equal to the BoneRestLength.

	User Interface:
	
	The BoneStrength functions value is set from the Strength 
	field on the Object Skeleton control panel.

	The BoneStrength function is listed for all bones.
*/
void LWSceneParser::BoneStrength(){
	double bone_strength = file->read_double();
}


/*
	ScaleBoneStrength <flag>

	example:  ScaleBoneStrength 1

	The ScaleBoneStrength flag  turns the ScaleBoneStrength
	function on. The listing is produced by the Scale Strength
	by Rest Length check box on the Object Skeleton control
	panel. This function allows the user to either lock the
	bone strength to the rest length of the bone, or to adjust
	them separately. This function produces a ScaleBoneStrength
	listing  with a value of 1 when turned on.  

	<flag>:
		0 - Off (Default)
		1 - On (Scale Strength by Rest Length)

	User Interface:
	
	The ScaleBoneStrength function is set from the Scale 
	Strength by Rest Length check box on the Object Skeleton 
	control panel.

	The ScaleBoneStrength flag is listed for all bones.
*/
void LWSceneParser::ScaleBoneStrength(){
	int scale_bone_strength = file->read_int();
}
void LWSceneParser::BoneLimitedRange(){
}
void LWSceneParser::BoneMinRange(){}
void LWSceneParser::BoneMaxRange(){}

/*
	BoneMotion (unnamed) 

	example:     BoneMotion (unnamed)

	The BoneMotion identifier denotes the beginning of the keyframe information 
	for the current bone segment.  It does not require any arguments to be passed 
	to it.

	The BoneMotion identifier is listed with all bones.
*/
void LWSceneParser::BoneMotion(){}

void LWSceneParser::HController(){
	int h_controller = file->read_int();
}
void LWSceneParser::PController(){
	int p_controller = file->read_int();
}
void LWSceneParser::BController(){
	int b_controller = file->read_int();
}


/*
	HLimits <min. angle> <max. angle>

	example:    HLimits -37.5 180

	The HLimits function provides the minimum and maximum angles of heading 
	rotation for the Inverse Kinematics function.  

	<min. angle>,<max. angle>:  Range = -360 to 360

	User Interface:  The HLimits angles are set from the IK Options controls 
			 from Layout.
*/
void LWSceneParser::HLimits(){
	double min = file->read_double();
	double max = file->read_double();
}


/*
	PLimits <min. angle> <max. angle>

	example:    PLimits -37.5 180

	The PLimits function provides the minimum and maximum angles of the pitch 
	rotation for the Inverse Kinematics function.  

	<min. angle>,<max. angle>:  Range = -360 to 360

	User Interface:  The PLimits angles are set from the IK Options controls 
			 from Layout.
*/
void LWSceneParser::PLimits(){
	double min = file->read_double();
	double max = file->read_double();
}


/*
	BLimits <min. angle> <max. angle>

	example:    BLimits -37.5 180

	The BLimits function provides the minimum and maximum angles of the banking 
	rotation for the Inverse Kinematics function.  

	<min. angle>,<max. angle>:  Range = -360 to 360

	User Interface:  The BLimits angles are set from the IK Options controls 
	     		 from Layout.
*/
void LWSceneParser::BLimits(){
	double min = file->read_double();
	double max = file->read_double();
}


/*
	IKAnchor <flag>

	example:  IKAnchor 1

	The IKAnchor function sets the current bone as an anchor bone in an inverse 
	kinematics chain.  The predecessors of this bone would not be affected by 
	the goal of its children.

	<flag>:	0 - Off (No function listing)
		1 - On  (Function listing)

	User Interface:  The IKAnchor function is set from the IK options from Layout.
*/
void LWSceneParser::IKAnchor(){
	int ik_anchor = file->read_int();
}


};  //  namespace Imports
};  //  namespace Teddy


#endif  //  TEDDY_INCLUDE_LW_SCENE


/*
  The Object Skeleton Section is a series of one or more bone descriptions 
  that are listed within an object segment.

  An object skeleton does not appear in all object segments.  It is listed 
  when at least one bone has been added to an object.

  Multiple bones in an object segment are listed sequentially in the 
  order in which they were created.

		AddBone *
		BoneName *
		ShowBone *
		BoneActive *
		BoneRestPosition *
		BoneRestDirection *
		BoneRestLength *
		ScaleBoneStrength *
		BoneStrength *
		BoneLimitedRange
			BoneMinRange
			BoneMaxRange
		BoneMotion (identifier) *
		Number of Information Channels *
		Number of Keyframes *
		Keyframe Information *
		EndBehavior *
		LockedChannels
		HLimits
		PLimits
		BLimits
		ParentObject
		GoalObject
		IKAnchor
*/

