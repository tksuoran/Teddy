
/*
	TEDDY - General graphics application library
	Copyright (C) 1999-2002  Timo Suoranta
	tksuoran@cc.helsinki.fi

		Adapted from

		3DC - http://www.on-the-web.ch/3dc/
		Copyright (C) 2000  Martin Herren
		sputnik@on-the-web.ch

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

	$Id: FaceSurface.cpp,v 1.1 2002/02/16 12:41:39 tksuoran Exp $
*/


#if 0
#include "gts.h"
#include "Teddy/Models/Face.h"
#include "Teddy/ColDet/ColDet.h"
#include <cassert>


namespace Teddy  {
namespace Models {


void util_prepend( gpointer data, GSList **lst ){
	*lst = g_slist_prepend( *lst, data );
}


void util_prepend_glist( gpointer data, GList **lst ){
	*lst = g_list_prepend( *lst, data);
}


GList *util_gslist2glist( GSList *gslist ){
	GList *glist = NULL;

	while( gslist ){
		glist  = g_list_append( glist, gslist->data );
		gslist = gslist->next;
	}

	return glist;
}


GSList *util_glist2gslist( GList *glist ){
	GSList *gslist = NULL;
	
	while( glist ){
		gslist = g_slist_append( gslist, glist->data );
		glist  = glist->next;
	}
	
	return gslist;
}


//!  returns a GSList with all the GtsVertices from the GtsEdges
GSList *util_edges_get_vertices( GSList *edges ){
	GtsEdge *e        = NULL;
	GSList  *p        = edges;
	GList   *lst      = NULL;  // dummy list needed by gts_vertices_merge()
	GSList  *vertices = NULL;
	
	while( p ){
		e = (GtsEdge *)p->data;
		vertices = g_slist_append( vertices, e->segment.v1 );
		vertices = g_slist_append( vertices, e->segment.v2 );
		p = p->next;
	}
	
	printf( "gtsExt_edges_get_vertices: vertices: %i", g_slist_length(vertices) );
	lst = util_gslist2glist( vertices );
	g_slist_free( vertices );
	vertices = NULL;
	lst      = gts_vertices_merge( lst, 0 );
	vertices = util_glist2gslist ( lst );
	g_list_free( lst );
	printf( " -> %i\n", g_slist_length(vertices) );
	
	return vertices;
}


bool aligned( GtsVertex *v1, GtsVertex *v2, GtsVertex *v3 ){
	double x1;
	double x2;
	double y1;
	double y2;
	double z1;
	double z2;
	double x;
	double y;
	double z;

	x1 = (v2->p.x - v1->p.x);
	y1 = (v2->p.y - v1->p.y);
	z1 = (v2->p.z - v1->p.z);
	x2 = (v3->p.x - v1->p.x);
	y2 = (v3->p.y - v1->p.y);
	z2 = (v3->p.z - v1->p.z);
	x  = y1 * z2 - z1 * y2;
	y  = z1 * x2 - x1 * z2;
	z  = x1 * y2 - y1 * x2;

	return (x == 0) && (y == 0) && (z == 0) ? true : false;
}


//!  Creates the transformation-matrix of the vertex-list
GtsMatrix *get_matrix( GSList *v ){
	GtsVertex   *v1;
	GtsVertex   *v2;
	GtsVertex   *v3;
	GtsEdge     *e1;
	GtsEdge     *e2;
	GtsEdge     *e3;
	GtsTriangle *t;
	GtsMatrix   *m;
  
	if( !v || (g_slist_length(v) < 3) ){
		return NULL;
	}

	//  Getting the first 3 vertices
	v1 = (GtsVertex*)v->data;  //  Getting the first vertex
	v  = v->next;
	v2 = (GtsVertex*)v->data;  //  Getting the second vertex
	v  = v->next;
	
	//  Letting vertices point to the first
	//  vertex which is not colinear with v2 and v2
	while( v && aligned(v1, v2, (GtsVertex *)v->data) ){
		v = v->next;
	}
	if( !v ){
		return NULL;
	}

	//  Now we found our 3rd vertex
	v3 = (GtsVertex*)v->data; 
	
	//  Building the 3 edges
	e1 = gts_edge_new( gts_edge_class(), v1, v2 );
	e2 = gts_edge_new( gts_edge_class(), v2, v3 );
	e3 = gts_edge_new( gts_edge_class(), v3, v1 );
	
	//  Building the reference triangle and the matrix
	t = gts_triangle_new( gts_triangle_class(), e1, e2, e3 );
	m = gts_matrix_projection( t );
	
	//  Destroying the reference triangle
	gts_allow_floating_vertices = TRUE;
	gts_object_destroy( (GtsObject *) t );
	gts_allow_floating_vertices = FALSE;
	
	//  and good-bye
	return m;
}


/*!
	Returns a GSList containing all faces of surface which
	have <em>all</em> their vertices in the vertice list
*/
GSList *faces_in_vertices( GtsSurface *s, GSList *v ){
	GSList *t = NULL;  //  GSList with all the triangles of the surface s
	GSList *p = NULL;  //  Pointer used to parse t
	GSList *f = NULL;  //  List of faces to be returned

	gts_surface_foreach_face( s, (GtsFunc) util_prepend, &t );
	p = t;

	while( p ){
		GtsVertex *v1=NULL, *v2=NULL, *v3=NULL;
		
		gts_triangle_vertices( (GtsTriangle*)p->data, &v1, &v2, &v3 );
		if( g_slist_find(v, v1) && g_slist_find(v, v2) && g_slist_find(v, v3) ){
			f = g_slist_append( f, p->data );
		}
		p = p->next;
	}

	g_slist_free( t );
	return f;
}


/*!
	\brief Return the triangulated surface of an OBJECT_POLY
	\bug removes too many triangles in non-convex holes

	An OBJECT_POLY is defined by a GSList containing 1 or more GSLists of vertices,
	the first of these GSList contains the vertices of the outer-polygons,
	the following (if they exist) are the vertices of the hole-polygons
*/
GtsSurface *triangulate_polygon( GSList *polygons ){
	GSList      *p = NULL;   //  a pointer to a polygon (GSList of vertices), used in loops
	GSList      *v = NULL;   //  a pointer to a vertex
	GList       *g = NULL;   //  a pointer to a GList, needed for gts_XXXX_merge
	GtsTriangle *t = NULL;   //  a triangle, needed to build the enclosing triangle
	GtsVertex   *v1;         //  the vertices of the enclosing triangle,
	GtsVertex   *v2;         //  needed for its destruction
	GtsVertex   *v3;

	//  The returned triangulated surface
	GtsSurface *s = gts_surface_new(
		gts_surface_class(),  
		gts_face_class(),
		gts_edge_class(),
		gts_vertex_class()
	);

	//  The transformation matrix and its inverse
	GtsMatrix *m   = NULL;  
	GtsMatrix *m_i = NULL;

	if( polygons==NULL ){
		return NULL;
	}

	//  v points to the first vertex list in polygons, which is the outer polygon
	v = (GSList*)polygons->data;

	if( !v || (g_slist_length(v) < 3) ){
		return NULL;
	}

	m = get_matrix( v );
	if( m==NULL ){
		return NULL;
	}
	m_i = gts_matrix_inverse( m );

	//  Rotates all vertices in the xy-plane
	p = polygons;
	while( p ){
		v = (GSList*)p->data;
		while( v ){
			gts_point_transform( (GtsPoint*)v->data, m_i );
			v = v->next;
		}
		p = p->next;
	}

	//  Creating the enclosing triangle of the outer boundary
	//  and adding it as first face to the surface s
	v = (GSList*)polygons->data;
	t = gts_triangle_enclosing( gts_triangle_class(), v, 100.0 );
	gts_surface_add_face(
		s,
		gts_face_new(
			gts_face_class(),
			t->e1,
			t->e2,
			t->e3
		)
	);

	//  Adding all vertices to the surface s
	p = polygons;
	while( p ){
		v = (GSList*)p->data;
		while( v ){
			assert(
				gts_delaunay_add_vertex(
					s,
					(GtsVertex*)v->data,
					NULL
				) == 0
			);
			v = v->next;
		}
		p = p->next;
	}

	/*   gts_surface_foreach_vertex(s, (GtsFunc) util_prepend_glist, &g); */
	/*   g = gts_vertices_merge(g, 0); */
	/*   g_list_free(g); */
	
	//  Now t can be destroyed
	gts_triangle_vertices( t, &v1, &v2, &v3 );
	gts_allow_floating_vertices = TRUE;
	gts_object_destroy( (GtsObject*)v1 );
	gts_object_destroy( (GtsObject*)v2 );
	gts_object_destroy( (GtsObject*)v3 );
	gts_allow_floating_vertices = FALSE;
	
	//  Adding the segments between consecutive vertices as constraints
	//  to the surface s
	p = polygons;
	while( p ){
		v = (GSList*)p->data;
		while( v ){

			//  If this isn't the last vertex, adds the edge to the next vertex
			if( v->next ){
				//  No test is made if the vertex was added succesfully
				gts_delaunay_add_constraint(
					s,
					(GtsConstraint *)gts_edge_new(
						(GtsEdgeClass *)gts_constraint_class(),
						(GtsVertex*)v->data,
						(GtsVertex*)v->next->data
					)
				);

			//  Here we got the last vertex, adds the edge to the first vertex
			}else{  
				//  No test is made if the constraint was added succesfully
				gts_delaunay_add_constraint(
					s,
					(GtsConstraint *)gts_edge_new(
						(GtsEdgeClass *)gts_constraint_class(),
						(GtsVertex*)v->data,
						(GtsVertex*)( ((GSList *)p->data)->data )
					)
				);
			}
			v = v->next;
		}
		p = p->next;
	}

	//  Cleaning up the surface... needed by gts_delaunay_remove_hull
	g = NULL;
	gts_surface_foreach_edge( s, (GtsFunc)util_prepend_glist, &g );
	g = gts_edges_merge( g );
	g_list_free( g );

	//  Remove the hull
	gts_delaunay_remove_hull( s );

#	if 0
	//  Removing the faces in the holes
	//  p points to the first vertex-list representing a hole
	p = polygons->next;
	while( p ){
		//  Here v is the face-list of the faces needing to be removed
		v = faces_in_vertices( s, (GSList*)p->data );
		g_slist_foreach( v, (GFunc)gts_object_destroy, NULL );
		p = p->next;
	}
#	endif

	//  Rotates all points back
	p = polygons;
	while( p ){
		v = (GSList*)p->data;
		while( v ){
			gts_point_transform( (GtsPoint*)v->data, m );
			v = v->next;
		}
		p = p->next;
	}

	return s;
}


/*!
	\brief Face add to collision model
	\todo  Tesselate polygons which have move points than three
*/
/*virtual*/ GtsSurface *Face::makeSurface(){

	//  1: Transform vertices so that they lie on x,y,0 plane. Then 
	//  2: Use Gts Delaunay triangulation adding all face vertices
	//  3: Transfrom vertices back to original orientation
	
	return NULL;
}


};  //  namespace Models
};  //  namespace Teddy


#endif


