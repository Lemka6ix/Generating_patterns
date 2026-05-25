#ifndef CPU_H
#define CPU_H

#include "Component.h"

class CPU : public Component {
private:
    int cores;
    double frequency;
    std::string socket;
    int tdp;
    bool hasIntegratedGraphics;
    
public:
    CPU(const std::string& n, double p, const std::string& m, 
        int c, double f, const std::string& s, int t = 65, bool igfx = false)
        : Component(n, p, m), cores(c), frequency(f), socket(s), tdp(t), hasIntegratedGraphics(igfx) {}
    
    CPU(const CPU& other)
        : Component(other), cores(other.cores), frequency(other.frequency),
          socket(other.socket), tdp(other.tdp), hasIntegratedGraphics(other.hasIntegratedGraphics) {}
    
    std::string getSpecs() const override {
        return "CPU: " + name + " (" + std::to_string(cores) + " cores, " +
               std::to_string(frequency) + "GHz, " + socket + ", " + std::to_string(tdp) + "W)";
    }
    
    std::string getType() const override { return "CPU"; }
    
    std::string getSocket() const { return socket; }
    int getCores() const { return cores; }
    double getFrequency() const { return frequency; }
    int getTDP() const { return tdp; }
};

#endif