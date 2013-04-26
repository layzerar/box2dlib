/*
 * @summary: box2d convertor
 * @date: 2012-03-29
 * @author: zl
 */

#ifndef CONVERTOR_H_
#define CONVERTOR_H_

#include "config.h"
#include <list>
#include <vector>

namespace converter = boost::python::converter;


template<class T>
struct list_to_list_converter {
	static PyObject* convert(const std::list<T>& v) {
		using boost::python::list;
		using boost::python::incref;

		list pylist;
		FOREACH(const T& e, v)
			pylist.append(e);
		return incref(pylist.ptr());
	}
};

template<class T>
struct vector_to_list_converter {
	static PyObject* convert(const std::vector<T>& v) {
		using boost::python::list;
		using boost::python::incref;

		list pylist;
		FOREACH(const T& e, v)
			pylist.append(e);
		return incref(pylist.ptr());
	}
};

template<class T>
struct list_to_list_ref_converter {
	static PyObject* convert(const std::list<T>& v) {
		using boost::python::list;
		using boost::python::incref;

		list pylist;
		FOREACH(const T& e, v)
			pylist.append(boost::ref(e));
		return incref(pylist.ptr());
	}
};

template<class T>
struct vector_to_list_ref_converter {
	static PyObject* convert(const std::vector<T>& v) {
		using boost::python::list;
		using boost::python::incref;

		list pylist;
		FOREACH(const T& e, v)
			pylist.append(boost::ref(e));
		return incref(pylist.ptr());
	}
};

template<typename T>
struct list_from_seq_converter {
	list_from_seq_converter() {
		using boost::python::type_id;
		converter::registry::push_back(&convertible, &construct, type_id<std::list<T> >());
	}

	static void* convertible(PyObject* obj_ptr){
		// the second condition is important, for some reason otherwise there were attempted conversions of Body to list which failed afterwards.
		if(!PySequence_Check(obj_ptr) || !PyObject_HasAttrString(obj_ptr, "__len__"))
			return NULL;
		return obj_ptr;
	}

	static void construct(PyObject* obj_ptr, converter::rvalue_from_python_stage1_data* data){
		using boost::python::extract;
		void* storage = ((converter::rvalue_from_python_storage<std::list<T> >*)(data))->storage.bytes;
		new (storage) std::list<T>();
		std::vector<T>* v = (std::list<T>*)(storage);
		Py_ssize_t vlen = PySequence_Size(obj_ptr);
		if(vlen < 0)
			abort();
		v->reserve(vlen);
		for(int i = 0; i < vlen; i++) {
			v->push_back(extract<T>(PySequence_GetItem(obj_ptr, i)));
		}
		data->convertible = storage;
	}
};

template<typename T>
struct vector_from_seq_converter {
	vector_from_seq_converter() {
		using boost::python::type_id;
		converter::registry::push_back(&convertible, &construct, type_id<std::vector<T> >());
	}

	static void* convertible(PyObject* obj_ptr){
		// the second condition is important, for some reason otherwise there were attempted conversions of Body to list which failed afterwards.
		if(!PySequence_Check(obj_ptr) || !PyObject_HasAttrString(obj_ptr, "__len__"))
			return NULL;
		return obj_ptr;
	}

	static void construct(PyObject* obj_ptr, converter::rvalue_from_python_stage1_data* data){
		using boost::python::extract;
		void* storage = ((converter::rvalue_from_python_storage<std::vector<T> >*)(data))->storage.bytes;
		new (storage) std::vector<T>();
		std::vector<T>* v = (std::vector<T>*)(storage);
		Py_ssize_t vlen = PySequence_Size(obj_ptr);
		if(vlen < 0)
			abort();
		v->reserve(vlen);
		for(int i = 0; i < vlen; i++) {
			v->push_back(extract<T>(PySequence_GetItem(obj_ptr, i)));
		}
		data->convertible = storage;
	}
};

struct b2vec2_from_seq_convertor {
	b2vec2_from_seq_convertor() {
		using boost::python::type_id;
		converter::registry::push_back(&convertible, &construct, type_id<b2Vec2>());
	}

	static void* convertible(PyObject* obj_ptr) {
		if (!PySequence_Check(obj_ptr) || !PyObject_HasAttrString(obj_ptr, "__len__"))
			return 0;
		if (PySequence_Size(obj_ptr) != 2)
			return 0;
		return obj_ptr;
	}

	static void construct(PyObject* obj_ptr,
			converter::rvalue_from_python_stage1_data* data) {
		using boost::python::extract;
		b2Assert(PySequence_Size(obj_ptr) == 2);

		void* storage = ((converter::rvalue_from_python_storage<b2Vec2>*) (data))->storage.bytes;
		new (storage) b2Vec2;
		b2Vec2* v2 = (b2Vec2*) storage;

		v2->x = extract<float32>(PySequence_GetItem(obj_ptr, 0));
		v2->y = extract<float32>(PySequence_GetItem(obj_ptr, 1));
		data->convertible = storage;
	}
};

struct b2vec3_from_seq_convertor {
	b2vec3_from_seq_convertor() {
		using boost::python::type_id;
		converter::registry::push_back(&convertible, &construct, type_id<b2Vec3>());
	}

	static void* convertible(PyObject* obj_ptr) {
		if (!PySequence_Check(obj_ptr) || !PyObject_HasAttrString(obj_ptr, "__len__"))
			return 0;
		if (PySequence_Size(obj_ptr) != 3)
			return 0;
		return obj_ptr;
	}

	static void construct(PyObject* obj_ptr,
			converter::rvalue_from_python_stage1_data* data) {
		using boost::python::extract;
		b2Assert(PySequence_Size(obj_ptr) == 3);

		void* storage = ((converter::rvalue_from_python_storage<b2Vec3>*) (data))->storage.bytes;
		new (storage) b2Vec3;
		b2Vec3* v3 = (b2Vec3*) storage;

		v3->x = extract<float32>(PySequence_GetItem(obj_ptr, 0));
		v3->y = extract<float32>(PySequence_GetItem(obj_ptr, 1));
		v3->z = extract<float32>(PySequence_GetItem(obj_ptr, 2));
		data->convertible = storage;
	}
};

struct b2Color_from_seq_convertor {
	b2Color_from_seq_convertor() {
		using boost::python::type_id;
		converter::registry::push_back(&convertible, &construct, type_id<b2Color>());
	}

	static void* convertible(PyObject* obj_ptr) {
		if (!PySequence_Check(obj_ptr) || !PyObject_HasAttrString(obj_ptr, "__len__"))
			return 0;
		if (PySequence_Size(obj_ptr) != 3)
			return 0;
		return obj_ptr;
	}

	static void construct(PyObject* obj_ptr,
		converter::rvalue_from_python_stage1_data* data) {
			using boost::python::extract;
			b2Assert(PySequence_Size(obj_ptr) == 3);

			void* storage = ((converter::rvalue_from_python_storage<b2Color>*) (data))->storage.bytes;
			new (storage) b2Color;
			b2Color* c3 = (b2Color*) storage;

			c3->r = extract<float32>(PySequence_GetItem(obj_ptr, 0));
			c3->g = extract<float32>(PySequence_GetItem(obj_ptr, 1));
			c3->b = extract<float32>(PySequence_GetItem(obj_ptr, 2));
			data->convertible = storage;
	}
};


#endif /* CONVERTOR_H_ */
