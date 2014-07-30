/*
 * @summary: box2d misc
 * @date: 2012-11-21
 * @author: zl
 */

#include "config.h"
#include "exc.h"


using boost::python::object;


/*
 * wrapper functions
 */

object b2Color__iter(b2Color& self)
{
	using boost::python::make_tuple;
	return make_tuple(self.r, self.g, self.b, self.a).attr("__iter__")();
}

float32 b2Color__getitem(b2Color& self, int32 index)
{
	if (index < -4 || index > 3) {
		IndexError();
		return 0.0f;
	}
	if (index < 0) {
		index += 4;
	}
	return (&self.r)[index];
}

void b2Color__setitem(b2Color& self, int32 index, float32 v)
{
	if (index < -4 || index > 3) {
		IndexError();
		return;
	}
	if (index < 0) {
		index += 4;
	}
	(&self.r)[index] = v;
}

inline b2Color operator*(const b2Color& c, float32 s)
{
	return b2Color(c.r * s, c.g * s, c.b * s, c.a);
}

inline b2Color operator/(const b2Color& c, float32 s)
{
	return b2Color(c.r / s, c.g / s, c.b / s, c.a);
}

inline b2Color operator*=(const b2Color& c, float32 s)
{
	return b2Color(c.r * s, c.g * s, c.b * s, c.a);
}

inline b2Color operator/=(const b2Color& c, float32 s)
{
	return b2Color(c.r / s, c.g / s, c.b / s, c.a);
}


void export_misc()
{
	using namespace boost::python;

	class_<b2Color>("b2Color")
		.def(init<float32, float32, float32, optional<float32> >())
		.def("Set", &b2Color::Set)
		.def_readwrite("r", &b2Color::r)
		.def_readwrite("g", &b2Color::g)
		.def_readwrite("b", &b2Color::b)
		.def_readwrite("a", &b2Color::a)
		.def("__iter__", b2Color__iter)
		.def("__getitem__", b2Color__getitem)
		.def("__setitem__", b2Color__setitem)
		.def(self * float32())
		.def(self / float32())
		.def(self *= float32())
		.def(self /= float32())
	;

	class_<b2Version>("b2Version")
		.def_readwrite("major", &b2Version::major)
		.def_readwrite("minor", &b2Version::minor)
		.def_readwrite("revision", &b2Version::revision)
	;

	scope().attr("b2_maxFloat") = b2_maxFloat;
	scope().attr("b2_epsilon") = b2_epsilon;
	scope().attr("b2_pi") = b2_pi;

	scope().attr("b2_maxManifoldPoints") = b2_maxManifoldPoints;
	scope().attr("b2_maxPolygonVertices") = b2_maxPolygonVertices;
	scope().attr("b2_aabbExtension") = b2_aabbExtension;
	scope().attr("b2_aabbMultiplier") = b2_aabbMultiplier;
	scope().attr("b2_linearSlop") = b2_linearSlop;
	scope().attr("b2_angularSlop") = b2_angularSlop;
	scope().attr("b2_polygonRadius") = b2_polygonRadius;
	scope().attr("b2_maxSubSteps") = b2_maxSubSteps;

	scope().attr("b2_maxTOIContacts") = b2_maxTOIContacts;
	scope().attr("b2_velocityThreshold") = b2_velocityThreshold;
	scope().attr("b2_maxLinearCorrection") = b2_maxLinearCorrection;
	scope().attr("b2_maxAngularCorrection") = b2_maxAngularCorrection;

	scope().attr("b2_maxTranslation") = b2_maxTranslation;
	scope().attr("b2_maxTranslationSquared") = b2_maxTranslationSquared;

	scope().attr("b2_maxRotation") = b2_maxRotation;
	scope().attr("b2_maxRotationSquared") = b2_maxRotationSquared;

	scope().attr("b2_baumgarte") = b2_baumgarte;
	scope().attr("b2_toiBaugarte") = b2_toiBaugarte;

	scope().attr("b2_timeToSleep") = b2_timeToSleep;
	scope().attr("b2_linearSleepTolerance") = b2_linearSleepTolerance;
	scope().attr("b2_angularSleepTolerance") = b2_angularSleepTolerance;

	scope().attr("b2_version") = b2_version;

	scope().attr("FLT_MAXFLOAT") = b2_maxFloat;
	scope().attr("FLT_EPSILON") = b2_epsilon;
	scope().attr("PI") = b2_pi;

}
