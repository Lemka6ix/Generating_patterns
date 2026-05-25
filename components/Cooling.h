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
    
    Cooling(const Cooling& other)
        : Component(other), type(other.type), tdpCapacity(other.tdpCapacity),
          fanCount(other.fanCount) {}
    
    std::string getSpecs() const override {
        return "Cooling: " + name + " (" + type + ", " + std::to_string(tdpCapacity) + "W TDP)";
    }
    
    std::string getType() const override { return "Cooling"; }
    
    int getTDPMax() const { return tdpCapacity; }
};

#endif