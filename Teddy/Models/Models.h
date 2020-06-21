
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

	$Id: Models.h,v 1.4 2002/02/16 12:41:39 tksuoran Exp $
*/


namespace Teddy {

/*!


\section section_models_intro Introduction to Models


Models namespace contains classes to maintain model
modeling and rendering data.

Model represents a renderable object. Each model defines
shape, material, location and orientation.

The shape of a Model is defined by a Geometry object. Geometry
object contains elements such as vertices, lines, polygons,
trinagle strips etc. Each Vertex may spesify space coordinate,
texture coordinate, color value and normal coordinates.

The material of a Model is defined by a Material object. Material
object spesifies lighting properties like ambient, diffuse and
specular color components, together with possible Texture
spesification.

Location and orientation of a Model should be accessed through
Model::getPosition(), Model::setPosition(), Model::getAttitude()
and Model::setAttitude() -methods.

Models can be hierarchial. Model can have children models.
This can be used in to ways. First, one can build complex
objects from several different simpler parts by making each
part a separate Model, and adding these parts as children to
a single Model. Second, the same Model can be used in several
objects by adding the 'shape' Model as a child to several other
'instance' Models. The instance models can spesify independent
position and orientation, but they use the same shape Model
for drawing.

If a Model does not spesify materiel, and it is drawn as child
of some other Model, it will use the material from its parent
Model. This way the same shape can be drawn in different
naterials on different Models.


\section section_hierarchial_models More about hierarchial models


Each Model has material, geometry and set of children.                                                                                     
If the material is set, that material is used to draw the geometry.                                                                        
                                                                                                                                           
If you want to have object with multiple materials, you must divide the                                                                    
object into multiple parts. For each part you make a separate Model.                                                                       
The shape data is placed into geometry of the model as usual, but now                                                                      
each submodel can also have their own material. Finally you need one                                                                       
parent Model into which you place the sub models as children.                                                                              
                                                                                                                                           
I really should do an example showing power of this. I might even try                                                                      
doing it tonight                                                                                                                           
                                                                                                                                           
A moderately complex draft for this example is below.. it is a car :)                                                                      
                                                                                                                                           
To make up a simple car model I want to have single box representing a                                                                     
body and four cylinders representing tires. The body is red and tires are                                                                  
black.                                                                                                                                     
                                                                                                                                           
// create reusable shapes                                                                                                                  
                                                                                                                                           
Box      *body = new Box(...);                                                                                                             
Cylinder *tire = new Cylinder(...);                                                                                                        
                                                                                                                                           
// create one instance of car                                                                                                              
Model *car = new Model(...);                                                                                                               
Model *front_left_tire  = new Model(...);                                                                                                  
Model *front_right_tire = new Model(...);                                                                                                  
Model *rear_left_tire   = new Model(...);                                                                                                  
Model *rear_right_tire  = new Model(...);                                                                                                  
front_left_tire .add( tire ); // use the shape from tire, do not redefine                                                                  
front_right_tire.add( tire ); // use the shape from tire, do not redefine                                                                  
rear_left_tire  .add( tire ); // use the shape from tire, do not redefine                                                                  
rear_right_tire .add( tire ); // use the shape from tire, do not redefine                                                                  
car.add( body             );                                                                                                               
car.add( front_left_tire  );                                                                                                               
car.add( front_right_tire );                                                                                                               
car.add( rear_left_tire   );                                                                                                               
car.add( rear_right_tire  );                                                        

Now you have option to set materials either for body and tire, or car,                                                                     
front_left_tire, front_right_tire, rear_left_tire and rear_right_tire.                                                                     
                                                                                                                                           
If you do spesify material for tire, then all tires will use that                                                                          
material.                                                                                                                                  
                                                                                                                                           
If you do not spesify material for body (set it to NULL), then when the                                                                    
car is drawn its body will be drawn using the material set for the car.                                                                    
This way you can have several cars using the same body but different                                                                       
material.                                                                                                                                  
                                                                                                                                           
While this is not about materials, I'll mention it here because it is                                                                      
related to the hierarchial Models and use of child Models. If you                                                                          
transform tire, say, turn it left a bit. This would affect all tires -                                                                     
nasty, you probably dont want that. But if you had                                                                                         
                                                                                                                                           
Model *front_tire = new Model(...);                                                                                                        
front_tire.add( tire );                                                                                                                    
                                                                                                                                           
and                                                                                                                                        
                                                                                                                                           
front_left_tire .add( front_tire ); // change initial example                                                                              
front_right_tire.add( front_tire ); // change initial example                                                                              
                                                                                                                                           
then turning the front_tire would turn both front tires at the same time,                                                                  
and this could be actually be useful somewhere (while this example still                                                                   
is not realistic)..                                       

*/
namespace Models {

};
};

