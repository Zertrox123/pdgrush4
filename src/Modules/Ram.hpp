#pragma once
#include "Modules/IModule.hpp"
#include <string>

class Ram : public Krell::IModule {
    private:
        std::string _name;
    public:
        Ram();
        void Draw(Krell::IDisplay *ui) override;
};
