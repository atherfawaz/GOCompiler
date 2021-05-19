//
// Created by ather on 18-May-21.
//

#include "Parser.h"
#include "Lexer.h"

#define CURRENTTOKEN tokens[cursor].getLexeme()

bool Parser::Parser::parse() {
    if (tokens[cursor].non_empty()) {
        START_PARSE();
    }
    return false;
}

Parser::Parser::Parser(const std::vector<Lexer::Token> &tok) {
    this->cursor = 0;
    this->tokens = tok;
}

void Parser::Parser::START_PARSE() {
    PROGRAM_START();
}

void Parser::Parser::PROGRAM_START() {
    if (match(CURRENTTOKEN, "func")) {
        FUNC_HEADER();
        PROG_S();
    }
}

void Parser::Parser::FUNC_HEADER() {
    if (match(CURRENTTOKEN, "func")) {
        RETURN_TYPE();
        IDENTIFIER();
    }
}

void Parser::Parser::PROG_S() {

}

bool Parser::Parser::match(const std::string &lexeme, const std::string &toMatch) {
    if (lexeme == toMatch) return true;
    return false;
}

void Parser::Parser::RETURN_TYPE() {
    cursor++;
    if (match(CURRENTTOKEN, "integer") || match(CURRENTTOKEN, "char") || match(CURRENTTOKEN, "void")) return;
    else {
        std::cerr << "Expected INTEGER, CHAR, or VOID but found " << CURRENTTOKEN << " instead." << std::endl;
        exit(1);
    }
}

void Parser::Parser::IDENTIFIER() {
    cursor++;
    if (isalpha(CURRENTTOKEN[0])) {
        ALPHABET();
        ALPHANUMERIC();
        IDENTIFIER();
    }
}

void Parser::Parser::ALPHABET() {
    if (isalpha(CURRENTTOKEN[0])) return;
    else {
        std::cerr << "Expected IDENTIFIER, but found " << CURRENTTOKEN << " instead." << std::endl;
        exit(1);
    }
}

void Parser::Parser::ALPHANUMERIC() {
    std::string str = CURRENTTOKEN;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalnum(str[i])) {
            std::cerr << "Expected IDENTIFIER, but found " << CURRENTTOKEN << " instead." << std::endl;
            exit(1);
        }
    }
}
