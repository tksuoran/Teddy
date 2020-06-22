
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

PhysicalComponents are user interface classes. On popular
operating environments these are also known as gadgets,
window gadgets, widgets, controls, windows and so on.

Area is the base class for all %Teddy widgets. See
documentation for Area for more information how Areas
work.

Root manager of all PhysicalComponents is WindowManager.
It is container for root level Areas, Layers, which further
can contain any Area and Projection instances. WindowManager
also processes input events and sends them to currently active
event listener.

Currently many features are under testing, and behave
differently than they are purposed to behave due to missing
features.

Most components are not yet interactive. To make component
interactive, it will have to implement either MouseListener
or KeyListener. This scheme may change later when
LogicalComponents and ComponentMapping are introduced.
*/
namespace PhysicalComponents {
};
};


