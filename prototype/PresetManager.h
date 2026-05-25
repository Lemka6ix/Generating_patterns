#ifndef PRESET_MANAGER_H
#define PRESET_MANAGER_H

#include "../builder/Computer.h"
#include <map>
#include <string>
#include <iostream>

class PresetManager {
private:
    static PresetManager* instance;
    std::map<std::string, Computer*> presets;
    
    PresetManager() = default;
    PresetManager(const PresetManager&) = delete;
    PresetManager& operator=(const PresetManager&) = delete;
    
public:
    static PresetManager* getInstance() {
        if (!instance) {
            instance = new PresetManager();
        }
        return instance;
    }
    
    static void destroyInstance() {
        if (instance) {
            for (auto& pair : instance->presets) {
                delete pair.second;
            }
            delete instance;
            instance = nullptr;
        }
    }
    
    ~PresetManager() {
        for (auto& pair : presets) {
            delete pair.second;
        }
    }
    
    bool savePreset(const std::string& name, Computer* computer) {
        if (!computer) return false;
        
        Computer* clone = new Computer(*computer);
        clone->setName(name);
        
        auto it = presets.find(name);
        if (it != presets.end()) {
            delete it->second;
        }
        
        presets[name] = clone;
        std::cout << "Preset '" << name << "' saved successfully" << std::endl;
        return true;
    }
    
    Computer* loadPreset(const std::string& name) {
        auto it = presets.find(name);
        if (it != presets.end()) {
            Computer* loaded = new Computer(*it->second);
            loaded->setName(it->second->getName() + " (loaded)");
            std::cout << "Preset '" << name << "' loaded successfully" << std::endl;
            return loaded;
        }
        std::cout << "Preset '" << name << "' not found" << std::endl;
        return nullptr;
    }
    
    void listPresets() const {
        if (presets.empty()) {
            std::cout << "No presets available" << std::endl;
            return;
        }
        
        std::cout << "\n=== SAVED PRESETS ===" << std::endl;
        for (const auto& [name, computer] : presets) {
            std::cout << name << ": $" << computer->calculateTotalPrice() << std::endl;
        }
    }
    
    void deletePreset(const std::string& name) {
        auto it = presets.find(name);
        if (it != presets.end()) {
            delete it->second;
            presets.erase(it);
            std::cout << "Preset '" << name << "' deleted" << std::endl;
        }
    }
    
    bool hasPreset(const std::string& name) const {
        return presets.find(name) != presets.end();
    }
};

PresetManager* PresetManager::instance = nullptr;

#endif