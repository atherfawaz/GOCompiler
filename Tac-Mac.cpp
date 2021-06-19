//
// Created by Mujtaba on 6/20/2021.
//

#include <iostream>
#include "Tac-Mac.h"


machineTranslator::translator::translator(const std::string &tac_file, const std::string &mac_file) {

    this->tac_file = tac_file;
    this->mac_file = mac_file;
    this->temp_name = "tempu";
    this->temp_number = 1;

    translatorTable["="] = 1;
    translatorTable["+"] = 2;
    translatorTable["-"] = 3;
    translatorTable["/"] = 4;
    translatorTable["*"] = 5;
    translatorTable["<"] = 6;
    translatorTable[">"] = 7;
    translatorTable["=="] = 8;
    translatorTable["<="] = 9;
    translatorTable[">="] = 10;
    translatorTable["if"] = 11;
    translatorTable["in"] = 12;
    translatorTable["out"] = 13;
    translatorTable["goto"] = 14;

}

machineTranslator::translator::~translator() {


}

std::vector<std::string> machineTranslator::translator::split(const std::string str, const std::string regex_str) {

    std::regex regexz(regex_str);
    std::vector<std::string> list(std::sregex_token_iterator(str.begin(), str.end(), regexz, -1),
                                  std::sregex_token_iterator());
    return list;
}

bool machineTranslator::translator::isArithmetic(std::string opp) {
    if (opp == "+" || opp == "-" || opp == "*" || opp == "/") return true;
    return false;
}

bool machineTranslator::translator::isRelational(std::string opp) {
    if (opp == "==" || opp == "<" || opp == ">" || opp == "<=" || opp == ">=") return true;
    return false;
}

void machineTranslator::translator::generateMacCode() {

    std::string line;
    std::ifstream myfile (this->tac_file);
    std::ofstream macFile;
    macFile.open(this->mac_file);
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            std::string regex_str = " ";
            int machineCode[4] = {-1, -1, -1, -1};
            auto tokens = split(line, regex_str);
            int index = tokens.size() -1;
            std::string token = tokens[index];



            if (isdigit(token[0])) {

                if( tokens[index - 1] == "goto"){

                    // case of simple goto statement
                    if (index -1 == 0){
                        machineCode[0] = this->translatorTable["goto"];
                        machineCode[1] = std::stoi(tokens[index]);
                    }
                    // case of complex jump
                    else {
                        machineCode[3] = std::stoi(tokens[index]);
                        index -= 2;
                        // case of jump with number of rhs
                        if (isdigit(tokens[index][0])){
                            machineCode[0] = translatorTable[tokens[index -1]];
                            this->location[this->temp_name + std::to_string(this->temp_number++)] = this->arr_pos;
                            memory[this->arr_pos++] = std::stoi(tokens[index]);
                            machineCode[2] = this->arr_pos -1;
                        }
                        else {
                            machineCode[2] = this->location[tokens[index]];
                        }
                        // assuming lhs always identifier
                        machineCode[1] = this->location[tokens[index - 2]];

                    }

                } else if (tokens[index - 1] == "=" || tokens[index - 1] == "out") {
                    this->location[this->temp_name + std::to_string(this->temp_number++)] = this->arr_pos;
                    memory[this->arr_pos++] = std::stoi(tokens[index]);
                    machineCode[1] = this->arr_pos -1;
                    // for the case of printing out
                    if (tokens[index - 1] == "out"){
                        machineCode[0] = this->translatorTable["out"];

                    } else {    // for the case of assignment
                        machineCode[0] = this->translatorTable["="];

                        if (this->location[tokens[0]] == 0){ this->location[tokens[0]]= this->arr_pos++;}
                        machineCode[2] = this->location[tokens[0]];

                    }
                    // the case of expressoin starting with number
                } else if (isArithmetic(tokens[index -1])) {

                    machineCode[0] = this->translatorTable[tokens[index -1]];
                    this->location[this->temp_name + std::to_string(this->temp_number++)] = this->arr_pos;
                    memory[this->arr_pos++] = std::stoi(tokens[index]);
                    machineCode[2] = this->arr_pos -1;

                    if (isdigit(tokens[index -2][0])){
                        this->location[this->temp_name + std::to_string(this->temp_number++)] = this->arr_pos;
                        memory[this->arr_pos++] = std::stoi(tokens[index - 2]);
                        machineCode[1] = this->arr_pos -1;
                    } else {
                        machineCode[1] = this->location[tokens[index -2]];
                    }

                    if (this->location[tokens[0]] == 0){ this->location[tokens[0]]= this->arr_pos++;}
                    machineCode[3] = this->location[tokens[0]];


                }


            } else {
                // possible = out, in, =, art
                machineCode[0] = this->translatorTable[tokens[index -1]];
                if( tokens[index - 1] == "out" || tokens[index -1] == "in"){
                    machineCode[1] = this->location[token];
                } else if (tokens[index -1] == "="){
                    machineCode[1] = this->location[token];
                    if (this->location[tokens[0]] == 0){ this->location[tokens[0]]= this->arr_pos++;}
                    machineCode[2] = this->location[tokens[0]];

                } else if (isArithmetic(tokens[index -1])){
                    machineCode[2] = this->location[token];
                    if (isdigit(tokens[index -2][0])){
                        this->location[this->temp_name + std::to_string(this->temp_number++)] = this->arr_pos;
                        memory[this->arr_pos++] = std::stoi(tokens[index - 2]);
                        machineCode[1] = this->arr_pos -1;
                    } else {machineCode[1] = this->location[tokens[index -2]];}
                    if (this->location[tokens[0]] == 0){ this->location[tokens[0]]= this->arr_pos++;}
                    machineCode[3] = this->location[tokens[0]];

                }

            }

            for(int i = 0; i < 4; i ++){
                if (machineCode[i] != -1){
                    macFile << std::to_string(machineCode[i]) + " ";
                    //std::cout <<  machineCode[i];
                }
            }
            macFile << std::endl;

        }
        myfile.close();
        macFile.close();
    }

    else std::cout << "Unable to open file";

}