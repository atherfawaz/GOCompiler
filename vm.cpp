
//
// Created by Mujtaba on 6/20/2021.
//

#include <iostream>
#include "vm.h"


VirtualMachine::VirtualMachine::VirtualMachine(const std::string &tac_file, const std::string &mac_file) : code(tac_file, mac_file){
    code.generateMacCode();
}

VirtualMachine::VirtualMachine::~VirtualMachine() {}

void VirtualMachine::VirtualMachine::execute() {

    int programCounter = 0;
    std::vector<int>instruction;
    int opCode;
    while (programCounter < code.instructions.size()){
        instruction = code.instructions[programCounter++];
        opCode = instruction[0];

        switch (opCode) {
            case 1:
                code.memory[instruction[2]] = code.memory[instruction[1]];
                break;
            case 2:
                code.memory[instruction[3]] = code.memory[instruction[2]] + code.memory[instruction[1]];
                break;
            case 3:
                code.memory[instruction[3]] = code.memory[instruction[2]] - code.memory[instruction[1]];
                break;
            case 4:
                code.memory[instruction[3]] = code.memory[instruction[2]] * code.memory[instruction[1]];
                break;
            case 5:
                code.memory[instruction[3]] = code.memory[instruction[2]] / code.memory[instruction[1]];
                break;
            case 6:
                if ( code.memory[1]  < code.memory[2] ) programCounter = code.memory[3] -1;
                break;
            case 7:
                if ( code.memory[1]  > code.memory[2] ) programCounter = code.memory[3] -1;
                break;
            case 8:
                if ( code.memory[1]  == code.memory[2] ) programCounter = code.memory[3] -1;
                break;
            case 9:
                if ( code.memory[1]  <= code.memory[2] ) programCounter = code.memory[3] -1;
                break;
            case 10:
                if ( code.memory[1]  >= code.memory[2] ) programCounter = code.memory[3] -1;
                break;
            case 11:
                std::cout << " Input some data(displaying for debugging purpose) \n";
                std::cin >> code.memory[1];
                break;
            case 12:
                std::cout << code.memory[1] << std::endl;
                break;
            case 13:
                programCounter = code.memory[1] -1;
                break;
            default:
                std::cout<< "wrong op code \n";
                break;
            
        }
        
        
        
    }
    
    
    
    
    
    
    }