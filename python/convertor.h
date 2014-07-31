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
#include <utility>

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

template<class T1, class T2>
struct pair_to_tuple_converter {
	static PyObject* convert(const std::pair<T1, T2>& pair) {
		using boost::python::incref;
		using boost::python::make_tuple;

		return incref(make_tuple(pair.first, pair.second).ptr());
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
		using boost::python::handle;
		using boost::python::extract;

		void* storage = ((converter::rvalue_from_python_storage<std::list<T> >*)(data))->storage.bytes;
		new (storage) std::list<T>();
		std::vector<T>* v = (std::list<T>*)(storage);
		Py_ssize_t vlen = PySequence_Size(obj_ptr);
		if(vlen < 0)
			abort();
		v->reserve(vlen);
		for(int i = 0; i < vlen; i++) {
			handle<> item(PySequence_GetItem(obj_ptr, i));
			v->push_back(extract<T>(item.get()));
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
		using boost::python::handle;
		using boost::python::extract;

		void* storage = ((converter::rvalue_from_python_storage<std::vector<T> >*)(data))->storage.bytes;
		new (storage) std::vector<T>();
		std::vector<T>* v = (std::vector<T>*)(storage);
		Py_ssize_t vlen = PySequence_Size(obj_ptr);
		if(vlen < 0)
			abort();
		v->reserve(vlen);
		for(int i = 0; i < vlen; i++) {
			handle<> item(PySequence_GetItem(obj_ptr, i));
			v->push_back(extract<T>(item.get()));
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
		using boost::python::handle;
		using boost::python::extract;
		b2Assert(PySequence_Size(obj_ptr) == 2);

		void* storage = ((converter::rvalue_from_python_storage<b2Vec2>*) (data))->storage.bytes;
		new (storage) b2Vec2;
		b2Vec2* v2 = (b2Vec2*) storage;

		handle<> x(PySequence_GetItem(obj_ptr, 0));
		handle<> y(PySequence_GetItem(obj_ptr, 1));
		v2->x = extract<float32>(x.get());
		v2->y = extract<float32>(y.get());
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
		using boost::python::handle;
		using boost::python::extract;
		b2Assert(PySequence_Size(obj_ptr) == 3);

		void* storage = ((converter::rvalue_from_python_storage<b2Vec3>*) (data))->storage.bytes;
		new (storage) b2Vec3;
		b2Vec3* v3 = (b2Vec3*) storage;

		handle<> x(PySequence_GetItem(obj_ptr, 0));
		handle<> y(PySequence_GetItem(obj_ptr, 1));
		handle<> z(PySequence_GetItem(obj_ptr, 2));
		v3->x = extract<float32>(x.get());
		v3->y = extract<float32>(y.get());
		v3->z = extract<float32>(z.get());
		data->convertible = storage;
	}
};

struct b2color_from_seq_convertor {
	b2color_from_seq_convertor() {
		using boost::python::type_id;
		converter::registry::push_back(&convertible, &construct, type_id<b2Color>());
	}

	static void* convertible(PyObject* obj_ptr) {
		if (!PySequence_Check(obj_ptr) || !PyObject_HasAttrString(obj_ptr, "__len__"))
			return 0;
		if (PySequence_Size(obj_ptr) != 3 && PySequence_Size(obj_ptr) != 4)
			return 0;
		return obj_ptr;
	}

	static void construct(PyObject* obj_ptr,
		converter::rvalue_from_python_stage1_data* data) {
			using boost::python::handle;
			using boost::python::extract;
			b2Assert(PySequence_Size(obj_ptr) == 3 || PySequence_Size(obj_ptr) == 4);

			void* storage = ((converter::rvalue_from_python_storage<b2Color>*) (data))->storage.bytes;
			new (storage) b2Color;
			b2Color* c3 = (b2Color*) storage;

			handle<> r(PySequence_GetItem(obj_ptr, 0));
			handle<> g(PySequence_GetItem(obj_ptr, 1));
			handle<> b(PySequence_GetItem(obj_ptr, 2));
			c3->r = extract<float32>(r.get());
			c3->g = extract<float32>(g.get());
			c3->b = extract<float32>(b.get());
			if (PySequence_Size(obj_ptr) == 4) {
				handle<> a(PySequence_GetItem(obj_ptr, 3));
				c3->a = extract<float32>(a.get());
			} else {
				c3->a = 1.0f;
			}
			data->convertible = storage;
	}
};

template<class T, class Conversion>
struct register_to_python_converter {
	register_to_python_converter() {
		using boost::python::type_id;
		using boost::python::to_python_converter;

		const converter::registration* entry;
		entry = converter::registry::query(type_id<T>());
		if (entry->m_to_python == 0)
		{
			to_python_converter<T, Conversion>();
		}
	}
};

#endif /* CONVERTOR_H_ */
