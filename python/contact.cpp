/*
 * @summary: box2d contact
 * @date: 2012-11-21
 * @author: zl
 */

#include "config.h"
#include "containers.h"
#include <memory>
#include <algorithm>


/*
 * rename overloading functions
 */
b2Manifold* (b2Contact::*b2Contact_GetManifold)() = &b2Contact::GetManifold;
b2Fixture* (b2Contact::*b2Contact_GetFixtureA)() = &b2Contact::GetFixtureA;
b2Fixture* (b2Contact::*b2Contact_GetFixtureB)() = &b2Contact::GetFixtureB;


/*
 * extend functions
 */


b2ManifoldPointList b2Manifold_GetPoints(b2Manifold& self)
{
	return b2ManifoldPointList(
			std::max(0, std::min(b2_maxManifoldPoints, self.pointCount)), *self.points);
}

void b2Manifold_SetPoints(b2Manifold& self, const b2ManifoldPointList& points)
{
	b2Assert(points.size() <= b2_maxManifoldPoints);
	if (points.empty())
		return;
	memcpy(self.points, &points[0], sizeof(points[0]) * points.size());
	self.pointCount = (int32)points.size();
}

b2Vec2List b2WorldManifold_GetPoints(b2WorldManifold& self)
{
	return b2Vec2List(self.points, self.points + b2_maxManifoldPoints);
	//return b2Vec2List(b2_maxManifoldPoints, *self.points);
}

void b2WorldManifold_SetPoints(b2WorldManifold& self, const b2Vec2List& points)
{
	b2Assert(points.size() <= b2_maxManifoldPoints);
	if (points.empty())
		return;
	memcpy(self.points, &points[0], sizeof(points[0]) * points.size());
}

b2Float32List b2ContactImpulse_GetNormalImpulses(b2ContactImpulse& self)
{
	int32 count = std::max(0, std::min(b2_maxManifoldPoints, self.count));
	return b2Float32List(self.normalImpulses, self.normalImpulses + count);
}

b2Float32List b2ContactImpulse_GetTangentImpulses(b2ContactImpulse& self)
{
	int32 count = std::max(0, std::min(b2_maxManifoldPoints, self.count));
	return b2Float32List(self.tangentImpulses, self.tangentImpulses + count);
}

bool b2ContactImpulse_Set(b2ContactImpulse& self,
		const b2Float32List& normalImpulses, const b2Float32List& tangentImpulses)
{
	b2Assert(normalImpulses.size() <= b2_maxManifoldPoints);
	b2Assert(normalImpulses.size() == tangentImpulses.size());

	if (normalImpulses.empty())
		return false;
	int32 count = (int32)normalImpulses.size();
	memcpy(self.normalImpulses, &normalImpulses[0], sizeof(normalImpulses[0]) * count);
	memcpy(self.tangentImpulses, &tangentImpulses[0], sizeof(tangentImpulses[0]) * count);
	self.count = count;
	return true;
}

b2WorldManifold b2Contact_GetWorldManifold(b2Contact& self)
{
	b2WorldManifold manifold;

	self.GetWorldManifold(&manifold);
	return manifold;
}

b2PointStateListPair b2GetPointStates_W(const b2Manifold* manifold1, const b2Manifold* manifold2)
{
	b2PointStateList state1(b2_maxManifoldPoints);
	b2PointStateList state2(b2_maxManifoldPoints);

	b2GetPointStates(&state1[0], &state2[0], manifold1, manifold2);

	return b2PointStateListPair(state1, state2);
}


void export_contact()
{
	using namespace boost::python;

	enum_<b2ContactFeature::Type>("b2ContactFeatureType")
		.value("e_vertex", b2ContactFeature::e_vertex)
		.value("e_face", b2ContactFeature::e_face)
	;

	enum_<b2Manifold::Type>("b2ManifoldType")
		.value("e_circles", b2Manifold::e_circles)
		.value("e_faceA", b2Manifold::e_faceA)
		.value("e_faceB", b2Manifold::e_faceB)
	;

	enum_<b2PointState>("b2PointState")
		.value("b2_nullState", b2_nullState)
		.value("b2_addState", b2_addState)
		.value("b2_persistState", b2_persistState)
		.value("b2_removeState", b2_removeState)
	;

	class_<b2ContactFeature>("b2ContactFeature")
		.def_readwrite("indexA", &b2ContactFeature::indexA)
		.def_readwrite("indexB", &b2ContactFeature::indexB)
		.def_readwrite("typeA", &b2ContactFeature::typeA)
		.def_readwrite("typeB", &b2ContactFeature::typeB)
	;

	class_<b2ContactID>("b2ContactID")
		.def_readwrite("cf", &b2ContactID::cf)
		.def_readwrite("key", &b2ContactID::key)
	;

	class_<b2ManifoldPoint>("b2ManifoldPoint")
		.def_readwrite("localPoint", &b2ManifoldPoint::localPoint)
		.def_readwrite("normalImpulse", &b2ManifoldPoint::normalImpulse)
		.def_readwrite("tangentImpulse", &b2ManifoldPoint::tangentImpulse)
		.def_readwrite("id", &b2ManifoldPoint::id)
	;

	class_<b2Manifold>("b2Manifold")
		.add_property("points", b2Manifold_GetPoints, b2Manifold_SetPoints)
		.def_readwrite("localNormal", &b2Manifold::localNormal)
		.def_readwrite("localPoint", &b2Manifold::localPoint)
		.def_readwrite("type", &b2Manifold::type)
		.def_readonly("pointCount", &b2Manifold::pointCount)
	;

	class_<b2WorldManifold>("b2WorldManifold")
		.def("Initialize", &b2WorldManifold::Initialize)
		.def_readwrite("normal", &b2WorldManifold::normal)
		.add_property("points", b2WorldManifold_GetPoints, b2WorldManifold_SetPoints)
	;

	class_<b2ContactImpulse>("b2ContactImpulse")
		.def("Set", b2ContactImpulse_Set)
		.add_property("normalImpulses", b2ContactImpulse_GetNormalImpulses)
		.add_property("tangentImpulses", b2ContactImpulse_GetTangentImpulses)
		.def_readonly("count", &b2ContactImpulse::count)
	;

	class_<b2Contact, boost::noncopyable, b2Contact*>("b2Contact", no_init)
		.def("GetManifold", b2Contact_GetManifold, return_internal_reference<>())
		.def("GetWorldManifold", b2Contact_GetWorldManifold)
		.def("IsTouching", &b2Contact::IsTouching)
		.def("SetEnabled", &b2Contact::SetEnabled)
		.def("IsEnabled", &b2Contact::IsEnabled)
		.def("GetFixtureA", b2Contact_GetFixtureA, return_internal_reference<>())
		.def("GetChildIndexA", &b2Contact::GetChildIndexA)
		.def("GetFixtureB", b2Contact_GetFixtureB, return_internal_reference<>())
		.def("GetChildIndexB", &b2Contact::GetChildIndexB)
		.def("SetFriction", &b2Contact::SetFriction)
		.def("GetFriction", &b2Contact::GetFriction)
		.def("ResetFriction", &b2Contact::ResetFriction)
		.def("SetRestitution", &b2Contact::SetRestitution)
		.def("GetRestitution", &b2Contact::GetRestitution)
		.def("SetTangentSpeed", &b2Contact::SetTangentSpeed)
		.def("GetTangentSpeed", &b2Contact::GetTangentSpeed)
		.def("ResetRestitution", &b2Contact::ResetRestitution)
		.def("Evaluate", &b2Contact::Evaluate)
		.add_property("manifold", make_function(b2Contact_GetManifold, return_internal_reference<>()))
		.add_property("worldManifold", b2Contact_GetWorldManifold)
		.add_property("touching", &b2Contact::IsTouching)
		.add_property("enabled", &b2Contact::IsEnabled, &b2Contact::SetEnabled)
		.add_property("fixtureA", make_function(b2Contact_GetFixtureA, return_internal_reference<>()))
		.add_property("childIndexA", &b2Contact::GetChildIndexA)
		.add_property("fixtureB", make_function(b2Contact_GetFixtureB, return_internal_reference<>()))
		.add_property("childIndexB", &b2Contact::GetChildIndexB)
		.add_property("friction", &b2Contact::GetFriction, &b2Contact::SetFriction)
		.add_property("restitution", &b2Contact::GetRestitution, &b2Contact::SetRestitution)
		.add_property("tangentSpeed", &b2Contact::GetTangentSpeed, &b2Contact::SetTangentSpeed)
	;

	def("b2GetPointStates", b2GetPointStates_W);

}

