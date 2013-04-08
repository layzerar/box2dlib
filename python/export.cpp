/*
 * @summary: box2d export
 * @date: 2012-11-21
 * @author: zl
 */

#include "config.h"
#include "export.h"
#include "utils.h"


BOOST_PYTHON_MODULE(_box2d)
{
	export_math();
	export_shapes();
	export_contact();
	export_bodyfixture();
	export_joints();
	export_world();
	export_misc();
	export_except();
}
