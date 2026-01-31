#pragma once
#include "Modules/IModule.hpp"
#include <string>

class Cpu : public Krell::IModule {
private:
    std::string _model;
    int _cores;
    long long _previdle;
    long long _prevtotal;
public:
    Cpu();
    void Draw(Krell::IDisplay *ui) override;
};
