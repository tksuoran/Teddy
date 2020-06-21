
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


#include "Teddy/Graphics/PsRenderer.h"
#include "Teddy/SysSupport/StdMaths.h"
#include <cassert>
#include "Teddy/SysSupport/StdAlgo.h"
using namespace Teddy::SysSupport;


namespace Teddy    {
namespace Graphics {


#define EPS_SMOOTH_LINE_FACTOR 0.06
#define EPS_GOURAUD_THRESHOLD  0.05
#define EPS_LINE_WIDTH         0.1


//  OpenGL's GL_3D_COLOR feedback vertex format.
struct Feedback3Dcolor {
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat red;
	GLfloat green;
	GLfloat blue;
	GLfloat alpha;
};


static char *NicegouraudtriangleEPS[] = {
	"\n% Smooth-shaded triangle - x3 y3 r3 g3 b3 x2 y2 r2 g2 b2 x1 y1 r1 g1 b1 ST",
	"/ST {",
	"	/b1 exch def",
	"	/g1 exch def",
	"	/r1 exch def",
	"	/y1 exch def",
	"	/x1 exch def",
	"	/b2 exch def",
	"	/g2 exch def",
	"	/r2 exch def",
	"	/y2 exch def",
	"	/x2 exch def",
	"	/b3 exch def",
	"	/g3 exch def",
	"	/r3 exch def",
	"	/y3 exch def",
	"	/x3 exch def",
	"	b2 b1 sub abs 0.05 gt",
	"	g2 g1 sub abs 0.017 gt",
	"	r2 r1 sub abs 0.032 gt",
	"	b3 b1 sub abs 0.05 gt",
	"	g3 g1 sub abs 0.017 gt",
	"	r3 r1 sub abs 0.032 gt",
	"	b2 b3 sub abs 0.05 gt",
	"	g2 g3 sub abs 0.017 gt",
	"	r2 r3 sub abs 0.032 gt",
	"	or or or or or or or or {",
	"		/b12 b1 b2 add 0.5 mul def",
	"		/g12 g1 g2 add 0.5 mul def",
	"		/r12 r1 r2 add 0.5 mul def",
	"		/y12 y1 y2 add 0.5 mul def",
	"		/x12 x1 x2 add 0.5 mul def",
	"		/b13 b1 b3 add 0.5 mul def",
	"		/g13 g1 g3 add 0.5 mul def",
	"		/r13 r1 r3 add 0.5 mul def",
	"		/y13 y1 y3 add 0.5 mul def",
	"		/x13 x1 x3 add 0.5 mul def",
	"		/b32 b3 b2 add 0.5 mul def",
	"		/g32 g3 g2 add 0.5 mul def",
	"		/r32 r3 r2 add 0.5 mul def",
	"		/y32 y3 y2 add 0.5 mul def",
	"		/x32 x3 x2 add 0.5 mul def",
	"		x1 y1 r1 g1 b1 x12 y12 r12 g12 b12 x13 y13 r13 g13 b13",
	"		x2 y2 r2 g2 b2 x12 y12 r12 g12 b12 x32 y32 r32 g32 b32",
	"		x3 y3 r3 g3 b3 x32 y32 r32 g32 b32 x13 y13 r13 g13 b13",
	"		x32 y32 r32 g32 b32 x12 y12 r12 g12 b12 x13 y13 r13 g13 b13",
	"		ST ST ST ST",
	"	} {",
	"		x1 y1 x2 y2 x3 y3 r1 g1 b1 T",
	"	} ifelse",
	"} bind def"
	"\n",
	NULL
};


static char *gouraudtriangleEPS[] ={
	"/bd{bind def}bind def /triangle { aload pop   setrgbcolor  aload pop 5 3",
	"roll 4 2 roll 3 2 roll exch moveto lineto lineto closepath fill } bd",
	"/computediff1 { 2 copy sub abs threshold ge {pop pop pop true} { exch 2",
	"index sub abs threshold ge { pop pop true} { sub abs threshold ge } ifelse",
	"} ifelse } bd /computediff3 { 3 copy 0 get 3 1 roll 0 get 3 1 roll 0 get",
	"computediff1 {true} { 3 copy 1 get 3 1 roll 1 get 3 1 roll 1 get",
	"computediff1 {true} { 3 copy 2 get 3 1 roll  2 get 3 1 roll 2 get",
	"computediff1 } ifelse } ifelse } bd /middlecolor { aload pop 4 -1 roll",
	"aload pop 4 -1 roll add 2 div 5 1 roll 3 -1 roll add 2 div 3 1 roll add 2",
	"div 3 1 roll exch 3 array astore } bd /gouraudtriangle { computediff3 { 4",
	"-1 roll aload 7 1 roll 6 -1 roll pop 3 -1 roll pop add 2 div 3 1 roll add",
	"2 div exch 3 -1 roll aload 7 1 roll exch pop 4 -1 roll pop add 2 div 3 1",
	"roll add 2 div exch 3 -1 roll aload 7 1 roll pop 3 -1 roll pop add 2 div 3",
	"1 roll add 2 div exch 7 3 roll 10 -3 roll dup 3 index middlecolor 4 1 roll",
	"2 copy middlecolor 4 1 roll 3 copy pop middlecolor 4 1 roll 13 -1 roll",
	"aload pop 17 index 6 index 15 index 19 index 6 index 17 index 6 array",
	"astore 10 index 10 index 14 index gouraudtriangle 17 index 5 index 17",
	"index 19 index 5 index 19 index 6 array astore 10 index 9 index 13 index",
	"gouraudtriangle 13 index 16 index 5 index 15 index 18 index 5 index 6",
	"array astore 12 index 12 index 9 index gouraudtriangle 17 index 16 index",
	"15 index 19 index 18 index 17 index 6 array astore 10 index 12 index 14",
	"index gouraudtriangle 18 {pop} repeat } { aload pop 5 3 roll aload pop 7 3",
	"roll aload pop 9 3 roll 8 index 6 index 4 index add add 3 div 10 1 roll 7",
	"index 5 index 3 index add add 3 div 10 1 roll 6 index 4 index 2 index add",
	"add 3 div 10 1 roll 9 {pop} repeat 3 array astore triangle } ifelse } bd",
	NULL
};



void PsRenderer::writePs( char *pFilename, GLfloat *pFeedbackBuffer, int NbValues, bool sort ){
	assert( pFilename );

	FILE *pFile = fopen( pFilename, "wt" );
	if( !pFile ){
		return;
	}

	spewWireFrameEPS( pFile, sort, NbValues, pFeedbackBuffer );
	fclose( pFile );
}


GLfloat *PsRenderer::spewPrimitiveEPS( FILE *file, GLfloat *loc ){
	int              token;
	int              nvertices, i;
	GLfloat          red, green, blue;
	int              smooth;
	GLfloat          dx, dy, dr, dg, db, absR, absG, absB, colormax;
	int              steps;
	Feedback3Dcolor *vertex;
	GLfloat          xstep, ystep, rstep, gstep, bstep;
	GLfloat          xnext, ynext, rnext, gnext, bnext, distance;

	token = (int)*loc;
	loc++;
	switch( token ){
	case GL_LINE_RESET_TOKEN:
	case GL_LINE_TOKEN:
		vertex = (Feedback3Dcolor *) loc;

		dr = vertex[1].red   - vertex[0].red;
		dg = vertex[1].green - vertex[0].green;
		db = vertex[1].blue  - vertex[0].blue;

		if( dr != 0 || dg != 0 || db != 0 ){
			//  Smooth shaded line.
			dx       = vertex[1].x - vertex[0].x;
			dy       = vertex[1].y - vertex[0].y;
			distance = (float)sqrt(dx * dx + dy * dy);

			absR = (float)fabs( dr );
			absG = (float)fabs( dg );
			absB = (float)fabs( db );

			colormax = MAX( absR, MAX(absG, absB) );
			steps = (int)MAX( 1.0, colormax * distance * EPS_SMOOTH_LINE_FACTOR );

			xstep = dx / steps;
			ystep = dy / steps;

			rstep = dr / steps;
			gstep = dg / steps;
			bstep = db / steps;

			xnext = vertex[0].x;
			ynext = vertex[0].y;
			rnext = vertex[0].red;
			gnext = vertex[0].green;
			bnext = vertex[0].blue;

			/* Back up half a step; we want the end points to be
			 exactly the their endpoint colors. */
			xnext -= (float)xstep / 2.0f;
			ynext -= (float)ystep / 2.0f;
			rnext -= (float)rstep / 2.0f;
			gnext -= (float)gstep / 2.0f;
			bnext -= (float)bstep / 2.0f;

			fprintf( file, "%g %g %g setrgbcolor\n", vertex[0].red, vertex[0].green, vertex[0].blue );
			fprintf( file, "%g %g moveto\n",         vertex[0].x,   vertex[0].y );

			for( i = 0; i < steps; i++ ){
				xnext += xstep;
				ynext += ystep;
				rnext += rstep;
				gnext += gstep;
				bnext += bstep;
				fprintf( file, "%g %g lineto stroke\n", xnext, ynext );
				fprintf( file, "%g %g %g setrgbcolor\n", rnext, gnext, bnext );
				fprintf( file, "%g %g moveto\n", xnext, ynext);
			}
			fprintf( file, "%g %g lineto stroke\n", vertex[1].x, vertex[1].y );
		}else{  //  single color segment -> S
			fprintf( file, "%g %g %g %g %g %g %g S\n",vertex[1].x,vertex[1].y, vertex[0].x,vertex[0].y,vertex[0].red, vertex[0].green, vertex[0].blue );
		}

		loc += 14;  /* Each vertex element in the feedback buffer is 7 GLfloats. */

		break;

	case GL_POLYGON_TOKEN:
		nvertices = (int)*loc;
		loc++;

		vertex = (Feedback3Dcolor *) loc;

		if( nvertices > 0 ){
			red    = vertex[0].red;
			green  = vertex[0].green;
			blue   = vertex[0].blue;
			smooth = 0;
			for( i=1; i<nvertices; i++ ){
				if (red   != vertex[i].red || green != vertex[i].green || blue  != vertex[i].blue ){
					smooth = 1;
					break;
				}
			}
			if( smooth ){
				/* Smooth shaded polygon; varying colors at vertices. */
				int triOffset;

				/* Break polygon into "nvertices-2" triangle fans. */
				for( i=0; i<nvertices - 2; i++ ){
					triOffset = i * 7;

					fprintf(file, "[%g %g %g %g %g %g]", vertex[0].x, vertex[i + 1].x, vertex[i + 2].x, vertex[0].y, vertex[i + 1].y, vertex[i + 2].y );
					fprintf(file, " [%g %g %g] [%g %g %g] [%g %g %g] gouraudtriangle\n", vertex[0].red, vertex[0].green, vertex[0].blue, vertex[i + 1].red, vertex[i + 1].green, vertex[i + 1].blue, vertex[i + 2].red, vertex[i + 2].green, vertex[i + 2].blue );
					/*
					 // x3 y3 r3 g3 b3 x2 y2 r2 g2 b2 x1 y1 r1 g1 b1 ST
					 fprintf(file,"%g %g %g %g %g %g %g %g %g %g %g %g %g %g %g ST\n",
					 vertex[i+2].x,vertex[i+2].y,vertex[i+2].red,vertex[i+2].green,vertex[i+2].blue,
					 vertex[i+1].x,vertex[i+1].y,vertex[i+1].red,vertex[i+1].green,vertex[i+1].blue,
					 vertex[0].x,vertex[0].y,vertex[0].red,vertex[0].green,vertex[0].blue);*/
				}
			}else{
				if( nvertices > 3 ){ // polygon
					// Draw a filled polygon
					fprintf( file, "newpath\n" );
					fprintf( file, "%g %g %g setrgbcolor\n", red, green, blue );
					fprintf( file, "%g %g moveto\n", vertex[0].x, vertex[0].y);
					for( i=1; i<nvertices; i++){
						fprintf( file, "%g %g lineto\n", vertex[i].x, vertex[i].y );
					}
					fprintf( file, "closepath fill\n\n" );
				}else{ // triangle -> T
					fprintf(file,"%g %g %g %g %g %g %g %g %g T\n", vertex[2].x,vertex[2].y, vertex[1].x,vertex[1].y, vertex[0].x,vertex[0].y, red,green,blue );
				}
			}
		}
		loc += nvertices * 7;  /* Each vertex element in the feedback buffer is 7 GLfloats. */
		break;

	case GL_POINT_TOKEN:
		vertex = (Feedback3Dcolor *) loc;
		fprintf(file, "%g %g %g 0 360 %g %g %g P\n",vertex[0].x, vertex[0].y, m_PointSize / 2.0,vertex[0].red,vertex[0].green,vertex[0].blue );
		loc += 7;           /* Each vertex element in the feedback buffer is 7 GLfloats. */
		break;
	default:
		/* XXX Left as an excersie to the reader. */
		//printf("Incomplete implementation.  Unexpected token (%d).\n", token);
		//exit(1);
		break;
	}
	return loc;
}

void PsRenderer::spewUnsortedFeedback( FILE *file, GLint size, GLfloat * buffer ){
	GLfloat *loc, *end;

	loc = buffer;
	end = buffer + size;
	while( loc < end ){
		loc = spewPrimitiveEPS( file, loc );
	}
}


int PsRenderer::compare( const void *a, const void *b ){
	DepthIndex *p1   = (DepthIndex *) a;
	DepthIndex *p2   = (DepthIndex *) b;
	GLfloat     diff = p2->depth - p1->depth;

	if( diff > 0.0 ){
		return 1;
	}else if( diff < 0.0 ){
		return -1;
	}else{
		return 0;
	}
}


void PsRenderer::spewSortedFeedback( FILE *file, GLint size, GLfloat *buffer ){
	int              token;
	GLfloat         *loc, *end;
	Feedback3Dcolor *vertex;
	GLfloat          depthSum;
	int              nprimitives, item;
	DepthIndex      *prims;
	int              nvertices, i;

	end = buffer + size;

	/* Count how many primitives there are. */
	nprimitives = 0;
	loc = buffer;
	while( loc < end ){
		token = (int)*loc;
		loc++;
		switch( token ){
		case GL_LINE_TOKEN:
		case GL_LINE_RESET_TOKEN:
			loc += 14;
			nprimitives++;
			break;
		case GL_POLYGON_TOKEN:
			nvertices = (int)*loc;
			loc++;
			loc += (7 * nvertices);
			nprimitives++;
			break;
		case GL_POINT_TOKEN:
			loc += 7;
			nprimitives++;
			break;
		default:
			//  XXX Left as an excersie to the reader.
			//printf("Incomplete implementation.  Unexpected token (%d).\n", token);
			//exit(1);
			break;
		}
	}

	//  Allocate an array of pointers that will point back at
	//  primitives in the feedback buffer.  There will be one
	//  entry per primitive.  This array is also where we keep the
	//  primitive's average depth.  There is one entry per
	//  primitive  in the feedback buffer.
	prims = new DepthIndex[nprimitives];

	item = 0;
	loc  = buffer;
	while( loc < end ){
		prims[item].ptr = loc;  //  Save this primitive's location.
		token = (int)*loc;
		loc++;
		switch( token ){
		case GL_LINE_TOKEN:
		case GL_LINE_RESET_TOKEN:
			vertex   = (Feedback3Dcolor *) loc;
			depthSum = vertex[0].z + vertex[1].z;
			prims[item].depth = (float)depthSum / 2.0f;
			loc += 14;
			break;
		case GL_POLYGON_TOKEN:
			nvertices = (int)*loc;
			loc++;
			vertex = (Feedback3Dcolor *) loc;
			depthSum = vertex[0].z;
			for( i=1; i<nvertices; i++ ){
				depthSum += vertex[i].z;
			}
			prims[item].depth = depthSum / nvertices;
			loc += (7 * nvertices);
			break;
		case GL_POINT_TOKEN:
			vertex = (Feedback3Dcolor *) loc;
			prims[item].depth = vertex[0].z;
			loc += 7;
			break;
		default:
			//  XXX Left as an excersie to the reader. */
			//  ASSERT(1);
			break;
		}
		item++;
	}
	assert( item == nprimitives );

	//  Sort the primitives back to front.
	qsort( prims, nprimitives, sizeof(DepthIndex), compare );

	//  XXX Understand that sorting by a primitives average depth
	//  doesn't allow us to disambiguate some cases like self
	//  intersecting polygons.  Handling these cases would require
	//  breaking up the primitives.  That's too involved for this
	//  example.  Sorting by depth is good enough for lots of
	//  applications.

	//  Emit the Encapsulated PostScript for the primitives in back to front order.
	for( item=0; item<nprimitives; item++ ){
		(void) spewPrimitiveEPS( file, prims[item].ptr );
	}

	delete[] prims;
}


void PsRenderer::spewWireFrameEPS( FILE *file, bool doSort, GLint size, GLfloat *buffer ){
	GLfloat clearColor[4], viewport[4];
	GLfloat lineWidth;

	//  Read back a bunch of OpenGL state to help make the EPS
	//  consistent with the OpenGL clear color, line width, point
	//  size, and viewport.
	glGetFloatv( GL_VIEWPORT,           viewport    );
	glGetFloatv( GL_COLOR_CLEAR_VALUE,  clearColor  );
	glGetFloatv( GL_LINE_WIDTH,        &lineWidth   );
	glGetFloatv( GL_POINT_SIZE,        &m_PointSize );

	//  Emit EPS header.
	fputs( "%!PS-Adobe-2.0 EPSF-2.0\n", file );
	//  Notice %% for a single % in the fprintf calls.
	fprintf( file, "%%%%BoundingBox: %g %g %g %g\n", viewport[0], viewport[1], viewport[2], viewport[3] );
	fputs( "%%EndComments\n", file );
	fputs( "\n", file );
	fputs( "gsave\n", file );
	fputs( "\n", file );

	fprintf( file, "/threshold %g def\n", EPS_GOURAUD_THRESHOLD );

	fprintf( file, "\n%% RGB color command - r g b C\n" );
	fprintf( file, "/C { setrgbcolor } bind def\n" );

	//  This is more compact
	fprintf( file, "\n%% Point - x_center y_center PointSize/2 0 360 r g b P\n" );
	fprintf( file, "/P { C arc fill } bind def\n" );

	fprintf( file, "\n%% Segment - x2 y2 x1 y1 r g b S\n" );
	fprintf( file, "/S { C moveto lineto stroke } bind def\n" );

	fprintf( file, "\n%% Flat-shaded triangle - x3 y3 x2 y2 x1 y1 r g b T\n" );
	fprintf( file, "/T { C newpath moveto lineto lineto closepath fill } bind def\n" );

	//  Output Frederic Delhoume's "gouraudtriangle" PostScript fragment.
	fputs( "% The gouraudtriangle PostScript fragement below is free\n", file );
	fputs( "% written by Frederic Delhoume (delhoume@ilog.fr)\n", file );

	for( int i=0; gouraudtriangleEPS[i]; i++ ){
		fprintf( file, "%s\n", gouraudtriangleEPS[i] );
	}

	fprintf( file, "\n%g setlinewidth\n", EPS_LINE_WIDTH );

	//  Clear the background like OpenGL had it
	fprintf( file, "%g %g %g setrgbcolor\n",   clearColor[0], clearColor[1], clearColor[2] );
	fprintf( file, "%g %g %g %g rectfill\n\n", viewport[0],   viewport[1], viewport[2], viewport[3] );

	// Main process
	if( doSort ){
		spewSortedFeedback( file, size, buffer );
	}else{
		spewUnsortedFeedback( file, size, buffer );
	}

	// Emit EPS trailer
	fputs( "\ngrestore\n", file );
	fputs( "showpage\n", file );

}


};  //  namespace Graphics
};  //  namespace Teddy

