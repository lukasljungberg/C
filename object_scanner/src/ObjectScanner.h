#ifndef OBJECT_SCANNER_H
#define OBJECT_SCANNER_H
#include <iostream>
#include <vector>
#include <sys/ptrace.h>
#include <cassert>
#include <sys/wait.h>
#include <fstream>
#include <sstream>
// The scanner class, dont worry it's gonna be fire!
class ObjectScanner
{
    private:
        // PID
        pid_t proc_id;

        // Memory regions
        std::vector<std::pair<std::string, std::string>> memoryRegions;
    public:
        ObjectScanner(pid_t pid);
        bool Attach();
        bool GetMemoryRegions();
        ~ObjectScanner();
};




#endif // OBJECT_SCANNER_H