#ifndef PERIPHERAL_H
#define PERIPHERAL_H

#include "Component.h"

class Peripheral : public Component {
private:
    std::string deviceType;
    std::string connection;
    
public:
    Peripheral(const std::string& n, double p, const std::string& m,
               const std::string& dType, const std::string& conn)
        : Component(n, p, m), deviceType(dType), connection(conn) {}
    
    Peripheral(const Peripheral& other)
        : Component(other), deviceType(other.deviceType), connection(other.connection) {}
    
    std::string getSpecs() const override {
        return deviceType + ": " + name + " (" + connection + ")";
    }
    
    std::string getType() const override { return "Peripheral"; }
    
    std::string getDeviceType() const { return deviceType; }
};

#endif