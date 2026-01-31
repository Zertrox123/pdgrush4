#pragma once
#include "Modules/IModule.hpp"
#include <string>
class Date : public Krell::IModule {
    private:
        std::string _name;
    public:
        Date();
        void Draw(Krell::IDisplay *ui) override;
};
