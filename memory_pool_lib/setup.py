from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
class custom_build_ext(build_ext):
    def run(self):
        # You can add custom build steps here if needed
        super().run()

# Define the C++ extension module using pybind11
module = Extension(
    'memory_pool',  # The name of the Python module
    sources=['src/MemoryPool.cpp', 'src/binding.cpp'],  # Your C++ source file(s)
    # Update this path below to your pybind11 include-->
    include_dirs=["../venv/lib64/python3.13/site-packages/pybind11/include"],  # Include the pybind11 headers
    extra_compile_args=['-std=c++11'],  # Add any required compile flags
    language='c++',  # Ensure the extension is compiled as C++
)

setup(
    name='memory_pool',
    version='1.0',
    cmdclass={'build_ext': custom_build_ext},
    description='Python bindings for MemoryPool',
    ext_modules=[module],
    zip_safe=False,
)
