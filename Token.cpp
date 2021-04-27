//
// Created by ather on 21-Apr-21.
//

#include "Token.h"
#include <iostream>
#include <utility>
#include "globals.h"

Lexer::Token::Token() {
    lexeme = '0';
    token = Lexer::NONE;
    row = 0;
    col = 0;
}

Lexer::Token::~Token() = default;

[[maybe_unused]] std::string Lexer::Token::getLexeme() const {
    return this->lexeme;
}

Lexer::TOKEN Lexer::Token::getToken() {
    return this->token;
}

Lexer::Token::Token(Lexer::TOKEN tok, std::string lexeme, int row, int col) : token(tok), lexeme(std::move(lexeme)), row(row), col(col) {}

// the maping information is imported from global.h

void Lexer::init_mapping() {
    int i = 0;
    for (const auto &a_token : tokens_list) {
        token_mapping.insert({i, a_token});
        ++i;
    }
}
bool Lexer::Token::non_empty() const {
    if (lexeme != "0")
        return true;
    else
        return false;
}

std::ostream& Lexer::operator<<(std::ostream &out, const Lexer::Token &tok) {

    out << token_mapping.at(tok.token) << " " << tok.lexeme << " row " + std::to_string(tok.row) + " col " + std::to_string(tok.col);

    return out;
}
