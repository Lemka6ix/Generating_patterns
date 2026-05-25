/**
 * @file main.cpp
 * @brief Главный исполняемый файл программы "Конфигуратор компьютеров"
 * @details Реализует пользовательский интерфейс для сборки компьютера,
 *          загрузки/сохранения пресетов, тестирования паттернов.
 *          Использует паттерны: Builder, Abstract Factory, Singleton, Prototype.
 * @note Для работы требуется корректная иерархия компонентов и фабрик.
 * @warning При ручном выборе компонентов проверяется совместимость сокетов.
 */

#include "builder/ComputerBuilder.h"
#include "builder/Director.h"
#include "factories/ComponentFactory.h"
#include "core/PriceCatalog.h"
#include "prototype/PresetManager.h"
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;  ///< Использование стандартного пространства имён

/**
 * @class TestRunner
 * @brief Класс для запуска и отслеживания результатов тестов
 * @details Управляет счётчиками пройденных, проваленных тестов и предупреждений.
 */
class TestRunner {
private:
    int passed = 0;     ///< Количество пройденных тестов
    int failed = 0;     ///< Количество проваленных тестов
    int warnings = 0;   ///< Количество предупреждений
    
public:
    /**
     * @brief Проверка условия и вывод результата теста
     * @param condition Проверяемое условие (true/false)
     * @param testName Название теста для вывода
     */
    void assertTrue(bool condition, const std::string& testName) {
        if (condition) {
            std::cout << "[OK] " << testName << std::endl;
            passed++;
        } else {
            std::cout << "[ERROR] " << testName << " - Assertion failed" << std::endl;
            failed++;
        }
    }
    
    /**
     * @brief Вывод итоговой статистики тестирования
     */
    void printResults() {
        std::cout << "\nTEST RESULTS: " << passed << " passed, " 
                  << failed << " failed, " << warnings << " warnings" << std::endl;
    }
};

/**
 * @brief Тестирование паттерна "Абстрактная фабрика" (Abstract Factory)
 * @details Проверяет совместимость процессора и материнской платы
 *          для Intel и AMD платформ.
 */
void testFactoryPattern() {
    std::cout << "\nTesting Factory Pattern" << std::endl;
    TestRunner runner;  ///< Объект для отслеживания результатов
    
    /// Тестирование Intel платформы
    IntelFactory intelFactory;
    CPU* intelCPU = intelFactory.createCPU();               ///< Создание Intel CPU
    Motherboard* intelMB = intelFactory.createMotherboard(); ///< Создание Intel материнской платы
    runner.assertTrue(intelCPU->getSocket() == intelMB->getSocket(), 
                     "Intel CPU and Motherboard socket compatibility");
    delete intelCPU;  ///< Очистка памяти
    delete intelMB;   ///< Очистка памяти
    
    /// Тестирование AMD платформы
    AMDFactory amdFactory;
    CPU* amdCPU = amdFactory.createCPU();                   ///< Создание AMD CPU
    Motherboard* amdMB = amdFactory.createMotherboard();    ///< Создание AMD материнской платы
    runner.assertTrue(amdCPU->getSocket() == amdMB->getSocket(),
                     "AMD CPU and Motherboard socket compatibility");
    delete amdCPU;  ///< Очистка памяти
    delete amdMB;   ///< Очистка памяти
    
    runner.printResults();  ///< Вывод результатов тестирования
}

/**
 * @brief Тестирование паттерна "Одиночка" (Singleton)
 * @details Проверяет, что PriceCatalog возвращает один и тот же экземпляр
 *          и корректно получает цены.
 */
void testSingletonPattern() {
    std::cout << "\nTesting Singleton Pattern" << std::endl;
    TestRunner runner;  ///< Объект для отслеживания результатов
    
    PriceCatalog* catalog1 = PriceCatalog::getInstance();  ///< Первый запрос экземпляра
    PriceCatalog* catalog2 = PriceCatalog::getInstance();  ///< Второй запрос экземпляра
    runner.assertTrue(catalog1 == catalog2, "Singleton returns same instance");
    
    double price = catalog1->getPrice("Intel Core i9-13900K");  ///< Получение цены
    runner.assertTrue(price == 580.0, "Correct price retrieval");
    
    runner.printResults();  ///< Вывод результатов тестирования
}

/**
 * @brief Тестирование паттерна "Прототип" (Prototype)
 * @details Проверяет сохранение, загрузку и удаление пресетов,
 *          а также глубокое копирование объектов.
 */
void testPrototypePattern() {
    std::cout << "\nTesting Prototype Pattern" << std::endl;
    TestRunner runner;  ///< Объект для отслеживания результатов
    
    PresetManager* pm = PresetManager::getInstance();  ///< Получение экземпляра менеджера пресетов
    
    /// Создание оригинального компьютера через Builder
    IntelFactory factory;
    GamingPCBuilder builder(&factory);
    Director director(&builder);
    Computer* original = director.constructCompleteComputer();
    
    /// Тест сохранения пресета
    bool saved = pm->savePreset("test_gaming_pc", original);
    runner.assertTrue(saved, "Save preset operation");
    runner.assertTrue(pm->hasPreset("test_gaming_pc"), "Preset exists after save");
    
    /// Тест загрузки пресета
    Computer* loaded = pm->loadPreset("test_gaming_pc");
    runner.assertTrue(loaded != nullptr, "Load preset returns valid computer");
    runner.assertTrue(loaded != original, "Loaded computer is different instance from original");
    
    /// Тест глубокого копирования (разные объекты CPU)
    if (loaded && loaded->cpu) {
        runner.assertTrue(loaded->cpu != original->cpu, "CPU objects are different (deep copy)");
    }
    
    /// Тест удаления пресета
    pm->deletePreset("test_gaming_pc");
    runner.assertTrue(!pm->hasPreset("test_gaming_pc"), "Preset deleted successfully");
    
    /// Очистка памяти
    delete original;
    delete loaded;
    runner.printResults();  ///< Вывод результатов тестирования
}

/**
 * @brief Запрос у пользователя продолжения работы
 * @return true если пользователь хочет продолжить, false для возврата в меню
 */
bool askToContinue() {
    std::cout << "\nPress 0 to return to main menu, any other key to continue: ";
    int choice;
    std::cin >> choice;
    return (choice != 0);
}

/**
 * @brief Интерактивный выбор процессора пользователем
 * @param factory Фабрика компонентов для определения платформы
 * @return Указатель на выбранный CPU или nullptr при отмене
 */
CPU* selectCPU(const ComponentFactory* factory) {
    std::string platformName = factory->getPlatformName();
    
    std::cout << "\nAvailable CPUs:" << std::endl;
    
    if (platformName == "Intel Platform") {
        CPU::printIntelCPUs();
        std::cout << "Choose (1-" << CPU::getIntelCPUsCount() << ") or 0 to cancel: ";
        
        int choice;
        std::cin >> choice;
        
        if (choice == 0) return nullptr;
        return CPU::getIntelCPUByIndex(choice);
    } 
    else if (platformName == "AMD Platform") {
        CPU::printAMDCPUs();
        std::cout << "Choose (1-" << CPU::getAMDCPUsCount() << ") or 0 to cancel: ";
        
        int choice;
        std::cin >> choice;
        
        if (choice == 0) return nullptr;
        return CPU::getAMDCPUByIndex(choice);
    }
    else {
        CPU::printServerCPUs();
        std::cout << "Choose (1-" << CPU::getServerCPUsCount() << ") or 0 to cancel: ";
        
        int choice;
        std::cin >> choice;
        
        if (choice == 0) return nullptr;
        return CPU::getServerCPUByIndex(choice);
    }
}

/**
 * @brief Интерактивный выбор материнской платы пользователем
 * @param factory Фабрика компонентов для определения платформы
 * @return Указатель на выбранную материнскую плату или nullptr при отмене
 */
Motherboard* selectMotherboard(const ComponentFactory* factory) {
    std::string platformName = factory->getPlatformName();
    
    std::cout << "\nAvailable Motherboards:" << std::endl;
    
    if (platformName == "Intel Platform") {
        Motherboard::printIntelMotherboards();
        std::cout << "Choose (1-" << Motherboard::getIntelMotherboardsCount() << ") or 0 to cancel: ";
        
        int choice;
        std::cin >> choice;
        
        if (choice == 0) return nullptr;
        return Motherboard::getIntelMotherboardByIndex(choice);
    }
    else if (platformName == "AMD Platform") {
        Motherboard::printAMDMotherboards();
        std::cout << "Choose (1-" << Motherboard::getAMDMotherboardsCount() << ") or 0 to cancel: ";
        
        int choice;
        std::cin >> choice;
        
        if (choice == 0) return nullptr;
        return Motherboard::getAMDMotherboardByIndex(choice);
    }
    else {
        Motherboard::printServerMotherboards();
        std::cout << "Choose (1-" << Motherboard::getServerMotherboardsCount() << ") or 0 to cancel: ";
        
        int choice;
        std::cin >> choice;
        
        if (choice == 0) return nullptr;
        return Motherboard::getServerMotherboardByIndex(choice);
    }
}

/**
 * @brief Интерактивный выбор видеокарты пользователем
 * @return Указатель на выбранную видеокарту или nullptr при отказе/выборе "None"
 */
GPU* selectGPU() {
    std::cout << "\nAvailable GPUs:" << std::endl;
    GPU::printGPUs();
    std::cout << "Choose (1-" << GPU::getGPUsCount() << ") or 0 to cancel: ";
    
    int choice;
    std::cin >> choice;
    
    if (choice == 0) return nullptr;
    return GPU::getGPUByIndex(choice);
}

/**
 * @brief Интерактивный выбор модулей оперативной памяти
 * @return Вектор указателей на выбранные модули RAM
 */
std::vector<RAM*> selectRAM() {
    std::vector<RAM*> ramModules;
    
    std::cout << "\nAvailable RAM options:" << std::endl;
    RAM::printRAMs();
    std::cout << "Choose (1-" << RAM::getRAMsCount() << ") or 0 to cancel: ";
    
    int choice;
    std::cin >> choice;
    
    if (choice == 0) return ramModules;
    
    RAM* newRam = RAM::getRAMByIndex(choice);
    if (newRam) {
        ramModules.push_back(newRam);
        
        char more;
        std::cout << "Add more RAM? (y/n): ";
        std::cin >> more;
        if (more == 'y' || more == 'Y') {
            std::vector<RAM*> additional = selectRAM();
            ramModules.insert(ramModules.end(), additional.begin(), additional.end());
        }
    }
    
    return ramModules;
}

/**
 * @brief Интерактивный выбор накопителей
 * @return Вектор указателей на выбранные накопители
 */
std::vector<Storage*> selectStorage() {
    std::vector<Storage*> storageDevices;
    
    std::cout << "\nAvailable Storage options:" << std::endl;
    Storage::printStorages();
    std::cout << "Choose (1-" << Storage::getStoragesCount() << ") or 0 to cancel: ";
    
    int choice;
    std::cin >> choice;
    
    if (choice == 0) return storageDevices;
    
    Storage* newStorage = Storage::getStorageByIndex(choice);
    if (newStorage) {
        storageDevices.push_back(newStorage);
        
        char more;
        std::cout << "Add additional storage? (y/n): ";
        std::cin >> more;
        if (more == 'y' || more == 'Y') {
            std::vector<Storage*> additional = selectStorage();
            storageDevices.insert(storageDevices.end(), additional.begin(), additional.end());
        }
    }
    
    return storageDevices;
}

/**
 * @brief Интерактивный выбор блока питания
 * @return Указатель на выбранный блок питания или nullptr при отмене
 */
PowerSupply* selectPSU() {
    std::cout << "\nAvailable Power Supplies:" << std::endl;
    PowerSupply::printPSUs();
    std::cout << "Choose (1-" << PowerSupply::getPSUsCount() << ") or 0 to cancel: ";
    
    int choice;
    std::cin >> choice;
    
    if (choice == 0) return nullptr;
    return PowerSupply::getPSUByIndex(choice);
}

/**
 * @brief Интерактивный выбор системы охлаждения
 * @return Указатель на выбранную систему охлаждения или nullptr при отмене
 */
Cooling* selectCooling() {
    std::cout << "\nAvailable Cooling solutions:" << std::endl;
    Cooling::printCoolings();
    std::cout << "Choose (1-" << Cooling::getCoolingsCount() << ") or 0 to cancel: ";
    
    int choice;
    std::cin >> choice;
    
    if (choice == 0) return nullptr;
    return Cooling::getCoolingByIndex(choice);
}

/**
 * @brief Основная функция сборки компьютера с интерактивным выбором
 * @param factory Фабрика компонентов для выбора платформы
 * @param typeName Тип собираемого компьютера (Gaming PC, Workstation, Server Module)
 * @return Указатель на собранный компьютер или nullptr при ошибке/отмене
 * @note Функция управляет всем процессом выбора компонентов и их валидацией
 */
Computer* buildComputer(const ComponentFactory* factory, const std::string& typeName) {
    Computer* computer = new Computer();  ///< Создание нового компьютера
    computer->setType(typeName);  ///< Установка типа
    
    std::string name;
    std::cout << "\nEnter computer name: ";
    std::cin.ignore();  ///< Очистка буфера ввода
    std::getline(std::cin, name);  ///< Ввод имени компьютера
    computer->setName(name);  ///< Установка имени
    
    /// Выбор процессора
    CPU* cpu = selectCPU(factory);
    if (cpu == nullptr) {
        delete computer;
        return nullptr;
    }
    computer->setCPU(cpu);
    std::string cpuSocket = cpu->getSocket();  ///< Получение сокета CPU для проверки
    
    /// Выбор материнской платы
    Motherboard* mb = selectMotherboard(factory);
    if (mb == nullptr) {
        delete computer;
        delete cpu;
        return nullptr;
    }
    
    /// Проверка совместимости сокетов
    if (cpu->getSocket() != mb->getSocket()) {
        std::cout << "\nWARNING: CPU socket (" << cpu->getSocket() 
                  << ") does not match Motherboard socket (" << mb->getSocket() << ")!" << std::endl;
        std::cout << "Compatibility issue! Please select another motherboard." << std::endl;
        delete mb;
        delete computer;
        delete cpu;
        return nullptr;
    }
    
    computer->setMotherboard(mb);
    //std::cout << "\nMotherboard: " << mb->getSpecs() << std::endl;
    
    /// Выбор оперативной памяти
    std::vector<RAM*> ramModules = selectRAM();
    if (ramModules.empty()) {
        delete computer;
        delete cpu;
        delete mb;
        return nullptr;
    }
    for (auto ram : ramModules) {
        computer->addRAM(ram);
    }
    
    /// Выбор видеокарты
    GPU* gpu = selectGPU();
    if (gpu != nullptr) {
        computer->setGPU(gpu);
    }
    
    /// Выбор накопителей
    std::vector<Storage*> storageDevices = selectStorage();
    for (auto storage : storageDevices) {
        computer->addStorage(storage);
    }
    
    /// Выбор блока питания
    PowerSupply* psu = selectPSU();
    if (psu == nullptr) {
        delete computer;
        delete cpu;
        delete mb;
        for (auto ram : ramModules) delete ram;
        for (auto storage : storageDevices) delete storage;
        if (gpu) delete gpu;
        return nullptr;
    }
    computer->setPSU(psu);
    
    /// Выбор системы охлаждения
    Cooling* cooling = selectCooling();
    if (cooling == nullptr) {
        delete computer;
        delete cpu;
        delete mb;
        for (auto ram : ramModules) delete ram;
        for (auto storage : storageDevices) delete storage;
        if (gpu) delete gpu;
        delete psu;
        return nullptr;
    }
    computer->setCooling(cooling);
    
    /// Добавление периферии по желанию
    char addPeripherals;
    std::cout << "\nAdd peripherals (monitor, keyboard, mouse)? (y/n): ";
    std::cin >> addPeripherals;
    if (addPeripherals == 'y' || addPeripherals == 'Y') {
        computer->addPeripheral(new Peripheral("Dell 27 4K Monitor", 350.0, "Dell", "Monitor", "DisplayPort"));
        computer->addPeripheral(new Peripheral("Logitech MK235", 40.0, "Logitech", "Keyboard+Mouse", "USB"));
    }
    
    return computer;  ///< Возврат готового компьютера
}

/**
 * @brief Отображение главного меню программы
 */
void showMainMenu() {
    std::cout << "\nCOMPUTER CONFIGURATOR" << std::endl;
    std::cout << "1. Build Gaming PC" << std::endl;
    std::cout << "2. Build Workstation" << std::endl;
    std::cout << "3. Build Server Module" << std::endl;
    std::cout << "4. Load Preset" << std::endl;
    std::cout << "5. Save Current as Preset" << std::endl;
    std::cout << "6. List Presets" << std::endl;
    std::cout << "7. Show Price Catalog" << std::endl;
    std::cout << "8. Run All Tests" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Choose option: ";
}

/**
 * @brief Отображение меню выбора платформы
 */
void showPlatformMenu() {
    std::cout << "\nSelect Platform:" << std::endl;
    std::cout << "1. Intel Platform" << std::endl;
    std::cout << "2. AMD Platform" << std::endl;
    std::cout << "Choose (1-2) or 0 to cancel: ";
}

/**
 * @brief Отображение меню выбора пресета
 */
void showPresetMenu() {
    std::cout << "\nAvailable Presets:" << std::endl;
    std::cout << "1. Gaming PC Preset" << std::endl;
    std::cout << "2. Workstation Preset" << std::endl;
    std::cout << "3. Server Preset" << std::endl;
    std::cout << "4. Back to Main Menu" << std::endl;
    std::cout << "Choose: ";
}

/**
 * @brief Главная функция программы
 * @return 0 при успешном завершении
 * @details Инициализирует пресеты по умолчанию, управляет главным циклом меню,
 *          обрабатывает выбор пользователя и управляет памятью.
 */
int main() {
    PresetManager* presetMgr = PresetManager::getInstance();  ///< Получение экземпляра менеджера пресетов
    Computer* currentPC = nullptr;  ///< Текущий выбранный компьютер
    int choice;  ///< Выбор пользователя
    
    /// Инициализация пресетов по умолчанию
    IntelFactory intelFactory;
    GamingPCBuilder gamingBuilder(&intelFactory);
    Director gamingDirector(&gamingBuilder);
    Computer* gamingPreset = gamingDirector.constructCompleteComputer();
    gamingPreset->setName("Gaming PC Preset");
    presetMgr->savePresetSilent("Gaming PC Preset", gamingPreset);
    delete gamingPreset;
    
    AMDFactory amdFactory;
    WorkstationBuilder wsBuilder(&amdFactory);
    Director wsDirector(&wsBuilder);
    Computer* wsPreset = wsDirector.constructCompleteComputer();
    wsPreset->setName("Workstation Preset");
    presetMgr->savePresetSilent("Workstation Preset", wsPreset);
    delete wsPreset;
    
    ServerFactory serverFactory;
    ServerBuilder serverBuilder(&serverFactory);
    Director serverDirector(&serverBuilder);
    Computer* serverPreset = serverDirector.constructCompleteComputer();
    serverPreset->setName("Server Preset");
    presetMgr->savePresetSilent("Server Preset", serverPreset);
    delete serverPreset;
    
    /// Главный цикл программы
    do {
        showMainMenu();  ///< Показ главного меню
        std::cin >> choice;  ///< Ввод выбора
        
        switch (choice) {
            case 1: {  ///< Сборка игрового ПК
                showPlatformMenu();
                int platform;
                std::cin >> platform;
                
                if (platform == 0) break;
                
                if (currentPC) delete currentPC;  ///< Очистка предыдущего компьютера
                
                /// Сборка на выбранной платформе
                if (platform == 1) {
                    IntelFactory factory;
                    currentPC = buildComputer(&factory, "Gaming PC");
                } else if (platform == 2) {
                    AMDFactory factory;
                    currentPC = buildComputer(&factory, "Gaming PC");
                } else {
                    std::cout << "Invalid platform!" << std::endl;
                    break;
                }
                
                if (currentPC) {
                    currentPC->printSpecification();  ///< Вывод спецификации
                    
                    char save;
                    std::cout << "\nSave this configuration as preset? (y/n): ";
                    std::cin >> save;
                    if (save == 'y' || save == 'Y') {
                        std::string presetName;
                        std::cout << "Enter preset name: ";
                        std::cin >> presetName;
                        presetMgr->savePreset(presetName, currentPC);
                    }
                }
                break;
            }
            case 2: {  ///< Сборка рабочей станции
                showPlatformMenu();
                int platform;
                std::cin >> platform;
                
                if (platform == 0) break;
                
                if (currentPC) delete currentPC;
                
                if (platform == 1) {
                    IntelFactory factory;
                    currentPC = buildComputer(&factory, "Workstation");
                } else if (platform == 2) {
                    AMDFactory factory;
                    currentPC = buildComputer(&factory, "Workstation");
                } else {
                    std::cout << "Invalid platform!" << std::endl;
                    break;
                }
                
                if (currentPC) {
                    currentPC->printSpecification();
                    
                    char save;
                    std::cout << "\nSave this configuration as preset? (y/n): ";
                    std::cin >> save;
                    if (save == 'y' || save == 'Y') {
                        std::string presetName;
                        std::cout << "Enter preset name: ";
                        std::cin >> presetName;
                        presetMgr->savePreset(presetName, currentPC);
                    }
                }
                break;
            }
            case 3: {  ///< Сборка серверного модуля
                std::cout << "\nSelect Server Platform:" << std::endl;
                std::cout << "1. Intel Xeon Platform" << std::endl;
                std::cout << "2. AMD EPYC Platform" << std::endl;
                std::cout << "Choose (1-2) or 0 to cancel: ";
                int platform;
                std::cin >> platform;
                
                if (platform == 0) break;
                
                if (currentPC) delete currentPC;
                
                if (platform == 1) {
                    ServerFactory factory;
                    currentPC = buildComputer(&factory, "Server Module");
                } else if (platform == 2) {
                    std::cout << "\nAMD EPYC platform coming soon. Using Intel Xeon instead." << std::endl;
                    ServerFactory factory;
                    currentPC = buildComputer(&factory, "Server Module");
                } else {
                    std::cout << "Invalid platform!" << std::endl;
                    break;
                }
                
                if (currentPC) {
                    currentPC->printSpecification();
                    
                    char save;
                    std::cout << "\nSave this configuration as preset? (y/n): ";
                    std::cin >> save;
                    if (save == 'y' || save == 'Y') {
                        std::string presetName;
                        std::cout << "Enter preset name: ";
                        std::cin >> presetName;
                        presetMgr->savePreset(presetName, currentPC);
                    }
                }
                break;
            }
            case 4: {  ///< Загрузка пресета
                showPresetMenu();
                int presetChoice;
                std::cin >> presetChoice;
                
                if (presetChoice == 4) break;
                
                Computer* loaded = nullptr;
                
                if (presetChoice == 1) {
                    loaded = presetMgr->loadPreset("Gaming PC Preset");
                } else if (presetChoice == 2) {
                    loaded = presetMgr->loadPreset("Workstation Preset");
                } else if (presetChoice == 3) {
                    loaded = presetMgr->loadPreset("Server Preset");
                }
                
                if (loaded) {
                    if (currentPC) delete currentPC;
                    currentPC = loaded;
                    currentPC->printSpecification();
                }
                break;
            }
            case 5: {  ///< Сохранение текущего компьютера как пресет
                if (currentPC) {
                    std::string name;
                    std::cout << "Enter preset name: ";
                    std::cin >> name;
                    presetMgr->savePreset(name, currentPC);
                } else {
                    std::cout << "No computer to save!" << std::endl;
                }
                break;
            }
            case 6:  ///< Список пресетов
                presetMgr->listPresets();
                break;
            case 7:  ///< Показ каталога цен
                PriceCatalog::getInstance()->printCatalog();
                break;
            case 8:  ///< Запуск всех тестов
                testFactoryPattern();
                testSingletonPattern();
                testPrototypePattern();
                break;
            case 0:  ///< Выход из программы
                std::cout << "Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice!" << std::endl;
        }
    } while (choice != 0);
    
    delete currentPC;  ///< Очистка текущего компьютера
    
    /// Уничтожение синглтонов
    PresetManager::destroyInstance();
    PriceCatalog::destroyInstance();
    
    std::cout << "\nPROGRAM FINISHED" << std::endl;
    
    return 0;  ///< Успешное завершение
}