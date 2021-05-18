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
        keywords["func"] = "FUNC";

        datatypes["Integer"] = "INTEGER";
        datatypes["Char"] = "CHAR";
        row_num = 0;
        col_num = 0;
    }

    void Lexer::next() {
        currentPtr++;
        col_num++;
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
        col_num--;
    }

    char Lexer::getCurrent() {
        return *currentPtr;
    }

    std::vector<Token> Lexer::generateTokens() {
        std::vector<Token> toks;
        while (this->peakNext()) {
            try {
                toks.push_back(findToken(this->getCurrent()));
            }
            catch (const char *msg) {
                std::cerr << "Exiting code due to follwing error";
                std::cerr << msg;
                exit(-1);
            }
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
                    while (this->getNext() != '*') {
                        if (this->getCurrent() == '\n' || this->getCurrent() == '\r') {
                            inc_row();
                        } else if (this->getCurrent() == '\t') {
                            col_num += 4;
                        }
                    }

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
                return Token(PRNT, charToString(currTok), row_num, col_num);

            case ')':
                return Token(PRNT, charToString(currTok), row_num, col_num);

            case '{':
                return Token(BRACES, charToString(currTok), row_num, col_num);

            case '}':
                return Token(BRACES, charToString(currTok), row_num, col_num);

            case '[':
                return Token(SQR_BRKT, charToString(currTok), row_num, col_num);

            case ']':
                return Token(SQR_BRKT, charToString(currTok), row_num, col_num);

            case '+':
                return Token(AR_OP, charToString(currTok), row_num, col_num);

            case '-':
                return Token(AR_OP, charToString(currTok), row_num, col_num);

            case '*':
                return Token(AR_OP, charToString(currTok), row_num, col_num);

            case '%':
                return Token(AR_OP, charToString(currTok), row_num, col_num);

            case ';':
                return Token(SEMICOLON, charToString(currTok), row_num, col_num);

            case ',':
                return Token(COMMA, charToString(currTok), row_num, col_num);

            case '/':
                return Token(AR_OP, charToString(currTok), row_num, col_num);

            case '<':
                return Token(RO_OP, charToString(currTok), row_num, col_num);

                // a lit const is simple character enclosed in single quotes e.g 'a'
            case '\'': {
                std::string litConst;
                litConst += '\'';
                litConst += this->getNext();
                if (this->getNext() == '\'') {
                    litConst += this->getCurrent();
                    return Token(LIT_CONST, litConst, row_num, col_num);
                } else {
                    throw "Syntax error!";
                    return Token();
                }
            }

            case '=': {
                std::string op;
                op += '=';
                if (this->getNext() == '=') {
                    op += this->getCurrent();
                    return Token(RO_OP, op, row_num, col_num);
                } else {
                    throw "Syntax error!";
                    return Token();
                }
            }

            case '>':
                if (this->peakNext() == '>') {
                    this->next();
                    return Token(INPUT_OP, ">>", row_num, col_num);
                }

                return Token(RO_OP, charToString(currTok), row_num, col_num);

            case ':':

                if (this->peakNext() == '=') {
                    this->next();
                    return Token(ASS_OP, ":=", row_num, col_num);
                }
                return Token(VAR_DEC, charToString(currTok), row_num, col_num);

            case '"': {
                std::string str;
                str += '"';
                str += this->getNext();
                // possible error if quots don't close at all
                while (this->getCurrent() != '"') {
                    str += this->getNext();
                    if (this->getCurrent() == '\n' || this->getCurrent() == '\r') {
                        inc_row();
                    } else if (this->getCurrent() == '\t') {
                        col_num += 4;
                    }
                }

                return Token(STRING, str, row_num, col_num);
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
                    std::string out = isKeyword(word);
                    if (!out.empty())
                        return Token(KEYWORD, word, row_num, col_num);
                    out = isDataType(word);
                    if (!out.empty())
                        return Token(DATATYPE, word, row_num, col_num);
                    else
                        return Token(IDENTIFIER, word, row_num, col_num);
                }
                    //ing fo  r number input which is kind of similar to Integer input
                    // should we check for negative sign
                else if (isdigit(currTok)) {
                    std::string number;
                    number += currTok;
                    while (isdigit(this->peakNext())) {
                        number += this->getNext();
                    }
                    return Token(NUMBER, number, row_num, col_num);
                }
                // if nothing matches return default
                currTok = this->getCurrent();
                if (currTok == '\n' || currTok == '\r') {
                    inc_row();
                } else if (currTok == '\t') {
                    col_num += 4;
                } else {
                    throw "invalid token " + charToString(currTok);
                }

                return Token();
        }
    }

    // map Identifier to Keyword
    std::string Lexer::isKeyword(const std::string &word) {
        if (keywords.find(word) == keywords.end()) return "";
        return keywords[word];
    }

    // map Identifier to Datatype
    std::string Lexer::isDataType(const std::string &word) {
        if (datatypes.find(word) == datatypes.end()) return "";
        return datatypes[word];
    }
}