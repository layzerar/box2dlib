/*
 * @summary: box2d world
 * @date: 2012-12-15
 * @author: zl
 */


#ifndef WORLD_H_
#define WORLD_H_

#include "config.h"


struct b2World_W: b2World
{
public:
	b2World_W(PyObject* self, const b2Vec2& gravity=b2Vec2_zero);
	PyObject* self;
};


#endif /* WORLD_H_ */
