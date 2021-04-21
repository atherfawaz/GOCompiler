//
// Created by ather on 21-Apr-21.
//

#ifndef GO_COMPILER_TOKEN_H
#define GO_COMPILER_TOKEN_H

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
    };

    class Token {

    };

}


#endif //GO_COMPILER_TOKEN_H
