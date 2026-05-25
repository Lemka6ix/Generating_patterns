/**
 * @file Component.h
 * @brief Базовый абстрактный класс для всех компонентов компьютера
 * @details Содержит общие поля (название, цена, производитель) и чистые виртуальные
 *          методы getSpecs() и getType(), которые должны быть реализованы в наследниках.
 * @note Все конкретные компоненты (CPU, GPU, RAM и т.д.) наследуются от Component.
 * @see CPU, GPU, RAM, Motherboard, Storage, PowerSupply, Cooling, Peripheral
 */

#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

/**
 * @class Component
 * @brief Абстрактный базовый класс для всех компонентов компьютера
 * @details Содержит общие поля и методы для всех компонентов.
 *          Реализует полиморфизм через виртуальные методы.
 */
class Component {
protected:
    std::string name;           /**< Название компонента */
    double price;               /**< Цена компонента в долларах США */
    std::string manufacturer;   /**< Название компании-производителя */
    
public:
    /**
     * @brief Конструктор компонента
     * @param n Название компонента
     * @param p Цена компонента в долларах
     * @param m Название производителя (по умолчанию "Unknown")
     */
    Component(const std::string& n, double p, const std::string& m = "Unknown")
        : name(n), price(p), manufacturer(m) {}
    
    /**
     * @brief Виртуальный деструктор для корректного удаления наследников
     */
    virtual ~Component() = default;
    
    /**
     * @brief Получение названия компонента
     * @return Строка с названием компонента
     */
    virtual std::string getName() const { return name; }
    
    /**
     * @brief Получение цены компонента
     * @return Цена компонента в долларах
     */
    virtual double getPrice() const { return price; }
    
    /**
     * @brief Получение названия производителя
     * @return Строка с названием производителя
     */
    virtual std::string getManufacturer() const { return manufacturer; }
    
    /**
     * @brief Получение полных характеристик компонента
     * @return Строка с отформатированными характеристиками
     * @note Чисто виртуальный метод, должен быть переопределён в наследниках
     */
    virtual std::string getSpecs() const = 0;
    
    /**
     * @brief Получение типа компонента
     * @return Строка с типом компонента (CPU, GPU, RAM и т.д.)
     * @note Чисто виртуальный метод, должен быть переопределён в наследниках
     */
    virtual std::string getType() const = 0;
    
    /**
     * @brief Установка новой цены компонента
     * @param p Новая цена в долларах
     */
    void setPrice(double p) { price = p; }
};

#endif  // COMPONENT_H