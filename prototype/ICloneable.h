/**
 * @file ICloneable.h
 * @brief Интерфейс для клонирования объектов (паттерн Prototype)
 * @details Определяет абстрактный метод clone(), который должны реализовать
 *          все классы, поддерживающие глубокое копирование.
 * @note Является ключевым для паттерна Prototype.
 * @see PresetManager, Computer
 */

#ifndef ICLONEABLE_H
#define ICLONEABLE_H

/**
 * @class ICloneable
 * @brief Интерфейс для паттерна Prototype
 * @details Позволяет клонировать объекты без привязки к их конкретному типу.
 */
class ICloneable {
public:
    /**
     * @brief Виртуальный деструктор для корректного удаления наследников
     */
    virtual ~ICloneable() = default;
    
    /**
     * @brief Создание глубокой копии объекта
     * @return Указатель на клон объекта
     * @note Клонированный объект полностью независим от оригинала
     * @warning Вызывающий код отвечает за удаление клона через delete
     */
    virtual ICloneable* clone() const = 0;
};

#endif  // ICLONEABLE_H