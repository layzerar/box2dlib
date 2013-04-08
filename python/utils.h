/*
 * @summary: box2d utils
 * @date: 2012-11-24
 * @author: zl
 */


#ifndef UTILS_H_
#define UTILS_H_

#include "config.h"
#include <vector>

using boost::python::object;
typedef std::vector<b2Fixture*> b2FixtureList;
typedef std::vector<b2Contact*> b2ContactList;
typedef std::vector<b2Joint*> b2JointList;
typedef std::vector<b2Body*> b2BodyList;


inline object CreateList(uint32 count)
{
	using boost::python::list;
	using boost::python::make_tuple;

	static list singleZeroList(make_tuple(0));
	return singleZeroList * count;
}

inline void IndexError()
{
	using boost::python::throw_error_already_set;
	PyErr_SetString(PyExc_IndexError, "Index out of range");
	throw_error_already_set();
}

template<class T>
inline object ArrayToList(const T* a,
		uint32 count, uint32 maxCount=b2_maxArrayCount)
{
	using namespace boost::python;

	if (count > maxCount)
		return object();

	object vl = CreateList(count);
	for(uint32 index = 0; index < count; ++index)
	{
		vl[index] = a[index];
	}
	return vl;
}


template<class T>
inline uint32 ListToArray(T* a, object s, uint32 maxCount=b2_maxArrayCount)
{
	using namespace boost::python;

	uint32 count = (uint32)len(s);
	if (count > maxCount)
		return 0;

	for(uint32 index=0; index < count; ++index)
	{
		a[index] = extract<T>(s[index]);
	}
	return count;
}


template<class T>
inline object ArrayToRefList(const T* a,
	uint32 count, uint32 maxCount=b2_maxArrayCount)
{
	using namespace boost::python;

	if (count > maxCount)
		return object();

	object vl = CreateList(count);
	for(uint32 index = 0; index < count; ++index)
	{
		vl[index] = boost::ref(a[index]);
	}
	return vl;
}


#endif /* UTILS_H_ */
