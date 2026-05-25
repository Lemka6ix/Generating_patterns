/**
 * @file Cooling.h
 * @brief Класс системы охлаждения
 * @details Наследуется от Component. Добавляет специфические поля:
 *          - тип охлаждения (Air/Liquid)
 *          - максимальный TDP в Ваттах
 *          - количество вентиляторов
 * @note Система охлаждения должна справляться с TDP процессора.
 * @see CPU::getTDP()
 */

#ifndef COOLING_H
#define COOLING_H

#include "Component.h"
#include <vector>
#include <iostream>

/**
 * @class Cooling
 * @brief Класс, представляющий систему охлаждения
 * @details Содержит все характеристики системы охлаждения и методы для их получения.
 *          Реализует статические методы для работы с каталогом охлаждения.
 */
class Cooling : public Component {
private:
    std::string type;           /**< Тип охлаждения: "Air" (воздушное) или "Liquid" (жидкостное) */
    int tdpCapacity;            /**< Максимальный TDP, который может рассеять система в Ваттах */
    int fanCount;               /**< Количество вентиляторов в системе охлаждения */
    
public:
    /**
     * @brief Конструктор системы охлаждения
     * @param n Название модели
     * @param p Цена в долларах
     * @param m Производитель (Noctua, Corsair, Cooler Master, Dynatron)
     * @param t Тип охлаждения (Air/Liquid)
     * @param tdp Максимальный TDP в Ваттах
     * @param fans Количество вентиляторов
     */
    Cooling(const std::string& n, double p, const std::string& m,
            const std::string& t, int tdp, int fans)
        : Component(n, p, m), type(t), tdpCapacity(tdp), fanCount(fans) {}
    
    /**
     * @brief Конструктор копирования
     * @param other Копируемый объект системы охлаждения
     */
    Cooling(const Cooling& other)
        : Component(other), type(other.type), tdpCapacity(other.tdpCapacity),
          fanCount(other.fanCount) {}
    
    /**
     * @brief Получение строки с характеристиками системы охлаждения
     * @return Форматированная строка с параметрами
     * @details Включает тип охлаждения и максимальный TDP
     */
    std::string getSpecs() const override {
        return "Cooling: " + name + " (" + type + ", " + std::to_string(tdpCapacity) + "W TDP)";
    }
    
    /**
     * @brief Получение типа компонента
     * @return Строка "Cooling"
     */
    std::string getType() const override { return "Cooling"; }
    
    /**
     * @brief Получение максимального TDP
     * @return TDP в Ваттах
     */
    int getTDPMax() const { return tdpCapacity; }
    
    
    /**
     * @brief Получение списка всех систем охлаждения
     * @return Вектор с предустановленными системами охлаждения
     * @details Включает воздушное (Air) и жидкостное (Liquid) охлаждение,
     *          от бюджетных вариантов до профессиональных
     */
    static std::vector<Cooling> getCoolings() {
        return {
            {"Stock Cooler", 0.0, "Intel/AMD", "Air", 65, 1},
            {"Cooler Master Hyper 212", 25.0, "Cooler Master", "Air", 150, 1},
            {"Noctua NH-D15", 110.0, "Noctua", "Air", 250, 2},
            {"Corsair H100i", 120.0, "Corsair", "Liquid", 200, 2},
            {"Corsair H150i", 180.0, "Corsair", "Liquid", 300, 3},
            {"Custom Water Loop", 500.0, "Custom", "Liquid", 500, 6}
        };
    }
    
    /**
     * @brief Вывод списка систем охлаждения в консоль
     * @details Выводит нумерованный список всех систем охлаждения с их характеристиками и ценами
     */
    static void printCoolings() {
        auto coolings = getCoolings();
        for (size_t i = 0; i < coolings.size(); ++i) {
            std::cout << (i + 1) << ". " << coolings[i].getSpecs() << " - $" << coolings[i].getPrice() << std::endl;
        }
    }
    
    /**
     * @brief Получение системы охлаждения по индексу
     * @param index Индекс в списке (начиная с 1)
     * @return Указатель на новый объект Cooling или nullptr
     */
    static Cooling* getCoolingByIndex(int index) {
        auto coolings = getCoolings();
        if (index < 1 || index > (int)coolings.size()) return nullptr;
        return new Cooling(coolings[index - 1]);
    }
    
    /**
     * @brief Получение количества систем охлаждения в каталоге
     * @return Количество моделей в каталоге
     */
    static int getCoolingsCount() { return getCoolings().size(); }
};

#endif