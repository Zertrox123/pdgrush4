#pragma once

#include "Displays/IDisplay.hpp"
#include "Modules/IModule.hpp"
#include <string>

class Hostname : Krell::IModule {
    private:
        std::string _name;
    public:
        Hostname();
        void Draw(Krell::IDisplay *winapi);
};
