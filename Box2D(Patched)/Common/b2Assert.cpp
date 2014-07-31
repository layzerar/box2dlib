/*
 * @summary: box2d assert
 * @date: 2012-11-21
 * @author: zl
 */

#include <Box2D/Common/b2Assert.h>

#define BOOST_PYTHON_STATIC_LIB
#include <boost/python.hpp>


void _b2_assert(const char* arg1, const char* arg2, int lineno)
{
	using namespace boost::python;

	PyErr_SetString(PyExc_AssertionError, arg1);
	throw_error_already_set();
}

