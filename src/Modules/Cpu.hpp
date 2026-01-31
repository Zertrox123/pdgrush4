#pragma once
#include "Modules/IModule.hpp"
#include <string>

class Cpu : public Krell::IModule {
private:
    std::string _model;
    int _cores;
    long long _prevIdle;
    long long _prevTotal;
public:
    Cpu();
    void Draw(Krell::IDisplay *ui) override;
};
