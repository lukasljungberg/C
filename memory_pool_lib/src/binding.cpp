// Mostly generated with chatGPT
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>  // For automatic conversions of STL containers
#include <iostream>
#include "MemoryPool.h"
namespace py = pybind11;
class PyParent {
    public:
        PyParent() { 
            std::cout << "Parent class initialized\n"; 
        }
        
        virtual ~PyParent() {
            std::cout << "Parent class destroyed\n";
        }
};

class PyMemoryPool : public PyParent {
public:
    PyMemoryPool(const std::string& name, bool attach) 
        : pool(new MemoryPool(name, attach)) {}

    ~PyMemoryPool() {
        delete_pool();
        delete pool;
    }

    void add(const std::string& key, py::object& value) {
        pool->add_value(key, value.ptr());
    }

    std::vector<std::string> list_keys() {
        PyObject* keys_obj = pool->list_keys();  // Get PyObject* (likely a Python list)
        
        if (!keys_obj || !PyList_Check(keys_obj)) {  // Ensure it's a valid Python list
            return {};  // Return empty vector if invalid
        }
    
        std::vector<std::string> keys;
        Py_ssize_t size = PyList_Size(keys_obj);
        
        for (Py_ssize_t i = 0; i < size; ++i) {
            PyObject* item = PyList_GetItem(keys_obj, i);  // Borrowed reference
    
            if (PyUnicode_Check(item)) {
                keys.push_back(PyUnicode_AsUTF8(item));  // Convert Python str -> std::string
            }
        }
    
        return keys;  // Return the converted vector
    }

    py::object get(const std::string& key) {
        PyObject* value = pool->get_value(key);
        if (!value)
            return py::none();
        return py::reinterpret_borrow<py::object>(value);
    }

private:
    MemoryPool* pool;
    void delete_pool() {
        pool->delete_pool();
    }
};

PYBIND11_MODULE(memory_pool, m) {  // Match the module name to the shared library name
    pybind11::class_<PyParent>(m, "Parent")
        .def(pybind11::init<>());

    pybind11::class_<PyMemoryPool, PyParent>(m, "MemoryPool")
        .def(py::init<const std::string&, bool>(), "Constructor for MemoryPool", py::arg("name"), py::arg("attach"))
        .def("add", &PyMemoryPool::add, "Add a key-value pair to the memory pool")
        .def("list_keys", &PyMemoryPool::list_keys, "Get all keys")
        .def("get", &PyMemoryPool::get, "Get a value by key");
}
