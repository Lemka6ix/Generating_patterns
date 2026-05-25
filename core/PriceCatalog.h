#ifndef PRICE_CATALOG_H
#define PRICE_CATALOG_H

#include <map>
#include <string>
#include <iostream>
#include <vector>

class PriceCatalog {
private:
    static PriceCatalog* instance;
    std::map<std::string, double> prices;
    
    PriceCatalog();
    PriceCatalog(const PriceCatalog&) = delete;
    PriceCatalog& operator=(const PriceCatalog&) = delete;
    
public:
    static PriceCatalog* getInstance();
    static void destroyInstance();
    
    void setPrice(const std::string& componentName, double price);
    double getPrice(const std::string& componentName) const;
    bool hasPrice(const std::string& componentName) const;
    void loadDefaultPrices();
    void printCatalog() const;
    double calculateTotalCost(const std::vector<std::string>& components) const;
};

#endif