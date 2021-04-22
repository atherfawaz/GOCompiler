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

[[maybe_unused]] std::string Lexer::Token::getLexeme() const {
    return this->lexeme;
}

Lexer::TOKEN Lexer::Token::getToken() {
    return this->token;
}

Lexer::Token::Token(Lexer::TOKEN tok, std::string lexeme) : token(tok), lexeme(std::move(lexeme)) {
}

std::ostream &Lexer::operator<<(std::ostream &out, const Lexer::Token &tok) {
    std::map<int , std::string> token_mapping;
    std::string tokens[] = { "AR_OP", "RO_OP", "IDENTIFIER", "NUMBER", "LIT_CONST", "STRING" ,"VAR_DEC", "ASS_OP", "INPUT_OP", "PRNT", "SQR_BRKT", "BRACES" ,"SEMICOLON", "COMMA", "KEYWORD","DATATYPE","NONE"};
    int i = 0;
    for (const auto& a_token : tokens){
        token_mapping.insert({i, a_token});
        ++i;
    }

    out << "(" << token_mapping.at(tok.token) << " | " << tok.lexeme << ")";
    return out;
}

std::ostream &operator<<(std::ostream &os, Lexer::Token &tok) {
    os << tok.getToken() << " | " << tok.getToken();
    return os;
}