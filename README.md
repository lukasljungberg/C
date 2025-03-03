# memory_pool
A KISS (Keep It Simple Stupid) module for python.
Ment to create a shared memory pool from an id where you can share
data and class object during runtime of X amount of python processes running.
Implemented with mutex lock.

## How to install: 

### Create the venv:
1. cd C && python -m venv venv && source venv/bin/activate
2. pip install pybind11

#### Make sure to change the pybind11 include path to your path in setup.py
#### You can run pybind11.get_include() to get it...
1. mkdir memory_pool_lib/build
2. cmake ..
3. make
4. cd ..
5. python setup.py build_ext --inplace
6. pip install .

#### Look in the example.py to see usage

#### WIP: dynamic size allocation for the pool...