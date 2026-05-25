/**
 * @file PresetManager.h
 * @brief Синглтон для управления пресетами (паттерн Prototype)
 * @details Реализует паттерн "Одиночка" (Singleton) и использует Prototype
 *          для глубокого копирования компьютеров при сохранении/загрузке.
 * @note Хранит все сохранённые конфигурации в памяти программы.
 * @see Computer, ICloneable
 */

#ifndef PRESET_MANAGER_H
#define PRESET_MANAGER_H

#include "../builder/Computer.h"
#include <map>
#include <string>
#include <iostream>
#include <vector>

/**
 * @class PresetManager
 * @brief Синглтон для управления сохранёнными конфигурациями компьютеров
 * @details Хранит пресеты в ассоциативном массиве. При сохранении создаёт
 *          глубокую копию компьютера через конструктор копирования.
 */
class PresetManager {
private:
    static PresetManager* instance;                     ///< Единственный экземпляр менеджера
    std::map<std::string, Computer*> presets;           ///< Ассоциативный массив пресетов (имя -> Computer)
    
    /**
     * @brief Приватный конструктор (синглтон)
     * @details Запрещает создание экземпляров вне класса
     */
    PresetManager() = default;
    
    // Запрет копирования (синглтон не должен копироваться)
    PresetManager(const PresetManager&) = delete;
    PresetManager& operator=(const PresetManager&) = delete;
    
public:
    /**
     * @brief Получение единственного экземпляра менеджера
     * @return Указатель на PresetManager
     * @details Реализует ленивую инициализацию - создаёт экземпляр при первом вызове
     */
    static PresetManager* getInstance() {
        if (!instance) {
            instance = new PresetManager();
        }
        return instance;
    }
    
    /**
     * @brief Уничтожение экземпляра и всех пресетов
     * @details Освобождает память всех сохранённых компьютеров и удаляет сам синглтон
     */
    static void destroyInstance() {
        if (instance) {
            for (auto& pair : instance->presets) {
                delete pair.second;
            }
            delete instance;
            instance = nullptr;
        }
    }
    
    /**
     * @brief Деструктор, освобождает память всех пресетов
     */
    ~PresetManager() {
        for (auto& pair : presets) {
            delete pair.second;
        }
    }
    
    /**
     * @brief Сохранение пресета с выводом сообщения
     * @param name Название пресета
     * @param computer Указатель на сохраняемый компьютер
     * @return true при успешном сохранении
     * @details Создаёт глубокую копию компьютера и сохраняет её в map.
     *          Если пресет с таким именем уже существует, он заменяется.
     */
    bool savePreset(const std::string& name, Computer* computer) {
        if (!computer) return false;
        
        // Создание глубокой копии через конструктор копирования Computer
        Computer* clone = new Computer(*computer);
        clone->setName(name);
        
        // Удаление старого пресета с таким же именем, если существует
        auto it = presets.find(name);
        if (it != presets.end()) {
            delete it->second;
        }
        
        presets[name] = clone;
        std::cout << "[SAVED] Preset '" << name << "' saved successfully" << std::endl;
        return true;
    }
    
    /**
     * @brief Сохранение пресета без вывода сообщения (для инициализации)
     * @param name Название пресета
     * @param computer Указатель на сохраняемый компьютер
     * @return true при успешном сохранении
     * @note Используется для создания начальных пресетов при запуске программы
     */
    bool savePresetSilent(const std::string& name, Computer* computer) {
        if (!computer) return false;
        
        Computer* clone = new Computer(*computer);
        clone->setName(name);
        
        auto it = presets.find(name);
        if (it != presets.end()) {
            delete it->second;
        }
        
        presets[name] = clone;
        return true;
    }
    
    /**
     * @brief Загрузка пресета по имени
     * @param name Название пресета
     * @return Указатель на загруженную копию компьютера или nullptr
     * @details Создаёт новую копию сохранённого компьютера.
     *          Вызывающий код отвечает за удаление возвращённого объекта.
     */
    Computer* loadPreset(const std::string& name) {
        auto it = presets.find(name);
        if (it != presets.end()) {
            // Создание копии сохранённого компьютера
            Computer* loaded = new Computer(*it->second);
            loaded->setName(it->second->getName() + " (loaded)");
            std::cout << "[LOADED] Preset '" << name << "' loaded successfully" << std::endl;
            return loaded;
        }
        std::cout << "[ERROR] Preset '" << name << "' not found" << std::endl;
        return nullptr;
    }
    
    /**
     * @brief Вывод списка всех сохранённых пресетов с полными спецификациями
     * @details Выводит каждый пресет с его номером, именем и полной спецификацией
     */
    void listPresets() const {
        if (presets.empty()) {
            std::cout << "\nNo presets available" << std::endl;
            return;
        }
        
        int index = 1;
        for (std::map<std::string, Computer*>::const_iterator it = presets.begin();
             it != presets.end(); ++it) {
            
            std::cout << "\n========== PRESET #" << index << ": " << it->first << " ==========" << std::endl;
            it->second->printSpecification();
            index++;
        }
        
        std::cout << std::endl;
    }
    
    /**
     * @brief Удаление пресета по имени
     * @param name Название пресета
     * @details Освобождает память компьютера и удаляет запись из map
     */
    void deletePreset(const std::string& name) {
        auto it = presets.find(name);
        if (it != presets.end()) {
            delete it->second;
            presets.erase(it);
            std::cout << "[DELETED] Preset '" << name << "' deleted" << std::endl;
        }
    }
    
    /**
     * @brief Проверка существования пресета
     * @param name Название пресета
     * @return true если пресет существует
     */
    bool hasPreset(const std::string& name) const {
        return presets.find(name) != presets.end();
    }
    
    /**
     * @brief Получение всех имён пресетов (для меню)
     * @return Вектор с именами пресетов
     */
    std::vector<std::string> getAllPresetNames() const {
        std::vector<std::string> names;
        for (auto const& pair : presets) {
            names.push_back(pair.first);
        }
        return names;
    }
};

/// Инициализация статического члена класса
PresetManager* PresetManager::instance = nullptr;

#endif  // PRESET_MANAGER_H