#include "PriceCatalog.h"

PriceCatalog* PriceCatalog::instance = nullptr;

PriceCatalog::PriceCatalog() {
    loadDefaultPrices();
}

PriceCatalog* PriceCatalog::getInstance() {
    if (!instance) {
        instance = new PriceCatalog();
    }
    return instance;
}

void PriceCatalog::destroyInstance() {
    delete instance;
    instance = nullptr;
}

void PriceCatalog::setPrice(const std::string& componentName, double price) {
    prices[componentName] = price;
}

double PriceCatalog::getPrice(const std::string& componentName) const {
    auto it = prices.find(componentName);
    return (it != prices.end()) ? it->second : 0.0;
}

bool PriceCatalog::hasPrice(const std::string& componentName) const {
    return prices.find(componentName) != prices.end();
}

void PriceCatalog::loadDefaultPrices() {
    // Intel компоненты
    prices["Intel Core i7-13700K"] = 380.0;
    prices["Intel Core i9-13900K"] = 580.0;
    prices["ASUS ROG Z790"] = 520.0;
    prices["Corsair Vengeance DDR5"] = 180.0;
    prices["NVIDIA RTX 4080"] = 1250.0;
    prices["NVIDIA RTX 4090"] = 1650.0;
    
    // AMD компоненты
    prices["AMD Ryzen 9 7950X"] = 550.0;
    prices["AMD Ryzen 9 7950X3D"] = 699.0;
    prices["ASRock X670E Taichi"] = 480.0;
    prices["G.Skill Trident Z5"] = 190.0;
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
    
    // Peripherals
    prices["ASUS ROG Swift PG32UQX"] = 2800.0;
    prices["Razer Huntsman V2"] = 200.0;
    prices["Logitech G502 X Plus"] = 150.0;
    prices["Dell UltraSharp U4323QE"] = 1150.0;
    prices["Logitech MX Mechanical"] = 170.0;
    prices["Logitech MX Master 3S"] = 100.0;
}

void PriceCatalog::printCatalog() const {
    std::cout << "              PRICE CATALOG                      \n";
    for (const auto& [name, price] : prices) {
        printf("║  %-35s $%8.2f ║\n", name.c_str(), price);
    }
}

double PriceCatalog::calculateTotalCost(const std::vector<std::string>& components) const {
    double total = 0;
    for (const auto& comp : components) {
        total += getPrice(comp);
    }
    return total;
}