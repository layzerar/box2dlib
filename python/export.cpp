/*
 * @summary: box2d export
 * @date: 2012-11-21
 * @author: zl
 */

#include "config.h"
#include "export.h"


BOOST_PYTHON_MODULE(MODULE_NAME)
{
	export_math();
	export_shapes();
	export_contact();
	export_bodyfixture();
	export_joints();
	export_world();
	export_misc();
	export_containers();
	export_except();
}
