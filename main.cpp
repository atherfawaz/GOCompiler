#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "Lexer.h"

std::string dir_path;


// This function asks user for file path
// Reads information from specified file and removes cartridge return newline and tabs
// Additionally it updates the directory path in the global variable
std::string getSourceCode() {
    std::cout << "Enter the path of the source file: ";
    std::string path;
    std::cin >> path;

    dir_path = path.substr(0, path.find_last_of("\\"));
    std::ifstream file(path);
    if (file.is_open()) {
        std::string sourceCode((std::istreambuf_iterator<char>(file)),
                               (std::istreambuf_iterator<char>()));
        file.close();
//        sourceCode.erase(std::remove(sourceCode.begin(), sourceCode.end(), '\r'), sourceCode.end());
//        sourceCode.erase(std::remove(sourceCode.begin(), sourceCode.end(), '\t'), sourceCode.end());
//        sourceCode.erase(std::remove(sourceCode.begin(), sourceCode.end(), '\n'), sourceCode.end());
        return sourceCode;
    } else std::cout << "ERROR: FILE READING ERROR.";
    return "";
}

// This function writes the tokens to the file words.txt
// and directory extracted when we asked for the source file

void exportTokens(const std::vector<Lexer::Token> &tokens) {
    std::string path = dir_path + "words.txt";
    std::ofstream file(path);
    if (file.is_open()) {
        for (const auto &tok: tokens) {
            file << tok << std::endl;
        }
        file.close();
    } else std::cout << "ERROR: FILE WRITING ERROR.";
}

// we run the main logic of program in this main
// 1. Get source code from specified file
// 2. Create a new Lexer object from the given sourceCode
// 3. Get tokens from the lexer object
// 4. Print those token and write them to the file
int main() {
    std::string sourceCode = getSourceCode();
    Lexer::Lexer Lexer(sourceCode);
    auto tokens = Lexer.generateTokens();

    Lexer::init_mapping();
    for (const auto &tok: tokens) {
        std::cout << tok << std::endl;
    }

    std::cout << "\nEXPORTING TOKENS.\n";
    exportTokens(tokens);
    std::cout << "\nEXPORTED TOKENS.\n";
    return 0;
}
