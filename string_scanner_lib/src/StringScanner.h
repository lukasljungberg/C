#ifndef STRING_SCANNER_H
#define STRING_SCANNER_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstring>
#include <cstdint>
#include <Python.h>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/uio.h>
#include <sstream>
#include <regex>

struct MemoryRegion {
    uintptr_t start;
    uintptr_t end;
    bool readable;
    MemoryRegion(uintptr_t s, uintptr_t e, bool r) : start(s), end(e), readable(r) {}
};
class StringScanner {
    public:
        explicit StringScanner(pid_t pid) : proc_id(pid) {};
        void find_match(std::string& regex, int offset);
    
    private:
        pid_t proc_id;
        std::vector<MemoryRegion> memory_regions;
    };


#endif // STRING_SCANNER_H