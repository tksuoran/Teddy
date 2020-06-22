
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


#include "Teddy/Models/Face.h"
#include "Teddy/Models/Vertex.h"
#include "Teddy/PhysicalComponents/Projection.h"
#include "Teddy/SysSupport/Messages.h"
#include "Teddy/SysSupport/StdIO.h"
#include "Teddy/SysSupport/StdAlgo.h"
using namespace std;
using namespace Teddy::PhysicalComponents;


namespace Teddy  {
namespace Models {


#define FACE_NORMAL_EPSILON (double)(0.0002)


//!  Face constructor
Face::Face()
:
Element(0)
{
}

//!  Virtual destructor
/*virtual*/ Face::~Face(){
}


//!  Insert a vertex to the face, pointer version
/*virtual*/ void Face::add( Vertex *v ){
	vertices.push_front( v );
	v->addFace( this );
}


//!  Insert a vertex to the face, component version
/*virtual*/ void Face::add( const float x, const float y, const float z ){
	Vertex *v = new Vertex(x,y,z);
	vertices.push_front( v );
	v->addFace( this );
}


//!  Insert a vertex to the face - pointer version, reverse order
/*virtual*/ void Face::append( Vertex *v ){
	vertices.push_back( v );
	v->addFace( this );
}


//!  Insert a vertex to the face - pointer version, reverse order
/*virtual*/ void Face::append( const float x, const float y, const float z ){
	Vertex *v = new Vertex(x,y,z);
	vertices.push_back( v );
	v->addFace( this );
}


//!  Drawing a Face Element
/*virtual*/ void Face::draw( Projection *p ){
	p->beginPolygon();

	if( isEnabled(EL_USE_ELEMENT_NORMAL|EL_HAS_ELEMENT_NORMAL) ){
		dmsg( M_MAT, "Drawing flat face" );
		p->normal( normal );
	}else{
		dmsg( M_MAT, "Drawing smoothed face" );
	}

	list<Vertex*>::const_iterator v_it = vertices.begin();
	while( v_it != vertices.end() ){
		(*v_it)->draw( p );
		v_it++;
	}

	p->end();
}


/*!
	Smooth face normals.

	Adjacent faces which normal difference is less or equal
	than max smoothing angle participate to the smoothed vertex
	normals.

	If the specified max smoothing angle is less or equal to
	zero, smoothing will not be done.

	If all adjacent faces either have normal difference more
	than the max smoothing angle or have equal normal, the face
	will remain Flat.

	This process calculates a normal for each vertex in the
	Face.

	If the existing Vertex has no normal set, the normal
	will set to existing Vertex.
	
	If the Vertex normal is already set to the same value, the
	Vertex will not be changed.

	If the Vertex has a different normal set it means that
	the Vertex is shared with some other Face which has already
	been processed. In this case a new Vertex will be created,
	and it will point to the old Vertex, or parent of the old
	Vertex, if it has such. The new normal will be set to the
	new Vertex.
*/
/*virtual*/ void Face::smooth( float max_smoothing_angle ){
	//  Face which has no normal calculated can not be smoothed
	//  Face normal is needed even if face is not smoothed
	if( isDisabled(EL_HAS_ELEMENT_NORMAL) ){
		makeNormal();
	}

	//  If the max smoothing angle is set to less or equal to zero,
	//  smoothing can not be applied.
	if( max_smoothing_angle <= 0 ){
		dmsg( M_MAT, "max_smoothing_angle <= 0 == %8.4f", max_smoothing_angle );
		enable ( EL_USE_ELEMENT_NORMAL );
		disable( EL_USE_VERTEX_NORMALS );
		return;
	}
	dmsg( M_MAT, "FACE SMOOTH" );

	int  flat_count   = 0;
	int  share_count  = 0;
	int  smooth_count = 0;
	bool flat         = true;
	int  vx_counter   = 0;

	//  For each vertex in the Face
	list<Vertex*>::iterator  v_it = vertices.begin();
	while( v_it != vertices.end() ){
		dmsg( M_MAT, "VERTEX SMOOTH %d", ++vx_counter );
		Vertex *old_vertex = *v_it;

		//  Make a new Vertex. We will add each normal of
		//  Faces that participate in the smoothing and
		//  normalize the normal in the end.
		Vertex *new_vertex = new Vertex( old_vertex );

		//  Set the normal of each vertex to the normal of this face in the start
		new_vertex->setNormal( this->getNormal() );

		//  For each other Face that use this Vertex,
		//  test the normal difference. On the way we
		//  also calculate the new normal the the new
		//  Vertex
		share_count  = 1;
		smooth_count = 0;
		flat_count   = 0;
		list<Face*>::iterator f_it = old_vertex->getFaces().begin();
		while( f_it != old_vertex->getFaces().end() ){
			Face *other = *f_it;

			//  Skip if same Face
			if( other == this ){
				f_it++;				
				continue;
			}

			//  Bad Face?
			if( other == NULL ){
				emsg( M_MAT, "NULL face in vertex cross-reference" );
				f_it++;
				continue;
			}

			//  The other face mtust have a normal as well
			if( other->isDisabled(EL_HAS_ELEMENT_NORMAL) ){
				other->makeNormal();
			}

			//  Calculate Face normal difference.
			//  We have earlier ensured that both Faces do have a normal.
			share_count++;
			Vector n1      = this ->getNormal();
			Vector n2      = other->getNormal();
			float  fn_ang  = (float)(  fabs( n1.angle(n2) )  );
			float  fn_diff = max_smoothing_angle - fn_ang;
            dmsg( M_MAT,
				"n2 = %8.4f, %8.4f, %8.4f",
				n2.v[0],
				n2.v[1],
				n2.v[2]
			);

			//  Is the enough different and not too much different?
			if( fn_ang > FACE_NORMAL_EPSILON && fn_diff > FLT_MIN ){
				new_vertex->addNormal( n2 );
				smooth_count++;
				//  If the face was considered flat earlier,
				//  we need to set normal to the vertices processed
				//  so far
				if( flat == true ){
					flat = false;

					Vector                  normal   = this->getNormal();
					list<Vertex*>::iterator v_it_fix = vertices.begin();
					if( v_it_fix != v_it ){
						Vertex *v = *v_it_fix;
						v->setNormal( normal );
						v_it_fix++;
					}
				}
			}else{  //  Otherwise it is too close or too different
				dmsg( 
					M_MAT, 
					"fn_ang = %8.4f fn_diff = %8.4f max = %8.4f", 
					fn_ang, 
					fn_diff, 
					max_smoothing_angle 
				);
				flat_count++;
			}
			f_it++;
		}

		dmsg( M_MAT, "a" );

		//  Finalize the new Vertex normal; normalize it
		new_vertex->normNormal();

		//  If the Face is not flat, we will need to store the new Vertex normal
//		if( flat == false ){
            dmsg( M_MAT,
				"smooth count = %ld flat count = %ld share_count = %ld ",
				smooth_count,
				flat_count,
				share_count
			);
			//  If the old Vertex has no normal, we can store the normal information there
			if( old_vertex->isDisabled(VX_HAS_NORMAL) ){
				old_vertex->setNormal( new_vertex->getNormal() );
                dmsg( M_MAT,
					"Old vertex %ld had no normal, setting it to (%.5f, %.5f, %.5f)",
					(unsigned long)(old_vertex),
					new_vertex->getNormal().v[0],
					new_vertex->getNormal().v[1],
					new_vertex->getNormal().v[2]
				);
				delete new_vertex;
			}else{
				//  If the old Vertex normal different, replace the
				//  Vertex in this Faces vertex list with the new Vertex
				//  This will not change the old Vertex, and other Faces'
				//  Vertex lists will not be changed.
				dmsg( M_MAT, "b" );
				Vector old_normal = old_vertex->getNormal();
				Vector new_normal = new_vertex->getNormal();
				float vn_ang;
				dmsg( M_MAT, "c" );
				if( 
					(old_normal.v[0] == new_normal.v[0]) &&
					(old_normal.v[1] == new_normal.v[1]) &&
					(old_normal.v[2] == new_normal.v[2])
				){
					vn_ang = 0.0;
				}else{
					dmsg( M_MAT, "d" );
					float da = old_normal | new_normal;
					if( da < (-1.0 + FACE_NORMAL_EPSILON) ){
						dmsg( M_MAT, "d1" );
						vn_ang = (float)M_PI;
					}else if( da > (1.0 - FACE_NORMAL_EPSILON) ){
						dmsg( M_MAT, "d2" );
						vn_ang = 0.0f;
					}else{
						dmsg( M_MAT, "d3a da = %20.10f", da );
						vn_ang = (float)(  fabs( acos(da) ) );
						dmsg( M_MAT, "d3b" );
					}
//					float dp = old_normal.angle( new_normal );
//					vn_ang = (float)(  fabs( dp )  );
					dmsg( M_MAT, "e" );
				}

				dmsg( M_MAT, "f" );
				if( vn_ang > FACE_NORMAL_EPSILON /*&& vn_diff > FLT_MIN*/ ){
                    dmsg( M_MAT,
						"Old vertex %ld had different %.5f normal, replacing with copy (%.5f, %.5f, %.5f)",
						old_vertex,
						vn_ang,
						new_vertex->getNormal().v[0],
						new_vertex->getNormal().v[1],
						new_vertex->getNormal().v[2]
					);
					//new_vertex->debug();
					*v_it = new_vertex;
				}else{
                    dmsg( M_MAT,
						"Old vertex %ld had the same normal %.5f",
						vn_ang,
						old_vertex
					);
					delete new_vertex;

				}
				dmsg( M_MAT, "g" );
				//  Otherwise, the old vertex has the same normal as the new
				//  vertex and we do nothing
			}
		/*}else{
			delete new_vertex;
		} */
		
		v_it++;
		dmsg( M_MAT, "h" );
	}


	dmsg( M_MAT, "if flat == false" );
	if( flat == false ){
		disable( EL_USE_ELEMENT_NORMAL );
		enable ( EL_USE_VERTEX_NORMALS );

		list<Vertex*>::iterator  v_it_check = vertices.begin();
		while( v_it_check != vertices.end() ){
			Vertex *check_vertex = *v_it_check;
			if( check_vertex->isDisabled(VX_HAS_NORMAL) ){
				check_vertex->debug();
				dmsg( M_MAT, "This smooth Face has Vertex with no normal!" );
			}
			v_it_check++;
		}
	}else{
		list<Vertex*>::iterator v_it_check = vertices.begin();
		while( v_it_check != vertices.end() ){
			Vertex *check_vertex = *v_it_check;
			check_vertex->setNormal( this->getNormal() );
/*			if( check_vertex->isDisabled(VX_HAS_NORMAL) ){
				check_vertex->debug();
				vert_debug_msg( "This smooth Face has Vertex with no normal!" );
			}*/
			v_it_check++;
		}

//?		v->disable( VX_USE_THIS_NORMAL | VX_USE_PARENT_NORMAL );
		enable( EL_HAS_ELEMENT_NORMAL | EL_USE_ELEMENT_NORMAL );
		//debug_msg( "This face is now FLAT" );
		//debug_msg( "This face is now SMOOTH" );
	}
	dmsg( M_MAT, "FACE SMOOTH DONE" );
}


#if 0
/*virtual*/ bool Face::stepCSGFace( GeometryIterator *gi ){
	return false;
}


/*virtual*/ void Face::fillCSGFace( GeometryIterator *gi, CSG_IFace *face ){
//	face->user_face_data        = 0;
//	face->user_face_vertex_data = 0;
	//face->vertex_index =
}
#endif


};  //  namespace Models
};  //  namespace Teddy



#if 0


// ** THIS IS A CODE SNIPPET WHICH WILL EFFICIEINTLY TRIANGULATE ANY
// ** POLYGON/CONTOUR (without holes) AS A STATIC CLASS.  THIS SNIPPET
// ** IS COMPRISED OF 3 FILES, TRIANGULATE.H, THE HEADER FILE FOR THE
// ** TRIANGULATE BASE CLASS, TRIANGULATE.CPP, THE IMPLEMENTATION OF
// ** THE TRIANGULATE BASE CLASS, AND TEST.CPP, A SMALL TEST PROGRAM
// ** DEMONSTRATING THE USAGE OF THE TRIANGULATOR.  THE TRIANGULATE
// ** BASE CLASS ALSO PROVIDES TWO USEFUL HELPER METHODS, ONE WHICH
// ** COMPUTES THE AREA OF A POLYGON, AND ANOTHER WHICH DOES AN EFFICENT
// ** POINT IN A TRIANGLE TEST.
// ** SUBMITTED BY JOHN W. RATCLIFF (jratcliff@verant.com) July 22, 2000

/**********************************************************************/
/************ HEADER FILE FOR TRIANGULATE.H ***************************/
/**********************************************************************/


#ifndef TRIANGULATE_H

#define TRIANGULATE_H

/*****************************************************************/
/** Static class to triangulate any contour/polygon efficiently **/
/** You should replace Vector2d with whatever your own Vector   **/
/** class might be.  Does not support polygons with holes.      **/
/** Uses STL vectors to represent a dynamic array of vertices.  **/
/** This code snippet was submitted to FlipCode.com by          **/
/** John W. Ratcliff (jratcliff@verant.com) on July 22, 2000    **/
/** I did not write the original code/algorithm for this        **/
/** this triangulator, in fact, I can't even remember where I   **/
/** found it in the first place.  However, I did rework it into **/
/** the following black-box static class so you can make easy   **/
/** use of it in your own code.  Simply replace Vector2d with   **/
/** whatever your own Vector implementation might be.           **/
/*****************************************************************/


#include <vector>  // Include STL vector class.

class Vector2d
{
public:
  Vector2d(float x,float y)
  {
    Set(x,y);
  };

  float GetX(void) const { return mX; };

  float GetY(void) const { return mY; };

  void  Set(float x,float y)
  {
    mX = x;
    mY = y;
  };
private:
  float mX;
  float mY;
};

// Typedef an STL vector of vertices which are used to represent
// a polygon/contour and a series of triangles.
typedef std::vector< Vector2d > Vector2dVector;


class Triangulate
{
public:

  // triangulate a contour/polygon, places results in STL vector
  // as series of triangles.
  static bool Process(const Vector2dVector &contour,
                      Vector2dVector &result);

  // compute area of a contour/polygon
  static float Area(const Vector2dVector &contour);

  // decide if point Px/Py is inside triangle defined by
  // (Ax,Ay) (Bx,By) (Cx,Cy)
  static bool InsideTriangle(float Ax, float Ay,
                      float Bx, float By,
                      float Cx, float Cy,
                      float Px, float Py);


private:
  static bool Snip(const Vector2dVector &contour,int u,int v,int w,int n,int *V);

};


#endif

/**************************************************************************/
/*** END OF HEADER FILE TRIANGULATE.H BEGINNING OF CODE TRIANGULATE.CPP ***/
/**************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "triangulate.h"

static const float EPSILON=0.0000000001f;

float Triangulate::Area(const Vector2dVector &contour)
{

  int n = contour.size();

  float A=0.0f;

  for(int p=n-1,q=0; q<n; p=q++)
  {
    A+= contour[p].GetX()*contour[q].GetY() - contour[q].GetX()*contour[p].GetY();
  }
  return A*0.5f;
}

   /*
     InsideTriangle decides if a point P is Inside of the triangle
     defined by A, B, C.
   */
bool Triangulate::InsideTriangle(float Ax, float Ay,
                      float Bx, float By,
                      float Cx, float Cy,
                      float Px, float Py)

{
  float ax, ay, bx, by, cx, cy, apx, apy, bpx, bpy, cpx, cpy;
  float cCROSSap, bCROSScp, aCROSSbp;

  ax = Cx - Bx;  ay = Cy - By;
  bx = Ax - Cx;  by = Ay - Cy;
  cx = Bx - Ax;  cy = By - Ay;
  apx= Px - Ax;  apy= Py - Ay;
  bpx= Px - Bx;  bpy= Py - By;
  cpx= Px - Cx;  cpy= Py - Cy;

  aCROSSbp = ax*bpy - ay*bpx;
  cCROSSap = cx*apy - cy*apx;
  bCROSScp = bx*cpy - by*cpx;

  return ((aCROSSbp >= 0.0f) && (bCROSScp >= 0.0f) && (cCROSSap >= 0.0f));
};

bool Triangulate::Snip(const Vector2dVector &contour,int u,int v,int w,int n,int *V)
{
  int p;
  float Ax, Ay, Bx, By, Cx, Cy, Px, Py;

  Ax = contour[V[u]].GetX();
  Ay = contour[V[u]].GetY();

  Bx = contour[V[v]].GetX();
  By = contour[V[v]].GetY();

  Cx = contour[V[w]].GetX();
  Cy = contour[V[w]].GetY();

  if ( EPSILON > (((Bx-Ax)*(Cy-Ay)) - ((By-Ay)*(Cx-Ax))) ) return false;

  for (p=0;p<n;p++)
  {
    if( (p == u) || (p == v) || (p == w) ) continue;
    Px = contour[V[p]].GetX();
    Py = contour[V[p]].GetY();
    if (InsideTriangle(Ax,Ay,Bx,By,Cx,Cy,Px,Py)) return false;
  }

  return true;
}

bool Triangulate::Process(const Vector2dVector &contour,Vector2dVector &result)
{
  /* allocate and initialize list of Vertices in polygon */

  int n = contour.size();
  if ( n < 3 ) return false;

  int *V = new int[n];

  /* we want a counter-clockwise polygon in V */

  if ( 0.0f < Area(contour) )
    for (int v=0; v<n; v++) V[v] = v;
  else
    for(int v=0; v<n; v++) V[v] = (n-1)-v;

  int nv = n;

  /*  remove nv-2 Vertices, creating 1 triangle every time */
  int count = 2*nv;   /* error detection */

  for(int m=0, v=nv-1; nv>2; )
  {
    /* if we loop, it is probably a non-simple polygon */
    if (0 >= (count--))
    {
      //** Triangulate: ERROR - probable bad polygon!
      return false;
    }

    /* three consecutive vertices in current polygon, <u,v,w> */
    int u = v  ; if (nv <= u) u = 0;     /* previous */
    v = u+1; if (nv <= v) v = 0;     /* new v    */
    int w = v+1; if (nv <= w) w = 0;     /* next     */

    if ( Snip(contour,u,v,w,nv,V) )
    {
      int a,b,c,s,t;

      /* true names of the vertices */
      a = V[u]; b = V[v]; c = V[w];

      /* output Triangle */
      result.push_back( contour[a] );
      result.push_back( contour[b] );
      result.push_back( contour[c] );

      m++;

      /* remove v from remaining polygon */
      for(s=v,t=v+1;t<nv;s++,t++) V[s] = V[t]; nv--;

      /* resest error detection counter */
      count = 2*nv;
    }
  }



  delete V;

  return true;
}


/************************************************************************/
/*** END OF CODE SECTION TRIANGULATE.CPP BEGINNING OF TEST.CPP A SMALL **/
/*** TEST APPLICATION TO DEMONSTRATE THE USAGE OF THE TRIANGULATOR     **/
/************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#include "triangulate.h"

void main(int argc,char **argv)
{

  // Small test application demonstrating the usage of the triangulate
  // class.


  // Create a pretty complicated little contour by pushing them onto
  // an stl vector.

  Vector2dVector a;

  a.push_back( Vector2d(0,6));
  a.push_back( Vector2d(0,0));
  a.push_back( Vector2d(3,0));
  a.push_back( Vector2d(4,1));
  a.push_back( Vector2d(6,1));
  a.push_back( Vector2d(8,0));
  a.push_back( Vector2d(12,0));
  a.push_back( Vector2d(13,2));
  a.push_back( Vector2d(8,2));
  a.push_back( Vector2d(8,4));
  a.push_back( Vector2d(11,4));
  a.push_back( Vector2d(11,6));
  a.push_back( Vector2d(6,6));
  a.push_back( Vector2d(4,3));
  a.push_back( Vector2d(2,6));

  // allocate an STL vector to hold the answer.

  Vector2dVector result;

  //  Invoke the triangulator to triangulate this polygon.
  Triangulate::Process(a,result);

  // print out the results.
  int tcount = result.size()/3;

  for (int i=0; i<tcount; i++)
  {
    const Vector2d &p1 = result[i*3+0];
    const Vector2d &p2 = result[i*3+1];
    const Vector2d &p3 = result[i*3+2];
    printf("Triangle %d => (%0.0f,%0.0f) (%0.0f,%0.0f) (%0.0f,%0.0f)\n",i+1,
    p1.GetX(),p1.GetY(),p2.GetX(),p2.GetY(),p3.GetX(),p3.GetY());
  }

}


#endif

