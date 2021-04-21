//
// Created by ather on 21-Apr-21.
//

#include "Lexer.h"

namespace Lexer {

    Lexer::Lexer() = default;

    Lexer::~Lexer() {
        keywords.clear();
        datatypes.clear();
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

        datatypes["Integer"] = "INTEGER";
        datatypes["Char"] = "CHAR";
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
        while (*currentPtr == ' ') {
            currentPtr++;
            currTok = *currentPtr;
        }
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
            case '<':
                return Token(RO_OP, charToString(currTok));
            case '=': {
                std::string op;
                op += '=';
                currentPtr++;
                if (*currentPtr == '=') {
                    op += *currentPtr;
                    return Token(RO_OP, op);
                } else {
                    std::cout << "Syntax error!";
                    return Token();
                }
            }
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
            case '"': {
                std::string str;
                str += '"';
                currentPtr++;
                while (*currentPtr != '"') {
                    str += *currentPtr;
                    currentPtr++;
                }
                str += '"';
                return Token(STRING, str);
            }
            default:
                if (isalpha(currTok)) {
                    std::string word;
                    word += currTok;
                    currentPtr++;
                    while (isalnum(*currentPtr)) {
                        word += *currentPtr;
                        currentPtr++;
                    }
                    currentPtr--;
                    if (isKeyword(word)) return Token(KEYWORD, word);
                    else if (isDataType(word)) return Token(DATATYPE, word);
                    else return Token(IDENTIFIER, word);
                } else if (isdigit(currTok)) {
                    std::string number;
                    number += currTok;
                    currentPtr++;
                    while (isdigit(*currentPtr)) {
                        number += *currentPtr;
                        currentPtr++;
                    }
                    currentPtr--;
                    return Token(NUMBER, number);
                }
                currTok = *currentPtr;
                std::cout << "Returning default token for: " << currTok << std::endl;
                return Token();
        }
    }

    bool Lexer::isKeyword(const std::string &word) {
        if (keywords.find(word) == keywords.end()) return false;
        return true;
    }

    bool Lexer::isDataType(const std::string &word) {
        if (datatypes.find(word) == datatypes.end()) return false;
        return true;
    }
}