#ifndef CPU_H
#define CPU_H

#include "Component.h"
#include "../core/PriceCatalog.h"

class CPU : public Component {
private:
    std::string socket;
    int cores;
    double frequency;
    int tdp;
    bool hasIntegratedGraphics;
    
public:
    CPU(const std::string& n, const std::string& s, const std::string& m,
        int c, double f, int tdpW, bool igfx)
        : Component(n, m), socket(s), cores(c), frequency(f), tdp(tdpW), hasIntegratedGraphics(igfx) {}
    
    CPU(const CPU& other)
        : Component(other), socket(other.socket), cores(other.cores),
          frequency(other.frequency), tdp(other.tdp), hasIntegratedGraphics(other.hasIntegratedGraphics) {}
    
    double getPrice() const override {
        return PriceCatalog::getInstance()->getPrice(name);
    }
    
    std::string getSpecs() const override {
        return "CPU: " + name + " (" + std::to_string(cores) + " cores, " +
               std::to_string(frequency) + "GHz, " + socket + ", " + std::to_string(tdp) + "W)";
    }
    
    std::string getType() const override { return "CPU"; }
    
    std::string getSocket() const override { return socket; }
    int getCores() const { return cores; }
    double getFrequency() const { return frequency; }
    int getTDP() const { return tdp; }
    bool hasIGPU() const { return hasIntegratedGraphics; }
};

#endif