# 🧵 C++ String Scanner 🔍 Module for Python 🐍  

A **python module** for scanning strings in processes on **Linux** 🐧.  
Supports **regex** 🔢 and **object address offset** for different process types.  

> 🛠 **Default offset:** `40` (Python **3.13.x**)  

---

## 📦 Installation  

### 🔧 **Build the `.so` file** & Install with `pip`  

```bash
c++ -O3 -Wall -shared -std=c++17 -fPIC $(python3 -m pybind11 --includes) \
   -o string_scanner.so src/binding.cpp src/StringScanner.cpp -lpthread

pip install .
```

---

🔥 **Features:**  
✅ Fast **C++ implementation** 🚀  
✅ **Regex support** for flexible scanning 🔍  
✅ Optimized for **Python 3.13.x** 🐍  

---
