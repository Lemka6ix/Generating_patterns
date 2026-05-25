/**
 * @file Storage.h
 * @brief Класс накопителя данных (SSD, HDD, NVMe)
 * @details Наследуется от Component. Добавляет специфические поля:
 *          - ёмкость в GB
 *          - тип накопителя (SSD/HDD/NVMe)
 *          - скорость чтения и записи в MB/s
 * @note NVMe накопители обеспечивают максимальную производительность.
 * @see Computer::addStorage()
 */

#ifndef STORAGE_H
#define STORAGE_H

#include "Component.h"
#include <vector>
#include <iostream>

/**
 * @class Storage
 * @brief Класс, представляющий накопитель (SSD, HDD, NVMe)
 * @details Содержит все характеристики накопителя и методы для их получения.
 *          Реализует статические методы для работы с каталогом накопителей.
 */
class Storage : public Component {
private:
    int capacityGB;         /**< Ёмкость накопителя в гигабайтах (GB) */
    std::string type;       /**< Тип накопителя: "SSD", "HDD", "NVMe" */
    int readSpeed;          /**< Скорость последовательного чтения в MB/s */
    int writeSpeed;         /**< Скорость последовательной записи в MB/s */
    
public:
    /**
     * @brief Конструктор накопителя
     * @param n Название модели
     * @param p Цена в долларах
     * @param m Производитель (Samsung, WD, Kingston, Seagate)
     * @param cap Ёмкость в GB
     * @param t Тип накопителя (SSD/HDD/NVMe)
     * @param rSpeed Скорость чтения в MB/s
     * @param wSpeed Скорость записи в MB/s
     */
    Storage(const std::string& n, double p, const std::string& m,
            int cap, const std::string& t, int rSpeed, int wSpeed)
        : Component(n, p, m), capacityGB(cap), type(t), readSpeed(rSpeed), writeSpeed(wSpeed) {}
    
    /**
     * @brief Конструктор копирования
     * @param other Копируемый объект накопителя
     */
    Storage(const Storage& other)
        : Component(other), capacityGB(other.capacityGB), type(other.type),
          readSpeed(other.readSpeed), writeSpeed(other.writeSpeed) {}
    
    /**
     * @brief Получение строки с характеристиками накопителя
     * @return Форматированная строка с параметрами
     * @details Включает название, ёмкость и тип накопителя
     */
    std::string getSpecs() const override {
        return "Storage: " + name + " (" + std::to_string(capacityGB) + "GB " + type + ")";
    }
    
    /**
     * @brief Получение типа компонента
     * @return Строка "Storage"
     */
    std::string getType() const override { return "Storage"; }
    
    /**
     * @brief Получение типа накопителя
     * @return Строка с типом (SSD/HDD/NVMe)
     */
    std::string getStorageType() const { return type; }
    
    /**
     * @brief Получение ёмкости накопителя
     * @return Ёмкость в гигабайтах
     */
    int getCapacity() const { return capacityGB; }
    
    // ============ СТАТИЧЕСКИЕ МЕТОДЫ ДЛЯ КАТАЛОГА ============
    
    /**
     * @brief Получение списка всех накопителей
     * @return Вектор с предустановленными накопителями
     * @details Включает SSD, NVMe и HDD накопители разных производителей и объёмов
     */
    static std::vector<Storage> getStorages() {
        return {
            {"Kingston 256GB SSD", 30.0, "Kingston", 256, "SSD", 500, 450},
            {"Kingston 512GB SSD", 50.0, "Kingston", 512, "SSD", 500, 450},
            {"Samsung 980 1TB", 100.0, "Samsung", 1000, "NVMe", 3500, 3000},
            {"Samsung 980 Pro 2TB", 180.0, "Samsung", 2000, "NVMe", 7000, 5100},
            {"WD Black 4TB", 350.0, "WD", 4000, "NVMe", 7300, 6600},
            {"Seagate 2TB HDD", 70.0, "Seagate", 2000, "HDD", 200, 200},
            {"Seagate 4TB HDD", 120.0, "Seagate", 4000, "HDD", 200, 200}
        };
    }
    
    /**
     * @brief Вывод списка накопителей в консоль
     * @details Выводит нумерованный список всех накопителей с их характеристиками и ценами
     */
    static void printStorages() {
        auto storages = getStorages();
        for (size_t i = 0; i < storages.size(); ++i) {
            std::cout << (i + 1) << ". " << storages[i].getSpecs() << " - $" << storages[i].getPrice() << std::endl;
        }
    }
    
    /**
     * @brief Получение накопителя по индексу
     * @param index Индекс в списке (начиная с 1)
     * @return Указатель на новый объект Storage или nullptr
     */
    static Storage* getStorageByIndex(int index) {
        auto storages = getStorages();
        if (index < 1 || index > (int)storages.size()) return nullptr;
        return new Storage(storages[index - 1]);
    }
    
    /**
     * @brief Получение количества накопителей в каталоге
     * @return Количество моделей в каталоге
     */
    static int getStoragesCount() { return getStorages().size(); }
};

#endif