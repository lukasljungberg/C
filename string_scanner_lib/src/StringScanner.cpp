#include "StringScanner.h"

void StringScanner::find_match(std::string& regex, int offset) {

    std::ifstream mapsFile("/proc/" + std::to_string(proc_id) + "/maps");  // Reads the current process's memory map
    if (!mapsFile) {
        std::cerr << "Error: Cannot open /proc/" + std::to_string(proc_id) + "/maps" << std::endl;
        return;
    }
    std::vector<MemoryRegion> regions;
    std::string line;
    while (std::getline(mapsFile, line)) {
        std::istringstream iss(line);
        std::string addressRange;
        std::string permission;
        if (iss >> addressRange >> permission) {
            size_t delimiter = addressRange.find('-');
            if (delimiter != std::string::npos) {
                uintptr_t start = std::stoul(addressRange.substr(0, delimiter), nullptr, 16);
                uintptr_t end = std::stoul(addressRange.substr(delimiter + 1), nullptr, 16);
                bool isReadable = !permission.empty() && permission[0] == 'r';
                regions.push_back({start, end, isReadable});
            }
        }
    }

    mapsFile.close();
    for (auto region : regions) {
        for (uintptr_t address = region.start; address < region.end; address += sizeof(long)) {
            char buffer[256] = {0};  // Buffer for reading
            size_t maxLen = sizeof(buffer);
        
            for (size_t i = 0; i < maxLen - 1; i++) {
                struct iovec local = { &buffer[i], 1 };  // Read one byte
                struct iovec remote = { (void*)(address + offset + i), 1 };
        
                ssize_t bytesRead = process_vm_readv(proc_id, &local, 1, &remote, 1, 0);
                if (bytesRead <= 0) {
                    //std::cerr << "Failed to read memory at " << std::hex << address + i << std::endl;
                    break;
                }
        
                if (buffer[i] == '\0') {  // Stop at null terminator
                    break;
                }
            }
            buffer[maxLen - 1] = '\0';  // Ensure null termination
            std::regex regexPattern(regex);
            bool found = std::regex_match(std::string(buffer), regexPattern);
            if (found)
                std::cout << "Found: " << buffer << std::endl;
        }
    }
}
