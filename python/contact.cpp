/*
 * @summary: box2d contact
 * @date: 2012-11-21
 * @author: zl
 */

#include "config.h"
#include "utils.h"
#include "convertor.h"
#include <memory>

using boost::python::object;


/*
 * rename overloading functions
 */
b2Manifold* (b2Contact::*b2Contact_GetManifold)() = &b2Contact::GetManifold;
b2Fixture* (b2Contact::*b2Contact_GetFixtureA)() = &b2Contact::GetFixtureA;
b2Fixture* (b2Contact::*b2Contact_GetFixtureB)() = &b2Contact::GetFixtureB;


/*
 * extend functions
 */


object b2Manifold_GetPoints(b2Manifold& self)
{
	return ArrayToRefList(self.points, self.pointCount, b2_maxManifoldPoints);
}

void b2Manifold_SetPoints(b2Manifold& self, object points)
{
	int32 count;

	self.pointCount = 0;
	count = (int32)ListToArray(self.points, points, b2_maxManifoldPoints);
	if (count > 0)
	{
		self.pointCount = count;
	}
}

object b2WorldManifold_GetPoints(b2WorldManifold& self)
{
	return ArrayToRefList(self.points, b2_maxManifoldPoints, b2_maxManifoldPoints);
}

void b2WorldManifold_SetPoints(b2WorldManifold& self, object points)
{
	ListToArray(self.points, points, b2_maxManifoldPoints);
}

object b2ContactImpulse_GetNormalImpulses(b2ContactImpulse& self)
{
	return ArrayToList(self.normalImpulses, self.count, b2_maxManifoldPoints);
}

object b2ContactImpulse_GetTangentImpulses(b2ContactImpulse& self)
{
	return ArrayToList(self.tangentImpulses, self.count, b2_maxManifoldPoints);
}

bool b2ContactImpulse_Set(b2ContactImpulse& self, object normalImpulses, object tangentImpulses)
{
	ssize_t count1, count2;

	count1 = len(normalImpulses);
	count2 = len(tangentImpulses);
	if ((count1 != count2) || (count1 > b2_maxManifoldPoints))
		return false;
	int32 len1, len2;

	self.count = 0;
	len1 = (int32)ListToArray(self.normalImpulses, normalImpulses, b2_maxManifoldPoints);
	len2 = (int32)ListToArray(self.tangentImpulses, tangentImpulses, b2_maxManifoldPoints);

	if (len1 != len2)
		return false;
	self.count = len1;
	return true;
}

b2WorldManifold* b2Contact_GetWorldManifold(b2Contact& self)
{
	std::auto_ptr<b2WorldManifold> wm(new b2WorldManifold);

	self.GetWorldManifold(wm.get());
	return wm.release();
}

object b2GetPointStates_W(const b2Manifold* manifold1, const b2Manifold* manifold2)
{
	b2PointState cstate1[b2_maxManifoldPoints];
	b2PointState cstate2[b2_maxManifoldPoints];

	b2GetPointStates(cstate1, cstate2, manifold1, manifold2);
	object state1 = ArrayToList(cstate1, b2_maxManifoldPoints, b2_maxManifoldPoints);
	object state2 = ArrayToList(cstate2, b2_maxManifoldPoints, b2_maxManifoldPoints);

	return make_tuple(state1, state2);
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
		.def("GetWorldManifold", b2Contact_GetWorldManifold, return_value_policy<manage_new_object>())
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
		.add_property("worldManifold", make_function(b2Contact_GetWorldManifold, return_value_policy<manage_new_object>()))
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

	to_python_converter<b2ContactList, vector_to_list_ref_converter<b2Contact*> >();
}

