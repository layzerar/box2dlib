/*
 * @summary: box2d userdata
 * @date: 2012-11-21
 * @author: zl
 */

#ifndef USERDATA_H_
#define USERDATA_H_


#include "config.h"


using boost::python::object;


template<class T>
inline void b2Attr_ClearUserData(T& self)
{
	using namespace boost::python;

	xdecref((PyObject*)self.userData);
	self.userData = NULL;
}

template<class T>
inline void b2Attr_SetUserData(T& self, object userData)
{
	using namespace boost::python;

	b2Attr_ClearUserData(self);
	self.userData = xincref(userData.ptr());
}

template<class T>
inline object b2Attr_GetUserData(T& self)
{
	using namespace boost::python;

	return object(handle<>(borrowed((PyObject*)self.userData)));
}

template<class T>
inline void b2Func_ClearUserData(T& self)
{
	using namespace boost::python;

	xdecref((PyObject*)self.GetUserData());
	self.SetUserData(NULL);
}

template<class T>
inline void b2Func_SetUserData(T& self, object userData)
{
	using namespace boost::python;

	b2Func_ClearUserData(self);
	self.SetUserData(xincref(userData.ptr()));
}

template<class T>
inline object b2Func_GetUserData(T& self)
{
	using namespace boost::python;

	return object(handle<>(borrowed((PyObject*)self.GetUserData())));
}


#endif /* USERDATA_H_ */
