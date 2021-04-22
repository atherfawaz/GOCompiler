#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "Lexer.h"

std::string getSourceCode() {
    std::string path = R"(C:\Users\Mujtaba\CLionProjects\GOCompiler\code.go)";
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

void exportTokens(const std::vector<Lexer::Token> &tokens) {
    std::string path = R"(C:\Users\Mujtaba\CLionProjects\GOCompiler\exportedTokens.txt)";
    std::ofstream file(path);
    if (file.is_open()) {
        for (const auto &tok: tokens) {
            file << tok << std::endl;
        }
        file.close();
    } else std::cout << "ERROR: FILE WRITING ERROR.";
}

int main() {
    std::string sourceCode = getSourceCode();
    Lexer::Lexer Lexer(sourceCode);
    auto tokens = Lexer.generateTokens();


    for (const auto &tok: tokens) {
        std::cout << tok << std::endl;
    }

    std::cout << "\nEXPORTING TOKENS.\n";
    exportTokens(tokens);
    return 0;
}
