
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

	$Id: doc_page_design.h,v 1.4 2002/03/12 10:46:07 tksuoran Exp $
*/


/*********************************************************************************/
/*! \page page_design Introduction to Teddy design and directory tree

\section section_why Why yet another scene graph library?

%Teddy started as my first OpenGL program, and I learned OpenGL
while writing and designing %Teddy.

I quickly found out that OpenGL was a low level graphics library.
OpenGL does not have concepts of camera or model. OpenGL deals with
very low level primitives like points, lines and polygons only. OpenGL
also does not have direct way to setup graphics contexts, and multiple
window management is out of the scope of OpenGL.

What I needed was a scene graph library. Scene graph introduces
concepts such as camera, model and an instance of a model. That time
I could have chosen some existing scene graph library. I did have a
look at a few scene graph libraries. What I found out that they were
not documented very well, and that most of them were specialized to
special kind of scene graph. Quake level viewers were quite popular
at that time. They work well with interior scenes, but do not suit
well to open scenes like outer space. At the moment I was planning
to make a space game not unlike the good old Elite from Bell and 
Braben.

Thus I started making my own scene graph library. I did not plan
many features. Parts were written as needed. I thought that I was
making a prototype, and I would make better plans when I had gotten
experience from this prototype.

\section section_basic_scene_graph_pipeline Basic scene graph pipeline

This section describes a basic scene graph pipeline. Scene graph
itself is a datastructure, usually a tree, which defines the world
by listing objects of the scene in nodes of the tree.

Notice that this is a general description and not spesific to %Teddy.
In fact %Teddy does some things slighly differently than described here.
How %Teddy actually works is described in later sections.

The pipeline is the process of displaying the scene from some
spesific point of view. The process is called pipeline because
it consists of several phases which need to be executed in pipeline.

The pipeline is executed from start to end for each frame. Roughly
scene graph can be divided into three pipeline stages:

<ol>
<li>Application stage
<li>Culling stage
<li>Rendering stage
</ol>


\subsection subsection_application_stage Application stage


The application stage is usually considered external to the scene
graph library. In application stage the client application may modify
the scene graph and its nodes. Almost every application wants to set
camera location for example, and this should be done in application
stage.


\subsection subsection_culling_stage Culling stage


Culling stage is optional but very recommened stage in scene graph
pipeline. It's purpose is to speed up rendering by examining objects
in the scene graph and trying to identify objects that do need to be
rendered because they would not be visible in the final rendered image.

There are several culling algorithms. Some of them are general, some
of them need spesific kind of scene graph. Many culling algoritms need
some amount of scene graph preprocessing. Preprocessing is needed to
be executed only once, not for each frame like the actual culling
stage, thus complex calculations can be performed during preprocessing.

One of the most primitive yet moderately effective culling algorithm
is view frustum culling. This algorithm works by testing intersection
of bounding volume of each potentially drawable object of the scene
graph to the view frustum of the camera. If the bounding volume does
not intersect with the view frustum, the object is not visible at all,
and thus need not be rendered at all.

View frustum culling needs some kind of bounding volume information for
each object. The bounding volume determination is usually done as
preprocessing. There are several types of bounding volumes each with
different characteristics.

Sphere as bounding volume is the fastest to test but it generates most
false positive results. False positives in this case means the
algorithm finds the bouding sphere (correctly) intersecting the view
frustum. Meanwhile the actual object inside the bounding sphere is
not intersecting the view frustum. False positives do not affect the
correctness of culling algorithm. It is acceptable to drawn objects
which actually are not visible, because this does not change the final
rendered image. We would want to draw only those objects which are at
least partially visible, but determining this set of objects may be
complex and take more time than simply rendering some false positive
(frustum intersecting) objects.

%Teddy currently only does bounding sphere to view frustum intersection
test culling.

Box is another common shape for bounding volume. For long or flat
objects it less false positives than sphere, but it is more complex
and thus more costly to perform. Bounding volume can also be a set
of several primitive bounding volumes, and/or hiearachial set of
progressively more and more precise sets of bounding primitives.


\subsection subsection_rendering_stage Rendering stage


To be written some rainy day.


\section section_design_goal Design goals in Teddy


With %Teddy I wanted first just to learn OpenGL. It soon turned out
that OpenGL did not provide essential high level 3D graphics features,
so I started making a framework. While most of the development so far
has been pretty unguided, following ideas have influenced the design:

<ul>
<li>First make it work, optimize later.
<li>Try to start with correct implementation even if you know a quick
hack which could be implemented faster. While all features need not to
be supported at once, make it easy to add support later, and put stubs
where needed.
<li>Avoid cryptic code at all costs. Do not use complex constructs
where they are not needed. Flatten class hierarchy by removing classes
which are not actually being used.
<li>Avoid limitations which are not needed.
<li>Avoid repetition of code at all costs. Even if it means more work,
try to think of how to generalize the situation.
<li>Generic methods should be collected to functions and separated
from application so the methods really are generally usable. Use
several development applications to test this.
<li>Last but not least: One should be able to use the framework for
something useful!
</ul>

\section section_threads Use of threads in Teddy

%Teddy uses two threads: the main thread, and a thread for a
simulation timer. The main thread sits in a loop updating
graphics display and polling events. This loop is currently in
<em>PhysicalComponents::WindowManager::inputLoop()</em>.

The simulation timer must be started by the user - see
TeddyTests examples.

*********************************************************************************/


