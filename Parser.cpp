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
void Parser::Parser::print_func_header(std::string func_name){
    for (int i = 0; i < this->tabs; i++)
    std::cout << "   ";
    std::cout << func_name << std::endl;

}
void Parser::Parser::goIn() {
    this->tabs++;
}
void Parser::Parser::getOut() {
    this->tabs--;
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
//    while (CURRENTTOKEN == "0" && cursor < tokens.size()) {
//        cursor++;
//    }
    if (cursor >= tokens.size()) {
        std::cout << "Finished parsing.";
        exit(0);
    }
    //std::cout << "Current Token: " << CURRENTTOKEN << "\n";
}

bool Parser::Parser::match(const std::string &lexeme, const std::string &toMatch) {
    if (lexeme == toMatch) return true;
    return false;
}

void Parser::Parser::START_PARSE() {
    print_func_header(__func__ );


    PROGRAM_START();

}

void Parser::Parser::PROGRAM_START() {

    print_func_header(__func__ );

    if (match(CURRENTTOKEN, "func")) {

        goIn();
        FUNC_HEADER();
        getOut();

        PROG_S();

    } else {
        goIn();
        STATEMENT();
        getOut();
    }

}

void Parser::Parser::FUNC_HEADER() {

    print_func_header(__func__ );
    goIn();
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
    getOut();
}

void Parser::Parser::PROG_S() {

    print_func_header(__func__ );

    if (match(CURRENTTOKEN, "func")) {
        goIn();
        FUNC_HEADER();
        getOut();
    } else {
        goIn();
        STATEMENT();
        getOut();
    }

}

void Parser::Parser::RETURN_TYPE() {

    print_func_header(__func__ );

    if (match(CURRENTTOKEN, "integer") || match(CURRENTTOKEN, "char") || match(CURRENTTOKEN, "void")) return;
    else {
        std::cerr << "Expected INTEGER, CHAR, or VOID but found " << CURRENTTOKEN << " instead." << std::endl;
        exit(1);
    }

}

void Parser::Parser::IDENTIFIER() {

    print_func_header(__func__ );

    goIn();
    if (isalpha(CURRENTTOKEN[0])) {

        ALPHABET();
        ALPHANUMERIC();
    }
    getOut();

}

void Parser::Parser::ALPHABET() {

    print_func_header(__func__ );

    if (isalpha(CURRENTTOKEN[0])) return;
    else {
        std::cerr << "Expected IDENTIFIER, but found " << CURRENTTOKEN << " instead." << std::endl;
        exit(1);
    }

}

void Parser::Parser::ALPHANUMERIC() {

    print_func_header(__func__ );

    std::string str = CURRENTTOKEN;
    for (int i = 1; str[i] != '\0'; i++) {
        if (!isalnum(str[i])) {
            std::cerr << "Expected IDENTIFIER, but found " << CURRENTTOKEN << " instead." << std::endl;
            exit(1);
        }
    }

}

void Parser::Parser::PARAMETERS() {

    print_func_header(__func__ );
    goIn();
    DATATYPE();
    nextToken();
    if (match(CURRENTTOKEN, ":")) {
        nextToken();
        IDENTIFIER();
        nextToken();
        getOut();
        ADDITIONAL_PARAMETERS();
    }

}

void Parser::Parser::STATEMENT() {

    print_func_header(__func__ );
    goIn();
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
            // the error was coming because i of In operator in code.go was capital hence the code would go into
            // identifier checker which would fail due to << signs
            std::cerr << "Terrible terrible mistakes" << std::endl;
            exit(1);
        }
    }
    getOut();
}

void Parser::Parser::ADDITIONAL_PARAMETERS() {

    print_func_header(__func__ );

    if (match(CURRENTTOKEN, ",")) {
        nextToken();
        PARAMETERS();
    }

}

void Parser::Parser::DATATYPE() {

    print_func_header(__func__ );

    if (match(CURRENTTOKEN, "integer") || match(CURRENTTOKEN, "char")) { ;
    } else {
        std::cerr << "Expected INTEGER or CHAR, but found " << CURRENTTOKEN << " instead." << std::endl;
        exit(1);
    }

}

void Parser::Parser::INT_DECLARATION() {

    print_func_header(__func__ );
    goIn();
    if (match(CURRENTTOKEN, "integer")) {
        nextToken();
        if (match(CURRENTTOKEN, ":")) {
            nextToken();
            IDENTIFIER();
            nextToken();
            getOut();
            ADD_INT_DEC();
            if (match(CURRENTTOKEN, ";")) {
                getOut();
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
    getOut();
}

void Parser::Parser::ADD_INT_DEC() {

    print_func_header(__func__ );
    goIn();
    if (match(CURRENTTOKEN, ",")) {
        nextToken();
        IDENTIFIER();
        nextToken();
        //getOut();
        ADD_INT_DEC();
    }
    getOut();
}

void Parser::Parser::CHAR_DECLARATION() {

    print_func_header(__func__ );

    goIn();
    if (match(CURRENTTOKEN, "char")) {
        nextToken();
        if (match(CURRENTTOKEN, ":")) {
            nextToken();
            IDENTIFIER();
            nextToken();
            getOut();
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
    getOut();
}

void Parser::Parser::ADD_CHAR_DEC() {

    print_func_header(__func__ );
    goIn();
    if (match(CURRENTTOKEN, ",")) {
        nextToken();
        IDENTIFIER();
        nextToken();
        getOut();
        ADD_CHAR_DEC();

    }
    getOut();
}

void Parser::Parser::ASSIGNMENT() {
    print_func_header(__func__ );
    goIn();
    if (match(CURRENTTOKEN, ":=")) {
        nextToken();
        TO_ASSIGN();
        nextToken();
        getOut();
        if (match(CURRENTTOKEN, ";")) {
            getOut();
            nextToken();
            STATEMENT();
        }
    } else {
        std::cerr << "Expected :=, but found " << CURRENTTOKEN << " instead." << std::endl;
        exit(1);
    }
    getOut();
}

void Parser::Parser::LOOP() {
    print_func_header(__func__ );
    goIn();
    if (match(CURRENTTOKEN, "while")) {
        nextToken();
        COMPARISON();
        if (match(CURRENTTOKEN, ":")) {
            nextToken();
            getOut();
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
    print_func_header(__func__ );

}

void Parser::Parser::IF() {
    print_func_header(__func__ );

}

void Parser::Parser::PRINTS() {
    print_func_header(__func__ );
    goIn();
    if (match(CURRENTTOKEN, "println") || match(CURRENTTOKEN, "print")) {
        nextToken();
        if (match(CURRENTTOKEN, "(")) {
            nextToken();
            TO_PRINT();
            nextToken();
            if (match(CURRENTTOKEN, ")")) {
                nextToken();
                getOut();
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
    print_func_header(__func__ );
    goIn();
    if (match(CURRENTTOKEN, "in")){
        nextToken();
        if (match(CURRENTTOKEN, ">>")) {
            nextToken();
            IDENTIFIER();
            nextToken();
            getOut();
            if (match(CURRENTTOKEN, ";")){
                nextToken();
                STATEMENT();
            } else {
                std::cerr << "Expected ;, but found " << CURRENTTOKEN << " instead." << std::endl;
                exit(1);
            }
        } else{
            std::cerr << "Expected >>, but found " << CURRENTTOKEN << " instead." << std::endl;
            exit(1);
        }
    }

}

void Parser::Parser::CHAR_DEC_ASS() {
    print_func_header(__func__ );

}

void Parser::Parser::INT_DEC_ASS() {
    print_func_header(__func__ );

}

void Parser::Parser::TO_ASSIGN() {
    print_func_header(__func__ );
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
    print_func_header(__func__ );

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
    print_func_header(__func__ );

    for (int i = 0; CURRENTTOKEN[i] != '\0'; i++) {
        if (!isdigit(CURRENTTOKEN[i])) {
            std::cerr << "Illegal number.";
            exit(1);
        }
    }
}

void Parser::Parser::TO_PRINT() {
    print_func_header(__func__ );
    goIn();
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
    getOut();
}

void Parser::Parser::STRING() {
    print_func_header(__func__ );

    if (CURRENTTOKEN[0] == '\"' && CURRENTTOKEN.back() == '\"') { ;
    } else {
        std::cerr << "Illegal print string.";
        exit(1);
    }
}
