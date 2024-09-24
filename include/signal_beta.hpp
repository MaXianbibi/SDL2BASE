#ifndef SIGNAL_BETA_HPP
#define SIGNAL_BETA_HPP

#include <iostream>
#include <unordered_map>
#include <string>
#include <functional>
#include <memory>
#include <vector>

class BaseSignal {
public:
    virtual ~BaseSignal() = default;
};

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

private:
    std::vector<std::function<void(Args...)>> callbacks;  
};

#endif