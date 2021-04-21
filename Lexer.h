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

    class Lexer {
    private:
        std::string::iterator currentPtr;
        std::unordered_map<std::string, std::string> keywords;
    public:
        Lexer();

        explicit Lexer(std::string &code);

        void next();

        char getNext();

        void prev();

        char getCurrent();

        std::vector<Token> generateTokens();

        Token findToken(char currTok);

        ~Lexer();
    };

}


#endif //GO_COMPILER_LEXER_H
