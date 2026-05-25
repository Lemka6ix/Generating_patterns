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
};

class GamingPCBuilder : public ComputerBuilder {
public:
    GamingPCBuilder(const ComponentFactory* f) : ComputerBuilder(f) {}
    
    void buildComputerType() override {
        computer->setName("Gaming Beast");
        computer->setType("Gaming PC");
    }
    
    void addPeripherals() override {
        computer->addPeripheral(new Peripheral("ASUS ROG Swift Monitor", 2800.0, "ASUS", "Monitor", "DisplayPort"));
        computer->addPeripheral(new Peripheral("Razer Huntsman Keyboard", 200.0, "Razer", "Keyboard", "USB"));
        computer->addPeripheral(new Peripheral("Logitech G502 Mouse", 150.0, "Logitech", "Mouse", "USB"));
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
        computer->addPeripheral(new Peripheral("Dell UltraSharp Monitor", 1150.0, "Dell", "Monitor", "USB-C"));
        computer->addPeripheral(new Peripheral("Logitech MX Keyboard", 170.0, "Logitech", "Keyboard", "Bluetooth"));
        computer->addPeripheral(new Peripheral("Logitech MX Master Mouse", 100.0, "Logitech", "Mouse", "Bluetooth"));
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
    
    void addGPU() override {}
    void addPeripherals() override {}
};

#endif