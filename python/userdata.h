/*
 * @summary: box2d userdata
 * @date: 2012-11-21
 * @author: zl
 */

#ifndef USERDATA_H_
#define USERDATA_H_


#include "config.h"
#include <vector>


using boost::python::object;


template<class T>
inline void b2Attr_ClearUserData(T& self)
{
	using namespace boost::python;

	xdecref((PyObject*)self.userData);
	self.userData = NULL;
}

template<class T>
inline void b2Attr_SetUserData(T& self, object userData)
{
	using namespace boost::python;

	b2Attr_ClearUserData(self);
	self.userData = xincref(userData.ptr());
}

template<class T>
inline object b2Attr_GetUserData(T& self)
{
	using namespace boost::python;

	return object(handle<>(borrowed((PyObject*)self.userData)));
}

template<class T>
inline void b2Func_ClearUserData(T& self)
{
	using namespace boost::python;

	xdecref((PyObject*)self.GetUserData());
	self.SetUserData(NULL);
}

template<class T>
inline void b2Func_SetUserData(T& self, object userData)
{
	using namespace boost::python;

	b2Func_ClearUserData(self);
	self.SetUserData(xincref(userData.ptr()));
}

template<class T>
inline object b2Func_GetUserData(T& self)
{
	using namespace boost::python;

	return object(handle<>(borrowed((PyObject*)self.GetUserData())));
}

template<typename T>
class b2Cls_ClearUserData
{
public:
	b2Cls_ClearUserData()
		: _userdata(NULL)
	{
	}

	b2Cls_ClearUserData(T* self)
	{
		_userdata = self->GetUserData();
	}

	~b2Cls_ClearUserData()
	{
		using namespace boost::python;

		xdecref((PyObject*)_userdata);
		_userdata = NULL;
	}

protected:
	void* _userdata;
};

class b2Cls_ClearUserDataList
{
public:
	typedef std::vector<void*> UserDataList;

	b2Cls_ClearUserDataList()
		: _userdatas()
	{
	}

	b2Cls_ClearUserDataList(b2Body* body)
	{
		void* userdata;
		b2Fixture* fixture;
		b2JointEdge* jedge;

		fixture = body->GetFixtureList();
		while (fixture != NULL)
		{
			userdata = fixture->GetUserData();
			if (userdata != NULL)
				_userdatas.push_back(userdata);
			fixture = fixture->GetNext();
		}

		jedge = body->GetJointList();
		while (jedge != NULL)
		{
			userdata = jedge->joint->GetUserData();
			if (userdata != NULL)
				_userdatas.push_back(userdata);
			jedge = jedge->next;
		}

		userdata = body->GetUserData();
		if (userdata != NULL)
			_userdatas.push_back(userdata);
	}

	~b2Cls_ClearUserDataList()
	{
		using namespace boost::python;
		UserDataList::iterator iter;

		for (iter = _userdatas.begin(); iter != _userdatas.end(); ++iter)
		{
			xdecref((PyObject*)*iter);
		}
		_userdatas.clear();
	}

protected:
	UserDataList _userdatas;
};


#endif /* USERDATA_H_ */
