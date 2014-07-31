/*
 * @summary: box2d containers
 * @date: 2013-04-26
 * @author: zl
 */

#include "containers.h"
#include "convertor.h"


void export_containers()
{
	using namespace boost::python;

	to_python_converter<b2FixtureList, vector_to_list_ref_converter<b2Fixture*> >();
	to_python_converter<b2BodyList, vector_to_list_ref_converter<b2Body*> >();
	to_python_converter<b2ContactList, vector_to_list_ref_converter<b2Contact*> >();
	to_python_converter<b2JointList, vector_to_list_ref_converter<b2Joint*> >();

	to_python_converter<b2Vec2List, vector_to_list_converter<b2Vec2> >();
	to_python_converter<b2PointStateList, vector_to_list_converter<b2PointState> >();
	to_python_converter<b2ManifoldPointList, vector_to_list_converter<b2ManifoldPoint> >();
	to_python_converter<b2PointStateListPair, pair_to_tuple_converter<b2PointStateList, b2PointStateList> >();

	register_to_python_converter<b2Float32List, vector_to_list_converter<float32> >();

	b2vec2_from_seq_convertor();
	b2vec3_from_seq_convertor();
	b2color_from_seq_convertor();
	vector_from_seq_converter<float32>();
	vector_from_seq_converter<b2Vec2>();
	vector_from_seq_converter<b2ManifoldPoint>();

}

