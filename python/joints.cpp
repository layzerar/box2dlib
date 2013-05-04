/*
 * @summary: box2d joints
 * @date: 2012-11-21
 * @author: zl
 */

#include "config.h"
#include "userdata.h"

using boost::python::object;


/*
 * extend functions
 */
void (*b2JointDef__del)(b2JointDef&) = b2Attr_ClearUserData;
void (*b2JointDef_SetUserData)(b2JointDef& self, object userData) = b2Attr_SetUserData;
object (*b2JointDef_GetUserData)(b2JointDef& self) = b2Attr_GetUserData;


static void export_jointdef()
{
	using namespace boost::python;

	enum_<b2JointType>("b2JointType")
		.value("e_unknownJoint", e_unknownJoint)
		.value("e_revoluteJoint", e_revoluteJoint)
		.value("e_prismaticJoint", e_prismaticJoint)
		.value("e_distanceJoint", e_distanceJoint)
		.value("e_pulleyJoint", e_pulleyJoint)
		.value("e_mouseJoint", e_mouseJoint)
		.value("e_gearJoint", e_gearJoint)
		.value("e_wheelJoint", e_wheelJoint)
		.value("e_weldJoint", e_weldJoint)
		.value("e_frictionJoint", e_frictionJoint)
		.value("e_ropeJoint", e_ropeJoint)
	;

	enum_<b2LimitState>("b2LimitState")
		.value("e_inactiveLimit", e_inactiveLimit)
		.value("e_atLowerLimit", e_atLowerLimit)
		.value("e_atUpperLimit", e_atUpperLimit)
		.value("e_equalLimits", e_equalLimits)
	;

	class_<b2JointDef>("b2JointDef", no_init)
		.def_readwrite("type", &b2JointDef::type)
		.def_readwrite("bodyA", &b2JointDef::bodyA)
		.def_readwrite("bodyB", &b2JointDef::bodyB)
		.def_readwrite("collideConnected", &b2JointDef::collideConnected)
		.add_property("userData", b2JointDef_GetUserData, b2JointDef_SetUserData)
		.def("__del__", b2JointDef__del)
	;

	class_<b2DistanceJointDef, bases<b2JointDef> >("b2DistanceJointDef")
		.def("Initialize", &b2DistanceJointDef::Initialize)
		.def_readwrite("localAnchorA", &b2DistanceJointDef::localAnchorA)
		.def_readwrite("localAnchorB", &b2DistanceJointDef::localAnchorB)
		.def_readwrite("length", &b2DistanceJointDef::length)
		.def_readwrite("frequencyHz", &b2DistanceJointDef::frequencyHz)
		.def_readwrite("dampingRatio", &b2DistanceJointDef::dampingRatio)
	;

	class_<b2FrictionJointDef, bases<b2JointDef> >("b2FrictionJointDef")
		.def("Initialize", &b2FrictionJointDef::Initialize)
		.def_readwrite("localAnchorA", &b2FrictionJointDef::localAnchorA)
		.def_readwrite("localAnchorB", &b2FrictionJointDef::localAnchorB)
		.def_readwrite("maxForce", &b2FrictionJointDef::maxForce)
		.def_readwrite("maxTorque", &b2FrictionJointDef::maxTorque)
	;

	class_<b2GearJointDef, bases<b2JointDef> >("b2GearJointDef")
		.def_readwrite("joint1", &b2GearJointDef::joint1)
		.def_readwrite("joint2", &b2GearJointDef::joint2)
		.def_readwrite("ratio", &b2GearJointDef::ratio)
	;

	class_<b2MouseJointDef, bases<b2JointDef> >("b2MouseJointDef")
		.def_readwrite("target", &b2MouseJointDef::target)
		.def_readwrite("maxForce", &b2MouseJointDef::maxForce)
		.def_readwrite("frequencyHz", &b2MouseJointDef::frequencyHz)
		.def_readwrite("dampingRatio", &b2MouseJointDef::dampingRatio)
	;

	class_<b2PrismaticJointDef, bases<b2JointDef> >("b2PrismaticJointDef")
		.def("Initialize", &b2PrismaticJointDef::Initialize)
		.def_readwrite("localAnchorA", &b2PrismaticJointDef::localAnchorA)
		.def_readwrite("localAnchorB", &b2PrismaticJointDef::localAnchorB)
		.def_readwrite("localAxisA", &b2PrismaticJointDef::localAxisA)
		.def_readwrite("referenceAngle", &b2PrismaticJointDef::referenceAngle)
		.def_readwrite("enableLimit", &b2PrismaticJointDef::enableLimit)
		.def_readwrite("lowerTranslation", &b2PrismaticJointDef::lowerTranslation)
		.def_readwrite("upperTranslation", &b2PrismaticJointDef::upperTranslation)
		.def_readwrite("enableMotor", &b2PrismaticJointDef::enableMotor)
		.def_readwrite("maxMotorForce", &b2PrismaticJointDef::maxMotorForce)
		.def_readwrite("motorSpeed", &b2PrismaticJointDef::motorSpeed)
	;

	class_<b2PulleyJointDef, bases<b2JointDef> >("b2PulleyJointDef")
		.def("Initialize", &b2PulleyJointDef::Initialize)
		.def_readwrite("groundAnchorA", &b2PulleyJointDef::groundAnchorA)
		.def_readwrite("groundAnchorB", &b2PulleyJointDef::groundAnchorB)
		.def_readwrite("localAnchorA", &b2PulleyJointDef::localAnchorA)
		.def_readwrite("localAnchorB", &b2PulleyJointDef::localAnchorB)
		.def_readwrite("lengthA", &b2PulleyJointDef::lengthA)
		.def_readwrite("lengthB", &b2PulleyJointDef::lengthB)
		.def_readwrite("ratio", &b2PulleyJointDef::ratio)
	;

	class_<b2RevoluteJointDef, bases<b2JointDef> >("b2RevoluteJointDef")
		.def("Initialize", &b2RevoluteJointDef::Initialize)
		.def_readwrite("localAnchorA", &b2RevoluteJointDef::localAnchorA)
		.def_readwrite("localAnchorB", &b2RevoluteJointDef::localAnchorB)
		.def_readwrite("referenceAngle", &b2RevoluteJointDef::referenceAngle)
		.def_readwrite("enableLimit", &b2RevoluteJointDef::enableLimit)
		.def_readwrite("lowerAngle", &b2RevoluteJointDef::lowerAngle)
		.def_readwrite("upperAngle", &b2RevoluteJointDef::upperAngle)
		.def_readwrite("enableMotor", &b2RevoluteJointDef::enableMotor)
		.def_readwrite("motorSpeed", &b2RevoluteJointDef::motorSpeed)
		.def_readwrite("maxMotorTorque", &b2RevoluteJointDef::maxMotorTorque)
	;

	class_<b2RopeJointDef, bases<b2JointDef> >("b2RopeJointDef")
		.def_readwrite("localAnchorA", &b2RopeJointDef::localAnchorA)
		.def_readwrite("localAnchorB", &b2RopeJointDef::localAnchorB)
		.def_readwrite("maxLength", &b2RopeJointDef::maxLength)
	;

	class_<b2WeldJointDef, bases<b2JointDef> >("b2WeldJointDef")
		.def("Initialize", &b2WeldJointDef::Initialize)
		.def_readwrite("localAnchorA", &b2WeldJointDef::localAnchorA)
		.def_readwrite("localAnchorB", &b2WeldJointDef::localAnchorB)
		.def_readwrite("referenceAngle", &b2WeldJointDef::referenceAngle)
		.def_readwrite("frequencyHz", &b2WeldJointDef::frequencyHz)
		.def_readwrite("dampingRatio", &b2WeldJointDef::dampingRatio)
	;

	class_<b2WheelJointDef, bases<b2JointDef> >("b2WheelJointDef")
		.def("Initialize", &b2WheelJointDef::Initialize)
		.def_readwrite("localAnchorA", &b2WheelJointDef::localAnchorA)
		.def_readwrite("localAnchorB", &b2WheelJointDef::localAnchorB)
		.def_readwrite("localAxisA", &b2WheelJointDef::localAxisA)
		.def_readwrite("enableMotor", &b2WheelJointDef::enableMotor)
		.def_readwrite("maxMotorTorque", &b2WheelJointDef::maxMotorTorque)
		.def_readwrite("motorSpeed", &b2WheelJointDef::motorSpeed)
		.def_readwrite("frequencyHz", &b2WheelJointDef::frequencyHz)
		.def_readwrite("dampingRatio", &b2WheelJointDef::dampingRatio)
	;
}


/*
 * rename overloading functions
 */
void (*b2Joint_SetUserData)(b2Joint& self, object userData) = b2Func_SetUserData;
object (*b2Joint_GetUserData)(b2Joint& self) = b2Func_GetUserData;


static void export_jointobj()
{
	using namespace boost::python;

	class_<b2Joint, boost::noncopyable, b2Joint*>("b2Joint", no_init)
		.def("GetType", &b2Joint::GetType)
		.def("GetBodyA", &b2Joint::GetBodyA, return_internal_reference<>())
		.def("GetBodyB", &b2Joint::GetBodyB, return_internal_reference<>())
		.def("GetAnchorA", pure_virtual(&b2Joint::GetAnchorA))
		.def("GetAnchorB", pure_virtual(&b2Joint::GetAnchorB))
		.def("GetReactionForce", pure_virtual(&b2Joint::GetReactionForce))
		.def("GetReactionTorque", pure_virtual(&b2Joint::GetReactionTorque))
		.def("IsActive", &b2Joint::IsActive)
		.def("GetCollideConnected", &b2Joint::GetCollideConnected)
		.def("GetUserData", b2Joint_GetUserData)
		.def("SetUserData", b2Joint_SetUserData)
		.add_property("type", &b2Joint::GetType)
		.add_property("bodyA", make_function(&b2Joint::GetBodyA, return_internal_reference<>()))
		.add_property("bodyB", make_function(&b2Joint::GetBodyB, return_internal_reference<>()))
		.add_property("anchorA", &b2Joint::GetAnchorA)
		.add_property("anchorB", &b2Joint::GetAnchorB)
		.add_property("reactionForce", &b2Joint::GetReactionForce)
		.add_property("reactionTorque", &b2Joint::GetReactionTorque)
		.add_property("active", &b2Joint::IsActive)
		.add_property("collideConnected", &b2Joint::GetCollideConnected)
		.add_property("userData", b2Joint_GetUserData, b2Joint_SetUserData)
	;

	class_<b2DistanceJoint, bases<b2Joint>, boost::noncopyable>("b2DistanceJoint", no_init)
		.def("GetLocalAnchorA", &b2DistanceJoint::GetLocalAnchorA, return_value_policy<copy_const_reference>())
		.def("GetLocalAnchorB", &b2DistanceJoint::GetLocalAnchorB, return_value_policy<copy_const_reference>())
		.def("SetLength", &b2DistanceJoint::SetLength)
		.def("GetLength", &b2DistanceJoint::GetLength)
		.def("SetFrequency", &b2DistanceJoint::SetFrequency)
		.def("GetFrequency", &b2DistanceJoint::GetFrequency)
		.def("SetDampingRatio", &b2DistanceJoint::SetDampingRatio)
		.def("GetDampingRatio", &b2DistanceJoint::GetDampingRatio)
		.add_property("localAnchorA", make_function(&b2DistanceJoint::GetLocalAnchorA, return_value_policy<copy_const_reference>()))
		.add_property("localAnchorB", make_function(&b2DistanceJoint::GetLocalAnchorB, return_value_policy<copy_const_reference>()))
		.add_property("length", &b2DistanceJoint::GetLength, &b2DistanceJoint::SetLength)
		.add_property("frequencyHz", &b2DistanceJoint::GetFrequency, &b2DistanceJoint::SetFrequency)
		.add_property("dampingRatio", &b2DistanceJoint::GetDampingRatio, &b2DistanceJoint::SetDampingRatio)
	;

	class_<b2FrictionJoint, bases<b2Joint>, boost::noncopyable>("b2FrictionJoint", no_init)
		.def("GetLocalAnchorA", &b2FrictionJoint::GetLocalAnchorA, return_value_policy<copy_const_reference>())
		.def("GetLocalAnchorB", &b2FrictionJoint::GetLocalAnchorB, return_value_policy<copy_const_reference>())
		.def("SetMaxForce", &b2FrictionJoint::SetMaxForce)
		.def("GetMaxForce", &b2FrictionJoint::GetMaxForce)
		.def("SetMaxTorque", &b2FrictionJoint::SetMaxTorque)
		.def("GetMaxTorque", &b2FrictionJoint::GetMaxTorque)
		.add_property("localAnchorA", make_function(&b2FrictionJoint::GetLocalAnchorA, return_value_policy<copy_const_reference>()))
		.add_property("localAnchorB", make_function(&b2FrictionJoint::GetLocalAnchorB, return_value_policy<copy_const_reference>()))
		.add_property("maxForce", &b2FrictionJoint::GetMaxForce, &b2FrictionJoint::SetMaxForce)
		.add_property("maxTorque", &b2FrictionJoint::GetMaxTorque, &b2FrictionJoint::SetMaxTorque)
	;

	class_<b2GearJoint, bases<b2Joint>, boost::noncopyable>("b2GearJoint", no_init)
		.def("GetJoint1", &b2GearJoint::GetJoint1, return_internal_reference<>())
		.def("GetJoint2", &b2GearJoint::GetJoint2, return_internal_reference<>())
		.def("SetRatio", &b2GearJoint::SetRatio)
		.def("GetRatio", &b2GearJoint::GetRatio)
		.add_property("joint1", make_function(&b2GearJoint::GetJoint1, return_internal_reference<>()))
		.add_property("joint2", make_function(&b2GearJoint::GetJoint2, return_internal_reference<>()))
		.add_property("ratio", &b2GearJoint::GetRatio, &b2GearJoint::SetRatio)
	;

	class_<b2MouseJoint, bases<b2Joint>, boost::noncopyable>("b2MouseJoint", no_init)
		.def("SetTarget", &b2MouseJoint::SetTarget)
		.def("GetTarget", &b2MouseJoint::GetTarget, return_value_policy<copy_const_reference>())
		.def("SetMaxForce", &b2MouseJoint::SetMaxForce)
		.def("GetMaxForce", &b2MouseJoint::GetMaxForce)
		.def("SetFrequency", &b2MouseJoint::SetFrequency)
		.def("GetFrequency", &b2MouseJoint::GetFrequency)
		.def("SetDampingRatio", &b2MouseJoint::SetDampingRatio)
		.def("GetDampingRatio", &b2MouseJoint::GetDampingRatio)
		.add_property("target", make_function(&b2MouseJoint::GetTarget, return_value_policy<copy_const_reference>()), &b2MouseJoint::SetTarget)
		.add_property("maxForce", &b2MouseJoint::GetMaxForce, &b2MouseJoint::SetMaxForce)
		.add_property("frequencyHz", &b2MouseJoint::GetFrequency, &b2MouseJoint::SetFrequency)
		.add_property("dampingRatio", &b2MouseJoint::GetDampingRatio, &b2MouseJoint::SetDampingRatio)
	;

	class_<b2PrismaticJoint, bases<b2Joint>, boost::noncopyable>("b2PrismaticJoint", no_init)
		.def("GetLocalAnchorA", &b2PrismaticJoint::GetLocalAnchorA, return_value_policy<copy_const_reference>())
		.def("GetLocalAnchorB", &b2PrismaticJoint::GetLocalAnchorB, return_value_policy<copy_const_reference>())
		.def("GetLocalAxisA", &b2PrismaticJoint::GetLocalAxisA, return_value_policy<copy_const_reference>())
		.def("GetReferenceAngle", &b2PrismaticJoint::GetReferenceAngle)
		.def("GetJointTranslation", &b2PrismaticJoint::GetJointTranslation)
		.def("GetJointSpeed", &b2PrismaticJoint::GetJointSpeed)
		.def("IsLimitEnabled", &b2PrismaticJoint::IsLimitEnabled)
		.def("EnableLimit", &b2PrismaticJoint::EnableLimit)
		.def("GetLowerLimit", &b2PrismaticJoint::GetLowerLimit)
		.def("GetUpperLimit", &b2PrismaticJoint::GetUpperLimit)
		.def("SetLimits", &b2PrismaticJoint::SetLimits)
		.def("IsMotorEnabled", &b2PrismaticJoint::IsMotorEnabled)
		.def("EnableMotor", &b2PrismaticJoint::EnableMotor)
		.def("SetMotorSpeed", &b2PrismaticJoint::SetMotorSpeed)
		.def("GetMotorSpeed", &b2PrismaticJoint::GetMotorSpeed)
		.def("SetMaxMotorForce", &b2PrismaticJoint::SetMaxMotorForce)
		.def("GetMaxMotorForce", &b2PrismaticJoint::GetMaxMotorForce)
		.def("GetMotorForce", &b2PrismaticJoint::GetMotorForce)
		.add_property("localAnchorA", make_function(&b2PrismaticJoint::GetLocalAnchorA, return_value_policy<copy_const_reference>()))
		.add_property("localAnchorB", make_function(&b2PrismaticJoint::GetLocalAnchorB, return_value_policy<copy_const_reference>()))
		.add_property("localAxisA", make_function(&b2PrismaticJoint::GetLocalAxisA, return_value_policy<copy_const_reference>()))
		.add_property("referenceAngle", &b2PrismaticJoint::GetReferenceAngle)
		.add_property("enableLimit", &b2PrismaticJoint::IsLimitEnabled, &b2PrismaticJoint::EnableLimit)
		.add_property("lowerTranslation", &b2PrismaticJoint::GetLowerLimit)
		.add_property("upperTranslation", &b2PrismaticJoint::GetUpperLimit)
		.add_property("enableMotor", &b2PrismaticJoint::IsMotorEnabled, &b2PrismaticJoint::EnableMotor)
		.add_property("maxMotorForce", &b2PrismaticJoint::GetMaxMotorForce, &b2PrismaticJoint::SetMaxMotorForce)
		.add_property("motorSpeed", &b2PrismaticJoint::GetMotorSpeed, &b2PrismaticJoint::SetMotorSpeed)
		.add_property("jointTranslation", &b2PrismaticJoint::GetJointTranslation)
		.add_property("jointSpeed", &b2PrismaticJoint::GetJointSpeed)
		.add_property("motorForce", &b2PrismaticJoint::GetMotorForce)
	;

	class_<b2PulleyJoint, bases<b2Joint>, boost::noncopyable>("b2PulleyJoint", no_init)
		.def("GetGroundAnchorA", &b2PulleyJoint::GetGroundAnchorA)
		.def("GetGroundAnchorB", &b2PulleyJoint::GetGroundAnchorB)
		.def("GetLengthA", &b2PulleyJoint::GetLengthA)
		.def("GetLengthB", &b2PulleyJoint::GetLengthB)
		.def("GetRatio", &b2PulleyJoint::GetRatio)
		.def("GetCurrentLengthA", &b2PulleyJoint::GetCurrentLengthA)
		.def("GetCurrentLengthB", &b2PulleyJoint::GetCurrentLengthB)
		.add_property("groundAnchorA", &b2PulleyJoint::GetGroundAnchorA)
		.add_property("groundAnchorB", &b2PulleyJoint::GetGroundAnchorB)
		.add_property("lengthA", &b2PulleyJoint::GetLengthA)
		.add_property("lengthB", &b2PulleyJoint::GetLengthB)
		.add_property("ratio", &b2PulleyJoint::GetRatio)
		.add_property("currentLengthA", &b2PulleyJoint::GetCurrentLengthA)
		.add_property("currentLengthB", &b2PulleyJoint::GetCurrentLengthB)
	;

	class_<b2RevoluteJoint, bases<b2Joint>, boost::noncopyable>("b2RevoluteJoint", no_init)
		.def("GetLocalAnchorA", &b2RevoluteJoint::GetLocalAnchorA, return_value_policy<copy_const_reference>())
		.def("GetLocalAnchorB", &b2RevoluteJoint::GetLocalAnchorB, return_value_policy<copy_const_reference>())
		.def("GetReferenceAngle", &b2RevoluteJoint::GetReferenceAngle)
		.def("GetJointAngle", &b2RevoluteJoint::GetJointAngle)
		.def("GetJointSpeed", &b2RevoluteJoint::GetJointSpeed)
		.def("IsLimitEnabled", &b2RevoluteJoint::IsLimitEnabled)
		.def("EnableLimit", &b2RevoluteJoint::EnableLimit)
		.def("GetLowerLimit", &b2RevoluteJoint::GetLowerLimit)
		.def("GetUpperLimit", &b2RevoluteJoint::GetUpperLimit)
		.def("SetLimits", &b2RevoluteJoint::SetLimits)
		.def("IsMotorEnabled", &b2RevoluteJoint::IsMotorEnabled)
		.def("EnableMotor", &b2RevoluteJoint::EnableMotor)
		.def("SetMotorSpeed", &b2RevoluteJoint::SetMotorSpeed)
		.def("GetMotorSpeed", &b2RevoluteJoint::GetMotorSpeed)
		.def("SetMaxMotorTorque", &b2RevoluteJoint::SetMaxMotorTorque)
		.def("GetMaxMotorTorque", &b2RevoluteJoint::GetMaxMotorTorque)
		.def("GetMotorTorque", &b2RevoluteJoint::GetMotorTorque)
		.add_property("localAnchorA", make_function(&b2RevoluteJoint::GetLocalAnchorA, return_value_policy<copy_const_reference>()))
		.add_property("localAnchorB", make_function(&b2RevoluteJoint::GetLocalAnchorB, return_value_policy<copy_const_reference>()))
		.add_property("referenceAngle", &b2RevoluteJoint::GetReferenceAngle)
		.add_property("enableLimit", &b2RevoluteJoint::IsLimitEnabled, &b2RevoluteJoint::EnableLimit)
		.add_property("lowerAngle", &b2RevoluteJoint::GetLowerLimit)
		.add_property("upperAngle", &b2RevoluteJoint::GetUpperLimit)
		.add_property("enableMotor", &b2RevoluteJoint::IsMotorEnabled, &b2RevoluteJoint::EnableMotor)
		.add_property("motorSpeed", &b2RevoluteJoint::GetMotorSpeed, &b2RevoluteJoint::SetMotorSpeed)
		.add_property("maxMotorTorque", &b2RevoluteJoint::GetMaxMotorTorque, &b2RevoluteJoint::SetMaxMotorTorque)
		.add_property("jointAngle", &b2RevoluteJoint::GetJointAngle)
		.add_property("jointSpeed", &b2RevoluteJoint::GetJointSpeed)
		.add_property("motorTorque", &b2RevoluteJoint::GetMotorTorque)
	;

	class_<b2RopeJoint, bases<b2Joint>, boost::noncopyable>("b2RopeJoint", no_init)
		.def("GetLocalAnchorA", &b2RopeJoint::GetLocalAnchorA, return_value_policy<copy_const_reference>())
		.def("GetLocalAnchorB", &b2RopeJoint::GetLocalAnchorB, return_value_policy<copy_const_reference>())
		.def("SetMaxLength", &b2RopeJoint::SetMaxLength)
		.def("GetMaxLength", &b2RopeJoint::GetMaxLength)
		.def("GetLimitState", &b2RopeJoint::GetLimitState)
		.add_property("localAnchorA", make_function(&b2RopeJoint::GetLocalAnchorA, return_value_policy<copy_const_reference>()))
		.add_property("localAnchorB", make_function(&b2RopeJoint::GetLocalAnchorB, return_value_policy<copy_const_reference>()))
		.add_property("maxLength", &b2RopeJoint::GetMaxLength, &b2RopeJoint::SetMaxLength)
	;

	class_<b2WeldJoint, bases<b2Joint>, boost::noncopyable>("b2WeldJoint", no_init)
		.def("GetLocalAnchorA", &b2WeldJoint::GetLocalAnchorA, return_value_policy<copy_const_reference>())
		.def("GetLocalAnchorB", &b2WeldJoint::GetLocalAnchorB, return_value_policy<copy_const_reference>())
		.def("GetReferenceAngle", &b2WeldJoint::GetReferenceAngle)
		.def("SetFrequency", &b2WeldJoint::SetFrequency)
		.def("GetFrequency", &b2WeldJoint::GetFrequency)
		.def("SetDampingRatio", &b2WeldJoint::SetDampingRatio)
		.def("GetDampingRatio", &b2WeldJoint::GetDampingRatio)
		.add_property("localAnchorA", make_function(&b2WeldJoint::GetLocalAnchorA, return_value_policy<copy_const_reference>()))
		.add_property("localAnchorB", make_function(&b2WeldJoint::GetLocalAnchorB, return_value_policy<copy_const_reference>()))
		.add_property("referenceAngle", &b2WeldJoint::GetReferenceAngle)
		.add_property("frequencyHz", &b2WeldJoint::GetFrequency, &b2WeldJoint::SetFrequency)
		.add_property("dampingRatio", &b2WeldJoint::GetDampingRatio, &b2WeldJoint::SetDampingRatio)
	;

	class_<b2WheelJoint, bases<b2Joint>, boost::noncopyable>("b2WheelJoint", no_init)
		.def("GetLocalAnchorA", &b2WheelJoint::GetLocalAnchorA, return_value_policy<copy_const_reference>())
		.def("GetLocalAnchorB", &b2WheelJoint::GetLocalAnchorB, return_value_policy<copy_const_reference>())
		.def("GetLocalAxisA", &b2WheelJoint::GetLocalAxisA, return_value_policy<copy_const_reference>())
		.def("GetJointTranslation", &b2WheelJoint::GetJointTranslation)
		.def("GetJointSpeed", &b2WheelJoint::GetJointSpeed)
		.def("IsMotorEnabled", &b2WheelJoint::IsMotorEnabled)
		.def("EnableMotor", &b2WheelJoint::EnableMotor)
		.def("SetMotorSpeed", &b2WheelJoint::SetMotorSpeed)
		.def("GetMotorSpeed", &b2WheelJoint::GetMotorSpeed)
		.def("SetMaxMotorTorque", &b2WheelJoint::SetMaxMotorTorque)
		.def("GetMaxMotorTorque", &b2WheelJoint::GetMaxMotorTorque)
		.def("GetMotorTorque", &b2WheelJoint::GetMotorTorque)
		.def("SetSpringFrequencyHz", &b2WheelJoint::SetSpringFrequencyHz)
		.def("GetSpringFrequencyHz", &b2WheelJoint::GetSpringFrequencyHz)
		.def("SetSpringDampingRatio", &b2WheelJoint::SetSpringDampingRatio)
		.def("GetSpringDampingRatio", &b2WheelJoint::GetSpringDampingRatio)
		.add_property("localAnchorA", make_function(&b2WheelJoint::GetLocalAnchorA, return_value_policy<copy_const_reference>()))
		.add_property("localAnchorB", make_function(&b2WheelJoint::GetLocalAnchorB, return_value_policy<copy_const_reference>()))
		.add_property("localAxisA", make_function(&b2WheelJoint::GetLocalAxisA, return_value_policy<copy_const_reference>()))
		.add_property("enableMotor", &b2WheelJoint::IsMotorEnabled, &b2WheelJoint::EnableMotor)
		.add_property("motorSpeed", &b2WheelJoint::GetMotorSpeed, &b2WheelJoint::SetMotorSpeed)
		.add_property("maxMotorTorque", &b2WheelJoint::GetMaxMotorTorque, &b2WheelJoint::SetMaxMotorTorque)
		.add_property("frequencyHz", &b2WheelJoint::GetSpringFrequencyHz, &b2WheelJoint::SetSpringFrequencyHz)
		.add_property("dampingRatio", &b2WheelJoint::GetSpringDampingRatio, &b2WheelJoint::SetSpringDampingRatio)
		.add_property("jointTranslation", &b2WheelJoint::GetJointTranslation)
		.add_property("jointSpeed", &b2WheelJoint::GetJointSpeed)
		.add_property("motorTorque", &b2WheelJoint::GetMotorTorque)
	;

}


void export_joints()
{
	export_jointdef();
	export_jointobj();
}
