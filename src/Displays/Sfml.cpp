#include <iostream>
#include "Sfml.hpp"

bool Display::Sfml::init() {
    auto window = new sf::RenderWindow();
    window->create(sf::VideoMode(sf::Vector2u{1280, 720}), "sfml", sf::Style::Titlebar | sf::Style::Close);
    return true;
};

Display::Sfml::~Sfml() {
}

void Display::Sfml::NewSection(std::string Name) {
    std::cout << Name << std::endl;
    return;
};

bool Display::Sfml::drawText(std::string text) {
    std::cout << text << std::endl;
    return true;
};
