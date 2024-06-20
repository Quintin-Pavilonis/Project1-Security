#include <cstdlib>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "block.h"

namespace fs = std::filesystem;

void blockCipher(const std::string& inputString, const char* outputFile, const std::string& keyString) {

    size_t inputSize = inputString.size();
    size_t paddingSize = (16 - (inputSize % 16) % 16);

    std::string paddedInput = inputString;

    if (paddingSize > 0) {
        paddedInput.append(paddingSize, 0x81);
    }
}