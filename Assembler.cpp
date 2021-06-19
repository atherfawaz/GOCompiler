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

void Assembler::Assembler::runAssembler() {
    for (auto &line : this->tacs) {
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
        int code = -1;
        if (isalpha(*words[1].begin())) {
            //first is identifier
            if (isalpha(*words[3].begin())) {
                //second is identifier too
                code = 1;
            } else if (isdigit(*words[3].begin())) {
                //only left is identifier
                code = 3;
            }
            bool result = handleRelationalOperator(words[2], words[1], words[3], code);
            if (result) {
                this->programCounter = std::stoi(words[5]) - 1;
            }
        } else if (isdigit(*words[1].begin())) {
            //first is digit
            if (isalpha(*words[3].begin())) {
                code = 2;
            } else if (isdigit(*words[3].begin())) {
                code = 4;
            }
            bool result = handleRelationalOperator(words[2], words[1], words[3], code);
            if (result) {
                this->programCounter = std::stoi(words[5]) - 1;
            }
        }
    } else if (words.size() == 5) {
        //arithmetic assignment
        //temp0 = b + d
        //words[0] = temp0
        //words[1] = =
        //words[2] = b
        //words[3] = +
        //words[4] = d
        this->dataSegment[words[0]] = INT_MIN;
        if (words[3] == "+") {
            int result = this->dataSegment[words[2]] + this->dataSegment[words[4]];
            //std::cout << "Result: " << result << std::endl;
        } else if (words[3] == "-") {
            this->dataSegment[words[0]] = this->dataSegment[words[2]] - this->dataSegment[words[4]];
        } else if (words[3] == "*") {
            this->dataSegment[words[0]] = this->dataSegment[words[2]] * this->dataSegment[words[4]];
        } else {
            this->dataSegment[words[0]] = this->dataSegment[words[2]] / this->dataSegment[words[4]];
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
Assembler::Assembler::handleRelationalOperator(const std::string &op, const std::string &lop, const std::string &rop,
                                               int code) {
    if (code == 1) {
        //both identifiers
        if (op == "<") {
            return this->dataSegment[lop] < this->dataSegment[rop];
        } else if (op == "<=") {
            return this->dataSegment[lop] <= this->dataSegment[rop];
        } else if (op == ">") {
            return this->dataSegment[lop] > this->dataSegment[rop];
        } else if (op == ">=") {
            return this->dataSegment[lop] >= this->dataSegment[rop];
        } else if (op == "==") {
            return this->dataSegment[lop] == this->dataSegment[rop];
        } else if (op == "!=") {
            return this->dataSegment[lop] >= this->dataSegment[rop];
        } else {
            std::cerr << "Expected a relational operator but found " << op << " instead" << std::endl;
        }
    } else if (code == 2) {
        //only right identifier
        if (op == "<") {
            return std::stoi(lop) < this->dataSegment[rop];
        } else if (op == "<=") {
            return std::stoi(lop) <= this->dataSegment[rop];
        } else if (op == ">") {
            return std::stoi(lop) > this->dataSegment[rop];
        } else if (op == ">=") {
            return std::stoi(lop) >= this->dataSegment[rop];
        } else if (op == "==") {
            return std::stoi(lop) == this->dataSegment[rop];
        } else if (op == "!=") {
            return std::stoi(lop) >= this->dataSegment[rop];
        } else {
            std::cerr << "Expected a relational operator but found " << op << " instead" << std::endl;
        }
    } else if (code == 3) {
        //only left identifier
        if (op == "<") {
            return this->dataSegment[lop] < std::stoi(rop);
        } else if (op == "<=") {
            return this->dataSegment[lop] <= std::stoi(rop);
        } else if (op == ">") {
            return this->dataSegment[lop] > std::stoi(rop);
        } else if (op == ">=") {
            return this->dataSegment[lop] >= std::stoi(rop);
        } else if (op == "==") {
            return this->dataSegment[lop] == std::stoi(rop);
        } else if (op == "!=") {
            return this->dataSegment[lop] >= std::stoi(rop);
        } else {
            std::cerr << "Expected a relational operator but found " << op << " instead" << std::endl;
        }
    } else {
        //none identifier
        if (op == "<") {
            return std::stoi(lop) < std::stoi(rop);
        } else if (op == "<=") {
            return std::stoi(lop) <= std::stoi(rop);
        } else if (op == ">") {
            return std::stoi(lop) > std::stoi(rop);
        } else if (op == ">=") {
            return std::stoi(lop) >= std::stoi(rop);
        } else if (op == "==") {
            return std::stoi(lop) == std::stoi(rop);
        } else if (op == "!=") {
            return std::stoi(lop) >= std::stoi(rop);
        } else {
            std::cerr << "Expected a relational operator but found " << op << " instead" << std::endl;
        }
    }
}
