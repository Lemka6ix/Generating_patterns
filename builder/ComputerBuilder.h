#ifndef COMPUTER_BUILDER_H
#define COMPUTER_BUILDER_H

#include "Computer.h"

class ComputerBuilder {
protected:
    Computer* computer;
    
public:
    ComputerBuilder() {
        computer = new Computer();
    }
    
    virtual ~ComputerBuilder() {
        delete computer;
    }
    
    virtual void buildComputerType() = 0;
    virtual void addCPU() = 0;
    virtual void addMotherboard() = 0;
    virtual void addRAM() = 0;
    virtual void addGPU() = 0;
    virtual void addStorage() = 0;
    virtual void addPowerSupply() = 0;
    virtual void addCooling() = 0;
    virtual void addPeripherals() = 0;
    
    Computer* getComputer() {
        Computer* result = computer;
        computer = new Computer();
        return result;
    }
    
    void reset() {
        delete computer;
        computer = new Computer();
    }
};

// Concrete Builder for Gaming PC
class GamingPCBuilder : public ComputerBuilder {
public:
    void buildComputerType() override {
        computer->setName("Gaming Beast");
        computer->setType("Gaming PC");
    }
    
    void addCPU() override {
        computer->setCPU(new CPU("Intel Core i9-13900K", 580.0, "Intel", 
                                 24, 5.8, "LGA1700", 125, true));
    }
    
    void addMotherboard() override {
        computer->setMotherboard(new Motherboard("ASUS ROG MAXIMUS Z790", 520.0, "ASUS",
                                                  "LGA1700", "Z790", "DDR5", 128, 4, 3, "ATX"));
    }
    
    void addRAM() override {
        computer->addRAM(new RAM("Corsair Dominator DDR5", 220.0, "Corsair",
                                 32, "DDR5", 6400, false));
        computer->addRAM(new RAM("Corsair Dominator DDR5", 220.0, "Corsair",
                                 32, "DDR5", 6400, false));
    }
    
    void addGPU() override {
        computer->setGPU(new GPU("NVIDIA RTX 4090", 1650.0, "NVIDIA",
                                 24, "GDDR6X", 16384, false));
    }
    
    void addStorage() override {
        computer->addStorage(new Storage("Samsung 990 Pro", 180.0, "Samsung",
                                         2000, "NVMe", 7450, 6900));
        computer->addStorage(new Storage("Samsung 870 EVO", 120.0, "Samsung",
                                         2000, "SSD", 560, 530));
    }
    
    void addPowerSupply() override {
        computer->setPSU(new PowerSupply("Corsair HX1200", 280.0, "Corsair",
                                         1200, "80+ Platinum", true));
    }
    
    void addCooling() override {
        computer->setCooling(new Cooling("Corsair iCUE H150i", 200.0, "Corsair",
                                         "Liquid", 250, 3));
    }
    
    void addPeripherals() override {
        computer->addPeripheral(new Peripheral("ASUS ROG Swift PG32UQX", 2800.0, "ASUS",
                                               "Monitor", "DisplayPort"));
        computer->addPeripheral(new Peripheral("Razer Huntsman V2", 200.0, "Razer",
                                               "Keyboard", "USB"));
        computer->addPeripheral(new Peripheral("Logitech G502 X Plus", 150.0, "Logitech",
                                               "Mouse", "USB"));
    }
};

// Concrete Builder for Workstation
class WorkstationBuilder : public ComputerBuilder {
public:
    void buildComputerType() override {
        computer->setName("Professional Workstation");
        computer->setType("Workstation");
    }
    
    void addCPU() override {
        computer->setCPU(new CPU("AMD Ryzen Threadripper 7980X", 2500.0, "AMD",
                                 64, 5.1, "sTR5", 350, false));
    }
    
    void addMotherboard() override {
        computer->setMotherboard(new Motherboard("ASUS Pro WS TRX50", 850.0, "ASUS",
                                                  "sTR5", "TRX50", "DDR5", 2048, 8, 5, "E-ATX"));
    }
    
    void addRAM() override {
        computer->addRAM(new RAM("Kingston Server Premier", 450.0, "Kingston",
                                 64, "DDR5", 5600, true));
        computer->addRAM(new RAM("Kingston Server Premier", 450.0, "Kingston",
                                 64, "DDR5", 5600, true));
        computer->addRAM(new RAM("Kingston Server Premier", 450.0, "Kingston",
                                 64, "DDR5", 5600, true));
        computer->addRAM(new RAM("Kingston Server Premier", 450.0, "Kingston",
                                 64, "DDR5", 5600, true));
    }
    
    void addGPU() override {
        computer->setGPU(new GPU("NVIDIA RTX 6000 Ada", 6800.0, "NVIDIA",
                                 48, "GDDR6", 18176, true));
    }
    
    void addStorage() override {
        computer->addStorage(new Storage("Samsung PM9A3", 450.0, "Samsung",
                                         4000, "NVMe", 7000, 5100));
        computer->addStorage(new Storage("Samsung PM9A3", 450.0, "Samsung",
                                         4000, "NVMe", 7000, 5100));
    }
    
    void addPowerSupply() override {
        computer->setPSU(new PowerSupply("Seasonic Prime TX-1600", 550.0, "Seasonic",
                                         1600, "80+ Titanium", true));
    }
    
    void addCooling() override {
        computer->setCooling(new Cooling("Arctic Liquid Freezer III 420", 150.0, "Arctic",
                                         "Liquid", 400, 3));
    }
    
    void addPeripherals() override {
        computer->addPeripheral(new Peripheral("Dell UltraSharp U4323QE", 1150.0, "Dell",
                                               "Monitor", "USB-C"));
        computer->addPeripheral(new Peripheral("Logitech MX Mechanical", 170.0, "Logitech",
                                               "Keyboard", "Bluetooth"));
        computer->addPeripheral(new Peripheral("Logitech MX Master 3S", 100.0, "Logitech",
                                               "Mouse", "Bluetooth"));
    }
};

// Concrete Builder for Server
class ServerBuilder : public ComputerBuilder {
public:
    void buildComputerType() override {
        computer->setName("Enterprise Server");
        computer->setType("Server");
    }
    
    void addCPU() override {
        computer->setCPU(new CPU("Intel Xeon Platinum 8480+", 5200.0, "Intel",
                                 56, 3.8, "LGA4677", 350, false));
    }
    
    void addMotherboard() override {
        computer->setMotherboard(new Motherboard("SuperMicro X13DEM", 1200.0, "SuperMicro",
                                                  "LGA4677", "C741", "DDR5", 4096, 16, 4, "EE-ATX"));
    }
    
    void addRAM() override {
        for (int i = 0; i < 8; i++) {
            computer->addRAM(new RAM("Samsung RDIMM", 380.0, "Samsung",
                                     64, "DDR5", 4800, true));
        }
    }
    
    void addGPU() override {
        // Servers may not need GPU, optional
    }
    
    void addStorage() override {
        computer->addStorage(new Storage("Intel Optane P5800X", 1200.0, "Intel",
                                         800, "NVMe", 7200, 6200));
        computer->addStorage(new Storage("Seagate Exos X20", 350.0, "Seagate",
                                         20000, "HDD", 285, 275));
        computer->addStorage(new Storage("Seagate Exos X20", 350.0, "Seagate",
                                         20000, "HDD", 285, 275));
    }
    
    void addPowerSupply() override {
        computer->setPSU(new PowerSupply("Delta Electronics 2400W", 650.0, "Delta",
                                         2400, "80+ Platinum", true));
    }
    
    void addCooling() override {
        computer->setCooling(new Cooling("Noctua NH-U14S", 85.0, "Noctua",
                                         "Air", 250, 2));
    }
    
    void addPeripherals() override {
        // Servers typically don't include peripherals
    }
};

#endif