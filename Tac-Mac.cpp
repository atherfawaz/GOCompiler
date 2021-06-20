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



int machineTranslator::translator::findAddress(auto var) {
    if (isdigit(var[0])){
        this->location[this->temp_name + std::to_string(this->temp_number++)] = this->arr_pos;
        memory[this->arr_pos++] = std::stoi(var);
        return this->arr_pos -1;
    }else {
        if (this->location[var] == 0){ this->location[var]= this->arr_pos++;}
        return this->location[var];
    }


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
            int index = tokens.size() -2;
            std::string token = tokens[index];

            machineCode[0] = this->translatorTable[token];

            if (token == "goto"){
                // only goto
                if (token == tokens[0]){
                   machineCode[1] = std::stoi(tokens[index +1]);    // the line to jump too

                }else { // the gump
                    machineCode[3] = std::stoi(tokens[index + 1]);
                    index -= 2;
                    machineCode[0] = this->translatorTable[tokens[index]];
                    machineCode[2] = this->findAddress(tokens[index+1]);
                    machineCode[1] = this->findAddress(tokens[index -1]);
                }

            } else if (token == "in" || token == "out"){
                machineCode[1] = this->findAddress(tokens[index + 1]);

            }else if (token == "="){
                machineCode[1] = this->findAddress(tokens[index +1]);
                machineCode[2] = this->findAddress(tokens[index -1]);


            }else if (isArithmetic(token)){
                machineCode[3] = this->findAddress(tokens[0]);
                machineCode[2] = this->findAddress(tokens[index +1]);
                machineCode[1] = this->findAddress(tokens[index - 1]);

            }else {
                std::cout << "invalid tac code \n";

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