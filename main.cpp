#include <iostream>
#include <string>
#include <fstream>
#include "Lexer.h"

std::string getSourceCode() {
    std::string path = R"(D:\dev\GO-Compiler\code.go)";
    std::ifstream newFile(path);
    if (newFile.is_open()) {
        std::string sourceCode((std::istreambuf_iterator<char>(newFile)),
                               (std::istreambuf_iterator<char>()));
        newFile.close();
        return sourceCode;
    } else std::cout << "ERROR: FILE READING ERROR.";
    return "";
}

int main() {
    std::string sourceCode = getSourceCode();
    Lexer::Lexer Lexer(sourceCode);
    while (Lexer.getNext()) {
        std::cout << Lexer.getCurrent();
        Lexer.next();
    }
    return 0;
}
