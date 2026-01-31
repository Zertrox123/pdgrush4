#pragma once
#include "Modules/IModule.hpp"
#include <string>

class Users : public Krell::IModule {
private:
    std::string _name;
public:
    Users();
    void Draw(Krell::IDisplay *ui) override;
};
