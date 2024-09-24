#ifndef SIGNAL_BETA_HPP
#define SIGNAL_BETA_HPP

#include <iostream>
#include <unordered_map>
#include <string>
#include <functional>
#include <memory>
#include <vector>

// Classe de base abstraite pour les signaux
class BaseSignal {
public:
    virtual ~BaseSignal() = default;
    virtual void emit() = 0;  // Méthode virtuelle pure pour émettre un signal
};

// Classe template dérivée pour les signaux avec arguments
template<typename... Args>
class Signal_Beta : public BaseSignal {
public:
    // Connecter un callback qui prend des arguments de type Args...
    void connect(const std::function<void(Args...)>& slot) {
        callbacks.push_back(slot);
    }

    // Émettre le signal avec des arguments
    void emit(Args... args)  {
        for (auto& callback : callbacks) {
            callback(args...);
        }
    }

    // Implémentation de la méthode virtuelle pure (sans arguments)
    void emit() override {
        // Si aucun argument n'est fourni, afficher un message d'erreur
        std::cout << "Signal requires arguments, none provided." << std::endl;
    }

private:
    std::vector<std::function<void(Args...)>> callbacks;  // Liste des callbacks
};

// Spécialisation de la classe pour le cas sans arguments
template<>
class Signal_Beta<> : public BaseSignal {
public:
    // Connecter un callback qui ne prend aucun argument
    void connect(const std::function<void()>& slot) {
        callbacks.push_back(slot);
    }

    // Émettre le signal sans arguments
    void emit() override {
        for (auto& callback : callbacks) {
            callback();
        }
    }

private:
    std::vector<std::function<void()>> callbacks;  // Liste des callbacks
};

#endif
