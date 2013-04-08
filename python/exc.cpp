/*
 * @summary: box2d exceptions
 * @date: 2012-11-21
 * @author: zl
 */

#include "config.h"
#include "exc.h"


#if defined(_MSC_VER)
#include <intrin.h>

void b2DebugBreak()
{
	__debugbreak();
}
#elif defined(__GNUC__)
void b2DebugBreak()
{
	__builtin_trap();
}
#else
void b2DebugBreak()
{
}
#endif


void export_except()
{
	using namespace boost::python;

#if defined(EXPORT_B2DEBUGBREAK)
	def("b2DebugBreak", b2DebugBreak);
#endif
}

