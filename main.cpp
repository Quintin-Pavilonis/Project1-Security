#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include "block.h"
#include "stream.h"

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {

    if (argc != 6) {
        return 1;
    }

    // argument input and checks / error output 
    const char* fileType = argv[1];
    if (std::string(argv[1]) != "B" && std::string(argv[1]) != "S") {
        std::cout << "Invalid Function Type" << std::endl;
        return 1;
    }

    const char* inputFilePath = argv[2];
    if (!fs::exists(inputFilePath)) {
       std::cout << "Input File Does Not Exist" << std::endl;
       return 1;
    }

    const char* outputFilePath = argv[3];

    const char* keyFilePath = argv[4];
    if (!fs::exists(keyFilePath)) {
       std::cout << "Key File Does Not Exist" << std::endl;
       return 1;
    }


    const char* modeOp = argv[5];
    if (std::string(argv[5]) != "E" && std::string(argv[5]) != "D") {
        std::cout << "Invalid Mode Type" << std::endl;
        return 1;
    }


    // had to change string to vectors as the string for input was causing issues removing the padding
    // file input reading
    std::ifstream inputFile(inputFilePath, std::ios::binary);
    std::vector<unsigned char> inputString((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();

    // key file input reading
    std::ifstream keyFile(keyFilePath, std::ios::binary);
    std::string keyString((std::istreambuf_iterator<char>(keyFile)), std::istreambuf_iterator<char>());
    keyFile.close();

    // block cipher call
    if (std::string(fileType) == "B") {
        blockCipher(inputString, outputFilePath, keyString, modeOp);
    }

    // stream cipher call
    if (std::string(fileType) == "S") {
        streamCipher(inputString, outputFilePath, keyString);
    }

    return 0;
}