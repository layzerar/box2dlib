/*
 * @summary: box2d body and fixture
 * @date: 2012-11-21
 * @author: zl
 */

#include "config.h"
#include "userdata.h"
#include "containers.h"
#include "world.h"


/*
* extend functions
*/

void b2FixtureDef_SetShape(b2FixtureDef& self, b2Shape* shape)
{
	self.shape = shape;
}

b2Shape* b2FixtureDef_GetShape(b2FixtureDef& self)
{
	return (b2Shape*)(self.shape);
}

void (*b2FixtureDef_SetUserData)(b2FixtureDef& self, object userData) = b2Attr_SetUserData;
object (*b2FixtureDef_GetUserData)(b2FixtureDef& self) = b2Attr_GetUserData;
void b2FixtureDef__del(b2FixtureDef& self)
{
	b2Attr_ClearUserData(self);
}

void (*b2Fixture_SetUserData)(b2Fixture& self, object userData) = b2Func_SetUserData;
object (*b2Fixture_GetUserData)(b2Fixture& self) = b2Func_GetUserData;


/*
 * rename overloading functions
 */
b2Shape* (b2Fixture::*b2Fixture_GetShape)() = &b2Fixture::GetShape;
b2Body* (b2Fixture::*b2Fixture_GetBody)() = &b2Fixture::GetBody;


b2MassData b2Fixture_GetMassData(b2Fixture& self)
{
	b2MassData massData;
	self.GetMassData(&massData);
	return massData;
}


static void export_fixture()
{
	using namespace boost::python;

	class_<b2Filter>("b2Filter", init<>())
		.def_readwrite("categoryBits", &b2Filter::categoryBits)
		.def_readwrite("maskBits", &b2Filter::maskBits)
		.def_readwrite("groupIndex", &b2Filter::groupIndex)
	;

	class_<b2FixtureDef>("b2FixtureDef", init<>())
		.def_readwrite("friction", &b2FixtureDef::friction)
		.def_readwrite("restitution", &b2FixtureDef::restitution)
		.def_readwrite("density", &b2FixtureDef::density)
		.def_readwrite("isSensor", &b2FixtureDef::isSensor)
		.def_readwrite("filter", &b2FixtureDef::filter)
		.add_property("shape",
			make_function(b2FixtureDef_GetShape, return_internal_reference<>()),
			make_function(b2FixtureDef_SetShape, with_custodian_and_ward<1, 2>()))
		.add_property("userData", b2FixtureDef_GetUserData, b2FixtureDef_SetUserData)
		.def("__del__", b2FixtureDef__del)
	;

	class_<b2Fixture, boost::noncopyable, b2Fixture*>("b2Fixture", no_init)
		.def("GetType", &b2Fixture::GetType)
		.def("SetSensor", &b2Fixture::SetSensor)
		.def("IsSensor", &b2Fixture::IsSensor)
		.def("SetFilterData", &b2Fixture::SetFilterData)
		.def("GetFilterData", &b2Fixture::GetFilterData, return_value_policy<copy_const_reference>())
		.def("Refilter", &b2Fixture::Refilter)
		.def("GetShape", b2Fixture_GetShape, return_internal_reference<>())
		.def("GetBody", b2Fixture_GetBody, return_internal_reference<>())
		.def("TestPoint", &b2Fixture::TestPoint)
		.def("RayCast", &b2Fixture::RayCast)
		.def("GetMassData", &b2Fixture::GetMassData)
		.def("SetDensity", &b2Fixture::SetDensity)
		.def("GetDensity", &b2Fixture::GetDensity)
		.def("GetFriction", &b2Fixture::GetFriction)
		.def("SetFriction", &b2Fixture::SetFriction)
		.def("GetRestitution", &b2Fixture::GetRestitution)
		.def("SetRestitution", &b2Fixture::SetRestitution)
		.def("GetAABB", &b2Fixture::GetAABB, return_value_policy<copy_const_reference>())
		.def("GetUserData", b2Fixture_GetUserData)
		.def("SetUserData", b2Fixture_SetUserData)
		.add_property("type", &b2Fixture::GetType)
		.add_property("friction", &b2Fixture::GetFriction, &b2Fixture::SetFriction)
		.add_property("restitution", &b2Fixture::GetRestitution, &b2Fixture::SetRestitution)
		.add_property("density", &b2Fixture::GetDensity, &b2Fixture::SetDensity)
		.add_property("isSensor", &b2Fixture::IsSensor, &b2Fixture::SetSensor)
		.add_property("userData", b2Fixture_GetUserData, b2Fixture_SetUserData)
		.add_property("shape", make_function(b2Fixture_GetShape, return_internal_reference<>()))
		.add_property("body", make_function(b2Fixture_GetBody, return_internal_reference<>()))
		.add_property("massData", b2Fixture_GetMassData)
		.add_property("aabb", make_function(&b2Fixture::GetAABB, return_value_policy<copy_const_reference>()))
		.add_property("filter",
			make_function(&b2Fixture::GetFilterData, return_value_policy<copy_const_reference>()),
			&b2Fixture::SetFilterData)
	;

}


/*
 * rename overloading functions
 */

b2Fixture* (b2Body::*b2Body_CreateFixture2)(const b2Shape* shape, float32 density) = &b2Body::CreateFixture;


/*
 * extend functions
 */

void (*b2BodyDef__del)(b2BodyDef& self) = b2Attr_ClearUserData;
void (*b2BodyDef_SetUserData)(b2BodyDef& self, object userData) = b2Attr_SetUserData;
object (*b2BodyDef_GetUserData)(b2BodyDef& self) = b2Attr_GetUserData;

void (*b2Body_SetUserData)(b2Body& self, object userData) = b2Func_SetUserData;
object (*b2Body_GetUserData)(b2Body& self) = b2Func_GetUserData;

void b2Body_SetPosition(b2Body& self, const b2Vec2& pos)
{
	self.SetTransform(pos, self.GetAngle());
}

b2MassData b2Body_GetMassData(b2Body& self)
{
	b2MassData massData;
	self.GetMassData(&massData);
	return massData;
}

b2Fixture* b2Body_CreateFixture1(b2Body& self, const b2FixtureDef* def)
{
	using namespace boost::python;

	b2Fixture* fixture = self.CreateFixture(def);
	if (fixture)
	{
		xincref((PyObject*)fixture->GetUserData());
	}
	return fixture;
}

void b2Body_DestroyFixture(b2Body& self, b2Fixture* fixture)
{
	b2Assert(self.GetWorld()->IsLocked() == false);
	b2Assert(fixture != NULL && fixture->GetBody() == &self);

	b2Cls_ClearUserData<b2Fixture> ctx(fixture);
	self.DestroyFixture(fixture);
}

b2FixtureList b2Body_GetFixtureList(b2Body& self)
{
	b2Fixture* ptr;
	b2FixtureList list;

	ptr = self.GetFixtureList();
	while (ptr != NULL)
	{
		list.push_back(ptr);
		ptr = ptr->GetNext();
	}

	return list;
}

b2JointList b2Body_GetJointList(b2Body& self)
{
	b2JointEdge* ptr;
	b2JointList list;

	ptr = self.GetJointList();
	while (ptr != NULL)
	{
		list.push_back(ptr->joint);
		ptr = ptr->next;
	}
	return list;
}

b2ContactList b2Body_GetContactList(b2Body& self)
{
	b2ContactEdge* ptr;
	b2ContactList list;

	ptr = self.GetContactList();
	while (ptr != NULL)
	{
		list.push_back(ptr->contact);
		ptr = ptr->next;
	}
	return list;
}

object b2Body_GetWorld(b2Body& self)
{
	using namespace boost::python;

	b2World* ptr = self.GetWorld();
	if (ptr != NULL)
		return object(handle<>(borrowed(static_cast<b2World_W*>(ptr)->self)));
	else
		return object();
}


static void export_body()
{
	using namespace boost::python;

	enum_<b2BodyType>("b2BodyType")
		.value("b2_staticBody", b2_staticBody)
		.value("b2_kinematicBody", b2_kinematicBody)
		.value("b2_dynamicBody", b2_dynamicBody)
	;

	class_<b2BodyDef>("b2BodyDef")
		.def_readwrite("type", &b2BodyDef::type)
		.def_readwrite("position", &b2BodyDef::position)
		.def_readwrite("angle", &b2BodyDef::angle)
		.def_readwrite("linearVelocity", &b2BodyDef::linearVelocity)
		.def_readwrite("angularVelocity", &b2BodyDef::angularVelocity)
		.def_readwrite("linearDamping", &b2BodyDef::linearDamping)
		.def_readwrite("allowSleep", &b2BodyDef::allowSleep)
		.def_readwrite("awake", &b2BodyDef::awake)
		.def_readwrite("fixedRotation", &b2BodyDef::fixedRotation)
		.def_readwrite("bullet", &b2BodyDef::bullet)
		.def_readwrite("active", &b2BodyDef::active)
		.def_readwrite("gravityScale", &b2BodyDef::gravityScale)
		.add_property("userData", b2BodyDef_GetUserData, b2BodyDef_SetUserData)
		.def("__del__", b2BodyDef__del)
	;

	class_<b2Body, boost::noncopyable, b2Body*>("b2Body", no_init)
		.def("CreateFixture", b2Body_CreateFixture1, return_internal_reference<>())
		.def("CreateFixture", b2Body_CreateFixture2, return_internal_reference<>())
		.def("DestroyFixture", b2Body_DestroyFixture)
		.def("SetTransform", &b2Body::SetTransform)
		.def("GetTransform", &b2Body::GetTransform, return_internal_reference<>())
		.def("GetPosition", &b2Body::GetPosition, return_internal_reference<>())
		.def("GetAngle", &b2Body::GetAngle)
		.def("GetWorldCenter", &b2Body::GetWorldCenter, return_internal_reference<>())
		.def("GetLocalCenter", &b2Body::GetLocalCenter, return_internal_reference<>())
		.def("SetLinearVelocity", &b2Body::SetLinearVelocity)
		.def("GetLinearVelocity", &b2Body::GetLinearVelocity)
		.def("SetAngularVelocity", &b2Body::SetAngularVelocity)
		.def("GetAngularVelocity", &b2Body::GetAngularVelocity)
		.def("ApplyForce", &b2Body::ApplyForce)
		.def("ApplyForceToCenter", &b2Body::ApplyForceToCenter)
		.def("ApplyTorque", &b2Body::ApplyTorque)
		.def("ApplyLinearImpulse", &b2Body::ApplyLinearImpulse)
		.def("ApplyAngularImpulse", &b2Body::ApplyAngularImpulse)
		.def("GetMass", &b2Body::GetMass)
		.def("GetInertia", &b2Body::GetInertia)
		.def("GetMassData", &b2Body::GetMassData)
		.def("SetMassData", &b2Body::SetMassData)
		.def("ResetMassData", &b2Body::ResetMassData)
		.def("GetWorldPoint", &b2Body::GetWorldPoint)
		.def("GetWorldVector", &b2Body::GetWorldVector)
		.def("GetLocalPoint", &b2Body::GetLocalPoint)
		.def("GetLocalVector", &b2Body::GetLocalVector)
		.def("GetLinearVelocityFromWorldPoint", &b2Body::GetLinearVelocityFromWorldPoint)
		.def("GetLinearVelocityFromLocalPoint", &b2Body::GetLinearVelocityFromLocalPoint)
		.def("GetLinearDamping", &b2Body::GetLinearDamping)
		.def("SetLinearDamping", &b2Body::SetLinearDamping)
		.def("GetAngularDamping", &b2Body::GetAngularDamping)
		.def("SetAngularDamping", &b2Body::SetAngularDamping)
		.def("GetGravityScale", &b2Body::GetGravityScale)
		.def("SetGravityScale", &b2Body::SetGravityScale)
		.def("SetType", &b2Body::SetType)
		.def("GetType", &b2Body::GetType)
		.def("SetBullet", &b2Body::SetBullet)
		.def("IsBullet", &b2Body::IsBullet)
		.def("SetSleepingAllowed", &b2Body::SetSleepingAllowed)
		.def("IsSleepingAllowed", &b2Body::IsSleepingAllowed)
		.def("SetAwake", &b2Body::SetAwake)
		.def("IsAwake", &b2Body::IsAwake)
		.def("SetActive", &b2Body::SetActive)
		.def("IsActive", &b2Body::IsActive)
		.def("SetFixedRotation", &b2Body::SetFixedRotation)
		.def("IsFixedRotation", &b2Body::IsFixedRotation)
		.def("GetFixtureList", b2Body_GetFixtureList)
		.def("GetJointList", b2Body_GetJointList)
		.def("GetContactList", b2Body_GetContactList)
		.def("GetWorld", b2Body_GetWorld)
		.def("GetUserData", b2Body_GetUserData)
		.def("SetUserData", b2Body_SetUserData)
		.def("SetPosition", b2Body_SetPosition)
		.add_property("type", &b2Body::GetType, &b2Body::SetType)
		.add_property("position", make_function(&b2Body::GetPosition, return_internal_reference<>()), b2Body_SetPosition)
		.add_property("angle", &b2Body::GetAngle)
		.add_property("worldCenter", make_function(&b2Body::GetWorldCenter, return_value_policy<copy_const_reference>()))
		.add_property("localCenter", make_function(&b2Body::GetLocalCenter, return_value_policy<copy_const_reference>()))
		.add_property("linearVelocity", &b2Body::GetLinearVelocity, &b2Body::SetLinearVelocity)
		.add_property("angularVelocity", &b2Body::GetAngularVelocity, &b2Body::SetAngularVelocity)
		.add_property("mass", &b2Body::GetMass)
		.add_property("inertia", &b2Body::GetInertia)
		.add_property("massData", b2Body_GetMassData, &b2Body::SetMassData)
		.add_property("linearDamping", &b2Body::GetLinearDamping, &b2Body::SetLinearDamping)
		.add_property("allowSleep", &b2Body::IsSleepingAllowed, &b2Body::SetSleepingAllowed)
		.add_property("awake", &b2Body::IsAwake, &b2Body::SetAwake)
		.add_property("fixedRotation", &b2Body::IsFixedRotation, &b2Body::SetFixedRotation)
		.add_property("bullet", &b2Body::IsBullet, &b2Body::SetBullet)
		.add_property("active", &b2Body::IsActive, &b2Body::SetActive)
		.add_property("gravityScale", &b2Body::GetGravityScale, &b2Body::SetGravityScale)
		.add_property("world", b2Body_GetWorld)
		.add_property("userData", b2Body_GetUserData, b2Body_SetUserData)
	;

}


void export_bodyfixture()
{
	export_fixture();
	export_body();
}

