//
// Created by ather on 18-May-21.
//

#ifndef MAIN_CPP_PARSER_H
#define MAIN_CPP_PARSER_H

#include "Token.h"
#include <utility>
#include <vector>
#include <map>
#include <fstream>
#include <tuple>
#include <windows.h>
#include <queue>
#include <stack>

namespace Parser {

    class Parser {

    private:
        int cursor = 0;
        int tabs = 0;
        int exprTemp = 0;
        bool isRight = false;
        int lineNum = 1;
        int offset = 0;
        std::string threeAddCode;
        std::vector<Lexer::Token> tokens;
        std::ofstream parsingTree;
        std::ofstream symbolTable;
        std::ofstream tac;
        std::map<std::string, std::string> parserSymbolTable;
        std::stack<std::string> stack;
        std::map<std::string, int> operatorPrecedence;
        std::string postfix;
        std::stack<std::string> evalStack;
        std::vector<std::string> expressionArray;

    public:
        Parser();

        explicit Parser(const std::vector<Lexer::Token> &tok, const std::string &tree, const std::string &table,
                        const std::string &tac);

        bool match(const std::string &func_name, const std::string &lexeme, const std::string &toMatch);

        void maintainStack(const std::string &op);

        void evaluatePostfix(const std::string &expr, const std::string &toAssign);

        void cleanStack();

        void storeExpression();

        static bool define_match(const std::string &lexeme, const std::string &toMatch);

        void functionHeader(const std::string &func_name, const std::string &cur_tok);

        void save();

        bool peekExpression();

        void writeTAC(const std::string &new_statement);

        void fillInTheHole(int pos);

        void emit(const std::string &to_print);

        //COORD getpos();
        //void setpos(COORD coords);
        bool parse();

        void nextToken();

        void getIn();

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

        void TO_ASSIGN();

        void NUMBER();

        void LIT_CONST();

        void TO_PRINT();

        void STRING();

        void CONDITIONAL();

        void RELATIONAL_OP();

        void ADDITIONAL_COMP();

        void ELIF(std::queue<int> &outer_queue);

        void ELSE();

        void FUNCTION_CALL();

        void ARGUMENTS();

        void MORE_ARGS();

        void RETURN_VALUE();

    };

}

#endif //MAIN_CPP_PARSER_H
