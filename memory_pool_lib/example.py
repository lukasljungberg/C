import memory_pool as mp

# MemoryPool can be inherited or also used to create an python object = MemoryPool()
class MPool(mp.MemoryPool):
    def __init__(self, *args, **kwargs):
        super(MPool, self).__init__(*args, **kwargs)
        
# The main pool instance
pool = MPool("m_mem", False)

# pool_attached can be a instance of another script/process
pool_attached = MPool("m_mem", True)

# Adding bytes to a key:value pair (could be used with pickle for objects of type class)
pool.add("test", b"testBYTES")

# Get the value of a key
print(pool_attached.get("test"))

# List the keys
print(pool.list_keys())

# run deconstructor to make sure the pool is freed from memory
del pool_attached
del pool