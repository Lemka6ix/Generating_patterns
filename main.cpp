#include "builder/ComputerBuilder.h"
#include "builder/Director.h"
#include "factories/ComponentFactory.h"
#include "core/PriceCatalog.h"
#include "prototype/PresetManager.h"
#include <iostream>

class TestRunner {
private:
    int passed = 0, failed = 0;
    
public:
    void assertTrue(bool condition, const std::string& testName) {
        if (condition) {
            std::cout << "OK: " << testName << std::endl;
            passed++;
        } else {
            std::cout << "ERROR: " << testName << " - Assertion failed" << std::endl;
            failed++;
        }
    }
    
    void printResults() {
        std::cout << "\n TEST RESULTS: " << passed << " passed, " << failed << " failed " << std::endl;
    }
};

void testFactoryPattern() {
    std::cout << "\nTesting Factory Pattern " << std::endl;
    TestRunner runner;
    
    IntelFactory intelFactory;
    CPU* intelCPU = intelFactory.createCPU();
    Motherboard* intelMB = intelFactory.createMotherboard();
    runner.assertTrue(intelCPU->getSocket() == intelMB->getSocket(), 
                     "Intel CPU and Motherboard socket compatibility");
    delete intelCPU;
    delete intelMB;
    
    AMDFactory amdFactory;
    CPU* amdCPU = amdFactory.createCPU();
    Motherboard* amdMB = amdFactory.createMotherboard();
    runner.assertTrue(amdCPU->getSocket() == amdMB->getSocket(),
                     "AMD CPU and Motherboard socket compatibility");
    delete amdCPU;
    delete amdMB;
    
    runner.printResults();
}

void testSingletonPattern() {
    std::cout << "\n Testing Singleton Pattern " << std::endl;
    TestRunner runner;
    
    PriceCatalog* catalog1 = PriceCatalog::getInstance();
    PriceCatalog* catalog2 = PriceCatalog::getInstance();
    runner.assertTrue(catalog1 == catalog2, "Singleton returns same instance");
    
    double price = catalog1->getPrice("Intel Core i9-13900K");
    runner.assertTrue(price == 580.0, "Correct price retrieval");
    
    runner.printResults();
}

void testPrototypePattern() {
    std::cout << "\nTesting Prototype Pattern " << std::endl;
    TestRunner runner;
    
    PresetManager* pm = PresetManager::getInstance();
    
    IntelFactory factory;
    GamingPCBuilder builder(&factory);
    Director director(&builder);
    Computer* original = director.constructCompleteComputer();
    
    bool saved = pm->savePreset("test_gaming_pc", original);
    runner.assertTrue(saved, "Save preset operation");
    
    runner.assertTrue(pm->hasPreset("test_gaming_pc"), "Preset exists after save");
    
    Computer* loaded = pm->loadPreset("test_gaming_pc");
    runner.assertTrue(loaded != nullptr, "Load preset returns valid computer");
    runner.assertTrue(loaded != original, "Loaded computer is different instance from original");
    
    if (loaded && loaded->cpu) {
        runner.assertTrue(loaded->cpu != original->cpu, "CPU objects are different (deep copy)");
    }
    
    pm->deletePreset("test_gaming_pc");
    runner.assertTrue(!pm->hasPreset("test_gaming_pc"), "Preset deleted successfully");
    
    delete original;
    delete loaded;
    runner.printResults();
}

int main() {
    
    PriceCatalog::getInstance()->printCatalog();
    
    testFactoryPattern();
    testSingletonPattern();
    testPrototypePattern();
    
    std::cout << "\n>>> DEMONSTRATION: Building and Saving Presets <<<" << std::endl;
    
    PresetManager* presetMgr = PresetManager::getInstance();
    
    IntelFactory intelFactory;
    GamingPCBuilder gamingBuilder(&intelFactory);
    Director gamingDirector(&gamingBuilder);
    Computer* gamingPC = gamingDirector.constructCompleteComputer();
    gamingPC->printSpecification();
    presetMgr->savePreset("My Gaming PC", gamingPC);
    delete gamingPC;
    
    AMDFactory amdFactory;
    WorkstationBuilder wsBuilder(&amdFactory);
    Director wsDirector(&wsBuilder);
    Computer* workstation = wsDirector.constructCompleteComputer();
    workstation->printSpecification();
    presetMgr->savePreset("My Workstation", workstation);
    delete workstation;
    
    std::cout << "\n>>> Loading and Displaying Presets <<<" << std::endl;
    Computer* loadedGaming = presetMgr->loadPreset("My Gaming PC");
    if (loadedGaming) {
        loadedGaming->printSpecification();
        delete loadedGaming;
    }
    
    presetMgr->listPresets();
    
    PresetManager::destroyInstance();
    PriceCatalog::destroyInstance();
    

    std::cout << "PROGRAM FINISHED" << std::endl;
    
    return 0;
}