//
// Created by ather on 18-May-21.
//

#ifndef MAIN_CPP_PARSER_H
#define MAIN_CPP_PARSER_H

#include "Token.h"
#include <utility>
#include <vector>

namespace Parser {

    class Parser {
    private:
        int cursor = 0;
        int tabs = 0;
        std::vector<Lexer::Token> tokens;

    public:
        Parser();

        explicit Parser(const std::vector<Lexer::Token> &tok);

        static bool match(const std::string &lexeme, const std::string &toMatch);

        bool peek(const std::string &toMatch);

        void functionHeader(const std::string &func_name) const;

        bool peekExpression();

        bool parse();

        void nextToken();

        void goIn();

        void getOut();

        void PROGRAM_START();

        void START_PARSE();

        void FUNC_HEADER();

        void RETURN_TYPE();

        void IDENTIFIER();

        void PARAMETERS();

        void STATEMENT();

        void PROG_S();


        void EXPRESSION();

        void MUL_DIV();

        void ADD_SUB();

        void MUL_DIV_();

        void FINAL();

        void ALPHABET();

        void ALPHANUMERIC();

        void ADDITIONAL_PARAMETERS();

        void DATATYPE();

        void INT_DECLARATION();

        void ADD_INT_DEC();

        void CHAR_DECLARATION();

        void ADD_CHAR_DEC();

        void ASSIGNMENT();

        void LOOP();

        void COMPARISON();

        void IF();

        void PRINTS();

        void INPUT();

        void CHAR_DEC_ASS();

        void INT_DEC_ASS();

        void TO_ASSIGN();

        void NUMBER();

        void LIT_CONST();

        void TO_PRINT();

        void STRING();

        void CONDITIONAL();

        void RELATIONAL_OP();

        void ADDITIONAL_COMP();

        void ELIF();

        void ELSE();

        void FUNCTION_CALL();

        void ARGUMENTS();

        void MORE_ARGS();

    };

}

#endif //MAIN_CPP_PARSER_H
