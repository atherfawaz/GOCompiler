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
        std::cout << line << std::endl;
    }
}

void Assembler::Assembler::runAssembler() {
    for (auto &line : this->tacs) {
        std::vector<std::string> words = splitByDelimiter(line, " ");
        processQuadruple(words);
    }
}

void Assembler::Assembler::processQuadruple(std::vector<std::string> words) {
    if (TACCODE == "out") {
        //handle printing
    } else if (TACCODE == "in") {
        //handle cin
    } else if (TACCODE == "Wif") {
        //handle whiles
    } else if (TACCODE == "if") {
        //handle ifs
    } else if (TACCODE == "elif") {
        //handle elifs
    } else if (words.size() == 5) {
        //arithmetic assignment
    } else if (words.size() == 3) {
        //simple assignment
        this->dataSegment[words[0]] = std::stoi(words[2]);
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
