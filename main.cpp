#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "Lexer.h"
#include "Parser.h"
#include "global_path.h"
#include "Assembler.h"
#include "vm.h"

std::string dir_path;


// This function asks user for file path
// Reads information from specified file and removes cartridge return newline and tabs
// Additionally it updates the directory path in the global variable
std::string getSourceCode() {
    std::cout << "Enter the path of the source file: ";
    std::string path;
    std::cin >> path;

    if (path == "0") {
        path = global_path + "test.go";
    }

    dir_path = path.substr(0, path.find_last_of('\\'));
    std::ifstream file(path);
    if (file.is_open()) {
        std::string sourceCode((std::istreambuf_iterator<char>(file)),
                               (std::istreambuf_iterator<char>()));
        file.close();
        return sourceCode;
    } else std::cout << "ERROR: FILE READING ERROR.";
    return "";
}

// This function writes the tokens to the file words.txt
// and directory extracted when we asked for the source file

void exportTokens(const std::vector<Lexer::Token> &tokens) {
    std::string path = dir_path + "\\words.txt";
    std::ofstream file(path);
    if (file.is_open()) {
        for (const auto &tok: tokens) {
            //if (tok.non_empty()) {
            file << tok << std::endl;
            //}
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

    //std::cout << "GENERATING TOKENS.\n";
    std::vector<Lexer::Token> tokens = Lexer.generateTokens();
    //std::cout << "GENERATED TOKENS.\n";

    Lexer::init_mapping();

    for (int i = 0; i < tokens.size(); i++) {
        auto test = tokens[i].getToken();
        if (!tokens[i].non_empty()) {
            tokens.erase(tokens.begin() + i);
            i--;
        }
    }

    exportTokens(tokens);

    //std::cout << "PARSING PROGRAM.\n";
    Parser::Parser Parser(tokens, global_path + "parsetree.txt", global_path + "translator-symboltable.txt",
                          global_path + "tac.txt");

    Parser.parse();

    Assembler::Assembler Assembler;
    Assembler.buildDataSegment(global_path + "translator-symboltable.txt");
    Assembler.buildTacArray(global_path + "tac.txt");
    VirtualMachine::VirtualMachine vm(global_path + "tac.txt", global_path + "mac.txt");

    bool input_verfied = false;
    while (!input_verfied) {
        char user_input;
        std::cout << "\n Input a for running assembler and v for running virutal machine \n";
        std::cin >> user_input;
        switch (user_input) {
            case 'a':
                input_verfied = true;
                std::cout << "Running Assembler...\n";

                Assembler.runAssembler();

                break;
            case 'v':
                input_verfied = true;

                std::cout << "Running VM...\n";
                vm.execute();
                std::cout << "VM complete.\n";
                break;
            default:
                std::cout << "Invalid selection \n";
                break;

        }
    }




    return 0;
}
