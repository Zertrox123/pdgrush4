#pragma once
#include "Modules/IModule.hpp"
#include <string>

class Battery : public Krell::IModule {
    private:
        std::string _name;
    public:
        Battery();
        void Draw(Krell::IDisplay *ui) override;
};
