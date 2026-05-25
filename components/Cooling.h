#ifndef COOLING_H
#define COOLING_H

#include "Component.h"

class Cooling : public Component {
private:
    std::string type; 
    int tdpCapacity;
    int fanCount;
    
public:
    Cooling(const std::string& n, double p, const std::string& m,
            const std::string& t, int tdp, int fans)
        : Component(n, p, m), type(t), tdpCapacity(tdp), fanCount(fans) {}
    
    std::string getSpecs() const override {
        return "Cooling: " + name + " (" + type + ", " + std::to_string(tdpCapacity) +
               "W TDP, " + std::to_string(fanCount) + " fans)";
    }
    
    std::string getType() const override { return "Cooling"; }
    
    int getTDPMax() const { return tdpCapacity; }
};

#endif