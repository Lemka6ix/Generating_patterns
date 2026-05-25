/**
 * @file ComputerBuilder.h
 * @brief Классы строителей для разных типов компьютеров (паттерн Builder)
 * @details Содержит абстрактный класс ComputerBuilder и конкретные реализации:
 *          GamingPCBuilder, WorkstationBuilder, ServerBuilder.
 *          Каждый строитель определяет свою логику сборки и набор периферии.
 * @see Director, Computer
 */

#ifndef COMPUTER_BUILDER_H
#define COMPUTER_BUILDER_H

#include "Computer.h"
#include "../factories/ComponentFactory.h"

/**
 * @class ComputerBuilder
 * @brief Абстрактный класс строителя компьютера
 * @details Реализует паттерн Builder для пошаговой сборки.
 *          Позволяет создавать сложные объекты Computer пошагово.
 */
class ComputerBuilder {
protected:
    Computer* computer;                 /**< Указатель на собираемый компьютер */
    const ComponentFactory* factory;    /**< Фабрика для создания компонентов */
    
public:
    /**
     * @brief Конструктор строителя
     * @param f Фабрика компонентов (может быть nullptr)
     * @details Создаёт новый пустой компьютер для сборки.
     */
    ComputerBuilder(const ComponentFactory* f = nullptr) : factory(f) {
        computer = new Computer();
    }
    
    /**
     * @brief Виртуальный деструктор
     * @details Освобождает память компьютера, если он не был получен через getComputer()
     */
    virtual ~ComputerBuilder() {
        delete computer;
    }
    
    /**
     * @brief Установка типа и имени компьютера (чисто виртуальный)
     * @details Должен быть реализован в наследниках для установки специфичных имени и типа
     */
    virtual void buildComputerType() = 0;
    
    /**
     * @brief Добавление процессора
     * @details Создаёт CPU через фабрику и устанавливает в компьютер
     */
    virtual void addCPU() {
        if (factory) computer->setCPU(factory->createCPU());
    }
    
    /**
     * @brief Добавление материнской платы
     * @details Создаёт Motherboard через фабрику и устанавливает в компьютер
     */
    virtual void addMotherboard() {
        if (factory) computer->setMotherboard(factory->createMotherboard());
    }
    
    /**
     * @brief Добавление оперативной памяти
     * @details Создаёт RAM через фабрику и добавляет в компьютер
     */
    virtual void addRAM() {
        if (factory) computer->addRAM(factory->createRAM());
    }
    
    /**
     * @brief Добавление видеокарты
     * @details Создаёт GPU через фабрику и устанавливает в компьютер
     */
    virtual void addGPU() {
        if (factory) computer->setGPU(factory->createGPU());
    }
    
    /**
     * @brief Добавление накопителя
     * @details Создаёт Storage через фабрику и добавляет в компьютер
     */
    virtual void addStorage() {
        if (factory) computer->addStorage(factory->createStorage());
    }
    
    /**
     * @brief Добавление блока питания
     * @details Создаёт PowerSupply через фабрику и устанавливает в компьютер
     */
    virtual void addPowerSupply() {
        if (factory) computer->setPSU(factory->createPowerSupply());
    }
    
    /**
     * @brief Добавление системы охлаждения
     * @details Создаёт Cooling через фабрику и устанавливает в компьютер
     */
    virtual void addCooling() {
        if (factory) computer->setCooling(factory->createCooling());
    }
    
    /**
     * @brief Добавление периферии (чисто виртуальный)
     * @details Должен быть реализован в наследниках для добавления специфичной периферии
     */
    virtual void addPeripherals() = 0;
    
    /**
     * @brief Получение готового компьютера
     * @return Указатель на собранный компьютер
     * @note После вызова строитель создаёт новый пустой компьютер для следующей сборки
     * @warning Вызывающий код отвечает за удаление полученного Computer
     */
    Computer* getComputer() {
        Computer* result = computer;
        computer = new Computer();  ///< Создание нового компьютера для следующей сборки
        return result;
    }
};

/**
 * @class GamingPCBuilder
 * @brief Строитель для игрового ПК
 * @details Добавляет топовую периферию: игровой монитор, клавиатуру и мышь.
 */
class GamingPCBuilder : public ComputerBuilder {
public:
    /**
     * @brief Конструктор строителя игрового ПК
     * @param f Фабрика компонентов
     */
    GamingPCBuilder(const ComponentFactory* f) : ComputerBuilder(f) {}
    
    /**
     * @brief Установка типа и имени для игрового ПК
     * @details Устанавливает имя "Gaming Beast" и тип "Gaming PC"
     */
    void buildComputerType() override {
        computer->setName("Gaming Beast");
        computer->setType("Gaming PC");
    }
    
    /**
     * @brief Добавление игровой периферии
     * @details Добавляет игровой монитор ASUS, клавиатуру Razer и мышь Logitech
     */
    void addPeripherals() override {
        computer->addPeripheral(new Peripheral("ASUS ROG Swift Monitor", 2800.0, "ASUS", "Monitor", "DisplayPort"));
        computer->addPeripheral(new Peripheral("Razer Huntsman Keyboard", 200.0, "Razer", "Keyboard", "USB"));
        computer->addPeripheral(new Peripheral("Logitech G502 Mouse", 150.0, "Logitech", "Mouse", "USB"));
    }
};

/**
 * @class WorkstationBuilder
 * @brief Строитель для рабочей станции
 * @details Добавляет 4 модуля RAM и профессиональную периферию.
 */
class WorkstationBuilder : public ComputerBuilder {
public:
    /**
     * @brief Конструктор строителя рабочей станции
     * @param f Фабрика компонентов
     */
    WorkstationBuilder(const ComponentFactory* f) : ComputerBuilder(f) {}
    
    /**
     * @brief Установка типа и имени для рабочей станции
     * @details Устанавливает имя "Professional Workstation" и тип "Workstation"
     */
    void buildComputerType() override {
        computer->setName("Professional Workstation");
        computer->setType("Workstation");
    }
    
    /**
     * @brief Добавление 4 модулей RAM для рабочей станции
     * @details Переопределяет стандартный метод для добавления 4 модулей RAM
     */
    void addRAM() override {
        if (factory) {
            for (int i = 0; i < 4; i++) {
                computer->addRAM(factory->createRAM());
            }
        }
    }
    
    /**
     * @brief Добавление профессиональной периферии
     * @details Добавляет монитор Dell, клавиатуру и мышь Logitech MX
     */
    void addPeripherals() override {
        computer->addPeripheral(new Peripheral("Dell UltraSharp Monitor", 1150.0, "Dell", "Monitor", "USB-C"));
        computer->addPeripheral(new Peripheral("Logitech MX Keyboard", 170.0, "Logitech", "Keyboard", "Bluetooth"));
        computer->addPeripheral(new Peripheral("Logitech MX Master Mouse", 100.0, "Logitech", "Mouse", "Bluetooth"));
    }
};

/**
 * @class ServerBuilder
 * @brief Строитель для сервера
 * @details Добавляет 8 модулей RAM, не добавляет видеокарту и периферию.
 */
class ServerBuilder : public ComputerBuilder {
public:
    /**
     * @brief Конструктор строителя сервера
     * @param f Фабрика компонентов
     */
    ServerBuilder(const ComponentFactory* f) : ComputerBuilder(f) {}
    
    /**
     * @brief Установка типа и имени для сервера
     * @details Устанавливает имя "Enterprise Server" и тип "Server"
     */
    void buildComputerType() override {
        computer->setName("Enterprise Server");
        computer->setType("Server");
    }
    
    /**
     * @brief Добавление 8 модулей RAM для сервера
     * @details Переопределяет стандартный метод для добавления 8 модулей RAM
     */
    void addRAM() override {
        if (factory) {
            for (int i = 0; i < 8; i++) {
                computer->addRAM(factory->createRAM());
            }
        }
    }
    
    /**
     * @brief Серверу не нужна видеокарта
     * @details Пустая реализация - видеокарта не добавляется
     */
    void addGPU() override {}
    
    /**
     * @brief Серверу не нужна периферия
     * @details Пустая реализация - периферия не добавляется
     */
    void addPeripherals() override {}
};

#endif  // COMPUTER_BUILDER_H