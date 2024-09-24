#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include "signal_beta.hpp"

#include <unordered_map>
#include <memory>
#include <string>
#include <iostream>
#include <typeindex>

#define ADD_SIGNAL(signal_name, ...) EventManager::getInstance().addSignal<__VA_ARGS__>(signal_name)
#define GET_SIGNAL(signal_name, ...) EventManager::getInstance().getSignal<__VA_ARGS__>(signal_name)
#define EMIT_SIGNAL(signal_name, ...) EventManager::getInstance().emitSignal(signal_name, __VA_ARGS__)

class EventManager
{
public:
    // Méthode statique pour obtenir l'instance unique du singleton
    static EventManager& getInstance() {
        static EventManager instance;
        return instance;
    }

    // Supprimer les méthodes de copie et d'assignation
    EventManager(const EventManager&) = delete;
    EventManager& operator=(const EventManager&) = delete;

    // Ajouter un signal et retourner un pointeur vers celui-ci
    template <typename... Args>
    Signal_Beta<Args...>* addSignal(const std::string& name) {
        auto signal = std::make_shared<Signal_Beta<Args...>>();
        signal_map[name] = signal;
        return signal.get();
    }

    // Récupérer un signal
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

    // Émettre un signal
    template <typename... Args>
    void emitSignal(const std::string& name, Args... args) {
        auto it = signal_map.find(name);
        if (it != signal_map.end()) {
            auto signal = std::dynamic_pointer_cast<Signal_Beta<Args...>>(it->second);
            if (signal) {
                signal->emit(std::forward<Args>(args)...);
            } else {
                std::cerr << "Error: Signal types do not match for '" << name << "'" << std::endl;
            }
        } else {
            std::cerr << "Error: Signal '" << name << "' not found." << std::endl;
        }
    }

private:
    // Constructeur privé pour empêcher l'instanciation directe
    EventManager() = default;
    ~EventManager() = default;

    // Stocker les signaux en tant que std::shared_ptr<BaseSignal>
    std::unordered_map<std::string, std::shared_ptr<BaseSignal>> signal_map;
};

#endif
