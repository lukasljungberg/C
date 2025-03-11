from setuptools import setup, Extension

setup(
    name="string_scanner",
    ext_modules=[
        Extension(
            "string_scanner",  # The name of the module
            ["src/binding.cpp"],  # The C++ source file
            include_dirs=["../venv/lib64/python3.13/site-packages/pybind11/include"],  # Include pybind11
            language="c++"
        ),
    ],
)
