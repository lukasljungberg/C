#include <cstring>
#include <iostream>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <unordered_map>
#include <Python.h>
#include <cstdlib>
#include "MemoryPool.h"

MemoryPool::MemoryPool(const std::string& shm_name, bool attach) : shm_name(shm_name) {
    shm_size = sizeof(SharedMemoryHeader);
    int flags = O_CREAT | O_RDWR;
    if (attach) {
        flags = O_RDWR;
    }
    // open or create the memory depending on the flag
    shm_fd = shm_open(shm_name.c_str(), flags, 0666);

    try {
        assert(shm_fd != -1 && "Failed to open shared memory.");
        if (!attach) {
            // set the size of the memory
            int size_is_set = ftruncate(shm_fd, shm_size);
            assert(size_is_set != -1 && "Failed to set shared memory size.");
        }
        // map the memory to this process
        shared_memory = mmap(NULL, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
        assert(shared_memory != MAP_FAILED && "Failed to map shared memory.");

    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "try block failed" << std::endl;
        return;
    }



    header = static_cast<SharedMemoryHeader*>(shared_memory);
    
    if (!attach) {
        if (!header->initialized) {
            memset(header, 0, sizeof(SharedMemoryHeader));
            header->initialized = true;
            header->count = 0;
            pthread_mutexattr_t attr;
            pthread_mutexattr_init(&attr);
            pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
            pthread_mutex_init(&header->lock, &attr);
            pthread_mutexattr_destroy(&attr);
        }
    } else {
        assert(header->initialized && "Shared memory pool is uninitialized!");
    }
}

MemoryPool::~MemoryPool() {
    munmap(shared_memory, shm_size);
    close(shm_fd);
}

void MemoryPool::add_value(const std::string& key, PyObject* value) {
    // lock the mutex to this process
    pthread_mutex_lock(&header->lock);
    char* serialized_data = PyBytes_AsString(value);
    size_t serialized_size = PyBytes_Size(value);
    try {
        assert(header->count < MAX_ENTRIES && "Shared memory is full!");
        assert(PyBytes_Check(value) && "Error: Only bytes values are allowed!");
        assert(serialized_data && "Error: Failed to convert Python bytes to bytes!");
        assert(serialized_size <= VALUE_SIZE && "Error: Data is too large for shared memory!");

    } catch (const std::exception &e) {
        pthread_mutex_unlock(&header->lock);
        std::cerr << e.what() << std::endl;
        return;
    }

    for (size_t i = 0; i < header->count; ++i) {
        // If the strings are equal we've found the existing key
        if (strncmp(header->entries[i].key, key.c_str(), KEY_SIZE) == 0) {
            memcpy(header->entries[i].value, serialized_data, serialized_size); // Copy new data to existing entry
            header->entries[i].value_size = serialized_size;  // Store the size of the value
            pthread_mutex_unlock(&header->lock);
            return;
        }
    }
    // If it's a new key, copy the key name and value into a new entry
    strncpy(header->entries[header->count].key, key.c_str(), KEY_SIZE);
    header->entries[header->count].key[KEY_SIZE - 1] = '\0'; 
    memcpy(header->entries[header->count].value, serialized_data, serialized_size);
    header->entries[header->count].value_size = serialized_size;
    header->count++;

    // unlock the mutex from this process
    pthread_mutex_unlock(&header->lock);
}

PyObject* MemoryPool::list_keys() {
    PyObject* keys = PyList_New(header->count);
    if (!keys) {
        return nullptr;
    }
    for (size_t i = 0; i < header->count; ++i) { 
        size_t key_len = strnlen(header->entries[i].key, KEY_SIZE);
        PyObject* py_str = PyUnicode_FromStringAndSize(header->entries[i].key, key_len);
        if (!py_str) {
            Py_DECREF(keys);
            return nullptr;
        }
        PyList_SET_ITEM(keys, i, py_str);
    }
    return keys;
}

PyObject* MemoryPool::get_value(const std::string& key) {
    pthread_mutex_lock(&header->lock);

    for (size_t i = 0; i < header->count; ++i) {
        if (strncmp(header->entries[i].key, key.c_str(), KEY_SIZE) == 0) {
            char* value = header->entries[i].value;
            size_t value_size = header->entries[i].value_size;

            PyObject* py_value = PyBytes_FromStringAndSize(value, value_size);
            pthread_mutex_unlock(&header->lock);

            return py_value;
        }
    }

    pthread_mutex_unlock(&header->lock);
    Py_RETURN_NONE;
}


void MemoryPool::delete_pool() {
    pthread_mutex_destroy(&header->lock);
    shm_unlink(shm_name.c_str());
    std::cerr << shm_name + " is deleted!" << std::endl;
}
