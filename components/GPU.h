#ifndef GPU_H
#define GPU_H

#include "Component.h"
#include "../core/PriceCatalog.h"

class GPU : public Component {
private:
    int vramGB;
    std::string vramType;
    int cudaCores;
    bool isProfessional;
    
public:
    GPU(const std::string& n, const std::string& m, int vram, 
        const std::string& vType, int cores, bool prof = false)
        : Component(n, m), vramGB(vram), vramType(vType), cudaCores(cores), isProfessional(prof) {}
    
    GPU(const GPU& other)
        : Component(other), vramGB(other.vramGB), vramType(other.vramType),
          cudaCores(other.cudaCores), isProfessional(other.isProfessional) {}
    
    double getPrice() const override {
        return PriceCatalog::getInstance()->getPrice(name);
    }
    
    std::string getSpecs() const override {
        return "GPU: " + name + " (" + std::to_string(vramGB) + "GB " + vramType +
               ", " + std::to_string(cudaCores) + " cores" + 
               (isProfessional ? ", Professional" : "") + ")";
    }
    
    std::string getType() const override { return "GPU"; }
    
    int getVRAM() const { return vramGB; }
    bool isProfessionalGPU() const { return isProfessional; }
};

#endif