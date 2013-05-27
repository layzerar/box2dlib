/*
 * @summary: box2d math
 * @date: 2012-11-21
 * @author: zl
 */

#include "config.h"
#include "exc.h"


using boost::python::object;

/*
 * rename overloading functions
 */
b2Vec2 (*b2AbsV2)(const b2Vec2& a) = b2Abs;
b2Mat22 (*b2AbsM2)(const b2Mat22& A) = b2Abs;

b2Vec2 (*b2ClampV2)(const b2Vec2& a, const b2Vec2& low, const b2Vec2& high) = b2ClampV2;

float32 (*b2CrossV2)(const b2Vec2& a, const b2Vec2& b) = b2Cross;
b2Vec2 (*b2CrossV2F)(const b2Vec2& a, float32 s) = b2Cross;
b2Vec2 (*b2CrossFV2)(float32 s, const b2Vec2& a) = b2Cross;
b2Vec3 (*b2CrossV3)(const b2Vec3& a, const b2Vec3& b) = b2Cross;

float32 (*b2DotV2)(const b2Vec2& a, const b2Vec2& b) = b2Dot;
float32 (*b2DotV3)(const b2Vec3& a, const b2Vec3& b) = b2Dot;

b2Vec2 (*b2MaxV2)(const b2Vec2& a, const b2Vec2& b) = b2Max;
b2Vec2 (*b2MinV2)(const b2Vec2& a, const b2Vec2& b) = b2Min;

b2Vec2 (*b2MulMV2)(const b2Mat22& A, const b2Vec2& v) = b2Mul;
b2Mat22 (*b2MulM2)(const b2Mat22& A, const b2Mat22& B) = b2Mul;
b2Vec3 (*b2MulMV3)(const b2Mat33& A, const b2Vec3& v) = b2Mul;
b2Rot (*b2MulRR)(const b2Rot& q, const b2Rot& r) = b2Mul;
b2Vec2 (*b2MulRV)(const b2Rot& q, const b2Vec2& v) = b2Mul;
b2Vec2 (*b2MulXV)(const b2Transform& T, const b2Vec2& v) = b2Mul;
b2Transform (*b2MulXX)(const b2Transform& A, const b2Transform& B) = b2Mul;

b2Vec2 (*b2MulTMV2)(const b2Mat22& A, const b2Vec2& v) = b2MulT;
b2Mat22 (*b2MulTM2)(const b2Mat22& A, const b2Mat22& B) = b2MulT;
b2Rot (*b2MulTRR)(const b2Rot& q, const b2Rot& r) = b2MulT;
b2Vec2 (*b2MulTRV)(const b2Rot& q, const b2Vec2& v) = b2MulT;
b2Vec2 (*b2MulTXV)(const b2Transform& T, const b2Vec2& v) = b2MulT;
b2Transform (*b2MulTXX)(const b2Transform& A, const b2Transform& B) = b2MulT;

float32 (*b2DistanceV2)(const b2Vec2& a, const b2Vec2& b) = b2Distance;

void (b2AABB::*b2AABB_Combine1)(const b2AABB& aabb) = &b2AABB::Combine;
void (b2AABB::*b2AABB_Combine2)(const b2AABB& aabb1, const b2AABB& aabb2) = &b2AABB::Combine;

bool (*b2TestOverlap2)(const b2AABB& a, const b2AABB& b) = b2TestOverlap;
bool (*b2TestOverlap6)(const b2Shape* shapeA, int32 indexA,
	const b2Shape* shapeB, int32 indexB,
	const b2Transform& xfA, const b2Transform& xfB) = b2TestOverlap;


/*
 * extend functions
 */

typedef std::auto_ptr<b2Vec2> b2Vec2Ref;

inline b2Vec2 operator*(const b2Vec2& a, float32 s)
{
	return b2Vec2(a.x * s, a.y * s);
}

inline b2Vec2 operator/(const b2Vec2& a, float32 s)
{
	return b2Vec2(a.x / s, a.y / s);
}

inline b2Vec2 operator/(float32 s, const b2Vec2& a)
{
	return b2Vec2(a.x / s, a.y / s);
}

inline b2Vec2 operator/=(const b2Vec2& a, float32 s)
{
	return b2Vec2(a.x / s, a.y / s);
}

inline b2Vec2 operator/=(float32 s, const b2Vec2& a)
{
	return b2Vec2(a.x / s, a.y / s);
}

inline b2Vec3 operator*(const b2Vec3& a, float32 s)
{
	return b2Vec3(a.x * s, a.y * s, a.z * s);
}

inline b2Vec3 operator/(const b2Vec3& a, float32 s)
{
	return b2Vec3(a.x / s, a.y / s, a.z / s);
}

inline b2Vec3 operator/(float32 s, const b2Vec3& a)
{
	return b2Vec3(a.x / s, a.y / s, a.z / s);
}

inline b2Vec3 operator/=(const b2Vec3& a, float32 s)
{
	return b2Vec3(a.x / s, a.y / s, a.z / s);
}

inline b2Vec3 operator/=(float32 s, const b2Vec3& a)
{
	return b2Vec3(a.x / s, a.y / s, a.z / s);
}

inline bool operator ==(const b2Vec3& a, const b2Vec3& b)
{
	return a.x == b.x && a.y == b.y && a.z == b.z;
}


/*
 * wrapper functions
 */

b2Vec2* b2Vec2__init(object v)
{
	using boost::python::extract;
	return new b2Vec2(extract<float32>(v[0]), extract<float32>(v[1]));
}

object b2Vec2__str(b2Vec2& self)
{
	using boost::format;
	using boost::python::str;
	return str((format("b2Vec2(%.2f, %.2f)") % self.x % self.y).str());
}

object b2Vec2__iter(b2Vec2& self)
{
	using boost::python::make_tuple;
	return make_tuple(self.x, self.y).attr("__iter__")();
}

float32 b2Vec2__getitem(b2Vec2& self, int32 index)
{
	if (index < -2 || index > 1) {
		IndexError();
		return 0.0f;
	}
	if (index < 0) {
		index += 2;
	}
	return (&self.x)[index];
}

void b2Vec2__setitem(b2Vec2& self, int32 index, float32 v)
{
	using boost::python::throw_error_already_set;
	if (index < -2 || index > 1) {
		IndexError();
		return;
	}
	if (index < 0) {
		index += 2;
	}
	(&self.x)[index] = v;
}

b2Vec3* b2Vec3__init(object v)
{
	using boost::python::extract;
	return new b2Vec3(extract<float32>(v[0]), extract<float32>(v[1]), extract<float32>(v[2]));
}

object b2Vec3__str(b2Vec3& self)
{
	using boost::format;
	using boost::python::str;
	return str((format("b2Vec3(%.2f, %.2f, %.2f)") % self.x % self.y % self.z).str());
}

object b2Vec3__iter(b2Vec3& self)
{
	using boost::python::make_tuple;
	return make_tuple(self.x, self.y, self.z).attr("__iter__")();
}

float32 b2Vec3__getitem(b2Vec3& self, int32 index)
{
	if (index < -3 || index > 2) {
		IndexError();
		return 0.0f;
	}
	if (index < 0) {
		index += 3;
	}
	return (&self.x)[index];
}

void b2Vec3__setitem(b2Vec3& self, int32 index, float32 v)
{
	if (index < -3 || index > 2) {
		IndexError();
		return;
	}
	if (index < 0) {
		index += 3;
	}
	(&self.x)[index] = v;
}

object b2Mat22__str(b2Mat22& self)
{
	using boost::format;
	using boost::python::str;
	return str((format("b2Mat22([%.2f, %.2f; %.2f, %.2f])") % 
		self.ex.x % self.ey.x % self.ex.y % self.ey.y).str());
}

object b2Mat33__str(b2Mat33& self)
{
	using boost::format;
	using boost::python::str;
	return str((format("b2Mat33([%.2f, %.2f, %.2f; %.2f, %.2f, %.2f; %.2f, %.2f, %.2f])") %
		self.ex.x % self.ey.x % self.ez.x % self.ex.y % self.ey.y % self.ez.y % self.ex.z % self.ey.z % self.ez.z).str());
}

object b2AABB__str(b2AABB& self)
{
	using boost::format;
	using boost::python::str;
	return str((format("b2AABB([%.2f, %.2f], [%.2f, %.2f])") % 
		self.lowerBound.x % self.lowerBound.y % self.upperBound.x % self.upperBound.y).str());
}

bool b2AABB_ContainsV(b2AABB& self, const b2Vec2& point)
{
	//If point is in aabb (including a small buffer around it), return true.
	if (point.x < (self.upperBound.x + b2_epsilon) &&
		point.x > (self.lowerBound.x - b2_epsilon) &&
		point.y < (self.upperBound.y + b2_epsilon) &&
		point.y > (self.lowerBound.y - b2_epsilon))
		return true;
	return false;
}


void export_math()
{
	using namespace boost::python;

	class_<b2Vec2>("b2Vec2")
		.def(init<b2Vec2>())
		.def(init<float32, float32>())
		.def( "__init__", make_constructor(b2Vec2__init))
		.def("SetZero", &b2Vec2::SetZero)
		.def("Set", &b2Vec2::Set)
		.def("Length", &b2Vec2::Length)
		.def("LengthSquared", &b2Vec2::LengthSquared)
		.def("Normalize", &b2Vec2::Normalize)
		.def("IsValid", &b2Vec2::IsValid)
		.def("Skew", &b2Vec2::Skew)
		.def_readwrite("x", &b2Vec2::x)
		.def_readwrite("y", &b2Vec2::y)
		.def("Dot", b2DotV2)
		.def("Cross", b2CrossV2)
		.def("Cross", b2CrossV2F)
		.def("__iter__", b2Vec2__iter)
		.def("__getitem__", b2Vec2__getitem)
		.def("__setitem__", b2Vec2__setitem)
		.def(-self)
		.def(self == other<b2Vec2>())
		.def(self + other<b2Vec2>())
		.def(self - other<b2Vec2>())
		.def(self += other<b2Vec2>())
		.def(self -= other<b2Vec2>())
		.def(self * float32())
		.def(self / float32())
		.def(self *= float32())
		.def(self /= float32())
		.def(float32() * self)
		.def(float32() / self)
		.def("__str__", &b2Vec2__str)
		.def("__repr__", &b2Vec2__str)
	;

	class_<b2Vec3>("b2Vec3")
		.def(init<b2Vec3>())
		.def(init<float32, float32, float32>())
		.def( "__init__", make_constructor(b2Vec3__init))
		.def("SetZero", &b2Vec3::SetZero)
		.def("Set", &b2Vec3::Set)
		.def_readwrite("x", &b2Vec3::x)
		.def_readwrite("y", &b2Vec3::y)
		.def_readwrite("z", &b2Vec3::z)
		.def("Dot", b2DotV3)
		.def("Cross", b2CrossV3)
		.def("__iter__", b2Vec3__iter)
		.def("__getitem__", b2Vec3__getitem)
		.def("__setitem__", b2Vec3__setitem)
		.def(-self)
		.def(self == other<b2Vec3>())
		.def(self + other<b2Vec3>())
		.def(self - other<b2Vec3>())
		.def(self += other<b2Vec3>())
		.def(self -= other<b2Vec3>())
		.def(self * float32())
		.def(self / float32())
		.def(self *= float32())
		.def(self /= float32())
		.def(float32() * self)
		.def(float32() / self)
		.def("__str__", &b2Vec3__str)
		.def("__repr__", &b2Vec3__str)
	;

	class_<b2Mat22>("b2Mat22")
		.def(init<b2Mat22>())
		.def(init<b2Vec2, b2Vec2>())
		.def(init<float32, float32, float32, float32>())
		.def("Set", &b2Mat22::Set)
		.def("SetIdentity", &b2Mat22::SetIdentity)
		.def("SetZero", &b2Mat22::SetZero)
		.def("GetInverse", &b2Mat22::GetInverse)
		.def("Solve", &b2Mat22::Solve)
		.def_readwrite("ex", &b2Mat22::ex)
		.def_readwrite("ey", &b2Mat22::ey)
		.def_readwrite("col1", &b2Mat22::ex)
		.def_readwrite("col2", &b2Mat22::ey)
		.def(self + other<b2Mat22>())
		.def("__str__", &b2Mat22__str)
		.def("__repr__", &b2Mat22__str)
	;

	class_<b2Mat33>("b2Mat33")
		.def(init<b2Mat33>())
		.def(init<b2Vec3, b2Vec3, b2Vec3>())
		.def(init<float32, float32, float32, float32, float32, float32, float32, float32, float32>())
		.def("SetZero", &b2Mat33::SetZero)
		.def("Solve33", &b2Mat33::Solve33)
		.def("Solve22", &b2Mat33::Solve22)
		.def("GetInverse22", &b2Mat33::GetInverse22)
		.def("GetSymInverse33", &b2Mat33::GetSymInverse33)
		.def_readwrite("ex", &b2Mat33::ex)
		.def_readwrite("ey", &b2Mat33::ey)
		.def_readwrite("ez", &b2Mat33::ez)
		.def_readwrite("col1", &b2Mat33::ex)
		.def_readwrite("col2", &b2Mat33::ey)
		.def_readwrite("col3", &b2Mat33::ez)
		.def("__str__", &b2Mat33__str)
		.def("__repr__", &b2Mat33__str)
	;

	class_<b2Rot>("b2Rot")
		.def(init<b2Rot>())
		.def(init<float32>())
		.def("Set", &b2Rot::Set)
		.def("SetIdentity", &b2Rot::SetIdentity)
		.def("GetAngle", &b2Rot::GetAngle)
		.def("GetXAxis", &b2Rot::GetXAxis)
		.def("GetYAxis", &b2Rot::GetYAxis)
		.def_readwrite("s", &b2Rot::s)
		.def_readwrite("c", &b2Rot::c)
		.add_property("angle", &b2Rot::GetAngle, &b2Rot::Set)
	;

	class_<b2Transform>("b2Transform")
		.def(init<b2Transform>())
		.def(init<b2Vec2, b2Rot>())
		.def("SetIdentity", &b2Transform::SetIdentity)
		.def("Set", &b2Transform::Set)
		.def_readwrite("p", &b2Transform::p)
		.def_readwrite("q", &b2Transform::q)
		.def_readwrite("position", &b2Transform::p)
		.def_readwrite("R", &b2Transform::q)
	;

	class_<b2Sweep>("b2Sweep")
		.def("GetTransform", &b2Sweep::GetTransform)
		.def("Advance", &b2Sweep::Advance)
		.def("Normalize", &b2Sweep::Normalize)
		.def_readwrite("localCenter", &b2Sweep::localCenter)
		.def_readwrite("c0", &b2Sweep::c0)
		.def_readwrite("c", &b2Sweep::c)
		.def_readwrite("a0", &b2Sweep::a0)
		.def_readwrite("a", &b2Sweep::a)
		.def_readwrite("alpha0", &b2Sweep::alpha0)
	;

	class_<b2RayCastInput>("b2RayCastInput")
		.def_readwrite("p1", &b2RayCastInput::p1)
		.def_readwrite("p2", &b2RayCastInput::p2)
		.def_readwrite("maxFraction", &b2RayCastInput::maxFraction)
	;

	class_<b2RayCastOutput>("b2RayCastOutput")
		.def_readwrite("normal", &b2RayCastOutput::normal)
		.def_readwrite("fraction", &b2RayCastOutput::fraction)
	;

	class_<b2AABB>("b2AABB")
		.def("IsValid", &b2AABB::IsValid)
		.def("GetCenter", &b2AABB::GetCenter)
		.def("GetExtents", &b2AABB::GetExtents)
		.def("GetPerimeter", &b2AABB::GetPerimeter)
		.def("Combine", b2AABB_Combine1)
		.def("Combine", b2AABB_Combine2)
		.def("Contains", &b2AABB::Contains)
		.def("Contains", b2AABB_ContainsV)
		.def("RayCast", &b2AABB::RayCast)
		.def_readwrite("lowerBound", &b2AABB::lowerBound)
		.def_readwrite("upperBound", &b2AABB::upperBound)
		.def("__contains__", &b2AABB::Contains)
		.def("__contains__", b2AABB_ContainsV)
		.def("__str__", &b2AABB__str)
		.def("__repr__", &b2AABB__str)
	;

	def("b2Cross", b2CrossV2);
	def("b2Cross", b2CrossV2F);
	def("b2Cross", b2CrossFV2);
	def("b2Cross", b2CrossV3);

	def("b2Distance", b2DistanceV2);
	def("b2DistanceSquared", b2DistanceSquared);

	def("b2Dot", b2DotV2);
	def("b2Dot", b2DotV3);

	def("b2Mul", b2MulMV2);
	def("b2Mul", b2MulM2);
	def("b2Mul", b2MulMV3);
	def("b2Mul", b2MulRR);
	def("b2Mul", b2MulRV);
	def("b2Mul", b2MulXX);
	def("b2Mul", b2MulXV);
	def("b2Mul", b2Mul22);
	def("b2Mul22", b2Mul22);

	def("b2MulT", b2MulTMV2);
	def("b2MulT", b2MulTM2);
	def("b2MulT", b2MulTRR);
	def("b2MulT", b2MulTRV);
	def("b2MulT", b2MulTXX);
	def("b2MulT", b2MulTXV);

	def("b2TestOverlap", b2TestOverlap2);
	def("b2TestOverlap", b2TestOverlap6);

	def("b2InvSqrt", b2InvSqrt);
	def("b2IsPowerOfTwo", b2IsPowerOfTwo);
	def("b2IsValid", b2IsValid);
	def("b2NextPowerOfTwo", b2NextPowerOfTwo);

	scope().attr("b2Vec2_zero") = b2Vec2_zero;

}

