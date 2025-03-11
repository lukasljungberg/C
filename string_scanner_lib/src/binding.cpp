#include <pybind11/pybind11.h>
#include <pybind11/stl.h>  // Needed for std::unordered_map
#include <iostream>
#include <unordered_map>
#include <string>
#include "StringScanner.h"  // Include ObjectScanner class

namespace py = pybind11;

PYBIND11_MODULE(string_scanner, m) {
    py::class_<StringScanner>(m, "StringScanner")
        .def(py::init<pid_t>())  // Bind constructor
        .def("find_match", &StringScanner::find_match);  // Bind Attach function
}
