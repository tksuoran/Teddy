
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


#ifndef TEDDY__TEDDY_H
#define TEDDY__TEDDY_H


/***********************************************************************************/
/*!


\mainpage Teddy Reference Manual


\section section_quick_access Quick access to Teddy resources


<ul>
<li><a href="http://teddy.sourceforge.net">Teddy homepage</a>
<li><a href="https://sourceforge.net/cvs/?group_id=40550">Teddy CVS</a>
<li><a href="https://sourceforge.net/project/showfiles.php?group_id=40550">Teddy Sourceforge file releases</a>
<li><a href="http://www.cs.helsinki.fi/u/tksuoran/">Teddy <em>beta</em> file releases</a>
</ul>

This is early development version of %Teddy.

%Teddy is a 3D graphics library.
It implements a simple windowing system and a simple scene
graph. Multiple camera windows, cameras and scenes can be
created with %Teddy.

I am working alone on %Teddy at the moment. If you would
like to join to help me with the development, I will be
happy to receive e-mail from you. Also mail me if you
have comments or suggestions.


\section section_getting_started Getting started guide to Teddy


<ul>
<li>\ref page_environment
<li>\ref page_registering
<li>\ref page_getting
<li>\ref page_cvs_support
<li>\ref page_build_process
<li>\ref page_coding_conventions
<li>\ref page_design
<li>\ref page_status
<li>\ref page_history
</ul>


\section section_reference Reference


See namespaces and class hierarhy and the section below for a really brief introduction
which explains how to get something drawn with Teddy.


\section section_drawing Drawing something with Teddy


To get something drawn, you must have a model that you want to show.             
Currently there are two easy ways to make a model. The first way is to           
create an instance of one of the primitive models which are included in          
the Teddy/Models directory. Not all classes there are primitives, so this        
can be a bit confusing. Well, at least Box annd Sphere are such primitive        
models.                                                                          
                                                                                 
You can not display single Model alone directly. Instead you must have a         
Scene, which is a collection of Models. Create a scene and add the model         
to it. Now you can display the scene.                                            
                                                                                 
Between right here you need to care about position and orientation of each       
Model in the Scene, but I'll skip it with this notice. Maybe later               
something more.                                                                  
                                                                                 
The next thing is that to display the scene you need to have a camera            
which is somewhere in (or relative) to your scene. The camera is similar         
to models of scene: it too has position and orientation. Additionally it         
can spesify the field of vision.                                                 
                                                                                 
At this point we know what things we want to show and from where we want         
to show them. Still we need to decide where we 'project' the scene. Most         
of the time this is the computer display in fullscreen or full window            
mode, but Teddy is a bit more complex. With Teddy you can show multiple          
scenes and cameras in the same fullscreen or window. Thus you must create        
a Projection. Then you can make the Projection to show some camera.              
                                                                                 
The projection must be added to a Layer in Teddy. The Layer is something
useless, but you must have one created and connected to WindowManger.            
WindowManager is the root of all drawing and event handling in teddy.            
                                                                                 
The Scene class contains the current 'scene management', which is very           
little currently. I am planning to add octrees and other things later, but       
I am not going to make such things until integration with flatfour.              
                                                                                 
The drawing of the scene is probably the next thing you might be                 
interested in. Like previosuly mentioned, WindowManager is root of all           
drawing. It loops a simple code blok like { drawFrame(); processEvents(); }      
The drawFrame() part calls drawing for each layer. Like I said the layer         
is stupid and might be removed later. Might.                                     
                                                                                 
Each layer again contains a set of Projections and a set of Areas.               
Projections are 3D stuff, Areas are 2D stuff. Strictly speaking Projection       
is derived from Area, so it is an Area.. Anyway, the further part goes           
like something like this:                                                        
                                                                                 
Each projection hshould have a camera connected to it. Otherwise the             
Projection will not show anything. Projection draws itself by telling the        
connected Camera to 'draw yourself to me' where 'yourself' is the camera         
and 'me' is the projection.                                                      
                                                                                 
At this point Camera hopes that it is connected to some scene. Each camera       
has a transformation (you can safely think it as transformation matrix,          
even though it is implemented as vector for position and quaternion for          
orientation) like any other model. The camera draws itself by first              
updating the camera matrix and then telling the connected scene to 'draw         
yourself to me' where 'yourself' is the scene and 'me' is the scene.           

The scene is simply a collection of models (okay there are lights too, at        
this point I skip them) and scene draws itself simply by telling each            
model to draw themselves to the camera which scene received as an argument       
for the drawing operation.                                                       
                                                                                 
Now we are at the point where single model is being told 'draw yourself to       
camera x'. When this happens, the model asks the camera what is the              
projection it is connected to. This is done so that the model and the            
projection can negotiate for the materials really used for the drawing.          
This works in the way that the model asks projection to apply model              
materials. The Projection then has the ultimate control to choose which          
material it actually applies. It can also save some time if it notices           
that the previous model used the very same material, and nothing needs to        
be done.                                                                         
                                                                                 
Hmm, actually, before the material apply happens the model asks the camera       
if the model is withing the viewing frustum. And even before that the            
model asks camera to apply the model transformation. The camera does this        
by concatenating the models' localToWorld() matrix with the cameras              
worldToLocal() matrix. As result the vertices from the models localc             
coordinates system are transformed into the local coordinate system of the       
camera.                                                                          
                                                                                 
After the modelview transformation matrix has been set, and the model has        
been tested for view frustum intersection (means visibility) and the             
material has been applied the model simply draws itself by drawing its           
Geometry. Each model has one transformation, material and geometry.              
Transformation and material are used as described above. Geometry is             
collection of Elements. Element is, for example, a trianglestrip                 
(GL_TRIANGLE_STRIP) - TriangleStrip is derived from Element and it is            
nothing more than a set of vertices.                                             
                                                                                 
Now you finally get properly trasformed and 'materialized' vertices drawn        
to the display as part of some opengl primitives - triangles or quads most       
of the time :)                                                                   

Things are sligtly more complex when you want to use the same shape in 
multiple model instances in the scene. In such case you should have one
Model which has the shape but which is not part of the scene, and then you
have two more models, which do not have geometry but which instead have
the first model as 'child'. There is a more detail example about this in the
documentation for the Teddy::Models namespace.

 *********************************************************************************/


/*********************************************************************************/
/*! \page page_teddy_license Teddy license
 *********************************************************************************/

/*********************************************************************************/
/*! \page page_people Teddy developers

The core of %Teddy is being written by Timo Suoranta.
Fabrice Bellard wrote TinyGL.
Amir Geva wrote ColDet.

 *********************************************************************************/


#endif  //  TEDDY__TEDDY_H

