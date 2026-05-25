/**
 * @file Peripheral.h
 * @brief Класс периферийных устройств
 * @details Наследуется от Component. Добавляет специфические поля:
 *          - тип устройства (Monitor, Keyboard, Mouse, Keyboard+Mouse)
 *          - тип подключения (USB, Bluetooth, DisplayPort, USB-C)
 * @note Периферия не влияет на совместимость основных компонентов.
 * @see Computer::addPeripheral()
 */

#ifndef PERIPHERAL_H
#define PERIPHERAL_H

#include "Component.h"

/**
 * @class Peripheral
 * @brief Класс, представляющий периферийное устройство
 * @details Включает мониторы, клавиатуры, мыши и другие внешние устройства.
 */
class Peripheral : public Component {
private:
    std::string deviceType;  /**< Тип устройства: "Monitor", "Keyboard", "Mouse", "Keyboard+Mouse" */
    std::string connection;  /**< Тип подключения: "USB", "Bluetooth", "DisplayPort", "USB-C" */
    
public:
    /**
     * @brief Конструктор периферийного устройства
     * @param n Название модели
     * @param p Цена в долларах
     * @param m Производитель (Dell, Logitech, Razer, ASUS)
     * @param dType Тип устройства
     * @param conn Тип подключения
     */
    Peripheral(const std::string& n, double p, const std::string& m,
               const std::string& dType, const std::string& conn)
        : Component(n, p, m), deviceType(dType), connection(conn) {}
    
    /**
     * @brief Конструктор копирования
     * @param other Копируемый объект периферии
     */
    Peripheral(const Peripheral& other)
        : Component(other), deviceType(other.deviceType), connection(other.connection) {}
    
    /**
     * @brief Получение строки с характеристиками периферии
     * @return Форматированная строка с параметрами
     * @details Включает тип устройства, название и тип подключения
     */
    std::string getSpecs() const override {
        return deviceType + ": " + name + " (" + connection + ")";
    }
    
    /**
     * @brief Получение типа компонента
     * @return Строка "Peripheral"
     */
    std::string getType() const override { return "Peripheral"; }
    
    /**
     * @brief Получение типа устройства
     * @return Тип устройства (Monitor, Keyboard, Mouse, Keyboard+Mouse)
     */
    std::string getDeviceType() const { return deviceType; }
};

#endif  // PERIPHERAL_H