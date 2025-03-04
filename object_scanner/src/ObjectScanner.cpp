#include "ObjectScanner.h"

ObjectScanner::ObjectScanner(pid_t pid)
{
    proc_id = pid;
}

bool ObjectScanner::Attach()
{   
    try {
        long attached = ptrace(PTRACE_ATTACH, proc_id, NULL, NULL);
        assert(attached == 0 && "Failed to attach the process");
        
        pid_t waited = waitpid(proc_id, NULL, 0);
        assert(waited == 0 && "Failed waiting for process");

        bool mem_regions = GetMemoryRegions();
        assert(mem_regions && "Failed to get memory regions of the child process");

    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
    return true;
}

bool ObjectScanner::GetMemoryRegions()
{   
    std::string path = "/proc/" + std::to_string(proc_id) + "/maps";
    std::ifstream file(path);
    std::string line;
    
    try {
        bool is_opened = file.is_open();
        assert(is_opened && "Failed to open process memory map file for the PID");

        // Read the lines
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string startAddr, endAddr;

            // Extract the start and end addresses from the line
            if (iss >> startAddr >> endAddr) {
                memoryRegions.push_back({startAddr, endAddr});
        }
        file.close();
    }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        file.close();
        return false;
    }

    return true;
}

ObjectScanner::~ObjectScanner()
{
}