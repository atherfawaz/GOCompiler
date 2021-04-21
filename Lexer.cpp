//
// Created by ather on 21-Apr-21.
//

#include "Lexer.h"

namespace Lexer {

    Lexer::Lexer() = default;

    Lexer::~Lexer() {
        keywords.clear();
    }

    Lexer::Lexer(std::string &code) {
        currentPtr = code.begin();
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

    std::vector<Token> Lexer::generateTokens() {
        std::vector<Token> toks;
        while (this->getNext()) {
            toks.push_back(findToken(this->getCurrent()));
            this->next();
        }
        return toks;
    }

    std::string charToString(char x) {
        return std::string(1, x);
    }


    Token Lexer::findToken(char currTok) {
        switch (currTok) {
            case '(':
                return Token(PRNT, charToString(currTok));
            case ')':
                return Token(PRNT, charToString(currTok));
            case '{':
                return Token(BRACES, charToString(currTok));
            case '}':
                return Token(BRACES, charToString(currTok));
            case '[':
                return Token(SQR_BRKT, charToString(currTok));
            case ']':
                return Token(SQR_BRKT, charToString(currTok));
            case '+':
                return Token(AR_OP, charToString(currTok));
            case '-':
                return Token(AR_OP, charToString(currTok));
            case '*':
                return Token(AR_OP, charToString(currTok));
            case '%':
                return Token(AR_OP, charToString(currTok));
            case ';':
                return Token(SEMICOLON, charToString(currTok));
            case ',':
                return Token(COMMA, charToString(currTok));
            case '/':
                return Token(AR_OP, charToString(currTok));
            case '>':
                currentPtr++;
                if (*currentPtr == '>') {
                    return Token(INPUT_OP, ">>");
                } else currentPtr--;
                return Token(RO_OP, charToString(currTok));
            case ':':
                currentPtr++;
                if (*currentPtr == '=') {
                    return Token(ASS_OP, ":=");
                } else currentPtr--;
                return Token(VAR_DEC, charToString(currTok));
            default:
                while (*currentPtr == ' ') {
                    currentPtr++;
                    currTok = *currentPtr;
                }
                if (isalpha(currTok)) {
                    std::string word;
                    word += currTok;
                    currentPtr++;
                    while (isalnum(*currentPtr)) {
                        word += *currentPtr;
                        currentPtr++;
                    }
                    if (isKeyword(word)) return Token(KEYWORD, word);
                    else return Token(IDENTIFIER, word);
                }
                return Token();
        }
    }

    bool Lexer::isKeyword(const std::string &word) {
        if (keywords.find(word) == keywords.end()) return false;
        return true;
    }
}