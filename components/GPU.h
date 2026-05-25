/**
 * @file GPU.h
 * @brief Класс видеокарты (Graphics Processing Unit)
 * @details Наследуется от Component. Добавляет специфические поля:
 *          - объём видеопамяти (VRAM) в GB
 *          - тип видеопамяти (GDDR6, GDDR6X, HBM2e)
 *          - количество CUDA/Stream ядер
 *          - флаг профессиональной карты (для рабочих станций)
 * @note Для серверных сборок видеокарта может отсутствовать (None).
 * @see Computer::setGPU()
 */

#ifndef GPU_H
#define GPU_H

#include "Component.h"
#include <vector>
#include <iostream>

/**
 * @class GPU
 * @brief Класс, представляющий видеокарту
 * @details Содержит все характеристики видеокарты и методы для их получения.
 *          Реализует статические методы для работы с каталогом видеокарт.
 */
class GPU : public Component {
private:
    int vramGB;                 /**< Объём видеопамяти в гигабайтах */
    std::string vramType;       /**< Тип видеопамяти (GDDR6, GDDR6X, HBM2e) */
    int cudaCores;              /**< Количество ядер (CUDA для NVIDIA, Stream для AMD) */
    bool isProfessional;        /**< Флаг профессиональной карты (Quadro, A100 и т.д.) */
    
public:
    /**
     * @brief Конструктор видеокарты
     * @param n Название модели видеокарты
     * @param p Цена в долларах
     * @param m Производитель (NVIDIA, AMD)
     * @param vram Объём видеопамяти в GB
     * @param vType Тип видеопамяти
     * @param cores Количество ядер
     * @param prof Флаг профессиональной карты (по умолчанию false)
     */
    GPU(const std::string& n, double p, const std::string& m,
        int vram, const std::string& vType, int cores, bool prof = false)
        : Component(n, p, m), vramGB(vram), vramType(vType), cudaCores(cores), isProfessional(prof) {}
    
    /**
     * @brief Конструктор копирования
     * @param other Копируемый объект видеокарты
     */
    GPU(const GPU& other)
        : Component(other), vramGB(other.vramGB), vramType(other.vramType),
          cudaCores(other.cudaCores), isProfessional(other.isProfessional) {}
    
    /**
     * @brief Получение строки с характеристиками видеокарты
     * @return Форматированная строка с параметрами GPU
     * @details Включает название, объём видеопамяти, тип памяти,
     *          количество ядер и флаг профессиональной карты
     */
    std::string getSpecs() const override {
        return "GPU: " + name + " (" + std::to_string(vramGB) + "GB " + vramType +
               ", " + std::to_string(cudaCores) + " cores" + 
               (isProfessional ? ", Professional" : "") + ")";
    }
    
    /**
     * @brief Получение типа компонента
     * @return Строка "GPU"
     */
    std::string getType() const override { return "GPU"; }
    
    /**
     * @brief Получение объёма видеопамяти
     * @return Объём в гигабайтах
     */
    int getVRAM() const { return vramGB; }
    

    
    /**
     * @brief Получение списка всех видеокарт
     * @return Вектор с предустановленными видеокартами
     * @details Включает опцию "None" для систем без дискретной графики,
     *          а также видеокарты NVIDIA и AMD разных поколений
     */
    static std::vector<GPU> getGPUs() {
        return {
            {"None (integrated graphics only)", 0.0, "N/A", 0, "N/A", 0, false},
            {"NVIDIA RTX 4060", 300.0, "NVIDIA", 8, "GDDR6", 3072, false},
            {"NVIDIA RTX 4070", 550.0, "NVIDIA", 12, "GDDR6X", 5888, false},
            {"NVIDIA RTX 4080", 1200.0, "NVIDIA", 16, "GDDR6X", 9728, false},
            {"NVIDIA RTX 4090", 1650.0, "NVIDIA", 24, "GDDR6X", 16384, false},
            {"AMD Radeon RX 7800 XT", 500.0, "AMD", 16, "GDDR6", 3840, false},
            {"AMD Radeon RX 7900 XTX", 1000.0, "AMD", 24, "GDDR6", 6144, false}
        };
    }
    
    /**
     * @brief Вывод списка видеокарт в консоль
     * @details Выводит нумерованный список всех видеокарт с их характеристиками и ценами
     */
    static void printGPUs() {
        auto gpus = getGPUs();
        for (size_t i = 0; i < gpus.size(); ++i) {
            std::cout << (i + 1) << ". " << gpus[i].getSpecs() << " - $" << gpus[i].getPrice() << std::endl;
        }
    }
    
    /**
     * @brief Получение видеокарты по индексу
     * @param index Индекс в списке (начиная с 1)
     * @return Указатель на новый объект GPU или nullptr
     * @note Индекс 1 соответствует "None" и возвращает nullptr
     */
    static GPU* getGPUByIndex(int index) {
        auto gpus = getGPUs();
        if (index < 1 || index > (int)gpus.size()) return nullptr;
        if (index == 1) return nullptr; // "None" option
        return new GPU(gpus[index - 1]);
    }
    
    /**
     * @brief Получение количества видеокарт в каталоге
     * @return Количество моделей в каталоге (включая "None")
     */
    static int getGPUsCount() { return getGPUs().size(); }
};

#endif