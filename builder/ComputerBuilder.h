#ifndef COMPUTER_BUILDER_H
#define COMPUTER_BUILDER_H

#include "Computer.h"
#include "../factories/ComponentFactory.h"

class ComputerBuilder {
protected:
    Computer* computer;
    const ComponentFactory* factory;
    
public:
    ComputerBuilder(const ComponentFactory* f = nullptr) : factory(f) {
        computer = new Computer();
    }
    
    virtual ~ComputerBuilder() {
        delete computer;
    }
    
    void setFactory(const ComponentFactory* f) {
        factory = f;
    }
    
    virtual void buildComputerType() = 0;
    virtual void addCPU() {
        if (factory) computer->setCPU(factory->createCPU());
    }
    virtual void addMotherboard() {
        if (factory) computer->setMotherboard(factory->createMotherboard());
    }
    virtual void addRAM() {
        if (factory) computer->addRAM(factory->createRAM());
    }
    virtual void addGPU() {
        if (factory) computer->setGPU(factory->createGPU());
    }
    virtual void addStorage() {
        if (factory) computer->addStorage(factory->createStorage());
    }
    virtual void addPowerSupply() {
        if (factory) computer->setPSU(factory->createPowerSupply());
    }
    virtual void addCooling() {
        if (factory) computer->setCooling(factory->createCooling());
    }
    virtual void addPeripherals() = 0;
    
    Computer* getComputer() {
        Computer* result = computer;
        computer = new Computer();
        return result;
    }
    
    void reset() {
        delete computer;
        computer = new Computer();
    }
};

class GamingPCBuilder : public ComputerBuilder {
public:
    GamingPCBuilder(const ComponentFactory* f) : ComputerBuilder(f) {}
    
    void buildComputerType() override {
        computer->setName("Gaming Beast");
        computer->setType("Gaming PC");
    }
    
    void addPeripherals() override {
        computer->addPeripheral(new Peripheral("ASUS ROG Swift PG32UQX", "ASUS",
                                               "Monitor", "DisplayPort"));
        computer->addPeripheral(new Peripheral("Razer Huntsman V2", "Razer",
                                               "Keyboard", "USB"));
        computer->addPeripheral(new Peripheral("Logitech G502 X Plus", "Logitech",
                                               "Mouse", "USB"));
    }
};

class WorkstationBuilder : public ComputerBuilder {
public:
    WorkstationBuilder(const ComponentFactory* f) : ComputerBuilder(f) {}
    
    void buildComputerType() override {
        computer->setName("Professional Workstation");
        computer->setType("Workstation");
    }
    
    void addRAM() override {
        if (factory) {
            for (int i = 0; i < 4; i++) {
                computer->addRAM(factory->createRAM());
            }
        }
    }
    
    void addPeripherals() override {
        computer->addPeripheral(new Peripheral("Dell UltraSharp U4323QE", "Dell",
                                               "Monitor", "USB-C"));
        computer->addPeripheral(new Peripheral("Logitech MX Mechanical", "Logitech",
                                               "Keyboard", "Bluetooth"));
        computer->addPeripheral(new Peripheral("Logitech MX Master 3S", "Logitech",
                                               "Mouse", "Bluetooth"));
    }
};

class ServerBuilder : public ComputerBuilder {
public:
    ServerBuilder(const ComponentFactory* f) : ComputerBuilder(f) {}
    
    void buildComputerType() override {
        computer->setName("Enterprise Server");
        computer->setType("Server");
    }
    
    void addRAM() override {
        if (factory) {
            for (int i = 0; i < 8; i++) {
                computer->addRAM(factory->createRAM());
            }
        }
    }
    
    void addGPU() override {
    }
    
    void addPeripherals() override {
    }
};

#endif