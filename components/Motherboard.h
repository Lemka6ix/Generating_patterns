#ifndef MOTHERBOARD_H
#define MOTHERBOARD_H

#include "Component.h"
#include "../core/PriceCatalog.h"
#include <vector>

class Motherboard : public Component {
private:
    std::string socket;
    std::string chipset;
    std::string ramType;
    int maxRAM;
    int ramSlots;
    int pcieSlots;
    std::string formFactor;
    std::vector<std::string> storageInterfaces;
    
public:
    Motherboard(const std::string& n, const std::string& s, const std::string& m,
                const std::string& cs, const std::string& rt, int maxR, 
                int rSlots, int pcie, const std::string& ff)
        : Component(n, m), socket(s), chipset(cs), ramType(rt), maxRAM(maxR),
          ramSlots(rSlots), pcieSlots(pcie), formFactor(ff) {
        storageInterfaces = {"SATA", "NVMe"};
    }
    
    Motherboard(const Motherboard& other)
        : Component(other), socket(other.socket), chipset(other.chipset),
          ramType(other.ramType), maxRAM(other.maxRAM), ramSlots(other.ramSlots),
          pcieSlots(other.pcieSlots), formFactor(other.formFactor),
          storageInterfaces(other.storageInterfaces) {}
    
    double getPrice() const override {
        return PriceCatalog::getInstance()->getPrice(name);
    }
    
    std::string getSpecs() const override {
        return "Motherboard: " + name + " (" + socket + ", " + chipset + 
               ", " + ramType + ", max " + std::to_string(maxRAM) + "GB, " + formFactor + ")";
    }
    
    std::string getType() const override { return "Motherboard"; }
    
    std::string getSocket() const override { return socket; }
    std::string getRAMType() const { return ramType; }
    int getMaxRAM() const { return maxRAM; }
    int getRAMSlots() const { return ramSlots; }
    std::string getFormFactor() const { return formFactor; }
};

#endif