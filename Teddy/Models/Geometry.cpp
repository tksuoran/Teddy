
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

	$Id: Geometry.cpp,v 1.7 2002/02/16 12:41:39 tksuoran Exp $
*/


#include "Teddy/TeddyConfig.h"
#include "Teddy/Graphics/Device.h"
#include "Teddy/Models/Element.h"
#include "Teddy/Models/Geometry.h"
#include "Teddy/SysSupport/Messages.h"
using namespace Teddy::SysSupport;


namespace Teddy  {
namespace Models {


int Geometry::draw_count = 0;


//!  Constructor
Geometry::Geometry(){
	gl_list_id = glGenLists( 1 );
	dirty      = true;
}


//!
void Geometry::beginUpdate( Projection *p ){
	glNewList( gl_list_id, GL_COMPILE );
}


//!
void Geometry::endUpdate( Projection *p ){
	glEndList();
	dirty = false;
}


//!
void Geometry::draw( Projection *p ){
	Geometry::draw_count++;
	if( dirty==true ){
		beginUpdate ( p );
		drawElements( p );
		endUpdate   ( p );
	}
	if( dirty==false ){
		glCallList( gl_list_id );
	}
}


void Geometry::clearTraversal(){
	list<Element*>::const_iterator e_it = elements.begin();
	while( e_it!=elements.end() ){
		(*e_it)->clearTraversal();
		e_it++;
	}
}

//!
void Geometry::transformVertices( const Matrix &m, const Matrix &normal_matrix, const bool reverse ){
	list<Element*>::const_iterator e_it = elements.begin();
	while( e_it!=elements.end() ){
		(*e_it)->transformVertices( m, normal_matrix, reverse );
		e_it++;
	}
	dirty = true;
}


//!
double Geometry::getMaxVector(){
	double max_len = 0;
	list<Element*>::const_iterator e_it = elements.begin();
	while( e_it!=elements.end() ){
		double len = (*e_it)->getMaxVector();
		if( len > max_len ){
			max_len = len;
		}
		e_it++;
	}
	return max_len;
}


/*!
	\brief Destructor
	\bug   remove display list
*/
Geometry::~Geometry(){
#if !defined( USE_TINY_GL )
	glDeleteLists( gl_list_id, 1 );
#endif
}

//!  Insert Element to Model
/*!
	\brief Insert Element to Model
	\param e Element which is added to this Model
*/
void Geometry::insert( Element *e ){
	elements.push_back( e );
}


/*!
	\brief Code to be executed before visiting elements in the Model for drawing
	\param p Projection Area to which this mesh is being drawn
*/
/*virtual*/ void Geometry::beginElements( Projection *p ){
}


/*!
	\brief Code to visit elements in the Geometry for drawing
	\param p Projection Area to which this Geometry is being drawn
*/
/*virtual*/ void Geometry::drawElements( Projection *p ){
	beginElements( p );

	list<Element*>::const_iterator e_it = elements.begin();
	while( e_it!=elements.end() ){
		(*e_it)->draw( p );
		e_it++;
	}

	endElements( p );
}


/*!
	\brief Code to be executed after visiting elements in the Geometry for drawing
	\param p Projection Area to which this mesh is being drawn
*/
/*virtual*/ void Geometry::endElements( Projection *p ){
}


/*!
	\brief   Average shared normals for vertices
	\warning This method is not recursive
	\param   max_smoothing angle The maximum angle between faces which vertices will participate the smoothing
	\bug     Check type (either degrees or radians) for max_smoothing_angle
*/
void Geometry::smooth( float max_smoothing_angle ){
	list<Element*>::iterator  e_it;
	Element                  *element;
	int                       element_smooth = 0;
	int pos = 0;

	//  For each Face element, smooth it.
	dmsg( M_MAT, "Geometry::smooth(). Elements to be smoothed: %d", elements.size() );
	e_it = elements.begin();
	while( e_it != elements.end() ){
		element = (*e_it);
		if( element != NULL ){
			dmsg( M_MAT, "1" );
			element->smooth( max_smoothing_angle );
			dmsg( M_MAT, "2" );
			element_smooth++;
		}else{
			emsg( M_MAT, "NULL element in Geometry::smooth" );
		}
		dmsg( M_MAT, "Next element %d", ++pos );
		e_it++;
	}

	dmsg( M_MAT, "Elements smoothed: %d", element_smooth );
}














#if 0


class GeometryIterator {
public:
    GeometryIterator( Geometry *g ){
        geometry = g;
        e_it = g->geometry->
    }
    int  faceItDone   (){
        // NO-OP
    }

    void faceItFill   ( CSG_IFace *face ){
        e_it->csgFill( face );
    }

    void faceItStep   (){
        bool same_element = e_it->csgStep();
        if( same_element == false ){
            e_it++;
            e_it->csgPrepare();
        }
    }
    void faceItReset  (){

    }
    int  vertexItDone ();
    void vertexItFill ( CSG_IVertex *face );
    void vertexItStep ();
    void vertexItReset();

protected:
    Geometry                  *geometry;  //  what geometry
    list<Element*>::iterator   e_it;      //  what element  -> face
    list<Vertex*> ::iterator   v_it;
};


/*
typedef struct  {
    int    vertex_index[4];
    int    vertex_number;

    void  *user_face_vertex_data[4];
    void  *user_face_data;
} CSG_IFace;
typedef struct  {
    float position[3];
} CSG_IVertex;
*/

bool ObjectManager::csg(){

    // Create a boolean operation handle
    CSG_BooleanOperation *operation = CSG_NewBooleanFunction();
    if( operation == NULL ){
        // deal with low memory exception
        return;
    }

    // Describe each mesh operand to the module.
    // NOTE: example properties!
    CSG_MeshPropertyDescriptor propA;
    CSG_MeshPropertyDescriptor propB;
    propA.user_data_size        = 0;
    propA.user_face_vertex_data = 0;
    propB.user_data_size        = 0;
    propB.user_face_vertex_data = 0;

    // Get the output properties of the mesh.
    CSG_MeshPropertyDescriptor output_properties = CSG_DescibeOperands( operation, propA, propB );

    // Report to the user if they will loose any data!
    ...;

    // Get some mesh iterators for your mesh data structures
    CSG_FaceIteratorDescriptor   face_it_desc;
    CSG_VertexIteratorDescriptor vertex_it_desc;
    face_it_desc  .it           = NULL;
    face_it_desc  .Done         = FaceItDone;
    face_it_desc  .Fill         = FaceItFill;
    face_it_desc  .Step         = FaceItStep;
    face_it_desc  .Reset        = FaceItReset;
    face_it_desc  .num_elements = 0;
    vertex_it_desc.it           = NULL;
    vertex_it_desc.Done         = VertexItDone;
    vertex_it_desc.Fill         = VertexItFill;
    vertex_it_desc.Step         = VertexItStep;
    vertex_it_desc.Reset        = VertexItReset;
    vertex_it_desc.num_elements = 0;

    CSG_FaceIteratorDescriptor   obA_faces = ...;
    CSG_VertexIteratorDescriptor obA_verts = ...;

    // same for object B
    CSG_FaceIteratorDescriptor   obB_faces = ...;
    CSG_VertexIteratorDescriptor obB_verts = ...;

    // perform the operation...!

    int success = CSG_PerformBooleanOperation( operation, e_csg_intersection, obA_faces, obA_vertices, obB_faces, obB_vertices );

    // if the operation fails, report miserable failure to user
    // and clear up data structures.
    if( !success ){
        ...;
        CSG_FreeBooleanOperation( operation );
        return;
    }

    // read the new mesh vertices back from the module
    // and assign to your own mesh structure.

    // First we need to create a CSG_IVertex so the module can fill it in.
    CSG_IVertex vertex;
    CSG_VertexIteratorDescriptor *verts_it = CSG_OutputVertexDescriptor( operation );

    // initialize your vertex container with the number of verts (verts_it->num_elements)

    while( !verts_it->Done(verts_it->it) ){
        verts_it->Fill( verts_it->it, &vertex );

        // create a new vertex of your own type and add it
        // to your mesh structure.

        verts_it->Step( verts_it->it );
    }
    // Free the vertex iterator
    CSG_FreeVertexDescriptor( verts_it );
  
    // similarly for faces.
    CSG_IFace face;

    // you may need to reserve some memory in face->user_data here.

    // initialize your face container with the number of faces (faces_it->num_elements)

    CSG_FaceIteratorDescriptor *faces_it = CSG_OutputFaceDescriptor( operation );
    while( !faces_it->Done(faces_it->it) ){
        faces_it->Fill( faces_it->it, &face );

        // create a new face of your own type and add it
        // to your mesh structure.
        faces_it->Step( &faces_it->it );
    }

    // Free the face iterator
    CSG_FreeVertexDescriptor( faces_it );

    // that's it free the operation.
    CSG_FreeBooleanOperation( operation );
    return;
}
















/*
 * CSG_IFace -- an interface polygon structure.
 *
 * vertex_index    is a fixed size array of 4 elements containing indices into
 *                 an abstract vertex container. 3 or 4 of these elements may be used to
 *                 describe either quads or triangles.
 * vertex_number   is the number of vertices in this face - either 3 or 4.
 * vertex_colors   is an array of {r,g,b} triplets one for each vertex index.
 * tex_coords      is an array of {u,v} triplets one for each vertex index.
 * user_data       is a pointer to arbitary data of fixed width,
 *                 this data is copied around with the face, and duplicated if a face is
 *                  split. Contains things like material index.
 */

typedef struct  {
    int    vertex_index[4];
    int    vertex_number;

    void  *user_face_vertex_data[4];
    void  *user_face_data;
} CSG_IFace;


typedef struct  {
    float position[3];
} CSG_IVertex;


/* Descibes the data stored in a mesh available through the
 * CSG_IFace interface.
 *
 * user_data_size              is the number of bytes of user_data associated with each CSG_IFace
 * user_face_vertex_data_size  is the number of bytes of user data associated with
 *                             every face vertex tuple.
 */

typedef struct CSG_MeshPropertyDescriptor{
    unsigned int user_face_vertex_data_size;
    unsigned int user_data_size;
} CSG_MeshPropertyDescriptor;



/* The iterator is used in the following manner.
 * 
 *   MyIterator *iterator = ...
 *   DataType    data;
 * 
 *   while (!IsDone(iterator)) {
 *		Fill(iterator,&data);
 *		//process information pointed to by data 
 *		...
 *		Step(iterator);
 *	 } 
 * 
 * The CSG module does not want to know about the implementation of these
 * functions  so we use the c function ptr mechanism to hide them. Our
 * iterator descriptor now looks like this.
 */

typedef void * CSG_IteratorPtr;
typedef int  (*CSG_FaceItDoneFunc )(CSG_IteratorPtr it);
typedef void (*CSG_FaceItFillFunc )(CSG_IteratorPtr it,CSG_IFace *face);
typedef void (*CSG_FaceItStepFunc )(CSG_IteratorPtr it);
typedef void (*CSG_FaceItResetFunc)(CSG_IteratorPtr it);


//  Similarly to walk through the vertex arrays we have.
typedef int  (*CSG_VertexItDoneFunc )(CSG_IteratorPtr it);
typedef void (*CSG_VertexItFillFunc )(CSG_IteratorPtr it,CSG_IVertex *face);
typedef void (*CSG_VertexItStepFunc )(CSG_IteratorPtr it);
typedef void (*CSG_VertexItResetFunc)(CSG_IteratorPtr it);

typedef struct CSG_VertexIteratorDescriptor {
    CSG_IteratorPtr        it;
    CSG_VertexItDoneFunc   Done;
    CSG_VertexItFillFunc   Fill;
    CSG_VertexItStepFunc   Step;
    CSG_VertexItResetFunc  Reset;
    unsigned int           num_elements;
} CSG_VertexIteratorDescriptor;

/* The actual iterator structures are not exposed to the CSG module, they
 * will contain datatypes specific to blender. */

/* The functions below are to be used in the following way:
 * 
 *  // Create a boolean operation handle
 *  CSG_BooleanOperation *operation = CSG_NewBooleanFunction();
 *  if (operation == NULL) {
 *     // deal with low memory exception
 *  }
 *
 *  // Describe each mesh operand to the module.
 *  // NOTE: example properties!
 *  CSG_MeshPropertyDescriptor propA,propB;
 *  propA.user_data_size = 0;
 *  propA.user_face_vertex_data = 0;
 *  propB.user_face_vertex_data = 0;
 *  propB.user_data_size = 0;
 *
 *  // Get the output properties of the mesh.
 *  CSG_MeshPropertyDescriptor output_properties;
 *  output_properties = CSG_DescibeOperands(
 *    operation,
 *    propA,
 *    propB
 *  );
 * 
 *  // Report to the user if they will loose any data!
 *  ...
 * 
 *  // Get some mesh iterators for your mesh data structures
 *  CSG_FaceIteratorDescriptor obA_faces = ...
 *  CSG_VertexIteratorDescriptor obA_verts = ...
 *  
 *  // same for object B
 *  CSG_FaceIteratorDescriptor obB_faces = ...
 *  CSG_VertexIteratorDescriptor obB_verts = ...
 *  
 *  // perform the operation...!
 *
 *  int success = CSG_PerformBooleanOperation(
 *     operation,
 *     e_csg_intersection,
 *     obA_faces,
 *     obA_vertices,
 *     obB_faces,
 *     obB_vertices
 *  );
 *
 *  // if the operation fails report miserable failure to user
 *  // and clear up data structures.
 *  if (!success) {
 *    ...
 *    CSG_FreeBooleanOperation(operation);
 *    return;
 *  }
 *
 *  // read the new mesh vertices back from the module
 *  // and assign to your own mesh structure.
 *
 *  // First we need to create a CSG_IVertex so the module can fill it in.
 *  CSG_IVertex vertex;
 *  CSG_VertexIteratorDescriptor * verts_it = CSG_OutputVertexDescriptor(operation);
 *
 *  // initialize your vertex container with the number of verts (verts_it->num_elements)
 * 
 *  while (!verts_it->Done(verts_it->it)) {
 *		verts_it->Fill(verts_it->it,&vertex);
 *
 *      // create a new vertex of your own type and add it
 *      // to your mesh structure.
 *      verts_it->Step(verts_it->it);
 *  }
 *  // Free the vertex iterator
 *	CSG_FreeVertexDescriptor(verts_it);
 * 
 *  // similarly for faces.
 *  CSG_IFace face;
 *
 *  // you may need to reserve some memory in face->user_data here.
 * 
 *  // initialize your face container with the number of faces (faces_it->num_elements)
 * 
 *  CSG_FaceIteratorDescriptor * faces_it = CSG_OutputFaceDescriptor(operation);
 * 
 *  while (!faces_it->Done(faces_it->it)) {
 *		faces_it->Fill(faces_it->it,&face);
 *
 *      // create a new face of your own type and add it
 *      // to your mesh structure.
 *      faces_it->Step(&faces_it->it);
 *  }
 *	
 *  // Free the face iterator
 *	CSG_FreeVertexDescriptor(faces_it);
 *
 *  // that's it free the operation.
 *
 *  CSG_FreeBooleanOperation(operation);
 *  return;
 *  
 */

/**
 * Description of boolean operation type.
 */

typedef enum {
	e_csg_union,
	e_csg_intersection,
	e_csg_difference,
	e_csg_classify
} CSG_OperationType;

/**
 * 'Handle' into the CSG module that identifies a particular CSG operation.
 *  the pointer CSG_info containers module specific data, and should not
 *  be touched in anyway outside of the module.
 */

typedef struct {
	void *CSG_info;
} CSG_BooleanOperation;

/**
 * Return a ptr to a CSG_BooleanOperation object allocated
 * on the heap. The CSG module owns the memory associated with 
 * the returned ptr, use CSG_FreeBooleanOperation() to free this memory.
 */
	CSG_BooleanOperation * 
CSG_NewBooleanFunction(
	void
);


#endif





};  //  namespace Models
};  //  namespace Teddy


