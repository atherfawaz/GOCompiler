//
// Created by ather on 21-Apr-21.
//

#ifndef GO_COMPILER_TOKEN_H
#define GO_COMPILER_TOKEN_H

#include <iostream>
#include <string>

namespace Lexer {
    enum TOKEN {
        AR_OP,
        RO_OP,
        IDENTIFIER,
        NUMBER,
        LIT_CONST,
        STRING,
        VAR_DEC,
        ASS_OP,
        INPUT_OP,
        PRNT,
        SQR_BRKT,
        BRACES,
        SEMICOLON,
        COMMA,
        KEYWORD,
        DATATYPE,
        NONE,
    };

    class Token {
    private:
        TOKEN token;
        std::string lexeme;
    public:
        Token();

        Token(TOKEN tok, std::string lexeme);

        ~Token();

        std::string getLexeme() const;

        TOKEN getToken();

        friend std::ostream &operator<<(std::ostream &out, const Lexer::Token &tok);

    };

}


#endif //GO_COMPILER_TOKEN_H
