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
    
    CPU* cpu;
    Motherboard* motherboard;
    std::vector<RAM*> ramModules;
    GPU* gpu;
    std::vector<Storage*> storageDevices;
    PowerSupply* psu;
    Cooling* cooling;
    std::vector<Peripheral*> peripherals;
    
public:
    Computer() : cpu(nullptr), motherboard(nullptr), gpu(nullptr), psu(nullptr), cooling(nullptr) {}
    
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
        

        for (auto ram : ramModules) {
            if (ram->getTypeName() != motherboard->getRAMType()) return false;
        }

        if (psu && cpu) {
            int totalTDP = cpu->getTDP();
            if (gpu) totalTDP += 200; 
            if (psu->getWattage() < totalTDP) return false;
        }
        

        if (cooling && cpu) {
            if (cooling->getTDPMax() < cpu->getTDP()) return false;
        }
        
        return true;
    }
    
    void printSpecification() const {
        std::cout << " " << name << " (" << computerType << ")\n";

        
        if (cpu) std::cout << "  " << cpu->getSpecs() << "\n";
        if (motherboard) std::cout << "  " << motherboard->getSpecs() << "\n";
        
        for (auto ram : ramModules) 
            std::cout << "  " << ram->getSpecs() << "\n";
        
        if (gpu) std::cout << "  " << gpu->getSpecs() << "\n";
        
        for (auto storage : storageDevices) 
            std::cout << "  " << storage->getSpecs() << "\n";
        
        if (psu) std::cout << "  " << psu->getSpecs() << "\n";
        if (cooling) std::cout << "  " << cooling->getSpecs() << "\n";
        
        for (auto peripheral : peripherals) 
            std::cout << "  " << peripheral->getSpecs() << "\n";
        std::cout << "  Total Price: $" << calculateTotalPrice() << "\n";
        std::cout << "  Compatible: " << (validateCompatibility() ? "YES" : "NO") << "\n";
    }
};

#endif