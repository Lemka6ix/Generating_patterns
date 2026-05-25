/**
 * @file PowerSupply.h
 * @brief Класс блока питания (Power Supply Unit)
 * @details Наследуется от Component. Добавляет специфические поля:
 *          - мощность в Ваттах
 *          - сертификат эффективности (80+ Bronze/Gold/Platinum/Titanium)
 *          - модульность (полностью/частично модульный)
 * @warning Мощность БП должна быть достаточной для всех компонентов системы.
 * @see Computer::setPSU()
 */

#ifndef POWERSUPPLY_H
#define POWERSUPPLY_H

#include "Component.h"
#include <vector>
#include <iostream>

/**
 * @class PowerSupply
 * @brief Класс, представляющий блок питания
 * @details Содержит все характеристики блока питания и методы для их получения.
 *          Реализует статические методы для работы с каталогом БП.
 */
class PowerSupply : public Component {
private:
    int wattage;                /**< Номинальная мощность в Ваттах (W) */
    std::string efficiency;     /**< Сертификат эффективности: 80+ Bronze/Gold/Platinum/Titanium */
    bool isModular;             /**< Флаг модульности (можно отключать кабели) */
    
public:
    /**
     * @brief Конструктор блока питания
     * @param n Название модели
     * @param p Цена в долларах
     * @param m Производитель (Corsair, EVGA, Seasonic, Cooler Master, Delta)
     * @param watts Мощность в Ваттах
     * @param eff Сертификат эффективности
     * @param modular Флаг модульности (true - модульный, false - немодульный)
     */
    PowerSupply(const std::string& n, double p, const std::string& m,
                int watts, const std::string& eff, bool modular)
        : Component(n, p, m), wattage(watts), efficiency(eff), isModular(modular) {}
    
    /**
     * @brief Конструктор копирования
     * @param other Копируемый объект блока питания
     */
    PowerSupply(const PowerSupply& other)
        : Component(other), wattage(other.wattage), efficiency(other.efficiency),
          isModular(other.isModular) {}
    
    /**
     * @brief Получение строки с характеристиками блока питания
     * @return Форматированная строка с параметрами
     * @details Включает мощность и сертификат эффективности
     */
    std::string getSpecs() const override {
        return "PSU: " + name + " (" + std::to_string(wattage) + "W, " + efficiency + ")";
    }
    
    /**
     * @brief Получение типа компонента
     * @return Строка "PowerSupply"
     */
    std::string getType() const override { return "PowerSupply"; }
    
    /**
     * @brief Получение мощности блока питания
     * @return Мощность в Ваттах
     */
    int getWattage() const { return wattage; }
    
    // ============ СТАТИЧЕСКИЕ МЕТОДЫ ДЛЯ КАТАЛОГА ============
    
    /**
     * @brief Получение списка всех блоков питания
     * @return Вектор с предустановленными блоками питания
     * @details Включает блоки питания мощностью от 450W до 1600W,
     *          с сертификатами от Bronze до Titanium
     */
    static std::vector<PowerSupply> getPowerSupplies() {
        return {
            {"EVGA 450W", 40.0, "EVGA", 450, "80+ Bronze", false},
            {"Corsair CV550", 60.0, "Corsair", 550, "80+ Bronze", false},
            {"Cooler Master 650W", 80.0, "Cooler Master", 650, "80+ Gold", false},
            {"Cooler Master 750W", 120.0, "Cooler Master", 750, "80+ Gold", true},
            {"Corsair RM850x", 150.0, "Corsair", 850, "80+ Gold", true},
            {"Seasonic Focus 1000W", 250.0, "Seasonic", 1000, "80+ Platinum", true},
            {"Corsair HX1200", 350.0, "Corsair", 1200, "80+ Platinum", true},
            {"Seasonic Prime 1600W", 550.0, "Seasonic", 1600, "80+ Titanium", true}
        };
    }
    
    /**
     * @brief Вывод списка блоков питания в консоль
     * @details Выводит нумерованный список всех БП с их характеристиками и ценами
     */
    static void printPSUs() {
        auto psus = getPowerSupplies();
        for (size_t i = 0; i < psus.size(); ++i) {
            std::cout << (i + 1) << ". " << psus[i].getSpecs() << " - $" << psus[i].getPrice() << std::endl;
        }
    }
    
    /**
     * @brief Получение блока питания по индексу
     * @param index Индекс в списке (начиная с 1)
     * @return Указатель на новый объект PowerSupply или nullptr
     */
    static PowerSupply* getPSUByIndex(int index) {
        auto psus = getPowerSupplies();
        if (index < 1 || index > (int)psus.size()) return nullptr;
        return new PowerSupply(psus[index - 1]);
    }
    
    /**
     * @brief Получение количества блоков питания в каталоге
     * @return Количество моделей в каталоге
     */
    static int getPSUsCount() { return getPowerSupplies().size(); }
};

#endif