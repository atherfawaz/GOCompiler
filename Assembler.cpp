//
// Created by ather on 14-Jun-21.
//

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iosfwd>
#include "Assembler.h"

#define TACCODE words[0]

Assembler::Assembler::Assembler() = default;

Assembler::Assembler::~Assembler() {
    this->tacs.clear();
}

void Assembler::Assembler::buildTacArray(const std::string &filePath) {
    std::cout << "Building three-address-code array...\n";
    std::ifstream input(filePath);
    for (std::string line; getline(input, line);) {
        this->tacs.emplace_back(line);
        //std::cout << line << std::endl;
    }
}

void Assembler::Assembler::generateMachineCode() {

}

void Assembler::Assembler::runAssembler() {
    generateMachineCode();
    while (this->programCounter <= this->tacs.size()) {
        std::string line = this->tacs[programCounter];
        std::vector<std::string> words = splitByDelimiter(line, " ");
        processQuadruple(words);
        this->programCounter++; //increment pc
    }
}

void Assembler::Assembler::processQuadruple(std::vector<std::string> words) {
    if (TACCODE == "out") {
        //handle printing
        if (words[1][0] == '"') {
            //printing something as a string
            std::string toPrint;
            for (int i = 1; i < words.size(); i++) {
                toPrint += words[i] + " ";
            }
            toPrint.pop_back();
            toPrint.pop_back();
            toPrint.erase(toPrint.begin());
            std::cout << toPrint << std::endl;
        } else if (isdigit(words[1][0])) {
            //printing number
            std::cout << words[1] << std::endl;
        } else {
            //printing identifier
            std::cout << this->dataSegment[words[1]] << std::endl;
        }
    } else if (TACCODE == "goto") {
        //handle jumps
        /*
         * goto 24
         * words[0] = goto
         * words[1] = 24
         * */
        this->programCounter = std::stoi(words[1]) - 2;
    } else if (TACCODE == "in") {
        //handle cin
        //in x
        std::cin >> this->dataSegment[words[1]];
    } else if (TACCODE == "if" || TACCODE == "Wif" || TACCODE == "elif") {
        //handle ifs
        //if j == 1 goto 26
        /*
         * words[0] = if
         * words[1] = j
         * words[2] = ==
         * words[3] = 1
         * words[4] = goto
         * words[5] = 26
         * */
        bool result = handleRelationalOperator(words[2], words[1], words[3]);
        if (result) {
            this->programCounter = std::stoi(words[5]) - 2; //-1 for pc++ -1 for pc starting from 0
        }

    } else if (words.size() == 5) {
        //arithmetic assignment
        //temp0 = b + d
        //words[0] = temp0
        //words[1] = =
        //words[2] = b or 4
        //words[3] = +
        //words[4] = d or 5
        int left, right;
        this->dataSegment[words[0]] = INT_MIN;
        if (this->dataSegment.find(words[2]) != this->dataSegment.end()) {
            left = this->dataSegment[words[2]];
        } else left = std::stoi(words[2]);
        if (this->dataSegment.find(words[4]) != this->dataSegment.end()) {
            right = this->dataSegment[words[4]];
        } else right = std::stoi(words[4]);
        if (words[3] == "+") {
            this->dataSegment[words[0]] = left + right;
        } else if (words[3] == "-") {
            this->dataSegment[words[0]] = left - right;
        } else if (words[3] == "*") {
            this->dataSegment[words[0]] = left * right;
        } else {
            this->dataSegment[words[0]] = left / right;
        }
    } else if (words.size() == 3) {
        //simple assignment
        //a = 5 or a = 'x'
        if (words[2][0] == '\'') {
            //assign character
            //assign the middle part of string('x')
            char character = words[2][1];
            this->dataSegment[words[0]] = character;
        } else if (isalpha(words[2][0])) {
            //assign identifier
            this->dataSegment[words[0]] = this->dataSegment[words[2]];
        } else {
            //assign number
            this->dataSegment[words[0]] = std::stoi(words[2]);
        }
    }
}

void Assembler::Assembler::buildDataSegment(const std::string &filePath) {
    std::cout << "Building data segment...\n";
    std::ifstream input(filePath);
    for (std::string line; getline(input, line);) {
        std::vector<std::string> words = splitByDelimiter(line, ":");
        this->dataSegment[words[1]] = INT_MIN;
    }
}

std::vector<std::string> Assembler::Assembler::splitByDelimiter(std::string toSplit, const std::string &delim) {
    std::vector<std::string> words;
    size_t pos = 0;
    while ((pos = toSplit.find(delim)) != std::string::npos) {
        words.push_back(toSplit.substr(0, pos));
        toSplit.erase(0, pos + delim.length());
    }
    words.emplace_back(toSplit);
    return words;
}

bool
Assembler::Assembler::handleRelationalOperator(const std::string &op, const std::string &lop, const std::string &rop) {
    int left, right;
    if (this->dataSegment.find(lop) != this->dataSegment.end()) {
        left = this->dataSegment[lop];
    } else left = std::stoi(lop);
    if (this->dataSegment.find(rop) != this->dataSegment.end()) {
        right = this->dataSegment[rop];
    } else right = std::stoi(rop);
    if (op == "<") {
        return left < right;
    } else if (op == "<=") {
        return left <= right;
    } else if (op == ">") {
        return left > right;
    } else if (op == ">=") {
        return left >= right;
    } else if (op == "==") {
        return left == right;
    } else if (op == "!=") {
        return left >= right;
    } else {
        std::cerr << "Expected a relational operator but found " << op << " instead" << std::endl;
    }


}
