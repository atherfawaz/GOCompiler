//
// Created by ather on 14-Jun-21.
//

#include "Quadruple.h"

Assembler::Quadruple::Quadruple() = default;

Assembler::Quadruple::Quadruple(int opcode, int foperand, int soperand, int resoperand) {
    this->opcode = opcode;
    this->firstOperand = foperand;
    this->secondOperand = soperand;
    this->resultOperand = resoperand;
}

Assembler::Quadruple::~Quadruple() = default;
