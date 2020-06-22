
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


#include "Teddy/TeddyConfig.h"
#if defined( TEDDY_INCLUDE_LW_SCENE )


#if defined(_MSC_VER)
#	pragma warning(disable:4786)
#endif


#include "Teddy/Imports/LWSurface.h"
#include "Teddy/Imports/LWSurfaceBlok.h"
#include "Teddy/Imports/LWFile.h"
#include "Teddy/SysSupport/Messages.h"
#include "Teddy/SysSupport/StdIO.h"


namespace Teddy   {
namespace Imports {


void LWSurfaceBlok::applyGradient(){
	//  Disabled gradients are easy to handle
	if( enable == 0 ){
		return;
	}

	dmsg( M_LWO, "I have not yet ivestigated how to handle gradients." );
}


};  //  namespace Imports
};  //  namespace Teddy


#endif  //  TEDDY_INCLUDE_LW_SCENE

