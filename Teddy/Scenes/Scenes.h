
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


namespace Teddy {

/*!

This namespace contains the root of %Teddy scene graph.
Root for each scene is an instance of Scene class. %Teddy
scene is simply created by creating an instances of Scene
and using add() method to add Models and Lights to
it.

To display %Teddy scene you must have PhysicalComponents::Projection,
Scenes::Camera and Scenes::Scene. These three are independent.
You can have several scenes, one camera, and several projections,
or one scene, several cameras, and one or more projections.

Projection are spesifies some rendering preferences for that
spesific area. Examples of such preferences are: lighting model,
filled/outline polygons, and coloring.

Camera spesifies the viewing position, direction and field
of vision. In the implementation Camera is responsible for
negotiating projection and modelview matrices.

Scene simply contains all lightsources and models in
the scene.
*/
namespace Scenes {
};
};


