//
// Created by Mujtaba on 4/23/2021.
//

#ifndef TEST_GLOBALS_H
#define TEST_GLOBALS_H
#include <map>

// global variables used to converted enum output to it's string value
std::map<int , std::string> token_mapping;
std::string tokens_list[] = { "AR_OP", "RO_OP", "IDENTIFIER", "NUMBER", "LIT_CONST", "STRING" ,"VAR_DEC", "ASS_OP", "INPUT_OP", "PRNT", "SQR_BRKT", "BRACES" ,"SEMICOLON", "COMMA", "KEYWORD","DATATYPE","NONE"};





#endif //TEST_GLOBALS_H
