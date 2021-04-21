//
// Created by ather on 21-Apr-21.
//

#include "Token.h"
#include <iostream>

Lexer::Token::Token() {
    lexeme = '0';
    token = Lexer::NONE;
}

Lexer::Token::~Token() = default;

char Lexer::Token::getLexeme() const {
    return this->lexeme;
}

Lexer::TOKEN Lexer::Token::getToken() {
    return this->token;
}

Lexer::Token::Token(Lexer::TOKEN tok, char lexeme) : token(tok), lexeme(lexeme) {
}

std::ostream &Lexer::operator<<(std::ostream &out, const Lexer::Token &tok) {
    out << "(" << tok.token << " | " << tok.lexeme << " )";
    return out;
}

std::ostream &operator<<(std::ostream &os, Lexer::Token &tok) {
    os << tok.getToken() << " | " << tok.getToken();
    return os;
}