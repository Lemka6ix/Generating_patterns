/**
 * @file RAM.h
 * @brief Класс оперативной памяти (Random Access Memory)
 * @details Наследуется от Component. Добавляет специфические поля:
 *          - объём в GB
 *          - тип памяти (DDR4/DDR5)
 *          - частота в MHz
 *          - поддержка ECC (Error-Correcting Code) для серверов
 * @note Для серверов рекомендуется использовать ECC-память для надёжности.
 * @see Motherboard::getRAMType()
 */

#ifndef RAM_H
#define RAM_H

#include "Component.h"
#include <vector>
#include <iostream>

/**
 * @class RAM
 * @brief Класс, представляющий модуль оперативной памяти
 * @details Содержит все характеристики RAM и методы для их получения.
 *          Реализует статические методы для работы с каталогом RAM.
 */
class RAM : public Component {
private:
    int sizeGB;             /**< Объём одного модуля в гигабайтах */
    std::string type;       /**< Тип памяти (DDR4, DDR5) */
    int frequency;          /**< Частота работы в мегагерцах (MHz) */
    bool isECC;             /**< Флаг поддержки ECC (Error-Correcting Code) */
    
public:
    /**
     * @brief Конструктор модуля RAM
     * @param n Название модели
     * @param p Цена в долларах
     * @param m Производитель (Kingston, Corsair, G.Skill, Samsung)
     * @param size Объём в GB
     * @param t Тип памяти (DDR4/DDR5)
     * @param freq Частота в MHz
     * @param ecc Поддержка ECC (по умолчанию false)
     */
    RAM(const std::string& n, double p, const std::string& m,
        int size, const std::string& t, int freq, bool ecc = false)
        : Component(n, p, m), sizeGB(size), type(t), frequency(freq), isECC(ecc) {}
    
    /**
     * @brief Конструктор копирования
     * @param other Копируемый объект RAM
     */
    RAM(const RAM& other)
        : Component(other), sizeGB(other.sizeGB), type(other.type),
          frequency(other.frequency), isECC(other.isECC) {}
    
    /**
     * @brief Получение строки с характеристиками RAM
     * @return Форматированная строка с параметрами
     * @details Включает объём, тип памяти, частоту и флаг ECC
     */
    std::string getSpecs() const override {
        return "RAM: " + name + " (" + std::to_string(sizeGB) + "GB " + type +
               ", " + std::to_string(frequency) + "MHz" + (isECC ? ", ECC" : "") + ")";
    }
    
    /**
     * @brief Получение типа компонента
     * @return Строка "RAM"
     */
    std::string getType() const override { return "RAM"; }
    
    /**
     * @brief Получение объёма модуля
     * @return Объём в гигабайтах
     */
    int getSize() const { return sizeGB; }
    
    /**
     * @brief Получение типа памяти
     * @return Строка с типом (DDR4/DDR5)
     */
    std::string getTypeName() const { return type; }
    
    /**
     * @brief Проверка поддержки ECC
     * @return true если поддерживается ECC, false в противном случае
     * @note ECC память используется в серверах для обнаружения и исправления ошибок
     */
    bool isECCCompatible() const { return isECC; }
    
    // ============ СТАТИЧЕСКИЕ МЕТОДЫ ДЛЯ КАТАЛОГА ============
    
    /**
     * @brief Получение списка всех модулей RAM
     * @return Вектор с предустановленными модулями RAM
     * @details Включает модули от 8GB до 128GB, с поддержкой ECC для серверных вариантов
     */
    static std::vector<RAM> getRAMs() {
        return {
            {"Kingston Fury 8GB", 40.0, "Kingston", 8, "DDR5", 4800, false},
            {"Kingston Fury 16GB", 80.0, "Kingston", 16, "DDR5", 5200, false},
            {"Corsair Vengeance 32GB", 150.0, "Corsair", 32, "DDR5", 5600, false},
            {"G.Skill Trident 64GB", 280.0, "G.Skill", 64, "DDR5", 6000, false},
            {"Kingston Server 128GB", 500.0, "Kingston", 128, "DDR5", 4800, true}
        };
    }
    
    /**
     * @brief Вывод списка модулей RAM в консоль
     * @details Выводит нумерованный список всех модулей RAM с их характеристиками и ценами
     */
    static void printRAMs() {
        auto rams = getRAMs();
        for (size_t i = 0; i < rams.size(); ++i) {
            std::cout << (i + 1) << ". " << rams[i].getSpecs() << " - $" << rams[i].getPrice() << std::endl;
        }
    }
    
    /**
     * @brief Получение модуля RAM по индексу
     * @param index Индекс в списке (начиная с 1)
     * @return Указатель на новый объект RAM или nullptr при неверном индексе
     */
    static RAM* getRAMByIndex(int index) {
        auto rams = getRAMs();
        if (index < 1 || index > (int)rams.size()) return nullptr;
        return new RAM(rams[index - 1]);
    }
    
    /**
     * @brief Получение количества модулей RAM в каталоге
     * @return Количество моделей в каталоге
     */
    static int getRAMsCount() { return getRAMs().size(); }
};

#endif