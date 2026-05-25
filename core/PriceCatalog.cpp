/**
 * @file PriceCatalog.cpp
 * @brief Реализация класса PriceCatalog
 * @details Содержит реализацию методов синглтона PriceCatalog.
 *          Инициализирует цены по умолчанию для популярных компонентов.
 */
#include <iomanip>
#include "PriceCatalog.h"
#include <cstdio>

/// Инициализация статического члена класса
PriceCatalog* PriceCatalog::instance = nullptr;

/**
 * @brief Приватный конструктор, загружает цены по умолчанию
 */
PriceCatalog::PriceCatalog() {
    loadDefaultPrices();
}

/**
 * @brief Получение единственного экземпляра (ленивая инициализация)
 * @return Указатель на экземпляр PriceCatalog
 */
PriceCatalog* PriceCatalog::getInstance() {
    if (!instance) {
        instance = new PriceCatalog();
    }
    return instance;
}

/**
 * @brief Уничтожение экземпляра и освобождение памяти
 */
void PriceCatalog::destroyInstance() {
    delete instance;
    instance = nullptr;
}

/**
 * @brief Установка цены для компонента
 * @param componentName Название компонента
 * @param price Цена в долларах
 */
void PriceCatalog::setPrice(const std::string& componentName, double price) {
    prices[componentName] = price;
}

/**
 * @brief Получение цены компонента
 * @param componentName Название компонента
 * @return Цена в долларах или 0.0
 */
double PriceCatalog::getPrice(const std::string& componentName) const {
    auto it = prices.find(componentName);
    return (it != prices.end()) ? it->second : 0.0;
}

/**
 * @brief Проверка наличия цены
 * @param componentName Название компонента
 * @return true если цена существует
 */
bool PriceCatalog::hasPrice(const std::string& componentName) const {
    return prices.find(componentName) != prices.end();
}

/**
 * @brief Загрузка цен по умолчанию для всех компонентов
 */
void PriceCatalog::loadDefaultPrices() {
    // Процессоры Intel
    prices["Intel Core i7-13700K"] = 380.0;
    prices["Intel Core i9-13900K"] = 580.0;
    
    // Процессоры AMD
    prices["AMD Ryzen 9 7950X"] = 550.0;
    prices["AMD Ryzen 9 7950X3D"] = 699.0;
    
    // Материнские платы
    prices["ASUS ROG Z790"] = 520.0;
    prices["ASRock X670E Taichi"] = 480.0;
    
    // Оперативная память
    prices["Corsair Vengeance DDR5"] = 180.0;
    prices["G.Skill Trident Z5"] = 190.0;
    
    // Видеокарты
    prices["NVIDIA RTX 4080"] = 1250.0;
    prices["NVIDIA RTX 4090"] = 1650.0;
    prices["AMD Radeon RX 7900 XTX"] = 1000.0;
    
    // Серверные компоненты
    prices["Intel Xeon Gold 6428R"] = 2800.0;
    prices["SuperMicro X13DEM"] = 1200.0;
    prices["Samsung RDIMM"] = 380.0;
    prices["NVIDIA A100"] = 11000.0;
    prices["Intel Optane P5800X"] = 1200.0;
    prices["Delta 2400W"] = 650.0;
    prices["Dynatron LGA4677"] = 180.0;
    
    // Накопители
    prices["Samsung 980 Pro"] = 150.0;
    prices["WD Black SN850X"] = 160.0;
    
    // Блоки питания
    prices["Corsair RM850x"] = 150.0;
    prices["EVGA SuperNOVA 1000 GT"] = 180.0;
    
    // Системы охлаждения
    prices["Corsair H100i"] = 150.0;
    prices["Noctua NH-D15"] = 110.0;
    
    // Периферия
    prices["ASUS ROG Swift PG32UQX"] = 2800.0;
    prices["Razer Huntsman V2"] = 200.0;
    prices["Logitech G502 X Plus"] = 150.0;
    prices["Dell UltraSharp U4323QE"] = 1150.0;
    prices["Logitech MX Mechanical"] = 170.0;
    prices["Logitech MX Master 3S"] = 100.0;
}

/**
 * @brief Вывод каталога цен в консоль
 */
void PriceCatalog::printCatalog() const {
    std::cout << "\nPRICE CATALOG:" << std::endl;
    for (const auto& pair : prices) {
        std::cout << std::left << std::setw(35) << pair.first 
                  << " $" << std::fixed << std::setprecision(2) << pair.second << std::endl;
    }
}
/**
 * @brief Расчёт общей стоимости списка компонентов
 * @param components Вектор названий компонентов
 * @return Суммарная цена
 */
double PriceCatalog::calculateTotalCost(const std::vector<std::string>& components) const {
    double total = 0;
    for (const auto& comp : components) {
        total += getPrice(comp);
    }
    return total;
}