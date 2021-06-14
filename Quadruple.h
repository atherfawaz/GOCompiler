//
// Created by ather on 14-Jun-21.
//

#ifndef MAIN_CPP_QUADRUPLE_H
#define MAIN_CPP_QUADRUPLE_H

namespace Assembler {
    class Quadruple {
    private:
        int opcode{};
        int firstOperand{};
        int secondOperand{};
        int resultOperand{};
    public:
        Quadruple();
        Quadruple(int opcode, int foperand, int soperand, int resoperand);
        ~Quadruple();
    };
}


#endif //MAIN_CPP_QUADRUPLE_H
