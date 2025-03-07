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
        ptrace(PTRACE_DETACH, proc_id, NULL, NULL);

    } catch (const std::exception &e) {
        std::cerr << "Exception in Attach: " << e.what() << std::endl;
        ptrace(PTRACE_DETACH, proc_id, NULL, NULL);
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
                // Optional
                std::getline(iss, pathname);
                if (permissions[0] != 'r') continue;
                if (iss >> pathname) continue;
                std::cout << line << std::endl;
                size_t dash_pos = addressRange.find('-');
                std::string start_str = addressRange.substr(0, dash_pos);
                std::string end_str = addressRange.substr(dash_pos + 1);

                void* start_addr = reinterpret_cast<void*>(std::stoull(start_str, nullptr, 16));
                void* end_addr = reinterpret_cast<void*>(std::stoull(end_str, nullptr, 16));

                for (char* addr = static_cast<char*>(start_addr); addr < static_cast<char*>(end_addr); addr += 1) {
                    long data = ptrace(PTRACE_PEEKDATA, proc_id, static_cast<void*>(addr), NULL);
                    //std::cout << static_cast<void*>(addr) << std::endl;
                    if (data == 1234567)
                        std::cout << data << std::endl;
                    int value = static_cast<int>(data);
                    if (value == 1234567)
                        std::cout << value << std::endl;
                    addressArray.push_back(addr);
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

void ObjectScanner::ReconstructObjects() {

}

