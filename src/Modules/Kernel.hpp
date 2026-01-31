#pragma once
#include "Modules/IModule.hpp"
#include <string>

class Kernel : public Krell::IModule {
private:
    std::string _name;
public:
    Kernel();
    void Draw(Krell::IDisplay *ui) override;
}; 
