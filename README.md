## How to install: 
#### Make sure to change the pybind11 include path to your path in setup.py
#### You can run pybind11.get_include() to get it... you need to install pybind11 with pip
1. mkdir memory_pool_lib/build
2. cmake ..
3. make
4. cd ..
5. python setup.py build_ext --inplace
6. pip install .

#### Look in the example.py to see usage

#### WIP: dynamic size allocation for the pool...