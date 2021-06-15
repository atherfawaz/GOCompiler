//
// Created by ather on 18-May-21.
//

#include <iterator>
#include <sstream>
#include "Parser.h"
#include "Lexer.h"

#define CURRENTTOKEN tokens[cursor].getLexeme()
#define PREVIOUSTOKEN tokens[cursor - 1].getLexeme()
#define ROW tokens[cursor].getRow()
#define COLUMN tokens[cursor].getCol()
#define ARITHMETIC_OPERATOR  define_match(CURRENTTOKEN, "+") || define_match(CURRENTTOKEN, "-") || define_match(CURRENTTOKEN, "*") || define_match(CURRENTTOKEN, "/")
#define ICV define_match(CURRENTTOKEN, "integer") || define_match(CURRENTTOKEN, "char") || define_match(CURRENTTOKEN, "void")
#define RELATIONALOPERATOR define_match(CURRENTTOKEN, "<") || define_match(CURRENTTOKEN, "<=") || define_match(CURRENTTOKEN, ">") || define_match(CURRENTTOKEN, ">=") || define_match(CURRENTTOKEN, "==") || define_match( CURRENTTOKEN, "/=")
#define TOKEN_METADATA "[" << ROW << ":" << COLUMN << "] "
#define STACKEMPTY this->stack.empty()
#define HIGHERPRECEDENCE this->operatorPrecedence[op] > this->operatorPrecedence[this->stack.top()]
#define LOWEREQUALPRECEDENCE this->operatorPrecedence[op] <= this->operatorPrecedence[this->stack.top()]

Parser::Parser::Parser() = default;

Parser::Parser::Parser(const std::vector<Lexer::Token> &tok, const std::string &tree, const std::string &table,
                       const std::string &tac) {
    this->cursor = 0;
    this->tokens = tok;
    this->parsingTree.open(tree);
    this->symbolTable.open(table);
    this->tac.open(tac);

    this->operatorPrecedence.insert(std::pair<std::string, int>("/", 4));
    this->operatorPrecedence.insert(std::pair<std::string, int>("*", 4));
    this->operatorPrecedence.insert(std::pair<std::string, int>("+", 2));
    this->operatorPrecedence.insert(std::pair<std::string, int>("-", 2));
}

void Parser::Parser::functionHeader(const std::string &func_name, const std::string &cur_tok) {
    //this->parsingTree << "|-";
    for (int i = 0; i < this->tabs; i++)

        if (i == this->tabs - 1)
            this->parsingTree << "|---";
        else
            this->parsingTree << "|   ";
    this->parsingTree << func_name << "     " << cur_tok << std::endl;
    //this->parsingTree.push_back(std::tuple<std::string, std::string  ,int>(func_name, CURRENTTOKEN, this->tabs));
}

void Parser::Parser::writeTAC(const std::string &new_statement) {
    this->threeAddCode += new_statement;
}

void Parser::Parser::fillInTheHole(int pos) {
    this->threeAddCode.insert(pos, std::to_string(this->lineNum));
    this->offset += std::to_string(this->lineNum).length();
}

void Parser::Parser::emit(const std::string &to_print) {
    writeTAC(to_print);
    this->lineNum++;
    // do something else for the future
}

void Parser::Parser::getIn() {
    this->tabs++;
}

void Parser::Parser::getOut() {
    this->tabs--;
}

bool Parser::Parser::parse() {
    //std::cout << "Current Token: " << CURRENTTOKEN << "\n";
    std::cout << std::endl;
    if (tokens[cursor].non_empty()) {
        std::cout << "Started parsing.\n";
        START_PARSE();
        return true;
    }
    return false;
}

void Parser::Parser::nextToken() {
    cursor++;
    if (cursor >= tokens.size()) {
        std::cout << "Finished parsing.\n";
        std::cout << "Generated three-address-code.\n";
        save();
        //exit(0);
    }
    //std::cout << "Current Token: " << CURRENTTOKEN << "\n";
}

void Parser::Parser::save() {

    std::map<std::string, std::string>::iterator it;
    int address = 0;

    for (it = this->translatorSymbolTable.begin(); it != this->translatorSymbolTable.end(); it++) {
        this->symbolTable << it->second    // data type
                          << ':'
                          << it->first   // identifier
                          << ":"
                          << address
                          << std::endl;
        if (it->second == "char") {
            address++;
        } else {
            address += 4;
        }
    }
    tac << this->threeAddCode;

    this->tac.close();
    this->symbolTable.close();
    this->parsingTree.close();


}

bool Parser::Parser::peekExpression() {
    nextToken();
    if (CURRENTTOKEN[0] == '\'') {
        cursor--;
        return false;
    }
    if (isalpha(CURRENTTOKEN[0]) || (isdigit(CURRENTTOKEN[0])))
        if (isalpha(CURRENTTOKEN[0]))
            IDENTIFIER();
        else if (isdigit(CURRENTTOKEN[0])) {
            NUMBER();
        } else {
            std::cerr << TOKEN_METADATA << "Identifier name for must start with an alpha character"
                      << std::endl << __func__;

            exit(-1);
        }
    else {
        std::cerr << TOKEN_METADATA << "Statement error neither Expression or assignment "
                  << std::endl << __func__;
    }
    nextToken();
    if (ARITHMETIC_OPERATOR) {
        cursor--;
        //std::swap(tokens[cursor], tokens[cursor + 1]);
        cursor--;
        return true;
    } else {
        cursor--;
        cursor--;
        return false;
    }

}

bool Parser::Parser::match(const std::string &func_name, const std::string &lexeme, const std::string &toMatch) {
    if (lexeme == toMatch) {
        functionHeader(func_name, toMatch);
        return true;
    } else {
        return false;
    }
}

bool Parser::Parser::define_match(const std::string &lexeme, const std::string &toMatch) {
    if (lexeme == toMatch) return true;
    return false;
}

void Parser::Parser::maintainStack(const std::string &op) {
    if (STACKEMPTY || HIGHERPRECEDENCE) {
        this->postfix += " ";
        this->stack.push(op);
        this->postfix += " ";
    } else {
        if (LOWEREQUALPRECEDENCE) {
            while (!STACKEMPTY && LOWEREQUALPRECEDENCE) {
                this->postfix += " ";
                this->postfix += this->stack.top();
                this->postfix += " ";
                this->stack.pop();
            }
            this->postfix += " ";
            this->stack.push(op);
            this->postfix += " ";

        }
    }
}

void Parser::Parser::evaluatePostfix(const std::string &expr, const std::string &toAssign) {
    int counter = 0;
    std::istringstream iss(expr);
    std::vector<std::string> result{std::istream_iterator<std::string>(iss), {}
    };
    for (auto &ch: result) {
        if (ch != "/" && ch != "*" && ch != "+" && ch != "-") {
            //encountered number or identifier
            this->evalStack.push(ch);
        } else {
            //encountered operator
            auto rightOperand = this->evalStack.top();
            this->evalStack.pop();
            auto leftOperand = this->evalStack.top();
            this->evalStack.pop();
            writeTAC("temp" + std::to_string(counter) + " = " + leftOperand + " " + ch + " " + rightOperand);
            emit("\n");
            this->evalStack.push("temp" + std::to_string(counter));
            counter++;
        }
    }
    while (!this->evalStack.empty()) this->evalStack.pop();
    writeTAC(toAssign + " = " + "temp" + std::to_string(counter - 1));
    emit("\n");
}

void Parser::Parser::cleanStack() {
    while (!STACKEMPTY) {
        this->postfix += this->stack.top();
        this->stack.pop();
    }
}

void Parser::Parser::storeExpression() {
    this->expressionArray.emplace_back(this->postfix);
    this->postfix.clear();
}

void Parser::Parser::START_PARSE() {
    functionHeader(__func__, "");

    PROGRAM_START();
}

void Parser::Parser::PROGRAM_START() {
    functionHeader(__func__, "");

    if (match(__func__, CURRENTTOKEN, "func")) {
        getIn();
        FUNC_HEADER();
        this->tabs = 0;
        nextToken();
        PROG_S();
    } else {
        getIn();
        STATEMENT();
        getOut();
        nextToken();
        PROG_S();
    }
}

void Parser::Parser::PROG_S() {
    functionHeader(__func__, "");
    if (this->cursor >= this->tokens.size()) {
        return;
    }
    if (match(__func__, CURRENTTOKEN, "func")) {
        getIn();
        FUNC_HEADER();
        this->tabs = 0;
        nextToken();
        PROG_S();
    } else {
        getIn();
        STATEMENT();
        getOut();
        nextToken();
        PROG_S();
    }

}

void Parser::Parser::FUNC_HEADER() {
    functionHeader(__func__, CURRENTTOKEN);

    getIn();
    if (match(__func__, CURRENTTOKEN, "func")) {
        nextToken();
        RETURN_TYPE();
        nextToken();
        if (match(__func__, CURRENTTOKEN, ":")) {
            nextToken();
            IDENTIFIER();
            nextToken();
            if (match(__func__, CURRENTTOKEN, "(")) {
                nextToken();
                PARAMETERS();
                //nextToken();
                if (match(__func__, CURRENTTOKEN, ")")) {
                    nextToken();
                    if (match(__func__, CURRENTTOKEN, "{")) {
                        nextToken();
                        STATEMENT();
                        //nextToken();
                        if (match(__func__, CURRENTTOKEN, "}")) {
                            //nextToken();
                            //FUNC_HEADER();
                            //nextToken();
                            //STATEMENT();
                        } else {
                            std::cerr << TOKEN_METADATA << "Expected }, but found " << CURRENTTOKEN
                                      << " instead." << std::endl;
                            exit(1);
                        }
                    } else {
                        std::cerr << TOKEN_METADATA << "Expected {, but found " << CURRENTTOKEN
                                  << " instead." << std::endl;
                        exit(1);
                    }
                } else {
                    std::cerr << TOKEN_METADATA << "Expected ), but found " << CURRENTTOKEN
                              << " instead." << std::endl;
                    exit(1);
                }
            } else {
                std::cerr << TOKEN_METADATA << "Expected (, but found " << CURRENTTOKEN
                          << " instead." << std::endl;
                exit(1);
            }
        } else {
            std::cerr << TOKEN_METADATA << "Expected :, but found " << CURRENTTOKEN << " instead."
                      << std::endl;
            exit(1);
        }
        //IDENTIFIER();
    }
    getOut();
}

void Parser::Parser::RETURN_TYPE() {
    functionHeader(__func__, CURRENTTOKEN);

    if (ICV) return;
    else {
        std::cerr << TOKEN_METADATA << "Expected INTEGER, CHAR, or VOID but found " << CURRENTTOKEN
                  << " instead." << std::endl;
        exit(1);
    }

}

void Parser::Parser::IDENTIFIER() {
    functionHeader(__func__, CURRENTTOKEN);

    getIn();
    if (isalpha(CURRENTTOKEN[0])) {
        ALPHABET();
        ALPHANUMERIC();
    }
    getOut();
}

void Parser::Parser::ALPHABET() {
    functionHeader(__func__, "");

    if (isalpha(CURRENTTOKEN[0])) return;
    else {
        std::cerr << TOKEN_METADATA << "Expected IDENTIFIER, but found " << CURRENTTOKEN
                  << " instead." << std::endl;
        exit(1);
    }

}

void Parser::Parser::ALPHANUMERIC() {
    functionHeader(__func__, "");

    std::string str = CURRENTTOKEN;
    for (int i = 1; str[i] != '\0'; i++) {
        if (!isalnum(str[i])) {
            std::cerr << TOKEN_METADATA << "Expected IDENTIFIER, but found " << CURRENTTOKEN
                      << " instead." << std::endl;
            exit(1);
        }
    }

}

void Parser::Parser::PARAMETERS() {
    functionHeader(__func__, "");

    getIn();
    DATATYPE();
    nextToken();
    if (match(__func__, CURRENTTOKEN, ":")) {
        nextToken();
        IDENTIFIER();
        nextToken();
        getOut();
        ADDITIONAL_PARAMETERS();
    }

}

void Parser::Parser::STATEMENT() {
    functionHeader(__func__, "");
    bool to_get_out = false;
    getIn();

    if (define_match(CURRENTTOKEN, "integer")) {
        to_get_out = true;
        INT_DECLARATION();
        getOut();
        nextToken();
        STATEMENT();
    } else if (define_match(CURRENTTOKEN, "char")) {
        to_get_out = true;
        CHAR_DECLARATION();
        getOut();
        nextToken();
        STATEMENT();
    } else if (define_match(CURRENTTOKEN, "while")) {
        to_get_out = true;
        int prev_tabs = this->tabs;
        LOOP();
        this->tabs = prev_tabs;
        getOut();
        nextToken();
        STATEMENT();
    } else if (define_match(CURRENTTOKEN, "if")) {
        to_get_out = true;
        IF();
        getOut();
        //nextToken();
        STATEMENT();
    } else if (define_match(CURRENTTOKEN, "print") || define_match(CURRENTTOKEN, "println")) {
        to_get_out = true;
        PRINTS();
        getOut();
        nextToken();
        STATEMENT();
    } else if (define_match(CURRENTTOKEN, "in")) {
        to_get_out = true;
        INPUT();
        getOut();
        nextToken();
        STATEMENT();
    } else if (define_match(CURRENTTOKEN, "ret")) {
        to_get_out = true;
        RETURN_VALUE();
        getOut();
        nextToken();
        if (define_match(CURRENTTOKEN, ";")) {
            to_get_out = true;
            nextToken();
            STATEMENT();
        } else {
            std::cerr << TOKEN_METADATA << "Expected ;, but found " << CURRENTTOKEN << " instead."
                      << std::endl;
            exit(1);
        }
    } else if (isalpha(CURRENTTOKEN[0])) {
        to_get_out = true;
        IDENTIFIER();
        std::string leftVar = CURRENTTOKEN;
        nextToken();
        if (RELATIONALOPERATOR) {
            COMPARISON();
            getOut();
            nextToken();
            STATEMENT();
        } else if (define_match(CURRENTTOKEN, ":=")) {
            if (peekExpression()) {
                nextToken();
                EXPRESSION();
                cleanStack();
                //emit(leftVar + " = " + "temp" + std::to_string(this->exprTemp) + " \n");
                storeExpression();
                //std::cout << "Converted postfix expression: " << this->expressionArray.back() << std::endl;
                //std::cout << "Evaluating expression...\n";
                evaluatePostfix(this->expressionArray.back(), leftVar);
                this->exprTemp = 0;
                getOut();
                if (define_match(CURRENTTOKEN, ";")) { ;
                } else {
                    std::cerr << TOKEN_METADATA << "Expected ;, but found " << CURRENTTOKEN
                              << " instead." << std::endl;
                    exit(1);
                }
            } else {
                this->assignString += leftVar;
                ASSIGNMENT();
                getOut();
            }
            nextToken();
            STATEMENT();
        } else if (define_match(CURRENTTOKEN, "(")) {
            to_get_out = true;
            FUNCTION_CALL();
            getOut();
            nextToken();
            STATEMENT();
        } else {
            std::cerr << TOKEN_METADATA << "Terrible terrible mistakes" << std::endl;
            exit(1);
        }
    }
    if (to_get_out)
        getOut();
}

void Parser::Parser::ADDITIONAL_PARAMETERS() {
    functionHeader(__func__, CURRENTTOKEN);

    if (match(__func__, CURRENTTOKEN, ",")) {
        nextToken();
        PARAMETERS();
    }

}

void Parser::Parser::DATATYPE() {
    functionHeader(__func__, CURRENTTOKEN);

    if (match(__func__, CURRENTTOKEN, "integer") || match(__func__, CURRENTTOKEN, "char")) { ;
    } else {
        std::cerr << TOKEN_METADATA << "Expected INTEGER or CHAR, but found " << CURRENTTOKEN
                  << " instead." << std::endl;
        exit(1);
    }

}

void Parser::Parser::INT_DECLARATION() {
    functionHeader(__func__, CURRENTTOKEN);

    getIn();
    if (match(__func__, CURRENTTOKEN, "integer")) {
        nextToken();
        if (match(__func__, CURRENTTOKEN, ":")) {
            nextToken();
            IDENTIFIER();
            this->translatorSymbolTable[CURRENTTOKEN] = "integer";
            nextToken();
            getOut();
            ADD_INT_DEC();
            //nextToken();
            if (match(__func__, CURRENTTOKEN, ";")) {
                //getOut();
                //nextToken();
                //STATEMENT();
            } else {
                std::cerr << TOKEN_METADATA << "Expected ;, but found " << CURRENTTOKEN
                          << " instead." << std::endl;
                exit(1);
            }
        } else {
            std::cerr << TOKEN_METADATA << "Expected :, but found " << CURRENTTOKEN << " instead."
                      << std::endl;
            exit(1);
        }
    } else {
        std::cerr << TOKEN_METADATA << "Expected INTEGER, but found " << CURRENTTOKEN
                  << " instead." << std::endl;
        exit(1);
    }
    getOut();
}

void Parser::Parser::ADD_INT_DEC() {
    functionHeader(__func__, CURRENTTOKEN);

    getIn();
    if (match(__func__, CURRENTTOKEN, ",")) {
        nextToken();
        IDENTIFIER();
        this->translatorSymbolTable[CURRENTTOKEN] = "integer";
        nextToken();
        getOut();
        ADD_INT_DEC();
    }
    //getOut();
}

void Parser::Parser::CHAR_DECLARATION() {
    functionHeader(__func__, CURRENTTOKEN);

    getIn();
    if (match(__func__, CURRENTTOKEN, "char")) {
        nextToken();
        if (match(__func__, CURRENTTOKEN, ":")) {
            nextToken();
            IDENTIFIER();
            this->translatorSymbolTable[CURRENTTOKEN] = "char";
            nextToken();
            getOut();
            ADD_CHAR_DEC();
            //nextToken();
            if (match(__func__, CURRENTTOKEN, ";")) {
                //nextToken();
                //STATEMENT();
            } else {
                std::cerr << TOKEN_METADATA << "Expected ;, but found " << CURRENTTOKEN
                          << " instead." << std::endl;
                exit(1);
            }
        } else {
            std::cerr << TOKEN_METADATA << "Expected :, but found " << CURRENTTOKEN << " instead."
                      << std::endl;
            exit(1);
        }
    } else {
        std::cerr << TOKEN_METADATA << "Expected CHAR, but found " << CURRENTTOKEN << " instead."
                  << std::endl;
        exit(1);
    }
    getOut();
}

void Parser::Parser::ADD_CHAR_DEC() {
    functionHeader(__func__, CURRENTTOKEN);

    getIn();
    if (match(__func__, CURRENTTOKEN, ",")) {
        nextToken();
        IDENTIFIER();
        this->translatorSymbolTable[CURRENTTOKEN] = "char";
        nextToken();
        getOut();
        ADD_CHAR_DEC();
    }
    //getOut();
}

void Parser::Parser::EXPRESSION() {
    functionHeader(__func__, CURRENTTOKEN);

    getIn();
    MUL_DIV();
    ADD_SUB();
    getOut();
}

void Parser::Parser::MUL_DIV() {
    functionHeader(__func__, "");

    getIn();
    FINAL();
    MUL_DIV_();
    getOut();
}

void Parser::Parser::MUL_DIV_() {
    functionHeader(__func__, CURRENTTOKEN);

    getIn();
    if (match(__func__, CURRENTTOKEN, "*")) {
        maintainStack("*");
        if (this->exprTemp != 0) {
            this->isRight = true;
        } else {
            isRight = true;
        }
        nextToken();
        FINAL();
        MUL_DIV_();
    }
    if (match(__func__, CURRENTTOKEN, "/")) {
        maintainStack("/");
        if (this->exprTemp != 0) {
            this->isRight = true;
        } else {
            isRight = true;
        }
        nextToken();
        FINAL();
        MUL_DIV_();
    }
    getOut();
}

void Parser::Parser::FINAL() {
    functionHeader(__func__, "");

    getIn();
    if (isalpha(CURRENTTOKEN[0])) {
        this->postfix += " ";
        this->postfix += CURRENTTOKEN;
        this->postfix += " ";
        IDENTIFIER();
        if (isRight) {
            this->exprTemp++;
            this->isRight = false;
        }
        nextToken();
    } else if (isdigit(CURRENTTOKEN[0])) {
        this->postfix += " ";
        this->postfix += CURRENTTOKEN;
        this->postfix += " ";
        NUMBER();
        if (isRight) {
            this->exprTemp++;
            this->isRight = false;
        }
        nextToken();
    }
    if (match(__func__, CURRENTTOKEN, "(")) {
        this->stack.push("(");
        nextToken();
        EXPRESSION();
        //nextToken();
        if (match(__func__, CURRENTTOKEN, ")")) {
            while (!this->stack.empty()) {
                if (this->stack.top() == "(") {
                    this->stack.pop();
                    break;
                } else {
                    this->postfix += " ";
                    this->postfix += this->stack.top();
                    this->postfix += " ";
                    this->stack.pop();
                }
            }
            nextToken();
        } else {
            std::cerr << TOKEN_METADATA << "Expected (, but found " << CURRENTTOKEN << " instead."
                      << std::endl;
            exit(1);
        }
    }
    getOut();
}

void Parser::Parser::ADD_SUB() {
    functionHeader(__func__, CURRENTTOKEN);

    getIn();
    if (match(__func__, CURRENTTOKEN, "+")) {
        maintainStack("+");
        if (this->exprTemp != 0) {
            this->isRight = true;
        } else {
            isRight = true;
        }
        nextToken();
        //right side
        MUL_DIV();
        ADD_SUB();
    }
    if (match(__func__, CURRENTTOKEN, "-")) {
        maintainStack("-");
        if (this->exprTemp != 0) {
            this->isRight = true;
        } else {
            isRight = true;
        }
        nextToken();
        //right side
        MUL_DIV();
        ADD_SUB();
    }
    getOut();
}

void Parser::Parser::ASSIGNMENT() {
    functionHeader(__func__, CURRENTTOKEN);

    getIn();
    if (match(__func__, CURRENTTOKEN, ":=")) {
        nextToken();
        TO_ASSIGN();
        nextToken();
        //getOut();
        if (match(__func__, CURRENTTOKEN, ";")) {
            //getOut();
            //nextToken();
            //STATEMENT();
        }
    } else {
        std::cerr << TOKEN_METADATA << "Expected :=, but found " << CURRENTTOKEN << " instead."
                  << std::endl;
        exit(1);
    }
    getOut();
}

void Parser::Parser::TO_ASSIGN() {
    functionHeader(__func__, "");
    this->assignString += " = " + CURRENTTOKEN; //adding assignment statement
    if (CURRENTTOKEN[0] == '\'') {
        LIT_CONST();
    } else if (isdigit(CURRENTTOKEN[0])) {
        NUMBER();
    } else if (isalpha(CURRENTTOKEN[0])) {
        IDENTIFIER();
    } else {
        std::cerr << TOKEN_METADATA << "Expected an assignment of some sort, but found "
                  << CURRENTTOKEN << " instead." << std::endl;
        exit(1);
    }
    writeTAC(this->assignString);
    emit("\n");
    this->assignString.clear();
}

void Parser::Parser::LOOP() {
    functionHeader(__func__, CURRENTTOKEN);
    std::queue<int> goto_queue;
    int offset = 0;
    getIn();
    if (match(__func__, CURRENTTOKEN, "while")) {
        writeTAC("Wif ");
        nextToken();
        COMPARISON();
        writeTAC("goto  ");
        goto_queue.push(this->threeAddCode.length() - 1);
        int loop_start = this->lineNum;
        emit("\n");
        if (match(__func__, CURRENTTOKEN, ":")) {
            nextToken();
            writeTAC("goto  ");
            goto_queue.push(this->threeAddCode.length() - 1);
            emit("\n");

            //getOut();
            if (match(__func__, CURRENTTOKEN, "{")) {
                fillInTheHole(goto_queue.front());
                goto_queue.pop();
                offset = std::to_string(this->lineNum).length();
                nextToken();
                STATEMENT();
                if (match(__func__, CURRENTTOKEN, "}")) {
                    //nextToken();
                    //STATEMENT();
                    emit("goto " + std::to_string(loop_start) + "\n");
                } else {
                    std::cerr << TOKEN_METADATA << "Expected }, but found " << CURRENTTOKEN
                              << " instead." << std::endl;
                    exit(1);
                }
            } else {
                std::cerr << TOKEN_METADATA << "Expected {, but found " << CURRENTTOKEN
                          << " instead." << std::endl;
                exit(1);
            }
        } else {
            std::cerr << TOKEN_METADATA << "Expected :, but found " << CURRENTTOKEN << " instead."
                      << std::endl;
            exit(1);
        }
    } else {
        std::cout << "Ye tou garbar hai";
    }
    fillInTheHole(goto_queue.front() + offset);
    goto_queue.pop();

    getOut();
}

void Parser::Parser::PRINTS() {
    functionHeader(__func__, CURRENTTOKEN);

    getIn();
    if (match(__func__, CURRENTTOKEN, "println") || match(__func__, CURRENTTOKEN, "print")) {
        nextToken();
        if (match(__func__, CURRENTTOKEN, "(")) {
            nextToken();
            TO_PRINT();
            emit("out " + CURRENTTOKEN + "\n");
            nextToken();
            if (match(__func__, CURRENTTOKEN, ")")) {
                nextToken();
                if (match(__func__, CURRENTTOKEN, ";")) {
                    //nextToken();
                    //STATEMENT();
                } else {
                    std::cerr << TOKEN_METADATA << "Expected ;, but found " << CURRENTTOKEN
                              << " instead." << std::endl;
                    exit(1);
                }
            } else {
                std::cerr << TOKEN_METADATA << "Expected ), but found " << CURRENTTOKEN
                          << " instead." << std::endl;
                exit(1);
            }
        } else {
            std::cerr << TOKEN_METADATA << "Expected (, but found " << CURRENTTOKEN << " instead."
                      << std::endl;
            exit(1);
        }
    }
    getOut();
}

void Parser::Parser::INPUT() {
    functionHeader(__func__, CURRENTTOKEN);

    getIn();
    if (match(__func__, CURRENTTOKEN, "in")) {
        nextToken();
        if (match(__func__, CURRENTTOKEN, ">>")) {
            nextToken();
            IDENTIFIER();
            nextToken();
            getOut();
            if (match(__func__, CURRENTTOKEN, ";")) {
                //nextToken();
                //STATEMENT();
            } else {
                std::cerr << TOKEN_METADATA << "Expected ;, but found " << CURRENTTOKEN
                          << " instead." << std::endl;
                exit(1);
            }
        } else {
            std::cerr << TOKEN_METADATA << "Expected >>, but found " << CURRENTTOKEN << " instead."
                      << std::endl;
            exit(1);
        }
    }
    emit("in " + PREVIOUSTOKEN + "\n");
}

void Parser::Parser::LIT_CONST() {
    functionHeader(__func__, CURRENTTOKEN);

    if (CURRENTTOKEN.size() != 3) {
        std::cerr << TOKEN_METADATA << "Illegal literal constant.";
        exit(1);
    }
    if (CURRENTTOKEN[0] == '\'' && CURRENTTOKEN[2] == '\'') { ;
    } else {
        std::cerr << TOKEN_METADATA << "Expected ', but found " << CURRENTTOKEN << " instead."
                  << std::endl;
        exit(1);
    }
}

void Parser::Parser::NUMBER() {
    functionHeader(__func__, CURRENTTOKEN);

    for (int i = 0; CURRENTTOKEN[i] != '\0'; i++) {
        if (!isdigit(CURRENTTOKEN[i])) {
            std::cerr << TOKEN_METADATA << "Illegal number.";
            exit(1);
        }
    }
}

void Parser::Parser::TO_PRINT() {
    functionHeader(__func__, "");
    getIn();
    if (CURRENTTOKEN[0] == '\'') {
        LIT_CONST();
    } else if (CURRENTTOKEN[0] == '\"') {
        STRING();
    } else if (CURRENTTOKEN[0] >= '0' && CURRENTTOKEN[0] <= '9') {
        NUMBER();
    } else if (isalpha(CURRENTTOKEN[0])) {
        IDENTIFIER();
    } else {
        std::cerr << TOKEN_METADATA << "Illegal print statement.";
        exit(1);
    }
    getOut();
}

void Parser::Parser::STRING() {
    functionHeader(__func__, CURRENTTOKEN);

    if (CURRENTTOKEN[0] == '\"' && CURRENTTOKEN.back() == '\"') { ;
    } else {
        std::cerr << TOKEN_METADATA << "Illegal print string.";
        exit(1);
    }
}

void Parser::Parser::CONDITIONAL() {
    functionHeader(__func__, "");

    getIn();
    if (isdigit(CURRENTTOKEN[0]))
        NUMBER();
    else if (isalpha(CURRENTTOKEN[0]))
        IDENTIFIER();
    else {
        std::cerr << TOKEN_METADATA << "Expected NUMBER or IDENTIFIER, but found " << CURRENTTOKEN
                  << " instead." << std::endl;
        exit(1);
    }
    writeTAC(CURRENTTOKEN + " ");
    getOut();
}

void Parser::Parser::RELATIONAL_OP() {
    functionHeader(__func__, CURRENTTOKEN);

    if (RELATIONALOPERATOR) {
        return;
    } else {
        std::cerr << TOKEN_METADATA << "Expected a RELATIONAL_OP, but found " << CURRENTTOKEN
                  << " instead." << std::endl;
        exit(1);
    }
}

void Parser::Parser::ADDITIONAL_COMP() {
    functionHeader(__func__, CURRENTTOKEN);

    if (RELATIONALOPERATOR) {
        writeTAC(CURRENTTOKEN + " ");
        nextToken();
        CONDITIONAL();
        nextToken();
        ADDITIONAL_COMP();
    }
}

void Parser::Parser::COMPARISON() {
    functionHeader(__func__, "");
    getIn();
    CONDITIONAL();
    //std::cout << CURRENTTOKEN + " ";
    nextToken();
    RELATIONAL_OP();
    writeTAC(CURRENTTOKEN + " ");
    nextToken();
    CONDITIONAL();
    //std::cout << CURRENTTOKEN + " ";
    nextToken();
    ADDITIONAL_COMP();
    getOut();
}

void Parser::Parser::IF() {
    functionHeader(__func__, CURRENTTOKEN);
    std::queue<int> goto_queue;
    getIn();
    int offset = 0;
    if (match(__func__, CURRENTTOKEN, "if")) {
        writeTAC("if ");
        nextToken();
        COMPARISON();
        writeTAC("goto  ");
        goto_queue.push(this->threeAddCode.length() - 1);
        emit("\n");

        //nextToken();
        if (match(__func__, CURRENTTOKEN, ":")) {
            nextToken();
            writeTAC("goto  ");
            goto_queue.push(this->threeAddCode.length() - 1);
            emit("\n");
            if (match(__func__, CURRENTTOKEN, "{")) {
                fillInTheHole(goto_queue.front());
                goto_queue.pop();
                offset = std::to_string(this->lineNum).length();
                nextToken();
                STATEMENT();
                //nextToken();
                if (match(__func__, CURRENTTOKEN, "}")) {

                    nextToken();
                    writeTAC("goto  ");
                    goto_queue.push(this->threeAddCode.length() - 1);
                    emit("\n");
                    fillInTheHole(goto_queue.front() + offset);
                    goto_queue.pop();
                    offset = std::to_string(this->lineNum).length();
                    if (match(__func__, CURRENTTOKEN, "elif")) {
                        ELIF(goto_queue);
                        getOut();
                        //nextToken();
                    }
                    if (match(__func__, CURRENTTOKEN, "else")) {
                        ELSE();
                        nextToken();
                    }
                } else {
                    std::cerr << TOKEN_METADATA << "Expected a }, but found " << CURRENTTOKEN
                              << " instead." << std::endl;
                    exit(1);
                }
            } else {
                std::cerr << TOKEN_METADATA << "Expected a {, but found " << CURRENTTOKEN
                          << " instead." << std::endl;
                exit(1);
            }
        } else {
            std::cerr << TOKEN_METADATA << "Expected an :, but found " << CURRENTTOKEN
                      << " instead." << std::endl;
            exit(1);
        }
    } else {
        std::cerr << TOKEN_METADATA << "Expected a if, but found " << CURRENTTOKEN << " instead."
                  << std::endl;
        exit(1);
    }

    //std::cout << goto_queue.size() << std::endl;

    int counter = 1;
    while (!goto_queue.empty()) {
        fillInTheHole(goto_queue.front() + (offset * counter));
        //std::cout <<"";
        counter++;
        goto_queue.pop();
    }
    getOut();
}

void Parser::Parser::ELIF(std::queue<int> &outer_queue) {
    functionHeader(__func__, CURRENTTOKEN);
    int offset = 0;
    std::queue<int> goto_queue;

    bool get_out = false;
    getIn();
    if (match(__func__, CURRENTTOKEN, "elif")) {

        writeTAC("elif ");
        nextToken();
        COMPARISON();
        writeTAC("goto  ");
        goto_queue.push(this->threeAddCode.length() - 1);
        emit("\n");
        //nextToken();
        if (match(__func__, CURRENTTOKEN, ":")) {
            writeTAC("goto  ");
            goto_queue.push(this->threeAddCode.length() - 1);
            emit("\n");
            nextToken();
            if (match(__func__, CURRENTTOKEN, "{")) {
                fillInTheHole(goto_queue.front());
                goto_queue.pop();
                offset = std::to_string(this->lineNum).length();
                nextToken();
                STATEMENT();
                //nextToken(); //hmmm, im not sure about this
                if (match(__func__, CURRENTTOKEN, "}")) {
                    get_out = true;
                    nextToken();
                    writeTAC("goto  ");
                    outer_queue.push(this->threeAddCode.length() - 1);
                    emit("\n");
                    fillInTheHole(goto_queue.front() + offset);
                    goto_queue.pop();
                    if (match(__func__, CURRENTTOKEN, "elif")) {
                        ELIF(outer_queue);
                    }
                } else {
                    std::cerr << TOKEN_METADATA << "Expected a }, but found " << CURRENTTOKEN
                              << " instead." << std::endl;
                    exit(1);
                }
            } else {
                std::cerr << TOKEN_METADATA << "Expected a {, but found " << CURRENTTOKEN
                          << " instead." << std::endl;
                exit(1);
            }
        } else {
            std::cerr << TOKEN_METADATA << "Expected a :, but found " << CURRENTTOKEN
                      << " instead." << std::endl;
            exit(1);
        }
    }
    if (get_out)
        getOut();
}

void Parser::Parser::ELSE() {
    functionHeader(__func__, CURRENTTOKEN);

    getIn();
    if (match(__func__, CURRENTTOKEN, "else")) {
        nextToken();
        if (match(__func__, CURRENTTOKEN, "{")) {
            nextToken();
            STATEMENT();
            //nextToken();
            if (match(__func__, CURRENTTOKEN, "}")) { ;
            } else {
                std::cerr << TOKEN_METADATA << "Expected a }, but found " << CURRENTTOKEN
                          << " instead." << std::endl;
                exit(1);
            }
        }

    } else {
        std::cerr << TOKEN_METADATA << "Expected a {, but found " << CURRENTTOKEN << " instead."
                  << std::endl;
        exit(1);
    }
    getOut();
}

void Parser::Parser::FUNCTION_CALL() {
    functionHeader(__func__, CURRENTTOKEN);

    getIn();
    if (match(__func__, CURRENTTOKEN, "(")) {
        nextToken();
        ARGUMENTS();
        if (match(__func__, CURRENTTOKEN, ")")) {
            nextToken();
            if (match(__func__, CURRENTTOKEN, ";")) { ;
            } else {
                std::cerr << TOKEN_METADATA << "Expected a ;, but found " << CURRENTTOKEN
                          << " instead." << std::endl;
                exit(1);
            }
        } else {
            std::cerr << TOKEN_METADATA << "Expected a ), but found " << CURRENTTOKEN
                      << " instead." << std::endl;
            exit(1);
        }
    } else {
        std::cerr << TOKEN_METADATA << "Expected a (, but found " << CURRENTTOKEN << " instead."
                  << std::endl;
        exit(1);
    }
    getOut();
}

void Parser::Parser::ARGUMENTS() {
    functionHeader(__func__, "");

    if (isdigit(CURRENTTOKEN[0])) {
        NUMBER();
        nextToken();
        MORE_ARGS();
    } else if (CURRENTTOKEN[0] == '\'') {
        LIT_CONST();
        nextToken();
        MORE_ARGS();
    } else if (CURRENTTOKEN[0] == '"') {
        STRING();
        nextToken();
        MORE_ARGS();
    } else if (isalpha(CURRENTTOKEN[0])) {
        IDENTIFIER();
        nextToken();
        MORE_ARGS();
    }
}

void Parser::Parser::MORE_ARGS() {
    functionHeader(__func__, CURRENTTOKEN);

    if (match(__func__, CURRENTTOKEN, ",")) {
        nextToken();
        ARGUMENTS();
    }
}

void Parser::Parser::RETURN_VALUE() {
    functionHeader(__func__, CURRENTTOKEN);

    getIn();
    if (match(__func__, CURRENTTOKEN, "ret")) {
        nextToken();
        IDENTIFIER();
    } else {
        std::cerr << TOKEN_METADATA << "Expected ret, but found " << CURRENTTOKEN << " instead."
                  << std::endl;
        exit(1);
    }
    getOut();
}

