#ifndef DIRECTOR_H
#define DIRECTOR_H

#include "ComputerBuilder.h"

class Director {
private:
    ComputerBuilder* builder;
    
public:
    Director(ComputerBuilder* b) : builder(b) {}
    
    Computer* constructCompleteComputer() {
        builder->buildComputerType();
        builder->addCPU();
        builder->addMotherboard();
        builder->addRAM();
        builder->addGPU();
        builder->addStorage();
        builder->addPowerSupply();
        builder->addCooling();
        builder->addPeripherals();
        return builder->getComputer();
    }
};

#endif