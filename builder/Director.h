/**
 * @file Director.h
 * @brief Класс директора, управляющего процессом сборки (паттерн Builder)
 * @details Директор определяет последовательность вызовов методов строителя
 *          для сборки готового компьютера. Инкапсулирует алгоритм сборки.
 * @see ComputerBuilder
 */

#ifndef DIRECTOR_H
#define DIRECTOR_H

#include "ComputerBuilder.h"

/**
 * @class Director
 * @brief Управляет процессом сборки компьютера
 * @details Определяет порядок вызова методов строителя.
 *          Позволяет переиспользовать алгоритм сборки с разными строителями.
 */
class Director {
private:
    ComputerBuilder* builder;   /**< Указатель на используемого строителя */
    
public:
    /**
     * @brief Конструктор директора
     * @param b Строитель, которым будет управлять директор
     * @details Сохраняет указатель на строителя для последующей сборки
     */
    Director(ComputerBuilder* b) : builder(b) {}
    
    /**
     * @brief Полная сборка компьютера по стандартному сценарию
     * @return Указатель на полностью собранный компьютер
     * @details Вызывает все методы строителя в строго определённом порядке:
     *          1. buildComputerType() - установка типа и имени
     *          2. addCPU() - добавление процессора
     *          3. addMotherboard() - добавление материнской платы
     *          4. addRAM() - добавление оперативной памяти
     *          5. addGPU() - добавление видеокарты
     *          6. addStorage() - добавление накопителей
     *          7. addPowerSupply() - добавление блока питания
     *          8. addCooling() - добавление системы охлаждения
     *          9. addPeripherals() - добавление периферии
     * @note Порядок вызовов важен для корректной сборки
     * @warning Вызывающий код отвечает за удаление возвращённого Computer
     */
    Computer* constructCompleteComputer() {
        builder->buildComputerType();
        builder->addCPU();
        builder->addMotherboard();
        builder->addRAM();
        builder->addGPU();
        builder->addStorage();
        builder->addPowerSupply();
        builder->addCooling();
        builder->addPeripherals();
        return builder->getComputer();
    }
};

#endif  // DIRECTOR_H