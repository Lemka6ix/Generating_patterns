/**
 * @file PriceCatalog.h
 * @brief Синглтон для хранения каталога цен на компоненты
 * @details Реализует паттерн "Одиночка" (Singleton).
 *          Хранит актуальные цены на все компоненты и позволяет их получать/изменять.
 * @note Цены загружаются из предустановленного списка при первом вызове getInstance().
 * @see PriceCatalog::getInstance()
 */

#ifndef PRICE_CATALOG_H
#define PRICE_CATALOG_H

#include <map>
#include <string>
#include <vector>
#include <iostream>

/**
 * @class PriceCatalog
 * @brief Синглтон для хранения каталога цен
 * @details Обеспечивает глобальную точку доступа к каталогу цен.
 */
class PriceCatalog {
private:
    static PriceCatalog* instance;                      ///< Единственный экземпляр класса
    std::map<std::string, double> prices;               ///< Ассоциативный массив: компонент -> цена
    
    /**
     * @brief Приватный конструктор (синглтон)
     * @details Инициализирует каталог и загружает цены по умолчанию
     */
    PriceCatalog();
    
    /**
     * @brief Загрузка цен по умолчанию
     * @details Заполняет prices значениями для всех доступных компонентов
     */
    void loadDefaultPrices();
    
    // Запрет копирования (синглтон не должен копироваться)
    PriceCatalog(const PriceCatalog&) = delete;
    PriceCatalog& operator=(const PriceCatalog&) = delete;
    
public:
    /**
     * @brief Получение единственного экземпляра каталога
     * @return Указатель на экземпляр PriceCatalog
     * @details Реализует ленивую инициализацию - создаёт экземпляр при первом вызове
     */
    static PriceCatalog* getInstance();
    
    /**
     * @brief Уничтожение экземпляра синглтона
     * @details Освобождает память, занятую каталогом цен
     */
    static void destroyInstance();
    
    /**
     * @brief Установка цены для компонента
     * @param componentName Название компонента
     * @param price Цена в долларах
     */
    void setPrice(const std::string& componentName, double price);
    
    /**
     * @brief Получение цены компонента
     * @param componentName Название компонента
     * @return Цена в долларах или 0.0, если компонент не найден
     */
    double getPrice(const std::string& componentName) const;
    
    /**
     * @brief Проверка наличия цены для компонента
     * @param componentName Название компонента
     * @return true если цена существует, false в противном случае
     */
    bool hasPrice(const std::string& componentName) const;
    
    /**
     * @brief Вывод всего каталога цен в консоль
     * @details Выводит цены с группировкой по категориям (CPU, Motherboards, RAM и т.д.)
     */
    void printCatalog() const;
    
    /**
     * @brief Расчёт общей стоимости списка компонентов
     * @param components Вектор названий компонентов
     * @return Суммарная цена в долларах
     */
    double calculateTotalCost(const std::vector<std::string>& components) const;
};

#endif  // PRICE_CATALOG_H