/*
 * @summary: box2d shapes
 * @date: 2012-11-21
 * @author: zl
 */

#include "config.h"
#include "containers.h"
#include <algorithm>


/*
 * rename functions
 */

void (b2PolygonShape::*b2PolygonShape_SetAsBox2)(float32 hx, float32 hy) = &b2PolygonShape::SetAsBox;
void (b2PolygonShape::*b2PolygonShape_SetAsBox4)(float32 hx, float32 hy, const b2Vec2& center, float32 angle) = &b2PolygonShape::SetAsBox;


/*
 * extend functions
 */

b2Vec2List b2PolygonShape_GetVertices(b2PolygonShape& self)
{
	int32 size = std::max(0, std::min(b2_maxPolygonVertices, self.m_count));
	return b2Vec2List(self.m_vertices, self.m_vertices + size);
}

b2Vec2List b2PolygonShape_GetNormals(b2PolygonShape& self)
{
	int32 size = std::max(0, std::min(b2_maxPolygonVertices, self.m_count));
	return b2Vec2List(self.m_normals, self.m_normals + size);
}

b2Vec2List b2EdgeShape_GetVertices(b2EdgeShape& self)
{
	if (self.m_hasVertex3)
	{
		b2Vec2List vertices(4);
		vertices[0] = self.m_vertex0;
		vertices[1] = self.m_vertex1;
		vertices[2] = self.m_vertex2;
		vertices[3] = self.m_vertex3;
		return vertices;
	}
	else if (self.m_hasVertex0)
	{
		b2Vec2List vertices(3);
		vertices[0] = self.m_vertex0;
		vertices[1] = self.m_vertex1;
		vertices[2] = self.m_vertex2;
		return vertices;
	}
	else
	{
		b2Vec2List vertices(2);
		vertices[0] = self.m_vertex1;
		vertices[1] = self.m_vertex2;
		return vertices;
	}
}

b2Vec2List b2ChainShape_GetVertices(b2ChainShape& self)
{
	return b2Vec2List(self.m_vertices,
		self.m_vertices + std::max(0, self.m_count));
}

void b2PolygonShape_Set(b2PolygonShape& self, const b2Vec2List& vertices)
{
	b2Assert(vertices.size() >= 3 && vertices.size() <= b2_maxPolygonVertices);

	self.Set(&vertices[0], (int32)vertices.size());
}


void b2EdgeShape_Set(b2EdgeShape& self, const b2Vec2List& vertices)
{
	b2Assert(vertices.size() >= 2 && vertices.size() <= 4);
	switch(vertices.size())
	{
	case 4:
		self.m_vertex0 = vertices[0];
		self.m_vertex1 = vertices[1];
		self.m_vertex2 = vertices[2];
		self.m_vertex3 = vertices[3];
		self.m_hasVertex0 = true;
		self.m_hasVertex3 = true;
		break;
	case 3:
		self.m_vertex0 = vertices[0];
		self.m_vertex1 = vertices[1];
		self.m_vertex2 = vertices[2];
		self.m_hasVertex0 = true;
		self.m_hasVertex3 = false;
		break;
	case 2:
		self.Set(vertices[0], vertices[1]);
		break;
	}
}


void b2ChainShape_CreateLoop(b2ChainShape& self, const b2Vec2List& vertices)
{
	b2Assert(vertices.size() >= 3);
	self.CreateLoop(&vertices[0], (int32)vertices.size());
}


void b2ChainShape_CreateChain(b2ChainShape& self, const b2Vec2List& vertices)
{
	b2Assert(vertices.size() >= 2);
	self.CreateChain(&vertices[0], (int32)vertices.size());
}


void export_shapes()
{
	using namespace boost::python;

	enum_<b2Shape::Type>("b2ShapeType")
		.value("e_circle", b2Shape::e_circle)
		.value("e_edge", b2Shape::e_edge)
		.value("e_polygon", b2Shape::e_polygon)
		.value("e_chain", b2Shape::e_chain)
		.value("e_typeCount", b2Shape::e_typeCount)
	;

	class_<b2MassData>("b2MassData")
		.def_readwrite("mass", &b2MassData::mass)
		.def_readwrite("center", &b2MassData::center)
		.def_readwrite("I", &b2MassData::I)
	;

	class_<b2Shape, boost::noncopyable, b2Shape*>("b2Shape", no_init)
		.def("GetType", &b2Shape::GetType)
		.def("GetChildCount", pure_virtual(&b2Shape::GetChildCount))
		.def("TestPoint", pure_virtual(&b2Shape::TestPoint))
		.def("RayCast", pure_virtual(&b2Shape::RayCast))
		.def("ComputeAABB", pure_virtual(&b2Shape::ComputeAABB))
		.def("ComputeMass", pure_virtual(&b2Shape::ComputeMass))
		.def_readonly("type", &b2Shape::m_type)
		.def_readwrite("radius", &b2Shape::m_radius)
	;

	class_<b2CircleShape, bases<b2Shape>, boost::noncopyable>("b2CircleShape")
		.def("GetSupport", &b2CircleShape::GetSupport)
		.def("GetSupportVertex", &b2CircleShape::GetSupportVertex, return_value_policy<copy_const_reference>())
		.def("GetVertexCount", &b2CircleShape::GetVertexCount)
		.def("GetVertex", &b2CircleShape::GetVertex, return_value_policy<copy_const_reference>())
		.def_readwrite("position", &b2CircleShape::m_p)
	;

	class_<b2PolygonShape, bases<b2Shape>, boost::noncopyable>("b2PolygonShape")
		.def("Set", b2PolygonShape_Set)
		.def("SetAsBox", b2PolygonShape_SetAsBox2)
		.def("SetAsBox", b2PolygonShape_SetAsBox4)
		.def("GetVertexCount", &b2PolygonShape::GetVertexCount)
		.def("GetVertex", &b2PolygonShape::GetVertex, return_value_policy<copy_const_reference>())
		.def("Validate", &b2PolygonShape::Validate)
		.def_readonly("centroid", &b2PolygonShape::m_centroid)
		.def_readonly("count", &b2PolygonShape::m_count)
		.add_property("normals", b2PolygonShape_GetNormals)
		.add_property("vertices", b2PolygonShape_GetVertices, b2PolygonShape_Set)
	;

	class_<b2EdgeShape, bases<b2Shape>, boost::noncopyable>("b2EdgeShape")
		.def("Set", &b2EdgeShape::Set)
		.def("Set", b2EdgeShape_Set)
		.def_readonly("hasVertex0", &b2EdgeShape::m_hasVertex0)
		.def_readonly("hasVertex3", &b2EdgeShape::m_hasVertex3)
		.def_readonly("vertex0", &b2EdgeShape::m_vertex0)
		.def_readonly("vertex1", &b2EdgeShape::m_vertex1)
		.def_readonly("vertex2", &b2EdgeShape::m_vertex2)
		.def_readonly("vertex3", &b2EdgeShape::m_vertex3)
		.add_property("vertices", b2EdgeShape_GetVertices, b2EdgeShape_Set)
	;

	class_<b2ChainShape, bases<b2Shape>, boost::noncopyable>("b2ChainShape")
		.def("CreateLoop", b2ChainShape_CreateLoop)
		.def("CreateChain", b2ChainShape_CreateChain)
		.def("SetPrevVertex", &b2ChainShape::SetPrevVertex)
		.def("SetNextVertex", &b2ChainShape::SetNextVertex)
		.def("GetChildEdge", &b2ChainShape::GetChildEdge)
		.def_readonly("count", &b2ChainShape::m_count)
		.def_readonly("hasPrevVertex", &b2ChainShape::m_hasPrevVertex)
		.def_readonly("hasNextVertex", &b2ChainShape::m_hasNextVertex)
		.def_readonly("prevVertex", &b2ChainShape::m_prevVertex)
		.def_readonly("nextVertex", &b2ChainShape::m_nextVertex)
		.add_property("vertices", b2ChainShape_GetVertices, b2ChainShape_CreateLoop)
	;
}
