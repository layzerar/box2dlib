/*
 * @summary: box2d assert
 * @date: 2012-11-21
 * @author: zl
 */

#ifndef B2ASSERT_H_
#define B2ASSERT_H_


#define BOOST_PYTHON_STATIC_LIB
#include <boost/python.hpp>

#undef b2Assert
#define b2Assert(e) ((e) ? (void)0: _b2_assert(#e, __FILE__, __LINE__))


inline void _b2_assert(const char* arg1, const char* arg2, int lineno)
{
	using namespace boost::python;

	PyErr_SetString(PyExc_AssertionError, arg1);
	throw_error_already_set();
}


#endif /* B2ASSERT_H_ */
