#include <vector>
#ifndef BLOCK_H
#define BLOCK_H

void blockCipher(const std::vector<unsigned char>& inputString, const char* outputFile, const std::string& keyString, const std::string& mode);

#endif