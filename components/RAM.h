#ifndef RAM_H
#define RAM_H

#include "Component.h"

class RAM : public Component {
private:
    int sizeGB;
    std::string type;
    int frequency;
    bool isECC;
    
public:
    RAM(const std::string& n, double p, const std::string& m,
        int size, const std::string& t, int freq, bool ecc = false)
        : Component(n, p, m), sizeGB(size), type(t), frequency(freq), isECC(ecc) {}
    
    std::string getSpecs() const override {
        return "RAM: " + name + " (" + std::to_string(sizeGB) + "GB " + type +
               ", " + std::to_string(frequency) + "MHz" + (isECC ? ", ECC" : "") + ")";
    }
    
    std::string getType() const override { return "RAM"; }
    
    int getSize() const { return sizeGB; }
    std::string getTypeName() const { return type; }
    bool isECCCompatible() const { return isECC; }
};

#endif