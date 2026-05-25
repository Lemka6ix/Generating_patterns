#ifndef STORAGE_H
#define STORAGE_H

#include "Component.h"
#include "../core/PriceCatalog.h"

class Storage : public Component {
private:
    int capacityGB;
    std::string type;
    int readSpeed;
    int writeSpeed;
    
public:
    Storage(const std::string& n, const std::string& m, int cap, 
            const std::string& t, int rSpeed, int wSpeed)
        : Component(n, m), capacityGB(cap), type(t), readSpeed(rSpeed), writeSpeed(wSpeed) {}
    
    Storage(const Storage& other)
        : Component(other), capacityGB(other.capacityGB), type(other.type),
          readSpeed(other.readSpeed), writeSpeed(other.writeSpeed) {}
    
    double getPrice() const override {
        return PriceCatalog::getInstance()->getPrice(name);
    }
    
    std::string getSpecs() const override {
        return "Storage: " + name + " (" + std::to_string(capacityGB) + "GB " + type +
               ", R:" + std::to_string(readSpeed) + "MB/s, W:" + std::to_string(writeSpeed) + "MB/s)";
    }
    
    std::string getType() const override { return "Storage"; }
    
    std::string getStorageType() const { return type; }
    int getCapacity() const { return capacityGB; }
};

#endif