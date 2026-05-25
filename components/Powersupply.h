#ifndef POWERSUPPLY_H
#define POWERSUPPLY_H

#include "Component.h"
#include "../core/PriceCatalog.h"

class PowerSupply : public Component {
private:
    int wattage;
    std::string efficiency;
    bool isModular;
    
public:
    PowerSupply(const std::string& n, const std::string& m, int watts, 
                const std::string& eff, bool modular)
        : Component(n, m), wattage(watts), efficiency(eff), isModular(modular) {}
    
    PowerSupply(const PowerSupply& other)
        : Component(other), wattage(other.wattage), efficiency(other.efficiency),
          isModular(other.isModular) {}
    
    double getPrice() const override {
        return PriceCatalog::getInstance()->getPrice(name);
    }
    
    std::string getSpecs() const override {
        return "PSU: " + name + " (" + std::to_string(wattage) + "W, " + efficiency +
               (isModular ? ", Modular" : ", Non-modular") + ")";
    }
    
    std::string getType() const override { return "PowerSupply"; }
    
    int getWattage() const { return wattage; }
};

#endif