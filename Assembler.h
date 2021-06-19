//
// Created by ather on 14-Jun-21.
//

#ifndef MAIN_CPP_ASSEMBLER_H
#define MAIN_CPP_ASSEMBLER_H

#include <string>
#include <unordered_map>
#include <vector>
#include "Quadruple.h"

namespace Assembler {
    enum OPCODE {
        GOTO,
        WHILEIF,
        IF,
        ELIF,
        ELSE,
        SUMTHREELEFTIDENRIGHTIDEN,
        SUBTHREE,
        MULTHREE,
        DIVTHREE,
        ASSIGN,
        CONSOLEIN,
        CONSOLEOUT,
    };

    class Assembler {
    private:
        std::vector<std::string> tacs;
        std::vector<Quadruple> quadruples;
        std::unordered_map<std::string, int> dataSegment;
        int programCounter = 0;
    public:
        Assembler();

        ~Assembler();

        static std::vector<std::string> splitByDelimiter(std::string toSplit, const std::string &delim);

        void buildTacArray(const std::string &filePath);

        void buildDataSegment(const std::string &filePath);

        void runAssembler();

        void processQuadruple(std::vector<std::string> words);

        bool handleRelationalOperator(const std::string &op, const std::string &lop, const std::string &rop);

        void generateMachineCode();
    };
}


#endif //MAIN_CPP_ASSEMBLER_H
