#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <iostream>

class Component {
protected:
    std::string name;
    double price;
    std::string manufacturer;
    
public:
    Component(const std::string& n, double p, const std::string& m = "Unknown")
        : name(n), price(p), manufacturer(m) {}
    
    virtual ~Component() = default;
    
    virtual std::string getName() const { return name; }
    virtual double getPrice() const { return price; }
    virtual std::string getManufacturer() const { return manufacturer; }
    virtual std::string getSpecs() const = 0;
    virtual std::string getType() const = 0;
    
    void setPrice(double p) { price = p; }
};

#endif