#pragma once
#include "IDisplay.hpp"
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>
#include <SFML/Graphics.hpp>

namespace Display{ 
    class Sfml: public Krell::IDisplay {
private:
        sf::RenderWindow* window = nullptr;
        sf::Font* font = nullptr;
        sf::View* view = nullptr;
        float lastsectionpos = 0;
        float sectionheight = 0;
        float cursor = 0;
        float scrolloffset = 0.0f;
        float currentcontent = 0.0f;
public:
        ~Sfml() override;
        bool init() override;

        void NewSection(std::string Name) override;
        bool drawText(std::string text) override;
        void refresh(void) override;
    };
}
