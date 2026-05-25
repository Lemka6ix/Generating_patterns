#ifndef COMPONENT_FACTORY_H
#define COMPONENT_FACTORY_H

#include "../components/CPU.h"
#include "../components/Motherboard.h"
#include "../components/RAM.h"
#include "../components/GPU.h"
#include "../components/Storage.h"
#include "../components/PowerSupply.h"
#include "../components/Cooling.h"
#include "../components/Peripheral.h"

class ComponentFactory {
public:
    virtual ~ComponentFactory() = default;
    
    virtual CPU* createCPU() const = 0;
    virtual Motherboard* createMotherboard() const = 0;
    virtual RAM* createRAM() const = 0;
    virtual GPU* createGPU() const = 0;
    virtual Storage* createStorage() const = 0;
    virtual PowerSupply* createPowerSupply() const = 0;
    virtual Cooling* createCooling() const = 0;
    
    virtual std::string getPlatformName() const = 0;
};

class IntelFactory : public ComponentFactory {
public:
    CPU* createCPU() const override {
        return new CPU("Intel Core i9-13900K", "LGA1700", "Intel", 24, 5.8, 125, true);
    }
    
    Motherboard* createMotherboard() const override {
        return new Motherboard("ASUS ROG Z790", "LGA1700", "ASUS", "Z790", "DDR5", 128, 4, 3, "ATX");
    }
    
    RAM* createRAM() const override {
        return new RAM("Corsair Vengeance DDR5", "Corsair", 32, "DDR5", 5600, false);
    }
    
    GPU* createGPU() const override {
        return new GPU("NVIDIA RTX 4080", "NVIDIA", 16, "GDDR6X", 9728, false);
    }
    
    Storage* createStorage() const override {
        return new Storage("Samsung 980 Pro", "Samsung", 1000, "NVMe", 7000, 5100);
    }
    
    PowerSupply* createPowerSupply() const override {
        return new PowerSupply("Corsair RM850x", "Corsair", 850, "80+ Gold", true);
    }
    
    Cooling* createCooling() const override {
        return new Cooling("Corsair H100i", "Corsair", "Liquid", 200, 2);
    }
    
    std::string getPlatformName() const override { return "Intel Platform"; }
};

class AMDFactory : public ComponentFactory {
public:
    CPU* createCPU() const override {
        return new CPU("AMD Ryzen 9 7950X3D", "AM5", "AMD", 16, 5.7, 120, true);
    }
    
    Motherboard* createMotherboard() const override {
        return new Motherboard("ASRock X670E Taichi", "AM5", "ASRock", "X670E", "DDR5", 128, 4, 4, "ATX");
    }
    
    RAM* createRAM() const override {
        return new RAM("G.Skill Trident Z5", "G.Skill", 32, "DDR5", 6000, false);
    }
    
    GPU* createGPU() const override {
        return new GPU("AMD Radeon RX 7900 XTX", "AMD", 24, "GDDR6", 6144, false);
    }
    
    Storage* createStorage() const override {
        return new Storage("WD Black SN850X", "WD", 1000, "NVMe", 7300, 6600);
    }
    
    PowerSupply* createPowerSupply() const override {
        return new PowerSupply("EVGA SuperNOVA 1000 GT", "EVGA", 1000, "80+ Gold", true);
    }
    
    Cooling* createCooling() const override {
        return new Cooling("Noctua NH-D15", "Noctua", "Air", 250, 2);
    }
    
    std::string getPlatformName() const override { return "AMD Platform"; }
};

class ServerFactory : public ComponentFactory {
public:
    CPU* createCPU() const override {
        return new CPU("Intel Xeon Gold 6428R", "LGA4677", "Intel", 32, 3.5, 250, false);
    }
    
    Motherboard* createMotherboard() const override {
        return new Motherboard("SuperMicro X13DEM", "LGA4677", "SuperMicro", "C741", "DDR5", 4096, 16, 4, "EE-ATX");
    }
    
    RAM* createRAM() const override {
        return new RAM("Samsung RDIMM", "Samsung", 64, "DDR5", 4800, true);
    }
    
    GPU* createGPU() const override {
        return new GPU("NVIDIA A100", "NVIDIA", 80, "HBM2e", 6912, true);
    }
    
    Storage* createStorage() const override {
        return new Storage("Intel Optane P5800X", "Intel", 800, "NVMe", 7200, 6200);
    }
    
    PowerSupply* createPowerSupply() const override {
        return new PowerSupply("Delta 2400W", "Delta", 2400, "80+ Platinum", true);
    }
    
    Cooling* createCooling() const override {
        return new Cooling("Dynatron LGA4677", "Dynatron", "Air", 350, 2);
    }
    
    std::string getPlatformName() const override { return "Server Platform (Xeon)"; }
};

#endif