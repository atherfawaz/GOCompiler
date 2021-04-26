//
// Created by ather on 21-Apr-21.
//

#ifndef GO_COMPILER_TOKEN_H
#define GO_COMPILER_TOKEN_H

#include <iostream>
#include <string>


namespace Lexer {
    // All possible token types that our program excepts
    enum TOKEN {
        AR_OP,  // Arathematic Operations +, -, *, /
        RO_OP,  // Relational Operators <, >, =, <=, >=, /=
        IDENTIFIER, // Identifier(vairbale or function name) starts off from alpha value then it can have any alpha numaric input
        NUMBER,     // Numaric input
        LIT_CONST,  // a character example 'c'
        STRING,     // String input example "Hello world"
        VAR_DEC,    // Variable declaration operator :, initializes the variable instantly
        ASS_OP,     // Assignment operator LHS := RHS   put the value of constant/Variable in RHS to LHS
        INPUT_OP,   // To take input from the user <<
        PRNT,       // Regular parenthesis ( )
        SQR_BRKT,   // Regular square brackets [ ]
        BRACES,     // Regular Braces { }
        SEMICOLON,  // ;
        COMMA,      // ,
        KEYWORD,    // a special identifier that is stored in the keyword table
        DATATYPE,   // a string or an Integer
        NONE,       // None of the above
    };

    // This is the class to store tokens( as mentioned above ) and lexeme(token values as extracted from the source code) pairs
    // This is an Immutable class
    // we have overloaded output operator << to write these to files and cout
    class Token {
    private:
        TOKEN token;
        std::string lexeme;
    public:
        Token();

        Token(TOKEN tok, std::string lexeme);

        ~Token();

        // for future use
        [[maybe_unused]] [[nodiscard]] std::string getLexeme() const;

        TOKEN getToken();

        friend std::ostream& operator<<(std::ostream &out, const Lexer::Token &tok);

    };

    std::ostream& operator<<(std::ostream &out, const Lexer::Token &tok);

    // maps the the token number returned from enum to their string value
    void init_mapping();
}


#endif //GO_COMPILER_TOKEN_H