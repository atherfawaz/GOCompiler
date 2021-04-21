#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "Lexer.h"

std::string getSourceCode() {
    std::string path = R"(D:\dev\GO-Compiler\code.go)";
    std::ifstream file(path);
    if (file.is_open()) {
        std::string sourceCode((std::istreambuf_iterator<char>(file)),
                               (std::istreambuf_iterator<char>()));
        file.close();
        sourceCode.erase(std::remove(sourceCode.begin(), sourceCode.end(), '\r'), sourceCode.end());
        sourceCode.erase(std::remove(sourceCode.begin(), sourceCode.end(), '\t'), sourceCode.end());
        sourceCode.erase(std::remove(sourceCode.begin(), sourceCode.end(), '\n'), sourceCode.end());
        return sourceCode;
    } else std::cout << "ERROR: FILE READING ERROR.";
    return "";
}

int main() {
    std::string sourceCode = getSourceCode();
    Lexer::Lexer Lexer(sourceCode);
    auto tokens = Lexer.generateTokens();

    for (const auto &tok: tokens) {
        std::cout << tok << std::endl;
    }
    return 0;
}
