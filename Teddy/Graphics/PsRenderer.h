
/*
	TEDDY - General graphics application library
	Copyright (C) 1999-2002  Timo Suoranta
	tksuoran@cc.helsinki.fi

		Adapted from

		Copyright (c) Mark J. Kilgard, 1997.

		This program is freely distributable without licensing fees
		and is provided without guarantee or warrantee expressed or
		implied. This program is -not- in the public domain.

		Example showing how to use OpenGL's feedback mode to capture
		transformed vertices and output them as Encapsulated PostScript.
		Handles limited hidden surface removal by sorting and does
		smooth shading (albeit limited due to PostScript).

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


#ifndef TEDDY__GRAPHICS__PS_RENDERER__H
#define TEDDY__GRAPHICS__PS_RENDERER__H


#include "Teddy/Graphics/Device.h"
#include "Teddy/SysSupport/StdIO.h"


namespace Teddy    {
namespace Graphics {


class PsRenderer {
	GLfloat m_PointSize;

public:
	PsRenderer(){}
	~PsRenderer(){}

public:
	void writePs( const char *pFilename, GLfloat *pFeedbackBuffer, int NbValues, bool sort );

private:
	static int  compare             ( const void *a, const void *b );
	GLfloat    *spewPrimitiveEPS    ( FILE *file, GLfloat *loc );
	void        spewWireFrameEPS    ( FILE *file, bool     doSort, GLint    size, GLfloat *buffer );
	void        spewUnsortedFeedback( FILE *file, GLint    size,   GLfloat *buffer );
	void        spewSortedFeedback  ( FILE *file, GLint    size,   GLfloat *buffer );
};

struct DepthIndex {
	GLfloat *ptr;
	GLfloat  depth;
};


};  //  namespace Graphics
};  //  namespace Teddy


#endif  //  TEDDY__GRAPHICS__VIEW_PS__H

