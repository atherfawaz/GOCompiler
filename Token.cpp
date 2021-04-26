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
}

Lexer::Token::~Token() = default;

[[maybe_unused]] std::string Lexer::Token::getLexeme() const {
    return this->lexeme;
}

Lexer::TOKEN Lexer::Token::getToken() {
    return this->token;
}

Lexer::Token::Token(Lexer::TOKEN tok, std::string lexeme) : token(tok), lexeme(std::move(lexeme)) {

}

// the maping information is imported from global.h

void Lexer::init_mapping() {
    int i = 0;
    for (const auto &a_token : tokens_list) {
        token_mapping.insert({i, a_token});
        ++i;
    }
}

std::ostream& Lexer::operator<<(std::ostream &out, const Lexer::Token &tok) {

    out << token_mapping.at(tok.token) << " " << tok.lexeme;
    return out;
}
