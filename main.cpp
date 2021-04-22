#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "Lexer.h"
#include "global.h"

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
    std::string path = R"(D:\dev\GO-Compiler\exportedTokens.txt)";
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
    std::string tokens_list[] = { "AR_OP", "RO_OP", "IDENTIFIER", "NUMBER", "LIT_CONST", "STRING" ,"VAR_DEC", "ASS_OP", "INPUT_OP", "PRNT", "SQR_BRKT", "BRACES" ,"SEMICOLON", "COMMA", "KEYWORD","DATATYPE","NONE"};

    int i = 0;
    for (auto a_token : tokens_list){
        token_mapping.insert({i, a_token});
        ++i;
    }



    auto tokens = Lexer.generateTokens();


    for (const auto &tok: tokens) {
        std::cout << tok << std::endl;
    }

    std::cout << "\nEXPORTING TOKENS.\n";
    exportTokens(tokens);
    return 0;
}
