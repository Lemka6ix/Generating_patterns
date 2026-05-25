/**
 * @file CPU.h
 * @brief Класс процессора (Central Processing Unit)
 * @details Наследуется от Component. Добавляет специфические поля:
 *          - количество ядер (cores)
 *          - тактовая частота (frequency) в GHz
 *          - тип сокета (socket) для совместимости с материнской платой
 *          - тепловыделение (TDP) в Ваттах
 *          - наличие встроенной графики (integrated graphics)
 * @note Сокет CPU должен совпадать с сокетом материнской платы.
 * @see Motherboard::getSocket()
 */

#ifndef CPU_H
#define CPU_H

#include "Component.h"
#include <vector>
#include <iostream>

/**
 * @class CPU
 * @brief Класс, представляющий процессор
 * @details Содержит все характеристики процессора и методы для их получения.
 *          Реализует статические методы для работы с каталогом CPU.
 */
class CPU : public Component {
private:
    int cores;                      /**< Количество физических ядер */
    double frequency;               /**< Тактовая частота в гигагерцах (GHz) */
    std::string socket;             /**< Тип сокета (LGA1700, AM5, LGA4677) */
    int tdp;                        /**< Тепловыделение в Ваттах (Thermal Design Power) */
    bool hasIntegratedGraphics;     /**< Флаг наличия встроенного графического ядра */
    
public:
    /**
     * @brief Конструктор процессора
     * @param n Название модели процессора
     * @param p Цена в долларах США
     * @param m Производитель (Intel, AMD)
     * @param c Количество ядер
     * @param f Тактовая частота в GHz
     * @param s Тип сокета
     * @param t TDP в Ваттах (по умолчанию 65)
     * @param igfx Наличие встроенной графики (по умолчанию false)
     */
    CPU(const std::string& n, double p, const std::string& m, 
        int c, double f, const std::string& s, int t = 65, bool igfx = false)
        : Component(n, p, m), cores(c), frequency(f), socket(s), tdp(t), hasIntegratedGraphics(igfx) {}
    
    /**
     * @brief Конструктор копирования (для паттерна Prototype)
     * @param other Копируемый объект процессора
     * @details Создаёт глубокую копию процессора
     */
    CPU(const CPU& other)
        : Component(other), cores(other.cores), frequency(other.frequency),
          socket(other.socket), tdp(other.tdp), hasIntegratedGraphics(other.hasIntegratedGraphics) {}
    
    /**
     * @brief Получение строки с характеристиками процессора
     * @return Форматированная строка с параметрами CPU
     * @details Включает название, количество ядер, частоту, сокет и TDP
     */
    std::string getSpecs() const override {
        return "CPU: " + name + " (" + std::to_string(cores) + " cores, " +
               std::to_string(frequency) + "GHz, " + socket + ", " + std::to_string(tdp) + "W)";
    }
    
    /**
     * @brief Получение типа компонента
     * @return Строка "CPU"
     */
    std::string getType() const override { return "CPU"; }
    
    /**
     * @brief Получение типа сокета процессора
     * @return Строка с типом сокета
     */
    std::string getSocket() const { return socket; }
    
    /**
     * @brief Получение количества ядер
     * @return Количество физических ядер
     */
    int getCores() const { return cores; }
    
    /**
     * @brief Получение тактовой частоты
     * @return Частота в гигагерцах
     */
    double getFrequency() const { return frequency; }
    
    /**
     * @brief Получение тепловыделения
     * @return TDP в Ваттах
     */
    int getTDP() const { return tdp; }
    
    /**
     * @brief Получение списка всех Intel процессоров
     * @return Вектор с предустановленными Intel CPU
     */
    static std::vector<CPU> getIntelCPUs() {
        return {
            {"Intel Core i7-13700K", 380.0, "Intel", 16, 5.4, "LGA1700", 125, true},
            {"Intel Core i9-13900K", 580.0, "Intel", 24, 5.8, "LGA1700", 125, true},
            {"Intel Core i9-14900K", 780.0, "Intel", 24, 6.0, "LGA1700", 150, true},
            {"Intel Core i9-14900KS", 980.0, "Intel", 24, 6.2, "LGA1700", 150, true}
        };
    }
    
    /**
     * @brief Получение списка всех AMD процессоров
     * @return Вектор с предустановленными AMD CPU
     */
    static std::vector<CPU> getAMDCPUs() {
        return {
            {"AMD Ryzen 7 7700X", 350.0, "AMD", 8, 5.4, "AM5", 105, true},
            {"AMD Ryzen 9 7900X", 450.0, "AMD", 12, 5.6, "AM5", 170, true},
            {"AMD Ryzen 9 7950X", 550.0, "AMD", 16, 5.7, "AM5", 170, true},
            {"AMD Ryzen 9 7950X3D", 699.0, "AMD", 16, 5.7, "AM5", 120, true}
        };
    }
    
    /**
     * @brief Получение списка серверных процессоров
     * @return Вектор с предустановленными серверными CPU (Intel Xeon)
     */
    static std::vector<CPU> getServerCPUs() {
        return {
            {"Intel Xeon Gold 6428R", 2800.0, "Intel", 32, 3.5, "LGA4677", 250, false},
            {"Intel Xeon Platinum 8480+", 5200.0, "Intel", 56, 3.8, "LGA4677", 350, false}
        };
    }
    
    /**
     * @brief Вывод списка Intel CPU в консоль
     * @details Выводит нумерованный список всех Intel процессоров с их ценами
     */
    static void printIntelCPUs() {
        auto cpus = getIntelCPUs();
        for (size_t i = 0; i < cpus.size(); ++i) {
            std::cout << (i + 1) << ". " << cpus[i].getSpecs() << " - $" << cpus[i].getPrice() << std::endl;
        }
    }
    
    /**
     * @brief Вывод списка AMD CPU в консоль
     * @details Выводит нумерованный список всех AMD процессоров с их ценами
     */
    static void printAMDCPUs() {
        auto cpus = getAMDCPUs();
        for (size_t i = 0; i < cpus.size(); ++i) {
            std::cout << (i + 1) << ". " << cpus[i].getSpecs() << " - $" << cpus[i].getPrice() << std::endl;
        }
    }
    
    /**
     * @brief Вывод списка серверных CPU в консоль
     * @details Выводит нумерованный список всех серверных процессоров с их ценами
     */
    static void printServerCPUs() {
        auto cpus = getServerCPUs();
        for (size_t i = 0; i < cpus.size(); ++i) {
            std::cout << (i + 1) << ". " << cpus[i].getSpecs() << " - $" << cpus[i].getPrice() << std::endl;
        }
    }
    
    /**
     * @brief Получение Intel CPU по индексу
     * @param index Индекс в списке (начиная с 1)
     * @return Указатель на новый объект CPU или nullptr при неверном индексе
     */
    static CPU* getIntelCPUByIndex(int index) {
        auto cpus = getIntelCPUs();
        if (index < 1 || index > (int)cpus.size()) return nullptr;
        return new CPU(cpus[index - 1]);
    }
    
    /**
     * @brief Получение AMD CPU по индексу
     * @param index Индекс в списке (начиная с 1)
     * @return Указатель на новый объект CPU или nullptr при неверном индексе
     */
    static CPU* getAMDCPUByIndex(int index) {
        auto cpus = getAMDCPUs();
        if (index < 1 || index > (int)cpus.size()) return nullptr;
        return new CPU(cpus[index - 1]);
    }
    
    /**
     * @brief Получение серверного CPU по индексу
     * @param index Индекс в списке (начиная с 1)
     * @return Указатель на новый объект CPU или nullptr при неверном индексе
     */
    static CPU* getServerCPUByIndex(int index) {
        auto cpus = getServerCPUs();
        if (index < 1 || index > (int)cpus.size()) return nullptr;
        return new CPU(cpus[index - 1]);
    }
    
    /**
     * @brief Получение количества Intel процессоров
     * @return Количество моделей в каталоге Intel
     */
    static int getIntelCPUsCount() { return getIntelCPUs().size(); }
    
    /**
     * @brief Получение количества AMD процессоров
     * @return Количество моделей в каталоге AMD
     */
    static int getAMDCPUsCount() { return getAMDCPUs().size(); }
    
    /**
     * @brief Получение количества серверных процессоров
     * @return Количество моделей в серверном каталоге
     */
    static int getServerCPUsCount() { return getServerCPUs().size(); }
};

#endif