/*
 * @summary: box2d export
 * @date: 2012-11-21
 * @author: zl
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#define MODULE_NAME _box2d
#define EXPORT_B2DEBUGBREAK


#define BOOST_PYTHON_STATIC_LIB
#include <boost/python.hpp>
#include <boost/format.hpp>
#include <boost/foreach.hpp>
#ifndef FOREACH
#define FOREACH BOOST_FOREACH
#endif

#include <Box2D/Box2D.h>

#endif /* CONFIG_H_ */
