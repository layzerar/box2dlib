/*
 * @summary: box2d exceptions
 * @date: 2012-11-21
 * @author: zl
 */

#ifndef EXC_H_
#define EXC_H_


inline void IndexError()
{
	using boost::python::throw_error_already_set;
	PyErr_SetString(PyExc_IndexError, "Index out of range");
	throw_error_already_set();
}


#endif /* EXC_H_ */
