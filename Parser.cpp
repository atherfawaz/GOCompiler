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
    //why isn't the deletion in the main function of empty tokens working ffs
    while (CURRENTTOKEN == "0" && cursor < tokens.size()) {
        cursor++;
    }
    if (cursor >= tokens.size()) {
        std::cout << "Finished parsing.";
        exit(0);
    }
    std::cout << "Current Token: " << CURRENTTOKEN << "\n";
}

bool Parser::Parser::match(const std::string &lexeme, const std::string &toMatch) {
    if (lexeme == toMatch) return true;
    return false;
}

void Parser::Parser::START_PARSE() {
    std::cout << __func__ << std::endl;

    PROGRAM_START();
}

void Parser::Parser::PROGRAM_START() {
    std::cout << __func__ << std::endl;

    if (match(CURRENTTOKEN, "func")) {
        FUNC_HEADER();
        PROG_S();
    }
}

void Parser::Parser::FUNC_HEADER() {
    std::cout << __func__ << std::endl;

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
    std::cout << __func__ << std::endl;

    if (match(CURRENTTOKEN, "func")) {
        FUNC_HEADER();
    } else {
        STATEMENT();
    }
}

void Parser::Parser::RETURN_TYPE() {
    std::cout << __func__ << std::endl;

    if (match(CURRENTTOKEN, "integer") || match(CURRENTTOKEN, "char") || match(CURRENTTOKEN, "void")) return;
    else {
        std::cerr << "Expected INTEGER, CHAR, or VOID but found " << CURRENTTOKEN << " instead." << std::endl;
        exit(1);
    }
}

void Parser::Parser::IDENTIFIER() {
    std::cout << __func__ << std::endl;

    if (isalpha(CURRENTTOKEN[0])) {
        ALPHABET();
        ALPHANUMERIC();
    }
}

void Parser::Parser::ALPHABET() {
    std::cout << __func__ << std::endl;

    if (isalpha(CURRENTTOKEN[0])) return;
    else {
        std::cerr << "Expected IDENTIFIER, but found " << CURRENTTOKEN << " instead." << std::endl;
        exit(1);
    }
}

void Parser::Parser::ALPHANUMERIC() {
    std::cout << __func__ << std::endl;

    std::string str = CURRENTTOKEN;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalnum(str[i])) {
            std::cerr << "Expected IDENTIFIER, but found " << CURRENTTOKEN << " instead." << std::endl;
            exit(1);
        }
    }
}

void Parser::Parser::PARAMETERS() {
    std::cout << __func__ << std::endl;

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
    std::cout << __func__ << std::endl;
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
    } else if (match(CURRENTTOKEN, "in")) {
        INPUT();
    } else if (isalpha(CURRENTTOKEN[0])) {
        IDENTIFIER();
        nextToken();
        if (match(CURRENTTOKEN, "<") || match(CURRENTTOKEN, "<=") || match(CURRENTTOKEN, ">") ||
            match(CURRENTTOKEN, ">=") || match(CURRENTTOKEN, "=") || match(CURRENTTOKEN, "/=")) {
            COMPARISON();
        } else if (match(CURRENTTOKEN, ":=")) {
            ASSIGNMENT();
        } else {
            std::cerr << "Terrible terrible mistakes" << std::endl;
            exit(1);
        }
    }
}

void Parser::Parser::ADDITIONAL_PARAMETERS() {
    std::cout << __func__ << std::endl;

    if (match(CURRENTTOKEN, ",")) {
        nextToken();
        PARAMETERS();
    }
}

void Parser::Parser::DATATYPE() {
    std::cout << __func__ << std::endl;

    if (match(CURRENTTOKEN, "integer") || match(CURRENTTOKEN, "char")) { ;
    } else {
        std::cerr << "Expected INTEGER or CHAR, but found " << CURRENTTOKEN << " instead." << std::endl;
        exit(1);
    }
}

void Parser::Parser::INT_DECLARATION() {
    std::cout << __func__ << std::endl;

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
    std::cout << __func__ << std::endl;

    if (match(CURRENTTOKEN, ",")) {
        nextToken();
        IDENTIFIER();
        nextToken();
        ADD_INT_DEC();
    }
}

void Parser::Parser::CHAR_DECLARATION() {
    std::cout << __func__ << std::endl;

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
    std::cout << __func__ << std::endl;

    if (match(CURRENTTOKEN, ",")) {
        nextToken();
        IDENTIFIER();
        nextToken();
        ADD_CHAR_DEC();
    }
}

void Parser::Parser::ASSIGNMENT() {
    std::cout << __func__ << std::endl;

    if (match(CURRENTTOKEN, ":=")) {
        nextToken();
        TO_ASSIGN();
        nextToken();
        if (match(CURRENTTOKEN, ";")) {
            nextToken();
            STATEMENT();
        }
    } else {
        std::cerr << "Expected :=, but found " << CURRENTTOKEN << " instead." << std::endl;
        exit(1);
    }
}

void Parser::Parser::LOOP() {
    std::cout << __func__ << std::endl;

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
    std::cout << __func__ << std::endl;

}

void Parser::Parser::IF() {
    std::cout << __func__ << std::endl;

}

void Parser::Parser::PRINTS() {
    std::cout << __func__ << std::endl;

    if (match(CURRENTTOKEN, "println") || match(CURRENTTOKEN, "print")) {
        nextToken();
        if (match(CURRENTTOKEN, "(")) {
            nextToken();
            TO_PRINT();
            nextToken();
            if (match(CURRENTTOKEN, ")")) {
                nextToken();
                if (match(CURRENTTOKEN, ";")) {
                    nextToken();
                    STATEMENT();
                } else {
                    std::cerr << "Expected ;, but found " << CURRENTTOKEN << " instead." << std::endl;
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
    }
}

void Parser::Parser::INPUT() {
    std::cout << __func__ << std::endl;

}

void Parser::Parser::CHAR_DEC_ASS() {
    std::cout << __func__ << std::endl;

}

void Parser::Parser::INT_DEC_ASS() {
    std::cout << __func__ << std::endl;

}

void Parser::Parser::TO_ASSIGN() {
    std::cout << __func__ << std::endl;

    if (CURRENTTOKEN[0] == '\'') {
        LIT_CONST();
    } else if (CURRENTTOKEN[0] >= '0' && CURRENTTOKEN[0] <= '9') {
        NUMBER();
    } else if (isalpha(CURRENTTOKEN[0])) {
        IDENTIFIER();
    } else {
        std::cerr << "Expected an assignment of some sort, but found " << CURRENTTOKEN << " instead." << std::endl;
        exit(1);
    }
}

void Parser::Parser::LIT_CONST() {
    std::cout << __func__ << std::endl;

    if (CURRENTTOKEN.size() != 3) {
        std::cerr << "Illegal literal constant.";
        exit(1);
    }
    if (CURRENTTOKEN[0] == '\'' && CURRENTTOKEN[2] == '\'') { ;
    } else {
        std::cerr << "Expected ', but found " << CURRENTTOKEN << " instead." << std::endl;
        exit(1);
    }
}

void Parser::Parser::NUMBER() {
    std::cout << __func__ << std::endl;

    for (int i = 0; CURRENTTOKEN[i] != '\0'; i++) {
        if (!isdigit(CURRENTTOKEN[i])) {
            std::cerr << "Illegal number.";
            exit(1);
        }
    }
}

void Parser::Parser::TO_PRINT() {
    std::cout << __func__ << std::endl;

    if (CURRENTTOKEN[0] == '\'') {
        LIT_CONST();
    } else if (CURRENTTOKEN[0] == '\"') {
        STRING();
    } else if (CURRENTTOKEN[0] >= '0' && CURRENTTOKEN[0] <= '9') {
        NUMBER();
    } else if (isalpha(CURRENTTOKEN[0])) {
        IDENTIFIER();
    } else {
        std::cerr << "Illegal print statement.";
        exit(1);
    }
}

void Parser::Parser::STRING() {
    std::cout << __func__ << std::endl;

    if (CURRENTTOKEN[0] == '\"' && CURRENTTOKEN.back() == '\"') { ;
    } else {
        std::cerr << "Illegal print string.";
        exit(1);
    }
}
