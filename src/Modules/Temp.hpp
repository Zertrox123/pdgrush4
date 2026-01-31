#pragma once
#include "Modules/IModule.hpp"
#include <string>

class Temp: public Krell::IModule {
private:
    std::string _name;
public:
    Temp();
    void Draw(Krell::IDisplay *ui) override;
};
