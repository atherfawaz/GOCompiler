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

    Token Lexer::findToken(char currTok) {
        switch (currTok) {
            case '(':
                return Token(PRNT, currTok);
            case ')':
                return Token(PRNT, currTok);
            case '{':
                return Token(BRACES, currTok);
            case '}':
                return Token(BRACES, currTok);
            case '[':
                return Token(SQR_BRKT, currTok);
            case ']':
                return Token(SQR_BRKT, currTok);
            case '+':
                return Token(AR_OP, currTok);
            case '-':
                return Token(AR_OP, currTok);
            case '*':
                return Token(AR_OP, currTok);
            case '%':
                return Token(AR_OP, currTok);
            case ';':
                return Token(SEMICOLON, currTok);
            case ',':
                return Token(COMMA, currTok);
            case '/':
                return Token(AR_OP, currTok);
            case '>':
                currentPtr++;
                if (*currentPtr == '>') {
                    return Token(INPUT_OP, '^');
                } else currentPtr--;
                return Token(RO_OP, currTok);
            case ':':
                currentPtr++;
                if (*currentPtr == '=') {
                    return Token(ASS_OP, '^');
                } else currentPtr--;
                return Token(VAR_DEC, currTok);
            default:
                while (*currentPtr == ' ') {
                    currentPtr++;
                    currTok = *currentPtr;
                }
                if (isalpha(currTok)) {
                    //add code here.
                    //check if we should change definition of Token to Token(TOKEN, String) from Token(TOKEN,char)
                }
                return Token();
        }
    }
}