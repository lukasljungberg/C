import memory_pool
import time
import pickle
from shared_classes import PythonObject
# Initialize memory pool
mp = memory_pool.MemoryPool("/shared_mem", True)

obj: PythonObject = pickle.loads(mp.get('test'))

print(obj)
print(obj.var1)
print(obj.var2)
print(obj.var3)
obj.var1 = "NEW_VALUE1"
obj.var2 = "NEW_VALUE2"
obj.var3 = b"NEW_VALUE3"
mp.add('test', obj.dumps())
print(mp.list_keys())
time.sleep(15)
mp.delete()
