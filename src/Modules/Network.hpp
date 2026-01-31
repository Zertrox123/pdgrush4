#pragma once
#include "Modules/IModule.hpp"
#include <string>
class Network : public Krell::IModule {
    private:
        std::string _name;
    public:
        Network();
        void Draw(Krell::IDisplay *ui) override;
};
