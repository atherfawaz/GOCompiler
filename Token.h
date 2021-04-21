//
// Created by ather on 21-Apr-21.
//

#ifndef GO_COMPILER_TOKEN_H
#define GO_COMPILER_TOKEN_H

#include <iostream>

namespace Lexer {
    enum TOKEN {
        AR_OP,
        RO_OP,
        COMMENT,
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
        char lexeme;
    public:
        Token();

        Token(TOKEN tok, char lexeme);

        ~Token();

        char getLexeme() const;

        TOKEN getToken();

        friend std::ostream &operator<<(std::ostream &out, const Lexer::Token &tok);

    };

}


#endif //GO_COMPILER_TOKEN_H
