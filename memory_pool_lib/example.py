import memory_pool as mp

class MPool(mp.MemoryPool):
    def __init__(self, *args, **kwargs):
        super(MPool, self).__init__(*args, **kwargs)
        

pool = MPool("m_mem", False)
pool_attached = MPool("m_mem", True)
pool.add("test", b"testBYTES")
print(pool_attached.get("test"))

del pool_attached
del pool