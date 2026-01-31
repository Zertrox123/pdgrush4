#pragma once
#include "Modules/IModule.hpp"
#include <string>

class Disk : public Krell::IModule {
    private:
        std::string _name;
    public:
        Disk();
        void Draw(Krell::IDisplay *ui) override;
};
