
/*
	TSGL - Teddy Space Game Library
	Copyright (C) 2002 Timo Suoranta
	tksuoran@gmail.com

		Adapted from

		The Universe Development Kit
		Copyright (C) 2000  Sean O'Neil
		s_p_oneil@hotmail.com

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


/*!
	\file
	\warning Not in use
	\class   RoamSphere
	\author  Sean O'Neil

	This class implements the spherical ROAM algorithm. It keeps lists of the
	vertices, triangles, and diamonds. Because it is currently used to implement
	a fractal-based planet, it also has a member variable of the CFractal class
	and a number of others for defining the planet's basic properties. Its main
	methods are Init(), Update(), and Draw(). Init() initializes the planet
	with a random seed and certain parameters, like radius and roughness.
	Update() updates the priority lists and performs any necessary splits or
	merges in the mesh. Draw() draws the mesh using either smooth or flat shading.
*/


#if 0


#ifndef SPACE_GAME__ROAM_SPHERE__H
#define SPACE_GAME__ROAM_SPHERE__H


#include "Models/Mesh.h"
#include "PhysicalComponents/Projection.h"
#include "UniverseDevelopmentKit/CMaster.h"
#include "UniverseDevelopmentKit/CROAMSphere.h"
using namespace Models;
using namespace PhysicalComponents;
using namespace UniverseDevelopmentKit;


class RoamSphere : public CROAMSphere, public Mesh {
public:
	RoamSphere(){}
	virtual ~RoamSphere(){}

	virtual void drawElements( Projection *p );
};


#define init Init


extern int roam_triangle_count;


#endif  //  SPACE_GAME__ROAM_SPHERE__H


#endif


