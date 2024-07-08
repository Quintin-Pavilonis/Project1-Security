#include <cstdlib>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <iomanip>
#include "block.h"
#include <vector>


void blockCipher(const std::vector<unsigned char>& inputString, const char* outputFile, const std::string& keyString, const std::string& mode) {

    bool encrypt = (mode == "E");
    
    std::vector<unsigned char> processedInput = inputString;

    // pads if less than 16 bit and not empty
    if( encrypt && !processedInput.empty()) {
        size_t inputSize = inputString.size();
        size_t paddingSize = (16 - (inputSize % 16));
        if (paddingSize < 16) {
            processedInput.insert(processedInput.end(), paddingSize, 0x81);
        }
    }

    std::vector<unsigned char> encryptedString;

        for (size_t i = 0; i < processedInput.size(); i += 16) {
            std::vector<unsigned char> block(processedInput.begin() + i, processedInput.begin() + i + 16);

            if (encrypt) {
                for (size_t j = 0; j < 16; j++) {
                    block[j] ^= keyString[j];
                }

            size_t start = 0, end = 15;

            // encryption
            for (size_t k = 0; k < 16 && start < end; k++) {
                if (keyString[k % 16] % 2 == 1) {
                    std::swap(block[start], block[end]);
                    start++;
                    end--;

                } else {
                    start++;
                }
            }
            } else {

                // decryption
                size_t start = 0, end = 15;
                for(size_t k = 0; k < 16 && start < end; k++) {
                    if (keyString [k % 16] % 2 == 1) {
                        std::swap(block[start], block[end]);
                        start++;
                        end--;
                    } else {
                        start++;
                    }
                }

                for (size_t j = 0; j < 16; j++) {
                    block[j] ^= keyString[j];
                }
            }

                encryptedString.insert(encryptedString.end(), block.begin(), block.end());
        }

    // remove padding from decrypted file
    if (!encrypt) {
        while (!encryptedString.empty() && encryptedString.back() == 0x81) {
            encryptedString.pop_back();
        }
    }

    // output
    std::ofstream outFile(outputFile, std::ios::binary);
    if (outFile.is_open()) {
        outFile.write(reinterpret_cast<const char*>(encryptedString.data()), encryptedString.size());
        outFile.close();
    }
}