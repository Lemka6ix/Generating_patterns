#ifndef PERIPHERAL_H
#define PERIPHERAL_H

#include "Component.h"

class Peripheral : public Component {
private:
    std::string deviceType; // Monitor, Keyboard, Mouse
    std::string connection; // USB, Wireless, HDMI, DP
    
public:
    Peripheral(const std::string& n, double p, const std::string& m,
               const std::string& dType, const std::string& conn)
        : Component(n, p, m), deviceType(dType), connection(conn) {}
    
    std::string getSpecs() const override {
        return deviceType + ": " + name + " (" + connection + ")";
    }
    
    std::string getType() const override { return "Peripheral"; }
    
    std::string getDeviceType() const { return deviceType; }
};

#endif