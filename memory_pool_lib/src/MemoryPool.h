/// Updated MemoryPool.h
#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <pthread.h>

#define MAX_ENTRIES 100
#define KEY_SIZE 64
#define VALUE_SIZE 1024

struct SharedMemoryHeader {
    bool initialized;
    size_t count;
    pthread_mutex_t lock; // Mutex
    struct Entry {
        char key[KEY_SIZE];
        char value[VALUE_SIZE];
        size_t value_size;
    } entries[MAX_ENTRIES];
};

class MemoryPool {
public:
    MemoryPool(const std::string& shm_name, bool attach);
    ~MemoryPool();
    void add_value(const std::string& key, PyObject* value);
    PyObject* list_keys();
    PyObject* get_value(const std::string& key);
    void delete_pool();

private:
    std::string shm_name;
    int shm_fd;
    size_t shm_size;
    void* shared_memory;
    SharedMemoryHeader* header;
};

#endif // MEMORY_POOL_H
