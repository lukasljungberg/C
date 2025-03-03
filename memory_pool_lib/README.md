# 💾 memory_pool

A **KISS (Keep It Simple Stupid)** module for Python.

📌 Designed to create a **shared memory pool** from an ID, allowing you to share data and class objects across multiple Python processes during runtime.

🔒 Implemented with **mutex lock** for safe access.

---

## 📥 Installation Guide

### 🛠️ Create the Virtual Environment:

```bash
cd C && python -m venv venv && source venv/bin/activate
pip install pybind11
```

### 🔧 Update `setup.py` (Important!)
Make sure to change the **pybind11 include path** in `setup.py` to match your system.
You can find the correct path using:

```python
import pybind11
print(pybind11.get_include())
```

### 🏗️ Build & Install:

```bash
mkdir memory_pool_lib/build
cd memory_pool_lib/build
cmake ..
make
cd ..
python setup.py build_ext --inplace
pip install .
```

---

## 📌 Usage
Check out [`example.py`](./example.py) to see how to use `memory_pool` in action! 🧠⚡

---

## 🔄 Work in Progress (WIP)
- ✨ **Dynamic size allocation** for the memory pool (Coming Soon!) ⏳

