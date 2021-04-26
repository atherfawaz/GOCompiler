//
// Created by ather on 21-Apr-21.
//

#include "Lexer.h"

namespace Lexer {

    Lexer::Lexer() = default;

    Lexer::~Lexer() {
        keywords.clear();
        datatypes.clear();
    }

    Lexer::Lexer(std::string &code) {

        currentPtr = code.begin();

        // mapping of keywords and datatype key and value pair
        // key is in small for access and values are in CAPS because they are tokens
        keywords["if"] = "IF";
        keywords["elif"] = "ELIF";
        keywords["else"] = "ELSE";
        keywords["while"] = "WHILE";
        keywords["in"] = "IN";
        keywords["print"] = "PRINT";
        keywords["println"] = "PRINTLN";
        keywords["integer"] = "INTEGER";
        keywords["char"] = "CHAR";

        datatypes["Integer"] = "INTEGER";
        datatypes["Char"] = "CHAR";
    }

    void Lexer::next() {
        currentPtr++;
    }

    char Lexer::peakNext() {
        // go to next pointer, get value and return to original pointer position
        this->next();
        char next = this->getCurrent();
        this->prev();

        // if the truthy value of char is true then return it otherwise return end
        if (next) return next;
        return '\0';
    }

    char Lexer::getNext() {
        this->next();
        char next = this->getCurrent();
        if (next) return next;
        return '\0';
    }

    void Lexer::prev() {
        currentPtr--;
    }

    char Lexer::getCurrent() {
        return *currentPtr;
    }

    std::vector<Token> Lexer::generateTokens() {
        std::vector<Token> toks;
        while (this->peakNext()) {
            toks.push_back(findToken(this->getCurrent()));
            this->next();
        }
        return toks;
    }

    // utility function to use character as string
    // used in returning single length token as string
    std::string charToString(char x) {
        return std::string(1, x);
    }


    Token Lexer::findToken(char currTok) {
        
        // Ignoring all the whitespaces
        while (currTok == ' ') {
            currTok = this->getNext();
        }
        // checking for a comment enclosed in /* ... */ we will ignore all of this
        if (currTok == '/') {

            if (this->peakNext() == '*') {

                //comment found
                this->next();
                bool end = false;
                while (!end) {
                    while (this->getNext() != '*') {}

                    // we need / right after * like */ to close our comment
                    if (this->peakNext() == '/') {
                        //end of comment
                        this->next();   // now current pointer is pointing towards / char
                        end = true;
                        currTok = this->getNext();  // and now finally it is pointing towards the next character and that char is stored as currTok
                    }
                }
            }
        }
        switch (currTok) {
            case '(':
                return Token(PRNT, charToString(currTok));

            case ')':
                return Token(PRNT, charToString(currTok));

            case '{':
                return Token(BRACES, charToString(currTok));

            case '}':
                return Token(BRACES, charToString(currTok));

            case '[':
                return Token(SQR_BRKT, charToString(currTok));

            case ']':
                return Token(SQR_BRKT, charToString(currTok));

            case '+':
                return Token(AR_OP, charToString(currTok));

            case '-':
                return Token(AR_OP, charToString(currTok));

            case '*':
                return Token(AR_OP, charToString(currTok));

            case '%':
                return Token(AR_OP, charToString(currTok));

            case ';':
                return Token(SEMICOLON, charToString(currTok));

            case ',':
                return Token(COMMA, charToString(currTok));

            case '/':
                return Token(AR_OP, charToString(currTok));

            case '<':
                return Token(RO_OP, charToString(currTok));

            // a lit const is simple character enclosed in single quotes e.g 'a'
            case '\'': {
                std::string litConst;
                litConst += '\'';
                litConst += this->getNext();
                if (this->getNext() == '\'') {
                    litConst += this->getCurrent();
                    return Token(LIT_CONST, litConst);
                } else {
                    std::cout << "Syntax error!";
                    return Token();
                }
            }

            case '=': {
                std::string op;
                op += '=';
                if (this->getNext() == '=') {
                    op += this->getCurrent();
                    return Token(RO_OP, op);
                } else {
                    std::cout << "Syntax error!";
                    return Token();
                }
            }

            case '>':
                if (this->peakNext() == '>') {
                    this->next();
                    return Token(INPUT_OP, ">>");
                }

                return Token(RO_OP, charToString(currTok));

            case ':':

                if (this->peakNext() == '=') {
                    this->next();
                    return Token(ASS_OP, ":=");
                }
                return Token(VAR_DEC, charToString(currTok));

            case '"': {
                std::string str;
                str += '"';
                str += this->getNext();
                // possible error if quots don't close at all
                while (this->getCurrent() != '"') {
                    str += this->getNext();
                }

                return Token(STRING, str);
            }

            default:
                // checking for Identifier starts with alpha input and then it can have either alpha or numeric input
                if (isalpha(currTok)) {
                    std::string word;
                    word += currTok;
                    while (isalnum(this->peakNext())) {
                        word += this->getNext();
                    }
                    // checking to see if the identifier exists in Keyword or Datatype map
                    if (isKeyword(word))
                        return Token(KEYWORD, word);
                    else if (isDataType(word))
                        return Token(DATATYPE, word);
                    else
                        return Token(IDENTIFIER, word);


                }
                // checking for number input which is kind of similar to Integer input
                // should we check for negative sign
                else if (isdigit(currTok)) {
                    std::string number;
                    number += currTok;
                    while (isdigit(this->peakNext() )) {
                        number += this->getNext();
                    }
                    return Token(NUMBER, number);
                }
                // if nothing matches return default
                currTok = this->getCurrent();
                std::cout << "Returning default token for: " << currTok << std::endl;
                return Token();
        }
    }
    // map Identifier to Keyword
    bool Lexer::isKeyword(const std::string &word) {
        if (keywords.find(word) == keywords.end()) return false;
        return true;
    }
    // map Identifier to Datatype
    bool Lexer::isDataType(const std::string &word) {
        if (datatypes.find(word) == datatypes.end()) return false;
        return true;
    }
}