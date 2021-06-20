//
// Created by Mujtaba on 6/20/2021.
//

#ifndef MAIN_CPP_TAC_MAC_H
#define MAIN_CPP_TAC_MAC_H

#endif //MAIN_CPP_TAC_MAC_H
#include <map>
#include <fstream>
#include <regex>

namespace machineTranslator{


    class translator {
    private:


        std::map<std::string, int> translatorTable;
        std::map<std::string, int> location;
        std::string tac_file;
        std::string mac_file;
        std::string temp_name;
        int temp_number;
        int arr_pos = 1;

        std::vector<std::string> split(const std::string str, const std::string regex_str);
        bool isArithmetic(std::string opp);

    public:
        int memory[1000] = {0};
        std::vector<std::vector<int>> instructions;
        translator(const std::string &tac_file, const std::string &mac_file);
        ~translator();

        void generateMacCode();

        int findAddress(auto var);



    };





}