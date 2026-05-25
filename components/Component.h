#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <iostream>

class Component {
protected:
    std::string name;
    std::string manufacturer;
    
public:
    Component(const std::string& n, const std::string& m = "Unknown")
        : name(n), manufacturer(m) {}
    
    virtual ~Component() = default;
    
    virtual std::string getName() const { return name; }
    virtual double getPrice() const = 0;
    virtual std::string getManufacturer() const { return manufacturer; }
    virtual std::string getSpecs() const = 0;
    virtual std::string getType() const = 0;
    virtual std::string getSocket() const { return ""; }
    
    void setManufacturer(const std::string& m) { manufacturer = m; }
};

#endif