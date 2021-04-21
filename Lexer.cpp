//
// Created by ather on 21-Apr-21.
//

#include "Lexer.h"

namespace Lexer {

    Lexer::Lexer() {
        currentPtr = std::string("string").begin();
        keywords["if"] = "IF";
        keywords["elif"] = "ELIF";
        keywords["else"] = "ELSE";
        keywords["while"] = "WHILE";
        keywords["in"] = "IN";
        keywords["print"] = "PRINT";
        keywords["println"] = "PRINTLN";
        keywords["integer"] = "INTEGER";
        keywords["char"] = "CHAR";
    }

    Lexer::~Lexer() {
        keywords.clear();
    }

    Lexer::Lexer(std::string &code) {
        currentPtr = code.begin();
    }

    void Lexer::next() {
        currentPtr++;
    }

    char Lexer::getNext() {
        currentPtr++;
        char next = *currentPtr;
        currentPtr--;
        if (next) return next;
        return '\0';
    }

    void Lexer::prev() {
        currentPtr--;
    }

    char Lexer::getCurrent() {
        return *currentPtr;
    }
}