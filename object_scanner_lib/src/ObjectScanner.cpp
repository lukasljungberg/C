#include "ObjectScanner.h"

ObjectScanner::ObjectScanner(pid_t pid)
{
    proc_id = pid;
}

ObjectScanner::~ObjectScanner()
{
}

bool ObjectScanner::Attach()
{   
    try {
        long attached = ptrace(PTRACE_ATTACH, proc_id, NULL, NULL);
        assert(attached == 0 && "Failed to attach the process");
        
        pid_t waited = waitpid(proc_id, NULL, 0);
        assert(waited == proc_id && "Failed waiting for process");

        // Sets the memoryRegions
        bool mem_regions = GetMemoryRegions();
        assert(mem_regions && "Failed to get memory regions of the child process");

    } catch (const std::exception &e) {
        std::cerr << "Exception in Attach: " << e.what() << std::endl;
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

        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string addressRange, permissions, offset, dev, inode, pathname;
            if (iss >> addressRange >> permissions >> offset >> dev >> inode) {
                // Optional: Read the pathname (if present)
                std::getline(iss, pathname);
                
                // Extract start and end addresses
                size_t dashPos = addressRange.find('-');
                if (dashPos != std::string::npos) {
                    std::string startAddr = addressRange.substr(0, dashPos);
                    std::string endAddr = addressRange.substr(dashPos + 1);
                    memoryRegions.push_back({startAddr, endAddr});
                }
            }
        }
        file.close();
    } catch (const std::exception &e) {
        std::cerr << "Exception in GetMemoryRegions: " << e.what() << std::endl;
        file.close();
        return false;
    }

    return true;
}

const DynamicObject* ObjectScanner::ReconstructObjects() {
    static DynamicObject fakeObject;
    return &fakeObject;  // Return a dummy object for now
}

