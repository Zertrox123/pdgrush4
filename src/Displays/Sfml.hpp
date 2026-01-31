#pragma once
#include "IDisplay.hpp"
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>
#include <SFML/Graphics.hpp>

namespace Display{ 
    class Sfml: public Krell::IDisplay {
private:

public:
        ~Sfml() override;
        bool init() override;

        void NewSection(std::string Name) override;
        bool drawText(std::string text) override;
    };
}
