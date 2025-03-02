import sys
import memory_pool
import time
import pickle
from shared_classes import PythonObject
# Initialize memory pool
mp = memory_pool.MemoryPool("/themem", False)

obj = PythonObject()
obj.var1 = False
obj.var2 = True
obj.var3 = "test3"
obj = obj.dumps()
mp.add("test", obj)
print(mp.get("test"))
while True:
    try:
        time.sleep(15)
        bt_str = mp.get("test")
        obj: PythonObject = pickle.loads(bt_str)
        print(obj.var1)
        print(obj.var2)
        print(obj.var3)
    except Exception as e:
        print(f"Error occurred: {e}")
        break

mp.delete()
del mp
