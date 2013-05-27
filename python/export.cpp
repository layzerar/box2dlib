/*
 * @summary: box2d export
 * @date: 2012-11-21
 * @author: zl
 */

#include "config.h"

extern void export_math();
extern void export_contact();
extern void export_bodyfixture();
extern void export_shapes();
extern void export_joints();
extern void export_world();
extern void export_misc();
extern void export_containers();
extern void export_except();


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
