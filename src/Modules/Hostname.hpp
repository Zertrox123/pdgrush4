#pragma once

#include "Displays/IDisplay.hpp"
#include "Modules/IModule.hpp"

class Hostname : Krell::IModule {
    public:
        void Draw(Krell::IDisplay winapi);
};
