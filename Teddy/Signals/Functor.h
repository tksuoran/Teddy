
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


#ifndef TEDDY__SIGNALS__FUNCTOR__H
#define TEDDY__SIGNALS__FUNCTOR__H


#include "Teddy/SysSupport/StdString.h"

namespace Teddy   {
namespace Signals {


//!  Functor
template <typename R                        > class Functor0 {public:virtual ~Functor0(){} virtual R    operator()() = 0;};
template <typename R,typename A1            > class Functor1 {public:virtual ~Functor1(){} virtual R    operator()( A1 a1 ) = 0;};
template <typename R,typename A1,typename A2> class Functor2 {public:virtual ~Functor2(){} virtual R    operator()( A1 a1, A2 a2 ) = 0;};
#if 0
                                              class FunctorV0{public:virtual ~FunctorV0(){} void operator()() = 0;};
template <typename A1                       > class FunctorV1{public:virtual ~FunctorV1(){} void operator()( A1 a1 ) = 0;};
template <typename A1,typename A2           > class FunctorV2{public:virtual ~FunctorV2(){} void operator()( A1 a1, A2 a2 ) = 0;};
#endif


//!  Holder
template <typename R> class Holder0 {
public:
	Holder0(){ functor = NULL; }
	~Holder0(){ if( functor != NULL ){ delete functor; } }
	R operator()(){ return (*functor)(); }
	Functor0<R> *functor;
};
template <typename R,typename A1> class Holder1 {
public:
	Holder1(){ functor = NULL; }
	~Holder1(){ if( functor != NULL ){ delete functor; } }
	R operator()( A1 a1 ){ return (*functor)( a1 ); }
	Functor1<R,A1> *functor;
};
template <typename R,typename A1,typename A2> class Holder2 {
public:
	Holder2(){ functor = NULL; }
	~Holder2(){ if( functor != NULL ){ delete functor; } }
	R operator()( A1 a1, A2 a2 ){ return (*functor)( a1, a2 ); }
	Functor2<R,A1,A2> *functor;
};
#if 0
class HolderV0 {
public:
	HolderV0(){ functor = NULL; }
	~HolderV0(){ if( functor != NULL ){ delete functor; } }
	void operator()(){ (*functor)(); }
	FunctorV0 *functor;
};
template <typename A1> class HolderV1 {
public:
	HolderV1(){ functor = NULL; }
	~HolderV1(){ if( functor != NULL ){ delete functor; } }
	void operator()( A1 a1 ){ (*functor)( a1 ); }
	FunctorV1<A1> *functor;
};
template <typename A1,typename A2> class HolderV2 {
public:
	HolderV2(){ functor = NULL; }
	~HolderV2(){ if( functor != NULL ){ delete functor; } }
	void operator()( A1 a1, A2 a2 ){ (*functor)( a1, a2 ); }
	FunctorV2<A1,A2> *functor;
};
#endif



//!  TFunctor
template <typename T,typename R> class TFunctor0 : public Functor0<R> {
public:
	TFunctor0( T *object, R(T::*operation)()):object(object),operation(operation){}
    virtual ~TFunctor0(){}
	virtual R operator()(){ return (*object.*operation)(); }
protected:
	T *object;
	R (T::*operation)();
};
template <typename T,typename R,typename A1> class TFunctor1 : public Functor1<R,A1> {
public:
	TFunctor1( T *object, R(T::*operation)( A1 )):object(object),operation(operation){}
    virtual ~TFunctor1(){}
	virtual R operator()( A1 a1 ){ return (*object.*operation)( a1 ); }
protected:
	T *object;
	R (T::*operation)( A1 );
};
template <typename T,typename R,typename A1,typename A2> class TFunctor2 : public Functor2<R,A1,A2> {
public:
	TFunctor2( T *object, R(T::*operation)( A1, A2 )):object(object),operation(operation){}
    virtual ~TFunctor2(){}
	virtual R operator()( A1 a1, A2 a2 ){ return (*object.*operation)( a1, a2 ); }
protected:
	T *object;
	R (T::*operation)( A1, A2 );
};
#if 0
template <typename T> class TFunctorV0 : public FunctorV0 {
public:
	TFunctorV0( T *object, void(T::*operation)()):object(object),operation(operation){}
	virtual void operator()(){ (*object.*operation)(); }
protected:
	T    *object;
	void (T::*operation)();
};
template <typename T,typename A1> class TFunctorV1 : public FunctorV1<A1> {
public:
	TFunctorV1( T *object, void(T::*operation)( A1 )):object(object),operation(operation){}
	virtual void operator()( A1 a1 ){ (*object.*operation)( a1 ); }
protected:
	T    *object;
	void (T::*operation)( A1 );
};
template <typename T,typename A1,typename A2> class TFunctorV2 : public FunctorV2<A1,A2> {
public:
	TFunctorV2( T *object, void(T::*operation)( A1, A2 )):object(object),operation(operation){}
	virtual void operator()( A1 a1, A2 a2 ){ (*object.*operation)( a1, a2 ); }
protected:
	T    *object;
	void (T::*operation)( A1, A2 );
};
#endif


//  Anonymous constructors

template <typename T,typename R> Functor0<R> *functor( T *object, R(T::*operation)()){
	return new TFunctor0<T,R>( object, operation );
}
template <typename T,typename R,typename A1> Functor1<R,A1> *functor( T *object, R(T::*operation)( A1 )){
	return new TFunctor1<T,R,A1>( object, operation );
}
template <typename T,typename R,typename A1,typename A2> Functor2<R,A1,A2> *functor( T *object, R(T::*operation)( A1, A2 )){
	return new TFunctor2<T,R,A1,A2>( object, operation );
}
#if 0
template <typename T> FunctorV0 *functor( T *object, void(T::*operation)()){
	return new TFunctorV0<T>( object, operation );
}
template <typename T,typename A1> FunctorV1<A1> *functor( T *object, void(T::*operation)( A1 )){
	return new TFunctorV1<T,A1>( object, operation );
}
template <typename T,typename A1,typename A2> FunctorV2<A1,A2> *functor( T *object, void(T::*operation)( A1, A2 )){
	return new TFunctorV2<T,A1,A2>( object, operation );
}
#endif

};  //  namespace Signals
};  //  namespace Teddy


#endif  //  TEDDY__SIGNALS__FUNCTOR__H

