//
// Created by ather on 21-Apr-21.
//

#ifndef GO_COMPILER_LEXER_H
#define GO_COMPILER_LEXER_H

#include <string>
#include <unordered_map>
#include <vector>
#include "Token.h"

namespace Lexer {

    // This class implements the main logic of an lexer
    // It store current position in input code and keywords + datatype dictionary mapping
    // for the main logic it iterates over the whole code and uses case statements to implements a DFA which reads characters and output
    // respective tokens based on character combinations defined
    class Lexer {
    private:
        std::string::iterator currentPtr;
        std::unordered_map<std::string, std::string> keywords;
        std::unordered_map<std::string, std::string> datatypes;
    public:
        int row_num;
        int col_num;
        Lexer();

        // initializes start pointer and keyword + datatype dictionaries
        explicit Lexer(std::string &code);

        // moves to next pointer
        void next();

        // get the next token
        char getNext();

        // peak at the next character without moving the pointer forward
        char peakNext();

        // moves to previous pointer
        void prev();

        // dereferences the pointer to get the current character
        char getCurrent();

        // iterate over all characters using findToken function
        // to generate and return all possible tokens
        std::vector<Token> generateTokens();

        // This is the main function that implements the DFA given in documentation
        // it uses cases statements and isalpha + isalphanumeric to map lexemes to their respective tokens
        Token findToken(char currTok);

        // Checks if Identifier from findToken maps to some predefined keyword
        bool isKeyword(const std::string &word);

        // Checks if Identifier from findToken maps to some predefined Datatype
        std::string isDataType(const std::string &word);

        void inc_row(){
            row_num+=1;
            col_num = 0;
        }
        ~Lexer();
    };

}


#endif //GO_COMPILER_LEXER_H
