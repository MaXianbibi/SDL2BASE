/**
 * Une class qui sert a simuler les signaux dans godots,
 * Cette class peut etre init seul, mais le but cest de la couper avec EventManager
 * 
 * 2 Version de la class Signal
 * Une version avec des arguments et une sans arguments
 * Il font la meme chose.
 * 
 * C'est un vecteur de fonction ( callbacks ), souvent anonyme,
 * qui est appeler quand le signal est emis
 * 
 * Connect peut etre utilser autant de fois que vous voulez
 * 
 * le Signal ne peut pas changer de type, il est fixer a la creation
 * Pour une utilastion plus dynamique, voir EventManager
 * 
 */

#ifndef SIGNAL_BETA_HPP
#define SIGNAL_BETA_HPP

#include <iostream>
#include <unordered_map>
#include <string>
#include <functional>
#include <memory>
#include <vector>


// Ne doit pas être instanciée directement
class BaseSignal {
public:
    virtual ~BaseSignal() = default;
    virtual void emit() = 0; 
};

// Classe template dérivée pour les signaux avec arguments
template<typename... Args>
class Signal_Beta : public BaseSignal {
public:


    void connect(const std::function<void(Args...)>& slot) {
        callbacks.push_back(slot);
    }

    void emit(Args... args)  {
        for (auto& callback : callbacks) {
            callback(args...);
        }
    }

    // Edge case pour le cas où aucun argument n'est fourni, dans un template avec des arguments
    void emit() override {
        std::cout << "Signal requires arguments, none provided." << std::endl;
    }

private:
    std::vector<std::function<void(Args...)>> callbacks;
};

// Spécialisation de la classe pour le cas sans arguments
template<>
class Signal_Beta<> : public BaseSignal {
public:
    void connect(const std::function<void()>& slot) {
        callbacks.push_back(slot);
    }

    void emit() override {
        for (auto& callback : callbacks) {
            callback();
        }
    }

private:
    std::vector<std::function<void()>> callbacks;
};

#endif
