/**
 * @file ComponentFactory.h
 * @brief Абстрактная фабрика и её реализации для создания совместимых компонентов
 * @details Реализует паттерн "Абстрактная фабрика" (Abstract Factory).
 *          Позволяет создавать семейства связанных компонентов для разных платформ:
 *          Intel, AMD, Server.
 * @note Обеспечивает совместимость компонентов внутри одной платформы.
 * @see IntelFactory, AMDFactory, ServerFactory
 */

#ifndef COMPONENT_FACTORY_H
#define COMPONENT_FACTORY_H

#include "../components/CPU.h"
#include "../components/Motherboard.h"
#include "../components/RAM.h"
#include "../components/GPU.h"
#include "../components/Storage.h"
#include "../components/PowerSupply.h"
#include "../components/Cooling.h"

/**
 * @class ComponentFactory
 * @brief Абстрактная фабрика для создания семейства компонентов
 * @details Реализует паттерн Abstract Factory.
 *          Позволяет создавать совместимые компоненты для разных платформ.
 */
class ComponentFactory {
public:
    /**
     * @brief Виртуальный деструктор для корректного удаления наследников
     */
    virtual ~ComponentFactory() = default;
    
    /**
     * @brief Создание процессора для платформы
     * @return Указатель на новый объект CPU
     */
    virtual CPU* createCPU() const = 0;
    
    /**
     * @brief Создание материнской платы для платформы
     * @return Указатель на новый объект Motherboard
     */
    virtual Motherboard* createMotherboard() const = 0;
    
    /**
     * @brief Создание модуля RAM для платформы
     * @return Указатель на новый объект RAM
     */
    virtual RAM* createRAM() const = 0;
    
    /**
     * @brief Создание видеокарты для платформы
     * @return Указатель на новый объект GPU
     */
    virtual GPU* createGPU() const = 0;
    
    /**
     * @brief Создание накопителя для платформы
     * @return Указатель на новый объект Storage
     */
    virtual Storage* createStorage() const = 0;
    
    /**
     * @brief Создание блока питания для платформы
     * @return Указатель на новый объект PowerSupply
     */
    virtual PowerSupply* createPowerSupply() const = 0;
    
    /**
     * @brief Создание системы охлаждения для платформы
     * @return Указатель на новый объект Cooling
     */
    virtual Cooling* createCooling() const = 0;
    
    /**
     * @brief Получение названия платформы
     * @return Строка с названием платформы
     */
    virtual std::string getPlatformName() const = 0;
};

/**
 * @class IntelFactory
 * @brief Фабрика для Intel платформы
 * @details Создаёт компоненты, совместимые с сокетом LGA1700 и чипсетом Z790.
 */
class IntelFactory : public ComponentFactory {
public:
    /**
     * @brief Создание Intel Core i9-13900K
     * @return Указатель на CPU Intel
     */
    CPU* createCPU() const override {
        return new CPU("Intel Core i9-13900K", 580.0, "Intel", 24, 5.8, "LGA1700", 125, true);
    }
    
    /**
     * @brief Создание ASUS ROG Z790
     * @return Указатель на материнскую плату Intel
     */
    Motherboard* createMotherboard() const override {
        return new Motherboard("ASUS ROG Z790", 520.0, "ASUS", "LGA1700", "Z790", "DDR5", 128, 4, 3, "ATX");
    }
    
    /**
     * @brief Создание Corsair DDR5 32GB
     * @return Указатель на модуль RAM
     */
    RAM* createRAM() const override {
        return new RAM("Corsair DDR5", 180.0, "Corsair", 32, "DDR5", 5600, false);
    }
    
    /**
     * @brief Создание NVIDIA RTX 4080
     * @return Указатель на видеокарту
     */
    GPU* createGPU() const override {
        return new GPU("NVIDIA RTX 4080", 1250.0, "NVIDIA", 16, "GDDR6X", 9728, false);
    }
    
    /**
     * @brief Создание Samsung 980 Pro 1TB NVMe
     * @return Указатель на накопитель
     */
    Storage* createStorage() const override {
        return new Storage("Samsung 980 Pro", 150.0, "Samsung", 1000, "NVMe", 7000, 5100);
    }
    
    /**
     * @brief Создание Corsair RM850x
     * @return Указатель на блок питания
     */
    PowerSupply* createPowerSupply() const override {
        return new PowerSupply("Corsair RM850x", 150.0, "Corsair", 850, "80+ Gold", true);
    }
    
    /**
     * @brief Создание Corsair H100i
     * @return Указатель на систему охлаждения
     */
    Cooling* createCooling() const override {
        return new Cooling("Corsair H100i", 150.0, "Corsair", "Liquid", 200, 2);
    }
    
    /**
     * @brief Получение названия платформы
     * @return "Intel Platform"
     */
    std::string getPlatformName() const override { return "Intel Platform"; }
};

/**
 * @class AMDFactory
 * @brief Фабрика для AMD платформы
 * @details Создаёт компоненты, совместимые с сокетом AM5 и чипсетом X670E.
 */
class AMDFactory : public ComponentFactory {
public:
    /**
     * @brief Создание AMD Ryzen 9 7950X3D
     * @return Указатель на CPU AMD
     */
    CPU* createCPU() const override {
        return new CPU("AMD Ryzen 9 7950X3D", 699.0, "AMD", 16, 5.7, "AM5", 120, true);
    }
    
    /**
     * @brief Создание ASRock X670E Taichi
     * @return Указатель на материнскую плату AMD
     */
    Motherboard* createMotherboard() const override {
        return new Motherboard("ASRock X670E Taichi", 480.0, "ASRock", "AM5", "X670E", "DDR5", 128, 4, 4, "ATX");
    }
    
    /**
     * @brief Создание G.Skill Trident Z5 32GB
     * @return Указатель на модуль RAM
     */
    RAM* createRAM() const override {
        return new RAM("G.Skill Trident Z5", 190.0, "G.Skill", 32, "DDR5", 6000, false);
    }
    
    /**
     * @brief Создание AMD Radeon RX 7900 XTX
     * @return Указатель на видеокарту
     */
    GPU* createGPU() const override {
        return new GPU("AMD Radeon RX 7900 XTX", 1000.0, "AMD", 24, "GDDR6", 6144, false);
    }
    
    /**
     * @brief Создание WD Black SN850X 1TB NVMe
     * @return Указатель на накопитель
     */
    Storage* createStorage() const override {
        return new Storage("WD Black SN850X", 160.0, "WD", 1000, "NVMe", 7300, 6600);
    }
    
    /**
     * @brief Создание EVGA SuperNOVA 1000 GT
     * @return Указатель на блок питания
     */
    PowerSupply* createPowerSupply() const override {
        return new PowerSupply("EVGA SuperNOVA 1000 GT", 180.0, "EVGA", 1000, "80+ Gold", true);
    }
    
    /**
     * @brief Создание Noctua NH-D15
     * @return Указатель на систему охлаждения
     */
    Cooling* createCooling() const override {
        return new Cooling("Noctua NH-D15", 110.0, "Noctua", "Air", 250, 2);
    }
    
    /**
     * @brief Получение названия платформы
     * @return "AMD Platform"
     */
    std::string getPlatformName() const override { return "AMD Platform"; }
};

/**
 * @class ServerFactory
 * @brief Фабрика для серверной платформы
 * @details Создаёт компоненты для серверов на базе Intel Xeon.
 */
class ServerFactory : public ComponentFactory {
public:
    /**
     * @brief Создание Intel Xeon Gold 6428R
     * @return Указатель на серверный CPU
     */
    CPU* createCPU() const override {
        return new CPU("Intel Xeon Gold 6428R", 2800.0, "Intel", 32, 3.5, "LGA4677", 250, false);
    }
    
    /**
     * @brief Создание SuperMicro X13DEM
     * @return Указатель на серверную материнскую плату
     */
    Motherboard* createMotherboard() const override {
        return new Motherboard("SuperMicro X13DEM", 1200.0, "SuperMicro", "LGA4677", "C741", "DDR5", 4096, 16, 4, "EE-ATX");
    }
    
    /**
     * @brief Создание Samsung RDIMM 64GB ECC
     * @return Указатель на серверный модуль RAM с ECC
     */
    RAM* createRAM() const override {
        return new RAM("Samsung RDIMM", 380.0, "Samsung", 64, "DDR5", 4800, true);
    }
    
    /**
     * @brief Создание NVIDIA A100
     * @return Указатель на профессиональную видеокарту
     */
    GPU* createGPU() const override {
        return new GPU("NVIDIA A100", 11000.0, "NVIDIA", 80, "HBM2e", 6912, true);
    }
    
    /**
     * @brief Создание Intel Optane P5800X
     * @return Указатель на серверный накопитель
     */
    Storage* createStorage() const override {
        return new Storage("Intel Optane P5800X", 1200.0, "Intel", 800, "NVMe", 7200, 6200);
    }
    
    /**
     * @brief Создание Delta 2400W
     * @return Указатель на мощный серверный БП
     */
    PowerSupply* createPowerSupply() const override {
        return new PowerSupply("Delta 2400W", 650.0, "Delta", 2400, "80+ Platinum", true);
    }
    
    /**
     * @brief Создание Dynatron LGA4677
     * @return Указатель на серверную систему охлаждения
     */
    Cooling* createCooling() const override {
        return new Cooling("Dynatron LGA4677", 180.0, "Dynatron", "Air", 350, 2);
    }
    
    /**
     * @brief Получение названия платформы
     * @return "Server Platform"
     */
    std::string getPlatformName() const override { return "Server Platform"; }
};

#endif  // COMPONENT_FACTORY_H