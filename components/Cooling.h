#ifndef COOLING_H
#define COOLING_H

#include "Component.h"
#include "../core/PriceCatalog.h"

class Cooling : public Component {
private:
    std::string type;
    int tdpCapacity;
    int fanCount;
    
public:
    Cooling(const std::string& n, const std::string& m, const std::string& t, 
            int tdp, int fans)
        : Component(n, m), type(t), tdpCapacity(tdp), fanCount(fans) {}
    
    Cooling(const Cooling& other)
        : Component(other), type(other.type), tdpCapacity(other.tdpCapacity),
          fanCount(other.fanCount) {}
    
    double getPrice() const override {
        return PriceCatalog::getInstance()->getPrice(name);
    }
    
    std::string getSpecs() const override {
        return "Cooling: " + name + " (" + type + ", " + std::to_string(tdpCapacity) +
               "W TDP, " + std::to_string(fanCount) + " fans)";
    }
    
    std::string getType() const override { return "Cooling"; }
    
    int getTDPMax() const { return tdpCapacity; }
};

#endif