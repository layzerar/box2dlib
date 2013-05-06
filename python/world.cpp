/*
 * @summary: box2d world
 * @date: 2012-11-21
 * @author: zl
 */

#include "config.h"
#include "world.h"
#include "userdata.h"
#include "containers.h"

using boost::ref;


/*
 * rename overloading functions
 */

void (b2DestructionListener::*b2DestructionListener_SayGoodbyeJ)(b2Joint* joint) = &b2DestructionListener::SayGoodbye;
void (b2DestructionListener::*b2DestructionListener_SayGoodbyeF)(b2Fixture* fixture) = &b2DestructionListener::SayGoodbye;


/*
 * extending functions
 */

b2ContactFilter* b2World_GetContactFilter(b2World& self)
{
	return self.GetContactManager().m_contactFilter;
}

b2Body* b2World_CreateBody(b2World& self, const b2BodyDef* def)
{
	using namespace boost::python;

	b2Body* body = self.CreateBody(def);
	if (body)
	{
		xincref((PyObject*)body->GetUserData());
	}
	return body;
}

void b2World_DestroyBody(b2World& self, b2Body* body)
{
	b2Assert(self.GetBodyCount() > 0);
	b2Assert(self.IsLocked() == false);

	b2Func_ClearUserData(*body);
	self.DestroyBody(body);
}

b2Joint* b2World_CreateJoint(b2World& self, const b2JointDef* def)
{
	using namespace boost::python;

	b2Joint* joint = self.CreateJoint(def);
	if (joint)
	{
		xincref((PyObject*)joint->GetUserData());
	}
	return joint;
}

void b2World_DestroyJoint(b2World& self, b2Joint* joint)
{
	b2Assert(self.IsLocked() == false);

	b2Func_ClearUserData(*joint);
	self.DestroyJoint(joint);
}

b2BodyList b2World_GetBodyList(b2World& self)
{
	b2Body* ptr;
	b2BodyList list;

	ptr = self.GetBodyList();
	while (ptr != NULL)
	{
		list.push_back(ptr);
		ptr = ptr->GetNext();
	}
	return list;
}

b2JointList b2World_GetJointList(b2World& self)
{
	b2Joint* ptr;
	b2JointList list;

	ptr = self.GetJointList();
	while (ptr != NULL)
	{
		list.push_back(ptr);
		ptr = ptr->GetNext();
	}
	return list;
}

b2ContactList b2World_GetContactList(b2World& self)
{
	b2Contact* ptr;
	b2ContactList list;

	ptr = self.GetContactList();
	while (ptr != NULL)
	{
		list.push_back(ptr);
		ptr = ptr->GetNext();
	}
	return list;
}


/*
 * wrap pure abstract class
 */
using boost::python::wrapper;
using boost::python::override;
using boost::python::error_already_set;


struct b2DestructionListener_W: b2DestructionListener, wrapper<b2DestructionListener>
{
public:
	void SayGoodbye(b2Joint* joint);
	void SayGoodbye(b2Fixture* fixture);
};

void b2DestructionListener_W::SayGoodbye(b2Joint* joint)
{
	try
	{
		this->get_override("SayGoodbye")(ref(joint));
	}
	catch (const error_already_set&)
	{
		if (PyErr_Occurred())
			PyErr_Print();
	}
}

void b2DestructionListener_W::SayGoodbye(b2Fixture* fixture)
{
	try
	{
		this->get_override("SayGoodbye")(ref(fixture));
	}
	catch (const error_already_set&)
	{
		if (PyErr_Occurred())
			PyErr_Print();
	}
}


struct b2ContactFilter_W: b2ContactFilter, wrapper<b2ContactFilter>
{
public:
	bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB);
	bool ShouldCollideDefault(b2Fixture* fixtureA, b2Fixture* fixtureB);
};

bool b2ContactFilter_W::ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB)
{
	override func = this->get_override("ShouldCollide");
	if (func)
	{
		try
		{
			return func(ref(fixtureA), ref(fixtureB));
		}
		catch (const error_already_set&)
		{
			if (PyErr_Occurred())
				PyErr_Print();

			//return false to terminate the collide
			return false;
		}
	}
	return b2ContactFilter::ShouldCollide(fixtureA, fixtureB);
}

bool b2ContactFilter_W::ShouldCollideDefault(b2Fixture* fixtureA, b2Fixture* fixtureB)
{
	return b2ContactFilter::ShouldCollide(fixtureA, fixtureB);
}


struct b2ContactListener_W: b2ContactListener, wrapper<b2ContactListener>
{
public:
	void BeginContact(b2Contact* contact);
	void BeginContactDefault(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void EndContactDefault(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void PreSolveDefault(b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
	void PostSolveDefault(b2Contact* contact, const b2ContactImpulse* impulse);
};

void b2ContactListener_W::BeginContact(b2Contact* contact)
{
	override func = this->get_override("BeginContact");
	if (func)
	{
		try
		{
			func(ref(contact));
		}
		catch (const error_already_set&)
		{
			if (PyErr_Occurred())
				PyErr_Print();
		}
	}
	else
	{
		b2ContactListener::BeginContact(contact);
	}
}

void b2ContactListener_W::BeginContactDefault(b2Contact* contact)
{
	b2ContactListener::BeginContact(contact);
}

void b2ContactListener_W::EndContact(b2Contact* contact)
{
	override func = this->get_override("EndContact");
	if (func)
	{
		try
		{
			func(ref(contact));
		}
		catch (const error_already_set&)
		{
			if (PyErr_Occurred())
				PyErr_Print();
		}
	}
	else
	{
		b2ContactListener::EndContact(contact);
	}
}

void b2ContactListener_W::EndContactDefault(b2Contact* contact)
{
	b2ContactListener::EndContact(contact);
}

void b2ContactListener_W::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	override func = this->get_override("PreSolve");
	if (func)
	{
		try
		{
			func(ref(contact), ref(oldManifold));
		}
		catch (const error_already_set&)
		{
			if (PyErr_Occurred())
				PyErr_Print();
		}
	}
	else
	{
		b2ContactListener::PreSolve(contact, oldManifold);
	}
}

void b2ContactListener_W::PreSolveDefault(b2Contact* contact, const b2Manifold* oldManifold)
{
	b2ContactListener::PreSolve(contact, oldManifold);
}

void b2ContactListener_W::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
	override func = this->get_override("PostSolve");
	if (func)
	{
		try
		{
			func(ref(contact), ref(impulse));
		}
		catch (const error_already_set&)
		{
			if (PyErr_Occurred())
				PyErr_Print();
		}
	}
	else
	{
		b2ContactListener::PostSolve(contact, impulse);
	}
}

void b2ContactListener_W::PostSolveDefault(b2Contact* contact, const b2ContactImpulse* impulse)
{
	b2ContactListener::PostSolve(contact, impulse);
}


enum b2DrawFlag
{
	e_shapeBit			= b2Draw::e_shapeBit,
	e_jointBit			= b2Draw::e_jointBit,
	e_aabbBit			= b2Draw::e_aabbBit,
	e_pairBit			= b2Draw::e_pairBit,
	e_centerOfMassBit	= b2Draw::e_centerOfMassBit,
};

struct b2Draw_W: b2Draw, wrapper<b2Draw>
{
public:
	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
	void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
	void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
	void DrawTransform(const b2Transform& xf);
};

void b2Draw_W::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	const b2Vec2List v(vertices, vertices + vertexCount);
	try
	{
		this->get_override("DrawPolygon")(&v, color);
	}
	catch (const error_already_set&)
	{
		if (PyErr_Occurred())
			PyErr_Print();
	}
}

void b2Draw_W::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	const b2Vec2List v(vertices, vertices + vertexCount);
	try
	{
		this->get_override("DrawSolidPolygon")(&v, color);
	}
	catch (const error_already_set&)
	{
		if (PyErr_Occurred())
			PyErr_Print();
	}
}

void b2Draw_W::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
	try
	{
		this->get_override("DrawCircle")(center, radius, color);
	}
	catch (const error_already_set&)
	{
		if (PyErr_Occurred())
			PyErr_Print();
	}
}

void b2Draw_W::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
	try
	{
		this->get_override("DrawSolidCircle")(center, radius, axis, color);
	}
	catch (const error_already_set&)
	{
		if (PyErr_Occurred())
			PyErr_Print();
	}
}

void b2Draw_W::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	try
	{
		this->get_override("DrawSegment")(p1, p2, color);
	}
	catch (const error_already_set&)
	{
		if (PyErr_Occurred())
			PyErr_Print();
	}
}

void b2Draw_W::DrawTransform(const b2Transform& xf)
{
	try
	{
		this->get_override("DrawTransform")(xf);
	}
	catch (const error_already_set&)
	{
		if (PyErr_Occurred())
			PyErr_Print();
	}
}


struct b2QueryCallback_W: b2QueryCallback, wrapper<b2QueryCallback>
{
public:
	bool ReportFixture(b2Fixture* fixture);
};

bool b2QueryCallback_W::ReportFixture(b2Fixture* fixture)
{
	try
	{
		return this->get_override("ReportFixture")(ref(fixture));
	}
	catch (const error_already_set&)
	{
		if (PyErr_Occurred())
			PyErr_Print();

		//return false to terminate the query
		return false;
	}
}


struct b2RayCastCallback_W: b2RayCastCallback, wrapper<b2RayCastCallback>
{
public:
	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);
};

float32 b2RayCastCallback_W::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
{
	try
	{
		return this->get_override("ReportFixture")(ref(fixture), point, normal, fraction);
	}
	catch (const error_already_set&)
	{
		if (PyErr_Occurred())
			PyErr_Print();

		//return 0 to terminate the raycast
		return 0.0f;
	}
}


b2World_W::b2World_W(PyObject* self, const b2Vec2& gravity): b2World(gravity), self(self)
{
}


void export_world()
{
	using namespace boost::python;

	class_<b2Profile>("b2Profile")
		.def_readwrite("step", &b2Profile::step)
		.def_readwrite("collide", &b2Profile::collide)
		.def_readwrite("solve", &b2Profile::solve)
		.def_readwrite("solveInit", &b2Profile::solveInit)
		.def_readwrite("solveVelocity", &b2Profile::solveVelocity)
		.def_readwrite("solvePosition", &b2Profile::solvePosition)
		.def_readwrite("broadphase", &b2Profile::broadphase)
		.def_readwrite("solveTOI", &b2Profile::solveTOI)
	;

	class_<b2DestructionListener_W, boost::noncopyable>("b2DestructionListener")
		.def("SayGoodbye", pure_virtual(b2DestructionListener_SayGoodbyeF))
		.def("SayGoodbye", pure_virtual(b2DestructionListener_SayGoodbyeJ))
	;

	class_<b2ContactFilter_W, boost::noncopyable>("b2ContactFilter")
		.def("ShouldCollide", &b2ContactFilter::ShouldCollide, &b2ContactFilter_W::ShouldCollideDefault)
	;

	class_<b2ContactListener_W, boost::noncopyable>("b2ContactListener")
		.def("BeginContact", &b2ContactListener::BeginContact, &b2ContactListener_W::BeginContactDefault)
		.def("EndContact", &b2ContactListener::EndContact, &b2ContactListener_W::BeginContactDefault)
		.def("PreSolve", &b2ContactListener::PreSolve, &b2ContactListener_W::PreSolveDefault)
		.def("PostSolve", &b2ContactListener::PostSolve, &b2ContactListener_W::PostSolveDefault)
	;

	enum_<b2DrawFlag>("b2DrawFlag")
		.value("e_shapeBit", e_shapeBit)
		.value("e_jointBit", e_jointBit)
		.value("e_aabbBit", e_aabbBit)
		.value("e_pairBit", e_pairBit)
		.value("e_centerOfMassBit", e_centerOfMassBit)
	;

	class_<b2Draw_W, boost::noncopyable>("b2Draw")
		.def("SetFlags", &b2Draw::SetFlags)
		.def("GetFlags", &b2Draw::GetFlags)
		.def("AppendFlags", &b2Draw::AppendFlags)
		.def("ClearFlags", &b2Draw::ClearFlags)
		.def("DrawPolygon", pure_virtual(&b2Draw::DrawPolygon))
		.def("DrawSolidPolygon", pure_virtual(&b2Draw::DrawSolidPolygon))
		.def("DrawCircle", pure_virtual(&b2Draw::DrawCircle))
		.def("DrawSolidCircle", pure_virtual(&b2Draw::DrawSolidCircle))
		.def("DrawSegment", pure_virtual(&b2Draw::DrawSegment))
		.def("DrawTransform", pure_virtual(&b2Draw::DrawTransform))
		.def_readonly("e_shapeBit", e_shapeBit)
		.def_readonly("e_jointBit", e_jointBit)
		.def_readonly("e_aabbBit", e_aabbBit)
		.def_readonly("e_pairBit", e_pairBit)
		.def_readonly("e_centerOfMassBit", e_centerOfMassBit)
	;

	class_<b2QueryCallback_W, boost::noncopyable>("b2QueryCallback")
		.def("ReportFixture", pure_virtual(&b2QueryCallback::ReportFixture))
	;

	class_<b2RayCastCallback_W, boost::noncopyable>("b2RayCastCallback")
		.def("ReportFixture", pure_virtual(&b2RayCastCallback::ReportFixture))
	;

	class_<b2World, b2World_W , boost::noncopyable>("b2World", init<optional<b2Vec2> >())
		.def("SetDestructionListener", &b2World::SetDestructionListener, with_custodian_and_ward<1, 2>())
		.def("SetContactFilter", &b2World::SetContactFilter, with_custodian_and_ward<1, 2>())
		.def("SetContactListener", &b2World::SetContactListener, with_custodian_and_ward<1, 2>())
		.def("SetDebugDraw", &b2World::SetDebugDraw, with_custodian_and_ward<1, 2>())
		.def("GetContactFilter", b2World_GetContactFilter, return_internal_reference<>())
		.def("CreateBody", b2World_CreateBody, return_internal_reference<>())
		.def("DestroyBody", b2World_DestroyBody)
		.def("CreateJoint", b2World_CreateJoint, return_internal_reference<>())
		.def("DestroyJoint", b2World_DestroyJoint)
		.def("Step", &b2World::Step)
		.def("ClearForces", &b2World::ClearForces)
		.def("DrawDebugData", &b2World::DrawDebugData)
		.def("QueryAABB", &b2World::QueryAABB)
		.def("RayCast", &b2World::RayCast)
		.def("GetBodyList", b2World_GetBodyList)
		.def("GetJointList", b2World_GetJointList)
		.def("GetContactList", b2World_GetContactList)
		.def("SetAllowSleeping", &b2World::SetAllowSleeping)
		.def("GetAllowSleeping", &b2World::GetAllowSleeping)
		.def("SetWarmStarting", &b2World::SetWarmStarting)
		.def("GetWarmStarting", &b2World::GetWarmStarting)
		.def("SetContinuousPhysics", &b2World::SetContinuousPhysics)
		.def("GetContinuousPhysics", &b2World::GetContinuousPhysics)
		.def("SetSubStepping", &b2World::SetSubStepping)
		.def("GetSubStepping", &b2World::GetSubStepping)
		.def("GetProxyCount", &b2World::GetProxyCount)
		.def("GetBodyCount", &b2World::GetBodyCount)
		.def("GetJointCount", &b2World::GetJointCount)
		.def("GetContactCount", &b2World::GetContactCount)
		.def("GetTreeHeight", &b2World::GetTreeHeight)
		.def("GetTreeBalance", &b2World::GetTreeBalance)
		.def("GetTreeQuality", &b2World::GetTreeQuality)
		.def("SetGravity", &b2World::SetGravity)
		.def("GetGravity", &b2World::GetGravity)
		.def("IsLocked", &b2World::IsLocked)
		.def("SetAutoClearForces", &b2World::SetAutoClearForces)
		.def("GetAutoClearForces", &b2World::GetAutoClearForces)
		.def("GetProfile", &b2World::GetProfile, return_value_policy<copy_const_reference>())
		.add_property("allowSleeping", &b2World::GetAllowSleeping, &b2World::SetAllowSleeping)
		.add_property("warmStarting", &b2World::GetWarmStarting, &b2World::SetWarmStarting)
		.add_property("continuousPhysics", &b2World::GetContinuousPhysics, &b2World::SetContinuousPhysics)
		.add_property("subStepping", &b2World::GetSubStepping, &b2World::SetSubStepping)
		.add_property("proxyCount", &b2World::GetProxyCount)
		.add_property("bodyCount", &b2World::GetBodyCount)
		.add_property("jointCount", &b2World::GetJointCount)
		.add_property("contactCount", &b2World::GetContactCount)
		.add_property("treeHeight", &b2World::GetTreeHeight)
		.add_property("treeBalance", &b2World::GetTreeBalance)
		.add_property("treeQuality", &b2World::GetTreeQuality)
		.add_property("gravity", &b2World::GetGravity, &b2World::SetGravity)
		.add_property("isLocked", &b2World::IsLocked)
		.add_property("autoClearForces", &b2World::GetAutoClearForces, &b2World::SetAutoClearForces)
	;
}

