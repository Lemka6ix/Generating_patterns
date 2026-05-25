/**
 * @file Computer.h
 * @brief Класс собранного компьютера, содержащий все компоненты
 * @details Содержит указатели на все компоненты (CPU, motherboard, RAM, GPU,
 *          storage, PSU, cooling, peripherals). Реализует конструктор копирования
 *          для глубокого копирования (паттерн Prototype).
 * @note Является целевым продуктом для паттерна Builder.
 * @see ComputerBuilder, Director, PresetManager
 */

#ifndef COMPUTER_H
#define COMPUTER_H

#include <vector>
#include <string>
#include <iostream>
#include "../components/CPU.h"
#include "../components/Motherboard.h"
#include "../components/RAM.h"
#include "../components/GPU.h"
#include "../components/Storage.h"
#include "../components/PowerSupply.h"
#include "../components/Cooling.h"
#include "../components/Peripheral.h"

using namespace std;  ///< Использование стандартного пространства имён

/**
 * @class Computer
 * @brief Класс, представляющий собранный компьютер
 * @details Содержит все компоненты ПК, обеспечивает глубокое копирование и валидацию.
 */
class Computer {
private:
    string name;           ///< Пользовательское название компьютера
    string computerType;   ///< Тип компьютера (Gaming PC, Workstation, Server)
    
public:
    CPU* cpu;                              ///< Указатель на процессор
    Motherboard* motherboard;              ///< Указатель на материнскую плату
    vector<RAM*> ramModules;               ///< Вектор указателей на модули RAM
    GPU* gpu;                              ///< Указатель на видеокарту
    vector<Storage*> storageDevices;       ///< Вектор указателей на накопители
    PowerSupply* psu;                      ///< Указатель на блок питания
    Cooling* cooling;                      ///< Указатель на систему охлаждения
    vector<Peripheral*> peripherals;       ///< Вектор указателей на периферийные устройства
    
    /**
     * @brief Конструктор по умолчанию
     * @details Инициализирует все указатели значением nullptr
     */
    Computer() : cpu(nullptr), motherboard(nullptr), gpu(nullptr), psu(nullptr), cooling(nullptr) {}
    
    /**
     * @brief Конструктор копирования (глубокое копирование)
     * @param other Копируемый компьютер
     * @details Создаёт полную независимую копию всех компонентов.
     *          Используется для паттерна Prototype.
     * @warning Все компоненты копируются через конструкторы копирования.
     */
    Computer(const Computer& other) 
        : name(other.name + " (copy)"), computerType(other.computerType),
          cpu(nullptr), motherboard(nullptr), gpu(nullptr), psu(nullptr), cooling(nullptr) {
        // Глубокое копирование CPU
        if (other.cpu) cpu = new CPU(*other.cpu);
        // Глубокое копирование материнской платы
        if (other.motherboard) motherboard = new Motherboard(*other.motherboard);
        // Глубокое копирование видеокарты
        if (other.gpu) gpu = new GPU(*other.gpu);
        // Глубокое копирование блока питания
        if (other.psu) psu = new PowerSupply(*other.psu);
        // Глубокое копирование системы охлаждения
        if (other.cooling) cooling = new Cooling(*other.cooling);
        
        // Глубокое копирование всех модулей RAM
        for (auto ram : other.ramModules) {
            if (ram) ramModules.push_back(new RAM(*ram));
        }
        // Глубокое копирование всех накопителей
        for (auto storage : other.storageDevices) {
            if (storage) storageDevices.push_back(new Storage(*storage));
        }
        // Глубокое копирование всех периферийных устройств
        for (auto peripheral : other.peripherals) {
            if (peripheral) peripherals.push_back(new Peripheral(*peripheral));
        }
    }
    
    /**
     * @brief Деструктор компьютера
     * @details Освобождает всю динамически выделенную память.
     *          Удаляет все компоненты и очищает векторы.
     */
    ~Computer() {
        delete cpu;
        delete motherboard;
        delete gpu;
        delete psu;
        delete cooling;
        for (auto ram : ramModules) delete ram;
        for (auto storage : storageDevices) delete storage;
        for (auto peripheral : peripherals) delete peripheral;
    }
    
    
    /**
     * @brief Установка имени компьютера
     * @param n Новое имя
     */
    void setName(const string& n) { name = n; }
    
    /**
     * @brief Установка типа компьютера
     * @param t Тип (Gaming PC, Workstation, Server)
     */
    void setType(const string& t) { computerType = t; }
    
    /**
     * @brief Установка процессора
     * @param c Указатель на CPU (компьютер забирает владение)
     * @note Компьютер становится владельцем памяти и удалит CPU в деструкторе
     */
    void setCPU(CPU* c) { cpu = c; }
    
    /**
     * @brief Установка материнской платы
     * @param m Указатель на Motherboard (компьютер забирает владение)
     */
    void setMotherboard(Motherboard* m) { motherboard = m; }
    
    /**
     * @brief Добавление модуля оперативной памяти
     * @param r Указатель на RAM (компьютер забирает владение)
     */
    void addRAM(RAM* r) { ramModules.push_back(r); }
    
    /**
     * @brief Установка видеокарты
     * @param g Указатель на GPU (компьютер забирает владение)
     */
    void setGPU(GPU* g) { gpu = g; }
    
    /**
     * @brief Добавление накопителя
     * @param s Указатель на Storage (компьютер забирает владение)
     */
    void addStorage(Storage* s) { storageDevices.push_back(s); }
    
    /**
     * @brief Установка блока питания
     * @param p Указатель на PowerSupply (компьютер забирает владение)
     */
    void setPSU(PowerSupply* p) { psu = p; }
    
    /**
     * @brief Установка системы охлаждения
     * @param c Указатель на Cooling (компьютер забирает владение)
     */
    void setCooling(Cooling* c) { cooling = c; }
    
    /**
     * @brief Добавление периферийного устройства
     * @param p Указатель на Peripheral (компьютер забирает владение)
     */
    void addPeripheral(Peripheral* p) { peripherals.push_back(p); }
    
    /**
     * @brief Получение имени компьютера
     * @return Имя компьютера
     */
    string getName() const { return name; }
    
    /**
     * @brief Получение типа компьютера
     * @return Тип компьютера
     */
    string getType() const { return computerType; }
    
    /**
     * @brief Расчёт общей стоимости всех компонентов
     * @return Суммарная цена в долларах
     * @details Суммирует цены CPU, материнской платы, GPU, БП, охлаждения,
     *          всех модулей RAM, накопителей и периферии.
     */
    double calculateTotalPrice() const {
        double total = 0;
        if (cpu) total += cpu->getPrice();
        if (motherboard) total += motherboard->getPrice();
        if (gpu) total += gpu->getPrice();
        if (psu) total += psu->getPrice();
        if (cooling) total += cooling->getPrice();
        for (auto ram : ramModules) total += ram->getPrice();
        for (auto storage : storageDevices) total += storage->getPrice();
        for (auto peripheral : peripherals) total += peripheral->getPrice();
        return total;
    }
    
    /**
     * @brief Проверка совместимости компонентов
     * @return true если CPU и материнская плата совместимы по сокету
     * @warning Сокет процессора должен совпадать с сокетом материнской платы
     */
    bool validateCompatibility() const {
        if (!cpu || !motherboard) return false;
        if (cpu->getSocket() != motherboard->getSocket()) return false;
        return true;
    }
    
    /**
     * @brief Вывод полной спецификации компьютера в консоль
     * @details Выводит все компоненты с их характеристиками,
     *          общую стоимость и статус совместимости.
     */
    void printSpecification() const {
        std::cout << "\nComputer: " << name << " (" << computerType << ")" << std::endl;
        if (cpu) std::cout << cpu->getSpecs() << std::endl;
        if (motherboard) std::cout << motherboard->getSpecs() << std::endl;
        for (auto ram : ramModules) std::cout << ram->getSpecs() << std::endl;
        if (gpu) std::cout << gpu->getSpecs() << std::endl;
        for (auto storage : storageDevices) std::cout << storage->getSpecs() << std::endl;
        if (psu) std::cout << psu->getSpecs() << std::endl;
        if (cooling) std::cout << cooling->getSpecs() << std::endl;
        for (auto peripheral : peripherals) std::cout << peripheral->getSpecs() << std::endl;
        std::cout << "Total Price: $" << calculateTotalPrice() << std::endl;
        std::cout << "Compatible: " << (validateCompatibility() ? "YES" : "NO") << std::endl;
    }
    
    /**
     * @brief Дружественный класс для доступа к приватным полям
     * @see PresetManager
     */
    friend class PresetManager;
};

#endif  // COMPUTER_H