#ifndef COMPUTER_H
#define COMPUTER_H

#include <vector>
#include <string>
#include <iostream>
#include "../components/CPU.h"
#include "../components/Motherboard.h"
#include "../components/RAM.h"
#include "../components/GPU.h"
#include "../components/Storage.h"
#include "../components/PowerSupply.h"
#include "../components/Cooling.h"
#include "../components/Peripheral.h"

class Computer {
private:
    std::string name;
    std::string computerType;
    
public:
    CPU* cpu;
    Motherboard* motherboard;
    std::vector<RAM*> ramModules;
    GPU* gpu;
    std::vector<Storage*> storageDevices;
    PowerSupply* psu;
    Cooling* cooling;
    std::vector<Peripheral*> peripherals;
    
    Computer() : cpu(nullptr), motherboard(nullptr), gpu(nullptr), psu(nullptr), cooling(nullptr) {}
    
    Computer(const Computer& other) 
        : name(other.name + " (copy)"), computerType(other.computerType),
          cpu(nullptr), motherboard(nullptr), gpu(nullptr), psu(nullptr), cooling(nullptr) {
        if (other.cpu) cpu = new CPU(*other.cpu);
        if (other.motherboard) motherboard = new Motherboard(*other.motherboard);
        if (other.gpu) gpu = new GPU(*other.gpu);
        if (other.psu) psu = new PowerSupply(*other.psu);
        if (other.cooling) cooling = new Cooling(*other.cooling);
        
        for (auto ram : other.ramModules) {
            if (ram) ramModules.push_back(new RAM(*ram));
        }
        for (auto storage : other.storageDevices) {
            if (storage) storageDevices.push_back(new Storage(*storage));
        }
        for (auto peripheral : other.peripherals) {
            if (peripheral) peripherals.push_back(new Peripheral(*peripheral));
        }
    }
    
    ~Computer() {
        delete cpu;
        delete motherboard;
        delete gpu;
        delete psu;
        delete cooling;
        for (auto ram : ramModules) delete ram;
        for (auto storage : storageDevices) delete storage;
        for (auto peripheral : peripherals) delete peripheral;
    }
    
    void setName(const std::string& n) { name = n; }
    void setType(const std::string& t) { computerType = t; }
    void setCPU(CPU* c) { cpu = c; }
    void setMotherboard(Motherboard* m) { motherboard = m; }
    void addRAM(RAM* r) { ramModules.push_back(r); }
    void setGPU(GPU* g) { gpu = g; }
    void addStorage(Storage* s) { storageDevices.push_back(s); }
    void setPSU(PowerSupply* p) { psu = p; }
    void setCooling(Cooling* c) { cooling = c; }
    void addPeripheral(Peripheral* p) { peripherals.push_back(p); }
    
    std::string getName() const { return name; }
    std::string getType() const { return computerType; }
    
    double calculateTotalPrice() const {
        double total = 0;
        if (cpu) total += cpu->getPrice();
        if (motherboard) total += motherboard->getPrice();
        if (gpu) total += gpu->getPrice();
        if (psu) total += psu->getPrice();
        if (cooling) total += cooling->getPrice();
        for (auto ram : ramModules) total += ram->getPrice();
        for (auto storage : storageDevices) total += storage->getPrice();
        for (auto peripheral : peripherals) total += peripheral->getPrice();
        return total;
    }
    
    bool validateCompatibility() const {
        if (!cpu || !motherboard) return false;
        if (cpu->getSocket() != motherboard->getSocket()) return false;
        return true;
    }
    
    void printSpecification() const {
        std::cout << "Computer: " << name << " (" << computerType << ")" << std::endl;
        if (cpu) std::cout << cpu->getSpecs() << std::endl;
        if (motherboard) std::cout << motherboard->getSpecs() << std::endl;
        for (auto ram : ramModules) std::cout << ram->getSpecs() << std::endl;
        if (gpu) std::cout << gpu->getSpecs() << std::endl;
        for (auto storage : storageDevices) std::cout << storage->getSpecs() << std::endl;
        if (psu) std::cout << psu->getSpecs() << std::endl;
        if (cooling) std::cout << cooling->getSpecs() << std::endl;
        for (auto peripheral : peripherals) std::cout << peripheral->getSpecs() << std::endl;
        std::cout << "Total Price: $" << calculateTotalPrice() << std::endl;
        std::cout << "Compatible: " << (validateCompatibility() ? "YES" : "NO") << std::endl;
    }
};

#endif