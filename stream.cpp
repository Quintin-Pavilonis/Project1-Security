#include <cstdlib>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <iomanip>
#include "stream.h"
#include <vector>


void streamCipher(const std::vector<unsigned char>& inputString, const char* outputFile, const std::string& keyString) {

    std::vector<unsigned char> processedInput = inputString;
    std::vector<unsigned char> processedOutput;

    // encrypt and decrypt 
    size_t keyLength = keyString.size();

    for (size_t i = 0; i < processedInput.size(); i++) {

        // cycles through key file char, cycling back if input larger than key
        unsigned char keyChar = keyString[i % keyLength];
        processedOutput.push_back(processedInput[i] ^ keyChar);
    }

    // output
    std::ofstream outFile(outputFile, std::ios::binary);
    if (outFile.is_open()) {
        outFile.write(reinterpret_cast<const char*>(processedOutput.data()), processedOutput.size());
        outFile.close();
    }

}