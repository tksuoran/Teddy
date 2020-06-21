
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

	$Id:  $
*/


#ifndef TEDDY__BEHAVIOUR__MODEL_ANIMATOR__H
#define TEDDY__BEHAVIOUR__MODEL_ANIMATOR__H


#include "Teddy/MixIn/Tick.h"
#include "Teddy/Maths/Vector.h"
#include "Teddy/SysSupport/StdString.h"


namespace Teddy { 
	namespace Models { class Model; } 
}


namespace Teddy     {
namespace Behaviour {


class ModelController;


//!  Simulated Model
class ModelAnimator : public Teddy::MixIn::Tick {
public:
    ModelAnimator(
        Teddy::Models::Model *m,
        Teddy::Maths::TVector<double> tick_translation=Teddy::Maths::TVector<double>(0.0,0.0,0.0),
        double up   =0.0,
        double right=0.0,
        double view =0.0
    );
	virtual ~ModelAnimator();

	virtual void                   tick              ();
	void                           setController     ( ModelController *controller );
	ModelController               *getController     ();
	void                           setModel          ( Teddy::Models::Model *m );
    Teddy::Models::Model          *getModel          ();
	void                           setTickTranslation( Teddy::Maths::TVector<double> tick_translation );
	void                           setTickRotation   ( double up, double right, double view );
	float                          getSpeed          ();
    Teddy::Maths::TVector<double>  getTickTranslation(){ return tick_translation; }

	inline double                  getHeading(){ return tick_rotation_up;    }
	inline double                  getPitch  (){ return tick_rotation_right; }
	inline double                  getRoll   (){ return tick_rotation_view;  }

protected:
	Teddy::Models::Model          *model;                //!<  Model being animated
	ModelController               *controller;           //!<  Model controller if any
	Teddy::Maths::TVector<double>  tick_translation;     //!<  Translation per tick
	double                         tick_rotation_up;     //!<  Rotation around up axis per tick
	double                         tick_rotation_right;  //!<  Rotation around right axis per tick
	double                         tick_rotation_view;   //!<  Rotation around view axis per tick
};


};  //  namespace Behaviour
};  //  namespace Teddy


#endif  //  TEDDY__BEHAVIOUR__MODEL_ANIMATOR__H

