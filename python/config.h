/*
 * @summary: box2d export
 * @date: 2012-11-21
 * @author: zl
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#define EXPORT_B2DEBUGBREAK

// define the max vertices for converter
#define b2_maxArrayCount 1024

#define BOOST_PYTHON_STATIC_LIB
#include <boost/python.hpp>
#include <boost/foreach.hpp>
#ifndef FOREACH
#define FOREACH BOOST_FOREACH
#endif

#include <Box2D/Box2D.h>

#endif /* CONFIG_H_ */
