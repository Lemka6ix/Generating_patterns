/**
 * @file Motherboard.h
 * @brief Класс материнской платы (Motherboard)
 * @details Наследуется от Component. Добавляет специфические поля:
 *          - сокет процессора (socket)
 *          - чипсет (chipset)
 *          - тип оперативной памяти (DDR4/DDR5)
 *          - максимальный объём RAM
 *          - количество слотов RAM и PCIe
 *          - форм-фактор (ATX, mATX, E-ATX, EE-ATX)
 * @warning Сокет материнской платы должен совпадать с сокетом выбранного CPU.
 * @see CPU::getSocket()
 */

#ifndef MOTHERBOARD_H
#define MOTHERBOARD_H

#include "Component.h"
#include <vector>
#include <iostream>

/**
 * @class Motherboard
 * @brief Класс, представляющий материнскую плату
 * @details Содержит все характеристики материнской платы и методы для их получения.
 *          Реализует статические методы для работы с каталогом материнских плат.
 */
class Motherboard : public Component {
private:
    std::string socket;         /**< Сокет процессора (LGA1700, AM5, LGA4677) */
    std::string chipset;        /**< Чипсет (Z790, X670E, C741, W790) */
    std::string ramType;        /**< Тип поддерживаемой памяти (DDR4, DDR5) */
    int maxRAM;                 /**< Максимальный объём оперативной памяти в GB */
    int ramSlots;               /**< Количество слотов для модулей RAM */
    int pcieSlots;              /**< Количество слотов PCI Express */
    std::string formFactor;     /**< Форм-фактор (ATX, mATX, E-ATX, EE-ATX) */
    
public:
    /**
     * @brief Конструктор материнской платы
     * @param n Название модели
     * @param p Цена в долларах
     * @param m Производитель (ASUS, MSI, Gigabyte, ASRock, SuperMicro)
     * @param s Тип сокета
     * @param cs Чипсет
     * @param rt Тип оперативной памяти
     * @param maxR Максимальный объём RAM в GB
     * @param rSlots Количество слотов RAM
     * @param pcie Количество PCIe слотов
     * @param ff Форм-фактор
     */
    Motherboard(const std::string& n, double p, const std::string& m,
                const std::string& s, const std::string& cs, const std::string& rt,
                int maxR, int rSlots, int pcie, const std::string& ff)
        : Component(n, p, m), socket(s), chipset(cs), ramType(rt), maxRAM(maxR),
          ramSlots(rSlots), pcieSlots(pcie), formFactor(ff) {}
    
    /**
     * @brief Конструктор копирования
     * @param other Копируемый объект материнской платы
     */
    Motherboard(const Motherboard& other)
        : Component(other), socket(other.socket), chipset(other.chipset),
          ramType(other.ramType), maxRAM(other.maxRAM), ramSlots(other.ramSlots),
          pcieSlots(other.pcieSlots), formFactor(other.formFactor) {}
    
    /**
     * @brief Получение строки с характеристиками материнской платы
     * @return Форматированная строка с параметрами
     */
    std::string getSpecs() const override {
        return "Motherboard: " + name + " (" + socket + ", " + chipset + 
               ", " + ramType + ", max " + std::to_string(maxRAM) + "GB, " + formFactor + ")";
    }
    
    /**
     * @brief Получение типа компонента
     * @return Строка "Motherboard"
     */
    std::string getType() const override { return "Motherboard"; }
    
    /**
     * @brief Получение типа сокета
     * @return Строка с типом сокета
     */
    std::string getSocket() const { return socket; }
    
    /**
     * @brief Получение типа поддерживаемой оперативной памяти
     * @return Строка с типом памяти (DDR4/DDR5)
     */
    std::string getRAMType() const { return ramType; }
    
    /**
     * @brief Получение максимального объёма RAM
     * @return Максимальный объём в гигабайтах
     */
    int getMaxRAM() const { return maxRAM; }
    
    // ============ СТАТИЧЕСКИЕ МЕТОДЫ ДЛЯ КАТАЛОГА ============
    
    /**
     * @brief Получение списка Intel материнских плат
     * @return Вектор с предустановленными Intel материнскими платами
     */
    static std::vector<Motherboard> getIntelMotherboards() {
        return {
            {"ASUS ROG Z790", 520.0, "ASUS", "LGA1700", "Z790", "DDR5", 128, 4, 3, "ATX"},
            {"MSI Z790 Tomahawk", 280.0, "MSI", "LGA1700", "Z790", "DDR5", 128, 4, 3, "ATX"},
            {"Gigabyte Z790 AORUS", 300.0, "Gigabyte", "LGA1700", "Z790", "DDR5", 128, 4, 3, "ATX"},
            {"ASRock Z790 Steel Legend", 250.0, "ASRock", "LGA1700", "Z790", "DDR5", 128, 4, 3, "ATX"},
            {"ASUS Prime B760", 150.0, "ASUS", "LGA1700", "B760", "DDR5", 128, 4, 2, "mATX"}
        };
    }
    
    /**
     * @brief Получение списка AMD материнских плат
     * @return Вектор с предустановленными AMD материнскими платами
     */
    static std::vector<Motherboard> getAMDMotherboards() {
        return {
            {"ASRock X670E Taichi", 480.0, "ASRock", "AM5", "X670E", "DDR5", 128, 4, 4, "ATX"},
            {"Gigabyte X670 AORUS", 300.0, "Gigabyte", "AM5", "X670", "DDR5", 128, 4, 3, "ATX"},
            {"MSI B650 Tomahawk", 220.0, "MSI", "AM5", "B650", "DDR5", 128, 4, 3, "ATX"},
            {"ASUS ROG STRIX B650", 250.0, "ASUS", "AM5", "B650", "DDR5", 128, 4, 3, "ATX"},
            {"ASRock B650M Pro", 150.0, "ASRock", "AM5", "B650", "DDR5", 96, 4, 2, "mATX"}
        };
    }
    
    /**
     * @brief Получение списка серверных материнских плат
     * @return Вектор с предустановленными серверными материнскими платами
     */
    static std::vector<Motherboard> getServerMotherboards() {
        return {
            {"SuperMicro X13DEM", 1200.0, "SuperMicro", "LGA4677", "C741", "DDR5", 4096, 16, 4, "EE-ATX"},
            {"ASUS Pro WS W790", 900.0, "ASUS", "LGA4677", "W790", "DDR5", 2048, 8, 4, "E-ATX"},
            {"Gigabyte MW34-SP0", 1100.0, "Gigabyte", "LGA4677", "C741", "DDR5", 4096, 16, 4, "EE-ATX"}
        };
    }
    
    /**
     * @brief Вывод списка Intel материнских плат в консоль
     */
    static void printIntelMotherboards() {
        auto boards = getIntelMotherboards();
        for (size_t i = 0; i < boards.size(); ++i) {
            std::cout << (i + 1) << ". " << boards[i].getSpecs() << " - $" << boards[i].getPrice() << std::endl;
        }
    }
    
    /**
     * @brief Вывод списка AMD материнских плат в консоль
     */
    static void printAMDMotherboards() {
        auto boards = getAMDMotherboards();
        for (size_t i = 0; i < boards.size(); ++i) {
            std::cout << (i + 1) << ". " << boards[i].getSpecs() << " - $" << boards[i].getPrice() << std::endl;
        }
    }
    
    /**
     * @brief Вывод списка серверных материнских плат в консоль
     */
    static void printServerMotherboards() {
        auto boards = getServerMotherboards();
        for (size_t i = 0; i < boards.size(); ++i) {
            std::cout << (i + 1) << ". " << boards[i].getSpecs() << " - $" << boards[i].getPrice() << std::endl;
        }
    }
    
    /**
     * @brief Получение Intel материнской платы по индексу
     * @param index Индекс в списке (начиная с 1)
     * @return Указатель на новый объект Motherboard или nullptr
     */
    static Motherboard* getIntelMotherboardByIndex(int index) {
        auto boards = getIntelMotherboards();
        if (index < 1 || index > (int)boards.size()) return nullptr;
        return new Motherboard(boards[index - 1]);
    }
    
    /**
     * @brief Получение AMD материнской платы по индексу
     * @param index Индекс в списке (начиная с 1)
     * @return Указатель на новый объект Motherboard или nullptr
     */
    static Motherboard* getAMDMotherboardByIndex(int index) {
        auto boards = getAMDMotherboards();
        if (index < 1 || index > (int)boards.size()) return nullptr;
        return new Motherboard(boards[index - 1]);
    }
    
    /**
     * @brief Получение серверной материнской платы по индексу
     * @param index Индекс в списке (начиная с 1)
     * @return Указатель на новый объект Motherboard или nullptr
     */
    static Motherboard* getServerMotherboardByIndex(int index) {
        auto boards = getServerMotherboards();
        if (index < 1 || index > (int)boards.size()) return nullptr;
        return new Motherboard(boards[index - 1]);
    }
    
    /**
     * @brief Получение количества Intel материнских плат
     * @return Количество моделей в каталоге Intel
     */
    static int getIntelMotherboardsCount() { return getIntelMotherboards().size(); }
    
    /**
     * @brief Получение количества AMD материнских плат
     * @return Количество моделей в каталоге AMD
     */
    static int getAMDMotherboardsCount() { return getAMDMotherboards().size(); }
    
    /**
     * @brief Получение количества серверных материнских плат
     * @return Количество моделей в серверном каталоге
     */
    static int getServerMotherboardsCount() { return getServerMotherboards().size(); }
};

#endif