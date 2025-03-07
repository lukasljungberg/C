#ifndef OBJECT_SCANNER_H
#define OBJECT_SCANNER_H
#include <iostream>
#include <vector>
#include <sys/ptrace.h>
#include <cassert>
#include <sys/wait.h>
#include <fstream>
#include <sstream>
#include <functional>
#include <sys/types.h>
#include <unistd.h>
#include <cstdint>
#include <Python.h>
#include <sys/ptrace.h>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>

class DynamicObject {
    public:
        std::unordered_map<std::string, void*> fields;
        std::unordered_map<std::string, std::string> types; // Store type info
    
        template<typename T>
        void addField(const std::string& name, void* address) {
            fields[name] = address;
            types[name] = typeid(T).name(); // Store type info
        }
    
        template<typename T>
        T getField(const std::string& name) {
            return *(T*)fields[name];
        }
    
        void printFields() {
            for (const auto& [name, ptr] : fields) {
                if (types[name] == typeid(int).name()) {
                    std::cout << name << " (int): " << *(int*)ptr << std::endl;
                } else if (types[name] == typeid(float).name()) {
                    std::cout << name << " (float): " << *(float*)ptr << std::endl;
                } else {
                    std::cout << name << ": Unknown Type\n";
                }
            }
        }
    };
    
// The scanner class, dont worry it's gonna be fire!
class ObjectScanner
{
    private:
        // PID
        pid_t proc_id;
        std::vector<long> bytesArr;
        // Memory regions
        std::vector<void*> addressArray;
        bool GetMemoryRegions();
    public:
        ObjectScanner(pid_t pid);
        bool Attach();
        void ReconstructObjects();
        ~ObjectScanner();
};




#endif // OBJECT_SCANNER_H