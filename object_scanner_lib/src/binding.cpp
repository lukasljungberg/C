#include <pybind11/pybind11.h>
#include <pybind11/stl.h>  // For exposing STL containers like std::unordered_map
#include <iostream>
#include <unordered_map>
#include <string>
#include "ObjectScanner.h"  // Include your header file for the ObjectScanner class

namespace py = pybind11;

// Define the functions for ObjectScanner and DynamicObject using pybind11
PYBIND11_MODULE(object_scanner, m) {
    py::class_<DynamicObject>(m, "DynamicObject")
        .def(py::init<>())  // Default constructor
        .def("add_field", &DynamicObject::addField<int>)  // Expose addField for int
        .def("add_field", &DynamicObject::addField<float>)  // Expose addField for float
        .def("get_field", &DynamicObject::getField<int>)  // Expose getField for int
        .def("get_field", &DynamicObject::getField<float>)  // Expose getField for float
        .def("print_fields", &DynamicObject::printFields);  // Expose printFields

    py::class_<ObjectScanner>(m, "ObjectScanner")
        .def(py::init<pid_t>())  // Bind the constructor
        .def("attach", &ObjectScanner::Attach)  // Bind Attach function
        .def("reconstruct_objects", &ObjectScanner::ReconstructObjects);  // Bind ReconstructObjects function
}
