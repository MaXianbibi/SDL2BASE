/**
 * 
 * EventMagager.hpp
 * 
 * Une class incroyablement, coupler aux signaux, qui permet de gerer les evenements
 * dynamiquement, sans avoir a creer des signaux a la main.
 * 
 * les macros rendend la syntaxe plus simple
 * 
 * 
 */


#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include "signal_beta.hpp"

#include <unordered_map>
#include <memory>
#include <string>
#include <iostream>
#include <typeindex>


// Macros pour simplifier l'utilisation de l'EventManager
// Non du signal, puis les types des arguments
#define ADD_SIGNAL(signal_name, ...) EventManager::getInstance().addSignal<__VA_ARGS__>(signal_name)

// Non du signal, puis les arguments
#define GET_SIGNAL(signal_name, ...) EventManager::getInstance().getSignal<__VA_ARGS__>(signal_name)
#define EMIT_SIGNAL(...) EventManager::getInstance().emitSignal(__VA_ARGS__)


class EventManager
{
public:
    // Singleton
    static EventManager& getInstance() {
        static EventManager instance;
        return instance;
    }
    EventManager(const EventManager&) = delete;
    EventManager& operator=(const EventManager&) = delete;

    template <typename... Args>
    Signal_Beta<Args...>* addSignal(const std::string& name) {

        if (signal_map.find(name) != signal_map.end()) {
            return getSignal<Args...>(name);
        }

        auto signal = std::make_shared<Signal_Beta<Args...>>();
        signal_map[name] = signal;
        return signal.get();
    }

    template <typename... Args>
    Signal_Beta<Args...>* getSignal(const std::string& name) {
        auto it = signal_map.find(name);
        if (it != signal_map.end()) {
            auto signal = std::dynamic_pointer_cast<Signal_Beta<Args...>>(it->second);
            if (signal) {
                return signal.get();
            } else {
                std::cerr << "Error: Signal types do not match for '" << name << "'" << std::endl;
                return nullptr;
            }
        } else {
            std::cerr << "Error: Signal '" << name << "' not found." << std::endl;
            return nullptr;
        }
    }

    template <typename... Args>
    void emitSignal(const std::string& name, Args... args) {
        auto signal = getSignal<Args...>(name);
        if (signal) {
            signal->emit(args...);
        }
    }

private:
    EventManager() = default;
    ~EventManager() = default;
    std::unordered_map<std::string, std::shared_ptr<BaseSignal>> signal_map;
};

#endif
