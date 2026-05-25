#ifndef MOTHERBOARD_H
#define MOTHERBOARD_H

#include "Component.h"
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
    
public:
    Motherboard(const std::string& n, double p, const std::string& m,
                const std::string& s, const std::string& cs, const std::string& rt,
                int maxR, int rSlots, int pcie, const std::string& ff)
        : Component(n, p, m), socket(s), chipset(cs), ramType(rt), maxRAM(maxR),
          ramSlots(rSlots), pcieSlots(pcie), formFactor(ff) {}
    
    Motherboard(const Motherboard& other)
        : Component(other), socket(other.socket), chipset(other.chipset),
          ramType(other.ramType), maxRAM(other.maxRAM), ramSlots(other.ramSlots),
          pcieSlots(other.pcieSlots), formFactor(other.formFactor) {}
    
    std::string getSpecs() const override {
        return "Motherboard: " + name + " (" + socket + ", " + chipset + 
               ", " + ramType + ", max " + std::to_string(maxRAM) + "GB, " + formFactor + ")";
    }
    
    std::string getType() const override { return "Motherboard"; }
    
    std::string getSocket() const { return socket; }
    std::string getRAMType() const { return ramType; }
    int getMaxRAM() const { return maxRAM; }
};

#endif