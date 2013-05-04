/*
 * @summary: box2d containers
 * @date: 2013-04-26
 * @author: zl
 */

#ifndef TYPES_H_
#define TYPES_H_

#include "config.h"
#include <vector>
#include <utility>

using boost::python::object;


typedef std::vector<b2Fixture*> b2FixtureList;
typedef std::vector<b2Contact*> b2ContactList;
typedef std::vector<b2Joint*> b2JointList;
typedef std::vector<b2Body*> b2BodyList;

typedef std::vector<float32> b2Float32List;
typedef std::vector<b2Vec2> b2Vec2List;
typedef std::vector<b2PointState> b2PointStateList;
typedef std::vector<b2ManifoldPoint> b2ManifoldPointList;

typedef std::pair<b2PointStateList, b2PointStateList> b2PointStateListPair;


#endif /* TYPES_H_ */
