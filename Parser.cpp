//
// Created by ather on 18-May-21.
//

#include "Parser.h"
#include "Lexer.h"

#define CURRENTTOKEN tokens[cursor].getLexeme()

Parser::Parser::Parser(const std::vector<Lexer::Token> &tok) {
    this->cursor = 0;
    this->tokens = tok;
}

bool Parser::Parser::parse() {
    std::cout << "Current Token: " << CURRENTTOKEN << "\n";
    if (tokens[cursor].non_empty()) {
        START_PARSE();
        return true;
    }
    return false;
}


void Parser::Parser::nextToken() {
    cursor++;
    std::cout << "Current Token: " << CURRENTTOKEN << "\n";
}

bool Parser::Parser::match(const std::string &lexeme, const std::string &toMatch) {
    if (lexeme == toMatch) return true;
    return false;
}

void Parser::Parser::START_PARSE() {
    PROGRAM_START();
}

void Parser::Parser::PROGRAM_START() {
    if (match(CURRENTTOKEN, "func")) {
        FUNC_HEADER();
        PROG_S();
    }
}

void Parser::Parser::FUNC_HEADER() {
    if (match(CURRENTTOKEN, "func")) {
        nextToken();
        RETURN_TYPE();
        nextToken();
        if (match(CURRENTTOKEN, ":")) {
            nextToken();
            IDENTIFIER();
            nextToken();
            if (match(CURRENTTOKEN, "(")) {
                nextToken();
                PARAMETERS();
                //nextToken();
                if (match(CURRENTTOKEN, ")")) {
                    nextToken();
                    if (match(CURRENTTOKEN, "{")) {
                        nextToken();
                        STATEMENT();
                        nextToken();
                        if (match(CURRENTTOKEN, "}")) {
                            nextToken();
                            FUNC_HEADER();
                            nextToken();
                            STATEMENT();
                        } else {
                            std::cerr << "Expected }, but found " << CURRENTTOKEN << " instead." << std::endl;
                            exit(1);
                        }
                    } else {
                        std::cerr << "Expected {, but found " << CURRENTTOKEN << " instead." << std::endl;
                        exit(1);
                    }
                } else {
                    std::cerr << "Expected ), but found " << CURRENTTOKEN << " instead." << std::endl;
                    exit(1);
                }
            } else {
                std::cerr << "Expected (, but found " << CURRENTTOKEN << " instead." << std::endl;
                exit(1);
            }
        } else {
            std::cerr << "Expected :, but found " << CURRENTTOKEN << " instead." << std::endl;
            exit(1);
        }
        IDENTIFIER();
    }
}

void Parser::Parser::PROG_S() {
    if (match(CURRENTTOKEN, "func")) {
        FUNC_HEADER();
    } else {
        STATEMENT();
    }
}

void Parser::Parser::RETURN_TYPE() {
    if (match(CURRENTTOKEN, "integer") || match(CURRENTTOKEN, "char") || match(CURRENTTOKEN, "void")) return;
    else {
        std::cerr << "Expected INTEGER, CHAR, or VOID but found " << CURRENTTOKEN << " instead." << std::endl;
        exit(1);
    }
}

void Parser::Parser::IDENTIFIER() {
    if (isalpha(CURRENTTOKEN[0])) {
        ALPHABET();
        ALPHANUMERIC();
    }
}

void Parser::Parser::ALPHABET() {
    if (isalpha(CURRENTTOKEN[0])) return;
    else {
        std::cerr << "Expected IDENTIFIER, but found " << CURRENTTOKEN << " instead." << std::endl;
        exit(1);
    }
}

void Parser::Parser::ALPHANUMERIC() {
    std::string str = CURRENTTOKEN;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalnum(str[i])) {
            std::cerr << "Expected IDENTIFIER, but found " << CURRENTTOKEN << " instead." << std::endl;
            exit(1);
        }
    }
}

void Parser::Parser::PARAMETERS() {
    DATATYPE();
    nextToken();
    if (match(CURRENTTOKEN, ":")) {
        nextToken();
        IDENTIFIER();
        nextToken();
        ADDITIONAL_PARAMETERS();
    }
}

void Parser::Parser::STATEMENT() {
    if (match(CURRENTTOKEN, "integer")) {
        INT_DECLARATION();
    } else if (match(CURRENTTOKEN, "char")) {
        CHAR_DECLARATION();
    } else if (match(CURRENTTOKEN, "while")) {
        LOOP();
    } else if (match(CURRENTTOKEN, "if")) {
        IF();
    } else if (match(CURRENTTOKEN, "print") || match(CURRENTTOKEN, "println")) {
        PRINTS();
    }
}

void Parser::Parser::ADDITIONAL_PARAMETERS() {
    if (match(CURRENTTOKEN, ",")) {
        nextToken();
        PARAMETERS();
    }
}

void Parser::Parser::DATATYPE() {
    if (match(CURRENTTOKEN, "integer") || match(CURRENTTOKEN, "char")) { ;
    } else {
        std::cerr << "Expected INTEGER or CHAR, but found " << CURRENTTOKEN << " instead." << std::endl;
        exit(1);
    }
}

void Parser::Parser::INT_DECLARATION() {
    if (match(CURRENTTOKEN, "integer")) {
        nextToken();
        if (match(CURRENTTOKEN, ":")) {
            nextToken();
            IDENTIFIER();
            nextToken();
            ADD_INT_DEC();
            if (match(CURRENTTOKEN, ";")) {
                nextToken();
                STATEMENT();
            } else {
                std::cerr << "Expected ;, but found " << CURRENTTOKEN << " instead." << std::endl;
                exit(1);
            }
        } else {
            std::cerr << "Expected :, but found " << CURRENTTOKEN << " instead." << std::endl;
            exit(1);
        }
    } else {
        std::cerr << "Expected INTEGER, but found " << CURRENTTOKEN << " instead." << std::endl;
        exit(1);
    }
}

void Parser::Parser::ADD_INT_DEC() {
    if (match(CURRENTTOKEN, ",")) {
        nextToken();
        IDENTIFIER();
        nextToken();
        ADD_INT_DEC();
    }
}

void Parser::Parser::CHAR_DECLARATION() {
    if (match(CURRENTTOKEN, "char")) {
        nextToken();
        if (match(CURRENTTOKEN, ":")) {
            nextToken();
            IDENTIFIER();
            nextToken();
            ADD_CHAR_DEC();
            if (match(CURRENTTOKEN, ";")) {
                nextToken();
                STATEMENT();
            } else {
                std::cerr << "Expected ;, but found " << CURRENTTOKEN << " instead." << std::endl;
                exit(1);
            }
        } else {
            std::cerr << "Expected :, but found " << CURRENTTOKEN << " instead." << std::endl;
            exit(1);
        }
    } else {
        std::cerr << "Expected CHAR, but found " << CURRENTTOKEN << " instead." << std::endl;
        exit(1);
    }
}

void Parser::Parser::ADD_CHAR_DEC() {
    if (match(CURRENTTOKEN, ",")) {
        nextToken();
        IDENTIFIER();
        nextToken();
        ADD_CHAR_DEC();
    }
}

void Parser::Parser::ASSIGNMENT() {
    IDENTIFIER();
    nextToken();
    if (match(CURRENTTOKEN, ":=")) {
        TO_ASSIGN();
        nextToken();
        if (match(CURRENTTOKEN, ";")) {
            //add code here
        }
    } else {
        std::cerr << "Expected :=, but found " << CURRENTTOKEN << " instead." << std::endl;
        exit(1);
    }
}

void Parser::Parser::LOOP() {
    if (match(CURRENTTOKEN, "while")) {
        nextToken();
        COMPARISON();
        if (match(CURRENTTOKEN, ":")) {
            nextToken();
            if (match(CURRENTTOKEN, "{")) {
                nextToken();
                STATEMENT();
                if (match(CURRENTTOKEN, "}")) {
                    nextToken();
                    STATEMENT();
                } else {
                    std::cerr << "Expected }, but found " << CURRENTTOKEN << " instead." << std::endl;
                    exit(1);
                }
            } else {
                std::cerr << "Expected {, but found " << CURRENTTOKEN << " instead." << std::endl;
                exit(1);
            }
        } else {
            std::cerr << "Expected :, but found " << CURRENTTOKEN << " instead." << std::endl;
            exit(1);
        }
    } else {
        std::cout << "Ye tou garbar hai";
    }
}

void Parser::Parser::COMPARISON() {

}

void Parser::Parser::IF() {

}

void Parser::Parser::PRINTS() {

}

void Parser::Parser::INPUT() {

}

void Parser::Parser::CHAR_DEC_ASS() {

}

void Parser::Parser::INT_DEC_ASS() {

}

void Parser::Parser::TO_ASSIGN() {
    if (CURRENTTOKEN[0] == '\'') {
        LIT_CONST();
    } else if (CURRENTTOKEN[0] >= '0' && CURRENTTOKEN[0] <= '9') {
        NUMBER();
    }
}

void Parser::Parser::LIT_CONST() {
    if (CURRENTTOKEN.size() != 3) {
        std::cerr << "Illegal literal constant.";
        exit(1);
    }
    if (CURRENTTOKEN[0] == '\'' && CURRENTTOKEN[2] == '\'') {
        return;
    } else {
        std::cerr << "Expected ', but found " << CURRENTTOKEN << " instead." << std::endl;
        exit(1);
    }
}

void Parser::Parser::NUMBER() {
    for (int i = 0; CURRENTTOKEN[i] != '\0'; i++) {
        if (!isdigit(CURRENTTOKEN[i])) {
            std::cerr << "Illegal number.";
            exit(1);
        }
    }
}
