#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <algorithm>
#include "Lexer.h"

bool isValidSourceFile(std::string path) {
    std::transform(path.begin(), path.end(), path.begin(), [](unsigned char c) { return std::tolower(c); });
    if (path.substr(path.length() - 2) == "go") return true;
    return false;
}

std::string getSourceCode() {
    std::cout << "Enter the path of the source file: ";
    std::string path;
    std::cin >> path;
    while (!isValidSourceFile(path)) {
        std::cout << "\nNot a valid .go source code file. Please re-enter path: ";
        std::cin >> path;
    }
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
    std::string path = R"(D:\dev\GO-Compiler\words.txt)";
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
    std::cout << "\nEXPORTED TOKENS.\n";
    return 0;
}
