#ifndef POWERSUPPLY_H
#define POWERSUPPLY_H

#include "Component.h"

class PowerSupply : public Component {
private:
    int wattage;
    std::string efficiency;
    bool isModular;
    
public:
    PowerSupply(const std::string& n, double p, const std::string& m,
                int watts, const std::string& eff, bool modular)
        : Component(n, p, m), wattage(watts), efficiency(eff), isModular(modular) {}
    
    std::string getSpecs() const override {
        return "PSU: " + name + " (" + std::to_string(wattage) + "W, " + efficiency +
               (isModular ? ", Modular" : ", Non-modular") + ")";
    }
    
    std::string getType() const override { return "PowerSupply"; }
    
    int getWattage() const { return wattage; }
};

#endif