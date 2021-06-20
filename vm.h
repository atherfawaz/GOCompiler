//
// Created by Mujtaba on 6/20/2021.
//

#ifndef MAIN_CPP_VM_H
#define MAIN_CPP_VM_H

#endif //MAIN_CPP_VM_H

#include "Tac-Mac.h"

namespace VirtualMachine{

    class VirtualMachine{


    private:
        machineTranslator::translator code;

    public:
        VirtualMachine(const std::string &tac_file, const std::string &mac_file);
        ~VirtualMachine();

        void execute();













    };


}

