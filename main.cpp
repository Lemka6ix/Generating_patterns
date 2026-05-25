
#include "builder/ComputerBuilder.h"
#include "builder/Director.h"
#include "factories/ComponentFactory.h"
#include <iostream>
#include <vector>
#include <functional>
#include <map>
#include <mutex>

class PriceCatalog {
private:
    static PriceCatalog* instance;
    static std::mutex mutex;
    std::map<std::string, double> prices;
    
    PriceCatalog() = default;
    PriceCatalog(const PriceCatalog&) = delete;
    PriceCatalog& operator=(const PriceCatalog&) = delete;
    
public:
    static PriceCatalog* getInstance() {
        std::lock_guard<std::mutex> lock(mutex);
        if (!instance) {
            instance = new PriceCatalog();
        }
        return instance;
    }
    
    static void destroyInstance() {
        std::lock_guard<std::mutex> lock(mutex);
        delete instance;
        instance = nullptr;
    }
    
    void setPrice(const std::string& componentName, double price) {
        prices[componentName] = price;
    }
    
    double getPrice(const std::string& componentName) const {
        auto it = prices.find(componentName);
        return (it != prices.end()) ? it->second : 0.0;
    }
    
    bool hasPrice(const std::string& componentName) const {
        return prices.find(componentName) != prices.end();
    }
    
    void loadDefaultPrices() {
        // Intel компоненты
        prices["Intel Core i7-13700K"] = 380.0;
        prices["Intel Core i9-13900K"] = 580.0;
        prices["ASUS ROG Z790"] = 320.0;
        prices["Corsair Vengeance DDR5"] = 180.0;
        prices["NVIDIA RTX 4080"] = 1250.0;
        prices["NVIDIA RTX 4090"] = 1650.0;
        
        // AMD компоненты
        prices["AMD Ryzen 9 7950X"] = 550.0;
        prices["AMD Ryzen 9 7950X3D"] = 699.0;
        prices["ASRock X670E"] = 280.0;
        prices["G.Skill Trident DDR5"] = 170.0;
        prices["AMD Radeon RX 7900 XTX"] = 1000.0;
        
        // Server компоненты
        prices["Intel Xeon Gold 6428R"] = 2800.0;
        prices["SuperMicro X13DEM"] = 1200.0;
        prices["Samsung RDIMM"] = 380.0;
        prices["NVIDIA A100"] = 11000.0;
        prices["Intel Optane P5800X"] = 1200.0;
        prices["Delta 2400W"] = 650.0;
        prices["Dynatron LGA4677"] = 180.0;
        
        // Storage
        prices["Samsung 980 Pro"] = 150.0;
        prices["WD Black SN850X"] = 160.0;
        
        // PSU
        prices["Corsair RM850x"] = 150.0;
        prices["EVGA SuperNOVA 1000 GT"] = 180.0;
        
        // Cooling
        prices["Corsair H100i"] = 150.0;
        prices["Noctua NH-D15"] = 110.0;
    }
    
    void printCatalog() const {

        std::cout << "              PRICE CATALOG                      \n";
        for (const auto& [name, price] : prices) {
            printf("  %-35s $%7.2f ║\n", name.c_str(), price);
        }
    }
    
    double calculateTotalCost(const std::vector<std::string>& components) const {
        double total = 0;
        for (const auto& comp : components) {
            total += getPrice(comp);
        }
        return total;
    }
};


PriceCatalog* PriceCatalog::instance = nullptr;
std::mutex PriceCatalog::mutex;

class TestRunner {
private:
    int passed = 0;
    int failed = 0;
    int warnings = 0;
    
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
    
    void assertWarning(bool condition, const std::string& testName) {
        if (condition) {
            std::cout << "WARNING: " << testName << std::endl;
            warnings++;
        } else {
            std::cout << "OK: " << testName << " (no warning)" << std::endl;
            passed++;
        }
    }
    
    void printResults() {
        std::cout << "\n=== TEST RESULTS: " << passed << " passed, " 
                  << failed << " failed, " << warnings << " warnings ===" << std::endl;
    }
};


void testSingletonPattern() {
    std::cout << "\n Testing Singleton Pattern \n";
    TestRunner runner;

    PriceCatalog* catalog1 = PriceCatalog::getInstance();
    PriceCatalog* catalog2 = PriceCatalog::getInstance();
    runner.assertTrue(catalog1 == catalog2, "Singleton returns same instance");
    
  
    double price = catalog1->getPrice("Intel Core i7-13700K");
    runner.assertTrue(price == 380.0, "Correct price retrieval for existing component");
    
    double unknownPrice = catalog1->getPrice("NonExistentComponent");
    runner.assertTrue(unknownPrice == 0.0, "Non-existent component returns 0");
    

    catalog1->setPrice("TestComponent", 99.99);
    runner.assertTrue(catalog1->getPrice("TestComponent") == 99.99, "Price update works");
    

    runner.assertTrue(catalog1->hasPrice("Intel Core i7-13700K"), "Component exists check");
    runner.assertTrue(!catalog1->hasPrice("FakeComponent"), "Non-existent component check");
    

    std::vector<std::string> components = {"Intel Core i7-13700K", "ASUS ROG Z790", "Corsair Vengeance DDR5"};
    double total = catalog1->calculateTotalCost(components);
    runner.assertTrue(total == 380.0 + 320.0 + 180.0, "Batch price calculation correct");
    
    runner.printResults();
}


void testFactoryPattern() {
    std::cout << "\n== Testing Factory Pattern \n";
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
    
    runner.assertTrue(intelFactory.createCPU()->getSocket() != amdFactory.createCPU()->getSocket(),
                     "Intel and AMD have different CPU sockets");
    
    Storage* storage = intelFactory.createStorage();
    runner.assertTrue(storage->getPrice() > 0, "Storage has valid price");
    delete storage;
    
    ServerFactory serverFactory;
    RAM* serverRAM = serverFactory.createRAM();
    runner.assertTrue(serverRAM->isECCCompatible(), "Server RAM supports ECC");
    delete serverRAM;
    
    runner.printResults();
}

int main() {
    
    // Инициализация PriceCatalog
    PriceCatalog::getInstance()->loadDefaultPrices();
    
    // Вывод каталога цен
    PriceCatalog::getInstance()->printCatalog();
    
    // Запуск тестов
    testSingletonPattern();
    testFactoryPattern();
    
    // Демонстрация сборки компьютеров
    std::cout << "\n>>> Building Computers with Different Platforms <<<\n";
    
    // Intel Gaming PC
    IntelFactory intelFactory;
    GamingPCBuilder intelGamingBuilder(&intelFactory);
    Director intelDirector(&intelGamingBuilder);
    Computer* intelPC = intelDirector.constructCompleteComputer();
    intelPC->printSpecification();
    delete intelPC;
    
    // AMD Workstation
    AMDFactory amdFactory;
    WorkstationBuilder amdWorkstationBuilder(&amdFactory);
    Director amdDirector(&amdWorkstationBuilder);
    Computer* amdWS = amdDirector.constructCompleteComputer();
    amdWS->printSpecification();
    delete amdWS;
    
    // Server with Xeon
    ServerFactory serverFactory;
    ServerBuilder serverBuilder(&serverFactory);
    Director serverDirector(&serverBuilder);
    Computer* server = serverDirector.constructCompleteComputer();
    server->printSpecification();
    delete server;
    
    // Очистка Singleton
    PriceCatalog::destroyInstance();

    std::cout << "PROGRAM FINISHED\n";
    
    return 0;
}