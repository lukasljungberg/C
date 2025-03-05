#include <pybind11/pybind11.h>
#include <pybind11/stl.h>  // Needed for std::unordered_map
#include <iostream>
#include <unordered_map>
#include <string>
#include "ObjectScanner.h"  // Include ObjectScanner class

namespace py = pybind11;

// Explicit template instantiations for Pybind11 compatibility
template void DynamicObject::addField<int>(const std::string&, void*);
template void DynamicObject::addField<float>(const std::string&, void*);
template int DynamicObject::getField<int>(const std::string&);
template float DynamicObject::getField<float>(const std::string&);

PYBIND11_MODULE(object_scanner, m) {
    py::class_<DynamicObject>(m, "DynamicObject")
        .def(py::init<>())  // Default constructor
        .def("add_field_int", &DynamicObject::addField<int>)
        .def("add_field_float", &DynamicObject::addField<float>)
        .def("get_field_int", &DynamicObject::getField<int>)
        .def("get_field_float", &DynamicObject::getField<float>)
        .def("print_fields", &DynamicObject::printFields);  // Ensure printFields is exposed

    py::class_<ObjectScanner>(m, "ObjectScanner")
        .def(py::init<pid_t>())  // Bind constructor
        .def("attach", &ObjectScanner::Attach)  // Bind Attach function
        .def("reconstruct_objects", &ObjectScanner::ReconstructObjects, py::return_value_policy::reference);  // Bind ReconstructObjects function properly
}
