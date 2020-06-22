
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


#include "Teddy/PhysicalComponents/MenuList.h"
#include "Teddy/PhysicalComponents/Style.h"
#include "Teddy/Graphics/View.h"
#include "Teddy/SysSupport/Messages.h"
#include <cstring>
using namespace Teddy::Graphics;


namespace Teddy              {
namespace PhysicalComponents {


//!  Constructor
MenuList::MenuList(  std::string name, const int axis ):Dock(name,axis){
};


/*virtual*/ void MenuList::drawSelf(){
      dmsg( 
			M_WMD, 
			"menu list %s drawLayer() size %d x %d", 
			getName().c_str(),
			size[0],
			size[1]
		);

	view->disable( View::TEXTURE_2D );
    Color color(0.65f,0.65f,0.65f,1.0f);
    color.glApply();
	this->drawFillRect( 1, 1, size[0]-1, size[1]-1 );
    drawBiColRect( 0, 0, size[0], size[1], Color::WHITE, Color::BLACK );
}


};  //  namespace PhysicalComponents
};  //  namespace Teddy

