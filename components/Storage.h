#ifndef STORAGE_H
#define STORAGE_H

#include "Component.h"

class Storage : public Component {
private:
    int capacityGB;
    std::string type; 
    int readSpeed;
    int writeSpeed;
    
public:
    Storage(const std::string& n, double p, const std::string& m,
            int cap, const std::string& t, int rSpeed, int wSpeed)
        : Component(n, p, m), capacityGB(cap), type(t), readSpeed(rSpeed), writeSpeed(wSpeed) {}
    
    std::string getSpecs() const override {
        return "Storage: " + name + " (" + std::to_string(capacityGB) + "GB " + type +
               ", R:" + std::to_string(readSpeed) + "MB/s, W:" + std::to_string(writeSpeed) + "MB/s)";
    }
    
    std::string getType() const override { return "Storage"; }
    
    std::string getStorageType() const { return type; }
    int getCapacity() const { return capacityGB; }
};

#endif