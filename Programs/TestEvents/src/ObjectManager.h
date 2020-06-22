
/*
	TEDDY - General graphics application library
	Copyright (C) 1999, 2000, 2001	Timo Suoranta
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


#ifndef TEST_EVENTS__OBJECT_MANAGER__H
#define TEST_EVENTS__OBJECT_MANAGER__H


#include "Teddy/TeddyConfig.h"
#include "Teddy/Application/BaseObjectManager.h"
#include "Teddy/Application/BaseSimulationTimer.h"
#include "Teddy/Materials/Material.h"
#include "Teddy/Models/Model.h"

#include "Node.h"


//!  ObjectManager
class ObjectManager 
: 
public Node,
public Teddy::Application::BaseObjectManager
{
public:
	ObjectManager( Root *root );

public:
	bool addLights           ();
	bool addFloorAndBoxes    ();
	bool addConesAndCylinders();
	bool addSpheresAndTorus  ();
	bool addSolids           ();
	bool addLwo              ();
	bool addTrees            ();
	bool addBallStacks       ();
	bool addLSystems         ();
	bool addGlow             ();
	bool addAxes             ();
	bool addTeddyLogo        ();

	void                  selectModel     ( Teddy::Models::Model *model );
	Teddy::Models::Model *getSelectedModel();

protected:
	int                                      SD;  //!<  Subdivision level for some objects
	Teddy::Application::BaseSimulationTimer *st;  //!<  Simulation timer

	//  Selection - initial hack-in, needs refactoring
	Teddy::Models::Model       *selected_model;   //!<  Selected object
	Teddy::Materials::Material  material_backup;  //!<  Material property for this Model

};


#endif  //  TEST_EVENTS__OBJECT_MANAGER__H

