
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


#ifndef TEDDY__MIX_IN__COUNTED_H
#define TEDDY__MIX_IN__COUNTED_H


namespace Teddy {
namespace MixIn {


class Counted {
public:
	virtual ~Counted() {}

	/*!  Default constructor.  Initial reference count is 0,
		 and will be incremented as soon as the object is
	     pointed to. */
	Counted() : num_instances(0) {}

	/*!  Add 1 to the reference count. */
	void addRef(){ num_instances++; }

	/*!  Subtract 1 from the reference count.
         Returns true if the reference count has reached 0
         and the object should be deleted. */
	bool subRef(){ return (--num_instances <= 0); }

private:
	unsigned long num_instances;
};


template <typename T> class CountedPointer {
public:
	/*!  Construct from normal pointer, default to NULL  */
	CountedPointer( T *ptr = 0 ) : instance_pointer(ptr){ addRef(); }
  
	/*!  Construct from another smart pointer.  Copy Constructor  */
	CountedPointer( const CountedPointer &p ) : instance_pointer( p.instance_pointer ) { addRef(); }

	/*!  Destructor.  */
	~CountedPointer(){ subRef(); }

	/*! Assignment operator. */
	CountedPointer &operator=( const CountedPointer &p ){
		return *this = p.instance_pointer;
	}

	/*! Assignment operator. */
	CountedPointer &operator=( T *ptr ){
		if( instance_pointer != ptr ){
			subRef();
			instance_pointer = ptr;
			addRef();
		}
		return *this;
	}

	/*!  Dereferencing operator. Provided to behave like the normal pointer.  */
	T &operator *    () const { return *instance_pointer; }
	/*!  Member access operator. Provided to behave like the normal pointer.  */
	T *operator ->   () const { return  instance_pointer; }
	// Conversion operators
	operator T*      () const { return  instance_pointer; }
	operator const T*() const { return  instance_pointer; }

	operator bool    () const { return  instance_pointer!=0; }  //! boolean test for NULL
	T **operator &   ()       { return &instance_pointer; }     //! Address of pointer.  May cause memory leaks if pointer is modified.

private:
	void addRef(){
		// Only change if non-null
		if( instance_pointer ){
			instance_pointer->addRef();
		}
	}

	void subRef(){
		// Only change if non-null
		if( instance_pointer ){
			// Subtract and test if this was the last pointer.
			if( instance_pointer->subRef() ){
				delete instance_pointer;
				instance_pointer = 0;
			}
		}
	}

	T *instance_pointer;
};


};  //  namespace MixIn
};  //  namespace Teddy


#endif  //  TEDDY__MIX_IN__COUNTED_H

