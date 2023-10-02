#include "main.h"

char* readFile(const char* filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return nullptr;
    }

    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    //std::size_t bufferSize = static_cast<std::size_t>(fileSize) + 1;
    char* buffer = new char[fileSize];

    if (!file.read(buffer, fileSize)) {
        std::cerr << "Failed to read file: " << filename << std::endl;
        delete[] buffer;
        return nullptr;
    }
    buffer[fileSize] = '\0';

    file.close();

    return buffer;
}
