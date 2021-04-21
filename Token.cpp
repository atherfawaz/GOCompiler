//
// Created by ather on 21-Apr-21.
//

#include "Token.h"
#include <iostream>
#include <utility>

Lexer::Token::Token() {
    lexeme = '0';
    token = Lexer::NONE;
}

Lexer::Token::~Token() = default;

std::string Lexer::Token::getLexeme() const {
    return this->lexeme;
}

Lexer::TOKEN Lexer::Token::getToken() {
    return this->token;
}

Lexer::Token::Token(Lexer::TOKEN tok, std::string lexeme) : token(tok), lexeme(std::move(lexeme)) {
}

std::ostream &Lexer::operator<<(std::ostream &out, const Lexer::Token &tok) {
    out << "(" << tok.token << " | " << tok.lexeme << " )";
    return out;
}

std::ostream &operator<<(std::ostream &os, Lexer::Token &tok) {
    os << tok.getToken() << " | " << tok.getToken();
    return os;
}